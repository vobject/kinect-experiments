#include "EmptyBackground.h"

#include <allegro5/allegro.h>

EmptyBackground::EmptyBackground()
{

}

EmptyBackground::~EmptyBackground()
{

}

void EmptyBackground::Update()
{

}

void EmptyBackground::Render()
{
   al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
   al_clear_to_color(al_map_rgb(0x00, 0x00, 0x00));
}
