#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

using namespace std;

class DialogueBox
{
    public:
        DialogueBox(SDL_Renderer* renderer, string text, SDL_Rect geom);
        DialogueBox(SDL_Renderer* renderer, SDL_Rect geom);
        virtual ~DialogueBox();

        void update();
        void render();

        void setGeometry(int x, int y, int w, int h) { rect = {x, y, w, h}; }
        void setGeometry(SDL_Rect geom) { rect = geom; }

        void setPosition(int x, int y) { setX(x); setY(y); }

        void setX(int x) { rect.x = x; }
        void setY(int y) { rect.y = y; }

        void setFontSize(int sz) { fontSize = sz; }

        void setText(string text) { this->text = text; }
        string getText() { return text; }

    private:
        string text;
        string fontSrc = "Assets/UI/Fonts/rpg.ttf";

        SDL_Renderer* renderer;

        SDL_Texture* fontTexture;

        int fontSize = 12;
        TTF_Font* font;
        SDL_Rect rect;

        void loadFontTexture();
};

#endif // DIALOGUEBOX_H
