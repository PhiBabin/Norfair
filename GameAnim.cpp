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
#include "GameAnim.hpp"

GameAnim::GameAnim(sf::Image &img,int nbrFrame,int nbrLigne,float time=0.f,float height=0, float width=0,float offsetColX=0,float offsetColY=0,bool col=false):
 GameEntity(img,nbrFrame,nbrLigne,height, width,offsetColX,offsetColY,col),m_nbrFrame(nbrFrame){
    loop(false);
}
bool GameAnim::isDraw(){
    return true;
}
bool GameAnim::isDelete()const{
    if(currentFrame()==(m_nbrFrame-1)||!isPlaying())return true;
    else{
        return false;
    }
}
bool GameAnim::isCollision()const{
    return m_col;
}
bool GameAnim::collisionEffect(Player &player){return false;}
GameAnim::~GameAnim(){
}
