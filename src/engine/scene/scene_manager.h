#pragma once
#include <memory>
#include <vector>

namespace engine::core
{
    class Context;
}

namespace engine::scene
{
    class Scene;

    /// @brief 场景管理器,管理和切换场景
    class SceneManager final
    {
    private:
        engine::core::Context &_context;
        std::vector<std::unique_ptr<Scene>> _scenes_stack;

        /// @brief 待处理的动作
        enum class PendingAction
        {
            None,
            Push,
            Pop,
            Replace
        };
        PendingAction _pending_action{PendingAction::None};
        /// @brief 待处理的场景
        std::unique_ptr<Scene> _pending_scene;

    public:
        explicit SceneManager(engine::core::Context &context);
        ~SceneManager();

        SceneManager(const SceneManager &) = delete;
        SceneManager(SceneManager &&) = delete;
        SceneManager &operator=(const SceneManager &) = delete;
        SceneManager &operator=(SceneManager &&) = delete;

        /// @brief  请求压入场景
        /// @param scene
        void requestPushScene(std::unique_ptr<Scene> &&scene);
        /// @brief  请求弹出场景
        void requestPopScene();
        /// @brief  请求替换场景
        /// @param scene
        void requestReplaceScene(std::unique_ptr<Scene> &&scene);

        Scene *getCurrentScene() const;
        engine::core::Context &getContext() const { return _context; }

        void update(float dt);
        void render();
        void handleInput();
        void close();

    private:
        void processPendingActions();
        void pushScene(std::unique_ptr<Scene> &&scene);
        void popScene();
        void replaceScene(std::unique_ptr<Scene> &&scene);
    };
}