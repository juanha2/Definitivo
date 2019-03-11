#include <iostream>
#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
#include "SDL_Mixer/include/SDL_mixer.h"


#pragma comment (lib, "SDL/libx86/SDL2.lib")
#pragma comment (lib, "SDL/libx86/SDL2main.lib")

#pragma comment (lib, "SDL_Image/libx86/SDL2_image.lib")

#pragma comment (lib, "SDL_Mixer/libx86/SDL2_mixer.lib")


using namespace std;

int main(int argc, char*argv[]) {

	//Inicialización 
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	Mix_Init(MIX_INIT_OGG);	
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

	//Creación ventana

	SDL_Window *window; //Declaramos puntero window

	window = SDL_CreateWindow(
		"Cuadrado rojo", //Titulo Ventana
		SDL_WINDOWPOS_CENTERED, // Posicion inicial x (centrado)
		SDL_WINDOWPOS_CENTERED, // Posicion inicial y (centrado)
		640, // Anchura de imagen
		480, // Altura de imagen
		SDL_WINDOW_FULLSCREEN_DESKTOP
	);

	//Creación Renderer

	SDL_Renderer *renderer; //Declaramos nuestro renderer	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	
	//Creación rectángulos

	SDL_Rect dstrect;

	dstrect.x = 190;
	dstrect.y = 110;
	dstrect.w = 180;
	dstrect.h = 110;		

	SDL_Rect dbala;

	dbala.x = -60;
	dbala.y = -20;
	dbala.w = 60;
	dbala.h = 20;

	//Declaración evento y variables

	SDL_Event event; 

	int run = true;
	bool key_left = false;
	bool key_right = false;
	bool key_up = false;
	bool key_down = false;
	bool bala = false;
	bool shoot = false;
	
	Mix_Chunk *musica;
	musica= Mix_LoadWAV("musica.WAV");	


	while (run==true) {		
		
		//INPUT 

		while (SDL_PollEvent(&event)) {

			
			switch (event.type) {	

			case SDL_QUIT: run = false; break;
				
			case(SDL_KEYDOWN):			

				switch (event.key.keysym.sym) { //
				case SDLK_LEFT: key_left = true; break;
				case SDLK_RIGHT:  key_right = true ; break;
				case SDLK_UP:;  key_up = true; break;
				case SDLK_DOWN:;  key_down = true; break;
				case SDLK_ESCAPE: run = false; break;
				case SDLK_SPACE: bala = true; break;
				default: break;
				}
				break;

			case (SDL_KEYUP):

				switch (event.key.keysym.sym) { 
				case SDLK_LEFT:  key_left = false; break;
				case SDLK_RIGHT: key_right = false; break;
				case SDLK_UP:; key_up = false; break;
				case SDLK_DOWN:; key_down = false; break;
				case SDLK_ESCAPE: run = false; break;
				case SDLK_SPACE: bala = false; break;
				default: break;
				}
				
				default: break;					
			}							
			
		}			

		//LOGICA			

		if (key_right) {
			dstrect.x += 10;
		}
		if (key_up) {
			dstrect.y -= 10;
		}
		if (key_down) {
			dstrect.y += 10;
		}
		if (key_left) {
			dstrect.x -= 10;
		}
		if (bala) {
			Mix_PlayChannel(-1, musica, 0);
			dbala.x = dstrect.x + dstrect.w /2;
			dbala.y = dstrect.y +dstrect.h /2;
			shoot = true;
		}
		if (shoot) {
			
			dbala.x += 50;
		}

		//PAINT

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); 
		SDL_RenderClear(renderer); 	

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
		SDL_RenderFillRect(renderer, &dstrect); 

		
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
		SDL_RenderFillRect(renderer, &dbala);
		SDL_RenderPresent(renderer);
	}

	//DESTROY 

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	

	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
	Mix_CloseAudio();

	return 0;
}

