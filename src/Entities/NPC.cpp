#include "NPC.h"

NPC::~NPC()
{
   SDL_DestroyTexture(spritesheet);
   delete movements;
}
