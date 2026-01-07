#include "game_scene.h"
#include "../../engine/scene/level_loader.h"
#include "../../engine/input/input_manager.h"
#include "../../engine/core/context.h"
#include "../../engine/component/transform_component.h"
#include "../../engine/component/sprite_component.h"
#include "../../engine/object/game_object.h"
#include "../../engine/render/camera.h"
#include <spdlog/spdlog.h>
#include <SDL3/SDL_rect.h>

game::scene::GameScene::GameScene(const std::string &name, engine::core::Context &context, engine::scene::SceneManager &scene_manager)
    : Scene(name, context, scene_manager)
{
    spdlog::info("GameScene created");
}

void game::scene::GameScene::init()
{
    engine::scene::LevelLoader level_loader;
    level_loader.loadLevel("assets/maps/level1.tmj", *this);
    createTestObject();
    Scene::init();
}

void game::scene::GameScene::update(float dt)
{
    Scene::update(dt);
}

void game::scene::GameScene::render()
{
    Scene::render();
}

void game::scene::GameScene::handleInput()
{
    Scene::handleInput();
    testCamera();
}

void game::scene::GameScene::clean()
{
    Scene::clean();
}

void game::scene::GameScene::createTestObject()
{
    auto test_object = std::make_unique<engine::object::GameObject>("TestObject");
    test_object->addComponent<engine::component::TransformComponent>(glm::vec2(100.0f, 100.0f));
    test_object->addComponent<engine::component::SpriteComponent>("assets/textures/Props/big-crate.png", _context.getResourceManager(), engine::utils::Alignment::CENTER);
    addGameObject(std::move(test_object));
}

void game::scene::GameScene::testCamera()
{
    auto &camera = _context.getCamera();
    auto &input_manager = _context.getInputManager();

    if (input_manager.isActionDown("move_down"))
    {
        spdlog::info("move_down detected, camera position: {}, {}", camera.getPosition().x, camera.getPosition().y);
        camera.move(glm::vec2(0.0f, 1.0f));
    }
    if (input_manager.isActionDown("move_up"))
    {
        spdlog::info("move_up detected, camera position: {}, {}", camera.getPosition().x, camera.getPosition().y);
        camera.move(glm::vec2(0.0f, -1.0f));
    }
    if (input_manager.isActionDown("move_right"))
    {
        spdlog::info("move_right detected, camera position: {}, {}", camera.getPosition().x, camera.getPosition().y);
        camera.move(glm::vec2(1.0f, 0.0f));
    }
    if (input_manager.isActionDown("move_left"))
    {
        spdlog::info("move_left detected, camera position: {}, {}", camera.getPosition().x, camera.getPosition().y);
        camera.move(glm::vec2(-1.0f, 0.0f));
    }
}
