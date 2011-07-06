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
#ifndef LAYER_H
#define LAYER_H


typedef std::vector<sf::Drawable*> FrameSet;
typedef FrameSet::const_iterator itFrame;

/*
*	Petite classe simple qui gère le système de couche de drawable.
*	Elle a la même utilisation que std::vector, l'élément à l'indice 0 est le premier affiché.
*/
class Layer :
	public sf::Drawable, public FrameSet
{
 public :
	//!Même constructeur que sf::Drawable
	Layer(const sf::Vector2f& Position = sf::Vector2f(0, 0), const sf::Vector2f& Scale = sf::Vector2f(1, 1), float Rotation = 0.f, const sf::Color& Col = sf::Color(255, 255, 255, 255));

	virtual ~Layer();
protected :
	virtual void Render(sf::RenderTarget& Target) const;
};

#endif


