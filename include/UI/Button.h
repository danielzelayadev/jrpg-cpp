#ifndef BUTTON_H
#define BUTTON_H

#include "UI.h"

class Button : public UI
{
    public:
        Button(string textureDir, int x, int y, SDL_Renderer* renderer):UI(textureDir, x, y, renderer){}

    void update();
	void draw();
	void dispose();

	void setText(string text);
	string getText();

    private:

    string text;
};

#endif // BUTTON_H
