//===============================================================================
// @ Game.cpp
// ------------------------------------------------------------------------------
// Game core routines
//
// Copyright (C) 2008-2015 by James M. Van Verth and Lars M. Bishop.
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
//
//
//===============================================================================

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include <IvClock.h>
#include <IvRenderer.h>
#include <IvEventHandler.h>
#include <IvMatrix33.h>
#include <IvMatrix44.h>
#include <IvRendererHelp.h>
#include <IvVector4.h>

#include "Game.h"
#include "Player.h"

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ IvGame::Create()
//-------------------------------------------------------------------------------
// Creation routine
//-------------------------------------------------------------------------------
bool
IvGame::Create()
{
    IvGame::mGame = new Game();

    return true;
}   // End of IvGame::Create()

//-------------------------------------------------------------------------------
// @ Game::Game()
//-------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------
Game::Game()
{
    // init variables
    mPlayer = 0;            // main player object

}   // End of Game::Game()


//-------------------------------------------------------------------------------
// @ Game::~Game()
//-------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------
Game::~Game()
{
    delete mPlayer;
    mPlayer = 0;
    
}   // End of Game::~Game()


//-------------------------------------------------------------------------------
// @ Game::PostRendererInitialize()
//-------------------------------------------------------------------------------
// Initialize subsystems
//-------------------------------------------------------------------------------
bool
Game::PostRendererInitialize()
{
    if (!IvGame::PostRendererInitialize())
        return false;

    mPlayer = new Player();
    if (!mPlayer)
        return false;

    // plug in a light
    IvSetDefaultLighting();

    return true;
}   // End of Game::PostRendererInitialize()


//-------------------------------------------------------------------------------
// @ Game::Update()
//-------------------------------------------------------------------------------
// Main update loop
//-------------------------------------------------------------------------------
void
Game::UpdateObjects( float dt )
{
    // update player
    mPlayer->Update( mClock->GetElapsedTime() );
    
}   // End of Game::Update()


//-------------------------------------------------------------------------------
// @ Game::Render()
//-------------------------------------------------------------------------------
// Render stuff
//-------------------------------------------------------------------------------
void 
Game::Render()                                  // Here's Where We Do All The Drawing
{
    // Reset The View
    ::IvSetDefaultViewer( -10.0f, 2.0f, 15.0f );

    // draw axes
    ::IvDrawAxes();

    // draw the main object
    mPlayer->Render();
}
