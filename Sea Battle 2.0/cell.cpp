#include "cell.h"

/* Global variables */
extern int EnemyField[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE], \
           MyField[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE];

Cell::Cell(int coord_x, int coord_y, bool point)
{
    x = coord_x;
    y = coord_y;
    cur = point;
}

QRectF Cell::boundingRect() const
{
    return QRectF(0, 0, SIZE_PALUB, SIZE_PALUB);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget)
    Q_UNUSED (option)

    QRectF object = boundingRect();

    QColor color(115, 255, 255);
    QBrush brush(color);

    if(cur)
    {
        if(EnemyField[y / SIZE_PALUB][x / SIZE_PALUB] == HIT)
            brush.setColor(Qt::black);
    }
    else
    {
        if(MyField[y / SIZE_PALUB][x / SIZE_PALUB] == HIT)
            brush.setColor(Qt::black);
    }
    painter->fillRect(object, brush);
    painter->drawRect(object);
}
