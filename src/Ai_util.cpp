#include "Ai_util.h"
#include "Luchador.h"
#include "Ai_luchador.h"

#include <random>
#include <algorithm>
#include <cmath>

static std::default_random_engine generator;
static std::uniform_real_distribution<double> distribution(0.0, 1.0);

double random()
{
	return distribution(generator);
}

unsigned int x_distance(Fighter& a, Fighter& b)
{
	return abs(a.get_position_x() - b.get_position_x());
}

static bool on_left(Fighter& subject, Fighter& target)
{
	if (subject.get_position_x() - target.get_position_x() < 0)
		return true;
	return false;
}

namespace Behavior
{
	Behavior::Behavior(BehaviorFunc func) 
	{
		type = DataType::FUNC;
		this->func = func;
		this->move = "";
	}

	Behavior::Behavior(std::string move)
	{
		type = DataType::FIGHTMOVE;
		this->move = move;
	}

	void Behavior::operator()(AIFighter& a, Fighter& b)
	{
		switch (type)
		{
		case FUNC:
			func(a, b);
			break;
		case FIGHTMOVE:
			a.perform_fightmove(move);
			break;
		}
	}

	void jump_towards(AIFighter& subject, Fighter& target)
	{
		if (on_left(subject, target))
		{
			subject.set_state(FighterStateMachine::State::JUMP_RIGHT);
		}
		else
		{
			subject.set_state(FighterStateMachine::State::JUMP_LEFT);
		}
	}

	void jump_away(AIFighter& subject, Fighter& target)
	{
		if (on_left(subject, target))
		{
			subject.set_state(FighterStateMachine::State::JUMP_LEFT);
		}
		else
		{
			subject.set_state(FighterStateMachine::State::JUMP_RIGHT);
		}
	}

	void move_towards(AIFighter& subject, Fighter& target)
	{
		if (on_left(subject, target))
		{
			subject.set_state(FighterStateMachine::State::MOVE_RIGHT);
		}
		else
		{
			subject.set_state(FighterStateMachine::State::MOVE_LEFT);
		}
	}

	void move_away(AIFighter& subject, Fighter& target)
	{
		if (on_left(subject, target))
		{
			subject.set_state(FighterStateMachine::State::MOVE_LEFT);
		}
		else
		{
			subject.set_state(FighterStateMachine::State::MOVE_RIGHT);
		}
	}

	void idle(AIFighter& subject, Fighter& target)
	{
		subject.set_state(FighterStateMachine::State::IDLE);
	}

	void block(AIFighter& subject, Fighter& target)
	{
		subject.set_state(FighterStateMachine::State::BLOCK, false);
	}
}