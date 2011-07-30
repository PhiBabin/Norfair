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

#include "PlayState.hpp"
#include "GameEngine.hpp"

/**
    Construction des éléments du jeu
**/
PlayState::PlayState(GameEngine* theGameEngine): m_playerOne(0),m_playerTwo(0),m_map(0),m_maxMove(0,0,200,200), m_gameEngine(theGameEngine){

    m_itemSound.SetBuffer(g_soundManag["item"]);

    m_playerOne= new Player((g_imgManag)["mago"].img, &m_map);
    m_playerTwo= new Player((g_imgManag)["squel"].img, &m_map, true);

    m_map =new MapTile(&(*m_gameEngine).m_app,m_playerOne,m_playerTwo);

    m_mapObject=m_map->getMapObject();
    m_mapItems=m_map->getMapItem();
    m_playerOne->SetMapObject(m_mapObject);
    m_playerTwo->SetMapObject(m_mapObject);
}
/**
    Initialisation des éléments du jeu
    Cette méthode est appelé lors démarrage ou du redémarrage du state
**/
void PlayState::init(){
    resume();
}
/**
    Exécution des éléments
**/
void PlayState::loop(){
    /**
        Gestion des entrées claviers
    */

//    //! Pauser le jeu
//   if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Return))pause();
//
//    //! Control du joueur 1
//    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::M))m_playerOne->Jump();
//    m_playerOne->TurnUp(sf::Keyboard::IsKeyPressed(sf::Keyboard::Up));
//    m_playerOne->Turn(sf::Keyboard::IsKeyPressed(sf::Keyboard::Left),sf::Keyboard::IsKeyPressed(sf::Keyboard::Right));
//    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::N))m_playerOne->Shoot();
//
//
//    //! Control du joueur 2
//    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::G))m_playerTwo->Jump();
//    m_playerTwo->TurnUp(sf::Keyboard::IsKeyPressed(sf::Keyboard::W));
//    m_playerTwo->Turn(sf::Keyboard::IsKeyPressed(sf::Keyboard::A),sf::Keyboard::IsKeyPressed(sf::Keyboard::D));
//    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::F))m_playerTwo->Shoot();

    const sf::Input &Input =m_gameEngine->m_app.GetInput();

    //! Pauser le jeu
   if(Input.IsKeyDown(sf::Key::Return))pause();

    //! Control du joueur 1
    if (Input.IsKeyDown(sf::Key::M))m_playerOne->Jump();
    m_playerOne->TurnUp(Input.IsKeyDown(sf::Key::Up));
    m_playerOne->Turn(Input.IsKeyDown(sf::Key::Left),Input.IsKeyDown(sf::Key::Right));
    if(Input.IsKeyDown(sf::Key::N))m_playerOne->Shoot();


    //! Control du joueur 2
    if (Input.IsKeyDown(sf::Key::G))m_playerTwo->Jump();
    m_playerTwo->TurnUp(Input.IsKeyDown(sf::Key::W));
    m_playerTwo->Turn(Input.IsKeyDown(sf::Key::A),Input.IsKeyDown(sf::Key::D));
    if(Input.IsKeyDown(sf::Key::F))m_playerTwo->Shoot();

    /**
        Gestion des personnages et objets
    */

 //! Déplacement du personnage 1
    movePlayer(*m_playerOne);

 //! Déplacement du personnage 2
    movePlayer(*m_playerTwo);

 //! Vérifie les items
    checkItems();

 //! Déplacement des objets
    moveObject();

 //! On vérifie si les personnages sont vivant
    if(m_playerOne->IsDead()){
        m_map->getMapObject()->push_back(new GameAnim(g_imgManag["dead"].img,(g_imgManag)["dead"].nbrCollum,(g_imgManag)["dead"].nbrLine));
        m_map->getMapObject()->back()->SetPosition(m_playerOne->GetPosition());
        m_map->getMapObject()->back()->Move(0,9);
        m_map->getMapObject()->back()->setDelay(35);
        m_playerOne->SetPosition(m_map->m_spawnLocationOne);
        m_gameMessage.AddMessage("Player 1 has been kill!");
    }
    if(m_playerTwo->IsDead()){
        m_map->getMapObject()->push_back(new GameAnim(g_imgManag["dead"].img,(g_imgManag)["dead"].nbrCollum,(g_imgManag)["dead"].nbrLine));
        m_map->getMapObject()->back()->SetPosition(m_playerTwo->GetPosition());
        m_map->getMapObject()->back()->Move(0,8);
        m_map->getMapObject()->back()->setDelay(35);
        m_map->getMapObject()->back()->setAnimRow(1);
        m_playerTwo->SetPosition(m_map->m_spawnLocationTwo);
        m_gameMessage.AddMessage("Player 2 has been kill!");
    }

//! On vérifie si ils ont encore des vies
    if(m_playerOne->GetVie()<=0){
        m_gameEngine->m_gameState.at(3)->init();
        m_gameEngine->changeState(3);
    }
    if(m_playerTwo->GetVie()<=0){
        m_gameEngine->m_gameState.at(3)->stop();
        m_gameEngine->changeState(3);
    }
}
/**
    Pause le jeu
    Appelé lors d'un changement de state
**/
void PlayState::pause(){
    m_playerOne->Pause();
    m_playerTwo->Pause();
    for(unsigned int i=0;i<m_mapObject->size();i++){
        m_mapObject->at(i)->pause();
    }
    //! On change le state principale
    m_gameEngine->changeState(2);
}
/**
    Démarrage après une pause
**/
void PlayState::resume(){
    m_playerOne->Resume();
    m_playerTwo->Resume();
    for(unsigned int i=0;i<m_mapObject->size();i++){
        if(!m_mapObject->at(i)->isStop())m_mapObject->at(i)->play();
    }
}
/**
    Remet à zéro
**/
void PlayState::stop(){
}
/**
    Utilisation des entrés
**/
void PlayState::GetEvents(sf::Event){
}
/**
    Affichage des éléments
**/
void PlayState::draw(){
    m_map->draw();
    m_gameMessage.drawing(&(m_gameEngine->m_app));
}


