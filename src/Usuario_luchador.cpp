#include "user_fighter.h"

UserFighter::UserFighter(FighterAnimator& animator, std::map<ActivationKey, std::string> move_map)
	: Fighter(animator), fightmove_handler(*this, move_map)
{

}

void UserFighter::handle_input_event(InputEvent& event, InputDevice& controller)
{
	if (state_machine->is_input_locked())
		return;
	fightmove_handler.process_event(event, state_machine->get_fightmove_hook(), 
		                            get_orientation());
	if (event.type == EventType::BUTTON_DOWN)
	{
		handle_button_press(event.button, controller);
	}
	if (event.type == EventType::BUTTON_UP)
	{
		handle_button_release(event.button, controller);
	}
}

void UserFighter::handle_button_press(InputButton button, InputDevice& controller)
{
	if (button == InputButton::BUTTON_UP)
	{
		if (controller.is_button_down(InputButton::BUTTON_RIGHT))
		{
			set_state(FighterStateMachine::State::JUMP_RIGHT);
		}
		else if (controller.is_button_down(InputButton::BUTTON_LEFT))
		{
			set_state(FighterStateMachine::State::JUMP_LEFT);
		}
		else
		{
			set_state(FighterStateMachine::State::JUMP);
		}
	}
	else if (button == InputButton::BUTTON_RIGHT)
	{
		set_state(FighterStateMachine::State::MOVE_RIGHT);
	}
	else if (button == InputButton::BUTTON_LEFT)
	{
		set_state(FighterStateMachine::State::MOVE_LEFT);
	}
	else if (button == InputButton::BUTTON_DOWN)
	{
		set_state(FighterStateMachine::State::CROUCH);
	}
	else if (button == InputButton::BUTTON_RIGHTSHOULDER)
	{
		bool is_crouch = false;
		if (controller.is_button_down(InputButton::BUTTON_DOWN))
		{
			is_crouch = true;
			set_state(FighterStateMachine::State::BLOCK, &is_crouch);
		}
		else
		{
			set_state(FighterStateMachine::State::BLOCK, &is_crouch);
		}
	}
}

void UserFighter::handle_button_release(InputButton button, InputDevice& controller)
{
	if (button == InputButton::BUTTON_DOWN)
	{
		set_state(FighterStateMachine::State::IDLE);
	}
	if (button == InputButton::BUTTON_RIGHT || button == InputButton::BUTTON_LEFT)
	{
		set_state(FighterStateMachine::State::IDLE);
	}
	if (button == InputButton::BUTTON_RIGHTSHOULDER)
	{
		if (controller.is_button_down(InputButton::BUTTON_DOWN))
		{
			set_state(FighterStateMachine::State::CROUCH);
		}
		else
		{
			set_state(FighterStateMachine::State::IDLE);
		}
	}
}