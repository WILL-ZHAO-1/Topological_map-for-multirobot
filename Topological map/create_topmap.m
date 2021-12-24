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


axis([0,350 ,0,350]);
axis off;
set(gcf,'color','w');
set(gca,'YDir','reverse'); 

data1=load('multi-map/match_node.txt');
y1=data1(:,2);
x1=data1(:,3);
y2=data1(:,5);
x2=data1(:,6);
size1=numel(y1);

data2=load('multi-map/sim_node.txt');
y=data2(:,2);
x=data2(:,3);
size2=numel(y);

door_node=load('multi-map/door_node.txt');
d_y=door_node(:,2);
d_x=door_node(:,3);
door_s=numel(d_y);
% 
cross_node=load('multi-map/cross_node.txt');
c_y=cross_node(:,2);
c_x=cross_node(:,3);
cross_s=numel(c_y);
% 
single_link=load('multi-map/single.txt');
s_y1=single_link(:,2);
s_x1=single_link(:,3);
s_y2=single_link(:,5);
s_x2=single_link(:,6);
single_s=numel(s_y1);

num=(0:(size2-1));

%ª≠±ﬂ
for i=1:size1
    line([x1(i),x2(i)],[y1(i),y2(i)],'color',color_list(10,:));
end
for i=1:single_s
    line([s_x1(i),s_x2(i)],[s_y1(i),s_y2(i)],'color',color_list(1,:));
end
for j=1:size2
    rectangle('Position', [x(j)-3,y(j)-3,2*3,2*3], 'Curvature', [1 1],'facecolor',color_list(4,:));
end

for i=1:door_s
    rectangle('Position', [d_x(i)-3,d_y(i)-3,2*3,2*3], 'Curvature', [1 1],'facecolor',color_list(2,:));
end
for i=1:cross_s
    rectangle('Position', [c_x(i)-3,c_y(i)-3,2*3,2*3], 'Curvature', [1 1],'facecolor',color_list(7,:));
end
for j=1:size2
    if (j<10)
        text(x(j)-0.5,y(j),num2str(num(j)),'fontsize',7,'color',color_list(8,:));
    elseif (j<99)
        text(x(j)-1,y(j),num2str(num(j)),'fontsize',7,'color',color_list(8,:));
        else
         text(x(j)-2,y(j),num2str(num(j)),'fontsize',7,'color',color_list(8,:));
    end
end

