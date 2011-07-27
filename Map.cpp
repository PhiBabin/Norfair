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

#include "Map.hpp"
MapTile::MapTile():m_app(NULL),m_playerOne(NULL),m_playerTwo(NULL){}
MapTile::MapTile(sf::RenderWindow *App, Player *playerOne, Player *playerTwo):
m_width(0),m_height(0),m_app(App),m_playerOne(playerOne),m_playerTwo(playerTwo){


    loadMap();
}

 bool MapTile::collisionTile(float x, float y){
    return m_tileSet.at(x).at(y).solid;
 }

Type MapTile::Tile(float x, float y){
    return m_tileSet.at(x).at(y);
 }

 vector<GameObject*> * MapTile::getMapObject(){
    return &m_mapObject;
 }

 vector<GameItems*> * MapTile::getMapItem(){
    return &m_mapItems;
 }

 bool MapTile::collisionGeneral(const sf::FloatRect playerRect){
    int maxHeight, minHeight, maxWidth, minWidth;
    minHeight=playerRect.Top/g_config["tileheight"];
    minWidth=playerRect.Left/g_config["tilewidth"];
    maxHeight=(playerRect.Top+playerRect.Height-1)/g_config["tileheight"];
    maxWidth=(playerRect.Left+playerRect.Width-1)/g_config["tilewidth"];

    if(minHeight<0)minHeight=0;
    if(maxHeight>m_height)maxHeight=m_height;
    if(minWidth<0)minWidth=0;
    if(maxWidth>m_width)maxWidth=m_width;
    for(int y=minHeight;y<=maxHeight;y++){
        for(int x=minWidth;x<=maxWidth;x++){
            if(!(x>=m_width or y>=m_height)){
                if(m_tileSet[x][y].solid){
                    sf::FloatRect  theTile(x*g_config["tilewidth"],y*g_config["tileheight"],g_config["tilewidth"],g_config["tileheight"]);
                    if(playerRect.Intersects(theTile)||theTile.Intersects(playerRect)) return true;
                }
            }
        }
    }
    return false;
 }

 Player* MapTile::oppositePlayer(Player *player){
        if(player==m_playerOne)return m_playerTwo;
        else return m_playerOne;
}
void MapTile::draw(){
    cout<<"FPS="<</*1.f/(m_app->GetFrameTime())*1000<<*/"Joueur 1 x="<<m_playerOne->GetPosition().x<<" y="<<m_playerOne->GetPosition().y<<" vely="<<m_playerOne->GetVely()<<" velx="<<m_playerOne->GetVelx()<<endl;
    //! On affiche les tiles
    m_app->Draw(sf::Sprite(m_background.GetImage()));
    m_app->Draw(sf::Sprite(m_map.GetImage()));
    //! On affiche le personnage et ces éléments
    m_app->Draw(*m_playerOne);
    m_playerOne->drawing(m_app);
    m_app->Draw(*m_playerTwo);
    m_playerTwo->drawing(m_app);
    //! On affiche les objets de la carte
    for(unsigned int i=0;i<m_mapObject.size();i++){
        if((m_mapObject.at(i))->isDelete()){
            delete m_mapObject.at(i);
            m_mapObject.erase( m_mapObject.begin() + i );
        }
        else m_app->Draw(*(m_mapObject.at(i)));
    }
    //! On affiche les items
    for(unsigned int i=0;i<m_mapItems.size();i++){
        if((m_mapItems.at(i))->isDraw()){
            m_app->Draw(*(m_mapItems.at(i)));
        }
    }
}
vector<Type> & MapTile::operator [] (int X){
    return m_tileSet.at(X);
}
 unsigned char MapTile::findType(sf::Color Pix){
        for(unsigned char it=0;it<m_typeList.size();it++){
            if(m_typeList[it].colorPix==Pix) return it;
        }
        cerr<<"[Fatal Error]Impossible de trouver un type correspondant."<<endl;
        exit(0);
        return 0;
 }
