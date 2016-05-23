#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include "const.h"

class Cell : public QGraphicsItem
{
public:
    int x, y;   //coordinates of the cell
    bool cur;   //igra->currentMove
public:
    Cell(int coord_x, int coord_y, bool point);
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
};

#endif // CELL_H