/**
    On vérifie les items
**/
void PlayState::checkItems(){
    for(unsigned int i=0;i<m_mapItems->size();i++){
        m_mapItems->at(i)->setGameMessage(&m_gameMessage);
        if(m_mapItems->at(i)->isCollision()){
            if(m_playerOne->GetPlayerRect().Intersects(m_mapItems->at(i)->GetRect())){
                 m_itemSound.Play();
                m_mapItems->at(i)->collisionEffect(*m_playerOne);
            }
            if(m_playerTwo->GetPlayerRect().Intersects(m_mapItems->at(i)->GetRect())){
                 m_itemSound.Play();
                m_mapItems->at(i)->collisionEffect(*m_playerTwo);
            }
        }
    }

}

/**
    Déplacement d'un Player dans la map
**/
void PlayState::movePlayer(Player &player){
    float movHor=0;
    float movVer=0;
    int limitVer=0;
    int limitHor=0;
    float movHorTest=player.GetVelx()*m_gameEngine->m_app.GetFrameTime()/1000.f;
    float movVerTest=player.GetVely()*m_gameEngine->m_app.GetFrameTime()/1000.f;
    bool bas=false;
    bool haut=false;
    bool gauche=false;
    bool droite=false;
    bool kill=false;
    //! On vérifie les collisions horizontals
    if(!player.collisionHorizontal(player.GetMovedPlayerRect(movHorTest,0),gauche,droite,limitHor)){//! Pas de collision
        movHor=movHorTest;
    }
    else{//! Sinon on reposition le joueur
        player.ResetVelx();
        if(gauche)movHor=((((limitHor+1)*g_config["tilewidth"]))-player.GetPosition().x)/1000.f;
        if(droite)movHor=((((limitHor)*g_config["tilewidth"]))-g_config["playercollwidth"]-player.GetPosition().x)/1000.f;
    }

    //! On vérifie les collisions vertical
    if(!player.collisionVertical(player.GetMovedPlayerRect(0,movVerTest),haut,bas,limitVer)){//! Pas de collision
        player.Gravity(m_gameEngine->m_app);
        movVer=movVerTest;
    }
    else{//! Sinon on reposition le joueur
        if(haut){//! Si l'on touche le haut
            player.ResetVely();
        }
        if(bas){//! Si l'on touche le sol
            if(!player.GetBottomCollision())movVer=(player.GetPosition().y-(limitVer*g_config["tileheight"])+g_config["playercollheight"])/1000.f;
            player.UnlockJump();
            player.BottomCollision(true);
        }
    }

    //! On vérifie si le mouvement envisagé cause une collision
    if(!player.collisionGeneral(player.GetMovedPlayerRect(movHor,movVer),kill)&&movHor<g_config["tileheight"]&&movVer<g_config["tilewidth"])player.Move(movHor,movVer);
    else player.ResetVely();

    //! Ouch!
    if(kill)player.Degat(200);
}

