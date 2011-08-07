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

#include "MenuState.hpp"
#include "GameEngine.hpp"

/**
    Construction des éléments du menu
**/
MenuState::MenuState(GameEngine* theGameEngine):m_start(true),m_scaleUp(true){
    m_gameEngine=theGameEngine;
    m_norfair.SetImage(g_imgManag["norfair"].img);
    m_norfair.SetScale(4,4);
    m_norfair.SetOrigin(g_imgManag["norfair"].img.GetWidth()/2,g_imgManag["norfair"].img.GetHeight()/2);
    m_norfair.SetPosition(g_config["screenwidth"]/2,g_config["screenheight"]/4);

    m_press.SetImage(g_imgManag["press"].img);
    m_press.SetOrigin(g_imgManag["press"].img.GetWidth()/2,g_imgManag["press"].img.GetHeight()/2);
    m_press.SetPosition(g_config["screenwidth"]/2,g_config["screenheight"]*0.75);

    m_pause.SetImage(g_imgManag["pause"].img);
    m_pause.SetScale(3,3);
    m_pause.SetPosition(g_config["screenwidth"]/2,g_config["screenheight"]/2);
    m_pause.SetOrigin(g_imgManag["pause"].img.GetWidth()/2,g_imgManag["pause"].img.GetHeight()/2);
}
/**
    Initialisation des éléments du menu
    Cette méthode est appelé lors démarrage ou du redémarrage du state
**/
void MenuState::init(){
}
/**
    Exécution des éléments
**/
void MenuState::loop(){
    if(m_start){
        if(m_press.GetScale().x>2)m_scaleUp=false;
        if(m_press.GetScale().x<1.2)m_scaleUp=true;

        if(m_scaleUp)m_press.SetScale(m_press.GetScale().x+0.002*m_gameEngine->m_app.GetFrameTime(),m_press.GetScale().x+0.002*m_gameEngine->m_app.GetFrameTime());
        else m_press.SetScale(m_press.GetScale().x-0.002*m_gameEngine->m_app.GetFrameTime(),m_press.GetScale().x-0.002*m_gameEngine->m_app.GetFrameTime());
    }
    else{
        if(m_pause.GetScale().x>4)m_scaleUp=false;
        if(m_pause.GetScale().x<3)m_scaleUp=true;

        if(m_scaleUp)m_pause.SetScale(m_pause.GetScale().x+0.002*m_gameEngine->m_app.GetFrameTime(),m_pause.GetScale().x+0.002*m_gameEngine->m_app.GetFrameTime());
        else m_pause.SetScale(m_pause.GetScale().x-0.002*m_gameEngine->m_app.GetFrameTime(),m_pause.GetScale().x-0.002*m_gameEngine->m_app.GetFrameTime());
    }
}
/**
    Pause le jeu
    Appelé lors d'un changement de state
**/
void MenuState::pause(){
}
/**
    Démarrage après une pause
**/
void MenuState::resume(){
}
/**
    Remet à zéro
**/
void MenuState::stop(){
}
/**
    Utilisation des entrés
**/
void MenuState::GetEvents(sf::Event Event){
    if (Event.Type == sf::Event::KeyPressed){
        if(m_start)m_start=false;
        m_gameEngine->m_gameState[1]->resume();
        m_gameEngine->changeState(1);
    }
}
/**
    Affichage des éléments
**/
void MenuState::draw(){
    if(!m_start){
        (*m_gameEngine).m_app.Draw(sf::Shape::Rectangle(0,0,g_config["screenwidth"], g_config["screenheight"], sf::Color(255,255,255)));
        (*m_gameEngine).m_app.Draw(m_pause);
    }
    else {
        (*m_gameEngine).m_app.Draw(sf::Shape::Rectangle(0,0,g_config["screenwidth"], g_config["screenheight"], sf::Color(0,0,0)));
        (*m_gameEngine).m_app.Draw(m_norfair);
        (*m_gameEngine).m_app.Draw(m_press);
    }
}

MenuState::~MenuState(){
}
