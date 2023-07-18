function [] = centeredDisplacement(fname)


fid = fopen(fname);
scan = textscan(fid, '%f %f %f %f %f');
a = scan{1,1};
b = scan{1,2};
c = scan{1,3};
d = scan{1,4};
e = scan{1,5};


numsteps = a(1);
numparts = b(1);
size = c(1);

colors = 0;

for j=1:numparts
    colors(j,1) = rand;
    colors(j,2) = rand;
    colors(j,3) = rand;
        
end

for i=1:numsteps
    p = (i - 1)*numparts + 1;
    
    

    
    
     for j=1:numparts
        dx = d(j + p);
        dy = e(j + p);
        
        hold on;
        
        
        x = colors(j,1);        
        y = colors(j,2);
        z = colors(j,3);
        
        
        plot(dx, dy, 'or', 'MarkerSize', 3, 'MarkerFaceColor',[x,y,z] , 'MarkerEdgeColor', [x,y,z])
        
        hold off;
     end
     
     pause(.05) 
     
end
        
        
fclose('all');


