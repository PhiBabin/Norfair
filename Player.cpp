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

#include "Player.hpp"
Player::Player(sf::Image &img, vector<sf::Image*> *imgManag,MapTile **map,bool machineGun=false):
 ImgAnim::ImgAnim(img,3,4),m_colBot(false),m_velx(0),m_vely(0),m_hp(100),m_vie(3)
 ,m_imgManag(imgManag),m_machineGun(machineGun)
 ,m_hpBarre(*imgManag->at(HPID),HPNBRCOLUMN,HPNBRLIGNE)
 ,m_vieBarre(*imgManag->at(VIEID),VIENBRCOLUMN,VIENBRLIGNE)
 ,m_map(map){
    setDelay(0.2);
     if(!machineGun)m_arm=new ImgAnim(*imgManag->at(ARMMID),ARMMNBRCOLUMN,ARMMNBRLIGNE);
     else m_arm=new ImgAnim(*imgManag->at(ARMMID),ARMMNBRCOLUMN,ARMMNBRLIGNE);
    m_arm->setDelay(0.2);
}

sf::FloatRect Player::GetPlayerRect(){
    return sf::FloatRect(GetPosition().x,GetPosition().y,PLAYERCOLLISIONWIDTH,PLAYERCOLLISIONHEIGHT);
}
sf::FloatRect Player::GetMovedPlayerRect(const float moveX,const float moveY){
  return sf::FloatRect(GetPosition().x+moveX,GetPosition().y+moveY,PLAYERCOLLISIONWIDTH,PLAYERCOLLISIONHEIGHT);
}
sf::FloatRect Player::GetViewRect(){
   return sf::FloatRect(GetPosition().x-SCREENWIDTH/8,GetPosition().y-SCREENHEIGHT/8,GetPosition().x+SCREENWIDTH/8,GetPosition().y+SCREENHEIGHT/8);
}

