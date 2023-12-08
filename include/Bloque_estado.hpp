#ifndef _BLOQUE_ESTADO_HPP
#define _BLOQUE_ESTADO_HPP

#include "fighter_state.h"

class BlockState : public FighterState
{
public:
	BlockState(FighterStateMachine& machine);
	void enter(void* data) override;
	void tick() override;
	void exit() override;
};
#endif