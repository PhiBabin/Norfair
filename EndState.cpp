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

#include "EndState.hpp"
#include "GameEngine.hpp"

/**
    Construction des éléments du menu
**/
EndState::EndState(GameEngine* theGameEngine):m_scaleUp(true),m_start(false)
,m_winner(GameConfig::GameConfig::g_imgManag["winner"].img,GameConfig::GameConfig::g_imgManag["winner"].nbrCollum,GameConfig::GameConfig::g_imgManag["winner"].nbrLine){
    m_gameEngine=theGameEngine;

    m_winner.SetScale(4,4);
    m_winner.SetPosition(GameConfig::g_config["screenwidth"]/2,GameConfig::g_config["screenheight"]/3);
    m_winner.SetOrigin(GameConfig::g_imgManag["winner"].img.GetWidth()/2,GameConfig::g_imgManag["winner"].img.GetHeight()/2);

    m_trophie.SetImage(GameConfig::g_imgManag["trophie"].img);
    m_trophie.SetScale(5,5);
    m_trophie.SetPosition(GameConfig::g_config["screenwidth"]/2,GameConfig::g_config["screenheight"]*0.5);
    m_trophie.SetOrigin(GameConfig::g_imgManag["trophie"].img.GetWidth()/2,GameConfig::g_imgManag["trophie"].img.GetHeight()/2);

    m_retry.SetImage(GameConfig::g_imgManag["retry"].img);
    m_retry.SetScale(3,3);
    m_retry.SetPosition(GameConfig::g_config["screenwidth"]/2,GameConfig::g_config["screenheight"]*0.75);
    m_retry.SetOrigin(GameConfig::g_imgManag["retry"].img.GetWidth()/2,GameConfig::g_imgManag["retry"].img.GetHeight()/2);
}
/**
    Initialisation des éléments du menu
    Cette méthode est appelé lors démarrage ou du redémarrage du state
**/
void EndState::init(){
    m_winner.setAnimRow(1);
    m_continue.Reset();
    m_party.Reset();
}
/**
    Exécution des éléments
**/
void EndState::loop(){
    if(!m_start){
        m_continue.Reset();
        m_party.Reset();
        m_start=true;
    }
    if(m_retry.GetScale().x>2)m_scaleUp=false;
    if(m_retry.GetScale().x<1.2)m_scaleUp=true;

    if(m_scaleUp)m_retry.SetScale(m_retry.GetScale().x+0.002*m_gameEngine->m_app.GetFrameTime(),m_retry.GetScale().x+0.002*m_gameEngine->m_app.GetFrameTime());
    else m_retry.SetScale(m_retry.GetScale().x-0.002*m_gameEngine->m_app.GetFrameTime(),m_retry.GetScale().x-0.002*m_gameEngine->m_app.GetFrameTime());

}
/**
    Pause le jeu
    Appelé lors d'un changement de state
**/
void EndState::pause(){
}
/**
    Démarrage après une pause
**/
void EndState::resume(){
}
/**
    Remet à zéro
**/
void EndState::stop(){
    m_winner.setAnimRow(0);
    m_continue.Reset();
    m_party.Reset();
}
/**
    Utilisation des entrés
**/
void EndState::GetEvents(sf::Event Event){
    if (Event.Type == sf::Event::KeyPressed && m_continue.GetElapsedTime()>3000){
        m_gameEngine->m_gameState[1]=new PlayState(m_gameEngine);
        m_gameEngine->changeState(1);
        m_start=false;
    }
}
/**
    Affichage des éléments
**/
void EndState::draw(){
    if(m_continue.GetElapsedTime()<3000){
        if(m_party.GetElapsedTime()>125){
            if(m_party.GetElapsedTime()>250)m_party.Reset();
            m_gameEngine->m_app.Draw(sf::Shape::Rectangle(0,0,GameConfig::g_config["screenwidth"], GameConfig::g_config["screenheight"], sf::Color(55,84,207)));
        }
        else {
            m_gameEngine->m_app.Draw(sf::Shape::Rectangle(0,0,GameConfig::g_config["screenwidth"], GameConfig::g_config["screenheight"], sf::Color(239,89,78)));
        }
        m_gameEngine->m_app.Draw(m_winner);
        m_gameEngine->m_app.Draw(m_trophie);
    }
    else{
        m_gameEngine->m_app.Draw(sf::Shape::Rectangle(0,0,GameConfig::g_config["screenwidth"], GameConfig::g_config["screenheight"],sf::Color::Black));
        m_gameEngine->m_app.Draw(m_winner);
        m_gameEngine->m_app.Draw(m_trophie);
        m_gameEngine->m_app.Draw(m_retry);
    }
}

EndState::~EndState(){
}
