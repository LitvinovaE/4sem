#ifndef SHIP_H
#define SHIP_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include "const.h"

class Ship: public QGraphicsItem
{
public:
    int coord_x, coord_y;               //coordinates of left top corner
    int numShip;                        //number of ship
    int numPalubs;                      //number of palubs
    int shipLen;                        //length of ship
    int shipWid;                        //width of ship
    bool Pressed;                       //a mouse click on the ship
    bool Changed;                       //turn the ship
    bool Moved;                         //changing the position of the ship
public:
    Ship(int numOfPalubs);
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    int CheckOfPlacement(qreal x, qreal y, int arrX[2][SHIP_AMOUNT], int arrY[2][SHIP_AMOUNT]);        //check of ship`s placement

/* control the ship with the mouse */
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SHIP_H
