//  $Id: pingu_collider.cxx,v 1.4 2003/10/18 23:17:27 grumbel Exp $
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

#include "../pingu_action.hxx"
#include "../groundtype.hxx"
#include "../vector.hxx"
#include "pingu_collider.hxx"

namespace Pingus {
namespace Colliders {

PinguCollider::PinguCollider(const int height_arg) : height(height_arg)
{
}

PinguCollider::~PinguCollider()
{
}

bool PinguCollider::operator() (World* const world, Vector current_pos,
				  const Vector& step_vector) const
{
  Vector new_pos = current_pos + step_vector;
  int pixel;
  bool falling = false;
  bool collided = false;

  if (step_vector.y > 0.0f)
    falling = true;

  // If the Pingu is going to move sideways to the next pixel...
  if (static_cast<int>(new_pos.x) != static_cast<int>(current_pos.x))
    {
      float top_of_pingu = new_pos.y - height;

      for (; new_pos.y >= top_of_pingu; --new_pos.y)
	{
	  pixel = getpixel(world, new_pos);

	  // If there is something in the way, then Pingu has collided with
	  // something.  However, if not falling and colliding with a
	  // Bridge, allow Pingu to go through it.
	  if ((!falling || pixel != Groundtype::GP_BRIDGE)
	      && pixel != Groundtype::GP_NOTHING)
	    {
	      collided = true;
	      break;
	    }
	}
    }
  // If the Pingu is not falling...
  else if (!falling)
    {
      pixel = getpixel(world, Vector(new_pos.x, new_pos.y - height));

      // If the top of the Pingu has hit something except a bridge...
      if (pixel != Groundtype::GP_NOTHING && pixel != Groundtype::GP_BRIDGE)
	{
	  collided = true;
	}
    }
  // If the Pingu's "feet" has hit something...
  else if (getpixel(world, new_pos) != Groundtype::GP_NOTHING)
    {
      collided = true;
    }

  return collided;
}

} // namespace Colliders
} // namespace Pingus

/* EOF */