//
//  Game.hpp
//  Game
//
//  Created by Monica Olanescu - (p) on 3/22/19.
//

#ifndef Game_hpp
#define Game_hpp


#include <IvGame.h>
#include<IvRendererOGL.h>
#include"../Player/Player.hpp"
#include"../Fireworks/Fireworks.hpp"
#include<stdlib.h>
#include<time.h>

class Game:public IvGame
{
public:
    Game();
    ~Game();
    bool PostRendererInitialize();

    Player* mPlayer;
    Player* mPlayerShadow;

    Entity* emptyB;
    Entity* background;
    Entity* backgroundChanger;
    
    Shape* shape;
    
    std::vector<Entity*> clouds;
    std::vector<Entity*> objects;
    
protected:
    virtual void UpdateObjects( float dt );
    virtual void Render();
    
private:
    Game( const Game& other );
    Game& operator=( const Game& other );
    void initialize();
};

#endif /* Game_hpp */
