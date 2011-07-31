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
#ifndef GAMEITEMS_H
#define GAMEITEMS_H
class GameItems: public GameObject{
    public:
        GameItems(sf::Image &img,int nbrFrame,int nbrLigne,float height, float width,float offsetColX,float offsetColY,bool col,int x, int y,int x2, int y2,int x3, int y3);
        virtual bool isDraw();
        virtual bool isDelete()const;
        virtual bool isCollision()const;
        virtual bool collisionEffect(Player &player);
        void setGameMessage(GameMessage *gameMessage);
        virtual ~GameItems();
    private:
        PausableClock m_lastSpawn;
        bool m_draw;
        int m_x, m_y, m_x2, m_y2, m_x3, m_y3;
        GameMessage *m_gameMessage;
};

#endif // GAMEITEMS_H
