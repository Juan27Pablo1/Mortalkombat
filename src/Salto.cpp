#include "Salto.h"
#include "Luchador.h"
#include "fighter_state_machine.h"
#include "constants.h"

JumpState::JumpState(FighterStateMachine& machine)
	: FighterState(machine, FightMoveHook::JUMP)
{
}

void JumpState::enter(void *data)
{
	fighter.set_graphics(FighterGraphics::JUMP);
	lock_input();
	fighter.jump();
}

void JumpState::tick()
{
	if (!fighter.is_airborne())
	{
		machine.change_to(FighterStateMachine::State::IDLE, nullptr);
	}
}

void JumpState::exit()
{
	unlock_input();
	fighter.get_animation()->restart();
}