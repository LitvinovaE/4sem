#ifndef SCENES_H
#define SCENES_H

#include "mainwindow.h"
#include "choose_level.h"

class Scenes
{
public:
    Scenes();
    void show_MainWindow(); //show Main window
    void show_FirstWindow(); //show First window
    QSound *main;   //music
private:
    class MainWindow* w;
    class Choose_level* cl;
};

#endif // SCENES_H
