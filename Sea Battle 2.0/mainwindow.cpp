#include "mainwindow.h"

/* Global variables */
extern int corX[2][SHIP_AMOUNT], corY[2][SHIP_AMOUNT], \
           corX_enemy[2][SHIP_AMOUNT], corY_enemy[2][SHIP_AMOUNT];
extern int EnemyField[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE], \
           MyField[SIZE_FIELD_SQUARE][SIZE_FIELD_SQUARE];
extern Scenes *b;
extern Game *igra;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /* random of rand() */

    QTime time = QTime::currentTime();
    qsrand(time.msec());

    /* playing field */

    igra = new Game();

    ui->setupUi(this);
    ui->player1->setScene(igra->scene1);
    ui->player2->setScene(igra->scene2);

    ui->player2->setEnabled(false);

    /* draw a grid */

    DrawGrid();

    /* placement of ships */

    PlacementShips();
}

void MainWindow::DrawGrid()
{
    for (int i = 0; i < SIZE_FIELD_SQUARE + 1; i++)
    {
        int w = ui->player1->width() / SIZE_FIELD_SQUARE;
        int h = ui->player1->height() - 2;
        igra->scene1->addLine(w*(i), 0, w*(i), h);
        igra->scene2->addLine(w*(i), 0, w*(i), h);
    }
    for (int i = 0; i < SIZE_FIELD_SQUARE + 1; i++)
    {
        int w = ui->player1->width() - 2;
        int h = ui->player1->height() / SIZE_FIELD_SQUARE;
        igra->scene1->addLine(0, h*(i), w, h*(i));
        igra->scene2->addLine(0, h*(i), w, h*(i));
    }
}

void MainWindow::PlacementShips()
{
    int k = 0;
    for(int i = 0; i < MAX_PALUBS; i++)
        for(int j = 0; j < (MAX_PALUBS - i); j++)    //j - number of ships with concrete amount of palubs
            igra->boat[k++] = new Ship(i + 1);

    //connect(ui->Button1,SIGNAL(clicked()),this,SLOT(AutoClicked()));
    //connect(ui->Button2,SIGNAL(clicked()),this,SLOT(ReadyClicked()));

    for(int i = 0; i < SHIP_AMOUNT; i++)             //drawing of ships
        igra->scene1->addItem(igra->boat[i]);

    for(int i = 0; i < SHIP_AMOUNT; i++)
    {
        corX[0][i] = 0;
        corY[0][i] = 0;
        corX[1][i] = igra->boat[i]->shipWid;
        corY[1][i] = igra->boat[i]->shipLen;
    }
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < SHIP_AMOUNT; i++)
    {
        corX_enemy[0][i] = 0;
        corY_enemy[0][i] = 0;
        corX_enemy[1][i] = 0;
        corY_enemy[1][i] = 0;
    }

    for(int i = 0; i < SIZE_FIELD_SQUARE; i++)
        for(int j = 0; j < SIZE_FIELD_SQUARE; j++)
        {
            EnemyField[i][j] = EMPTY;
            MyField[i][j] = EMPTY;
        }

    delete igra->scene1;
    delete igra->scene2;
    delete [] igra->kletka;
    delete [] igra->boat;

    delete ui;
}

int MainWindow::ReadyEnabled()
{
    int k = 0;

    for(int i = 0; i < SHIP_AMOUNT; i++)
        if((igra->boat[i]->coord_x == 0) && (igra->boat[i]->coord_y == 0))
            k++;

    if(k <= 1)
        return OK;
    return ERROR;
}

void MainWindow::AutoClicked()
{
    igra->RandomPlacement(0, corX, corY, igra->boat);
    for (int i(0); i < SHIP_AMOUNT; i++)                 //set ships on new coordinates
        igra->boat[i]->setPos(corX[0][i], corY[0][i]);
}

void MainWindow::ReadyClicked()
{
    int flag = 0;   //check flag of position's correctness

    for(int i(0); i < SHIP_AMOUNT; i++)
    {
        if(!igra->boat[i]->CheckOfPlacement(igra->boat[i]->coord_x, igra->boat[i]->coord_y, corX, corY))
            flag++;
    }

    if((!ReadyEnabled()) && (flag == SHIP_AMOUNT))  //the beginning of game
    {
        ui->Button1->hide();
        ui->Button2->setEnabled(false);
        for(int i(0); i < SHIP_AMOUNT; i++)
            igra->boat[i]->setEnabled(false);
        ui->player2->setEnabled(true);
        b->main->stop();
        QSound ready("music/ready.wav");
        ready.play();
        while(!ready.isFinished())
            Delay();
        igra->StartGame();
    }
}

void MainWindow::CreateNewGame()
{
    for(int i = 0; i < SHIP_AMOUNT; i++)
    {
        corX_enemy[0][i] = 0;
        corY_enemy[0][i] = 0;
        corX_enemy[1][i] = 0;
        corY_enemy[1][i] = 0;
    }

    for(int i = 0; i < SIZE_FIELD_SQUARE; i++)
        for(int j = 0; j < SIZE_FIELD_SQUARE; j++)
        {
            EnemyField[i][j] = EMPTY;
            MyField[i][j] = EMPTY;
        }

    igra->my_win = 0;
    igra->comp_win = 0;

    igra->last_hit_x = -1;
    igra->last_hit_y = -1;

    igra->scene1->clear();
    igra->scene2->clear();

    DrawGrid();

    PlacementShips();

    ui->Button1->show();
    ui->Button2->setEnabled(true);
    ui->player2->setEnabled(false);

    igra->finish = false;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNew_game_triggered()
{
    b->show_FirstWindow();
}

void MainWindow::on_actionGame_over_triggered()
{
    b->main->stop();
    QSound::play("music/lose.wav");
    QMessageBox::information(0, "Result", "You lose!");
    igra->finish = true;
}

void MainWindow::on_actionCreator_triggered()
{
    QMessageBox::information(0, "Creator", "© 2015 Litvinova Eugeniya\n\nMIPT");
}

void MainWindow::on_actionRules_triggered()
{
   QMessageBox::information(0, "Rules", "Beggining of game\n\nIn the game your opponent is a computer. You can choose one\n of the difficultly levels:\n"
                                        "- shipboy (easy level)\n- captain (medium level)\n- admiral (hard level)\n\n"
                                        "Then you sould place battle fleet. It consists of 10 ships:\n"
                                        "- one battleship (4 cell)\n- two cruisers (3 cell)\n- three destroyers (2 cell)\n- four submarines (1 cell)\n"
                                        "It's important that ships can not touch each other!\n\nFighting\n\n"
                                        "The right to make the first shot is determined randomly.\n"
                                        "You should right-click on the enemy field to shoot. If you hit the ship, a cell paints over in black,\
                                        and you have to do another shot. Killed ship is marked blue cells around. Blue cell means you missed.\n\nWin\
                                        \n\nWinner is an opponent who overthrew the all the ships of the enemy.\n\nGood luck!!!");
}
