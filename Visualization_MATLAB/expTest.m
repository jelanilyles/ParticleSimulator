function [] = expTest(fname)

fid = fopen(fname);
scan = textscan(fid, '%f %f');
a = scan{1,1};
b = scan{1,2};

c = zeros(1,2);

for i = 1:size(a)
    
    num = b(i)*10.0;
    num = round(num);
    check = false;
    j = 1;
    count = 1;
    
    while j <= size(c,1) && check == false
         
        if num == c(j,1)
            
            c(j,2) = c(j,2) + 1;            
            check = true;
            
        end
            
        j = j + 1;
        
    end
        
    if check == false
        
        count = count + 1;
        
        c(count,1) = num;
        c(count,2) = 1;
        
    end
       
    
end

for i = 1:size(c)
    
    xx = c(i,1);
    yy = c(i,2);
    
    hold on;
    plot(xx, yy, 'or', 'MarkerSize', 3, 'MarkerFaceColor', 'b')
    
    
    
end

fclose('all');
    
    
    