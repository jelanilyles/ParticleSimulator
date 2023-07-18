/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particle.h
 * Author: jelanilyles
 *
 * Created on June 5, 2018, 11:19 AM
 */


#ifndef PARTICLE_H
#define PARTICLE_H

#include "GridRow.h"
#include <vector>

using namespace std;

class GridPlane;

class Particle 
{
public:
    Particle();
    Particle( double vel, int num, double size, int ore, bool h8);    //Particle init
    Particle(double x, double y, int num, double vel, double theta, int ore);                                             //Test particle init    
    void Update(bool a1, bool b2, bool c3, bool d4, bool e5, bool g7, double k1, double k2, double k3, double alimit, double rlimit, double tlimit, double size, int space, vector<double> ores, vector<double> values);                                                                      //updates position variables                                                                 //updates velocity variables                                                                    //updates theta
    void UpdateDR();                                                                            // updates dr
    void AlternateAngle(double size, double tlimit, int space);
    void UpdateGridBox(double size);
    double GGen(double mean, double stddv);
    double EGen(double mean, double lambda);
    double LGen(double min, double max, double mean);
    vector<double> RungeKutta();
    double VGen(vector<double> values);
    double FindX(Particle p, double size, int space);
    double FindY(Particle p, double size, int space);
    vector<double> FindForces(Particle p, double alimit, double rlimit, double tlimit, double k1, double k2, double k3, double size, int space);
    vector<double> FindForceSums(double alimit, double rlimit, double tlimit, double k1, double k2, double k3, double size, int space);
    void Adjust(int space, double size, double particlesize);
    double xf, yf, xg, yg;
    int num;                                            //Identifier                               
    double test;
    double particlesize;
    double posx, posy, posx0, posy0, dx, dy;           //position variables, originals position variables, displacement variables
    double px, py, ptheta;
    int dxbox, dybox;                                          //particle to box displacement variables
    double velocity, initialvelocity, velx, vely, vel0;                        //velocity variables   
    double theta, randt;                                       //angle variable
    double dr;                                          //random factor variable
    double stddev;                                      // standard deviation for random number generator
    double sd;                                          // squared displacement variable
    int xbox, ybox;                                     //grid position variable                                           // the constant of the strength of the interacting forces
    int orientation;
    vector<Particle> close;
    vector<Particle> touching;
};

#endif /* PARTICLE_H */

