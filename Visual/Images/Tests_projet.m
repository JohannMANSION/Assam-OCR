%% Carctère 0
I=imread('381.jpeg');
figure;
subplot(3,3,1); imshow(I); title('Origine');
subplot(3,3,2); OUT=im2bw(I,graythresh(I)); imshow(OUT); title('Binarisée');
subplot(3,3,3); OUT2=imcomplement(OUT); imshow(OUT2); title('Inversées');
subplot(3,3,4); OUT3=imclose(OUT2,strel('disk',4)); imshow(OUT3); title('Fermeture sphere 4');
subplot(3,3,5); OUT4=bwmorph(OUT3,'skel',inf); imshow(OUT4); title('Skelette infini');
subplot(3,3,6); OUT5=bwmorph(OUT4,'spur',inf); imshow(OUT5); title('Spur infini');
subplot(3,3,7); OUT6=imfill(OUT5,'holes'); imshow(OUT6); title('Remplissage intérieur');

per = regionprops(OUT5, 'Perimeter');
area = regionprops(OUT6, 'Area');
compacity = (per.Perimeter*per.Perimeter)/(4*pi*area.Area);

%% Calcul compacité des 0 base test
compa = 0:1:38;
figure;
for i=0:9
    lecture = strcat('0',int2str(i));
    lecture = strcat(lecture,'1.jpeg');
    I = imread(lecture);
    [val, OUT6] = CalculCompacity(I);
    compa(i+1)=val;
    subplot(6,7,i+1); imshow(OUT6);
end

for i=10:38
    lecture = strcat(int2str(i),'1.jpeg');
    I = imread(lecture);
    [val, OUT6] = CalculCompacity(I);
    compa(i+1)=val;
    subplot(6,7,i+1); imshow(OUT6);
end
compa
max(compa)
min(compa)

%% Test de détection généralisée des boucles.
% L'objectif consiste à partir d'un élément structurant de type disque de
% taille 0 et de réaliser : fermeture, squelette, spur et fill jusqu'à
% obtenir une composante connexe de + de 1 pixel (on augmente le rayon du
% disque de 1 à chaque fois)

% Problème de forme de l'élément structurant ne permettant pas d'obtenir
% une boucle sur l'image 252 --> essayer de plus arondir la forme de
% l'élément structurant et tester (possible amélioration globale du
% programme !)
I = imread('001.jpeg');
figure;

subplot(3,3,1); imshow(I); title('Origine');
subplot(3,3,2); OUT=im2bw(I,graythresh(I)); imshow(OUT); title('Binarisée');
subplot(3,3,3); OUT2=imcomplement(OUT); imshow(OUT2); title('Inversées');
SE = strel('disk',12,0);


subplot(3,3,4); OUT3=imclose(OUT2,SE); imshow(OUT3); title('Fermeture sphere 4');
subplot(3,3,5); OUT4=bwmorph(OUT3,'skel',inf); imshow(OUT4); title('Skelette infini');
subplot(3,3,6); OUT5=bwmorph(OUT4,'spur',inf); imshow(OUT5); title('Spur infini');
subplot(3,3,7); OUT6=imfill(OUT5,'holes'); imshow(OUT6); title('Remplissage intérieur');
norme = norm(double(OUT5)) % Si norme = 1 alors il n'y à qu'un seul pixel blanc dans l'image

L = bwlabel(OUT6);
nbComposantes = max(max(L)) % retourne la plus grande valeur présente dans l'image = nombre de composantes connexes

%% Essai de FFT

subplot(3,3,1); I = imread('013.jpeg'); OUT=im2bw(I,graythresh(I)); imshow(OUT);
subplot(3,3,2); OUT = imcomplement(OUT); imshow(OUT);
subplot(3,3,3); OUT = bwmorph(OUT, 'skel', inf); imshow(OUT);
%subplot(3,3,4); OUT = imdilate(OUT, strel('disk',2)); imshow(OUT);
subplot(3,3,4); OUT = imcomplement(OUT); imshow(OUT);
subplot(3,3,5); OUT = fft2(OUT); imshow(OUT);

