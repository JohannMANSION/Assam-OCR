function[]=detectionCerclePourIntegrationC(chiffre)

chiffre = chiffre + 1;
if chiffre == 10
    chiffre = 0;
end
chaine = int2str(chiffre);
chaine2 = strcat(chaine,'.jpeg');

%-------- FIXATION DE LA LIMITE DE TAILLE DE L ELEMENT STRUCTURANT
limite = 12;
%--------

if chiffre == 0
    for i=1:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
       
        OUT=im2bw(I,graythresh(I)); 
        IOK=imcomplement(OUT); 
        
        for i = 0:1:limite
           SE = strel('disk', i);
           OUT=imclose(IOK,SE);
           OUT=bwmorph(OUT,'skel',inf);
           OUT=bwmorph(OUT,'spur',inf);
           OUT=imfill(OUT,'holes');
           nbPixBlanc(i+1) = sum(sum(OUT(:,:))); % i+1 car pas d'indice 0 sur matlab
        end
        
        [valMax, indiceMax] = max(nbPixBlanc);
        SE = strel('disk', indiceMax - 1); % -1 pour compensation
        OUT=imclose(IOK,SE);
        OUT=bwmorph(OUT,'skel',inf);
        OUT=bwmorph(OUT,'spur',inf);
        OUT=imfill(OUT,'holes');
        imshow(OUT);
    end

    for i=10:38
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
       
        OUT=im2bw(I,graythresh(I)); 
        IOK=imcomplement(OUT); 
        
        for i = 0:1:limite
           SE = strel('disk', i);
           OUT=imclose(IOK,SE);
           OUT=bwmorph(OUT,'skel',inf);
           OUT=bwmorph(OUT,'spur',inf);
           OUT=imfill(OUT,'holes');
           nbPixBlanc(i+1) = sum(sum(OUT(:,:))); % i+1 car pas d'indice 0 sur matlab
        end
        
        [valMax, indiceMax] = max(nbPixBlanc);
        SE = strel('disk', indiceMax - 1); % -1 pour compensation
        OUT=imclose(IOK,SE);
        OUT=bwmorph(OUT,'skel',inf);
        OUT=bwmorph(OUT,'spur',inf);
        OUT=imfill(OUT,'holes');
        imshow(OUT);
    end
    
elseif (chiffre == 8) | (chiffre == 9)
    for i=0:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        OUT=im2bw(I,graythresh(I)); 
        IOK=imcomplement(OUT); 
        
        for i = 0:1:limite
           SE = strel('disk', i);
           OUT=imclose(IOK,SE);
           OUT=bwmorph(OUT,'skel',inf);
           OUT=bwmorph(OUT,'spur',inf);
           OUT=imfill(OUT,'holes');
           nbPixBlanc(i+1) = sum(sum(OUT(:,:))); % i+1 car pas d'indice 0 sur matlab
        end
        
        [valMax, indiceMax] = max(nbPixBlanc);
        SE = strel('disk', indiceMax - 1); % -1 pour compensation
        OUT=imclose(IOK,SE);
        OUT=bwmorph(OUT,'skel',inf);
        OUT=bwmorph(OUT,'spur',inf);
        OUT=imfill(OUT,'holes');
        imshow(OUT);
    end

    for i=10:37
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        
        OUT=im2bw(I,graythresh(I)); 
        IOK=imcomplement(OUT); 
        
        for i = 0:1:limite
           SE = strel('disk', i);
           OUT=imclose(IOK,SE);
           OUT=bwmorph(OUT,'skel',inf);
           OUT=bwmorph(OUT,'spur',inf);
           OUT=imfill(OUT,'holes');
           nbPixBlanc(i+1) = sum(sum(OUT(:,:))); % i+1 car pas d'indice 0 sur matlab
        end
        
        [valMax, indiceMax] = max(nbPixBlanc);
        SE = strel('disk', indiceMax - 1); % -1 pour compensation
        OUT=imclose(IOK,SE);
        OUT=bwmorph(OUT,'skel',inf);
        OUT=bwmorph(OUT,'spur',inf);
        OUT=imfill(OUT,'holes');
        imshow(OUT);
    end
    
else
    for i=0:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        OUT=im2bw(I,graythresh(I)); 
        IOK=imcomplement(OUT); 
        
        for i = 0:1:limite
           SE = strel('disk', i);
           OUT=imclose(IOK,SE);
           OUT=bwmorph(OUT,'skel',inf);
           OUT=bwmorph(OUT,'spur',inf);
           OUT=imfill(OUT,'holes');
           nbPixBlanc(i+1) = sum(sum(OUT(:,:))); % i+1 car pas d'indice 0 sur matlab
        end
        
        [valMax, indiceMax] = max(nbPixBlanc);
        SE = strel('disk', indiceMax - 1); % -1 pour compensation
        OUT=imclose(IOK,SE);
        OUT=bwmorph(OUT,'skel',inf);
        OUT=bwmorph(OUT,'spur',inf);
        OUT=imfill(OUT,'holes');
        imshow(OUT);
    end

    for i=10:38
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
       
        OUT=im2bw(I,graythresh(I)); 
        IOK=imcomplement(OUT); 
        
        for i = 0:1:limite
           SE = strel('disk', i);
           OUT=imclose(IOK,SE);
           OUT=bwmorph(OUT,'skel',inf);
           OUT=bwmorph(OUT,'spur',inf);
           OUT=imfill(OUT,'holes');
           nbPixBlanc(i+1) = sum(sum(OUT(:,:))); % i+1 car pas d'indice 0 sur matlab
        end
        
        [valMax, indiceMax] = max(nbPixBlanc);
        SE = strel('disk', indiceMax - 1); % -1 pour compensation
        OUT=imclose(IOK,SE);
        OUT=bwmorph(OUT,'skel',inf);
        OUT=bwmorph(OUT,'spur',inf);
        OUT=imfill(OUT,'holes');
        imshow(OUT);
    end
end