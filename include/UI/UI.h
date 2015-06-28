#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

using namespace std;

class UI
{
    protected:

    SDL_Texture* texture, *touchedTexture;
    SDL_Renderer* renderer;
    SDL_Rect bounds;

	string tag = "";

	bool touched = false;

	bool focused;

	bool shown = true;
	bool hidden = false;

	bool enabled = true;

    public:

    UI(){}
    UI(string textureDir, int x, int y, SDL_Renderer* renderer);
    UI(SDL_Renderer* renderer, int x, int y , int width, int height);

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void dispose() = 0;

	void vectorDraw(void (*customVectorDraw)());

	void setPosition(int x, int y);

	void translate(int dx, int dy);

	void setX(int x);

	void setY(int y);

	void setWidth(int w);

	void setHeight(int h);

	void setDimensions(int w, int h);

	void setBounds(int x, int y, int w, int h);

	void setBounds(SDL_Rect bounds);

	void show();

	void hide();

	void focus();

	void unfocus();

	int getX();

	int getY();

	int getWidth();

	int getHeight();

	SDL_Rect getBounds();

	void enable();

	void disable();

	bool isEnabled();

	bool isDisabled();

	bool isShown();

	bool isHidden();

	bool hasFocus();

	void setTouched(bool t);

	bool getTouched();

	bool isTouched(int x, int y);

	bool contains(int x, int y);

	void setTag(string tag);

	string getTag();

	void setTexture(string textureDir);

	void setRenderer(SDL_Renderer* renderer);

	void setTextureColorMod(int r, int g, int b, int a);

};

#endif // UI_H
