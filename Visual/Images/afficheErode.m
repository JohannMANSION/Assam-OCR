function[]=afficheErode(chiffre, SE)
% Cette fonction prend en entrée :
% chiffre : le chiffre à afficher (de 0 à 9)
% SE : l'élément structurant avec lequel on veux réaliser l'opération
% d'érodage
% SORTIE : aucune mais affiche les toutes les images traitées

chiffre = chiffre + 1;
if chiffre == 10
    chiffre = 0;
end
chaine = int2str(chiffre);
chaine2 = strcat(chaine,'.jpeg');

if chiffre == 0
    for i=1:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1); OUT=im2bw(I,graythresh(I)); OUT=imcomplement(OUT); OUT=imerode(OUT,SE); imshow(OUT);
    end

    for i=10:38
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1); OUT=im2bw(I,graythresh(I)); OUT=imcomplement(OUT); OUT=imerode(OUT,SE); imshow(OUT);
    end
    
elseif (chiffre == 8) or (chiffre == 9)
    for i=0:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1); OUT=im2bw(I,graythresh(I)); OUT=imcomplement(OUT); OUT=imerode(OUT,SE); imshow(OUT);
    end

    for i=10:37
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1); OUT=im2bw(I,graythresh(I)); OUT=imcomplement(OUT); OUT=imerode(OUT,SE); imshow(OUT);
    end
    
else
    for i=0:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1); OUT=im2bw(I,graythresh(I)); OUT=imcomplement(OUT); OUT=imerode(OUT,SE); imshow(OUT);
    end

    for i=10:38
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1); OUT=im2bw(I,graythresh(I)); OUT=imcomplement(OUT); OUT=imerode(OUT,SE); imshow(OUT);
    end
end