#include "context.h"
#include <spdlog/spdlog.h>
engine::core::Context::Context(engine::input::InputManager &input_manager, engine::render::Renderer &render, engine::resource::ResourceManager &resource_manager, engine::render::Camera &camera)
    : _input_manager(input_manager), _renderer(render), _resource_manager(resource_manager), _camera(camera)
{
    spdlog::info("Context created");
}
