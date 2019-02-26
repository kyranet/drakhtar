#include "Button.h"


Button::Button(Texture* t, int x, int y, int w, int h, void(*callback)(Game* game), Game* game) :
	GameObject(t, Vector2D<int>(x, y), Vector2D<int>(w, h)), texture(t), x(x), y(y), w(w), h(h), cb(callback), game(game) {}

void Button::handleEvents(SDL_Event& e) {	
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {    // RATON IZQUIERDO
		SDL_Point p = { e.button.x, e.button.y };
		SDL_Rect r = { x, y, w, h };
		if (SDL_PointInRect(&p, &r)) {
			cb(game);			
		}		
	}
}
