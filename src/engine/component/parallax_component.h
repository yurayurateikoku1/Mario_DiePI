#pragma once
#include "component.h"
#include "../render/sprite.h"
#include <string>
#include <glm/vec2.hpp>

namespace engine::component
{
    class TransformComponent;
    /// @brief 在背景中渲染视差滚动的贴图，根据相机的位置和视差滚动因子进行移动
    class ParallaxComponent : public Component
    {
        friend class engine::object::GameObject;

    private:
        /// @brief 缓存变换组件
        TransformComponent *_transform{nullptr};

        engine::render::Sprite _sprite;
        glm::vec2 _scroll_factor{1.0f, 1.0f};
        glm::bvec2 _repeat;
        bool _is_hidden = false;

    public:
        ParallaxComponent(const std::string &texture_id, const glm::vec2 &scroll_factor, const glm::bvec2 &repeat);

        void setSprite(const engine::render::Sprite &sprite) { _sprite = sprite; }
        void setScrollFactor(const glm::vec2 &scroll_factor) { _scroll_factor = scroll_factor; }
        void setRepeat(const glm::bvec2 &repeat) { _repeat = repeat; }
        void setIsHidden(bool is_hidden) { _is_hidden = is_hidden; }

        const engine::render::Sprite &getSprite() const { return _sprite; }
        const glm::vec2 &getScrollFactor() const { return _scroll_factor; }
        const glm::bvec2 &getRepeat() const { return _repeat; }
        bool getIsHidden() const { return _is_hidden; }

    protected:
        void update(float dt, engine::core::Context &) override {}
        void init() override;
        void render(engine::core::Context &) override;
    };
}