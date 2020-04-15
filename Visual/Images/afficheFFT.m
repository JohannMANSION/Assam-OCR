function[]=afficheFFT(chiffre)
% Cette fonction prend en entrée :
% chiffre : le chiffre à afficher (de 0 à 9)
% SORTIE : aucune mais affiche les toutes les images traitées

chiffre = chiffre + 1;
if chiffre == 10
    chiffre = 0;
end
chaine = int2str(chiffre);
chaine2 = strcat(chaine,'.jpeg');

%------------ CHOIX DE LA TAILLE DU DISQUE
tailleCercle = 0;
%------------ CHOIX DE LA TAILLE DU DISQUE

if chiffre == 0
    for i=1:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1); 
        OUT=im2bw(I,graythresh(I));
        OUT = imcomplement(OUT)
        OUT = bwmorph(OUT, 'skel', inf);
        OUT = imcomplement(OUT);
        OUT = fft2(OUT);
        OUT = insertShape(real(OUT), 'FilledCircle', [50, 50, tailleCercle],'Color','black','Opacity',1); imshow(OUT);
        OUT = fft2(OUT);
        imshow(OUT);
    end

    for i=10:38
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        OUT=im2bw(I,graythresh(I));
        OUT = imcomplement(OUT)
        OUT = bwmorph(OUT, 'skel', inf);
        OUT = imcomplement(OUT);
        OUT = fft2(OUT);
        OUT = insertShape(real(OUT), 'FilledCircle', [50, 50, tailleCercle],'Color','black','Opacity',1); imshow(OUT);
        OUT = fft2(OUT);
        imshow(OUT);
    end
    
elseif (chiffre == 8) | (chiffre == 9)
    for i=0:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        OUT=im2bw(I,graythresh(I));
        OUT = imcomplement(OUT)
        OUT = bwmorph(OUT, 'skel', inf);
        OUT = imcomplement(OUT);
        OUT = fft2(OUT);
        OUT = insertShape(real(OUT), 'FilledCircle', [50, 50, tailleCercle],'Color','black','Opacity',1); imshow(OUT);
        OUT = fft2(OUT);
        imshow(OUT);
    end

    for i=10:37
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        OUT=im2bw(I,graythresh(I));
        OUT = imcomplement(OUT)
        OUT = bwmorph(OUT, 'skel', inf);
        OUT = imcomplement(OUT);
        OUT = fft2(OUT);
        OUT = insertShape(real(OUT), 'FilledCircle', [50, 50, tailleCercle],'Color','black','Opacity',1); imshow(OUT);
        OUT = fft2(OUT);
        imshow(OUT);
    end
    
else
    for i=0:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        OUT=im2bw(I,graythresh(I));
        OUT = imcomplement(OUT)
        OUT = bwmorph(OUT, 'skel', inf);
        OUT = imcomplement(OUT);
        OUT = fft2(OUT);
        OUT = insertShape(real(OUT), 'FilledCircle', [50, 50, tailleCercle],'Color','black','Opacity',1); imshow(OUT);
        OUT = fft2(OUT);
        imshow(OUT);
    end

    for i=10:38
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        OUT=im2bw(I,graythresh(I));
        OUT = imcomplement(OUT)
        OUT = bwmorph(OUT, 'skel', inf);
        OUT = imcomplement(OUT);
        OUT = fft2(OUT);
        OUT = insertShape(real(OUT), 'FilledCircle', [50, 50, tailleCercle],'Color','black','Opacity',1); imshow(OUT);
        OUT = fft2(OUT);
        imshow(OUT);
    end
end