#ifndef _MANDO_H
#define _MANDO_H

#include "input_device.h"
#include <memory>

struct GamepadDeleterFunctor{
	void operator()(SDL_GameController* controller) {
		SDL_GameControllerClose(controller);
	}
};

class GamepadDevice : public InputDevice
{
public:
	GamepadDevice(SDL_GameController* controller, int id);

	InputEvent get_input(SDL_Event& event) override;
	bool is_button_down(InputButton button) override;

private:
	std::unique_ptr <SDL_GameController, GamepadDeleterFunctor> controller;
	int id;
};

#endif