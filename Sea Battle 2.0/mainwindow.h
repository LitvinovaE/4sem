#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QSound>
#include <QTime>
#include "const.h"
#include "ship.h"
#include "game.h"
#include "my_scene.h"
#include "scenes.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void DrawGrid();
    void PlacementShips();
    ~MainWindow();
    int ReadyEnabled();                    //button`s availability conditions
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void CreateNewGame();                  //if you want to play new game
    Ui::MainWindow *ui;

/* buttons */
private slots:
    void AutoClicked();
    void ReadyClicked();

    void on_actionCreator_triggered();

    void on_actionRules_triggered();

public slots:
    void on_actionExit_triggered();
    void on_actionNew_game_triggered();
    void on_actionGame_over_triggered();
};

#endif // MAINWINDOW_H
