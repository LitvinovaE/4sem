#include "enemy_scene.h"

/* Global variables */
extern int EnemyField[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE], \
           MyField[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE];
extern Game *igra;
extern int corX_enemy[2][SHIP_AMOUNT], corY_enemy[2][SHIP_AMOUNT];

void Enemy_scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if((igra->currentMove) && (event->button() == Qt::LeftButton) && (igra->miss->isFinished()) \
            && (igra->hit->isFinished()) && (igra->kill->isFinished()) && (igra->finish == false))
    {
        int x = (int) event->scenePos().x() / SIZE_PALUB;
        int y = (int) event->scenePos().y() / SIZE_PALUB;

        if((EnemyField[y][x] == MISS) || (EnemyField[y][x] == HIT))
            return;

        if(EnemyField[y][x] == EMPTY)           //if you missed
        {
            EnemyField[y][x] = MISS;
            addCell(x, y, igra->scene2);
            igra->miss->play();
            while(!igra->miss->isFinished())    //to hear music
                Delay();
            igra->currentMove = false;          //change of the right of step
            StepComp();                         //computer makes a step
        }
        else                                    //if you hit
        {
            EnemyField[y][x] = HIT;
            addCell(x, y, igra->scene2);
            if(isCrashed(x, y, EnemyField, igra->scene2))   //check: killed or not
                igra->kill->play();
            else
                igra->hit->play();
            while((!igra->hit->isFinished()) || (!igra->kill->isFinished()))    //to hear music
                Delay();
            igra->my_win++;

        }

        if(igra->my_win == 20)  //if you win
        {
            igra->my_win++;
            QSound::play("music/win.wav");
            QMessageBox::information(0, "Result", "You win!");
            igra->finish = true;
        }
    }
}
