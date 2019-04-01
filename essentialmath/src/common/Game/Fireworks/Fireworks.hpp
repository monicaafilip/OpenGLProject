//
//  Fireworks.hpp
//  Game
//
//  Created by Monica Olanescu - (p) on 3/28/19.
//

#ifndef Fireworks_hpp
#define Fireworks_hpp

#include"Entity/Entity.hpp"
#include<IvUniform.h>

#include <stdio.h>
#include<iostream>
#include<vector>

//struct Particle
//{
//    float Type;
//    std::vector<float> positions;
//    std::vector<float> velocity;
//    float lifeTimeM;
//};

class Fireworks:public Entity
{
    std::vector<IvTCPVertex*> dataPtr;
    
    IvVector3 center;
    float radium;
    
    IvUniform* velocity;
    IvUniform* lifeTime;
    IvUniform* resolution;
    IvUniform* globalTime;
    IvUniform* texture;
public:
    Fireworks();
    Fireworks(const char* fileName);
    Fireworks(IvVector3 center,float radium);
    ~Fireworks();
    
    void setPosition(int cadre);
    void setUniforms();
    void Render();
    void create();
};

#endif /* Fireworks_hpp */
