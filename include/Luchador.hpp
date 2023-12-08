#ifndef _LUCHADOR_HPP
#define _LUCHADOR_HPP

#include "Luchador_animator.h"
#include "fighter_state_machine.h"
#include "projectile.h"

#include <vector>
#include <map>
#include <memory>
#include <string>

class Fighter
{
public:
	Fighter(FighterAnimator &animator);
	Fighter(const Fighter& other);
	Fighter& operator = (const Fighter& other) = delete;

	/* Gets the top left coords of starting position of current animation frame.
	 * Needed to adjust collision box positions and drawing positions.
	 */
	int topleft_x();
	int topleft_y();

	Orientation get_orientation();
	bones::Animation* get_animation();
	FighterStateMachine* get_state();
	void set_state(FighterStateMachine::State state, void* data = nullptr);

	void move_left();
	void move_right();
	void jump();

	int get_velocity_x();
	void set_velocity_x(int val);
	int get_velocity_y();
	void set_velocity_y(int val);
	
	int get_position_x();
	void set_position_x(int val);
	int get_position_y();
	void set_position_y(int val);

	bool is_airborne();

	int get_health() const;
	void set_health(int value);

	void set_graphics(FighterGraphics graphics);
	void flip_orientation();

	void add_projectile(std::unique_ptr<Projectile> projectile);
	std::vector<std::unique_ptr<Projectile>>* get_projectiles();

	void tick();
	void draw(SDL_Renderer* renderer, const SDL_Rect& camera);
	FightMove& get_fightmove() const;
	void add_fightmove(const std::string& key, std::shared_ptr<FightMove> move);
	void perform_fightmove(const std::string& move);

protected:
	int x, y;
	int x_vel, y_vel;
	int health;
	bool airborne;
	FighterAnimator animator;
	std::unique_ptr<FighterStateMachine> state_machine;
	Orientation orientation;
	std::vector<std::unique_ptr<Projectile>> projectiles;
	FightMove* current_fightmove;
	std::map<std::string, std::shared_ptr<FightMove>> fightmoves;

private:
	int gravity_counter{ 0 };
	void apply_gravity();
	void init_common_fightmoves();
	void perform_fightmove(FightMove& move);
};

void face(Fighter& fighter, int x);
#endif