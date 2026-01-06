#include "scene_manager.h"
#include <spdlog/spdlog.h>
#include "scene.h"
#include "../core/context.h"
engine::scene::SceneManager::SceneManager(engine::core::Context &context)
    : _context(context)
{
    spdlog::info("SceneManager created");
}

engine::scene::SceneManager::~SceneManager()
{
    spdlog::info("SceneManager destroyed");
    close();
}

void engine::scene::SceneManager::requestPushScene(std::unique_ptr<Scene> &&scene)
{
    _pending_action = PendingAction::Push;
    _pending_scene = std::move(scene);
}

void engine::scene::SceneManager::requestPopScene()
{
    _pending_action = PendingAction::Pop;
}

void engine::scene::SceneManager::requestReplaceScene(std::unique_ptr<Scene> &&scene)
{
    _pending_action = PendingAction::Replace;
    _pending_scene = std::move(scene);
}

engine::scene::Scene *engine::scene::SceneManager::getCurrentScene() const
{
    if (_scenes_stack.empty())
        return nullptr;

    return _scenes_stack.back().get();
}

void engine::scene::SceneManager::update(float dt)
{
    Scene *current_scene = getCurrentScene();
    if (current_scene)
    {
        current_scene->update(dt);
    }
    processPendingActions();
}

void engine::scene::SceneManager::render()
{
    for (const auto &scene : _scenes_stack)
    {
        /* code */
        if (scene)
            scene->render();
    }
}

void engine::scene::SceneManager::handleInput()
{
    Scene *current_scene = getCurrentScene();
    if (current_scene)
    {
        current_scene->handleInput();
    }
}

void engine::scene::SceneManager::close()
{
    spdlog::info("SceneManager closed");
    while (!_scenes_stack.empty())
    {
        /* code */
        if (_scenes_stack.back())
        {
            /* code */
            spdlog::info("Scene {} closed", _scenes_stack.back()->getName());
            _scenes_stack.back()->clean();
        }
        _scenes_stack.pop_back();
    }
}

void engine::scene::SceneManager::processPendingActions()
{
    if (_pending_action == PendingAction::None)
    {
        /* code */
        return;
    }
    switch (_pending_action)
    {
    case PendingAction::Pop:
        /* code */
        popScene();
        break;
    case PendingAction::Push:
        /* code */
        pushScene(std::move(_pending_scene));
        break;
    case PendingAction::Replace:
        /* code */
        replaceScene(std::move(_pending_scene));
        break;
    default:
        break;
    }
    _pending_action = PendingAction::None;
}

void engine::scene::SceneManager::pushScene(std::unique_ptr<Scene> &&scene)
{
    if (!scene)
    {
        /* code */
        spdlog::warn("Scene is nullptr");
        return;
    }
    spdlog::info("Scene {} pushed", scene->getName());
    if (!scene->getInitialized())
    {
        /* code */
        scene->init();
    }
    _scenes_stack.push_back(std::move(scene));
}

void engine::scene::SceneManager::popScene()
{
    if (_scenes_stack.empty())
    {
        spdlog::warn("Scene stack is empty");
        return;
    }
    spdlog::info("Scene {} popped", _scenes_stack.back()->getName());
    if (_scenes_stack.back())
    {
        /* code */
        _scenes_stack.back()->clean();
    }
    _scenes_stack.pop_back();
}

void engine::scene::SceneManager::replaceScene(std::unique_ptr<Scene> &&scene)
{
    if (!scene)
    {
        /* code */
        spdlog::warn("Scene is nullptr");
        return;
    }
    spdlog::info("Scene {} replaced", scene->getName());
    while (!_scenes_stack.empty())
    {
        /* code */
        if (_scenes_stack.back())
        {
            /* code */
            _scenes_stack.back()->clean();
        }
        _scenes_stack.pop_back();
    }
    if (!scene->getInitialized())
    {
        /* code */
        scene->init();
    }
    _scenes_stack.push_back(std::move(scene));
}
