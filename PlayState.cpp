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
PlayState::PlayState(GameEngine* theGameEngine): m_playerOne(0),m_playerTwo(0),m_map(0)
,m_coutdown(GameConfig::GameConfig::g_imgManag["coutdown"].img,GameConfig::GameConfig::g_imgManag["coutdown"].nbrCollum,GameConfig::GameConfig::g_imgManag["coutdown"].nbrLine)
,m_scaleUp(false),m_start(false)
,m_gameEngine(theGameEngine){

    m_itemSound.SetBuffer(GameConfig::g_soundManag["item"]);
    m_select.SetBuffer(GameConfig::g_soundManag["select"]);

    m_playerOne= new Player(GameConfig::GameConfig::g_imgManag["mago"].img, &m_map, &m_gameMessage);
    m_playerTwo= new Player(GameConfig::GameConfig::g_imgManag["squel"].img, &m_map, &m_gameMessage, true);

    m_map =new MapTile(&(*m_gameEngine).m_app,m_playerOne,m_playerTwo);

    m_mapEntity=m_map->GetMapEntity();
    m_mapItems=m_map->GetMapItem();
    m_playerOne->SetMapObject(m_mapEntity);
    m_playerTwo->SetMapObject(m_mapEntity);



    m_coutdown.SetScale(2,2);
    m_coutdown.SetOrigin(GameConfig::g_imgManag["m_coutdown"].img.GetWidth()/2,19/2);
    m_coutdown.SetPosition(GameConfig::g_config["screenwidth"]/2,GameConfig::g_config["screenheight"]/2);
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

    if(!m_start){
        m_startCoutdown.Reset();
        m_start=true;
    }
    if(m_startCoutdown.GetElapsedTime()>4000){
        const sf::Input &Input =m_gameEngine->m_app.GetInput();

        //! Pauser le jeu
       if(Input.IsKeyDown(sf::Key::Return))pause();

        //! Control du joueur 1
        if(Input.IsKeyDown(sf::Key::L))m_playerOne->Degat(-40);
        if(Input.IsKeyDown(sf::Key::Numpad3))m_playerOne->Jump();
        if(Input.IsKeyDown(sf::Key::Numpad2))m_playerOne->Shoot();
        m_playerOne->TurnUp(Input.IsKeyDown(sf::Key::Up));
        m_playerOne->Turn(Input.IsKeyDown(sf::Key::Left),Input.IsKeyDown(sf::Key::Right));


        //! Control du joueur 2
        if (Input.IsKeyDown(sf::Key::G))m_playerTwo->Jump();
        m_playerTwo->TurnUp(Input.IsKeyDown(sf::Key::W));
        m_playerTwo->Turn(Input.IsKeyDown(sf::Key::A),Input.IsKeyDown(sf::Key::D));
        if(Input.IsKeyDown(sf::Key::F))m_playerTwo->Shoot();
    }
     else{
        if(m_coutdown.GetScale().x>2)m_scaleUp=false;
        if(m_coutdown.GetScale().x<1.2)m_scaleUp=true;

        if(m_scaleUp)m_coutdown.SetScale(m_coutdown.GetScale().x+0.002*m_gameEngine->m_app.GetFrameTime(),m_coutdown.GetScale().x+0.002*m_gameEngine->m_app.GetFrameTime());
        else m_coutdown.SetScale(m_coutdown.GetScale().x-0.002*m_gameEngine->m_app.GetFrameTime(),m_coutdown.GetScale().x-0.002*m_gameEngine->m_app.GetFrameTime());

        if(m_startCoutdown.GetElapsedTime()<=1000){
            m_coutdown.setAnimRow(0);
        }
        else if(m_startCoutdown.GetElapsedTime()<=2000){
            m_coutdown.setAnimRow(1);
        }
        else if(m_startCoutdown.GetElapsedTime()<=3000){
            m_coutdown.setAnimRow(2);
        }
        else{
            m_coutdown.setAnimRow(3);
        }
        m_coutdown.SetOrigin(GameConfig::g_imgManag["coutdown"].img.GetWidth()/2,(GameConfig::g_imgManag["coutdown"].img.GetHeight()/GameConfig::g_imgManag["coutdown"].nbrLine)*(1+m_coutdown.animRow()/2.f));
    }
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
        m_mapEntity->push_back(new GameAnim(GameConfig::g_imgManag["dead"].img,GameConfig::GameConfig::g_imgManag["dead"].nbrCollum,GameConfig::GameConfig::g_imgManag["dead"].nbrLine));
        m_mapEntity->back()->SetPosition(m_playerOne->GetPosition());
        m_mapEntity->back()->Move(0,9);
        m_mapEntity->back()->setDelay(35);
        m_playerOne->SetPosition(m_map->m_spawnLocationOne);
        m_gameMessage.AddMessage("Player 1 has been kill!");
    }
    if(m_playerTwo->IsDead()){
        m_mapEntity->push_back(new GameAnim(GameConfig::g_imgManag["dead"].img,GameConfig::GameConfig::g_imgManag["dead"].nbrCollum,GameConfig::GameConfig::g_imgManag["dead"].nbrLine));
        m_mapEntity->back()->SetPosition(m_playerTwo->GetPosition());
        m_mapEntity->back()->Move(0,8);
        m_mapEntity->back()->setDelay(35);
        m_mapEntity->back()->setAnimRow(1);
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
    for(unsigned int i=0;i<m_mapEntity->size();i++){
        m_mapEntity->at(i)->pause();
    }
    //! On change le state principale
    m_gameEngine->changeState(2);
    m_coutdown.pause();
    m_select.Play();
}
/**
    Démarrage après une pause
**/
void PlayState::resume(){
    m_playerOne->Resume();
    m_playerTwo->Resume();
    for(unsigned int i=0;i<m_mapEntity->size();i++){
        if(!m_mapEntity->at(i)->isStop())m_mapEntity->at(i)->play();
    }
    m_coutdown.play();
    m_select.Play();
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
    m_map->Draw();
    m_gameMessage.drawing(&(m_gameEngine->m_app));
    if(m_startCoutdown.GetElapsedTime()<4000)m_gameEngine->m_app.Draw(m_coutdown);
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
    bool bas=false, haut=false, gauche=false, droite=false, kill=false;
    //! On vérifie les collisions horizontals
    if(!player.CollisionHorizontal(player.GetMovedPlayerRect(movHorTest,0),gauche,droite,limitHor)){//! Pas de collision
        movHor=movHorTest;
    }
    else{//! Sinon on reposition le joueur
        player.SetVelx(0);
        if(gauche)movHor=((((limitHor+1)*GameConfig::g_config["tilewidth"]))-player.GetPosition().x)/1000.f;
        if(droite)movHor=((((limitHor)*GameConfig::g_config["tilewidth"]))-GameConfig::g_config["playercollwidth"]-player.GetPosition().x)/1000.f;
    }

    //! On vérifie les collisions vertical
    if(!player.CollisionVertical(player.GetMovedPlayerRect(0,movVerTest),haut,bas,limitVer)){//! Pas de collision
        player.Gravity(m_gameEngine->m_app);
        movVer=movVerTest;
    }
    else{//! Sinon on reposition le joueur
        if(haut){//! Si l'on touche le haut
            player.SetVely(0);
        }
        if(bas){//! Si l'on touche le sol
            if(!player.GetBottomCollision())movVer=(player.GetPosition().y-(limitVer*GameConfig::g_config["tileheight"])+GameConfig::g_config["playercollheight"])/1000.f;
            player.UnlockJump();
            player.SetBottomCollision(true);
        }
    }

    //! On vérifie si le mouvement envisagé cause une collision
    if(!player.CollisionGeneral(player.GetMovedPlayerRect(movHor,movVer),kill)&&movHor<GameConfig::g_config["tileheight"]&&movVer<GameConfig::g_config["tilewidth"])player.Move(movHor,movVer);
    else player.SetVely(0);

    //! Ouch!
    if(kill)player.Degat(200);
}

