/**
Copyright (C) 2011 babin philippe

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

#include "GameEngine.hpp"
GameEngine::GameEngine(sf::RenderWindow &app):m_app(app),m_updateRate(FRAME),m_running(true){
    init();
    loop();
}
/**
    Initialisation du moteur
**/
void GameEngine::init(){
   cout<<"********************"<<endl;
   cout<<"**GameStates::Init**"<<endl;
    m_gameState.push_back(new PlayState(this));
}
/**
    Boucle du Moteur
**/
void GameEngine::loop(){
    sf::Clock anUpdateClock;
    anUpdateClock.Reset();
    float anUpdateNext = anUpdateClock.GetElapsedTime();
   cout<<"********************"<<endl;
   cout<<"*GameEngine::loop start*"<<endl;
    while(m_app.IsOpened()&&m_running){
        sf::Event event;
        while(m_app.PollEvent(event)){
                switch(event.Type){
                  case sf::Event::Closed:       // Window closed
                    m_running=false;
                    break;
                  case sf::Event::GainedFocus:  // Window gained focus
                    m_gameState[0]->resume();
                    break;
                  case sf::Event::LostFocus:    // Window lost focus
                    m_gameState[0]->pause();
                    break;
                  case sf::Event::Resized:      // Window resized
                    break;
                  default:                      // Current active state will handle
                    m_gameState[0]->GetEvents(event);
              }
        }
        m_gameState[0]->loop();
        m_app.Clear();

      // cout<<"********************"<<endl;
       cout<<"***PlayState::draw**"<<endl;
        m_gameState[0]->draw();
        m_app.Display();
    }
   cout<<"********************"<<endl;
   cout<<"*GameEngine::loop stop*"<<endl;
}
GameEngine::~GameEngine(){
   cout<<"********************"<<endl;
   cout<<"*GameEngine::delete*"<<endl;
}

