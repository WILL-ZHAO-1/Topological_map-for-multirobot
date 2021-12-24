clear all;
close all;
clc

%…Ë÷√—’…´
%color_list=rand(10,3);
red=[1 0 0];
blue=[0 0.898 0.933];
green = [0 0.804 0.400];
orange=[1,0.549,0];
pink=[1,0.412,0.706];
purple=[0.627,0.125,0.941];
yellow=[0.933,0.933,0];
brown=[0.545,0.102,0.102];
gray=[0.514,0.545,0.545];
black=[0 0 0];
white=[0.961 0.961 0.961];
color_list = [red;blue;green;orange;pink;purple;yellow;brown;gray;black;white];

% axis square;
axis([0,200 ,0,200]);
axis off;
set(gcf,'color','w');

i=imread('reality-map/final.jpg');
imshow(i);
hold on;

data1=load('reality-map/match_node.txt');
y1=data1(:,2);
x1=data1(:,3);
y2=data1(:,5);
x2=data1(:,6);
size1=numel(y1);

data2=load('reality-map/sim_node.txt');
y=data2(:,1);
x=data2(:,2);
size2=numel(y);

num=(0:(size2-1));

%ª≠±ﬂ
for i=1:size1
    line([x1(i)+1,x2(i)+1],[y1(i)+1,y2(i)+1],'color',color_list(10,:));
end

% for j=1:(size1-1)
%     if (j<10)
%         text(x(j)-0.5,y(j),num2str(num(j)),'fontsize',10,'color',color_list(8,:));
%     else
%         text(x(j)-1,y(j),num2str(num(j)),'fontsize',10,'color',color_list(8,:));
%     end
% end