/**
    Déplacement des objets
**/
void PlayState::moveObject(){
    for(unsigned int i=0;i<m_mapEntity->size();i++){
        if(m_mapEntity->at(i)->isCollision()){
            //! On affiche détermine le rectangle de l'object
            sf::FloatRect Rect=m_mapEntity->at(i)->GetMovedRect(m_mapEntity->at(i)->GetVelx()*m_gameEngine->m_app.GetFrameTime()/1000.f,m_mapEntity->at(i)->GetVely()*m_gameEngine->m_app.GetFrameTime()/1000.f);
            //! On vérifie si l'object touche le joueur si oui on supprimer l'objet et crée un animation d'un explosion
            if((m_playerOne->GetPlayerRect().Intersects(Rect) && m_mapEntity->at(i)->collisionEffect(*m_playerOne))     //! Joueur1
               ||(m_playerTwo->GetPlayerRect().Intersects(Rect) && m_mapEntity->at(i)->collisionEffect(*m_playerTwo))){   //! Joueur 2
                //! On crée l'animation
                m_mapEntity->push_back(new GameAnim(GameConfig::g_imgManag["explosion"].img,GameConfig::GameConfig::g_imgManag["explosion"].nbrCollum,GameConfig::GameConfig::g_imgManag["explosion"].nbrLine));
                m_mapEntity->back()->SetPosition((m_playerTwo->GetPosition()));
                if(m_playerOne->GetPlayerRect().Intersects(Rect) && m_mapEntity->at(i)->collisionEffect(*m_playerOne))
                m_mapEntity->back()->SetPosition(m_playerOne->GetPosition().x+rand() *-3.f /RAND_MAX + 3.f,m_playerOne->GetPosition().y+rand() *-5.f /RAND_MAX + 2.f);
                m_mapEntity->back()->Move(0,5);
                m_mapEntity->back()->setDelay(0.1);
                //! On crée libère la mémoire de le l'instance de l'objet
                delete m_mapEntity->at(i);
                //! On supprime le pointeur du tableau dynamique
                m_mapEntity->erase( m_mapEntity->begin() + i );
            }
            else if(!m_map->CollisionGeneral(Rect))
                //! On déplace l'objet
                m_mapEntity->at(i)->Move(Rect.Left-m_mapEntity->at(i)->GetPosition().x,Rect.Top-m_mapEntity->at(i)->GetPosition().y);
            else {
                //! On crée une explosion
                m_mapEntity->push_back(new GameAnim(GameConfig::g_imgManag["explosion2"].img,GameConfig::GameConfig::g_imgManag["explosion2"].nbrCollum,GameConfig::GameConfig::g_imgManag["explosion2"].nbrLine));
                m_mapEntity->back()->SetPosition(m_mapEntity->at(i)->GetPosition().x,m_mapEntity->at(i)->GetPosition().y);
                m_mapEntity->back()->setDelay(0.1);
                delete m_mapEntity->at(i);
                m_mapEntity->erase( m_mapEntity->begin() + i );
            }
        }
        else{
            m_mapEntity->at(i)->Move(m_mapEntity->at(i)->GetVelx()*m_gameEngine->m_app.GetFrameTime(),m_mapEntity->at(i)->GetVely()*m_gameEngine->m_app.GetFrameTime());
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