/**
    Déplacement des objets
**/
void PlayState::moveObject(){
    for(unsigned int i=0;i<m_mapObject->size();i++){
        if(m_mapObject->at(i)->isCollision()){
            //! On affiche détermine le rectangle de l'object
            sf::FloatRect Rect=m_mapObject->at(i)->GetMovedRect(m_mapObject->at(i)->GetVelx()*m_gameEngine->m_app.GetFrameTime()/1000.f,m_mapObject->at(i)->GetVely()*m_gameEngine->m_app.GetFrameTime()/1000.f);
            //! On vérifie si l'object touche le joueur si oui on supprimer l'objet et crée un animation d'un explosion
            if((m_playerOne->GetPlayerRect().Intersects(Rect) && m_mapObject->at(i)->collisionEffect(*m_playerOne))     //! Joueur1
               ||(m_playerTwo->GetPlayerRect().Intersects(Rect) && m_mapObject->at(i)->collisionEffect(*m_playerTwo))){   //! Joueur 2
                //! On crée l'animation
                m_map->getMapObject()->push_back(new GameAnim(g_imgManag["explosion"].img,(g_imgManag)["explosion"].nbrCollum,(g_imgManag)["explosion"].nbrLine));
                m_mapObject->back()->SetPosition((m_playerTwo->GetPosition()));
                if(m_playerOne->GetPlayerRect().Intersects(Rect) && m_mapObject->at(i)->collisionEffect(*m_playerOne))
                m_mapObject->back()->SetPosition(m_playerOne->GetPosition().x+rand() *-3.f /RAND_MAX + 3.f,m_playerOne->GetPosition().y+rand() *-5.f /RAND_MAX + 2.f);
                m_mapObject->back()->Move(0,5);
                m_mapObject->back()->setDelay(0.1);
                //! On crée libère la mémoire de le l'instance de l'objet
                delete m_mapObject->at(i);
                //! On supprime le pointeur du tableau dynamique
                m_mapObject->erase( m_mapObject->begin() + i );
            }
            else if(!m_map->collisionGeneral(Rect))
                //! On déplace l'objet
                m_mapObject->at(i)->Move(Rect.Left-m_mapObject->at(i)->GetPosition().x,Rect.Top-m_mapObject->at(i)->GetPosition().y);
            else {
                //! On crée une explosion
                m_map->getMapObject()->push_back(new GameAnim(g_imgManag["explosion2"].img,(g_imgManag)["explosion2"].nbrCollum,(g_imgManag)["explosion2"].nbrLine));
                m_mapObject->back()->SetPosition(m_mapObject->at(i)->GetPosition().x,m_mapObject->at(i)->GetPosition().y);
                m_mapObject->back()->setDelay(0.1);
                delete m_mapObject->at(i);
                m_mapObject->erase( m_mapObject->begin() + i );
            }
        }
    }
}

/**
    Déconstruction des éléments du jeu
**/
PlayState::~PlayState(){
    delete m_playerOne;
    delete m_playerTwo;
    delete m_map;
}
