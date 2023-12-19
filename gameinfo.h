#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

#include "gametimer.h"

namespace gm
{

class GameInfo : public QWidget
{
public:
    GameInfo(QWidget* pwgt = nullptr);

public slots:
    void updateBlinds();

private:
    qsizetype _bigBlind;
    std::unique_ptr<QLabel> _blinds;
    std::unique_ptr<QLabel> _playerCount;
    std::unique_ptr<GameTimer> _totalTime;
    std::unique_ptr<GameTimer> _blindsTime;

};

}


#endif // GAMEINFO_H
