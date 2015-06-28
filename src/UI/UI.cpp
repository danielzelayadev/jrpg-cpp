#include "UI/UI.h"

UI::UI(string textureDir, int x, int y, SDL_Renderer* renderer)
{
   touchedTexture = nullptr;
   setPosition(x, y);
   setRenderer(renderer);
   setTexture(textureDir);
}

UI::UI(SDL_Renderer* renderer, int x, int y , int width, int height)
{
    texture = nullptr;
    touchedTexture = nullptr;
    setRenderer(renderer);
    setBounds(x, y, width, height);
}

void UI::vectorDraw(void (*customVectorDraw)())
{
    customVectorDraw();
}

void UI::setPosition(int x, int y)
{
  setX(x);
  setY(y);
}

void UI::setX(int x)
{
  bounds.x = x;
}

void UI::setY(int y)
{
  bounds.y = y;
}

void UI::setWidth(int w)
{
  bounds.w = w;
}

void UI::setHeight(int h)
{
  bounds.h = h;
}

void UI::setDimensions(int w, int h)
{
  setWidth(w);
  setHeight(h);
}

void UI::setBounds(int x, int y, int w, int h)
{
  setPosition(x, y);
  setDimensions(w, h);
}

void UI::setBounds(SDL_Rect bounds)
{
  this->bounds = bounds;
}

void UI::translate(int dx, int dy)
{
   bounds.x += dx;
   bounds.y += dy;
}

void UI::show()
{
   shown = true;
   hidden = false;
}

void UI::hide()
{
  shown = false;
  hidden = true;
}

void UI::focus()
{
  focused = true;
}

void UI::unfocus()
{
  focused = false;
}

void UI::enable()
{
  enabled = true;
}

void UI::disable()
{
  enabled = false;
}

int UI::getX()
{
  return bounds.x;
}

int UI::getY()
{
  return bounds.y;
}

int UI::getWidth()
{
  return bounds.w;
}

int UI::getHeight()
{
  return bounds.h;
}

SDL_Rect UI::getBounds()
{
  return bounds;
}

bool UI::isEnabled()
{
  return enabled;
}

bool UI::isDisabled()
{
  return !enabled;
}

bool UI::isShown()
{
  return shown;
}

bool UI::isHidden()
{
  return hidden;
}

bool UI::hasFocus()
{
  return focused;
}

void UI::setTouched(bool t)
{
  touched = t;
}

bool UI::getTouched()
{
  return touched;
}

bool UI::isTouched(int x, int y)
{
   touched = contains(x, y);
   return touched;
}

bool UI::contains(int x, int y)
{
  return bounds.x < x && bounds.x + bounds.w > x &&
             bounds.y < y && bounds.y + bounds.h > y;
}

void UI::setTag(string tag)
{
   this->tag = tag;
}

string UI::getTag()
{
  return tag;
}

void UI::setTexture(string textureDir)
{
  texture = IMG_LoadTexture(renderer, textureDir.c_str());
  SDL_QueryTexture(texture, 0, 0, &bounds.w, &bounds.h);
}

void UI::setRenderer(SDL_Renderer* renderer)
{
  this->renderer = renderer;
}

void UI::setTextureColorMod(int r, int g, int b, int a)
{
   SDL_SetTextureColorMod(texture, r, g, b );
}
