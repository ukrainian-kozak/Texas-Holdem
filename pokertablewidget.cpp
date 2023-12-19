#include "pokertablewidget.h"

namespace gm
{

PokerTableWidget::PokerTableWidget(QWidget* pwgt) :
    QWidget(pwgt),
    _pot(std::make_unique<QLabel>("0")),
    _players()
{
    QGridLayout* pgridLayout = new QGridLayout;

    for (qsizetype i = 0; i < 3; ++i) {
        _players.push_back(std::make_unique<PlayerWidget>("Player" + QString::number(i + 2)));
        pgridLayout->addWidget(_players[i].get(), 0, i + 1);
    }
    _players.push_back(std::make_unique<PlayerWidget>("Player1"));
    _players.push_back(std::make_unique<PlayerWidget>("Player5"));
    _players.push_back(std::make_unique<PlayerWidget>("Player6"));

    pgridLayout->addWidget(_players[3].get(), 1, 0);
    pgridLayout->addWidget(_players[4].get(), 1, 4);
    pgridLayout->addWidget(_players[5].get(), 2, 2);
    pgridLayout->addWidget(_pot.get(), 1, 2);

    setLayout(pgridLayout);

    resize(800, 400);
}


void PokerTableWidget::updatePot(qsizetype val)
{
    _pot.get()->setText(QString::number(val + _pot.get()->text().toInt()));
}

}

