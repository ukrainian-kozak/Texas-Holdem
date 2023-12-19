#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QHBoxLayout>

namespace gm
{

class GameTimer : public QWidget
{
    Q_OBJECT
public:
    GameTimer(QWidget* pwgt = nullptr);

    void setInterval(int);

signals:
    void updateBlinds();

public slots:
    void updateTime();

private:
    std::unique_ptr<QTimer> _timer;
    std::unique_ptr<QLabel> _lblTimer;
    int _elapsedSec;
    int _elapsedMin;
    int _elapsedHour;
    int _interval;
};

}


#endif // GAMETIMER_H
