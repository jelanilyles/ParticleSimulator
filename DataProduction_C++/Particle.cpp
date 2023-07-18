/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Particle.h"
#include "GridBox.h"
#include "GridRow.h"
#include <vector>
#include "math.h"
#define PI 3.1415926535

using namespace std;

Particle::Particle() {
    
}
Particle::Particle(double vel, int num, double size, int ore, bool h8) {  // Particle initialization
    
    posx = (double)(size * rand() / RAND_MAX);
    posy = (double)(size * rand() / RAND_MAX);

    posx0 = posx;
    posy0 = posy;
  
    dx = 0.0;
    dy = 0.0;
  
    dxbox = 0;
    dybox = 0;
  
    vel0 = vel;
    
    initialvelocity = vel;
    velocity = vel;
    theta = (double)((2.0 * PI) * rand() / RAND_MAX);
    if(h8){
        theta = 0.0;
    }
    randt = 0.0;
    
    velx = vel * cos(theta);
    vely = vel * sin(theta);
 
   // dr = GGen(0, std);
    sd = dx*dx + dy*dy;
    this->num = num;
    orientation = ore;
    
}

Particle::Particle(double x, double y, int num, double vel, double the, int ore) {                        //Test Particle Initialization
    posx = x;
    posy = y;
    
    velocity = vel;
    theta = the;

    this->num = num;
    
    orientation = ore;
}
void Particle::Update(bool a1, bool b2, bool c3, bool d4, bool e5, bool g7, double k1, double k2, double k3, double alimit, double rlimit, double tlimit, double size, int space, vector<double> ores, vector<double> values) {                                                   // Updates the position based on the velocity
        
        
        double xx, yy;
        
        
        double mean = ores[(orientation - 1)*2];
        double std = ores[2*orientation - 1];
        double lambda = sqrt(2/(std*std));
        
        
        vector<double> forcesums = FindForceSums(alimit, rlimit, tlimit, k1, k2, k3, size, space);
        
        xf = forcesums[0];
        yf = forcesums[1];

        xx = forcesums[2];
        yy = forcesums[3];
        
        xg = -forcesums[4];
        yg = -forcesums[5];
    
        
        
        
        
        if(!a1) {
            xf = 0.0;
            yf = 0.0;
        }
        if(!b2) {
            xg = 0.0;
            yg = 0.0;
        }
        
        if(c3) {
                theta = atan2(yy, xx);
//                AlternateAngle(size, limit);
                if(theta < 0){
                    theta += 2*PI;
                }
        }
        
       
        
        if(e5) {
            randt = EGen(mean, lambda);
        }else{
            randt = GGen(mean, std);
        }
        
        if(d4) {
            theta += randt;
            while(theta > 2*PI){
                theta -= 2*PI;
            }
            while(theta < 0){
                theta += 2*PI;
            }
        }
        
        if(g7) {
            velocity = initialvelocity * VGen(values);
        }
        
        px = posx;
        py = posy;
        ptheta = theta;
        
       
        
        posx += velocity * cos(theta) + xf + xg;
            while(posx >= size) {
                posx = posx - size;
            }
            while(posx < 0.0) {
                posx += size;
            } 
        posy += velocity * sin(theta) + yf + yg;
            while(posy >= size) {
                posy = posy - size;
            }
            while(posy < 0.0) {
                posy += size;
            }
        
    
    
        dx += velocity * cos(theta) + xf + xg;                                                    // Total displacement
        dy += velocity * sin(theta) + yf + yg;

    
    
        dxbox = (int)(((((posx0 + dx) / size)*100)) - (((int)((posx0 + dx) / size)*100) % 100))/100;   // Box displacement, how many times has the particle been transferred across a border
        dybox = (int)(((((posy0 + dy) / size)*100)) - (((int)((posy0 + dx) / size)*100) % 100))/100;
        
    
        sd = dx*dx + dy*dy;
       
     
}    

