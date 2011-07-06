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
PlayState::PlayState(GameEngine* theGameEngine): m_playerOne(0),m_playerTwo(0),m_map(0),m_maxMove(0,0,200,200){
//    m_camera.SetFromRect(m_maxMove);
    m_imgManag.resize(20);
    addImg(MAGOPATH,MAGOID);
    addImg(SQUELPATH,SQUELID);
	addImg(FIREPATH,FIREID);
	addImg(SHOTPATH,SHOTID);
	addImg(ARMMPATH,ARMMID);
	addImg(VIEPATH,VIEID);
	addImg(LIFEPATH,LIFEID);
	addImg(EXPPATH,EXPID);
	addImg(EXP2PATH,EXP2ID);
	addImg(EXP3PATH,EXP3ID);
    m_playerOne= new Player(*m_imgManag.at(MAGOID), &m_imgManag, &m_map, false, true);
    m_playerTwo= new Player(*m_imgManag.at(SQUELID), &m_imgManag, &m_map, true, false);

    m_gameEngine=theGameEngine;
    m_map =new MapTile(&(*m_gameEngine).m_app,MAPPATH,"tile5.png","tileimage_NorAdvan2.png","tileprop5.txt",&m_imgManag,m_playerOne,m_playerTwo);

    m_mapObject=m_map->getMapObject();
    m_playerOne->SetMapObject(m_mapObject);
    m_playerTwo->SetMapObject(m_mapObject);




    //m_map.setPlayer();
}
/**
    Initialisation des éléments du jeu
    Cette méthode est appelé lors démarrage ou du redémarrage du state
**/
void PlayState::init(){
}
/**
    Exécution des éléments
**/
void PlayState::loop(){

    /**
        Gestion des entrées claviers
    */
    const sf::Input &Input =m_gameEngine->m_app.GetInput();
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

    if(Input.IsKeyDown(sf::Key::V))m_playerOne->Degat(4);
    if(Input.IsKeyDown(sf::Key::B))m_playerOne->Degat(-6);
    if(Input.IsKeyDown(sf::Key::Z))m_map->getMapObject()->push_back(new GameAnim(*m_imgManag[EXP3ID],4,1));
///    m_mapObject->back()->SetPosition(m_playerOne->GetPosition().x+3.f +sf::Randomizer::Random(-3, 3),m_playerOne->GetPosition().y+3.f+sf::Randomizer::Random(-8, 8));
///    m_mapObject->back()->setDelay(0.1);cout<< m_mapObject->size()<<endl;}
    bool inutile;
    if(m_map->collisionGeneral(m_playerOne->GetPlayerRect(),inutile)){
         cout<<"this is shit"<<endl;
         sleep(1);
         ///exit(0);
    }
 //! Déplacement du personnage
    //movePlayer(*m_playerOne);
    m_playerOne->mapCollision(&(m_gameEngine->m_app));
 //! Déplacement de la vue
 // moveView(*m_playerOne);
    movePlayer(*m_playerTwo);
 //! Déplacement des objets
    moveObject();


}
/**
    Arrêt du jeu
    Appelé lors d'un défocus ou d'un changement de state
**/
void PlayState::pause(){
}
/**
    Démarrage après une pause
**/
void PlayState::resume(){
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
    float x= m_playerOne->GetPosition().x;
    float y= m_playerOne->GetPosition().y;
   //! m_gameEngine->m_app.Draw(sf::Shape::Line(x+8, y+8,  x+8, 8+y+(m_playerOne->GetVely())*0.6666,1,sf::Color(0, 0, 0, 200)));
   //! m_gameEngine->m_app.Draw(sf::Shape::Line(x+8, y+8,  x+8+(m_playerOne->GetVelx())*0.6666, 8+y,1,sf::Color(0, 0, 0, 200)));
   //! m_gameEngine->m_app.Draw(sf::Shape::Line(x+8, y+8,  x+8+(m_playerOne->GetVelx())*0.6666, 8+y+(m_playerOne->GetVely())*0.6666,3,sf::Color(255, 0, 0, 200)));
}

/**
    Ajoute un sprite
**/
void PlayState::addImg(const char* path,int id){
	m_imgManag.at(id)=new sf::Image;
	m_imgManag.at(id)->LoadFromFile(path);
	m_imgManag.at(id)->SetSmooth(false);
}

