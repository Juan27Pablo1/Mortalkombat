#include "Ai_luchador.h"
#include "Ai_util.h"

#include <cmath>
#include <iostream>

static Uint32 timer_callback(Uint32 interval, void* param)
{
	bool* status = static_cast<bool*>(param);
	*status = false;
	return 0;
}

AIFighter::AIFighter(FighterAnimator& animator, std::function<void(AIFighter& ai, Fighter& other)> logic)
	: Fighter(animator), logic_func(logic)
{
}

void AIFighter::tick()
{
	Fighter::tick();
}

void AIFighter::driver(Fighter& other)
{
	if (!state_machine->is_input_locked() && !action_chosen)
	{ 
		logic_func(*this, other);
		action_chosen = true;
		SDL_AddTimer(200, timer_callback, &action_chosen);
	}
}