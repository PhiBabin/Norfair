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
}
bool GameItems::isDraw(){
   if(m_lastSpawn.GetElapsedTime()>15.f)m_draw=true;
    return m_draw;
}
bool GameItems::isDelete()const{
    return false;
}
bool GameItems::isCollision()const{
    return true;
}
bool GameItems::collisionEffect(Player &player){
    m_draw=false;
    m_lastSpawn.Reset();
    return true;
}
GameItems::~GameItems(){
}
