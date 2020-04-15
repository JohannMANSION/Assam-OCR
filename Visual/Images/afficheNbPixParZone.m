function[]=afficheNbPixParZone(chiffre)
% Cette fonction prend en entrée :
% chiffre : le chiffre à afficher (de 0 à 9)
% SORTIE : aucune mais affiche :
% - Si chiffre = 9 : les graphes des images squelettes et les graphiques du
% nomre de pixel par image (chaque graphique correspond à une des 9 zones
% définies)
% - Si chiffre = autre valeur, affiche uniquement les graphes du nombre de
% pixel par zone, chaque graphique correspond à une image.


chiffre = chiffre + 1;
if chiffre == 10
    chiffre = 0;
end
chaine = int2str(chiffre);
chaine2 = strcat(chaine,'.jpeg');

ZONE = 1:1:9;
NB11for0 = 1:1:38;
NB12for0 = 1:1:38;
NB13for0 = 1:1:38;
NB21for0 = 1:1:38;
NB22for0 = 1:1:38;
NB23for0 = 1:1:38;
NB31for0 = 1:1:38;
NB32for0 = 1:1:38;
NB33for0 = 1:1:38;

if chiffre == 0
    for i=1:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1); 
        OUT=im2bw(I,graythresh(I)); 
        OUT=imcomplement(OUT);
        OUT=bwmorph(OUT,'skel',inf);
        
        nb11 = sum(sum(OUT(1:32,1:32)));
        nb12 = sum(sum(OUT(1:32,33:66)));
        nb13 = sum(sum(OUT(1:32,67:100)));
        nb21 = sum(sum(OUT(33:66,1:32)));
        nb22 = sum(sum(OUT(33:66,33:66)));
        nb23 = sum(sum(OUT(33:66,67:100)));
        nb31 = sum(sum(OUT(67:100,1:32)));
        nb32 = sum(sum(OUT(67:100,33:66)));
        nb33 = sum(sum(OUT(67:100,67:100)));
        nbPIX = [nb11 nb12 nb13 nb21 nb22 nb23 nb31 nb32 nb33];
        
        NB11for0(i) = nb11;
        NB12for0(i) = nb12;
        NB13for0(i) = nb13;
        NB21for0(i) = nb21;
        NB22for0(i) = nb22;
        NB23for0(i) = nb23;
        NB31for0(i) = nb31;
        NB32for0(i) = nb32;
        NB33for0(i) = nb33;
        %plot(ZONE, nbPIX);
        imshow(OUT);
    end

    for i=10:38
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        OUT=im2bw(I,graythresh(I)); 
        OUT=imcomplement(OUT);
        OUT=bwmorph(OUT,'skel',inf);
        
        nb11 = sum(sum(OUT(1:32,1:32)));
        nb12 = sum(sum(OUT(1:32,33:66)));
        nb13 = sum(sum(OUT(1:32,67:100)));
        nb21 = sum(sum(OUT(33:66,1:32)));
        nb22 = sum(sum(OUT(33:66,33:66)));
        nb23 = sum(sum(OUT(33:66,67:100)));
        nb31 = sum(sum(OUT(67:100,1:32)));
        nb32 = sum(sum(OUT(67:100,33:66)));
        nb33 = sum(sum(OUT(67:100,67:100)));
        nbPIX = [nb11 nb12 nb13 nb21 nb22 nb23 nb31 nb32 nb33];
        
        NB11for0(i) = nb11;
        NB12for0(i) = nb12;
        NB13for0(i) = nb13;
        NB21for0(i) = nb21;
        NB22for0(i) = nb22;
        NB23for0(i) = nb23;
        NB31for0(i) = nb31;
        NB32for0(i) = nb32;
        NB33for0(i) = nb33;
        %plot(ZONE, nbPIX);
        imshow(OUT);
    end
    
    figure;
    subplot(3,3,1); plot(NB11for0);
    subplot(3,3,2); plot(NB12for0);
    subplot(3,3,3); plot(NB13for0);
    subplot(3,3,4); plot(NB21for0);
    subplot(3,3,5); plot(NB22for0);
    subplot(3,3,6); plot(NB23for0);
    subplot(3,3,7); plot(NB31for0);
    subplot(3,3,8); plot(NB32for0);
    subplot(3,3,9); plot(NB33for0);
    
