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

GameItems::GameItems(sf::Image &img,int nbrFrame,int nbrLigne,float height=0, float width=0,float offsetColX=0,float offsetColY=0,bool col=false,int x=0, int y=0,int x2=0, int y2=0,int x3=0, int y3=0):
 GameObject(img,nbrFrame,nbrLigne,height, width,offsetColX,offsetColY,col),m_draw(true)
 ,m_x(x),m_y(y),m_x2(x2),m_y2(y2),m_x3(x3),m_y3(y3){
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
    switch(rand() % 7 + 1){
        case 1:
            player.AddLife();
            m_gameMessage->AddMessage("New Life");
        break;
        case 2:
            player.GodInvocation();
            m_gameMessage->AddMessage("God hates you!");
        break;
        case 3:
            if(rand() % 4 + 1==1){
                player.MortalKombat(true);
                m_gameMessage->AddMessage("MORTAL KOMBAT!");
            }
            else{
                player.Degat(200);
                m_gameMessage->AddMessage("Sudden death");
            }
        break;
        case 4:
            player.HellInvocation();
            m_gameMessage->AddMessage("Hell Fire!");
        case 5:
            player.Exchange();
            m_gameMessage->AddMessage("The blood exchange");
        break;
        case 6:
            player.Shuriken();
            m_gameMessage->AddMessage("Shuriken of lighting");
        break;
        default:
            player.RaiseShield();
            m_gameMessage->AddMessage("Raise shield");
    }
    //! Set the seed
    srand((unsigned)time(0)*m_lastSpawn.GetElapsedTime());
    switch(rand() % 3 +1 ){
        case 2:
            SetPosition((m_x2+0.5)*g_config["tilewidth"],m_y2*g_config["tileheight"]);
        break;
        case 3:
            SetPosition((m_x3+0.5)*g_config["tilewidth"],m_y3*g_config["tileheight"]);
        break;
        default:
            SetPosition((m_x+0.5)*g_config["tilewidth"],m_y*g_config["tileheight"]);
    }
    m_lastSpawn.Reset();
    return true;
}
void GameItems::setGameMessage(GameMessage *gameMessage){
    m_gameMessage=gameMessage;
}
GameItems::~GameItems(){
}
