#include "my_scene.h"

/* Global variables */
extern int MyField[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE];
extern Game *igra;
extern int EnemyField[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE];
extern int corX_enemy[2][SHIP_AMOUNT], corY_enemy[2][SHIP_AMOUNT];

int isCrashed(int coord_x, int coord_y, int Field[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE], QGraphicsScene *scene)
{
    int x_up = coord_x;
    int y_up = coord_y;
    int x_down = coord_x;
    int y_down = coord_y;

    while ((Field[coord_y][x_up] == HIT) && (x_up > 0))     //can`t shoot around the crushed ship
        if(Field[coord_y][--x_up] == BUSY)
            return 0;

    while ((Field[y_up][coord_x] == HIT) && (y_up > 0))
        if(Field[--y_up][coord_x] == BUSY)
            return 0;

    while ((Field[coord_y][x_down] == HIT) && (x_down < SIZE_FIELD_SQUARE - 1))
        if(Field[coord_y][++x_down] == BUSY)
            return 0;

    while ((Field[y_down][coord_x] == HIT) && (y_down < SIZE_FIELD_SQUARE - 1))
        if(Field[++y_down][coord_x] == BUSY)
            return 0;

    for(int i = y_up; i < y_down + 1; i++)
        for(int j = x_up; j < x_down + 1; j++)
            if((Field[i][j] != HIT) && (Field[i][j] != MISS))
            {
                Field[i][j] = MISS;
                addCell(j, i, scene);
            }
    return 1;
}

void addCell(int x, int y, QGraphicsScene *scene)
{
    static int count = 0;

    igra->kletka[count] = new Cell(x * SIZE_PALUB, y * SIZE_PALUB, igra->currentMove);
    scene->addItem(igra->kletka[count]);
    igra->kletka[count]->setPos(igra->kletka[count]->x, igra->kletka[count]->y);
    count++;

    if(count == 199)
        count = 0;
}

void StepComp()
{
    int x = 0, y = 0;

    if((igra->last_hit_x != -1) && (igra->last_hit_y != -1))
        ChooseWay();
    else
    {
        if(igra->difficultly_level == HARD)
        {
            x = qrand() % SIZE_FIELD_SQUARE;
            y = 4 - ((x + 1) % 4) + (qrand() % 3) * 4;                  //smart rand
            if(y > 9)
                y %= 4;

            int k = 0;
            while((MyField[y][x] == MISS) || (MyField[y][x] == HIT))
            {
                if (k < 500)
                {
                    x = qrand() % SIZE_FIELD_SQUARE;
                    y = 4 - ((x + 1) % 4) + (qrand() % 3) * 4;
                    if(y > 9)
                        y %= 4;
                    k++;
                }
                else
                {
                    igra->difficultly_level = MEDIUM;
                    break;
                }
            }
        }
        if(igra->difficultly_level == MEDIUM)
        {
            x = qrand() % SIZE_FIELD_SQUARE;
            y = 4 - ((x + 3) % 4) + (qrand() % 3) * 4;                  //smart rand
            if(y > 9)
                y %= 4;

            int k = 0;
            while((MyField[y][x] == MISS) || (MyField[y][x] == HIT))
            {
                if(k < 500)
                {
                    x = qrand() % SIZE_FIELD_SQUARE;
                    y = 4 - ((x + 3) % 4) + (qrand() % 3) * 4;
                    if(y > 9)
                        y %= 4;
                    k++;
                }
                else
                {
                    igra->difficultly_level = EASY;
                    break;
                }
            }
        }
        if(igra->difficultly_level == EASY)
        {
            x = qrand() % SIZE_FIELD_SQUARE;
            y = qrand() % SIZE_FIELD_SQUARE;
            int k = 0;
            while(((MyField[y][x] == MISS) || (MyField[y][x] == HIT)) && (k < 500))
            {
                x = qrand() % SIZE_FIELD_SQUARE;
                y = qrand() % SIZE_FIELD_SQUARE;
                k++;
            }
            if(k == 500)
            {
                for(int i(0); i < SIZE_FIELD_SQUARE; i++)
                    for(int j(0); j < SIZE_FIELD_SQUARE; j++)
                    {
                        if((MyField[i][j] == EMPTY) || (MyField[i][j] == BUSY))
                        {
                            x = j;
                            y = i;
                        }
                    }
            }
        }

        if(MyField[y][x] == EMPTY)
        {
            MyField[y][x] = MISS;
            addCell(x, y, igra->scene1);
            igra->miss->play();
            while(!igra->miss->isFinished())
                Delay();
            igra->currentMove = true;
        }

        if(MyField[y][x] == BUSY)
        {
            MyField[y][x] = HIT;
            igra->last_hit_x = x;
            igra->last_hit_y = y;
            addCell(x, y, igra->scene1);
            if(isCrashed(x, y, MyField, igra->scene1))
                igra->kill->play();
            else
                igra->hit->play();
            while((!igra->hit->isFinished()) || (!igra->kill->isFinished()))
                Delay();
            igra->comp_win++;

            if(isCrashed(x, y, MyField, igra->scene1))
            {
                igra->last_hit_x = -1;
                igra->last_hit_y = -1;
            }
            StepComp();
        }
    }

    if(igra->comp_win == 20)    //if computer won
    {
        QSound *lose = new QSound("music/lose.wav");
        lose->play();
        QMessageBox::information(0, "Result", "You lose!");
        while(!lose->isFinished())
            Delay();
        igra->currentMove = true;
        //igra->comp_win++;
        igra->finish = true;
    }
}

