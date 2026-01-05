#pragma once
namespace engine::object
{
    class GameObject;
}
namespace engine::core
{
    class Context;
}
namespace engine::component
{

    class Component
    {
        friend class engine::object::GameObject;

    protected:
        engine::object::GameObject *_owner{nullptr};

    private:
        /* data */
    public:
        Component(/* args */) = default;
        virtual ~Component() = default;
        Component(const Component &) = delete;
        Component(Component &&) = delete;
        Component &operator=(const Component &) = delete;
        Component &operator=(Component &&) = delete;

        void setOwner(engine::object::GameObject *owner) { _owner = owner; }
        engine::object::GameObject *getOwner() const { return _owner; }

    protected:
        virtual void init() {}
        /// @brief 处理输入
        virtual void handleInput(engine::core::Context &) {}
        /// @brief 更新
        /// @param dt
        virtual void update(float dt, engine::core::Context &) {}
        /// @brief 渲染
        virtual void render(engine::core::Context &) {}
        /// @brief 清除
        virtual void clean() {}
    };

} // namespace engine::component
