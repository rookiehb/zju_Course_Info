function createfigure(X1, Y1)
%CREATEFIGURE(X1, Y1)
%  X1:  x 数据的向量
%  Y1:  y 数据的向量

%  由 MATLAB 于 22-Oct-2022 10:55:03 自动生成

% 创建 figure
figure1 = figure;

% 创建 axes
axes1 = axes('Parent',figure1);
hold(axes1,'on');

% 创建 plot
plot1 = plot(X1,Y1,'DisplayName','负载电压','LineWidth',2,'Color',[1 0 0]);

% 下面一行演示创建数据提示的另一种方法。
% datatip(plot1,0.00538462514578811,4.73021216178081);
% 创建 datatip
datatip(plot1,'DataIndex',9694);

% 创建 ylabel
ylabel({'Uo/V'},'FontWeight','bold');

% 创建 xlabel
xlabel('时间 (秒)','FontWeight','bold');

% 创建 title
title('CCM负载电压','FontWeight','bold');

box(axes1,'on');
hold(axes1,'off');
% 设置其余坐标区属性
set(axes1,'FontSize',12,'FontWeight','bold','XGrid','on','YGrid','on');
% 创建 legend
legend(axes1,'show');

