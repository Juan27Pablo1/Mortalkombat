#ifndef _ESTADO_JUEGO_HPP
#define _ESTADO_JUEGO_HPP

#include "graphics.h"
#include "input_device.h"
#include "audio.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <array>

class Fighter;
class GameState
{
public:
	GameState();
	enum State { ROUND_START, FIGHT_W_TEXT, FIGHT, ROUND_END, GAME_OVER_A, GAME_OVER_B, GAME_OVER, PAUSE };
	void init(int fighter_a, bool ai_a, int fighter_b, bool ai_b,
		bones::GraphicsLoader& loader,
		InputDevice* device1,
		InputDevice* device2);
	void handle_input(SDL_Event& event);
	void tick();
	void render(SDL_Renderer *renderer);
	void setup_round();
	bool is_complete();

private:
	std::unique_ptr<Fighter> fighter_a;
	std::unique_ptr<Fighter> fighter_b;
	std::array<InputDevice*, 2> input_devices;
	bool fighter_a_ai, fighter_b_ai;
	bones::Sprite stage;
	State state;
	SDL_Rect camera;
	int time;
	int ticks = 0;
	int round = 0;
	int fighter_a_wins = 0;
	int fighter_b_wins = 0;
	TTF_Font* font;
	SDL_Texture* timer;
	SDL_Texture* round_text;
	void draw_timer(SDL_Renderer* renderer);
	void draw_round_text(SDL_Renderer* renderer);
	void do_round_end(int winner);
	bool complete = false;
	bones::AudioClip round1, round2, round3, fight;
	bool fightsound_played = false;
};

#endif