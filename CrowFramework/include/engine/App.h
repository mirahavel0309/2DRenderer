#pragma once

namespace engine
{
    class Game;

    class App
    {
    public:
        App(int width, int height, const char* title);
        ~App();

        int Run(Game& game);

    private:
        void* mWindow = nullptr;

        int mWidth = 0;
        int mHeight = 0;
        const char* mTitle = nullptr;

    private:
        bool Init();
        void Shutdown();

        bool InitGL();

        void FrameBegin();
        void FrameEnd();

        float CalcDeltaTime();
    };
}