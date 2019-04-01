//
//  Shape.cpp
//  Game
//
//  Created by Monica Olanescu - (p) on 3/25/19.
//

#include "Shape/Shape.hpp"
Shape::Shape(std::vector<IvTCPVertex> vertices,std::vector<unsigned int> indices):vertices(vertices),indices(indices)
{
    
}
void Shape::create()
{
    unsigned int numVerts = (unsigned int)vertices.size();
     dataPtr = (IvTCPVertex*)IvStackAllocator::mScratchAllocator->Allocate(kIvVFSize[kTCPFormat] * numVerts);
    
    for ( unsigned int i = 0; i < numVerts; ++i )
    {
        dataPtr[i].position = vertices[i].position;
        dataPtr[i].color=vertices[i].color;
        dataPtr[i].texturecoord=vertices[i].texturecoord;
    }
    
    unsigned int numIndices =(unsigned int) indices.size();
    indexPtr = (UInt32*)IvStackAllocator::mScratchAllocator->Allocate(sizeof(UInt32)* numIndices);
    for ( unsigned int i = 0; i < numIndices; ++i )
    {
        indexPtr[i] = indices[i];
    }
}
void Shape::setUniforms(IvVector3 color,IvMatrix44 transformMatrix_)
{
    mColor=mShader->GetUniform("constColor");
    mColor->SetValue(color,0);
    
    transformMatrix = mShader->GetUniform("transform");
    transformMatrix->SetValue(transformMatrix_,0);
    
    IvRenderer::mRenderer->SetShaderProgram(mShader);
    
}
void Shape::setVertices(std::vector<IvTCPVertex> vertices)
{
    this->vertices=vertices;
    for(int i=0;i<vertices.size();i++)
        indices.push_back(i);
}
void Shape::setup(const char* shaderName)
{
    create();
    
    mShader=IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram( IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile(shaderName),
    IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile(shaderName));

    
    vertexBuffer = IvRenderer::mRenderer->GetResourceManager()->CreateVertexBuffer(kTCPFormat, 4, dataPtr,kImmutableUsage);
    
    indexBuffer = IvRenderer::mRenderer->GetResourceManager()->CreateIndexBuffer(4, indexPtr,kImmutableUsage);
    
    
}
void Shape::drawSquare()
{
        IvRenderer::mRenderer->Draw(kTriangleStripPrim, vertexBuffer, indexBuffer);
}

void Shape::drawTriangle()
{
        IvRenderer::mRenderer->Draw(kTriangleListPrim, vertexBuffer, indexBuffer);
}

void Shape::setPosition(IvVector3 position)
{
    std::vector<IvTCPVertex> vert;
    vert.resize(4);
    vertices.resize(4);
    
    float signX=1.0f,signY=1.0f,signZ=1.0f;
    
    if(position.x<0.0f)
        signX=-1.0f;
    if(position.y<0.0f)
        signY=-1.0f;
    if(position.z<0.0f)
        signZ=-1.0f;
    
    vert[0].position={0.5f*signX+position.x,0.0f+position.y,0.5f*signZ+position.z};
    vert[1].position={-0.5f*signX+position.x,0.0f+position.y,0.5f*signZ+position.z};
    vert[2].position={0.5f*signX+position.x,0.0f+position.y,-0.5f*signZ+position.z};
    vert[3].position={-0.5f*signX+position.x,0.0f+position.y,-0.5f*signZ+position.z};
    
    for(int i=0;i<vertices.size();i++)
        vertices[i].position=vert[i].position;
    
    for(int i=0;i<vertices.size();i++)
        indices.push_back(i);
}

void Shape::Update(float dt)
{
    
        IvMatrix44 positionTranslation;
        IvMatrix44 rotationTranslation;
        IvMatrix44 scaleTranslation;
    
        float s = 1.0f;
        float r = 0.0f;
    
        float x = 0.0f, y = 0.0f, z = 0.0f;
        
    
         //scalin
         if (IvGame::mGame->mEventHandler->IsKeyDown(';'))
         s -= 0.25f*dt;
         
         if (IvGame::mGame->mEventHandler->IsKeyDown('p'))
         s += 0.25f*dt;
         
         
         //rotation
         if (IvGame::mGame->mEventHandler->IsKeyDown('o'))
         r -= kPI*0.25f*dt;
         
         if (IvGame::mGame->mEventHandler->IsKeyDown('u'))
         r += kPI*0.25f*dt;
         
    
        //translation
        if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
            x -= 3.0f*dt;
        
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
            x += 3.0f*dt;
        
        if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
            z -= 3.0f*dt;
        
        if (IvGame::mGame->mEventHandler->IsKeyDown('w'))
            z += 3.0f*dt;
        
        
        scaleTranslation.Scaling( IvVector3(s,s,s) );
        rotationTranslation.RotationY( r );
        positionTranslation.Translation( IvVector3(x, y, z) );
        
        IvMatrix44 identity;
        transform =  positionTranslation*transform*identity*scaleTranslation * rotationTranslation ;
    
}

void Shape::Render()
{
    drawTriangle();
//    drawSquare();
//    
//    IvMatrix44 position;
//    position.Scaling(IvVector3{3.,3.,3.});
//    transform=position*transform;
//    
//    drawTriangle();
//    drawSquare();
//    
//    position.Scaling(IvVector3{3.,3.,3.});
//    transform=position*transform;
//    
//    drawTriangle();
//    drawSquare();
}

