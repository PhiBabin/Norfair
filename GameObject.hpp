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
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
class Player;

class GameObject:public ImgAnim{
    public:
        GameObject(sf::Image &img,int nbrFrame,int nbrLigne,float height, float width,float offsetColX,float offsetColY,bool col);
        sf::FloatRect GetRect()const;
        sf::FloatRect GetMovedRect(const float moveX,const float moveY)const;
        int GetVelx()const;
        int GetVely()const;
        virtual bool isDraw();
        virtual bool isDelete()const;
        virtual bool isCollision()const;
        virtual bool collisionEffect(Player &player)=0;
        virtual ~GameObject();
    protected:
        int m_velx;
        int m_vely;
        bool m_col;
        float m_offsetColX;
        float m_offsetColY;
        float m_colHeight;
        float m_colWidth;
};

#endif // GAMEOBJECT_H