

%Lab 6 Fourier Series 



clearvars; 
close all;
clc;

%part 2 

%these have same rows so they work if everything was swap and had same
%columns it can work too 
A=ones(2,3);
B=zeros(2,1);
C=2*ones(2,2);

%same columns 
A = ones(2, 3);
B = zeros(1, 3);
%in on comand window enter C = [A; B]


%vectors can be combined (slicing)
a=1:3;
b=[a(3:-1:1),0,a]

%vectors can have additional content 
x = [1, 1, 2, 3, 5];
 x = [x, 8];
 x = [x, 13, 21]