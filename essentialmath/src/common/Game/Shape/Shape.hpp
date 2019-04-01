//
//  Shape.hpp
//  Game
//
//  Created by Monica Olanescu - (p) on 3/25/19.
//

#ifndef Shape_hpp
#define Shape_hpp

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


//static IvVertexBuffer* vertexBuffer = 0;
//static IvIndexBuffer* indexBuffer = 0;
static float kPI=3.14;


class Shape
{
    
    std::vector<IvTCPVertex> vertices;
    std::vector<unsigned int> indices;
    IvShaderProgram* mShader;
    IvUniform* mColor;
    IvVertexBuffer* vertexBuffer;
    IvIndexBuffer* indexBuffer;
    IvUniform* transformMatrix;
    IvMatrix44 transform;
    
    IvTCPVertex* dataPtr;
    UInt32* indexPtr;
    
    const char* shaderName;
    
public:
    
    Shape() = default;
    Shape(std::vector<IvTCPVertex> vertices,std::vector<unsigned int>indices);
    
    void Update(float dt);
    void Render();
    
    void create();
    void setUniforms(IvVector3 color,IvMatrix44 transformMatrix);
    void setPosition(IvVector3 position);
    void setup(const char* shaderName);
    void drawSquare();
    void drawTriangle();
    void setVertices(std::vector<IvTCPVertex> vertices);
};

#endif /* Shape_hpp */
