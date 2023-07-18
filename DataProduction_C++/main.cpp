/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jelanilyles
 *
 * Created on June 5, 2018, 11:18 AM
 */

#include <cstdlib>
#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <vector>
#include "Particle.h"
#include "GridBox.h"
#include "GridRow.h"
#include "math.h"
#define PI 3.1415926535
using namespace std;

/*
 *  
 */


vector<double> Distribution()
{
    double x, y, h, a, b, beta, max;
    
    vector<double> values;
    
    x = 0;
    a = 2.0;
    beta = 3.0 / 35.0;
    b = 27.0 * beta / 7.0;
    max = 100.0;
    h = max / 5000.0;
    
    while(x <= max) {
        
        y = - (x*x * exp(-b*x) / b) - (2.0 * x * exp(-b*x) / (b*b)) - (2.0 * exp(-b*x) / (b*b*b)) + (2.0 / (b*b*b));
        
        values.push_back(y);
        x += h;
    }
    
    for(int i = 0; i < 5001; i++) {
        
        
        values[i] /= values[5000];
        
    }
    
    
    
    return values;
    
}

double VGen(vector<double> values) {
    
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

double EGen(double mean, double lambda)
{
    double x, y, result;
    double side = 1;
    
    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    
    if(y < 0.5) {
        side = -1;
    }
    
    
    result = mean + side*(log(1.0-x)/(-lambda));
    
    return result;
    
}

double GGen(double mean, double stddv)                                    // Random number generator
{ //Box muller method
        double u1, u2, x, result;
       
        
        u1 = (double)rand() / RAND_MAX;
        u2 = (double)rand() / RAND_MAX;
 
        x = sqrt(-2.0 * log(u1)) * cos((double)(2.0 * PI) * u2);
       
        result = x * stddv + mean;
        
        return result;
}

void trim(string &s) {                                                          // TRIMS EXCESS STRING SPACE
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);
  
    p = s.find_last_not_of(" \t");
    
    if (string::npos != p)
       s.erase(p+1);
 }


void UpdateGridBoxesAndClose(vector<Particle> &parts, vector<GridRow> &rows, int size, int space) {     //Tracks which particles are close to the subject particle based on the grid
    
    Particle * p;
    
    for(int i = 0; i < 10; i++) {                                   //EMPTIES GRIDBOXES
        for(int j = 0; j < 10; j++) {
            
               rows[i].blocks[j].parts.clear();
        
        }
    }    
    
    for(int i = 0; i < parts.size(); i++) {
        p = &parts[i];
        p->close.clear();
    }
                
        
    for(int q = 0; q < parts.size(); q++) {                                     // FILLS GRIDBOXES
        
        
        p = &parts[q];
        p->UpdateGridBox(size);            
        rows[p->ybox].blocks[p->xbox].parts.push_back(*p);
    }                                                                           //
    
    
    
    
    
    
    bool one = false, two = false, three = false, four = false;  //SORTS PARTICLES INTO EACH OTHERS CLOSE-VECTORS
    
    
    
    for(int q = 0; q < parts.size(); q++) {
        
        p = &parts[q];
        
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
               
                    
        
                    if(abs(i - p->xbox) <= space) {
                        one = true;
                    }
                    else if(abs(i - p->xbox) >= 10 - space) {
                        one = true;
                    }
                    else{ one = false; };
                
                    if(abs(j - p->ybox) <= space) {                                                                  //
                        two = true;
                    }
                    else if(abs(j - p->ybox) >= 10 - space) {
                        two = true;
                    }
                    else{ two = false; }
                
                            
               
        
        
                    if(one && two) {                                                                           
                                
                                for(int l = 0; l < rows[j].blocks[i].parts.size(); l++) {
                                    
                                    Particle * v = &rows[j].blocks[i].parts[l];                  
                                    
                               
                                        p->close.push_back(*v);                                 
                                }
                            }
                        
                                                                                                                   //
            }    
        }
    }   
}


    
    
    