vector<double> Particle::FindForceSums(double alimit, double rlimit, double tlimit, double k1, double k2, double k3, double size, int space) {
        
        Particle p;
        double xif = 0.0;
        double yif = 0.0;
        
        double xig = 0.0;
        double yig = 0.0;

        double xx = 0.0;
        double yy = 0.0;
        vector<double> forcesums;
        
        double x, y, r;
        
        for(int i = 0; i < close.size(); i++) {
            
            p = close[i]; 
            x = FindX(p, size, space);
            y = FindY(p, size, space);

            r = sqrt(x*x + y*y);
            
            vector<double> forces;
            
            
    
            if(r < alimit || r < rlimit || r < tlimit) {
                
                forces = FindForces(p, alimit, rlimit, tlimit, k1, k2, k3, size, space);
                
                xif += forces[0];
                yif += forces[1];
                                
                xx += forces[2];                     // cartesian sum of sin/cos coordinates proportionalized by distance should produce correct angle
                yy += forces[3];
                
                xig += forces[4];
                yig += forces[5];
                

                                     
            }        
        }
        
        forcesums.push_back(xif);
        forcesums.push_back(yif);
        
        forcesums.push_back(xx);
        forcesums.push_back(yy);
        
        forcesums.push_back(xig);
        forcesums.push_back(yig);

        
        return forcesums;
        
}



double Particle::FindX(Particle p, double size, int space) 
{
    
    double x;                   
    
            if(abs(p.xbox - xbox) <= space) { 
                x = p.posx - posx;
            }else if(p.posx > posx) {
                x = p.posx - posx - size;
            }else if(p.posx < posx) {
                x = size - posx + p.posx;
            }
    
    return x;    
}

double Particle::FindY(Particle p, double size, int space)
{
    double y;
    
            if(abs(p.ybox - ybox) <= space) {
                y = p.posy - posy;
            }else if(p.posy > posy) {
                y = p.posy - posy - size;
            }else if(posy > p.posy) {
                y = size - posy + p.posy;
            }
    
    return y;
}


vector<double> Particle::FindForces(Particle p, double alimit, double rlimit, double tlimit, double k1, double k2, double k3, double size, int space)
{
    vector<double> forces;

    double xf, yf, xx, yy, xg, yg;
    double x, y;
    
    x = FindX(p, size, space);
    y = FindY(p, size, space);
    
    
    
    double r = sqrt(x*x + y*y);
            
    if(r < alimit && r > 0) {
                xf = k1 * (1.0 - r / alimit) * x / r;
                yf = k1 * (1.0 - r / alimit) * y / r;
    } else { 
        xf = 0.0;
        yf = 0.0;
    }
    if(r < rlimit && r > 0) {
                xg = k2 * (1.0 - r / rlimit) * x / r;
                yg = k2 * (1.0 - r / rlimit) * y / r;
    } else {
        xg = 0.0;
        yg = 0.0;
    }
    if(r < tlimit) {          
                xx = (1.0 - r / tlimit) * cos(p.theta);                     // cartesian sum of sin/cos coordinates proportionalized by distance should produce correct angle
                yy = (1.0 - r / tlimit) * sin(p.theta);            
    } else { 
        xx = 0.0;
        yy = 0.0;
    }
    
    if(p.num != num) {
        xx = k3 * xx;
        yy = k3 * yy;
    }
    
                forces.push_back(xf);
                forces.push_back(yf);

                forces.push_back(xx);
                forces.push_back(yy);
                
                forces.push_back(xg);
                forces.push_back(yg);

                
                return forces;
}


void Particle::Adjust(int space, double size, double particlesize)
{
    Particle p;
    double x, y, r;
    
    for(int i = 0; i < this->close.size(); i++) {
        p = close[i];
        x = FindX(p, size, space);
        y = FindY(p, size, space);
        
        if(r < particlesize) {
            touching.push_back(p);
        }
    }
    
    
    
    
}

                               


double Particle::GGen(double mean, double stddv)                                    // Random number generator
{ //Box muller method
        double u1, u2, x, result;
       
        
        u1 = (double)rand() / RAND_MAX;
        u2 = (double)rand() / RAND_MAX;
 
        x = sqrt(-2.0 * log(u1)) * cos((double)(2.0 * PI) * u2);
       
        result = x * stddv + mean;
        
        return result;
}