void Player::Gravity(sf::RenderWindow &app){
        m_vely+=GRAVITY*app.GetFrameTime()/1000;
}
void Player::Jump(){
    if(!m_jumpLock){
        m_jumpLock=true;
        m_vely+=-400;
        BottomCollision(false);
        cout<<"jump"<<endl;
    }
}
void Player::TurnUp(bool up){
    if(up==HAUT)m_lookUp=true;
    else m_lookUp=false;
}
void Player::Turn(bool left, bool right){

    if(left&&!right){
        m_moving=true;
        m_direction=GAUCHE;
        if(m_colBot){
            setAnimRow(1);
        }
        else {
            setAnimRow(3);
        }
        m_arm->setAnimRow(1);
        m_arm->play();
        play();
        m_velx=-150.f;
    }
    else if(!left&&right){
        m_moving=true;
        m_direction=DROITE;
        if(m_colBot)setAnimRow(0);
        else setAnimRow(2);
        play();
        m_arm->setAnimRow(0);
        m_arm->play();
        m_velx=150.f;
    }
    else{
        m_moving=false;
        if(m_colBot&& m_direction==GAUCHE)setAnimRow(1);
        else if(m_colBot&& m_direction==DROITE)setAnimRow(0);
        else if(animRow()<2) setAnimRow(animRow()+2);
        else setAnimRow(animRow());
        stop();
m_arm->stop();
        m_velx=0;
    }
}
 bool Player::collisionGeneral(const sf::FloatRect playerRect,bool &kill){
    int maxHeight, minHeight, maxWidth, minWidth;
    bool Collision=false;
    minHeight=playerRect.Top/TILEHEIGHT;
    minWidth=playerRect.Left/TILEWIDTH;
    maxHeight=(playerRect.Top+playerRect.Height-1)/TILEHEIGHT;
    maxWidth=(playerRect.Left+playerRect.Width-1)/TILEWIDTH;

    if(minHeight<0)minHeight=0;
    if(maxHeight>(*m_map)->m_height)maxHeight=(*m_map)->m_height;
    if(minWidth<0)minWidth=0;
    if(maxWidth>(*m_map)->m_width)maxWidth=(*m_map)->m_width;
    for(int y=minHeight;y<=maxHeight;y++){
        for(int x=minWidth;x<=maxWidth;x++){
            if(!(x>=(*m_map)->m_width or y>=(*m_map)->m_height)){
                if((*m_map)->Tile(x,y).kill)kill=true;
                if((*m_map)->Tile(x,y).solid){
                    sf::FloatRect  theTile(x*TILEWIDTH,y*TILEHEIGHT,TILEWIDTH,TILEHEIGHT);
                    if(playerRect.Intersects(theTile)||theTile.Intersects(playerRect)) return true;
                }
            }
        }
    }
    return false;
 }
 bool Player::collisionVertical(const sf::FloatRect playerRect, bool &haut, bool &bas,int &solidLimit){
    int maxHeight, minHeight, maxWidth, minWidth;
    bool CollisionVertical=false;
    minHeight=playerRect.Top/TILEHEIGHT;
    minWidth=playerRect.Left/TILEWIDTH;
    maxHeight=(playerRect.Top+playerRect.Height-1)/TILEHEIGHT;
    maxWidth=(playerRect.Left+playerRect.Width-1)/TILEWIDTH;

    if(minHeight<0)minHeight=0;
    if(maxHeight>(*m_map)->m_height)maxHeight=(*m_map)->m_height;
    if(minWidth<0)minWidth=0;
    if(maxWidth>(*m_map)->m_width)maxWidth=(*m_map)->m_width;
    for(int y=minHeight;y<=maxHeight;y++){
        for(int x=minWidth;x<=maxWidth;x++){
            if(!(x>=(*m_map)->m_width or y>=(*m_map)->m_height)){
                if((*m_map)->Tile(x,y).solid){

                    sf::FloatRect  theTile(x*TILEWIDTH,y*TILEHEIGHT,TILEWIDTH,TILEHEIGHT);
                    if(playerRect.Intersects(theTile)||theTile.Intersects(playerRect)){
                        CollisionVertical=true;
                        if(y*TILEHEIGHT<=playerRect.Top+playerRect.Height&&y*TILEHEIGHT>=playerRect.Top){
                            bas=true;
                            solidLimit=y;
                        }
                        if((y+1)*TILEHEIGHT>=playerRect.Top&&(y+1)*TILEHEIGHT<=playerRect.Top+playerRect.Height){
                            haut=true;
                        }
                    }
                }
            }
        }
    }
    return CollisionVertical;
 }
 bool Player::collisionHorizontal(const sf::FloatRect playerRect, bool &gauche, bool &droite,int &solidLimit){
    int maxHeight, minHeight, maxWidth, minWidth;
    bool CollisionHorizontal=false;
    minHeight=playerRect.Top/TILEHEIGHT;
    minWidth=playerRect.Left/TILEWIDTH;
    maxHeight=(playerRect.Top+playerRect.Height-1)/TILEHEIGHT;
    maxWidth=(playerRect.Left+playerRect.Width-1)/TILEWIDTH;

    if(minHeight<0)minHeight=0;
    if(maxHeight>(*m_map)->m_height)maxHeight=(*m_map)->m_height;
    if(minWidth<0)minWidth=0;
    if(maxWidth>(*m_map)->m_width)maxWidth=(*m_map)->m_width;
    for(int y=minHeight;y<=maxHeight;y++){
        for(int x=minWidth;x<=maxWidth;x++){
            if(!(x>=(*m_map)->m_width or y>=(*m_map)->m_height)){
                if((*m_map)->Tile(x,y).solid){
                    sf::FloatRect  theTile(x*TILEWIDTH,y*TILEHEIGHT,TILEWIDTH,TILEHEIGHT);
                    if(playerRect.Intersects(theTile)||theTile.Intersects(playerRect)){
                        CollisionHorizontal= true;
                        if(x*TILEWIDTH>=playerRect.Left&&x*TILEWIDTH<=playerRect.Left+playerRect.Width){
                            cout<<" ====Droit==";
                            droite=true;
                            solidLimit=x;
                        }
                        if((x+1)*TILEWIDTH<=playerRect.Left+playerRect.Width&&(x+1)*TILEWIDTH>=playerRect.Left){
                            cout<<" ====Gauche==";
                            gauche=true;
                            solidLimit=x;
                        }
                    }
                }
            }
        }
    }
    return CollisionHorizontal;
 }
