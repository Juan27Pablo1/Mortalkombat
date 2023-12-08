#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "gamestate.h"
#include "Graphics.h"
#include "Constantes.h"
#include "keyboard_device.h"
#include "gamepad_device.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* screen = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) != 0)
	{
		std::cout << "Could not initialize! " << Mix_GetError() << std::endl;
	}
	if (TTF_Init() == -1)
	{
		std::cout << "Could not initialize!" << TTF_GetError() << std::endl;
		return 1;
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_CHANNELS, 1024) != 0)
	{
		std::cout << "Could not open audio! " << Mix_GetError() << std::endl;
	}
	window = SDL_CreateWindow("Mortal Kombat II", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_SHOWN);
	const int FPS = 60;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, 400, 254);
	bones::GraphicsLoader graphics(renderer);

	int nusers = SDL_NumJoysticks();
	std::cout << nusers << " detected." << std::endl;
	SDL_GameController* controller = nullptr; 
	SDL_GameController* controller2 = nullptr;
	InputDevice* input_device = nullptr;
	InputDevice* input_device2 = nullptr;
	if (nusers == 0)
	{
		input_device = new KeyboardDevice();
	}
	else if (nusers == 1)
	{
		controller = SDL_GameControllerOpen(0);
		input_device = new GamepadDevice(controller, 0);
	}
	else
	{
		controller = SDL_GameControllerOpen(0);
		input_device = new GamepadDevice(controller, 0);
		controller2 = SDL_GameControllerOpen(1);
		input_device2 = new GamepadDevice(controller2, 1);
	}

	SDL_Event event;
	bool quit = false;
	GameState gamestate;
	gamestate.init(0, false, 0, true, graphics, input_device, input_device2);
	bones::AudioClip music("data/sounds/musiccues/mk2-oneguy.mp3");
	music.play(-1);
	while (!quit)
	{
		Uint32 ticks = SDL_GetTicks();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit = true;
			gamestate.handle_input(event);
		}
		gamestate.tick();
		gamestate.render(renderer);
		SDL_RenderPresent(renderer);

		if (gamestate.is_complete())
			break;

		int time = SDL_GetTicks() - ticks;
		if (time < (1000 / FPS))
		{
			SDL_Delay((1000 / FPS) - time);
		}
	}
	delete input_device;
	if (nusers > 1)
		delete input_device2;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	return 0;
}