double Particle::EGen(double mean, double lambda)
{
    double x, y, result;
    double side = 1.0;
    
    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    
    if(y < 0.5) {
        side = -1.0;
    }
    
    
    result = mean + side*(log(1.0-x)/(-lambda));
    
    return result;
    
}

double Particle::LGen(double mean, double max, double min)
{
    double x, y, result, slope;
    double side = 1.0;
    
    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    slope = max - min;
    
    if(y < 0.5) {
        side = -1.0;
    }
    
    result = mean + min + side * slope * sqrt(x);
    
    return result;
}

double Particle::VGen(vector<double> values) {
    
    double x = (double)rand() / RAND_MAX;
    
    int i = 0;
    
    double a1, a2, result;
    
    while(values[i] <= x) {
        i++;
    }
    
    if(values[i-1] == x) {
        
        result = (i-1) / 50;
        
    }else{
        
        a1 = i-1;
        a2 = i;
        
        result = a1 + 50*(a2 - a1)*(x - values[i-1]);
     
    }    

    return result / 454.563;
}




void Particle::AlternateAngle(double size, double alimit, int space) 
{
    double sumt = 0, dif, t1, t2, x, y, r;
    int count = 0;
    t1 = theta;
    
    for(int i = 0; i < this->close.size(); i++) {
         Particle p = close[i]; 
            x = FindX(p, size, space);
            y = FindY(p, size, space);

            r = sqrt(x*x + y*y);
        if(r < alimit & p.num != num) {
            t2 = p.theta;
            dif = t2 - t1;
            
            if(dif > PI) {
                dif = 2*PI - dif;
            } else if(dif < -PI) {
                dif = 2*PI + dif;
            } else if(dif == PI) {
                dif = 0;
            }
            
            sumt += dif * (1 - r/alimit) / 2;
            count++;           
        }    
            
    }
    
    theta += sumt / count;
    
}


void Particle::UpdateGridBox(double size) {
    xbox = 11;
    ybox = 11;
    
    if(posx <= size/10.0) {
            xbox = 0;
        }else if(posx <= 2*size/10.0 && posx > size/10.0) {
            xbox = 1;
        }else if(posx <= 3*size/10.0 && posx > 2*size/10.0) {
            xbox = 2;
        }else if(posx <= 4*size/10.0 && posx > 3*size/10.0) {
            xbox = 3;
        }else if(posx <= 5*size/10.0 && posx > 4*size/10.0) {
            xbox = 4;
        }else if(posx <= 6*size/10.0 && posx > 5*size/10.0) {
            xbox = 5;
        }else if(posx <= 7*size/10.0 && posx > 6*size/10.0) {
            xbox = 6;
        }else if(posx <= 8*size/10.0 && posx > 7*size/10.0) {
            xbox = 7;
        }else if(posx <= 9*size/10.0 && posx > 8*size/10.0) {
            xbox = 8;
        }else{
            xbox = 9;
        }
            
        if(posy <= size/10.0) {
            ybox = 0;
        }else if(posy <= 2*size/10.0 && posy > size/10.0) {
            ybox = 1;
        }else if(posy <= 3*size/10.0 && posy > 2*size/10.0) {
            ybox = 2;
        }else if(posy <= 4*size/10.0 && posy > 3*size/10.0) {
            ybox = 3;
        }else if(posy <= 5*size/10.0 && posy > 4*size/10.0) {
            ybox = 4;
        }else if(posy <= 6*size/10.0 && posy > 5*size/10.0) {
            ybox = 5;
        }else if(posy <= 7*size/10.0 && posy > 6*size/10.0) {
            ybox = 6;
        }else if(posy <= 8*size/10.0 && posy > 7*size/10.0) {
            ybox = 7;
        }else if(posy <= 9*size/10.0 && posy > 8*size/10.0) {
            ybox = 8;
        }else{
            ybox = 9;
        }
}



void Particle::UpdateDR() {                                                             //Updates dr, the random factor if that factor is to be uniform for each step
    dr = GGen(0, stddev);
}


