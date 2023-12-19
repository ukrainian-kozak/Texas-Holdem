#include "menuwindow.h"



namespace gm
{

//=========Constructors begin================


MenuWindow::MenuWindow(QWidget* pwgt) :
    QWidget(pwgt)
{
    QPushButton* pcmd = new QPushButton("&Play");
    QObject::connect(pcmd, &QPushButton::clicked, this, &MenuWindow::openGameWindow);

    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(pcmd);

    setLayout(pvbxLayout);
}


//===========Constructors end==============





//=============Slots begin==================


void MenuWindow::openGameWindow()
{
    _gameWindow.show();
    hide();
}


//==========Close Event begin=================


void MenuWindow::closeEvent(QCloseEvent* e)
{
    if (_gameWindow.isActiveWindow())
        _gameWindow.close();

    e->accept();
}


//=========Close Event end=====================

}




