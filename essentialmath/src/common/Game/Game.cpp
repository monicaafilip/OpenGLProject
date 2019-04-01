//
//  Game.cpp
//  Game
//
//  Created by Monica Olanescu - (p) on 3/22/19.
//

#include "Game.hpp"


#include <IvRendererHelp.h>

bool
IvGame::Create()
{
    IvGame::mGame = new Game();
    return ( IvGame::mGame != 0 );
}
Game::Game() : IvGame()
{

}
Game::~Game()
{
    
}
bool
Game::PostRendererInitialize()
{
    initialize();
    IvRendererOGL::mRenderer->SetBlendFunc(kSrcAlphaBlendFunc, kOneMinusSrcAlphaBlendFunc, kAddBlendOp);
    IvRendererOGL::mRenderer->SetDepthWrite(false);
    IvRendererOGL::mRenderer->SetDepthTest(kDisableDepthTest);
    const char* basicShader="backgrShader";

    emptyB->setup("genCloudsShader");
    
    background->setup("sunShader");
    //background->setup(basicShader);
    
//    shape->setup("shapeShader");
//    //shape->setup(basicShader);
   
    backgroundChanger->setup("backgroundChanger");
   //backgroundChanger->setup(basicShader);
    
    for(int i=0;i<clouds.size();i++)
        clouds[i]->setup(basicShader);
    
    mPlayer->setup(basicShader);
    mPlayerShadow->setup("shadowShader");

    for(int i=0;i<objects.size();i++)
    {
        if(objects[i]->getShadow())
            objects[i]->setup("shadowShader");
        else
            objects[i]->setup(basicShader);
    }
    
    if ( !IvGame::PostRendererInitialize() )
        return false;
    ::IvSetDefaultLighting();
    return true;
}

void
Game::UpdateObjects( float dt )
{
    float speed=0.3f;

    if(background->getBackgroundChanged())
    {
        backgroundChanger->setBackgroundChanger(true);
        backgroundChanger->Update(dt,speed);
        if(backgroundChanger->getTransition()==0)
            backgroundChanger->setTransition(background->getTransition());
        if(!backgroundChanger->getBackgroundChanged() )
            background->setBackgroundChanger(false);
    }
    else
   {
       emptyB->Update(dt,speed);
       background->Update(dt,speed);
       mPlayer->Update(dt);
       mPlayerShadow->Update(dt);

       for(int i=0;i<clouds.size();i++)
       {
           clouds[i]->Update(dt,speed);
           speed+=0.1f;
       }

       speed=0.05f;
       for(int i=0;i<objects.size();i++)
       {
           if(i!=0 && i%6==0)
               speed+=0.004f;
           objects[i]->fall(dt,speed);
       }
   }
}

