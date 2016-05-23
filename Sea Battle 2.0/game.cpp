#include "game.h"

/* Global variables */
extern int corX_enemy[2][SHIP_AMOUNT], corY_enemy[2][SHIP_AMOUNT];
extern int MyField[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE], \
           EnemyField[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE];
extern int corX[2][SHIP_AMOUNT], corY[2][SHIP_AMOUNT];
extern Game *igra;

Game::Game()
{
    scene1 = new QGraphicsScene();
    scene2 = new Enemy_scene();
    kletka = new Cell* [2 * SIZE_FIELD_SQUARE * SIZE_FIELD_SQUARE];
    boat = new Ship* [SHIP_AMOUNT];
    my_win = 0;
    comp_win = 0;
    last_hit_x = -1;
    last_hit_y = -1;
    currentMove = false;
    finish = false;
    hit = new QSound("music/hit.wav");
    miss = new QSound("music/miss.wav");
    kill = new QSound("music/kill.wav");
}

void Game::StartGame()
{
    class Ship **ships = new Ship *[SHIP_AMOUNT];

    int k = 0;
    for(int i = 0; i < MAX_PALUBS; i++)
        for(int j = 0; j < (MAX_PALUBS - i); j++)    //j - number of ships with concrete amount of palubs
            ships[k++] = new Ship(i + 1);

    RandomPlacement(0, corX_enemy, corY_enemy, ships);  //to place computer's ships

    for(int i(0); i < SHIP_AMOUNT; i++)
        delete ships[i];
    delete [] ships;

    Transformation();   //to transform coordinates

    currentMove = qrand() % 2;  //to set who starts

    if(!currentMove)
        StepComp();
}

void Game::Filling(int Field[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE], int X[2][SHIP_AMOUNT], int Y[2][SHIP_AMOUNT])
{
    for (int i(0); i < SHIP_AMOUNT; i++)
    {
        int CoordShipX, CoordShipY;
        CoordShipX = X[0][i] / SIZE_PALUB;
        CoordShipY = Y[0][i] / SIZE_PALUB;

        for (int j(0); j < (Y[1][i] - Y[0][i]) / SIZE_PALUB; j++)
            for (int k(0); k < (X[1][i] - X[0][i]) / SIZE_PALUB; k++)
                Field[CoordShipY + j][CoordShipX + k] = BUSY;
    }
}

void Game::Transformation()
{
    for (int i(0); i < SIZE_FIELD_SQUARE; i++)                  //start position of field`s arrays
        for (int j(0); j < SIZE_FIELD_SQUARE; j++)
        {
            MyField[i][j] = EMPTY;
            EnemyField[i][j] = EMPTY;
        }

    Filling(MyField, corX, corY);
    Filling(EnemyField, corX_enemy, corY_enemy);
}

void Game::RandomPlacement(int numShip, int arrX[2][SHIP_AMOUNT], int arrY[2][SHIP_AMOUNT], Ship **ships)
{
    if (numShip == SHIP_AMOUNT) //if all ships placed
        return;

    if(qrand() % 2) //randomly turn the ship
    {
        int temp = ships[numShip]->shipWid;
        ships[numShip]->shipWid = ships[numShip]->shipLen;
        ships[numShip]->shipLen = temp;
    }

    static int count = 0;   //counter of attempts

    ships[numShip]->coord_x = qrand() % SIZE_FIELD_SQUARE * SIZE_PALUB;
    ships[numShip]->coord_y = qrand() % SIZE_FIELD_SQUARE * SIZE_PALUB;

    if (count > 50)                             //if impossible(attempts > 50) to place the ship, than replace previous ship
    {
        arrX[0][numShip] = 0;
        arrY[0][numShip] = 0;
        arrX[1][numShip] = ships[numShip]->shipWid;
        arrY[1][numShip] = ships[numShip]->shipLen;
        count = 0;
        RandomPlacement(--numShip, arrX, arrY, ships);
    }
    else if(!ships[numShip]->CheckOfPlacement(ships[numShip]->coord_x, ships[numShip]->coord_y, arrX, arrY))  //to set the ship and go to next ship
    {
        count = 0;
        RandomPlacement(++numShip, arrX, arrY, ships);
    }
    else    //try to place the ship again
    {
        count++;
        arrX[0][numShip] = 0;
        arrY[0][numShip] = 0;
        arrX[1][numShip] = ships[numShip]->shipWid;
        arrY[1][numShip] = ships[numShip]->shipLen;
        RandomPlacement(numShip, arrX, arrY, ships);
    }
}
