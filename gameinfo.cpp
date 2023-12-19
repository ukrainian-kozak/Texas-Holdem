#include "gameinfo.h"

namespace  gm
{

GameInfo::GameInfo(QWidget* pwgt) :
    QWidget(pwgt),
    _bigBlind(10),
    _blinds(std::make_unique<QLabel>(QString::number(10) + " / " + QString::number(_bigBlind / 2))),
    _playerCount(std::make_unique<QLabel>("6")),
    _totalTime(std::make_unique<GameTimer>()),
    _blindsTime(std::make_unique<GameTimer>())
{
    QGridLayout* pgridLayout = new QGridLayout;

    _blindsTime->setInterval(10);
    connect(_blindsTime.get(), &GameTimer::updateBlinds, this, &GameInfo::updateBlinds);

    pgridLayout->addWidget(_playerCount.get(), 0, 0);
    pgridLayout->addWidget(_totalTime.get(), 1, 0);
    pgridLayout->addWidget(_blindsTime.get(), 0, 1);
    pgridLayout->addWidget(_blinds.get(), 1, 1);
    setLayout(pgridLayout);
}

void GameInfo::updateBlinds()
{
    qDebug() << "Update Blinds!\n";
    _bigBlind += 100;
    _blinds->setText(QString::number(_bigBlind) + " / " + QString::number(_bigBlind / 2));
}

}
