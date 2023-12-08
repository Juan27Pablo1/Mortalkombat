#include "Mando.h"

#include <map>

static std::map<InputButton, SDL_GameControllerButton> translations = {
	{InputButton::BUTTON_A, SDL_CONTROLLER_BUTTON_A},
	{InputButton::BUTTON_X, SDL_CONTROLLER_BUTTON_X},
	{InputButton::BUTTON_Y, SDL_CONTROLLER_BUTTON_Y},
	{InputButton::BUTTON_B, SDL_CONTROLLER_BUTTON_B},
	{InputButton::BUTTON_UP, SDL_CONTROLLER_BUTTON_DPAD_UP},
	{InputButton::BUTTON_DOWN, SDL_CONTROLLER_BUTTON_DPAD_DOWN},
	{InputButton::BUTTON_LEFT, SDL_CONTROLLER_BUTTON_DPAD_LEFT},
	{InputButton::BUTTON_RIGHT, SDL_CONTROLLER_BUTTON_DPAD_RIGHT},
	{InputButton::BUTTON_BACK, SDL_CONTROLLER_BUTTON_BACK},
	{InputButton::BUTTON_START, SDL_CONTROLLER_BUTTON_START},
	{InputButton::BUTTON_LEFTSHOULDER, SDL_CONTROLLER_BUTTON_LEFTSHOULDER},
	{InputButton::BUTTON_RIGHTSHOULDER, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER},
};

GamepadDevice::GamepadDevice(SDL_GameController* game_controller, int id) : controller(game_controller), id(id)
{
}

InputEvent GamepadDevice::get_input(SDL_Event& event)
{
	InputEvent evnt = { EventType::NONE, InputButton::NONE };

	if (event.cdevice.which != id) return evnt; // this event doesn't concern us

	if (event.type == SDL_CONTROLLERBUTTONDOWN) evnt.type = EventType::BUTTON_DOWN;
	if (event.type == SDL_CONTROLLERBUTTONUP) evnt.type = EventType::BUTTON_UP;

	if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP)
	{
		for (auto item : translations)
		{
			if (event.cbutton.button == item.second)
			{
				evnt.button = item.first;
			}
		}
	}
	return evnt;
}

bool GamepadDevice::is_button_down(InputButton btn)
{
	if (btn == InputButton::NONE)
		return false;

	SDL_GameControllerButton key = translations[btn];
	if (SDL_GameControllerGetButton(controller.get(), key))
		return true;
	return false;
}