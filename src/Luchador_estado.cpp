#include "Luchador_estado.h"
#include "fighter_state_machine.h"

FighterState::FighterState(FighterStateMachine& machine, FightMoveHook hook)
	: machine(machine), fighter(machine.fighter)
{
	fightmove_hook = hook;
}

bool FighterState::is_input_locked() const
{
	return is_locked;
}

void FighterState::lock_input()
{
	is_locked = true;
}
void FighterState::unlock_input()
{
	is_locked = false;
}

FightMoveHook FighterState::get_move_hook() const
{
	return fightmove_hook;
}