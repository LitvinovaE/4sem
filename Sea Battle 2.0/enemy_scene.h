#ifndef ENEMY_SCENE_H
#define ENEMY_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QSound>
#include "cell.h"
#include "mainwindow.h"
#include "const.h"

class Enemy_scene : public QGraphicsScene
{
    Q_OBJECT
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event); //click on enemy's scene
};

#endif // ENEMY_SCENE_H
