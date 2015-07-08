#include "DialogueBox.h"

DialogueBox::DialogueBox(SDL_Renderer* renderer, SDL_Rect geom)
{
    this->renderer = renderer;
    setText("");
    font = TTF_OpenFont(fontSrc.c_str(), fontSize);
    setGeometry(geom);
    loadFontTexture();
}

DialogueBox::DialogueBox(SDL_Renderer* renderer, string text, SDL_Rect geom)
{
    this->renderer = renderer;
    setText(text);
    font = TTF_OpenFont(fontSrc.c_str(), fontSize);
    setGeometry(geom);
    loadFontTexture();
}

void DialogueBox::render()
{
   SDL_SetRenderDrawColor(renderer, 150, 255, 200, 255);
   SDL_RenderFillRect(renderer, &rect);
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
   SDL_RenderDrawRect(renderer, &rect);

   SDL_Rect textRect = {rect.x, rect.y + 20, 1000, 100 };

   SDL_RenderCopy(renderer, fontTexture, 0, &textRect);
}

void DialogueBox::loadFontTexture()
{
    SDL_Color textColor = {0, 0, 0, 255};

    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor );

    fontTexture = SDL_CreateTextureFromSurface( renderer, textSurface );

    SDL_FreeSurface( textSurface );
}

DialogueBox::~DialogueBox()
{
   TTF_CloseFont(font);
   SDL_DestroyTexture(fontTexture);
}
