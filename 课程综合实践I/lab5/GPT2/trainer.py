
import os
import time
import torch
from utils import CfgNode as CN
from collections import defaultdict
from torch.utils.data.dataloader import DataLoader
from torch.utils.tensorboard import SummaryWriter

class Trainer:

    @staticmethod
    def get_default_config():
        C = CN()
        # device to train on
        C.device = 'auto'
        # dataloder parameters
        C.num_workers = 0
        # optimizer parameters
        C.max_iters = None
        C.batch_size = 1
        C.learning_rate = 3e-4
        C.betas = (0.9, 0.95)
        C.weight_decay = 0.1    # only applied on matmul weights
        C.grad_norm_clip = 1.0
        return C

    def __init__(self, config, model, train_dataset, args):

        self.config = config
        self.model = model
        self.optimizer = None
        self.train_dataset = train_dataset
        self.callbacks = defaultdict(list)
        self.args = args
        self.device =  torch.device("cuda" if torch.cuda.is_available() else "cpu")
        # determine the device we'll train on
        if config.device == 'auto':
            self.device =  torch.device("cuda" if torch.cuda.is_available() else "cpu")
        
        self.model = self.model.to(self.device)

        # variables that will be assigned to trainer class later for logging and etc
        self.iter_num = 0
        self.iter_time = 0.0
        self.iter_dt = 0.0

    # def add_callback(self, onevent: str, callback):
    #     self.callbacks[onevent].append(callback)

    # def set_callback(self, onevent: str, callback):
    #     self.callbacks[onevent] = [callback]

    # def trigger_callbacks(self, onevent: str):
    #     for callback in self.callbacks.get(onevent, []):
    #         callback(self)

    def run(self):
        writer = SummaryWriter()
        config = self.config

        # setup the optimizer
        self.optimizer = self.model.configure_optimizers(config)

        print("The device is ", self.device)
        self.model = torch.nn.parallel.DistributedDataParallel(self.model, device_ids=[self.args.local_rank])
        train_sampler = torch.utils.data.distributed.DistributedSampler(self.train_dataset)

        train_loader = DataLoader(
            self.train_dataset,
            sampler=train_sampler,
            shuffle=False,
            # pin_memory=True,
            batch_size=config.batch_size,
            num_workers=0
        )

        self.iter_time = time.time()
        print("====== TRAIN TIME ")
        print("====== TRAINING LEN IS {}".format(len(train_loader)))
        for epoch in range(config.max_iters):
            self.model.train()
            for i, (x, y) in enumerate(train_loader):
                x = x.to(self.device)
                y = y.to(self.device)
                _, self.loss = self.model(x, y, self.args)
                self.model.zero_grad()
                self.loss.backward()
                self.optimizer.step()
                
              
                writer.add_scalar("Loss/train", self.loss, epoch*config.max_iters + i)

                if i % 500 == 0 :
                    print("====== EPOCH: [{}/{}], STEP: [{}/{}], TRAIN LOSS {:.5f}".format(
                        epoch, config.max_iters, i, len(train_loader),  self.loss.item()
                    ))
        tnow = time.time()
        self.iter_dt = tnow - self.iter_time
        print("Time is: {:.4f} min".format(self.iter_dt/60))
        writer.flush()
        
        # torch.save(self.model,"gpt_1.pt")

       
