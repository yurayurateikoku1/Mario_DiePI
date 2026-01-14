#include "sprite.h"

engine::render::Sprite::Sprite(const std::string &texture_id, std::optional<SDL_Rect> source_rect, bool is_flipped)
    : _texture_id(texture_id), _source_rect(source_rect), _is_flipped(is_flipped)
{
}