/**
    Affichage les vecteurs
**/
void PlayState::showVector(){
    float x= m_playerOne->GetPosition().x;
    float y= m_playerOne->GetPosition().y;
    float x2= m_playerTwo->GetPosition().x;
    float y2= m_playerTwo->GetPosition().y;
    sf::Shape *vecPlayerOne;
   // vecPlayerOne = sf::Shape::Line(x, y, x+m_playerOne->GetVelx, x+m_playerOne->GetVely,3,sf::Color(255, 255, 255, 200));

}
/**
    Déplacement d'un Player dans la map
**/
void PlayState::movePlayer(Player &player){
    float movHor=0;
    float movVer=0;
    float movHorTest=player.GetVelx()*m_gameEngine->m_app.GetFrameTime()/1000;
    float movVerTest=player.GetVely()*m_gameEngine->m_app.GetFrameTime()/1000;
    bool bas=false;
    bool haut=false;
    bool gauche=false;
    bool droite=false;
    bool kill=false;
    int limitVer=0;
    int limitHor=0;
    if(!m_map->collisionHorizontal(player.GetMovedPlayerRect(movHorTest,0),gauche,droite,limitHor)){
       movHor=movHorTest;
    }
    else{
        if(gauche)movHor=(((limitHor+1)*TILEWIDTH))-player.GetPosition().x;
        if(droite)movHor=(((limitHor)*TILEWIDTH))-PLAYERCOLLISIONWIDTH-player.GetPosition().x;
        //if(droite)movHor=-m_playerOne->GetPosition().x+((limitHor)*TILEWIDTH)-1-PLAYERCOLLISIONWIDTH;
    }

    if(!m_map->collisionVertical(player.GetMovedPlayerRect(0,movVerTest),haut,bas,limitVer)){
        player.Gravity(m_gameEngine->m_app);
//        player.Move(0,GRAVITY*m_gameEngine->m_app.GetFrameTime());
        movVer=movVerTest;
    }
    else{
        if(haut){
            player.ResetVely();
        }
        if(bas){
            if(!player.GetBottomCollision())movVer=player.GetPosition().y-(limitVer*TILEHEIGHT)+PLAYERCOLLISIONHEIGHT;
            player.UnlockJump();
            player.BottomCollision(true);
        }
    }

    if(!m_map->collisionVertical(player.GetMovedPlayerRect(movHor,movVer),haut,bas,limitVer)&&!m_map->collisionHorizontal(player.GetMovedPlayerRect(movHor,movVer),gauche,droite,limitHor)/*&&
       !m_map->collisionGeneral(player.GetMovedPlayerRect(movHor,movVer),kill)*/&&movHor<TILEHEIGHT&&movVer<TILEWIDTH) player.Move(movHor,movVer);
    if(kill)player.Degat(200);
}

void PlayState::moveObject(){
    bool inutile;
    for(int i=0;i<m_mapObject->size();i++){
        if(m_mapObject->at(i)->isCollision()){
            //! On affiche détermine le rectangle de l'object
            sf::FloatRect Rect=m_mapObject->at(i)->GetMovedRect(m_mapObject->at(i)->GetVelx()*m_gameEngine->m_app.GetFrameTime()/1000,m_mapObject->at(i)->GetVely()*m_gameEngine->m_app.GetFrameTime()/1000);
            //! On vérifie si l'object touche le joueur si oui on supprimer l'objet et crée un animation d'un explosion
            if((m_playerOne->GetPlayerRect().Intersects(Rect) && m_mapObject->at(i)->collisionEffect(*m_playerOne))     //! Joueur1
               ||m_playerTwo->GetPlayerRect().Intersects(Rect) && m_mapObject->at(i)->collisionEffect(*m_playerTwo)){   //! Joueur 2
                //! On crée l'animation
                m_map->getMapObject()->push_back(new GameAnim(*m_imgManag[EXPID],EXPNBRCOLUMN,EXPNBRLIGNE));
                m_mapObject->back()->SetPosition(m_mapObject->at(i)->GetPosition().x,m_mapObject->at(i)->GetPosition().y);
                m_mapObject->back()->setDelay(0.1);
                //! On crée libère la mémoire de le l'instance de l'objet
                delete m_mapObject->at(i);
                //! On supprime le pointeur du tableau dynamique
                m_mapObject->erase( m_mapObject->begin() + i );
            }
            else if(!m_map->collisionGeneral(Rect,inutile))
                m_mapObject->at(i)->Move(m_mapObject->at(i)->GetVelx()*m_gameEngine->m_app.GetFrameTime()/1000,m_mapObject->at(i)->GetVely()*m_gameEngine->m_app.GetFrameTime()/1000);
            else {
                m_map->getMapObject()->push_back(new GameAnim(*m_imgManag[EXP2ID],EXP2NBRCOLUMN,EXP2NBRLIGNE));
                m_mapObject->back()->SetPosition(m_mapObject->at(i)->GetPosition().x,m_mapObject->at(i)->GetPosition().y);
                m_mapObject->back()->setDelay(0.1);
                delete m_mapObject->at(i);
                m_mapObject->erase( m_mapObject->begin() + i );
            }
        }
    }
}


