#include "engine/App.h"
#include "game/VNGame.h"

int main()
{
    engine::App app(1920, 1080, "Project VN");
    engine::VNGame game;
    return app.Run(game);
}