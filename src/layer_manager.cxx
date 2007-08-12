//  $Id: layer_manager.cxx,v 1.8 2003/12/14 00:30:04 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <iostream>
#include <ClanLib/Display/sprite.h>
#include <ClanLib/Display/sprite_description.h>
#include "layer_manager.hxx"

namespace Pingus {

LayerManager::LayerManager ()
{
}

LayerManager::~LayerManager()
{
}

void
LayerManager::add_layer (const CL_PixelBuffer& sur, float x_o, float y_o, float x_u, float y_u)
{
	CL_SpriteDescription desc;
	desc.add_frame(sur);
  layers.push_back (Layer(CL_Sprite(desc), x_o, y_o, x_u, y_u));
}

void
LayerManager::draw (DrawingContext& gc)
{
  for (std::vector<Layer>::iterator i = layers.begin ();
       i != layers.end (); ++i)
    i->draw(gc);
}

void
LayerManager::update (float delta)
{
  for (std::vector<Layer>::iterator i = layers.begin ();
       i != layers.end (); ++i)
    i->update(delta);
}

} // namespace Pingus

/* EOF */