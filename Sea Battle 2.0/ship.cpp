#include "ship.h"

/* Global variables */
extern int corX[2][SHIP_AMOUNT], corY[2][SHIP_AMOUNT];

Ship::Ship(int numOfPalubs)
{
    static int count = 0;

    if (count == SHIP_AMOUNT)
        count = 0;

    Pressed = false;
    Changed = false;
    Moved = false;
    numPalubs = numOfPalubs;
    numShip = count++;
    shipLen = SIZE_PALUB;
    shipWid = SIZE_PALUB * numOfPalubs;
    coord_x = x();
    coord_y = y();

    setFlags(QGraphicsItem::ItemIsSelectable |
                QGraphicsItem::ItemIsMovable |
                QGraphicsItem::ItemSendsGeometryChanges);
}

QRectF Ship::boundingRect() const
{
    return QRectF(0, 0, shipWid, shipLen);
}

void Ship::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget)
    Q_UNUSED (option)

    if(Changed)                 //turn the ship
    {
        int temp = shipWid;
        shipWid = shipLen;
        shipLen = temp;
    }
    QRectF object = boundingRect();
    QBrush brush(Qt::red);
    prepareGeometryChange();
    Changed = false;
    if(Pressed)
        brush.setColor(Qt::darkRed);
    painter->fillRect(object,brush);
    painter->drawRect(object);
}

void Ship::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;

    update();
    QGraphicsItem::mousePressEvent(event);
}

void Ship::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    Moved = true;

    CheckOfPlacement(x(), y(), corX, corY);
    setPos(coord_x, coord_y);

    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

int Ship::CheckOfPlacement(qreal x, qreal y, int arrX[2][SHIP_AMOUNT], int arrY[2][SHIP_AMOUNT])
{
    /* for field */

    if (x < 0)
        coord_x = 0;
    else if (x + shipWid > SIZE_FIELD)
        coord_x = SIZE_FIELD - shipWid;
    else
        coord_x = (int)(x / SIZE_PALUB) * SIZE_PALUB;

    if (y < 0)
        coord_y = 0;
    else if (y + shipLen > SIZE_FIELD)
        coord_y = SIZE_FIELD - shipLen;
    else
        coord_y = ((int)(y) / SIZE_PALUB) * SIZE_PALUB;

    arrX[0][numShip] = coord_x;
    arrY[0][numShip] = coord_y;
    arrX[1][numShip] = coord_x + shipWid;
    arrY[1][numShip] = coord_y + shipLen;

    /* for ships */

    for (int i = 0; i < SHIP_AMOUNT; i++)
    {
        if (i == numShip)
            continue;

        if((coord_x + shipWid > arrX[0][i] - SIZE_PALUB) && (coord_x < arrX[1][i] + SIZE_PALUB) && \
           (coord_y + shipLen > arrY[0][i] - SIZE_PALUB) && (coord_y < arrY[1][i] + SIZE_PALUB))
        {
            coord_x = 0;
            coord_y = 0;
            arrX[0][numShip] = 0;
            arrY[0][numShip] = 0;
            arrX[1][numShip] = shipWid;
            arrY[1][numShip] = shipLen;
            return ERROR;
        }
    }
    return OK;
}

void Ship::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Changed = true;
    update();
    QGraphicsItem::mouseDoubleClickEvent(event);
}