int main(int argc, char** argv) {
    
    int numcells, numsteps, space;                                                   //VARIABLE INITIALIZATION
    double  velocity, mean,  std, t1mean, t1std, t2mean, t2std, t3mean, t3std, t4mean, t4std, t5mean, t5std, k1, k2, k3, alimit, rlimit, tlimit, size;
    vector<Particle> particles;
    vector<GridRow> rows;
    vector<double> ores, values;
    fstream file1, file2, file3, file4, file5;
    
    
    bool a1, b2, c3, d4, e5, g7, h8, f1, f2, f3, f4, f5, f6;                  // BOOLEAN VARIABLES FOR TYPE OF SIMULATION
    
    
    
    string filename1 = "Paths.txt", filename2 = "Mean-Squared.txt", filename3 = "Close-Vectors.txt", filename4 = "VisualData.txt", filename5 = "GammaIntegral.txt";           //FILENAMES
    int choice = 0;
    values = Distribution();
//   
    
    
//    cout << "Input filename" << endl;
//    cin >> filename;                                                            //INPUT VARIABLE VALUES
//    
//    cout << "Input mean-squared filename" << endl;
//    cin >> filename1;
//    
//    cout << "Input close particles filename" << endl;
//    cin >> filename2;
//    
//    cout << "Input number of particles" << endl;
//    cin >> numcells;
//    
//    cout << "Input number of time steps" << endl;
//    cin >> numsteps;
//    
//    cout << "Input velocity" << endl;
//    cin >> velocity;
//    
//    cout << "Input mean/flow" << endl;
//    cin >> mean;
//    
//    cout << "Input Standard Deviation" << endl;
//    cin >> std;
//    
//    cout << "Input k-value for attraction" << endl;
//    cin >> k1;
//
//    cout << "Input k-value for repulsion" << endl;
//    cin >> k2;
//
//    cout << "Input k-value for anglular alignment" << endl;
//    cin >> k3;
//    
//    cout << "Input limiting distance for attraction" << endl;
//    cin >> alimit;
//
//    cout << "Input limiting distance for repulsion" << endl;
//    cin >> rlimit;
//    
//    cout << "Input limiting distance for angular alignment" << endl;
//    cin >> tlimit;
//    
//    cout << "Input pane width" << endl;
//    cin >> pw;
//   
//    cout << "Input pane height" << endl;
//    cin >> ph;
    
    
    //TEST VARIABLES//   
    a1 = false; //attraction
    b2 = false; //repulsion
    c3 = false;  //alignment
    d4 = true; //random angle delta
    e5 = false; //Gaussian(false) vs Exponential(true)
    g7 = false; //Velocity distribution if true
    h8 = false; //Initial Alignment
    
    
    f1 = false; //pathways
    f2 = false; //mean-squared
    f3 = false; //close-vectors
    f4 = true;  //data 
    f5 = false; //method testing
    f6 = false; //variable printing
    
    numcells = 500;
    numsteps = 500;
    velocity = 1.0;
    size = 1000.0;
    
    
    ///TEST CONSTANTS
    k1 = 0.5; // attraction k-value
    k2 = 2.0;  // repulsion k-value
    alimit = 50.0; //attraction r0
    rlimit = 25.0;  //repulsion r0
    
    ///VARIABLES
    k3 = 0.3;  // alignment k-value
    tlimit = 50.0;  //alignment r0
    
   // armean = 0.0;   // random attraction/repulsion variable mean
   // arstd = 0.1;    //random attraction/repulsion variable standard deviation
    
    t1mean = 0.0;  // random alignment variable mean
    t1std = 1.0;  // random alignment variable standard deviation
    ores.push_back(t1mean);
    ores.push_back(t1std);
    
//    t2mean = -0.1;
//    t2std = 0.1;
//    ores.push_back(t2mean);
//    ores.push_back(t2std);
//    
//    t3mean = 0.2;
//    t3std = 0.1;
//    ores.push_back(t3mean);
//    ores.push_back(t3std);
//    
//    t4mean = -0.2;
//    t4std = 0.1;
//    ores.push_back(t4mean);
//    ores.push_back(t4std);
//    
//    t5mean = 0;
//    t5std = 0.05;
//    ores.push_back(t5mean);
//    ores.push_back(t5std);
//    
    
    
    
    //TEST VARIABLES//
    
    
    if(f1) {
        file1.open(filename1, ios::out);                                                    //FILE CREATION
        file1 << filename1 << endl;
    }
    
    if(f2) {
        file2.open(filename2, ios::out);
        file2 << filename2 << endl;
    }
    
    if(f3) {
        file3.open(filename3, ios::out);
        file3 << filename3 << endl;
    }
    
    if(f4) {
        file4.open(filename4, ios::out);
    }
    
    if(f5) {
        file5.open(filename5, ios::out);
    }
    
    double limit;
    
    if(alimit >= rlimit && alimit >= tlimit) { limit = alimit; }
    
    if(rlimit >= alimit && rlimit >= tlimit) { limit = rlimit; }
    
    if(tlimit >= alimit && tlimit >= rlimit) { limit = tlimit; }
    
    double s = limit / size;
    
    
    
    if(s <= 0.1) { space = 1; }
    
    else if(s <= 0.2) { space = 2; }
    
    else if(s <= 0.3) { space = 3; }
    
    else if(s <= 0.4) { space = 4; }

    else { space = 5; } 
            
    
    
    
    
   
        for(int j = 0; j < 10; j++) {            
                rows.push_back(GridRow(j));            
            for(int k = 0; k < 10; k++) {   
                    rows[j].blocks.push_back(GridBox(k, j));                
            }
        }
    
    
    
//    
    for(int i = 1; i <= numcells; i++) {
        
        int ore = i%(ores.size() / 2) + 1;
        
        
        Particle q = Particle(velocity, i, size, ore, h8);                                                                                        // FILLS PARTICLE ARRAY
        particles.push_back(q);
    }

    
//    Particle q;
//    q = Particle(110, 110, 1, 1, PI/2);
//    particles.push_back(q);
//    q = Particle(120, 110, 2, 1, PI);
//    particles.push_back(q);
//    q = Particle(710, 710, 3, 1, 3*PI/2);
//    particles.push_back(q);
//    q = Particle(720, 710, 4, 1, PI);
//    particles.push_back(q);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //METHOD TESTING
    
    if(f5) {
        
        
        f1 = false;
        f2 = false;
        f3 = false;
        f4 = false;
        f6 = false;
        
        
        
        for(int i = 0; i < values.size(); i++) {
            
            double j = i / 454.563;
            file5 << to_string(j) + " " + to_string(values[i]) << endl;
            
        }
  
    }
    
    //METHOD TESTING END
    
    string output1, data;
    
    if(f1) {
        file1 << to_string(particles.size()) + " " + to_string(numsteps) + " " + to_string(k1) + " " + to_string(k2) + " " + to_string(k3) << endl;              // PRINT PARAMETERS TO FILES
    }
    
    if(f2) {
        file2 << to_string(particles.size()) + " " + to_string(numsteps) + " " + to_string(k1) + " " + to_string(k2) + " " + to_string(k3) << endl;
    }
    
    if(f3) {
        file3 << to_string(particles.size()) + " " + to_string(numsteps) + " " + to_string(k1) + " " + to_string(k2) + " " + to_string(k3) << endl;
    }
    
    if(f4) {
        file4 << to_string(numsteps) + " " + to_string(particles.size()) + " " + to_string(size) + " " + to_string(k3) + " " + to_string(t1std) + " " + to_string(velocity) << endl;
    }
    
    
    
    
    if(f1 || f2 || f3 || f4 || f6) {
        
    
        for(int j = 0; j < numsteps; j++) {
        
            double sd = 0;
        
       
            UpdateGridBoxesAndClose(particles, rows, size, space);
        
            if(f1) {
                file1 << "STEP#" + to_string(j+1) << endl;
            }
        
            for(int i = 0; i < particles.size(); i++) {
                Particle * c;
                c = &particles[i];
                string output3 = " ";
            
                for(int h = 0; h < c->close.size(); h++) {
                    Particle * r;
                    r = &c->close[h];
                    output3 += std::to_string(r->num) + " ";    
               
                }
            
                trim(output3);
            
                if(f3) {
                    file3 << output3 << endl;
                }
            }
        
            for(int i = 0; i < particles.size(); i++) {
            
                Particle * p;
            
                p = &particles[i];
            
                string output1;
            
                output1 = "num - " + std::to_string(p->num) + " ";           
                output1 += "posx - " + to_string(p->posx) + " posy - " + to_string(p->posy) + " ";
                output1 += "xbox - " + to_string(p->xbox) + " ybox - " + to_string(p->ybox) + " ";         
                output1 += "theta - " + to_string(p->theta) + " ore - " + to_string(p->orientation);
            
            
                if(f4) {
                    file4 << to_string(p->posx) + " " + to_string(p->posy) + " " + to_string(p->theta) + " " + to_string(p->dx) + " " + to_string(p->dy) << endl;
                }
              
                if(f1) {
                    file1 << output1 << endl;
                }
            
                sd += (p->dx)*(p->dx) + (p->dy)*(p->dy); 
          
//                cout << to_string(p->xf) + " " + to_string(p->yf) + " " + to_string(p->xg) + " " + to_string(p->yg) << endl;
            
            
                
                //VARIABLE PRINTING
                if(f6) {
                    cout << to_string(p->velocity) << endl;
                }
                //VARIABLE PRINTING
                
                
                
                p->Update(a1, b2, c3, d4, e5, g7, k1, k2, k3, alimit, rlimit, tlimit, size, space, ores, values);
                
                
             
            } 
            
            if(f6) {
                    cout << "-------------------------" << endl;
                }
        
        
        
            if(f3) {
                file3 << "-----------------" << endl;
            }
            string output2;
            output2 = std::to_string(sd / particles.size());
//            cout << to_string(sd / particles.size()) << endl;
        
            if(f2) {
                file2 << output2 << endl;
            }
        }
    }    
    
    
    
    
    
    
        if(f1){ file1.close(); }
        if(f2){ file2.close(); }
        if(f3){ file3.close(); }
        if(f4){ file4.close(); }
        if(f5){ file5.close(); }
    
    
    cout << "Files were successfully written." << endl;   
    
    
}

