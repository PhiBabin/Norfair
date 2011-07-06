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

//#include "includes.hpp"
#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED;
class MapTile;
//class GameEngine;
class Player:public ImgAnim{
    public:
        //Player();
        Player(sf::Image &img, vector<sf::Image*> *imgManag, MapTile **map,bool machineGun,bool fireBall);
        sf::FloatRect GetViewRect();
        sf::FloatRect GetPlayerRect();
        sf::FloatRect GetMovedPlayerRect(const float moveX,const float moveY);
        void Gravity(sf::RenderWindow &app);
        void ResolveUp(float ry);
        void ResolveDown(float ry);
        void ResolveLeft(float rx);
        void ResolveRight(float rx);
        void mapCollision(sf::RenderWindow* app);
        void Jump();
        void UnlockJump();
        void Turn(bool left, bool right);
        void TurnUp(bool up);
        void SetMapObject(vector<GameObject*> *listObject);
        void Degat(int degats);
        void SetOnFire();
        float GetVelx();
        float GetVely();
//        void SetVely(float vely);
        void BottomCollision(bool is);
        bool GetBottomCollision() const;
        void ResetVely();
        void Shoot();
        void drawing(sf::RenderWindow* app);
    private:
       // sf::Image *m_imgArm;
        //sf::Image *m_imgBullet;
        ImgAnim *m_arm;
        ImgAnim m_lifeBarre;
        ImgAnim m_vieBarre;
        vector<sf::Image*> *m_imgManag;
        MapTile **m_map;
        int m_vie;
        int m_live;
        int m_velx;
        int m_vely;
        bool m_jumpLock;
        bool m_colBot;
        bool m_direction;
        bool m_lookUp;
        bool m_moving;
        bool m_onFire;
        bool m_machineGun;
        bool m_fireBall;
        PausableClock m_lastShot;
        vector<GameObject*> *m_listObject;
};
#endif // PLAYER_HPP_INCLUDED
