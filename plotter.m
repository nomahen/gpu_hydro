close all;
clear all;
clf;

nx=512;
ngc=2;
i0  = 1;
ibeg=ngc+1;
iend=nx+ngc;
imax=2*ngc+nx;

for i=0:18;
    fhead = 'slug_shuOsher_';
    ext   = '.dat';
    fNum  = i+10000;
    filename=[fhead,num2str(fNum),ext];
    data=dlmread(filename);
    %plot(data(1:4,1),data(1:4,2),'+-');
    %plot(data(ibeg:iend,1),data(ibeg:iend,2),'+-');
    plot(data(:,1),data(:,2),'+-');
    pause(0.1);
end

% ngc = 2;
% iend=6;
% for i = 1:2
%    k0=2*ngc+1;
%    k1=iend-ngc;
%    i
%    k0-i
%    k1+i
%    k1+k0-i
% end