#include "game_scene.h"
#include "../../engine/core/context.h"
#include "../../engine/component/transform_component.h"
#include "../../engine/component/sprite_component.h"
#include "../../engine/object/game_object.h"
#include <spdlog/spdlog.h>
#include <SDL3/SDL_rect.h>

game::scene::GameScene::GameScene(const std::string &name, engine::core::Context &context, engine::scene::SceneManager &scene_manager)
    : Scene(name, context, scene_manager)
{
    spdlog::info("GameScene created");
}

void game::scene::GameScene::init()
{
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
