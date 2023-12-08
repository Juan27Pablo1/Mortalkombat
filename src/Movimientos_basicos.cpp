#include "basic_fightmove.h"
#include "effect.h"

BasicFightMove::BasicFightMove(int animation, int damage, std::shared_ptr<Effect> effect)
{
	this->animation = animation;
	this->damage = damage;
	this->effect = effect;
}

void BasicFightMove::enter(Fighter& fighter)
{
	fighter.set_graphics(static_cast<FighterGraphics>(this->animation));
}

bool BasicFightMove::is_complete(Fighter& fighter)
{
	return fighter.get_animation()->is_complete();
}

void BasicFightMove::apply_effect(Fighter& target)
{
	target.set_health(target.get_health() - damage);
	target.set_state(FighterStateMachine::State::STUN, effect.get());
}