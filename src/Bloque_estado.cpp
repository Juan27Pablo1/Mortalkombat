#include "Bloque_estado.h"
#include "Luchador.h"

BlockState::BlockState(FighterStateMachine& machine) :
	FighterState(machine, FightMoveHook::NONE)
{
}

void BlockState::enter(void* data)
{
	bool is_crouch = (!data) ? false : *static_cast<bool*>(data);
	if (is_crouch)
		fighter.set_graphics(FighterGraphics::CROUCH_BLOCK);
	else
		fighter.set_graphics(FighterGraphics::BLOCK);
}

void BlockState::tick()
{

}

void BlockState::exit()
{
	fighter.get_animation()->restart();
}