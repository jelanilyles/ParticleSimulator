function [] = mstdCalc(fname)

folder = 'VisualTexts';
folder2 = 'MSTDTexts/';
fname = fullfile(folder,fname);
fid = fopen(fname);

splitter = split(fname,'.');
str = splitter(1);
str = split(str,'/');
str = str(2);
glue = folder2 + string(str) + '_mstd.txt';

fileID = fopen(glue,'w');

formatSpec = '%8.4f\n';
scan = textscan(fid, '%f %f %f %f %f %f');
a = scan{1,1};
b = scan{1,2};
c = scan{1,3};


numsteps = a(1);
numparts = b(1);

sumdth = zeros(numparts,1);


for i = 2:numsteps 
    
    
    t = (i - 1)*numparts + 1;
    
    
    
    for j = 1:numparts
       
       th = c(j + t);
       th0 = c(j + t - numparts);
       
       if th < 0
           th = 2*pi + th;
       end
       
       if th0 < 0
           th0 = 2*pi + th0;
       end
       
       dth = th - th0;
       
       
       if dth > pi
           dth = -((2*pi - th) + th0);
       end
       
       if dth < -pi
           dth = (2*pi - th0) + th;
       end
       
       
        sumdth(j) = sumdth(j) + dth;
        
    end
    
    sqdth = 0;
    
    for k = 1:numparts
        sqdth = sqdth + (sumdth(k)^2)/numparts;
    end
    
    
    fprintf(fileID, formatSpec, sqdth);   
        
end

    fclose('all');
        
        
        
        
        
        
        