void MapTile::loadMap(){
    //! On charge le niveau
     stringstream ss;
     ss<<g_config["level"];
    string pathConfig="map/level"+ ss.str()+".xml";
    TiXmlDocument doc(pathConfig.c_str());
    doc.LoadFile();

    TiXmlHandle hDoc(&doc);
    TiXmlHandle hRoot(0);
    TiXmlElement* pElem;

    map<string,string> levelConfig;

    pElem=hDoc.FirstChild("map").FirstChild().Element();
    for(; pElem; pElem=pElem->NextSiblingElement()){
        levelConfig[pElem->Attribute("name")]=string(pElem->Attribute("value"));
    }
    //! Initiation des images temporaire
    sf::Image tilesetImg,backImg ,image_schemaImg;
    tilesetImg.LoadFromFile(levelConfig["mappath"]);
    backImg.LoadFromFile(levelConfig["backpath"]);
    //! On supprime les vectors
	m_typeList.erase(m_typeList.begin(),m_typeList.end());
	m_tileSet.erase(m_tileSet.begin(),m_tileSet.end());
    image_schemaImg.LoadFromFile(levelConfig["corrpath"]);
    //! Initiation des images des tiles
    m_ImgTypeTile.LoadFromFile(levelConfig["tilepath"]);
    m_ImgTypeTile.SetSmooth(false);
    m_width=tilesetImg.GetWidth();
    m_height=tilesetImg.GetHeight();
    //! On crée un vector de tile et on les fait corresponds à un pixel
    for(unsigned int it2=0;it2<image_schemaImg.GetHeight();it2++){
        for(unsigned int it=0;it<image_schemaImg.GetWidth();it++){
            Type newTile;
            newTile.colorPix = image_schemaImg.GetPixel(it, it2);
            newTile.zoneRect=sf::IntRect(it*g_config["tilewidth"], it2*g_config["tileheight"], g_config["tilewidth"], g_config["tileheight"]);
            if(image_schemaImg.GetPixel(it, it2)!=sf::Color(42,42,42))m_typeList.insert(m_typeList.end(),newTile);
        }
    }
    //! On charge le fichier des propriétés de la map
    FILE* tilePropFile = NULL;
	tilePropFile = fopen(levelConfig["proppath"].c_str(), "r");
	if(tilePropFile==NULL){ cerr<<"[FATAL ERROR] Map not found."<<endl; exit(1);}

	int nbrItems,itemX,itemY,Visible,Solid,Spawn,Killer,typeSpawn1,typeSpawn2;

	//! On charge crée les items
	fscanf(tilePropFile, "%d",&nbrItems);
	for(int it=0;it<nbrItems;it++){
        fscanf(tilePropFile, "%d %d",&itemX,&itemY);
	    m_mapItems.push_back(new GameItems((g_imgManag)["item"].img,(g_imgManag)["item"].nbrCollum,(g_imgManag)["item"].nbrLine));
	    m_mapItems.back()->SetPosition(itemX*g_config["tileheight"],itemY*g_config["tilewidth"]);
	    m_mapItems.back()->setDelay(0.2);
	}
	    //! On charge les propriétés
	for(unsigned int it=0;it<m_typeList.size();it++){
        fscanf(tilePropFile, "%d  %d %d %d",&Visible,&Solid,&Spawn,&Killer);
        if(Spawn==1)typeSpawn1=it;
        if(Spawn==2)typeSpawn2=it;

        if(Visible==1)m_typeList[it].visible=true;
        else m_typeList[it].visible=false;

        if(Killer==1)m_typeList[it].kill=true;
        else m_typeList[it].kill=false;

        if(Solid==1)m_typeList[it].solid=true;
        else m_typeList[it].solid=false;
	}
	//! Charge le niveau
    m_map.Create(m_width*g_config["tilewidth"],m_height*g_config["tileheight"]);
	int theTile;
    for(int it=0;it<m_width;it++){
        vector<Type> tileList2;
        m_tileSet.insert(m_tileSet.end(),tileList2);
        for(int it2=0;it2< m_height;it2++){
            theTile=findType(tilesetImg.GetPixel(it, it2));
            if(theTile==typeSpawn1){
                sf::Vector2f spawnLocationOne(it*g_config["tilewidth"] ,(it2+1)*g_config["tileheight"]-g_config["playercollheight"]);
                m_spawnLocationOne=spawnLocationOne;
                m_playerOne->SetPosition(m_spawnLocationOne);
            }
            else if(theTile==typeSpawn2){
                sf::Vector2f spawnLocationTwo(it*g_config["tilewidth"] ,(it2+1)*g_config["tileheight"]-g_config["playercollheight"]);
                m_spawnLocationTwo=spawnLocationTwo;
                m_playerTwo->SetPosition(m_spawnLocationTwo);
            }
            Type theNewTile= m_typeList[theTile];
            theNewTile.tile.SetPosition(it*g_config["tilewidth"],it2*g_config["tileheight"]);
            theNewTile.tile.SetImage(m_ImgTypeTile);
            theNewTile.tile.SetSubRect(m_typeList[theTile].zoneRect);
            m_tileSet[it].insert( m_tileSet[it].end(),theNewTile);

            if(theNewTile.visible)m_map.Draw(theNewTile.tile);
        }
    }
    m_map.Display();
    //! Chargement du background
    m_background.Create(m_width*g_config["tilewidth"],m_height*g_config["tileheight"]);
    for(int it=0;it<m_width;it++){
        for(int it2=0;it2< m_height;it2++){
            theTile=findType(backImg.GetPixel(it, it2));
            Type theNewTile= m_typeList[theTile];
            theNewTile.tile.SetPosition(it*g_config["tilewidth"],it2*g_config["tileheight"]);
            theNewTile.tile.SetImage(m_ImgTypeTile);
            theNewTile.tile.SetSubRect(m_typeList[theTile].zoneRect);
            if(theNewTile.visible)m_background.Draw(theNewTile.tile);
        }
    }
    m_background.Display();
}
MapTile::~MapTile(){
    for(unsigned int i=0;i<m_mapObject.size();i++){
        delete m_mapObject.at(i);
    }
    for(unsigned int i=0;i<m_mapItems.size();i++){
        delete m_mapItems.at(i);
    }
}
