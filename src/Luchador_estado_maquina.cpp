#include "Luchador_estado_maquina.h"

FighterStateMachine::FighterStateMachine(Fighter& owner) : fighter(owner)
{
	states[State::IDLE] = new IdleState(*this);
	states[State::CROUCH] = new CrouchState(*this);
	states[State::MOVE_RIGHT] = new MoveRightState(*this);
	states[State::MOVE_LEFT] = new MoveLeftState(*this);
	states[State::FIGHT_MOVE] = new FightMoveState(*this);
	states[State::JUMP] = new JumpState(*this);
	states[State::JUMP_RIGHT] = new JumpRightState(*this);
	states[State::JUMP_LEFT] = new JumpLeftState(*this);
	states[State::BLOCK] = new BlockState(*this);
	states[State::STUN] = new StunState(*this);
	current_state = states[State::IDLE];
	prev_state = states[State::IDLE];
}

FighterStateMachine::~FighterStateMachine()
{
	for (auto state : states)
	{
		delete state;
	}
}

void FighterStateMachine::change_to(State new_state, void *data)
{
	if (states[new_state] == current_state)
		return;
	current_state->exit();
	prev_state = current_state;
	current_state = states[new_state];
	current_state->enter(data);
}

FightMoveHook FighterStateMachine::get_fightmove_hook()
{
	return current_state->get_move_hook();
}

bool FighterStateMachine::is_input_locked()
{
	return current_state->is_input_locked();
}

FighterState* FighterStateMachine::get_previous_state()
{
	return prev_state;
}

static int index(FighterState* p, std::array<FighterState*, FighterStateMachine::State::TOTAL> arry)
{
	int index = 0;
	for (auto& item : arry)
	{
		if (item == p)
			return index;
		index++;
	}
	return -1;
}

FighterStateMachine::State FighterStateMachine::get_state()
{
	return static_cast<FighterStateMachine::State>(index(current_state, states));
}


void FighterStateMachine::tick()
{
	current_state->tick();
}