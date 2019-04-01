//
//  Fireworks.cpp
//  Game
//
//  Created by Monica Olanescu - (p) on 3/28/19.
//

#include "Fireworks.hpp"

Fireworks::Fireworks()
{
    
}
Fireworks::Fireworks(const char* fileName):Entity(fileName)
{
    
}
Fireworks::Fireworks(IvVector3 center,float radium):center(center),radium(radium)
{

}

Fireworks::~Fireworks()
{
    
}

void Fireworks::setPosition(int cadre)
{
    std::vector<IvTCPVertex> vert;
    vert.resize(3);
    
    if(cadre==1)
    {
        vert[0].position=center;
        vert[1].position=IvVector3{center.x+radium,center.y,center.z};
        vert[2].position=IvVector3{center.x,center.y,radium+center.z};
    }
    else if(cadre==2)
    {
        vert[0].position=center;
        vert[1].position=IvVector3{-center.x+radium,center.y,center.z};
        vert[2].position=IvVector3{center.x,center.y,radium+center.z};
    }
    else if(cadre==3)
    {
        vert[0].position=center;
        vert[1].position=IvVector3{-center.x+radium,center.y,center.z};
        vert[2].position=IvVector3{center.x,center.y,radium-center.z};
    }
    else if(cadre==4)
    {
        vert[0].position=center;
        vert[1].position=IvVector3{center.x+radium,center.y,center.z};
        vert[2].position=IvVector3{center.x,center.y,radium-center.z};
    }
    
    vertices=vert;
    for(int i=0;i<3;i++)
        indices.push_back(i);
}
void Fireworks::setUniforms()
{
    /*
     uniform vec3 iResolution;
     uniform float iGlobalTime;
     */
    
    resolution=mShader->GetUniform("iResolution");
    resolution->SetValue(IvVector3{250.0f,225.0f,100.0f},0);

    globalTime=mShader->GetUniform("iGlobalTime");
    globalTime->SetValue(70.0f,0);
   
    //texture=mShader->GetUniform("s2");
    
}
void Fireworks::create()
{

}
void Fireworks::Render()
{
    IvRenderer::mRenderer->Draw(kTriangleListPrim, vertexBuffer, indexBuffer);

}
