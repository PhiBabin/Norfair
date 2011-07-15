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
#include "GameObject.hpp"
// TODO (user#1#): Ajouter la classe animation
// TODO (user#1#): Ajout et suppression d'object
// TODO (user#1#): Permettre de tirer
// TODO (user#1#): Manager d'image
// TODO (user#1#): Affichage des bras et animation.
// TODO (user#1#): Barre de vie
// TODO (user#1#): Création du vecteur de collision
// TODO (user#1#): Ajout des collisions aux objet
// TODO (user#1#): Ajout du 2ème joueur
// TODO (user#1#): Gestion de la vue
// TODO (user#1#): Ajouter item et gestion de la présence des items
// TODO (user#1#): Gestion du 4 ground et background
// TODO (user#1#): Anouncer
// TODO (user#1#): Gestion des fichiers de configuration XML
// TODO (user#1#): EXPLOSION!!!

GameObject::GameObject(sf::Image &img,int nbrFrame,int nbrLigne,float height=0, float width=0, float offsetColX=0,float offsetColY=0,bool col=false):
 ImgAnim::ImgAnim(img,nbrFrame,nbrLigne),m_colHeight(height),m_colWidth(width),m_offsetColX(offsetColX),m_offsetColY(offsetColY),m_col(col),m_velx(0),m_vely(0){
}

int GameObject::GetVelx()const{
    return m_velx;
}
int GameObject::GetVely()const{
    return m_vely;
}
sf::FloatRect GameObject::GetRect()const {
    return  sf::FloatRect(GetPosition().x,GetPosition().y,m_colWidth,m_colHeight);
}
sf::FloatRect GameObject::GetMovedRect(const float moveX,const float moveY)const{
    return sf::FloatRect(GetPosition().x+moveX,GetPosition().y+moveY,m_colWidth,m_colHeight);
}

bool GameObject::isDraw(){
    return true;
}
bool GameObject::isDelete()const{
    return false;
}
bool GameObject::isCollision()const{
    return m_col;
}

GameObject::~GameObject(){
}
