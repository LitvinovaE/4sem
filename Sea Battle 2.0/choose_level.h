#ifndef CHOOSE_LEVEL_H
#define CHOOSE_LEVEL_H

#include <QDialog>
#include "const.h"
#include "game.h"
#include "scenes.h"
#include "ui_choose_level.h"

namespace Ui {
class Choose_level;
}

class Choose_level : public QDialog
{
    Q_OBJECT

public:
    explicit Choose_level(QWidget *parent = 0);
    ~Choose_level();

/* buttons difficulty level */
public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::Choose_level *ui;
};

#endif // CHOOSE_LEVEL_H
