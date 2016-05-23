#include "mainwindow.h"
#include <iostream>
#include <QSound>
#include "const.h"
#include "game.h"
#include "ship.h"
#include "choose_level.h"
#include "scenes.h"

/* Global variables */
Scenes* b;
int corX_enemy[2][SHIP_AMOUNT], corY_enemy[2][SHIP_AMOUNT]; //arrays of ship`s coordinates of enemy
int MyField[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE], \
    EnemyField[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE];       //arrays of ship, which wrote with help of flags 0-3
Game *igra;
int corX[2][SHIP_AMOUNT], corY[2][SHIP_AMOUNT];             //arrays of ship`s coordinates

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    b = new Scenes();
    b->show_FirstWindow();

    return a.exec();
}
