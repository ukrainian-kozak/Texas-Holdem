#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

#include "pokertablewidget.h"
#include "dealer.h"
#include "gameinfo.h"
#include "texturemanager.h"


namespace gm
{

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget*  pwgt = nullptr);

private:
    std::unique_ptr<PokerTableWidget> _tableWgt;
    std::unique_ptr<GameInfo> _gameInfo;
    std::unique_ptr<Dealer> _dealer;
    TextureManager _texManager;
};

}


#endif // GAMEWINDOW_H
