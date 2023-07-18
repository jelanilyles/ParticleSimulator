function [] = plotPathways(fname)


fid = fopen(fname);
scan = textscan(fid, '%f %f %f %f %f %f');
a = scan{1,1};
b = scan{1,2};
c = scan{1,3};
d = scan{1,4};
e = scan{1,5};


numsteps = a(1);
numparts = b(1);
size = c(1);



for i=1:numsteps
    p = (i - 1)*numparts + 1;
    
    
    time = i*size/numsteps;
    
    
     for j=1:numparts
        xx = a(j + p);
        yy = b(j + p);
        th = c(j + p);
        
        hold on;
        axis([0 size 0 size])
        plot(xx, yy, 'or', 'MarkerSize', 5, 'MarkerFaceColor', 'r')
        plot(xx - 5*cos(th), yy - 5*sin(th), 'or', 'MarkerSize', 2, 'MarkerFaceColor', 'r')
        plot(xx - 10*cos(th), yy - 10*sin(th), 'or', 'MarkerSize', 2, 'MarkerFaceColor', 'r')
        plot(xx - 15*cos(th), yy - 15*sin(th), 'or', 'MarkerSize', 2, 'MarkerFaceColor', 'r')
        
        
     end
        
        plot(time, 0, 'or', 'MarkerSize', 3, 'MarkerFaceColor', 'b', 'MarkerEdgeColor', 'b')
        hold off;
        
     pause(.05)
     
     if i ~= numsteps
         
        for k=1:numparts
            xx = d(j + p);
            yy = e(j + p);
        
            plot(xx, yy, 'or', 'MarkerSize', 1, 'MarkerFaceColor','w' , 'MarkerEdgeColor', 'w')
        end
        
     end
        
     
    hold off;
     
     
end


        
        
fclose('all');


