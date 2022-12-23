import os
import torch
import argparse
from model import GPT
from utils import set_seed
from trainer import Trainer
from torch.utils.data import Dataset
from transformers import GPT2Tokenizer


def parse():
    parser = argparse.ArgumentParser()
    parser.add_argument('--local_rank', type=int, default=-1, help='node rank for distrubuted training')
    parser.add_argument("--master_addr", type=str, default="172.16.0.12")
    parser.add_argument("--master_port", type=str, default="12300")
    parser.add_argument("--rank", type=int,default=0)
    args = parser.parse_args()
    return args

class CharDataset(Dataset):
    def __init__(self, data, block_size, tokenizer):
        
        encode_text = tokenizer.encode(data, add_special_tokens = True)
        chars = sorted(list(set(encode_text)))      
        data_size, vocab_size = len(encode_text), len(chars)
        print('data has %d characters, %d unique.' % (data_size, vocab_size))
        self.block_size = block_size
        # self.vocab_size = vocab_size
        # self.data = data
        self.data = encode_text
        self.tokenizer = tokenizer

    def __len__(self):
        return len(self.data) // self.block_size - 1

    def __getitem__(self, idx):
        # grab a chunk of (block_size + 1) characters from the data
        # chunk = self.data[idx : idx + self.block_size + 1 ]
        
        # # print(chunk)
        # # encode every character to an integer
        # dix = [self.stoi[s] for s in chunk]

        # print(len(dix))

        # x = torch.tensor(dix[:-1], dtype=torch.long)
        # y = torch.tensor(dix[1:], dtype=torch.long)
        # print(x.shape, "|", y.shape)
        # exit(1)

        # text_encoded = self.tokenizer.encode(
        #     self.data[idx*self.block_size : idx*self.block_size + self.block_size + 1], 
        #     max_length=self.block_size+1,
        #     # pad_to_max_length = True,
        #     padding = 'max_length',
        #     add_special_tokens = True,
        #     truncation=True
        #     )
        text_encoded = self.data[idx*self.block_size : idx*self.block_size + self.block_size + 1]
        x = torch.tensor(text_encoded[:-1], dtype=torch.long)
        y = torch.tensor(text_encoded[1:], dtype=torch.long)

        # x = torch.tensor(self.data[idx : idx+self.block_size-1], dtype=torch.long)
        # y = torch.tensor(self.data[idx+1 : idx+self.block_size], dtype=torch.long)
        return x, y


if __name__ == '__main__':
    args = parse()
    set_seed(3407)
    text = open('X.txt', 'r').read()
    tokenizer = GPT2Tokenizer.from_pretrained("gpt2")
    tokenizer.padding_side = 'right'
    if tokenizer.pad_token is None:
        tokenizer.add_special_tokens({'pad_token': '[PAD]', 'sep_token':'<|sep|>'})
 
    train_dataset = CharDataset(text, 1024, tokenizer)

    # rank = args.local_rank + args.node_rank * args.local_size
    # torch.distributed.init_process_group("nccl",
    #                         init_method="tcp://{}:{}".format(args.master_addr, args.master_port),
    #                         rank=rank,
    #                         world_size=args.world_size)

    torch.distributed.init_process_group('nccl',
                            init_method='tcp://{}:{}'.format(args.master_addr, args.master_port),
                            world_size = 1,
                            rank = args.rank
                            )
    torch.cuda.set_device(args.local_rank)

    model_config = GPT.get_default_config()
    model_config.block_size = train_dataset.block_size
    model_config.model_type = 'gpt_1'
    model = GPT(model_config)

    train_config = Trainer.get_default_config()
    train_config.max_iters = 4
    trainer = Trainer(train_config, model, train_dataset, args)

    trainer.run()
    torch.distributed.destroy_process_group()
    print("save the model")