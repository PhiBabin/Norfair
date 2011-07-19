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

#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED;
class MapTile;
class Player:public ImgAnim{
    public:
    //! Construteur
        Player(sf::Image &img, vector<sf::Image*> *imgManag, MapTile **map,bool machineGun);
    //! Affiche
        void drawing(sf::RenderWindow* app);
    //! Retourne le rectangle de Camera
        sf::FloatRect GetViewRect();
    //! Retourne le rectangle de collision
        sf::FloatRect GetPlayerRect();
        sf::FloatRect GetMovedPlayerRect(const float moveX,const float moveY);
    //! Collision
        bool collisionGeneral(const sf::FloatRect playerRect,bool &kill);
        bool collisionHorizontal(const sf::FloatRect playerRect, bool &gauche, bool &droite,int &solidLimit);
        bool collisionVertical(const sf::FloatRect playerRect, bool &haut, bool &bas,int &solidLimit);
        void BottomCollision(bool is);
        bool GetBottomCollision() const;
    //! Saut
        void Jump();
        void UnlockJump();
    //! Tire
        void Shoot();
    //! Déplacement
        void Turn(bool left, bool right);
        void TurnUp(bool up);
    //! Link la liste des entités
        void SetMapObject(vector<GameObject*> *listObject);
    //! Vie et mort
        int GetVie();
        void Degat(int degats);
        bool IsDead();
    //! I just want to kill stuff with FIRE!
        void SetOnFire();
    //! Velocité
        void Gravity(sf::RenderWindow &app);
        float GetVelx();
        float GetVely();
        void SetVelx(float nx);
        void SetVely(float ny);
        void ResetVely();
    //! Pause et arrêt
        void Pause();
        void Resume();
    private:
        ImgAnim *m_arm;
        ImgAnim m_vieBarre;
        ImgAnim m_hpBarre;
        vector<sf::Image*> *m_imgManag;

        MapTile **m_map;
        vector<GameObject*> *m_listObject;

        int m_hp;
        int m_vie;
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
};
#endif // PLAYER_HPP_INCLUDED
