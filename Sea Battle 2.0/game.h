#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QSound>
#include "const.h"
#include "ship.h"
#include "cell.h"
#include "enemy_scene.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    Game();
    class Cell **kletka;
    QGraphicsScene *scene1;
    class Enemy_scene *scene2;
    class Ship **boat;
    int my_win;                     //counter of my win
    int comp_win;                   //counter of computer's win
    int last_hit_x;                 //for game with computer
    int last_hit_y;                 //for game with computer
    bool currentMove;               //true - we, false - opponent
    int difficultly_level;          //flag of difficultly level
    QSound *hit, *miss, *kill;      //music
    bool finish;                    //flag of completed game
    void StartGame();
    void Filling(int Field[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE], int X[2][SHIP_AMOUNT], int Y[2][SHIP_AMOUNT]); //filling new arrays
    void Transformation();               //transform types of coordinates
    void RandomPlacement(int numShip, int arrX[2][SHIP_AMOUNT], int arrY[2][SHIP_AMOUNT], Ship **ships);
};

#endif // GAME_H
