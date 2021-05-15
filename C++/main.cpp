#include "graphics.h"
#include "game.h"
#include "config.h"

void resize(int w, int h) {
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->setWindowDimensions((unsigned int)w, (unsigned int)h);

}
void update(float ms)
{
    //lambanw pisw thn dieuthunsh ston pointer gamr gia na mporw na thn xrhsimopoiw kai xrhsimopoiw thn reinterpret gia na castarw se typoy game ton pointer me ton phinothero tropo
    Game * game = reinterpret_cast<Game *>(graphics::getUserData());
    game->update();
}


void draw()
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->draw();
}

int main()
{
    Game mygame;

    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tutorial");

    graphics::setUserData(&mygame); //pairnw thn dieuthunsh toy mygame

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    mygame.init();
    mygame.setDebugMode(false);
    graphics::startMessageLoop();

    return 0;
}
