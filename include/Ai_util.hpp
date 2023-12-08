#ifndef _AI_UTIL_HPP
#define _AI_UTIL_HPP

#include <stdexcept>
#include <string>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

double random();

class AILuchador;
class Luchador;
unsigned int x_distance(Luchador& a, Luchador& b);

namespace Behavior
{
	using BehaviorFunc = std::function<void(AILuchador&, Luchador&)>;

	class Behavior
	{
	public:
		Behavior() = default;
		~Behavior() = default;
		Behavior(BehaviorFunc behavior);
		Behavior(std::string move);

		void operator()(AILuchador&, Luchador&);

	private:
		BehaviorFunc func;
		std::string move;
		enum DataType { FUNC, FIGHTMOVE } type;
	};

	void jump_towards(AIFighter& subject, Fighter& target);
	void jump_away(AIFighter& subject, Fighter& target);
	void move_towards(AIFighter& subject, Fighter& target);
	void move_away(AIFighter& subject, Fighter& target);
	void idle(AIFighter& subject, Fighter& target);
	void block(AIFighter& subject, Fighter& target);
};

template <typename T, typename V>
bool pair_compare(const std::pair<T, V>& a, const std::pair<T, V>& b)
{
	return (a.first < b.first);
}

template <typename T> 
T nonuni_random_state_from(std::vector<std::pair<int, T>> prob_map)
{
	int prob_total = 0;
	int last_prob = 0;
	for (auto& item : prob_map) {
		prob_total += item.first;
		last_prob += item.first;
		item.first = last_prob;
	}
	if (prob_total != 100)
		throw std::logic_error("Probabilities must sum to 1.");
	
	int roll = static_cast<int>(random() * 100);
	for (auto item : prob_map)
	{
		if (roll < item.first)
			return item.second;
	}
	return prob_map[0].second;
}
#endif