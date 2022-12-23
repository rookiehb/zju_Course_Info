import torch
import torch.optim as optim
from conv import *
from utils import prepare_MNIST
import shutil
import numpy as np
import torch.nn.functional as F
from torch.autograd import Variable
import torch.nn as nn
from torch.utils.tensorboard import SummaryWriter

writer = SummaryWriter()
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
EPOCH = 15
LR = 1e-4
BATCHSIZE = 64

def train():
    print("Now start training")
    model = myLeNet()
    model = model.to(device)

    optimizer = optim.Adam(model.parameters(), lr=LR)
    loss = nn.CrossEntropyLoss()

    trainloader, testloader = prepare_MNIST(BATCHSIZE, 1)
    print("Already load the data")
    print("size of training set is: ", len(trainloader), "| size of test set is:", len(testloader))
    for epoch in range(EPOCH):
        total_loss, train_acc = 0, 0
        for i, (batch_x, batch_y) in enumerate(trainloader):
            inputs = batch_x.to(device)
            batch_y = batch_y.to(device)
            output = model(inputs)
            l = loss(output, batch_y)
            total_loss = total_loss + l
            train_acc = (output.argmax(dim=1) == batch_y).sum().item() / batch_y.size(0)
            optimizer.zero_grad()
            l.backward()
            optimizer.step()
            writer.add_scalar("Loss/train", l, epoch*EPOCH+i)
            writer.add_scalar("Acc/train", train_acc, epoch * EPOCH + i)

        print("Training Time: Epoch[{}/{}], Total loss {:.4f}"  .format(epoch + 1, EPOCH, total_loss.item()))

    test_acc = 0
    total = 0
    torch.load("LeNet.pkl")
    print("Save model successfully and start to test the model")
    writer.flush()
    model.eval()
    # writer.close()
    for i, (batch_x, batch_y) in enumerate(testloader):
        inputs = batch_x.to(device)
        batch_y = batch_y.to(device)
        testOutput = model(inputs)
        total += batch_y.size(0)
        test_acc += (testOutput.argmax(dim=1) == batch_y).sum().item()

    Total_Acc = test_acc/total
    print("Test accuracy : {}" .format(Total_Acc))

if __name__ == '__main__':
    train()


