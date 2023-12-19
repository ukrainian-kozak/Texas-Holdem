#include "gamewindow.h"


namespace gm
{

GameWindow::GameWindow(QWidget* pwgt) :
    QWidget(pwgt),
    _tableWgt(std::make_unique<PokerTableWidget>()),
    _gameInfo(std::make_unique<GameInfo>()),
    _dealer(std::make_unique<Dealer>()),
    _texManager()
{
    QObject::connect(_dealer.get(), &Dealer::antePosted,
                     _tableWgt.get(), &PokerTableWidget::updatePot);

    QLineEdit* lineEdit = new QLineEdit;
    QPushButton* pcmdCall = new QPushButton("Call");
    QPushButton* pcmdFold = new QPushButton("Fold");
    QPushButton* pcmdBet = new QPushButton("Bet");
    QGridLayout* pgridLayout = new QGridLayout;
    QHBoxLayout* phbxLayout = new QHBoxLayout;

    //Setup Layout
    pgridLayout->addWidget(_gameInfo.get(), 0, 4, 2, 2);
    pgridLayout->addWidget(_tableWgt.get(), 0, 0, 3, 4);
    phbxLayout->addWidget(pcmdBet);
    phbxLayout->addWidget(pcmdCall);
    phbxLayout->addWidget(pcmdFold);
    pgridLayout->addLayout(phbxLayout, 3, 0, 1, 6);
    pgridLayout->addWidget(lineEdit, 4, 0);
    setLayout(pgridLayout);

    setPalette(_texManager.upload(":/img/background_main_window.jpg"));

    resize(1200, 800);


    _dealer.get()->startHand();
}

}

