import torch
import torch.nn as nn

class myLeNet(nn.Module):
    def __init__(self):
        super(myLeNet, self).__init__()
        self.conv1 = nn.Conv2d(in_channels=1, out_channels=6, kernel_size=5, stride=1, padding=0)
        self.pooling = nn.AvgPool2d(kernel_size=2, stride=2)
        self.activation = nn.Tanh()
        self.conv2 = nn.Conv2d(in_channels=6, out_channels=16, kernel_size=5, stride=1, padding=0)
        self.fc1 = nn.Linear(in_features=400, out_features=120)
        self.fc2 = nn.Linear(in_features=120, out_features=84)
        self.fc3 = nn.Linear(in_features=84, out_features=10)

    def forward(self, x):
        x = self.pooling(self.activation(self.conv1(x)))
        x = self.pooling(self.activation(self.conv2(x)))
        # print(x.shape)
        x = self.activation(self.fc1(x.view(x.size(0), -1)))
        x = self.activation(self.fc2(x))
        # x = nn.Softmax(self.fc3(x))
        x = self.fc3(x)
        return x
