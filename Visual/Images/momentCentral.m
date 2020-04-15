function[muPQ]=momentCentral(p,q,I)

CentreGrav = regionprops(I, 'Centroid');
n10 = CentreGrav.Centroid(1); % Centre de gravité x
n01 = CentreGrav.Centroid(2); % Centre de gravité y


muPQ = 0;
for y=1:1:100
    for x=1:1:100
        muPQ = muPQ + ((x-n10)^p)*((y-n01)^q)*double(I(x,y));
    end
end