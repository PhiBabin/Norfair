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

#ifndef INCLUDES_HPP_INCLUDED
#define INCLUDES_HPP_INCLUDED

/**
    Configuration
*/

//! Configuration de l'écran
#define SCREENWIDTH 800.f //Px width of the screen
#define SCREENHEIGHT 600.f //Px height of the screen

//! Configuration d'une map
#define TILEWIDTH 16 //Px width a tile
#define TILEHEIGHT 15  //Px height a tile
#define TILESETWIDTH 10 //Number of tile in a tile set image
#define TILESETHEIGHT 9 //Number of tile in a tile set image
#define FRAME 0.1 //Frame time

//! Constantes
#define GRAVITY 350.f //Gravity force
#define GAUCHE true
#define DROITE false
#define HAUT true
#define BAS false
#define BOUGE true
#define IMMOBILE false

//! Collision d'un personnage
#define PLAYERCOLLISIONWIDTH 16 //16
#define PLAYERCOLLISIONHEIGHT 18 //18

//! Carte
#define MAPPATH "levelArenaLarg.png" //Chemin vers la carte
//! Personnage
#define MAGOID 1 // ID de ce sprite
#define MAGOPATH "sprite_mago4.png" //Chemin vers le sprite du personnage
#define MAGONBRCOLUMN 3 //Nombre de collone du sprite du personnage
#define MAGONBRLIGNE 4 //Nombre de ligne du sprite du personnage

#define SQUELID 2 // ID de ce sprite
#define SQUELPATH "sprite_squel.png" //Chemin vers le sprite du personnage
#define SQUELNBRCOLUMN 3 //Nombre de collone du sprite du personnage
#define SQUELNBRLIGNE 4 //Nombre de ligne du sprite du personnage
//! Bras
#define ARMMID 6 // ID de ce sprite
#define ARMMPATH "arm_mago2.png" //Chemin vers  le sprite
#define ARMMNBRCOLUMN  3 //Nombre de colone du sprite
#define ARMMNBRLIGNE  2 //Nombre de ligne du sprite
//! Barre de vie
#define VIEID 3 // ID de ce sprite
#define VIEPATH "barre_vie2.png" //Chemin vers  le sprite
#define VIENBRCOLUMN  1 //Nombre de colone du sprite
#define VIENBRLIGNE  11 //Nombre de ligne du sprite
#define LIFEID 4 // ID de ce sprite
#define LIFEPATH "images/live.png" //Chemin vers  le sprite
#define LIFENBRCOLUMN  1 //Nombre de colone du sprite
#define LIFENBRLIGNE  7 //Nombre de ligne du sprite

#define STARTLIVE  3 //Nombre de vie qu'a le joueur au début
//! Arme
#define FIREID 5 // ID de ce sprite
#define FIREPATH "fireball2.png" //Chemin vers  le sprite
#define FIRENBRCOLUMN 6 //Nombre de colone du sprite
#define FIRENBRLIGNE 5 //Nombre de ligne du sprite

#define SHOTID 10 // ID de ce sprite
#define SHOTPATH "shot2.png" //Chemin vers  le sprite
#define SHOTNBRCOLUMN 16 //Nombre de colone du sprite
#define SHOTNBRLIGNE 1 //Nombre de ligne du sprite
//! Explosion & cie
#define EXPID 7 // ID de ce sprite
#define EXPPATH "explosion.png" //Chemin vers  l'explosion
#define EXPNBRCOLUMN 6 //Nombre de colone de l'explosion
#define EXPNBRLIGNE 3 //Nombre de ligne de l'explosion
#define EXP2ID 8 // ID de ce sprite
#define EXP2PATH "explosion2.png" //Chemin vers l'explosion
#define EXP2NBRCOLUMN 3 //Nombre de colone de l'explosion
#define EXP2NBRLIGNE 1 //Nombre de ligne de l'explosion
#define EXP3ID 9 // ID de ce sprite
#define EXP3PATH "fire2.png" //Chemin vers l'explosion
#define EXP3NBRCOLUMN  //Nombre de colone de l'explosion
#define EXP3NBRLIGNE  //Nombre de ligne de l'explosion


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



sf::Clock Clock;
using namespace std;
#include "LayerAnim.cpp"
#include "ImgAnim.cpp"

#include "GameObject.hpp"
#include "GameAnim.hpp"
#include "GameBullet.hpp"
#include "GameItems.hpp"

#include "Player.hpp"
#include "Map.hpp"

#include "GameObject.cpp"
#include "GameAnim.cpp"
#include "GameBullet.cpp"
#include "GameItems.cpp"

#include "Player.cpp"
#include "Map.cpp"

#include "GameState.cpp"
#include "PlayState.cpp"
#include "GameEngine.cpp"

#endif // INCLUDES_HPP_INCLUDED