elseif (chiffre == 8) | (chiffre == 9)
    for i=0:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        OUT=im2bw(I,graythresh(I)); 
        OUT=imcomplement(OUT);
        OUT=bwmorph(OUT,'skel',inf);
        
        nb11 = sum(sum(OUT(1:32,1:32)));
        nb12 = sum(sum(OUT(1:32,33:66)));
        nb13 = sum(sum(OUT(1:32,67:100)));
        nb21 = sum(sum(OUT(33:66,1:32)));
        nb22 = sum(sum(OUT(33:66,33:66)));
        nb23 = sum(sum(OUT(33:66,67:100)));
        nb31 = sum(sum(OUT(67:100,1:32)));
        nb32 = sum(sum(OUT(67:100,33:66)));
        nb33 = sum(sum(OUT(67:100,67:100)));
        nbPIX = [nb11 nb12 nb13 nb21 nb22 nb23 nb31 nb32 nb33];
        plot(ZONE, nbPIX);
    end

    for i=10:37
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        OUT=im2bw(I,graythresh(I)); 
        OUT=imcomplement(OUT);
        OUT=bwmorph(OUT,'skel',inf);
        
        nb11 = sum(sum(OUT(1:32,1:32)));
        nb12 = sum(sum(OUT(1:32,33:66)));
        nb13 = sum(sum(OUT(1:32,67:100)));
        nb21 = sum(sum(OUT(33:66,1:32)));
        nb22 = sum(sum(OUT(33:66,33:66)));
        nb23 = sum(sum(OUT(33:66,67:100)));
        nb31 = sum(sum(OUT(67:100,1:32)));
        nb32 = sum(sum(OUT(67:100,33:66)));
        nb33 = sum(sum(OUT(67:100,67:100)));
        nbPIX = [nb11 nb12 nb13 nb21 nb22 nb23 nb31 nb32 nb33];
        plot(ZONE, nbPIX);
    end
    
else
    for i=0:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        OUT=im2bw(I,graythresh(I)); 
        OUT=imcomplement(OUT);
        OUT=bwmorph(OUT,'skel',inf);
        
        nb11 = sum(sum(OUT(1:32,1:32)));
        nb12 = sum(sum(OUT(1:32,33:66)));
        nb13 = sum(sum(OUT(1:32,67:100)));
        nb21 = sum(sum(OUT(33:66,1:32)));
        nb22 = sum(sum(OUT(33:66,33:66)));
        nb23 = sum(sum(OUT(33:66,67:100)));
        nb31 = sum(sum(OUT(67:100,1:32)));
        nb32 = sum(sum(OUT(67:100,33:66)));
        nb33 = sum(sum(OUT(67:100,67:100)));
        nbPIX = [nb11 nb12 nb13 nb21 nb22 nb23 nb31 nb32 nb33];
        plot(ZONE, nbPIX);
    end

    for i=10:38
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        OUT=im2bw(I,graythresh(I)); 
        OUT=imcomplement(OUT);
        OUT=bwmorph(OUT,'skel',inf);
        
        nb11 = sum(sum(OUT(1:32,1:32)));
        nb12 = sum(sum(OUT(1:32,33:66)));
        nb13 = sum(sum(OUT(1:32,67:100)));
        nb21 = sum(sum(OUT(33:66,1:32)));
        nb22 = sum(sum(OUT(33:66,33:66)));
        nb23 = sum(sum(OUT(33:66,67:100)));
        nb31 = sum(sum(OUT(67:100,1:32)));
        nb32 = sum(sum(OUT(67:100,33:66)));
        nb33 = sum(sum(OUT(67:100,67:100)));
        nbPIX = [nb11 nb12 nb13 nb21 nb22 nb23 nb31 nb32 nb33];
        plot(ZONE, nbPIX);
    end
end

