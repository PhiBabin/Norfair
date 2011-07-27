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

#include "includes.hpp"

/**
    Chargement de la configuration
**/
void loadConfig(){
    TiXmlDocument doc("config/config.xml");
    doc.LoadFile();

    TiXmlHandle hDoc(&doc);
    TiXmlHandle hRoot(0);
    TiXmlElement* pElem;

    pElem=hDoc.FirstChild("img").FirstChild().Element();
    for(; pElem; pElem=pElem->NextSiblingElement()){
        imgAnim newAnim;
        sf::Image newImg;
        newImg.LoadFromFile(pElem->Attribute("path"));
        newAnim.img=newImg;
        newAnim.nbrCollum=atoi(pElem->Attribute("nbrCollums"));
        newAnim.nbrLine=atoi(pElem->Attribute("nbrLines"));
        g_imgManag[pElem->Attribute("name")]=newAnim;
    }
    pElem=hDoc.FirstChild("sound").FirstChild().Element();
    for(; pElem; pElem=pElem->NextSiblingElement()){
        sf::SoundBuffer newSound;
        newSound.LoadFromFile(pElem->Attribute("path"));
        g_soundManag[pElem->Attribute("name")]=newSound;
    }
    pElem=hDoc.FirstChild("config").FirstChild().Element();
    for(; pElem; pElem=pElem->NextSiblingElement()){
        g_config[pElem->Attribute("name")]=atoi(pElem->Attribute("value"));
    }
}

int main(){
   cout<<"  /App Start"<<endl;

   cout<<"  /App Load Configuration"<<endl;

   loadConfig();

    sf::RenderWindow App(sf::VideoMode(g_config["screenwidth"], g_config["screenheight"], 32), "Norfair", sf::Style::Close | sf::Style::Titlebar );

    App.EnableVerticalSync(true);

   cout<<"  /GameEngine   Start"<<endl;
    GameEngine *Game(0);
    Game=new GameEngine(App);
    delete Game;

}
