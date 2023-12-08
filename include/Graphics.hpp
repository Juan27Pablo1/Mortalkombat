#ifndef _GRAPHICS_HPP
#define _GRAPHICS_HPP

#include "animation.h"
#include "sprite.h"

#include <SDL.h>
#include <memory>
#include <string>
#include <map>

namespace bones 
{
	class GraphicsLoader
	{
	public:
		GraphicsLoader() = delete;
		GraphicsLoader(GraphicsLoader& rhs) = delete;
		GraphicsLoader(SDL_Renderer* renderer);

		Sprite load_sprite(std::string filepath);
		Animation load_animation(std::string filepath);

	private:
		std::map<std::string, std::shared_ptr<SDL_Texture>> registry;
		SDL_Renderer* renderer;

		bool is_texture_in_registry(std::string filepath);
		std::shared_ptr<SDL_Texture> get_loaded_texture(std::string filepath);
		std::shared_ptr<SDL_Texture> load_new_texture(std::string filepath);
	};
}
#endif