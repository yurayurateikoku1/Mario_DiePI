#pragma once
#include <nlohmann/json_fwd.hpp>

namespace engine::scene
{
    class Scene;

    class LevelLoader final
    {
    public:
        LevelLoader() = default;

        bool loadLevel(const std::string &map_path, Scene &scene);

    private:
        std::string _map_path;

        void loadImageLayer(const nlohmann::json &layer_json, Scene &scene);
        void loadTileLayer(const nlohmann::json &layer_json, Scene &scene);
        void loadObjectLayer(const nlohmann::json &layer_json, Scene &scene);

        std::string resolvePath(const std::string &file_path);
    };
}