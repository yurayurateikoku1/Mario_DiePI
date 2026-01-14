#pragma once
#include "../render/sprite.h"
#include "component.h"
#include "../utils/alignment.h"
#include <optional>
#include <SDL3/SDL_rect.h>
#include <glm/vec2.hpp>
namespace engine::core
{
    class Context;
}

namespace engine::resource
{
    class ResourceManager;
}

namespace engine::component
{
    class TransformComponent;

    class SpriteComponent final : public engine::component::Component
    {
        friend class engine::object::GameObject;

    private:
        engine::resource::ResourceManager *_resourceManager{nullptr};
        TransformComponent *_transform{nullptr};

        /// @brief 纹理对象
        engine::render::Sprite _sprite;
        /// @brief 对齐方式
        engine::utils::Alignment _alignment = engine::utils::Alignment::NONE;
        glm::vec2 _sprite_size{0.0f, 0.0f};
        glm::vec2 _offset{0.0f, 0.0f};
        /// @brief 是否隐藏
        bool _is_hidden = false;

    public:
        SpriteComponent(const std::string &texture_id,
                        engine::resource::ResourceManager &resource_manager,
                        engine::utils::Alignment alignment = engine::utils::Alignment::NONE,
                        std::optional<SDL_Rect> source_rect = std::nullopt,
                        bool is_flipped = false);

        SpriteComponent(engine::render::Sprite &&sprite,
                        engine::resource::ResourceManager &resource_manager,
                        engine::utils::Alignment alignment = engine::utils::Alignment::NONE);
        ~SpriteComponent() override = default;
        SpriteComponent(const SpriteComponent &) = delete;
        SpriteComponent &operator=(const SpriteComponent &) = delete;
        SpriteComponent(SpriteComponent &&) = delete;
        SpriteComponent &operator=(SpriteComponent &&) = delete;

        /// @brief 更新偏移量(根据alignment和sprite_size计算offset)
        void updateOffset();

        const engine::render::Sprite &getSprite() const { return _sprite; }
        const std::string &getTextureId() const { return _sprite.getTextureId(); }
        bool isFlipped() const { return _sprite.isFlipped(); }
        bool isHidden() const { return _is_hidden; }
        const glm::vec2 &getOffset() const { return _offset; }
        const glm::vec2 &getSpriteSize() const { return _sprite_size; }
        engine::utils::Alignment getAlignment() const { return _alignment; }

        void setSpriteById(const std::string &texture_id, const std::optional<SDL_Rect> &source_rect = std::nullopt);
        void setSourceRect(const std::optional<SDL_Rect> &source_rect_opt);
        void setFlipped(bool is_flipped) { _sprite.setFlipped(is_flipped); };
        void setAlignment(engine::utils::Alignment anchor);
        void setHidden(bool is_hidden) { _is_hidden = is_hidden; };

    private:
        void updateSpriteSize();

        void init() override;
        void update(float dt, engine::core::Context &context) override {};
        void render(engine::core::Context &context) override;
    };

}
