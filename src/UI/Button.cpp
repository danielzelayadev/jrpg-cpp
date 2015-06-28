#include "UI/Button.h"

void Button::update()
{
}

void Button::draw()
{
   SDL_RenderCopy(renderer, texture, 0, &bounds);
}

void Button::dispose()
{
   if(texture)
   {
     SDL_DestroyTexture(texture);
     delete texture;
   }

   if(touchedTexture)
   {
     SDL_DestroyTexture(touchedTexture);
     delete touchedTexture;
   }
}

void Button::setText(string text)
{
   this->text = text;
}

string Button::getText()
{
   return text;
}

