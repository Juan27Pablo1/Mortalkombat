#ifndef _AI_LUCHADOR_HPP
#define _AI_LUCHADOR_HPP

#include "Luchador.h"
#include <memory>
#include <functional>

class AIFighter : public Fighter
{
public:
	AILuchador(FighterAnimator &animator, std::function<void(AIFighter& ai, Fighter& other)> logic); 
	AILuchador(const AIFighter& aifighter) = delete;
	AIFighter& operator =(const AIFighter& aifighter) = delete;

	void tick();
	void driver(Fighter& other);
private:
	std::function<void(AIFighter& ai, Fighter& other)> logic_func;
	bool action_chosen{ false };
};
#endif