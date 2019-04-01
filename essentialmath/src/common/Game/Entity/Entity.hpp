//
//  Shape.hpp
//  Game
//
//  Created by Monica Olanescu - (p) on 3/22/19.
//

#ifndef Entity_hpp
#define Entity_hpp

#include<iostream>
#include<vector>
#include<IvShaderProgram.h>
#include <IvRenderer.h>
#include <IvResourceManager.h>
#include "IvRendererHelp.h"
#include <IvVector3.h>
#include <IvStackAllocator.h>
#include <IvVertexFormats.h>
#include <IvVertexBuffer.h>
#include <IvIndexBuffer.h>
#include<IvImage.h>
#include<IvUniform.h>
#include<IvTexture.h>
#include<IvBezier.h>
#include<IvMatrix33.h>
#include<IvMatrix44.h>
#include<IvGame.h>
#include<IvEventHandler.h>

#include"Shape/Shape.hpp"

static float offset=0.01f;

class Entity
{
protected:
    std::vector<IvTCPVertex> vertices;
    std::vector<unsigned int> indices;
    const char* fileName;
    bool shadow;
    IvVector4  transparencyColor_;

    //shader
    IvShaderProgram* mShader;
    
    //uniforms
    IvUniform* mColor;
    IvUniform* texture;
    IvUniform* uvOffset;
    IvUniform* transparencyColor;
    IvUniform* transformMatrix;
    IvUniform* u_resolution;
    IvUniform* u_time;
    
    IvTCPVertex* dataPtr;
    UInt32* indexPtr ;
    IvMatrix44 transform;
    IvVertexBuffer *vertexBuffer;
    IvIndexBuffer *indexBuffer;
   
    std::vector<IvTexture*> mTextures;
    std::vector<const char*> fileNames;
    
    int speed;
    int textureIndex;
    int cloudsCounter;
    float time;
    bool switcher;
    float transition;
    
    Shape shape;
public:
    
    
    IvVector3 m_velocity;
    IvVector3 m_position;
    
    Entity();
    Entity(std::vector<IvTCPVertex> vertices,std::vector<unsigned int>indices);
    Entity(std::vector<IvTCPVertex> vertices,std::vector<unsigned int>indices,const char* fileName);
    Entity(const char * fileName);
    Entity(const char * fileName,bool shadow);
    
    bool getShadow();
    void setShadow(bool shadow_);
    
    IvVector4 getTransparencyColor();
    void setTransparencyColor(IvVector4 vector);

    IvMatrix44 getTransform();
    void setTransform(IvMatrix44 matrix);
    
    void setPosition(IvVector3 position);
    void setVertices(std::vector<IvTCPVertex> vertices);
    void setTexCoord(std::vector<IvTCPVertex> vert);
    
    void create();
    bool getBackgroundChanged();
    void setBackgroundChanger(bool changed);
    
    float getTransition();
    void setTransition(float transition);
    
    void setTexture();
    void loadTexture(const char* fileName);
    void addTexture(const char* fileName);
    void setTextureIndex(int textureIndex);
    
    void setup(const char* shaderName);
    
    void setUniforms();
    void setUniforms(IvVector2 resolution);
    void setUniforms(IvVector3 color);
    
  
    
    void fall(float dt,float speed);
    void Update(float dt,float speed);
    void Render();
    
    
};

#endif /* Entity_hpp */
