#ifndef _LUCHADOR_ESTADO_MAQUINA_HPP
#define _LUCHADOR_ESTADO_MAQUINA_HPP

#include "all_fight_states.h"

#include <array>

class Luchador;
class FighterStateMachine
{
public:
	enum State {
		IDLE,
		CROUCH,
		MOVE_RIGHT,
		MOVE_LEFT,
		FIGHT_MOVE,
		JUMP,
		JUMP_RIGHT,
		JUMP_LEFT,
		BLOCK,
		STUN,
		TOTAL,
	};

	FighterStateMachine(Fighter& fighter);
	FighterStateMachine(const FighterStateMachine& machine) = delete;
	FighterStateMachine& operator = (const FighterStateMachine& machine) = delete;

	~FighterStateMachine();

	void change_to(State new_state, void *data);
	FightMoveHook get_fightmove_hook();
	bool is_input_locked();
	FighterState* get_previous_state();
	State get_state();
	void tick();

	friend class FighterState;

private:
	std::array<FighterState*, State::TOTAL> states;
	FighterState* current_state;
	FighterState* prev_state;
	Fighter& fighter;
};
#endif