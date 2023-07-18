function [] = msdCalc(fname)

% folder = 'VisualTexts';
% folder2 = 'MSDTexts/';
% fname = fullfile(folder,fname);
fid = fopen(fname);

% splitter = split(fname,'.');
% str = splitter(1);
% str = split(str,'/');
% str = str(2);
% glue = folder2 + string(str) + '_msd.txt';
glue = 'justvelocity_05gstd_msd.txt';

fileID = fopen(glue,'w');

formatSpec = '%8.4f\n';

scan = textscan(fid, '%f %f %f %f %f %f');

a = scan{1,1};
b = scan{1,2};

d = scan{1,4};
e = scan{1,5};


numsteps = a(1);
numparts = b(1);



for i = 2:numsteps 
    
    t = (i - 1)*numparts + 1;
    
    msd = 0;
    
    
    for j = 1:numparts
        
          
       dx = d(j + t);
       dy = e(j + t);
       
       
       msd = msd + (dx^2 + dy^2)/numparts;
       
        
    end
       
        
     fprintf(fileID, formatSpec, msd);
%      disp(msd);
        
end

    fclose('all');
        
        
        
        
        
        
        