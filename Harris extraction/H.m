clc;clear;close all;

axis off;
set(gcf,'color','w');

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

data1=load('line.text');
x1=data1(:,1);
y1=data1(:,2);
x2=data1(:,3);
y2=data1(:,4);
size1=numel(x1);

img_gray=imread('gallery.png');
% subplot(121),imshow(img),title('原图');
% img_gray=rgb2gray(img);

psf=fspecial('gaussian',[5,5],1);
Ix=filter2([-1,0,1],img_gray);
Iy=filter2([-1,0,1]',img_gray);
Ix2=filter2(psf,Ix.^2);
Iy2=filter2(psf,Iy.^2);
Ixy=filter2(psf,Ix.*Iy);

[m,n]=size(img_gray);
R=zeros(m,n);
max=0;
for i=1:m
    for j=1:n
        M=[Ix2(i,j),Ixy(i,j); Ixy(i,j),Iy2(i,j)];
        R(i,j)=det(M)-0.05*(trace(M))^2;
        if R(i,j)>max
            max=R(i,j);
        end
    end
end

thresh=0.1;%阈值可调
tmp=zeros(m,n);
neighbours=[-1,-1;-1,0;-1,1;0,-1;0,1;1,-1;1,0;1,1];
for i=2:m-1
    for j=2:n-1
        if R(i,j)>thresh*max
            for k=1:8
                if R(i,j)<R(i+neighbours(k,1),j+neighbours(k,2))
                    break;
                end
            end
            if k==8
                tmp(i,j)=1;
            end
        end
    end
end

% subplot(122),imshow(img),title('角点检测');
imshow(img_gray);
hold on;
for i=2:m-1
    for j=2:n-1
        if tmp(i,j)==1
%             plot(j,i,'rx')
            rectangle('Position', [j-2,i-2,2*2,2*2], 'Curvature', [1 1],'LineWidth',2,'EdgeColor',color_list(4,:));
%             fid = fopen('point2.text','a');
%             fprintf(fid,'%d %d \t ',j,i); 
%             fprintf(fid,'\r\n');  % 换行
%             fclose(fid);
        end
    end
end
for i=1:size1
    line([x1(i)+1,x2(i)+1],[y1(i)+1,y2(i)+1],'linestyle','--','color',color_list(8,:));
end
hold off;      
