//  $Id: woodthing.hxx,v 1.5 2003/10/20 13:11:09 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_WORLDOBJS_ENTRANCES_WOODTHING_HXX
#define HEADER_PINGUS_WORLDOBJS_ENTRANCES_WOODTHING_HXX

#include "entrance.hxx"

namespace Pingus {
namespace WorldObjs {
// FIXME: Re-enable this namespace.
//namespace Entrances {

class WoodThing : public Entrance
{
private:
  CL_Sprite   surface2;

public:
  WoodThing(const FileReader& reader);

  void update();
  void draw (SceneContext& gc);

private:
  WoodThing (const WoodThing&);
  WoodThing& operator= (const WoodThing&);
};

//} // namespace Entrances
} // namespace WorldObjs
} // namespace Pingus

#endif

/* EOF */