#ifndef MY_SCENE_H
#define MY_SCENE_H

#include <QGraphicsScene>
#include <QEventLoop>
#include <QTimer>
#include <QSound>
#include <QMessageBox>
#include "cell.h"
#include "const.h"
#include "game.h"

void StepComp();    //when the right of step belongs to computer
int isCrashed(int coord_x, int coord_y, int Field[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE], QGraphicsScene *scene); //check the ship to distruction
void ChooseWay();                      //choose the way to kill the ship
int Kill(int Way);                     //destroy everything on its way
void addCell(int x, int y, QGraphicsScene *scene);
void Delay();

#endif // MY_SCENE_H
