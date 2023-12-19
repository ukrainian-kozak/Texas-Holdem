#ifndef POKERTABLEWIDGET_H
#define POKERTABLEWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QGridLayout>

#include "playerwidget.h"


namespace gm
{

class PokerTableWidget : public QWidget
{
    Q_OBJECT
public:
    PokerTableWidget(QWidget* pwgt = nullptr);

    void bigBlind(qsizetype);

public slots:
    void updatePot(qsizetype);

private:
    std::unique_ptr<QLabel> _pot;
    QVector<std::shared_ptr<PlayerWidget>> _players;

};

}



#endif // POKERTABLEWIDGET_H
