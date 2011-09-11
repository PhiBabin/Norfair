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
#define PLAYER_HPP_INCLUDED
class MapTile;
class Player:public ImgAnim{
    public:
    //! Construteur
        Player(sf::Texture &img, MapTile **map,GameMessage *gameMessage,bool machineGun);
    //! Affiche
        void Drawing(sf::RenderWindow* app);
    //! Retourne le rectangle de Camera
        sf::FloatRect GetViewRect();
    //! Retourne le rectangle de collision
        sf::FloatRect GetPlayerRect();
        sf::FloatRect GetMovedPlayerRect(const float moveX,const float moveY);
    //! Collision
        bool CollisionGeneral(const sf::FloatRect playerRect,bool &kill);
        bool CollisionHorizontal(const sf::FloatRect playerRect, bool &gauche, bool &droite,int &solidLimit);
        bool CollisionVertical(const sf::FloatRect playerRect, bool &haut, bool &bas,int &solidLimit);
        void SetBottomCollision(bool is);
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
        void SetMapObject(vector<GameEntity*> *listObject);
    //! Vie et mort
        int GetVie();
        void SetVie(int nv);
        int GetHp();
        void SetHp(int nhp);
        void Degat(int degats);
        void AddLife();
        bool IsDead();
    //! Items
        void RaiseShield();
        void GodInvocation();
        void HellInvocation();
        void Exchange();
        void MortalKombat(bool launch);
        void Shuriken();
    //! I just want to kill stuff with FIRE!
        void SetOnFire();
    //! Velocité
        void Gravity(sf::RenderWindow &app);
        float GetVelx();
        float GetVely();
        void SetVelx(float nx);
        void SetVely(float ny);
        void Pause();
        void Resume();
    //! Déconstruteur
        ~Player();
    private:
        ImgAnim *m_arm;
        ImgAnim m_vieBarre;
        ImgAnim m_hpBarre;
        ImgAnim m_blueShield;
        sf::Sound m_jumpSound;
        sf::Sound m_hurtSound;
        sf::Sound m_pafPafSound;

        MapTile **m_map;
        vector<GameEntity*> *m_listObject;
        GameMessage *m_gameMessage;

        int m_hp;
        int m_vie;
        float m_velx;
        float m_vely;
        bool m_jumpLock;
        bool m_colBot;
        bool m_direction;
        bool m_lookUp;
        bool m_moving;
        bool m_onFire;
        bool m_machineGun;
        bool m_shield;
        bool m_flashing;
        bool m_mortalKombat;
        bool m_shuriken;

        PausableClock m_shieldCoolDown;
        PausableClock m_lastShot;
        PausableClock m_burning;
        PausableClock m_hurt;
        PausableClock m_shurikenOn;
};
#endif // PLAYER_HPP_INCLUDED
