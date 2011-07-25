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
Player::Player(sf::Image &img, map<string,imgAnim> *imgManag, vector<sf::SoundBuffer*> *soundManag, MapTile **map,bool machineGun=false):
 ImgAnim::ImgAnim(img,3,4),m_colBot(false),m_velx(0),m_vely(0),m_hp(100),m_vie(3),m_shield(false),m_onFire(false)
 ,m_imgManag(imgManag) ,m_soundManag(soundManag),m_machineGun(machineGun)
 ,m_hpBarre((*imgManag)["hp"].img,HPNBRCOLUMN,HPNBRLIGNE)
 ,m_vieBarre((*imgManag)["vie"].img,VIENBRCOLUMN,VIENBRLIGNE)
 ,m_blueShield((*imgManag)["shield"].img,SHIENBRCOLUMN,SHIENBRLIGNE)
,m_map(map){
    setDelay(0.2);
     if(!machineGun)m_arm=new ImgAnim((*m_imgManag)["marm"].img,MARMMNBRCOLUMN,MARMMNBRLIGNE);
     else m_arm=new ImgAnim((*m_imgManag)["sarm"].img,SARMMNBRCOLUMN,SARMMNBRLIGNE);
    m_arm->setDelay(0.2);

    m_jumpSound.SetBuffer(*m_soundManag->at(JUMPID));
    m_hurtSound.SetBuffer(*m_soundManag->at(HURID));
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
        m_vely+=GRAVITY/1000.f*app.GetFrameTime();
}
void Player::Jump(){
    if(!m_jumpLock){
        m_jumpSound.Play();
        m_jumpLock=true;
        m_vely+=-300;
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
        if(!m_machineGun){
            m_arm->setAnimRow(1);
            m_arm->play();
        }
        play();
        m_velx=-150;
    }
    else if(!left&&right){
        m_moving=true;
        m_direction=DROITE;
        if(m_colBot)setAnimRow(0);
        else setAnimRow(2);
        play();
        if(!m_machineGun){
            m_arm->setAnimRow(0);
            m_arm->play();
        }
        m_velx=150;
    }
    else{
        m_moving=false;
        if(m_colBot&& m_direction==GAUCHE)setAnimRow(1);
        else if(m_colBot&& m_direction==DROITE)setAnimRow(0);
        else if(animRow()<2) setAnimRow(animRow()+2);
        else setAnimRow(animRow());
        stop();
        if(!m_machineGun)m_arm->stop();
        m_velx*=0.8;
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
            if(!(x>=(*m_map)->m_width or y>=(*m_map)->m_height)&&(*m_map)->Tile(x,y).solid){
                sf::FloatRect  theTile(x*TILEWIDTH,y*TILEHEIGHT,TILEWIDTH,TILEHEIGHT);
                if(playerRect.Intersects(theTile)||theTile.Intersects(playerRect)){
                    CollisionHorizontal= true;
                    if(x*TILEWIDTH>=playerRect.Left&&x*TILEWIDTH<=playerRect.Left+playerRect.Width){
                        droite=true;
                        solidLimit=x;
                    }
                    if((x+1)*TILEWIDTH<=playerRect.Left+playerRect.Width&&(x+1)*TILEWIDTH>=playerRect.Left){
                        gauche=true;
                        solidLimit=x;
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
void Player::AddLife(){
    if(m_vie<6)m_vie++;
}
void Player::RaiseShield(){
    m_shield=true;
    m_shieldCoolDown.Reset();
}
void Player::GodInvocation(){

    m_listObject->push_back(new GameAnim((*m_imgManag)["god"].img,GODNBRCOLUMN,GODNBRLIGNE));
    m_listObject->back()->setDelay(0.3);
    m_listObject->back()->SetPosition((*m_map)->oppositePlayer(this)->GetPosition().x-7,0);

    m_listObject->push_back(new GameAnim((*m_imgManag)["explosion2"].img,EXP2NBRCOLUMN,EXP2NBRLIGNE));
    m_listObject->back()->SetPosition((*m_map)->oppositePlayer(this)->GetPosition());
    m_listObject->back()->setDelay(0.3);
    m_listObject->push_back(new GameAnim((*m_imgManag)["explosion2"].img,EXP2NBRCOLUMN,EXP2NBRLIGNE));
    m_listObject->back()->SetPosition((*m_map)->oppositePlayer(this)->GetPosition());
    m_listObject->back()->Move(-3,-5);
    m_listObject->back()->setDelay(0.4);
    m_listObject->push_back(new GameAnim((*m_imgManag)["explosion2"].img,EXP2NBRCOLUMN,EXP2NBRLIGNE));
    m_listObject->back()->SetPosition((*m_map)->oppositePlayer(this)->GetPosition());
    m_listObject->back()->Move(5,-4);
    m_listObject->back()->setDelay(0.5);

    (*m_map)->oppositePlayer(this)->Degat(200);
}
void Player::Degat(int degats){
    if(!m_shield){
        m_hp-=degats;
        m_hurtSound.Play();
    }
}
int Player::GetVie(){
    return m_vie;
}
bool Player::IsDead(){
    if(m_hp<=0){
        m_hp=100;
        m_vie--;
        m_onFire=false;
        return true;
    }
    else return false;
}
void Player::SetOnFire(){
    if(!m_shield){
        m_onFire=true;
        m_burning.Reset();
        m_hurt.Reset();
    }
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

void Player::ResetVelx(){
    m_velx=0;
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

        m_listObject->push_back(new GameBullet((*m_imgManag)["fire"].img,FIRENBRCOLUMN,FIRENBRLIGNE,10,true,this,velx,vely));
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
            m_arm->play();
            m_listObject->push_back(new GameBullet((*m_imgManag)["shot"].img,SHOTNBRCOLUMN,SHOTNBRLIGNE,5,false,this,velx,vely));
            m_listObject->back()->SetPosition(GetPosition());
            m_listObject->back()->Move(0,4);
            m_listObject->back()->setDelay(0.04);
            m_listObject->back()->loop(true);
            m_lastShot.Reset();
    }
}

void Player::drawing(sf::RenderWindow* app){
    m_arm->SetPosition(GetPosition());
    if(m_machineGun){
        if(m_lastShot.GetElapsedTime()/1000<0.2){
            m_arm->play();
        }
        else{
            m_arm->stop();
        }

        if(m_direction==GAUCHE){
            m_arm->FlipX(true);
            m_arm->Move(-5,0);
        }
        else m_arm->FlipX(false);
    }
    app->Draw(*m_arm);

    if(m_burning.GetElapsedTime()>5000)m_onFire=false;

    if(m_shieldCoolDown.GetElapsedTime()/1000>15)m_shield=false;
    if(m_shield){
        m_blueShield.SetPosition(GetPosition());
        if(m_machineGun)m_blueShield.Move(-9,-7);
        else m_blueShield.Move(-7,-7);
        app->Draw(m_blueShield);
    }

    if(m_onFire){
        if(m_hurt.GetElapsedTime()>1000){
            m_hurt.Reset();
            Degat(5);
        }
        m_listObject->push_back(new GameAnim((*m_imgManag)["explosion3"].img,4,1));
        m_listObject->back()->SetPosition(GetPosition().x+1.f +rand() *-4.f /RAND_MAX + 3.f,GetPosition().y+3.f+rand() *-8.f /RAND_MAX + 8.f);
        m_listObject->back()->setDelay(0.1);
    }


    if(m_hp>0){
        m_hpBarre.SetPosition(GetPosition().x-3,GetPosition().y-13);
        m_hpBarre.setAnimRow(10-floor(m_hp/10));
        app->Draw(m_hpBarre);
    }
    if(m_vie<=STARTVIE)m_vieBarre.SetPosition(GetPosition().x-3+(-4*(STARTVIE-3)),GetPosition().y-7);
    else m_vieBarre.SetPosition(GetPosition().x-3+(-4*(m_vie-3)),GetPosition().y-7);
    m_vieBarre.setAnimRow(6-m_vie);
    app->Draw(m_vieBarre);
}
void Player::Pause(){
    m_lastShot.Pause();
    m_shieldCoolDown.Pause();
    m_burning.Pause();
    m_hurt.Pause();
}
void Player::Resume(){
    m_lastShot.Play();
    m_shieldCoolDown.Play();
    m_burning.Play();
    m_hurt.Play();
}
