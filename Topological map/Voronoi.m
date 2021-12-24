img=imread('Voronoi/la.png');
figure
imshow(img,[]);
title('orign');
 
imgo=bwmorph(img,'skel',Inf);
 
figure
imshow(imgo,[]);
title('Voronoi');