void Player::SetMapObject(vector<GameObject*> *listObject){
    m_listObject=listObject;
}
void Player::Degat(int degats){
    m_hp-=degats;
 }
int Player::GetVie(){
    return m_vie;
}
bool Player::IsDead(){
    if(m_hp<=0){
        m_hp=100;
        m_vie--;
        return true;
    }
    else return false;
}
void Player::SetOnFire(){
    m_onFire=true;
 }
float Player::GetVelx(){
    return m_velx;
}
float Player::GetVely(){
    return m_vely;
}
void Player::SetVelx(float nx){
    m_velx=nx;
}
void Player::SetVely(float ny){
    m_vely=ny;
}
void Player::BottomCollision(bool is){
    m_colBot=is;
}
bool Player::GetBottomCollision() const{
    return m_colBot;
}

void Player::ResetVely(){
    m_vely=0;
}
void Player::UnlockJump(){
    m_jumpLock=false;
    m_vely=0;
}
void Player::Shoot(){
    if(m_lastShot.GetElapsedTime()/1000.f>0.4 && !m_machineGun){
        float velx=0,vely=0;
        int rotation=0;
        if(m_lookUp==HAUT ){
            if(m_moving==BOUGE){
                rotation=-45;
                vely=-141;
                velx=141;
                if(m_direction==GAUCHE){
                    rotation=45;
                    velx=-141;
                }
            }
            else{
                rotation=-90;
                vely=-200;
            }
        }
        else{
            velx=-200;
            if(m_direction==DROITE)velx=200;
        }
        m_arm->play();
//        m_listObject->push_back(new GameBullet(*m_imgManag->at(FLASHID),FLASHNBRCOLUMN,FLASHNBRLIGNE,0,false,this,velx,vely));
//        m_listObject->back()->SetPosition(GetPosition());
//        m_listObject->back()->setDelay(0.1);

        m_listObject->push_back(new GameBullet(*m_imgManag->at(FIREID),FIRENBRCOLUMN,FIRENBRLIGNE,20,true,this,velx,vely));
        m_listObject->back()->SetPosition(GetPosition());
        m_listObject->back()->setDelay(0.1);
        if(!(m_lookUp==HAUT && m_moving==IMMOBILE))m_listObject->back()->FlipX(m_direction);
        else m_listObject->back()->FlipX(false);
        m_listObject->back()->SetRotation(rotation);
        m_lastShot.Reset();
    }
    if(m_lastShot.GetElapsedTime()/1000.f>0.2 && m_machineGun){
        float velx=0,vely=0;
        if(m_lookUp==HAUT ){
            if(m_moving==BOUGE){
                velx=167;
                vely=-167;
                if(m_direction==GAUCHE){
                    velx=-167;
                }
            }
            else{
                vely=-300;
            }
        }
        else{
            velx=-300;
            if(m_direction==DROITE)velx=300;
        }

        m_listObject->push_back(new GameBullet(*m_imgManag->at(SHOTID),SHOTNBRCOLUMN,SHOTNBRLIGNE,5,false,this,velx,vely));
        m_listObject->back()->SetPosition(GetPosition());
        m_listObject->back()->setDelay(0.04);
        m_listObject->back()->loop(true);
        m_lastShot.Reset();
    }
}

    void Player::drawing(sf::RenderWindow* app){
        if(m_hp>0){
            m_hpBarre.SetPosition(GetPosition().x-3,GetPosition().y-13);
            m_hpBarre.setAnimRow(10-floor(m_hp/10));
            app->Draw(m_hpBarre);
        }
        m_vieBarre.SetPosition(GetPosition().x-3+(-4*(STARTVIE-3)),GetPosition().y-7);
        m_vieBarre.setAnimRow(6-m_vie);
        app->Draw(m_vieBarre);
//        if(m_lastShot.GetElapsedTime()<0.2 && m_arm->animRow()<2){
//            if(m_direction==GAUCHE)m_arm->setAnimRow(3);
//            else m_arm->setAnimRow(2);
//        }
        m_arm->SetPosition(GetPosition());
        if(!m_machineGun)app->Draw(*m_arm);

    }
    void Player::Pause(){
        m_lastShot.Pause();
    }
    void Player::Resume(){
        m_lastShot.Play();
    }
