//
//  Shape.cpp
//  Game
//
//  Created by Monica Olanescu - (p) on 3/22/19.
//

#include "Entity.hpp"


Entity::Entity()
{
    m_position = IvVector3(0.0f, 0.0f, 0.0f);
    m_velocity = IvVector3(0.0f, 0.0f, -9.8f);
    
    transform.Identity();
}
Entity::Entity(std::vector<IvTCPVertex> vertices,std::vector<unsigned int> indices,const char* fileName):vertices(vertices),indices(indices),fileName(fileName)
{
}
Entity::Entity(const char * fileName):fileName(fileName)
{
    transition=0;
    switcher=false;
    time=0.005f;
    cloudsCounter=0;
    shadow=false;
    textureIndex=0;
    m_position = IvVector3(0.0f, 0.0f, 0.0f);
    m_velocity = IvVector3(0.0f, 0.0f, -9.8f);

    transform.Identity();
}
Entity::Entity(const char * fileName,bool shadow):fileName(fileName),shadow(shadow)
{
    transition=0;
    time=0.005f;
    cloudsCounter=0;
    textureIndex=0;
    m_position = IvVector3(0.0f, 0.0f, 0.0f);
    m_velocity = IvVector3(0.0f, 0.0f, -9.8f);
    transform.Identity();
}

bool Entity::getShadow()
{
    return shadow;
}
void Entity::setShadow(bool shadow_)
{
    shadow=shadow_;
}
IvVector4 Entity::getTransparencyColor()
{
    return transparencyColor_;
}

void Entity::setTransparencyColor(IvVector4 vector)
{
    transparencyColor_=vector;
}
IvMatrix44 Entity::getTransform()
{
    return transform;
}

void Entity::setTransform(IvMatrix44 matrix)
{
    transform=matrix;
}
void Entity::create()
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
        indexPtr[i] = indices[i];
    
}

void Entity::setTexture()
{
    IvImage* image = IvImage::CreateFromFile(fileName);
    
    if (image)
    {
        mTextures.push_back(IvRenderer::mRenderer->GetResourceManager()->CreateTexture((image->GetBytesPerPixel() == 4) ? kRGBA32TexFmt : kRGB24TexFmt,image->GetWidth(), image->GetHeight(), image->GetPixels(), kImmutableUsage));
        delete image;
        image = 0;
    }
}
void Entity::loadTexture(const char* file)
{
    IvImage* image = IvImage::CreateFromFile(file);
    
    if (image)
    {
        mTextures.push_back( IvRenderer::mRenderer->GetResourceManager()->CreateTexture((image->GetBytesPerPixel() == 4) ? kRGBA32TexFmt : kRGB24TexFmt,image->GetWidth(), image->GetHeight(), image->GetPixels(), kImmutableUsage));
        delete image;
        image = 0;
    }
}

void Entity::setTextureIndex(int textureIndex)
{
    this->textureIndex=textureIndex;
}
void Entity::addTexture(const char *fileName)
{
    fileNames.push_back(fileName);
}

void Entity::setUniforms()
{
    if(shadow)
    {
        transparencyColor=mShader->GetUniform("transparencyColor");
        transparencyColor->SetValue(transparencyColor_,0);
    }
    
    texture=mShader->GetUniform("Texture");
    
    if(texture)
        texture->SetValue(mTextures[textureIndex]);

    
    transformMatrix = mShader->GetUniform("transform");
    transformMatrix->SetValue(transform,0);
    
    IvRenderer::mRenderer->SetShaderProgram(mShader);
}

void Entity::setUniforms(IvVector2 resolution)
{    
    transformMatrix=mShader->GetUniform("transform");
    transformMatrix->SetValue(transform,0);
    
    u_resolution=mShader->GetUniform("u_resolution");
    u_resolution->SetValue(IvVector3{resolution.x,resolution.y,1.0f},0);
    
    u_time=mShader->GetUniform("u_time");
    u_time->SetValue(this->time,0);
    
    IvRenderer::mRenderer->SetShaderProgram(mShader);
}
void Entity::setUniforms(IvVector3 color)
{
    mColor=mShader->GetUniform("constColor");
    mColor->SetValue(color,0);
    
    transformMatrix=mShader->GetUniform("transform");
    transformMatrix->SetValue(transform, 0);
}

