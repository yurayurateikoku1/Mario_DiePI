#include "sprite_component.h"
#include "transform_component.h"
#include <spdlog/spdlog.h>
#include "../resource/resource_manager.h"
#include "../render/render.h"
#include "../render/camera.h"
#include "../core/context.h"
#include "../object/game_object.h"
engine::component::SpriteComponent::SpriteComponent(const std::string &texture_id, engine::resource::ResourceManager &resource_manager, engine::utils::Alignment alignment, std::optional<SDL_Rect> source_rect_opt, bool is_flipped)
    : _resourceManager(&resource_manager), _alignment(alignment), _sprite(texture_id, source_rect_opt, is_flipped)
{
    if (!_resourceManager)
    {
        spdlog::error("ResourceManager is not initialized.");
    }
}

void engine::component::SpriteComponent::updateOffset()
{
    if (_sprite_size.x <= 0 || _sprite_size.y <= 0)
    {
        /* code */
        _offset = {0.0f, 0.0f};
        return;
    }
    auto scale = _transform->getScale();
    switch (_alignment)
    {
    case engine::utils::Alignment::TOP_LEFT:
        _offset = glm::vec2{0.0f, 0.0f} * scale;
        break;
    case engine::utils::Alignment::TOP_CENTER:
        _offset = glm::vec2{-_sprite_size.x / 2.0f, 0.0f} * scale;
        break;
    case engine::utils::Alignment::TOP_RIGHT:
        _offset = glm::vec2{-_sprite_size.x, 0.0f} * scale;
        break;
    case engine::utils::Alignment::CENTER_LEFT:
        _offset = glm::vec2{0.0f, -_sprite_size.y / 2.0f} * scale;
        break;
    case engine::utils::Alignment::CENTER:
        _offset = glm::vec2{-_sprite_size.x / 2.0f, -_sprite_size.y / 2.0f} * scale;
        break;
    case engine::utils::Alignment::CENTER_RIGHT:
        _offset = glm::vec2{-_sprite_size.x, -_sprite_size.y / 2.0f} * scale;
        break;
    case engine::utils::Alignment::BOTTOM_LEFT:
        _offset = glm::vec2{0.0f, -_sprite_size.y} * scale;
        break;
    case engine::utils::Alignment::BOTTOM_CENTER:
        _offset = glm::vec2{-_sprite_size.x / 2.0f, -_sprite_size.y} * scale;
        break;
    case engine::utils::Alignment::BOTTOM_RIGHT:
        _offset = glm::vec2{-_sprite_size.x, -_sprite_size.y} * scale;
        break;
    default:
        break;
    }
}

void engine::component::SpriteComponent::setSpriteById(const std::string &texture_id, const std::optional<SDL_Rect> &source_rect)
{
    _sprite.setTextureId(texture_id);
    _sprite.setSourceRect(source_rect);
    updateSpriteSize();
    updateOffset();
}

void engine::component::SpriteComponent::setSourceRect(const std::optional<SDL_Rect> &source_rect_opt)
{
    _sprite.setSourceRect(source_rect_opt);
    updateSpriteSize();
    updateOffset();
}

void engine::component::SpriteComponent::setAlignment(engine::utils::Alignment anchor)
{
    _alignment = anchor;
    updateOffset();
}

void engine::component::SpriteComponent::updateSpriteSize()
{
    if (!_resourceManager)
    {
        spdlog::error("ResourceManager is not initialized.");
        return;
    }
    if (_sprite.getSourceRect().has_value())
    {
        const auto &src_rect = _sprite.getSourceRect().value();
        _sprite_size = {src_rect.w, src_rect.h};
    }
    else
    {
        _sprite_size = _resourceManager->getTextureSize(_sprite.getTextureId());
    }
}

void engine::component::SpriteComponent::init()
{
    if (!_owner)
    {
        spdlog::error("SpriteComponent: Owner is not set.");
        return;
    }
    _transform = _owner->getComponent<engine::component::TransformComponent>();
    if (!_transform)
    {
        spdlog::warn("GameObject {} does not have a TransformComponent.", _owner->getName());
        return;
    }
    updateSpriteSize();
    updateOffset();
}

void engine::component::SpriteComponent::render(engine::core::Context &context)
{
    if (_is_hidden || !_transform || !_resourceManager)
    {
        return;
    }

    const glm::vec2 &position = _transform->getPosition() + _offset;
    const glm::vec2 &scale = _transform->getScale();
    const float rotation = _transform->getRotation();
    context.getRender().drawSprite(context.getCamera(), _sprite, position, scale, rotation);
}
