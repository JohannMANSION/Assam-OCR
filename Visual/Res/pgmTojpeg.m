clear all
close all
clc

list = dir('*.pgm');
numeros = [];
numero3 = [];
for i = 1:length(list)
    I = imread(list(i).name);
    
    newName = list(i).name(1:end-4);
    newName = [newName, '.jpeg'];
    
    imwrite(I, newName);
end