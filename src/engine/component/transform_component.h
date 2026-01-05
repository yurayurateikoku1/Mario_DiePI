#pragma once
#include "component.h"
#include <glm/glm.hpp>
#include <utility>

namespace engine::component
{
    /// @brief 管理GameObject的位置，旋转和缩放
    class TransformComponent : public Component
    {
        friend class engine::object::GameObject;

    public:
        glm::vec2 _position{0.0f, 0.0f};
        glm::vec2 _scale{1.0f, 1.0f};
        float _rotation{0.0f};
        TransformComponent(const glm::vec2 &position = {0.0f, 0.0f}, const glm::vec2 &scale = {1.0f, 1.0f}, float rotation = 0.0f) : _position(position), _scale(scale), _rotation(rotation) {};

        TransformComponent(const TransformComponent &) = delete;
        TransformComponent &operator=(const TransformComponent &) = delete;
        TransformComponent(TransformComponent &&) = delete;
        TransformComponent &operator=(TransformComponent &&) = delete;

        const glm::vec2 &getPosition() const { return _position; };
        const glm::vec2 &getScale() const { return _scale; };
        float getRotation() const { return _rotation; };
        void setPosition(const glm::vec2 &position) { _position = position; };
        void setScale(const glm::vec2 &scale);
        void setRotation(float rotation) { _rotation = rotation; };
        /// @brief 平移
        /// @param offset
        void translate(const glm::vec2 &offset) { _position += offset; };

    private:
        void update(float dt, engine::core::Context &) override {}
    };
}