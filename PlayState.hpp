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

#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP
class PlayState: public GameState {
    public:
        PlayState(GameEngine* theGameEngine);
        virtual void init();
        virtual void loop();
        virtual void stop();
        virtual void pause();
        virtual void resume();
        virtual void GetEvents(sf::Event eventNew);
        virtual void draw();
        void addImg(const char* path,int id);
        void checkItems();
        void moveObject();
        void movePlayer(Player &player);
        virtual ~PlayState();
    private:
        Player *m_playerOne;
        Player *m_playerTwo;
        MapTile *m_map;
        sf::Image *m_imgPlayer;
        sf::View m_camera;
        sf::FloatRect m_maxMove;
        sf::Shape m_vecPlayerOne;
        sf::Shape m_vecPlayerTwo;
        sf::IntRect m_minMove;
        vector<sf::Image*> m_imgManag;
        vector<GameObject*> *m_mapObject;
        vector<GameItems*> *m_mapItems;
        GameEngine *m_gameEngine;
};

#endif // PLAYSTATE_HPP
