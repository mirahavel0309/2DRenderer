#pragma once

#include "engine/Game.h"

class Shader;

namespace engine
{

    class VNGame : public Game
    {
    public:
        bool Load() override;
        void Render() override;
        void Unload() override;

    private:
        unsigned int mVao = 0;
        unsigned int mVbo = 0;
        Shader* mShader = nullptr;
    };
}