//void PlayState::moveView(Player &player){
//    float x1,x2,y1,y2;
//    //sf::FloatRect newView;
//    float screenRapport= SCREENHEIGHT/SCREENWIDTH;
//    float screenRapport2= SCREENWIDTH/SCREENHEIGHT;
//    if(m_playerOne->GetPosition().x>m_playerTwo->GetPosition().x){
//        x2=m_playerOne->GetPosition().x+PLAYERCOLLISIONWIDTH;
//        x1=m_playerTwo->GetPosition().x;
//    }
//    if(m_playerOne->GetPosition().x<m_playerTwo->GetPosition().x){
//        x1=m_playerOne->GetPosition().x;
//        x2=m_playerTwo->GetPosition().x+PLAYERCOLLISIONWIDTH;
//    }
//
//    if(m_playerOne->GetPosition().y>m_playerTwo->GetPosition().y){
//        y2=m_playerOne->GetPosition().y+PLAYERCOLLISIONHEIGHT;
//        y1=m_playerTwo->GetPosition().y;
//    }
//    if(m_playerOne->GetPosition().y<m_playerTwo->GetPosition().y){
//        y1=m_playerOne->GetPosition().y+PLAYERCOLLISIONHEIGHT;
//        y2=m_playerTwo->GetPosition().y;
//    }
//    cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
//    m_camera.SetCenter((x2-x1)/2+x1,(y2-y1)/2+y1);
//            cout<<"chus en haut"<<m_camera.GetRect().Top-y1<<" "<<m_camera.GetRect().Top<<endl;
//    if(!m_camera.GetRect().Intersects(player.GetPlayerRect())){
//        if(m_camera.GetRect().Top<y1-50){
//            m_maxMove=sf::FloatRect(m_camera.GetRect().Left-(m_camera.GetRect().Top+50-y1)*screenRapport2,y1-50,m_camera.GetRect().Right,m_camera.GetRect().Bottom);
//            //m_maxMove.Offset((player.GetPlayerRect().Top-m_maxMove.Top)*screenRapport2,player.GetPlayerRect().Top-m_maxMove.Top);
//             m_camera.SetFromRect(m_maxMove);
//
//       }
//
//    }
//    m_camera.SetCenter((x2-x1)/2+x1,(y2-y1)/2+y1);
//        //cout << m_camera.GetRect().Left-(x2-x1)/2.f-200.f+x1<<endl;//-(x2-x1)/2.f-200.f+x1
////    if(x2-x1>370.f || y2-y1>(370*screenRapport)|| 1==1){
////        m_camera.SetCenter((x2-x1)/2+x1,(y2-y1)/2+y1);
////        if(x2-x1>y2-y1)m_camera.SetHalfSize((x2-x1)/2+50,screenRapport*((x2-x1))/2+50);
////        else m_camera.SetHalfSize(screenRapport2*((y2-y1))/2+50,(y2-y1)/2+50);
////         //m_camera.SetFromRect(sf::FloatRect((x2-x1)/2.f*-0.8+x1,(y2-y1)/2.f*(-0.8*screenRapport)+y1,(x2-x1)/2.f*0.8+x1,(y2-y1)/2.f*(0.8*screenRapport)+y1));
////    }
////    else{//sf::FloatRect(x1-(0.1*400.f),x1+(1.1*400.f),(y1+(1.1*400.f)*screenRapport),(y1+(1.1*400.f)*screenRapport))
////        //!if(y2-y1<(400*screenRapport))
////        m_camera.SetFromRect(sf::FloatRect((x2-x1)/2.f-200.f+x1,(y2-y1)/2.f-(200*screenRapport)+y1,(x2-x1)/2.f+200.f+x1,(y2-y1)/2.f+(200*screenRapport)+y1));
////        //!else m_camera.SetFromRect(sf::FloatRect((x2-x1)/2.f-(200.f*screenRapport2)+x1,(y2-y1)/2.f-(200.f*screenRapport)+y1,(x2-x1)/2.f+(200.f*screenRapport2)+x1,(y2-y1)/2.f+(200.f*screenRapport)+y1));
////    }
//   m_gameEngine->m_app.SetView(m_camera);
//}
/**
    Déconstruction des éléments du jeu
**/
PlayState::~PlayState(){
}
