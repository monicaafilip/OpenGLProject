
//
//  Player.cpp
//  Game
//
//  Created by Monica Olanescu - (p) on 3/22/19.
//

#include "Player/Player.hpp"

Player::Player(const char * fileName):  Entity(fileName)
{
    
}
Player::Player()
{
    textureIndex=0;
    keep=4;
    
    //0
    Entity::addTexture("female_chher1-20.tga");
    Entity::loadTexture("female_chher1-20.tga");
    
    //1
    Entity::addTexture("female_chher1-21.tga");
    Entity::loadTexture("female_chher1-21.tga");
    
    //2
    Entity::addTexture("female_chher1-22.tga");
    Entity::loadTexture("female_chher1-22.tga");
    
    //3
    Entity::addTexture("female_chher1-23.tga");
    Entity::loadTexture("female_chher1-23.tga");
    
    //4
    Entity::addTexture("female_chher1-16.tga");
    Entity::loadTexture("female_chher1-16.tga");
    
//    //5
//    Entity::addTexture("female_chher1-15.tga");
//    Entity::loadTexture("female_chher1-15.tga");
    
}

Player::Player(bool shadow):Player()
{
    Entity::setShadow(shadow);
}

Player::~Player()
{
}

void Player::setVertices(std::vector<IvTCPVertex> vertices)
{
    this->vertices=vertices;
}
void Player::setTransparencyColor(IvVector4 vector)
{
    Entity::setTransparencyColor(vector);
}
void Player::setTransform(IvMatrix44 matrix)
{
    Entity::setTransform(matrix);
}

void Player::Update(float dt)
{
    IvMatrix44 positionTranslation;
    float x = 0.0f, y = 0.0f, z = 0.0f;
    keep++;
    
    //TRANSLATION
    if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
    {
        x -= 2.0f*dt;
        
            keep=keep%2;
            if(keep==0)
            {
                if(textureIndex!=0)
                    textureIndex = 0;
                else
                    textureIndex=4;
            }
            Entity::setTextureIndex(textureIndex);
        
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
    {
        x += 2.0f*dt;
        keep=keep%4;
        if(keep==0)
        {
            if(textureIndex!=3)
                textureIndex = 3;
            else
                if(textureIndex!=2)
                    textureIndex=2;
                else
                    textureIndex=0;
        }
        Entity::setTextureIndex(textureIndex);
        
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
    {
        x -= 4.0f*dt;
        keep=keep%7;
        if(keep==0)
        {   if(keep==0)
        {    if(textureIndex!=0)
            textureIndex = 0;
        else
            textureIndex=4;
        }
        }
        Entity::setTextureIndex(textureIndex);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('f'))
    {
        x += 4.0f*dt;
        keep=keep%7;
        if(keep==0)
        {     if(textureIndex!=3)
            textureIndex = 3;
        else
            if(textureIndex!=2)
                textureIndex=2;
            else
                textureIndex=0;
        }
        Entity::setTextureIndex(textureIndex);
    }

    positionTranslation.Translation( IvVector3(x, y, z) );
    
    IvMatrix44 identity;
    transform =  positionTranslation*transform*identity;
    
}
void Player::Render()
{
    Entity::Render();
}
