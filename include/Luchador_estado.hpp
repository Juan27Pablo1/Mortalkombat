#ifndef _FIGHTER_STATE
#define _FIGHTER_STATE

// Which way is fighter facing
enum class Orientation
{
	LEFT,
	RIGHT
};

// Lets us know what kind of fight moves we can transition to from this state.
// i.e Can't do a roundhouse kick if the FightMoveHook is CROUCH.
enum class FightMoveHook {
	NONE,
	STAND,
	CROUCH,
	JUMP
};

class Luchador;
class Luchador_estado_maquina;
class Luchador_estado
{
public:
	virtual ~FighterState() = default;

	virtual void enter(void* data) = 0;
	virtual void tick() = 0;
	virtual void exit() = 0;

	bool is_input_locked() const;
	FightMoveHook get_move_hook() const;

	friend class FighterStateMachine;

protected:
	void lock_input();
	void unlock_input();

	FighterState(FighterStateMachine& machine, FightMoveHook hook); // Only FighterStateMachine can instantiate 
	FighterStateMachine& machine;
	Fighter& fighter;

private:
	bool is_locked{ false };
	FightMoveHook fightmove_hook;
};
#endif