void ChooseWay()
{
    static int Step[4] = {0, 0, 0, 0};
    int Way = 0, flag;

    for(int i(0); i < 4; i++)
    {
        if(Step[i] == 1)
            Way = i;
    }

    while(Step[Way] == -1)
        Way = qrand() % 4;

    flag = Kill(Way);

    if(flag == 1)
    {
        igra->last_hit_x = -1;
        igra->last_hit_y = -1;
        for (int i(0); i < 4; i++)
            Step[i] = 0;
        StepComp();
        return;
    }
    else if(flag == 2)
    {
        Step[Way] = -1;
        Step[(Way + 2) % 4] = 1;
        Step[(Way + 1) % 4] = -1;
        Step[(Way + 3) % 4] = -1;
        igra->currentMove = true;

    }
    else if(flag == 0)
    {
        Step[Way] = -1;
        igra->currentMove = true;
    }
    else
    {
        Step[Way] = -1;
        ChooseWay();
    }
}

/* for function Kill()
 *
 * return 0: miss at once
 * return 1: ship is destroyed
 * return 2: miss but ship is injured */

int Kill(int Way)
{
    int x = igra->last_hit_x;
    int y = igra->last_hit_y;

    switch (Way)
    {
    case 0:
        while((x > 0) && (MyField[y][--x] != MISS) && (MyField[y][x] != HIT))
        {
            MyField[y][x] += MISS - EMPTY;
            addCell(x, y, igra->scene1);
            if(MyField[y][x] == HIT)
            {
                if(isCrashed(x, y, MyField, igra->scene1))
                    igra->kill->play();
                else
                    igra->hit->play();
                while((!igra->hit->isFinished()) || (!igra->kill->isFinished()))
                    Delay();
                igra->comp_win++;
            }
            if(MyField[y][x] == MISS)
            {
                igra->miss->play();
                while(!igra->miss->isFinished())
                    Delay();
            }
            if(isCrashed(igra->last_hit_x, igra->last_hit_y, MyField, igra->scene1))
                return 1;
            if(((MyField[y][x] == MISS) || (x == 0)) && (igra->last_hit_x - x > 1))
                return 2;
            else if(MyField[y][x] == MISS)
                return 0;
        }
        break;
    case 1:
        while((y > 0) && (MyField[--y][x] != MISS) && (MyField[y][x] != HIT))
        {
            Delay();
            MyField[y][x] += MISS - EMPTY;
            addCell(x, y, igra->scene1);
            if(MyField[y][x] == HIT)
            {
                if(isCrashed(x, y, MyField, igra->scene1))
                    igra->kill->play();
                else
                    igra->hit->play();
                while((!igra->hit->isFinished()) || (!igra->kill->isFinished()))
                    Delay();
                igra->comp_win++;
            }
            if(MyField[y][x] == MISS)
            {
                igra->miss->play();
                while(!igra->miss->isFinished())
                    Delay();
            }
            if(isCrashed(igra->last_hit_x, igra->last_hit_y, MyField, igra->scene1))
                return 1;
            if(((MyField[y][x] == MISS) || (y == 0)) && (igra->last_hit_y - y > 1))
                return 2;
            else if(MyField[y][x] == MISS)
                return 0;
        }
        break;
    case 2:
        while((x < SIZE_FIELD_SQUARE - 1) && (MyField[y][++x] != MISS) && (MyField[y][x] != HIT))
        {
            Delay();
            MyField[y][x] += MISS - EMPTY;
            addCell(x, y, igra->scene1);
            if(MyField[y][x] == HIT)
            {
                if(isCrashed(x, y, MyField, igra->scene1))
                    igra->kill->play();
                else
                    igra->hit->play();
                while((!igra->hit->isFinished()) || (!igra->kill->isFinished()))
                    Delay();
                igra->comp_win++;
            }
            if(MyField[y][x] == MISS)
            {
                igra->miss->play();
                while(!igra->miss->isFinished())
                    Delay();
            }
            if(isCrashed(igra->last_hit_x, igra->last_hit_y, MyField, igra->scene1))
                return 1;
            if(((MyField[y][x] == MISS) || (x == SIZE_FIELD_SQUARE - 1)) && (x - igra->last_hit_x > 1))
                return 2;
            else if(MyField[y][x] == MISS)
                return 0;
        }
        break;
    case 3:
        while((y < SIZE_FIELD_SQUARE - 1) && (MyField[++y][x] != MISS) && (MyField[y][x] != HIT))
        {
            Delay();
            MyField[y][x] += MISS - EMPTY;
            addCell(x, y, igra->scene1);
            if(MyField[y][x] == HIT)
            {
                if(isCrashed(x, y, MyField, igra->scene1))
                    igra->kill->play();
                else
                    igra->hit->play();
                while((!igra->hit->isFinished()) || (!igra->kill->isFinished()))
                    Delay();
                igra->comp_win++;
            }
            if(MyField[y][x] == MISS)
            {
                igra->miss->play();
                while(!igra->miss->isFinished())
                    Delay();
            }
            if(isCrashed(igra->last_hit_x, igra->last_hit_y, MyField, igra->scene1))
                return 1;
            if(((MyField[y][x] == MISS) || (y == SIZE_FIELD_SQUARE - 1)) && (y - igra->last_hit_y > 1))
                return 2;
            else if(MyField[y][x] == MISS)
                return 0;
        }
        break;
    default:
        break;
    }
    return 3;
}

void Delay()
{
    QEventLoop loop;
    QTimer::singleShot(1, &loop, SLOT(quit()));
    loop.exec();
}