subplot(3,3,6); OUT = insertShape(real(OUT), 'FilledCircle', [50, 50, 10],'Color','black','Opacity',1); imshow(OUT);
subplot(3,3,7); OUT = fft2(OUT); imshow(OUT);

%% Essai de dérivée

I = imread('079.jpeg');
filter = [1 0 -1]';

subplot(3,3,1); imshow(I);
subplot(3,3,2); OUT = imfilter(I,filter,'replicate'); imshow(OUT);
%subplot(3,3,2); OUT=im2bw(OUT,graythresh(OUT)); imshow(OUT);
subplot(3,3,3); OUT=imcomplement(I); OUT = im2bw(OUT,graythresh(OUT)); OUT = bwmorph(OUT, 'skel', inf); OUT=imerode(OUT, strel('line',3, 0)); imshow(OUT);

%% Essai de comptage du nombre de pixels du squelette par zone d'image

I = imread('001.jpeg');
subplot(3,3,1); imshow(I);
subplot(3,3,2); OUT=imcomplement(I); imshow(OUT);
subplot(3,3,3); OUT = im2bw(OUT,graythresh(OUT)); imshow(OUT);
subplot(3,3,4); OUT = bwmorph(OUT, 'skel', inf) ; imshow(OUT);

nb11 = sum(sum(OUT(1:32,1:32)));
nb12 = sum(sum(OUT(1:32,33:66)));
nb13 = sum(sum(OUT(1:32,67:100)));
nb21 = sum(sum(OUT(33:66,1:32)));
nb22 = sum(sum(OUT(33:66,33:66)));
nb23 = sum(sum(OUT(33:66,67:100)));
nb31 = sum(sum(OUT(67:100,1:32)));
nb32 = sum(sum(OUT(67:100,33:66)));
nb33 = sum(sum(OUT(67:100,67:100)));

ZONE = 1:1:9;
nbPIX = [nb11 nb12 nb13 nb21 nb22 nb23 nb31 nb32 nb33]
figure;
plot(ZONE, nbPIX)

%% Essais sur le caractère n°4

I = imread('065.jpeg');
subplot(3,3,1); imshow(I);
subplot(3,3,2); OUT=imcomplement(I); imshow(OUT);
subplot(3,3,3); OUT=imclose(OUT,strel('disk', 9)); imshow(OUT);
subplot(3,3,4); OUT = im2bw(OUT,graythresh(OUT)); imshow(OUT);
subplot(3,3,5); OUT = bwmorph(OUT, 'skel', inf) ; imshow(OUT);
subplot(3,3,6); OUT = bwmorph(OUT, 'spur', inf) ; imshow(OUT);
subplot(3,3,7); OUT = imfill(OUT, 'holes'); imshow(OUT);

%% Calcul moments objet

I = imread('001.jpeg');
subplot(3,3,1); imshow(I);
subplot(3,3,2); OUT=imcomplement(I); imshow(OUT);
subplot(3,3,3); OUT = im2bw(OUT,graythresh(OUT)); imshow(OUT);
subplot(3,3,4); OUT = bwmorph(OUT, 'skel', inf) ; imshow(OUT);

Area = regionprops(OUT, 'Area'); % Aire de l'objet
M00 = Area.Area

CentreGrav = regionprops(OUT, 'Centroid');
n10 = CentreGrav.Centroid(1) % Centre de gravité x
n01 = CentreGrav.Centroid(2) % Centre de gravité y

Orientation_ = regionprops(OUT, 'Orientation'); % Angle entre l'axe x et l'axe principal de l'ellipse
Orientation = Orientation_.Orientation

MajorAxisLength = regionprops(OUT, 'MajorAxisLength');
a = MajorAxisLength.MajorAxisLength

MinorAxisLength = regionprops(OUT, 'MinorAxisLength');
b = MinorAxisLength.MinorAxisLength