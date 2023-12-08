#ifndef _MOVIMIENTOS_BASICOS_HPP
#define _MOVIMIENTOS_BASICOS_HPP

#include "fightm.h"
#include "fighter_animator.h"

#include <memory>

class Effect;
class BasicFightMove : public FightMove
{
public:
	
	BasicFightMove() = default;
	BasicFightMove(int animation, int damage, std::shared_ptr<Effect> effect); 

	void enter(Fighter& fighter) override;
	bool is_complete(Fighter& fighter) override;
	void exit(Fighter& fighter) override {};
	void apply_effect(Fighter& target) override;

private:
	int damage;
	int animation;
	std::shared_ptr<Effect> effect;
};
#endif