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
Player::Player(sf::Image &img, vector<sf::Image*> *imgManag,MapTile **map,bool machineGun=false,bool fireBall=false):
 ImgAnim::ImgAnim(img,3,4),m_colBot(false),m_velx(0),m_vely(0),m_vie(100),m_live(3)
 ,m_imgManag(imgManag),m_machineGun(machineGun),m_fireBall(fireBall)
 ,m_lifeBarre(*imgManag->at(VIEID),VIENBRCOLUMN,VIENBRLIGNE)
 ,m_vieBarre(*imgManag->at(LIFEID),LIFENBRCOLUMN,LIFENBRLIGNE)
 ,m_map(map){
    setDelay(0.2);
     if(fireBall)m_arm=new ImgAnim(*imgManag->at(ARMMID),ARMMNBRCOLUMN,ARMMNBRLIGNE);
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

//! Reposition le player pour une collision sur le sol
void Player::ResolveUp(float ry){
    if(m_vely>0) m_vely=0;
    m_colBot=false;
    m_jumpLock=false;
    SetPosition(GetPosition().x,ry*TILEHEIGHT-PLAYERCOLLISIONHEIGHT);
}
void Player::ResolveDown(float ry){
    if(m_vely<0) m_vely=0;
    SetPosition(GetPosition().x,(ry+1)*TILEHEIGHT);
}
void Player::ResolveLeft(float rx){
    if(m_velx>0) m_velx=0;
    SetPosition(rx*TILEWIDTH-PLAYERCOLLISIONWIDTH,GetPosition().y);
}
void Player::ResolveRight(float rx){
    if(m_velx<0) m_velx=0;
    SetPosition((rx+1)*TILEWIDTH,GetPosition().y);
}
void Player::mapCollision(sf::RenderWindow* app){
    int T,L,B,R;
    bool TL,TR,BL,BR;
    m_colBot=true;
    m_jumpLock=true;

    m_vely+=GRAVITY/1000.f*app->GetFrameTime();
    float movHor=m_velx/1000.f*app->GetFrameTime();
    float movVer=m_vely/1000.f*app->GetFrameTime();
    //cout<<"frame="<<app->GetFrameTime()/1000.f<<" vely="<<m_vely<<" movey="<<movVer<<endl;
    sf::FloatRect playerRect=GetMovedPlayerRect(movHor,movVer);
    Move(movHor,movVer);
    T=playerRect.Top/TILEHEIGHT;
    L=playerRect.Left/TILEWIDTH;
    B=(playerRect.Top+playerRect.Height-1)/TILEHEIGHT;
    R=(playerRect.Left+playerRect.Width-1)/TILEWIDTH;

    if(L<0)L=0;
    if(R>(*m_map)->m_width)R=(*m_map)->m_width;
    if(T<0)T=0;
    if(B>(*m_map)->m_height)B=(*m_map)->m_height;

    TL=(*m_map)->collisionTile(L,T);
    TR=(*m_map)->collisionTile(R,T);
    BL=(*m_map)->collisionTile(L,B);
    BR=(*m_map)->collisionTile(R,B);

    if(!BL && !BR && !TL && !TR){
        return;
    }
    else if(BL && BR && TL && TR){
        ResolveUp(B);
    }
    else if(TL&&TR&&BR){
        ResolveDown(T);
        ResolveLeft(R);
    }
    else if(TL&&TR&&BL){
        ResolveDown(T);
        ResolveRight(L);
    }
    else if(BL&&BR&&TR){
        ResolveUp(B);
        ResolveLeft(R);
    }
    else if(BL&&BR&&TL){
        ResolveUp(B);
        ResolveRight(L);
    }
    else if(BL&&BR){
        ResolveUp(B);
    }
    else if(TL&&TR){
        ResolveDown(T);
    }
    else if(BL&&TL){
        ResolveRight(L);
    }
    else if(BR&&TR){
        ResolveLeft(R);
    }
    else if (TR){
        float xoff = PLAYERCOLLISIONWIDTH+GetPosition().x-(R)*TILEWIDTH;
//        float yoff = (T)*TILEWIDTH-GetPosition().y;
        float yoff = (T-1)*TILEWIDTH-GetPosition().y;
        if(xoff>yoff){
            ResolveDown(T);
            cout<<xoff<<" "<<yoff<<endl;
        }
        else{
            ResolveLeft(R);
            cout<<xoff<<" "<<yoff<<endl;
        }
    }
    else if (TL){
        float xoff = (L+1)*TILEWIDTH-GetPosition().x;
        float yoff = (T-1)*TILEWIDTH-GetPosition().y;
        if(xoff>yoff){
            ResolveDown(T);
            cout<<xoff<<" "<<yoff<<endl;
        }
        else{
            ResolveRight(L);
            cout<<xoff<<" "<<yoff<<endl;
        }
    }
    else if (BR){
//        float xoff = (R-1)*TILEWIDTH-PLAYERCOLLISIONWIDTH-GetPosition().x;
        float xoff = PLAYERCOLLISIONWIDTH+GetPosition().x-(R)*TILEWIDTH;
        float yoff = (GetPosition().y+PLAYERCOLLISIONHEIGHT)-B*TILEHEIGHT;
        if(xoff>yoff){
            ResolveUp(B);
        }
        else{
            ResolveLeft(R);
        }
    }
    else if (BL){
        float xoff = (L+1)*TILEWIDTH-GetPosition().x;
        float yoff = (GetPosition().y+PLAYERCOLLISIONHEIGHT)-B*TILEHEIGHT;
        if(xoff>yoff){
            ResolveUp(B);
        }
        else{
            ResolveRight(L);
        }
    }

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
		//if(m_arm->animRow()<2)m_arm->stop();
		m_arm->stop();
        m_velx=0;
    }
}
void Player::SetMapObject(vector<GameObject*> *listObject){
    m_listObject=listObject;
}
void Player::Degat(int degats){
    m_vie-=degats;
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
    if(m_lastShot.GetElapsedTime()/1000.f>0.5 && m_fireBall){
        float velx=0,vely=0;
        int row=0;
        if(m_lookUp==HAUT ){
            if(m_moving==BOUGE){
                row=2;
                velx=141.42;
                vely=-141.42;
                if(m_direction==GAUCHE){
                    row=3;
                    velx=-141.42;
                }
            }
            else{
                row=4;
                vely=-200;
            }
        }
        else{
            velx=-200;
            if(m_direction==DROITE)velx=200;
            else row=1;
        }
        //m_arm->setAnimRow(2);
        m_arm->play();
        m_listObject->push_back(new GameBullet(*m_imgManag->at(FIREID),FIRENBRCOLUMN,FIRENBRLIGNE,20,true,this,velx,vely));
        m_listObject->back()->SetPosition(GetPosition());
        m_listObject->back()->setDelay(0.1);
        m_listObject->back()->setAnimRow(row);
        m_lastShot.Reset();
    }
    if(m_lastShot.GetElapsedTime()/1000.f>0.2 && m_machineGun){
        float velx=0,vely=0;
        if(m_lookUp==HAUT ){
            if(m_moving==BOUGE){
                velx=200;
                vely=-200;
                if(m_direction==GAUCHE){
                    velx=-200;
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
        if(m_vie>0){
            m_lifeBarre.SetPosition(GetPosition().x-3,GetPosition().y-13);
            m_lifeBarre.setAnimRow(10-floor(m_vie/10));
            app->Draw(m_lifeBarre);
        }
        m_vieBarre.SetPosition(GetPosition().x-3+(-4*(STARTLIVE-3)),GetPosition().y-7);
        m_vieBarre.setAnimRow(6-m_live);
        app->Draw(m_vieBarre);
//        if(m_lastShot.GetElapsedTime()<0.2 && m_arm->animRow()<2){
//            if(m_direction==GAUCHE)m_arm->setAnimRow(3);
//            else m_arm->setAnimRow(2);
//        }
        m_arm->SetPosition(GetPosition());
        if(!m_machineGun)app->Draw(*m_arm);
        //app->Draw(m_imgArm);

    }
