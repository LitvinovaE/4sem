#include "choose_level.h"

/* Global variables */
extern Game *igra;
extern Scenes *b;

Choose_level::Choose_level(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choose_level)
{
    setWindowFlags (windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
}

Choose_level::~Choose_level()
{
    delete ui;
}

void Choose_level::on_pushButton_2_clicked() //click on "shipboy"
{
    b->show_MainWindow();
    igra->difficultly_level = EASY;
}

void Choose_level::on_pushButton_3_clicked() //click on "captain"
{
    b->show_MainWindow();
    igra->difficultly_level = MEDIUM;
}

void Choose_level::on_pushButton_clicked() //click on "admiral"
{
    b->show_MainWindow();
    igra->difficultly_level = HARD;
}

void Choose_level::on_pushButton_4_clicked() //click on "exit"
{
    QApplication::quit();
}
