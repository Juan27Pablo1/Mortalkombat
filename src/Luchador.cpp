#include "Luchador.h"
#include "Constantes.h" 
#include "common_fightmoves.h"

#include <iostream>

Fighter::Luchador(FighterAnimator& animator)
	: state_machine(std::make_unique<FighterStateMachine>(*this)), animator(animator), current_fightmove(nullptr)
{
	x = y = 0;
	orientation = Orientation::RIGHT;
	x_vel = y_vel = 0;
	health = 100;
	airborne = false;
	init_common_fightmoves();
}

Luchador::Luchador(const Luchador& other)
	: state_machine(std::make_unique<FighterStateMachine>(*this)), animator(other.animator), current_fightmove(nullptr)
{
	x = other.x;
	y = other.y;
	x_vel = other.x_vel;
	y_vel = other.y_vel;
	health = other.health;
	orientation = other.orientation;
	airborne = other.airborne;
	init_common_fightmoves();
}

//TODO: Can prob move these to FighterAnimator
int Fighter::topleft_x()
{
	int w = animator.get_current_animation()->get_current_frame().sheet_clip.w;
	int topleft = x - (w / 2);
	return topleft;
}

int Fighter::topleft_y()
{
	int h = animator.get_current_animation()->get_current_frame().sheet_clip.h;
	int topleft = y - h;
	return topleft;
}

Orientation Fighter::get_orientation()
{
	return orientation;
}

bones::Animation* Fighter::get_animation()
{
	return animator.get_current_animation();
}

FighterStateMachine* Fighter::get_state()
{
	return state_machine.get();
}

void Fighter::set_state(FighterStateMachine::State state, void* data)
{
	state_machine->change_to(state, data);
}

void Fighter::move_left()
{
	x -= 1;
	set_velocity_x(-1);
}

void Fighter::move_right()
{
	x += 1;
	set_velocity_x(1);
}

int Fighter::get_velocity_x()
{
	return x_vel;
}

void Fighter::set_velocity_x(int val)
{
	x_vel = val;
}

int Fighter::get_velocity_y()
{
	return y_vel;
}

void Fighter::set_velocity_y(int val)
{
	y_vel = val;
}

int Fighter::get_position_x()
{
	return x;
}

void Fighter::set_position_x(int val)
{
	x = val;
}

int Fighter::get_position_y()
{
	return y;
}

void Fighter::set_position_y(int val)
{
	y = val;
}

bool Fighter::is_airborne()
{
	return airborne;
}

int Fighter::get_health() const
{
	return health;
}

void Fighter::set_health(int value)
{
	if (state_machine->get_state() != FighterStateMachine::STUN)
		health = value;
	if (health < 0)
		health = 0;
}

void Fighter::set_graphics(FighterGraphics graphics)
{
	animator.set_graphics(graphics);
}

void Fighter::flip_orientation()
{
	if (orientation == Orientation::LEFT)
	{
		orientation = Orientation::RIGHT;
	}
	else if (orientation == Orientation::RIGHT)
	{
		orientation = Orientation::LEFT;
	}
	animator.flip_orientation();
}


void Fighter::add_projectile(std::unique_ptr<Projectile> projectile)
{
	projectiles.push_back(std::move(projectile));
}

std::vector<std::unique_ptr<Projectile>>* Fighter::get_projectiles()
{
	return &projectiles;
}

void Fighter::tick()
{
	apply_gravity();

	x += x_vel;
	if (x < 0)
		x = 0;
	if (x > MAP_WIDTH - 20)
		x = MAP_WIDTH - 20;
	state_machine->tick();
	for (auto& projectile : projectiles)
	{
		if (!projectile->is_dead())
			projectile->tick();
	}
}

void Fighter::draw(SDL_Renderer* renderer, const SDL_Rect& camera)
{
	// "Anchor" of every frame is the bottom-middle.
	// This fixes the animation jumping around on the screen. 
	int draw_x = topleft_x() - camera.x;
	int draw_y = topleft_y() - camera.y;
	animator.play(renderer, draw_x, draw_y);

	for (auto& projectile : projectiles)
	{
		if (!projectile->is_dead())
			projectile->draw(renderer, camera);
	}
}

void Fighter::jump()
{
	if (!airborne)
	{
		set_velocity_y(JUMP_FORCE);
		airborne = true;
	}
}

void Fighter::apply_gravity()
{
	if (gravity_counter > GRAVITY_FRAME_DELAY)
	{
		set_velocity_y(get_velocity_y() + GRAVITY);
		gravity_counter = 0;
	}
	set_position_y(get_position_y() + get_velocity_y());
	if (get_position_y() >= FLOOR_Y)
	{
		set_velocity_y(0);
		set_position_y(FLOOR_Y);
		airborne = false;
	}
	gravity_counter++;
}

void Fighter::add_fightmove(const std::string& key, std::shared_ptr<FightMove> move)
{
	fightmoves[key] = move;
}

FightMove& Fighter::get_fightmove() const
{
	return *current_fightmove;
}

void Fighter::perform_fightmove(FightMove& move)
{
	current_fightmove = &move;
	set_state(FighterStateMachine::State::FIGHT_MOVE, &move);
}

void Fighter::perform_fightmove(const std::string& move)
{
	perform_fightmove(*fightmoves[move]);
}


void Fighter::init_common_fightmoves()
{
	auto standard_effect = std::make_shared<StandardEffect>();
	auto uppercut_effect = std::make_shared<UppercutEffect>();
	fightmoves["low_punch"] = std::make_shared<BasicFightMove>(FighterGraphics::LOW_PUNCH, 5, standard_effect);
	fightmoves["high_punch"] = std::make_shared<BasicFightMove>(FighterGraphics::HIGH_PUNCH, 5, standard_effect);
	fightmoves["low_kick"] = std::make_shared<BasicFightMove>(FighterGraphics::LOW_KICK, 5, standard_effect);
	fightmoves["high_kick"] = std::make_shared<BasicFightMove>(FighterGraphics::HIGH_KICK, 5, standard_effect);
	fightmoves["crouch_kick_low"] = std::make_shared<BasicFightMove>(FighterGraphics::CROUCH_KICK_LOW, 5, standard_effect);
	fightmoves["crouch_kick_high"] = std::make_shared<BasicFightMove>(FighterGraphics::CROUCH_KICK_HIGH, 5, standard_effect);
	fightmoves["uppercut"] = std::make_shared<BasicFightMove>(FighterGraphics::UPPERCUT, 15, uppercut_effect);
	fightmoves["throw"] = std::make_shared<ThrowFightMove>();
	// temporary hack for right now...
	fightmoves["cage_projectile_fightmove"] = std::make_shared<ProjectileFightMove>(FighterGraphics::SPECIAL_0, CAGE_PROJECTILE);
}

void face(Fighter& fighter, int x)
{
	if (fighter.get_state()->is_input_locked())
		return;
	int dx = fighter.get_position_x() - x;
	Orientation orientation = fighter.get_orientation();
	if (dx > 0 && orientation != Orientation::LEFT)
	{
		fighter.flip_orientation();
	}
	if (dx < 0 && orientation != Orientation::RIGHT)
	{
		fighter.flip_orientation();
	}
}