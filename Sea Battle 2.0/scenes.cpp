#include "scenes.h"

Scenes::Scenes()
{
    w = new MainWindow();
    cl = new Choose_level();
    main = new QSound("music/main.wav");
    main->setLoops(-1); //the eternal playing music
}

void Scenes::show_MainWindow()
{
    w->show();
    cl->hide();
}

void Scenes::show_FirstWindow()
{
    cl->show();
    w->hide();
    w->CreateNewGame();
    main->play();
}
