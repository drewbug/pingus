/*  $Id$
**   __      __ __             ___        __   __ __   __
**  /  \    /  \__| ____    __| _/_______/  |_|__|  | |  |   ____
**  \   \/\/   /  |/    \  / __ |/  ___/\   __\  |  | |  | _/ __ \
**   \        /|  |   |  \/ /_/ |\___ \  |  | |  |  |_|  |_\  ___/
**    \__/\  / |__|___|  /\____ /____  > |__| |__|____/____/\___  >
**         \/          \/      \/    \/                         \/
**  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
** 
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
**  02111-1307, USA.
*/

#include <iostream>
#include "group_component.hpp"

namespace GUI {

GroupComponent::GroupComponent(const Rect& rect, bool clip)
  : RectComponent(rect),
    drawing_context(rect, clip),
    mouse_over_comp(0),
    focused_comp(0),
    primary_pressed_comp(0),
    secondary_pressed_comp(0)
{
}

GroupComponent::~GroupComponent()
{
}
  	
void
GroupComponent::draw (DrawingContext& parent_gc)
{
  drawing_context.clear();

  draw_background(drawing_context);

  for(Components::iterator i = children.begin(); i != children.end(); ++i)
    {
      if ((*i)->is_visible())
        (*i)->draw(drawing_context);
    }
  
  parent_gc.draw(drawing_context);
}

void
GroupComponent::update (float delta)
{
  for(Components::iterator i = children.begin(); i != children.end(); ++i)
    {
      if ((*i)->is_visible())
        (*i)->update(delta);
    }
}

bool
GroupComponent::is_at (int x, int y)
{
  return (RectComponent::is_at(x,y) || component_at(drawing_context.screen_to_world(Vector2i(x, y))));
}

void
GroupComponent::on_primary_button_press (int x, int y)
{
  Vector2i mouse_pos = drawing_context.screen_to_world(Vector2i(x, y));
  Component* comp = component_at(mouse_pos);
  if (comp)
    {
      comp->on_primary_button_press(mouse_pos.x, mouse_pos.y);
      
      if (focused_comp)
        focused_comp->set_focus(false);

      focused_comp = comp;

      if (focused_comp)
        focused_comp->set_focus(true);
    }

  primary_pressed_comp = comp;
}

void
GroupComponent::on_primary_button_release (int x, int y)
{
  Vector2i mouse_pos = drawing_context.screen_to_world(Vector2i(x, y));
  Component* comp = component_at(mouse_pos);
      
  if (primary_pressed_comp)
    {
      primary_pressed_comp->on_primary_button_release(mouse_pos.x, mouse_pos.y);

      if (comp == primary_pressed_comp)
        primary_pressed_comp->on_primary_button_click(mouse_pos.x, mouse_pos.y);

      primary_pressed_comp = 0;
    }
  else
    {
      if (comp)
        comp->on_primary_button_release(mouse_pos.x, mouse_pos.y);
    }
}
  
void
GroupComponent::on_secondary_button_press (int x, int y)
{
  Vector2i mouse_pos = drawing_context.screen_to_world(Vector2i(x, y));
  Component* comp = component_at(mouse_pos);
  if (comp)
    comp->on_secondary_button_press(mouse_pos.x, mouse_pos.y);

  if (!primary_pressed_comp)
    secondary_pressed_comp = comp;
}

void
GroupComponent::on_secondary_button_release(int x, int y)
{
  Vector2i mouse_pos = drawing_context.screen_to_world(Vector2i(x, y));

  Component* comp = component_at(mouse_pos);
  
  if (secondary_pressed_comp)
    {
      secondary_pressed_comp->on_secondary_button_release(mouse_pos.x, mouse_pos.y);
      
      if (comp == secondary_pressed_comp)
        secondary_pressed_comp->on_secondary_button_click(mouse_pos.x, mouse_pos.y);
      
      secondary_pressed_comp = 0;
    }
  else
    {
      if (comp)
        comp->on_secondary_button_release(mouse_pos.x, mouse_pos.y);
    }
}

void
GroupComponent::on_key_pressed(const unsigned short c)
{
  if (focused_comp)
    focused_comp->on_key_pressed(c);
  else if (mouse_over_comp)
    mouse_over_comp->on_key_pressed(c);
}

void
GroupComponent::on_pointer_move(int x, int y)
{
  Vector2i mouse_pos = drawing_context.screen_to_world(Vector2i(x, y));
  if (primary_pressed_comp)
    {
      primary_pressed_comp->on_pointer_move(mouse_pos.x, mouse_pos.y);
    }
  else if (secondary_pressed_comp)
    {
      secondary_pressed_comp->on_pointer_move(mouse_pos.x, mouse_pos.y);
    }
  else
    {
      Component* comp = component_at(mouse_pos);
      if (comp)
        {
          comp->on_pointer_move(mouse_pos.x, mouse_pos.y); 
        }

      if (comp != mouse_over_comp)
        {
          if (mouse_over_comp)
            mouse_over_comp->on_pointer_leave();
      
          if (comp)
            comp->on_pointer_enter();
        }

      mouse_over_comp = comp;
    }
}

Component*
GroupComponent::component_at (const Vector2i& pos)
{
  for(Components::iterator i = children.begin(); i != children.end(); ++i)
    {
      if ((*i)->is_visible() && (*i)->is_at(pos.x, pos.y))
        return *i;
    }
  return 0;
}

void
GroupComponent::add(Component* comp, bool delete_comp)
{
  children.push_back(comp);
}

void
GroupComponent::update_layout()
{
  drawing_context.set_rect(rect);
}

} // namespace GUI

/* EOF */
