function [] = overlapdensityFunc(fname,n)


fid = fopen(fname);
scan = textscan(fid, '%f %f %f %f %f');
a = scan{1,1};
b = scan{1,2};
c = scan{1,3};



numsteps = a(1);
numparts = b(1);
size = c(1);
m = zeros(10,2);
r = 1;

    
    
    for h = 500:-1:10

        if mod(size,h) == 0

            frame = h;


            p = (n-1)*numparts+1;
            s = (size / frame)*(size / frame);
            densities = zeros(s);
            q = 1;


            for i = 0:frame/2:size-frame/2
                for j = 0:frame/2:size-frame/2

                    sx = i;
                    fx = i+frame;
                    sy = j;
                    fy = j+frame;

    %                 disp(sx + " " + fx + " " + sy + " " + fy);
                    cells = 0;

                    for k = 1:numparts

                        xx = a(k + p);
                        yy = b(k + p);
                        checkx = false;
                        checky = false;
                        
                        if i ~= size-frame/2 
                            if xx >= sx 
                                if xx < fx

                                    checkx = true;

                                end
                            end
                        else
                            if xx >= sx || xx < size - sx
                                
                                    checkx = true;

                            end
                            
                        end
                        
                        
                        if j ~= size-frame/2
                            if yy >= sy 
                                if yy < fy

                                    checky = true;
                                end
                            end
                        else
                            if yy >= sy || yy < size - sx

                                    checky = true;
                                
                            end
                        end

                            if checkx 
                                if checky
                                    cells = cells+1;
    %                                disp(checkx + " " + checky + " " + xx + " " + yy);
                                end
                            end
                       


             
                        
                        
                        
                    end

                    density = cells/frame;


                    densities(q) = density;

                    q = q+1;

                end
            end

            results = std(densities);



            res = results(1);
            hs = h;

            m(r,1) = hs;
            m(r,2) = res;



    %         
    %         disp(res + " " + hs);
    %         disp(m(r,1) + " " + m(r,2));
            r = r + 1;


        end


    end




    for i = 1:10
        xx = m(i,1);
        yy = m(i,2)*10;       
        hold on
%         axis([0 500 0 10])

       
            plot(xx, yy, 'or' , 'MarkerSize', 2, 'MarkerFaceColor', 'r')
            disp(xx +" "+ yy);
    end




fclose('all');

        
                
                
            
            
            
            
            