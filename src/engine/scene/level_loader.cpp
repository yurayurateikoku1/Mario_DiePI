#include "level_loader.h"
#include "../component/transform_component.h"
#include "../component/sprite_component.h"
#include "../component/parallax_component.h"
#include "../scene/scene.h"
#include "../core/context.h"
#include "../resource/resource_manager.h"
#include "../render/sprite.h"
#include "../utils/math.h"
#include "../object/game_object.h"

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <fstream>
#include <glm/vec2.hpp>
#include <filesystem>
bool engine::scene::LevelLoader::loadLevel(const std::string &map_path, Scene &scene)
{
    _map_path = map_path;
    std::ifstream map_file(map_path);
    if (!map_file.is_open())
    {
        spdlog::error("Failed to open map file: {}", map_path);
        return false;
    }
    nlohmann::json json_data;
    try
    {
        /* code */
        map_file >> json_data;
    }
    catch (const std::exception &e)
    {
        spdlog::error("Failed to parse map file: {},{},{},{}", map_path, e.what(), __FILE__, __LINE__);
        return false;
    }
    if (!json_data.contains("layers") || !json_data["layers"].is_array())
    {
        /* code */
        spdlog::error("Invalid map file: {}", map_path);
        return false;
    }

    for (const auto &layer_json : json_data["layers"])
    {
        std::string layer_type = layer_json.value("type", "none");
        if (!layer_json.value("visible", true))
        {
            /* code */
            spdlog::info("Skipping invisible layer: {}", layer_type);
            continue;
        }
        if (layer_type == "imagelayer")
        {
            loadImageLayer(layer_json, scene);
        }
        else if (layer_type == "tilelayer")
        {
            loadTileLayer(layer_json, scene);
        }
        else if (layer_type == "objectgroup")
        {
            loadObjectLayer(layer_json, scene);
        }
        else
        {
            spdlog::warn("Unknown layer type: {}", layer_type);
        }
    }
    spdlog::info("Map file loaded: {}", map_path);
    return true;
}

void engine::scene::LevelLoader::loadImageLayer(const nlohmann::json &layer_json, Scene &scene)
{
    const std::string &file_path = layer_json.value("image", "");
    if (file_path.empty())
    {
        /* code */
        spdlog::warn("Image layer has no image file");
        return;
    }
    auto texture_id = resolvePath(file_path);
    const glm::vec2 offset = glm::vec2(layer_json.value("offsetx", 0.0f), layer_json.value("offsety", 0.0f));

    const glm::vec2 scroll_factor = glm::vec2(layer_json.value("parallaxx", 1.0f), layer_json.value("parallaxy", 1.0f));
    const glm::bvec2 repeat = glm::bvec2(layer_json.value("repeatx", false), layer_json.value("repeaty", false));

    const std::string &layer_name = layer_json.value("name", "Unamed");

    auto game_object = std::make_unique<engine::object::GameObject>(layer_name);
    game_object->addComponent<engine::component::TransformComponent>(offset);
    game_object->addComponent<engine::component::ParallaxComponent>(texture_id, scroll_factor, repeat);
    scene.addGameObject(std::move(game_object));
    spdlog::info("Image layer loaded: {}", file_path);
}
void engine::scene::LevelLoader::loadTileLayer(const nlohmann::json &layer_json, Scene &scene)
{
}

void engine::scene::LevelLoader::loadObjectLayer(const nlohmann::json &layer_json, Scene &scene)
{
}

std::string engine::scene::LevelLoader::resolvePath(const std::string &file_path)
{
    try
    {
        auto map_dir = std::filesystem::path(_map_path).parent_path();
        auto final_path = std::filesystem::canonical(map_dir / file_path);

        return final_path.string();
    }
    catch (const std::exception &e)
    {
        spdlog::error("Failed to resolve path: {},{},{},{}", file_path, e.what(), __FILE__, __LINE__);
        return file_path;
    }
}
