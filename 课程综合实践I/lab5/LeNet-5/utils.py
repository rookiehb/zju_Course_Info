import torch.utils.data
import torchvision
from torchvision import transforms
from torch.utils.data.dataloader import DataLoader
import numpy as np

Batch_Size = 128
Num_Workers = 1

def prepare_MNIST(batch_size=Batch_Size, num_workers=Num_Workers):
    transform = transforms.Compose([
        transforms.Resize((32, 32)),
        transforms.ToTensor()
    ])

    Training_Set = torchvision.datasets.MNIST("./dataset", train=True, download=True, transform=transform)
    Test_Set = torchvision.datasets.MNIST("./dataset", train=False, download=True, transform=transform)

    trainloader = DataLoader(Training_Set, batch_size=batch_size, shuffle=True, num_workers=num_workers)
    testloader = DataLoader(Test_Set, batch_size=batch_size, shuffle=True, num_workers=num_workers)

    return trainloader, testloader