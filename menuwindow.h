#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QCloseEvent>
#include <QVector>

#include "gamewindow.h"


namespace gm
{

class MenuWindow : public QWidget
{
    Q_OBJECT

public:
    MenuWindow(QWidget* pwgt = nullptr);

private slots:
    void openGameWindow();

protected:
    void closeEvent(QCloseEvent*);

private:
    GameWindow _gameWindow;

};


}


#endif // MENUWINDOW_H
