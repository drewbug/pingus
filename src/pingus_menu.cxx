//  $Id: pingus_menu.cxx,v 1.22 2003/10/19 12:25:47 grumbel Exp $
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

#include <ClanLib/Display/display.h>
#include <config.h>
#include "gettext.h"
#include "menu_button.hxx"
#include "resource.hxx"
#include "debug.hxx"
#include "sound/sound.hxx"
#include "stat_manager.hxx"
#include "story_screen.hxx"
#include "story.hxx"
#include "worldmap/manager.hxx"
#include "gui/screen_manager.hxx"
#include "pingus_menu_manager.hxx"
#include "gui/gui_manager.hxx"

namespace Pingus {

PingusMenu::PingusMenu (PingusMenuManager* m)
  : PingusSubMenu (m)
{
  is_init = false;
    
  start_button = new MenuButton(CL_Point(CL_Display::get_width() * 400 / 800,
                                         CL_Display::get_height() * 370 / 600),
                                Resource::load_sprite("menu/play_on", "core"),
                                _("Start"),
                                _("..:: Start the game ::.."));
  
  quit_button = new MenuButton(CL_Point(CL_Display::get_width() * 650 / 800,
                                        CL_Display::get_height() * 370 / 600),
                               Resource::load_sprite("menu/exit_on", "core"),
                               _("Exit"),
                               _("..:: Bye, bye ::.."));

  contrib_button = new MenuButton(CL_Point(CL_Display::get_width() * 150 / 800,
                                          CL_Display::get_height() * 370 / 600),
                                  Resource::load_sprite("menu/options_on", "core"),
                                  _("Contrib\nLevels"),
                                  _("..:: Play User Build levels ::.."));

  story_button  = new MenuButton(CL_Point(CL_Display::get_width() * 400 / 800,
                                          CL_Display::get_height() * 370 / 600),
                                 Resource::load_sprite("menu/credits_on", "core"),
                                 _("Story"),
                                 _("..:: Start the story ::.."));
  
  multiplayer_button = new MenuButton(CL_Point(CL_Display::get_width() * 650 / 800,
                                               CL_Display::get_height() * 370 / 600),
                                      Resource::load_sprite("menu/multi_on", "core"),
                                      _("Multiplayer"),
                                      _("..:: Multiplayer Match ::.."));

  slots.push_back(start_button->sig_click().connect(this, &PingusMenu::setup_game_menu));
  slots.push_back(quit_button->sig_click().connect(this, &PingusMenu::do_quit));

  slots.push_back(story_button->sig_click().connect(this, &PingusMenu::do_start));
  slots.push_back(multiplayer_button->sig_click().connect(this, &PingusMenu::setup_main_menu));
}

void
PingusMenu::setup_main_menu()
{
  gui_manager->remove(contrib_button);
  gui_manager->remove(story_button);
  gui_manager->remove(multiplayer_button);

  gui_manager->add(quit_button);
  gui_manager->add(start_button);
}

void
PingusMenu::setup_game_menu()
{
  gui_manager->remove(quit_button);
  gui_manager->remove(start_button);

  gui_manager->add(contrib_button);
  gui_manager->add(story_button);
  gui_manager->add(multiplayer_button);
}

void
PingusMenu::preload ()
{
  if (!is_init)
    {
      is_init = true;

      background = Resource::load_sprite("misc/logo", "core");
      setup_main_menu();
    }
}

PingusMenu::~PingusMenu()
{
}

void
PingusMenu::do_quit()
{
  get_manager ()->show_exit_menu ();
}

void
PingusMenu::do_start()
{ // Start the story mode
  Sound::PingusSound::play_sound ("letsgo");

  bool story_seen = false;
  StatManager::instance()->get_bool("story-seen", story_seen);

  if (!story_seen)
    {
      ScreenManager::instance()->push_screen(new StoryScreen(Story::intro), true);
    }
  else
    {
      ScreenManager::instance()->push_screen(WorldMapNS::WorldMapManager::instance ());
    }
}

void
PingusMenu::on_resize(int w, int h)
{
  pout << "Width: " << w << " Height: " << h << std::endl;
}

void
PingusMenu::on_escape_press ()
{
  get_manager ()->show_exit_menu ();
}

void
PingusMenu::draw_foreground(GraphicContext& gc)
{
  if (gc.get_height() == 480)
    {
      gc.draw(background,
              Vector((gc.get_width()/2) - (background.get_width()/2),
                     20));
    }
  else
    {
      gc.draw(background, 
              Vector((gc.get_width()/2) - (background.get_width()/2),
                     CL_Display::get_height()/10));
    }
#ifdef OFFICIAL_PINGUS_BUILD
  gc.print_left(Fonts::pingus_small, 20, CL_Display::get_height()-100,
                "Pingus version "VERSION", Copyright (C) 2003 Ingo Ruhnke <grumbel@gmx.de>\n");
#else
  gc.print_left(Fonts::pingus_small, 20, CL_Display::get_height()-100,
                "Pingus version "VERSION" (unofficial build), Copyright (C) 2003 Ingo Ruhnke <grumbel@gmx.de>\n");
#endif
  gc.print_left(Fonts::pingus_small, 20, CL_Display::get_height()-70,
                "Pingus comes with ABSOLUTELY NO WARRANTY. This is free software, and you are welcome\n"
                "to redistribute it under certain conditions; see the file COPYING for details.\n");
}

} // namespace Pingus

/* EOF */