void Game::Render()
{
    IvSetDefaultViewer(0.0f,-10.0f,0.0f);

    if(background->getBackgroundChanged())
    {
        backgroundChanger->setUniforms(IvVector2{255.0f,255.0f});
        backgroundChanger->Render();
    }
    else
    {
//        IvMatrix44 trans;
//        shape->setUniforms(IvVector3{1.,0.,0.},trans);
//        shape->Render();
        
        background->setUniforms();
        background->Render();

        mPlayer->setUniforms();
        mPlayer->Render();

        mPlayerShadow->setUniforms();
        mPlayerShadow->Render();

        emptyB->setUniforms(IvVector2{255.0f,255.0f});
        emptyB->Render();


        for(int i=0;i<clouds.size();i++)
        {
            clouds[i]->setUniforms();
            clouds[i]->Render();
        }

        for(int i=0;i<objects.size();i++)
        {
            objects[i]->setUniforms();
            objects[i]->Render();
        }
    }
}
void Game::initialize()
{
    std::vector<IvTCPVertex> vert;
    IvMatrix44 transform;
    vert.resize(4);
    vert[0].texturecoord={0.0f,1.0f};
    vert[1].texturecoord={1.0f,1.0f};
    vert[2].texturecoord={0.0f,0.0f};
    vert[3].texturecoord={1.0f,0.0f};

    
    //generated clouds
    emptyB=new Entity("bEmpty.tga");
    emptyB->setPosition(IvVector3{0.0f,0.0001f,0.27f});
    emptyB->setTexCoord(vert);
    IvMatrix44 position;
    position.Scaling(IvVector3{8.3,0.0,5.7});
    transform=position*transform;
    emptyB->setTransform(transform);
    
    
    //backgrounds
    background=new Entity("b1.tga");
    background->setPosition(IvVector3{0.0f,0.001f,0.0f});
    background->setTexCoord(vert);
    transform.Scaling(IvVector3{8.3,8.3,8.3});
    background->setTransform(transform);
    
//    shape=new Shape();
//    shape->setPosition(IvVector3{0.,0.5,0.});
//    shape->setVertices(vert);
    
    backgroundChanger=new Entity("b1.tga");
    backgroundChanger->setPosition(IvVector3{0.0f,0.001f,0.0f});
    backgroundChanger->setTexCoord(vert);
    transform.Scaling(IvVector3{8.3,8.3,8.3});
    backgroundChanger->setTransform(transform);
    
    
    vert[0].texturecoord={0.0f,1.0f};
    vert[1].texturecoord={1.0f,1.0f};
    vert[2].texturecoord={0.0f,0.0f};
    vert[3].texturecoord={1.0f,0.0f};
    
    //adding clouds
    Entity* cloud=new Entity("*-0.tga");
    cloud->setPosition(IvVector3{3.0f,-0.1f,3.5f});
    cloud->setTexCoord(vert);
    clouds.push_back(cloud);
    
    cloud=new Entity("*-1.tga");
    cloud->setPosition(IvVector3{0.0f,-0.1f,2.5f});
    cloud->setTexCoord(vert);
    clouds.push_back(cloud);
    
    cloud=new Entity("*-2.tga");
    cloud->setPosition(IvVector3{2.0f,-0.1f,3.0f});
    cloud->setTexCoord(vert);
    clouds.push_back(cloud);
    
    cloud=new Entity("*-3.tga");
    cloud->setPosition(IvVector3{-1.0f,-0.1f,3.2f});
    cloud->setTexCoord(vert);
    clouds.push_back(cloud);
    
    //setting player
    mPlayer=new Player();
    mPlayer->setPosition(IvVector3{0.0f,-1.8f,-2.0f});
    
    vert[0].texturecoord={1.0f,0.0f};
    vert[1].texturecoord={0.0f,0.0f};
    vert[2].texturecoord={1.0f,1.0f};
    vert[3].texturecoord={0.0f,1.0f};
    
    mPlayer->setTexCoord(vert);
    
    mPlayerShadow=new Player(true);
    mPlayerShadow->setPosition(IvVector3{0.0f,-1.9f,-2.88f});
    mPlayerShadow->setTransparencyColor(IvVector4{0.0f,0.0f,0.0f,0.7f});
    
    vert[0].texturecoord={0.0f,1.0f};
    vert[1].texturecoord={1.0f,1.0f};
    vert[2].texturecoord={0.0f,0.0f};
    vert[3].texturecoord={1.0f,0.0f};

    mPlayerShadow->setTexCoord(vert);
    
    //setting entities
    Entity* ent;
    std::srand(time(nullptr));
    float x=0.0f,y=0.02f,z=4.5f;
    for(int i=0;i<7;i++)
    {
        do
        {
            float sign;
            sign=rand()%2;
            if(sign==1)
                sign*=-1.0f;
            else
                sign=1.0f;
            x+=sign;
            
        }while(x>4. || x< -4.);
      
        ent=new Entity("cherry.tga");
        ent->setPosition(IvVector3{x,y,z});
        ent->setTexCoord(vert);
        objects.push_back(ent);
    
        float keepZ=4.5f;
        float alpha_=0.6f;
        for(int i=0;i<5;i++)
        {
            ent=new Entity("cherry.tga",true);
            ent->setPosition(IvVector3{x,y,keepZ});
            ent->setTexCoord(vert);
            ent->setTransparencyColor(IvVector4{1.0f,1.0f,1.0f,alpha_});
            objects.push_back(ent);
            keepZ+=0.05f;
            alpha_-=0.1f;
        }
    
    }

}