void Entity::setup(const char* shaderName)
{
    this->create();
    
    if(fileNames.size()!=0)
        loadTexture(fileNames[textureIndex]);
    else
        if(fileName)
            setTexture();
    mShader=IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram( IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile(shaderName),
        IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile(shaderName));

    vertexBuffer = IvRenderer::mRenderer->GetResourceManager()->CreateVertexBuffer(kTCPFormat, 4, dataPtr,kImmutableUsage);
    indexBuffer = IvRenderer::mRenderer->GetResourceManager()->CreateIndexBuffer(4, indexPtr,kImmutableUsage);

}

void Entity::fall(float dt,float speed)
{
    m_position += m_velocity * dt * speed;
    transform=transform.Translation(m_position);
    
    if(transform(2,3)< -6.)
    {
        IvMatrix44 positionTranslation;
        positionTranslation.Translation( IvVector3{0.0f,0.0f,6.5f} );
        IvMatrix44 identity;
        transform =  positionTranslation*transform*identity;
        m_position=IvVector3{0.0f,0.0f,0.0f};
    }
}
void Entity::Update(float dt,float speed)
{
    time+=0.004f;
    if ( fileName[0]=='b' && IvGame::mGame->mEventHandler->IsKeyPressed('b'))
    {
        if(strcmp(fileName,"b1.tga")==0)
        {   fileName="b2.tga";
            if(fileNames.size()==0)
                loadTexture("b2.tga");
            if(textureIndex==0)
            {
                textureIndex=1;
                switcher=true;
                transition=150;
            }
        }
        else
            if(strcmp(fileName,"b2.tga")==0)
            {   fileName="b1.tga";
                if(fileNames.size()==1)
                    loadTexture("b2.tga");
                if(textureIndex==1)
                {
                    textureIndex=0;
                    switcher=true;
                    transition=150;
                }
            }
        
    }
    if(fileName[0]!='b')
    {
        float x=0.0f,y=0.0f,z=0.0f;
        speed+=0.02;
    
        cloudsCounter++;
        if(cloudsCounter%5==0)
        {
            cloudsCounter=0;
            x-=speed*dt;
        }
    
        IvMatrix44 positionTranslation;
        IvMatrix44 identity;
    
        positionTranslation.Translation( IvVector3(x, y, z) );
        transform =  positionTranslation*transform*identity;
   
        if(transform(0,3)<-4.5f)
        {
            positionTranslation.Translation( IvVector3(10.0f, y, z) );
            transform =  positionTranslation*transform*identity;
        }
    }
   else
   {
       if(transition>0)
           transition--;
       if(transition==0)
           switcher=false;
   }
}

void Entity::Render()
{
    IvRenderer::mRenderer->Draw(kTriangleStripPrim, vertexBuffer, indexBuffer);
}

void Entity::setPosition(IvVector3 position)
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
    
    vert[0].position={0.5f*signX+position.x,0.0f*signY+position.y,0.5f*signZ+position.z};
    vert[1].position={-0.5f*signX+position.x,0.0f*signY+position.y,0.5f*signZ+position.z};
    vert[2].position={0.5f*signX+position.x,0.0f*signY+position.y,-0.5f*signZ+position.z};
    vert[3].position={-0.5f*signX+position.x,0.0f*signY+position.y,-0.5f*signZ+position.z};
    
    for(int i=0;i<vertices.size();i++)
        vertices[i].position=vert[i].position;
    
    for(int i=0;i<vertices.size();i++)
        indices.push_back(i);
}
void Entity::setVertices(std::vector<IvTCPVertex> vertices)
{
    vertices.resize(4);
    this->vertices=vertices;
    for(int i=0;i<vertices.size();i++)
        indices.push_back(i);
}
void Entity::setTexCoord(std::vector<IvTCPVertex> vert)
{
    vertices.resize(4);
    for(int i=0;i<vertices.size();i++)
        vertices[i].texturecoord=vert[i].texturecoord;
}

bool Entity::getBackgroundChanged()
{
    return switcher;
}

void Entity::setBackgroundChanger(bool changed)
{
    this->switcher=changed;
}

float Entity::getTransition()
{
    return transition;
}
void Entity::setTransition(float transition)
{
    this->transition=transition;
}
