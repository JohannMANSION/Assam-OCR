function[]=CalculMoments(chiffre)

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
        subplot(6,7,i+1);
       
        OUT=imcomplement(I);
        OUT = im2bw(OUT,graythresh(OUT));
        OUT = bwmorph(OUT, 'skel', inf) ;

        Area = regionprops(OUT, 'Area'); % Aire de l'objet
        M00(i) = Area.Area;

        CentreGrav = regionprops(OUT, 'Centroid');
        n10(i) = CentreGrav.Centroid(1); % Centre de gravité x
        n01(i) = CentreGrav.Centroid(2); % Centre de gravité y

        Orientation_ = regionprops(OUT, 'Orientation'); % Angle entre l'axe x et l'axe principal de l'ellipse
        Orientation(i) = Orientation_.Orientation;

        MajorAxisLength = regionprops(OUT, 'MajorAxisLength');
        a(i) = MajorAxisLength.MajorAxisLength;

        MinorAxisLength = regionprops(OUT, 'MinorAxisLength');
        b(i) = MinorAxisLength.MinorAxisLength;
        imshow(OUT);
    end

    for i=10:38
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
       
        OUT=imcomplement(I);
        OUT = im2bw(OUT,graythresh(OUT));
        OUT = bwmorph(OUT, 'skel', inf) ;

        Area = regionprops(OUT, 'Area'); % Aire de l'objet
        M00(i) = Area.Area;

        CentreGrav = regionprops(OUT, 'Centroid');
        n10(i) = CentreGrav.Centroid(1); % Centre de gravité x
        n01(i) = CentreGrav.Centroid(2); % Centre de gravité y

        Orientation_ = regionprops(OUT, 'Orientation'); % Angle entre l'axe x et l'axe principal de l'ellipse
        Orientation(i) = Orientation_.Orientation;

        MajorAxisLength = regionprops(OUT, 'MajorAxisLength');
        a(i) = MajorAxisLength.MajorAxisLength;

        MinorAxisLength = regionprops(OUT, 'MinorAxisLength');
        b(i) = MinorAxisLength.MinorAxisLength;
        imshow(OUT);
    end
    
elseif (chiffre == 8) | (chiffre == 9)
    for i=0:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        
        OUT=imcomplement(I);
        OUT = im2bw(OUT,graythresh(OUT));
        OUT = bwmorph(OUT, 'skel', inf) ;

        Area = regionprops(OUT, 'Area'); % Aire de l'objet
        M00(i+1) = Area.Area;

        CentreGrav = regionprops(OUT, 'Centroid');
        n10(i+1) = CentreGrav.Centroid(1); % Centre de gravité x
        n01(i+1) = CentreGrav.Centroid(2); % Centre de gravité y

        Orientation_ = regionprops(OUT, 'Orientation'); % Angle entre l'axe x et l'axe principal de l'ellipse
        Orientation(i+1) = Orientation_.Orientation;

        MajorAxisLength = regionprops(OUT, 'MajorAxisLength');
        a(i+1) = MajorAxisLength.MajorAxisLength;

        MinorAxisLength = regionprops(OUT, 'MinorAxisLength');
        b(i+1) = MinorAxisLength.MinorAxisLength;
        imshow(OUT);
    end

    for i=10:37
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        
        OUT=imcomplement(I);
        OUT = im2bw(OUT,graythresh(OUT));
        OUT = bwmorph(OUT, 'skel', inf) ;

        Area = regionprops(OUT, 'Area'); % Aire de l'objet
        M00(i+1) = Area.Area;

        CentreGrav = regionprops(OUT, 'Centroid');
        n10(i+1) = CentreGrav.Centroid(1); % Centre de gravité x
        n01(i+1) = CentreGrav.Centroid(2); % Centre de gravité y

        Orientation_ = regionprops(OUT, 'Orientation'); % Angle entre l'axe x et l'axe principal de l'ellipse
        Orientation(i+1) = Orientation_.Orientation;

        MajorAxisLength = regionprops(OUT, 'MajorAxisLength');
        a(i+1) = MajorAxisLength.MajorAxisLength;

        MinorAxisLength = regionprops(OUT, 'MinorAxisLength');
        b(i+1) = MinorAxisLength.MinorAxisLength;
        imshow(OUT);
    end
    
else
    for i=0:9
        lecture = strcat('0',int2str(i));
        lecture = strcat(lecture,chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
        
        OUT=imcomplement(I);
        OUT = im2bw(OUT,graythresh(OUT));
        OUT = bwmorph(OUT, 'skel', inf) ;

        Area = regionprops(OUT, 'Area'); % Aire de l'objet
        M00(i+1) = Area.Area;

        CentreGrav = regionprops(OUT, 'Centroid');
        n10(i+1) = CentreGrav.Centroid(1); % Centre de gravité x
        n01(i+1) = CentreGrav.Centroid(2); % Centre de gravité y

        Orientation_ = regionprops(OUT, 'Orientation'); % Angle entre l'axe x et l'axe principal de l'ellipse
        Orientation(i+1) = Orientation_.Orientation;

        MajorAxisLength = regionprops(OUT, 'MajorAxisLength');
        a(i+1) = MajorAxisLength.MajorAxisLength;

        MinorAxisLength = regionprops(OUT, 'MinorAxisLength');
        b(i+1) = MinorAxisLength.MinorAxisLength;
        imshow(OUT);
    end

    for i=10:38
        lecture = strcat(int2str(i),chaine2);
        I = imread(lecture);
        subplot(6,7,i+1);
       
        OUT=imcomplement(I);
        OUT = im2bw(OUT,graythresh(OUT));
        OUT = bwmorph(OUT, 'skel', inf) ;

        Area = regionprops(OUT, 'Area'); % Aire de l'objet
        M00(i+1) = Area.Area;

        CentreGrav = regionprops(OUT, 'Centroid');
        n10(i+1) = CentreGrav.Centroid(1); % Centre de gravité x
        n01(i+1) = CentreGrav.Centroid(2); % Centre de gravité y

        Orientation_ = regionprops(OUT, 'Orientation'); % Angle entre l'axe x et l'axe principal de l'ellipse
        Orientation(i+1) = Orientation_.Orientation;

        MajorAxisLength = regionprops(OUT, 'MajorAxisLength');
        a(i+1) = MajorAxisLength.MajorAxisLength;

        MinorAxisLength = regionprops(OUT, 'MinorAxisLength');
        b(i+1) = MinorAxisLength.MinorAxisLength;
        imshow(OUT);
    end
end

figure;
subplot(2,3,1); plot(M00);
subplot(2,3,2); plot(n10);
subplot(2,3,3); plot(n01);
subplot(2,3,4); plot(Orientation);
subplot(2,3,5); plot(a);
subplot(2,3,6); plot(b);