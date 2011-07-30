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
#include "GameItems.hpp"
#include "Player.hpp"

GameItems::GameItems(sf::Image &img,int nbrFrame,int nbrLigne,float height=0, float width=0,float offsetColX=0,float offsetColY=0,bool col=false):
 GameObject(img,nbrFrame,nbrLigne,height, width,offsetColX,offsetColY,col),m_draw(true){
     m_lastSpawn.Reset();
     if(height==0){
         m_colHeight=img.GetHeight()/nbrLigne;
         m_colWidth=img.GetWidth()/nbrFrame;
     }
}
bool GameItems::isDraw(){
   if(m_lastSpawn.GetElapsedTime()/1000>g_config["itemcooldown"])m_draw=true;
   else m_draw=false;
    return m_draw;
}
bool GameItems::isDelete()const{
    return false;
}
bool GameItems::isCollision()const{
    return m_draw;
}
bool GameItems::collisionEffect(Player &player){
    m_draw=false;
    m_lastSpawn.Reset();
    switch(rand() % 3 + 1){
        case 1:
            player.AddLife();
            m_gameMessage->AddMessage("New Life");
        break;
        case 2:
            player.GodInvocation();
            m_gameMessage->AddMessage("God hates you!");
        break;
        default:
            player.RaiseShield();
            m_gameMessage->AddMessage("Raise shield");
    }
    return true;
}
void GameItems::setGameMessage(GameMessage *gameMessage){
    m_gameMessage=gameMessage;
}
GameItems::~GameItems(){
}
