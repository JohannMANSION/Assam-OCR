function[compacity, OUT6]=CalculCompacity(I)

OUT=im2bw(I,graythresh(I));
OUT2=imcomplement(OUT);
OUT3=imclose(OUT2,strel('disk',4));
OUT4=bwmorph(OUT3,'skel',inf);
OUT5=bwmorph(OUT4,'spur',inf);
OUT6=imfill(OUT5,'holes');

per = regionprops(OUT5, 'Perimeter');
area = regionprops(OUT6, 'Area');
compacity = (per.Perimeter*per.Perimeter)/(4*pi*area.Area);