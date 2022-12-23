CUDA_VISIBLE_DEVICES=0 python -m torch.distributed.launch \
        --nnodes=1 \
        --node_rank=0 \
        --nproc_per_node=1 \
        --master_addr="172.16.0.12" \
        --master_port="12300" \
        train.py \
        --rank=0 