#include "gametimer.h"

namespace gm
{

GameTimer::GameTimer(QWidget* pwgt) :
    QWidget(pwgt),
    _timer(std::make_unique<QTimer>()),
    _lblTimer(std::make_unique<QLabel>("00:00")),
    _elapsedSec(0),
    _elapsedMin(0),
    _elapsedHour(0),
    _interval(-1)
{
    QHBoxLayout* phbxLayout = new QHBoxLayout;

    connect(_timer.get(), &QTimer::timeout, this, &GameTimer::updateTime);

    _timer.get()->setInterval(1000);

    phbxLayout->addWidget(_lblTimer.get());

    setLayout(phbxLayout);

    _timer.get()->start();
}

void GameTimer::updateTime()
{
    qDebug() << "Timeout Signal Received\n";

    ++_elapsedSec;
    if (_elapsedSec == 60) {
        ++_elapsedMin;
        _elapsedSec = 0;
        if (_elapsedMin == 60) {
            ++_elapsedHour;
            _elapsedMin = 0;
        }
    }

    _lblTimer->setText(QString::number(_elapsedHour) + ":" + QString::number(_elapsedMin) + ":" + QString::number(_elapsedSec));

    if (_interval == _elapsedMin) {
        _elapsedSec = 0;
        _elapsedMin = 0;
        _elapsedHour = 0;
        emit updateBlinds();
    }

}

void GameTimer::setInterval(int val)
{
    _interval = val;
}

}

