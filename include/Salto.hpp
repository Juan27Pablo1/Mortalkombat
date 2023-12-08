#ifndef _SALTO_HPP
#define _SALTO_HPP

#include "Luchador.h"

class Salto : public Luchador
{
public:
	JumpState(FighterStateMachine& machine);
	void enter(void *data) override;
	void tick() override;
	void exit() override;
};
#endif