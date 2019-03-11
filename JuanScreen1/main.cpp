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

	SDL_Window *window; 

	window = SDL_CreateWindow(
		"Cuadrado rojo", //Titulo Ventana
		SDL_WINDOWPOS_CENTERED, // Posicion inicial x (centrado)
		SDL_WINDOWPOS_CENTERED, // Posicion inicial y (centrado)
		1280, // Anchura de imagen
		720, // Altura de imagen
		SDL_WINDOW_OPENGL
	);

	//Creación Renderer

	SDL_Renderer *renderer; 	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	
	//Creación rectángulos

	SDL_Rect dstrect;

	dstrect.x = 190;
	dstrect.y = 110;
	dstrect.w = 150;
	dstrect.h = 180;		

	SDL_Rect dbala;

	dbala.x = -100;
	dbala.y = -100;
	dbala.w = 200;
	dbala.h = 100;

	//Declaración evento y variables

	SDL_Event event; 

	int run = true;
	bool key_left = false;
	bool key_right = false;
	bool key_up = false;
	bool key_down = false;
	bool bala = false;
	bool shoot = false;
	
	Mix_Chunk *spit;
	spit= Mix_LoadWAV("spit.WAV");	

	Mix_Music *music;
	music = Mix_LoadMUS("music.WAV");

	SDL_Surface *sbackground = IMG_Load("background.png");
	SDL_Texture *tbackground = SDL_CreateTextureFromSurface(renderer, sbackground);

	SDL_Surface *sllama = IMG_Load("llama.png");
	SDL_Texture *tllama = SDL_CreateTextureFromSurface(renderer, sllama);

	SDL_Surface *sbala = IMG_Load("bala.png");
	SDL_Texture *tbala = SDL_CreateTextureFromSurface(renderer, sbala);


	Mix_PlayMusic(music,  - 1);

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
				case SDLK_SPACE:
					Mix_PlayChannel(-1, spit, 0);
					dbala.x = (dstrect.x + dstrect.w / 2) - 40;
					dbala.y = (dstrect.y + dstrect.h / 2) - 80;
					 break;
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
				default: break;
				}
				
				default: break;					
			}							
			
		}			
		
		//LOGICA			
		if (dstrect.x < 0) dstrect.x = 0; 
		if (dstrect.y < 0) dstrect.y = 0;
		if (dstrect.x > (1280-dstrect.w)) dstrect.x = (1280 - dstrect.w);
		if (dstrect.y > (720 - dstrect.h)) dstrect.y = (720 - dstrect.h);

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
		dbala.x += 50;

		//PAINT
		
		SDL_RenderCopy(renderer, tbackground, NULL, NULL);
		
		SDL_RenderCopy(renderer, tllama, NULL, &dstrect);

		SDL_RenderCopy(renderer, tbala, NULL, &dbala);	
		
	
		SDL_RenderPresent(renderer);
	}

	//DESTROY 

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(tbackground);	
	SDL_DestroyTexture(tbackground);
	Mix_FreeChunk(spit);
	Mix_FreeMusic(music);
		

	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
	Mix_CloseAudio();

	return 0;
}

