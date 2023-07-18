function [] = snapshotPlot(fname)


fid = fopen(fname);
scan = textscan(fid, '%f %f %f %f %f');
a = scan{1,1};
b = scan{1,2};
c = scan{1,3};
% d = scan{1,4};
% e = scan{1,5};


numsteps = a(1);
numparts = b(1);
size = c(1);

i = -1;

while i > numsteps || i < 1
    
    prompt = "Enter a step an integer\n";

    i = input(prompt);
    
    if i > numsteps || i < 1
        
        disp("Invalid step number\n");

    end
end

p = (i - 1)*numparts + 1;
       

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
        
        hold off;
     end
        
        
fclose('all');


