//
//  Player.hpp
//  Game
//
//  Created by Monica Olanescu - (p) on 3/22/19.
//

#ifndef Player_hpp
#define Player_hpp

#include<IvEventHandler.h>
#include<IvGame.h>

#include<iostream>
#include<fstream>

#include"../Entity/Entity.hpp"



class Player:public Entity
{
public:
    Player();
    Player(const char* fileName);
    Player(bool shadow);
    ~Player();
    
    int textureIndex;
    
    void Update( float dt );
    void Render();
    
    void setVertices(std::vector<IvTCPVertex> vertices);
    void setTransparencyColor(IvVector4 vector);
    void setTransform(IvMatrix44 matrix);
private:
    int keep;
    std::vector<IvTCPVertex> vertices;
    std::vector<unsigned int> indices;
  
    //std::vector<IvTexture> textures;
    
};


#endif /* Player_hpp */
