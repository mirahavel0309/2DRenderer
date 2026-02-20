#pragma once

namespace engine
{
    class Game
    {
    public:
        virtual ~Game() = default;

        virtual bool Load() { return true; }
        virtual void Update(float dt) { (void)dt; }
        virtual void Render() {}
        virtual void Unload() {}
    };
}