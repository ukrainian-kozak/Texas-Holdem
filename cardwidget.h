#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include "texturemanager.h"

namespace gm
{

class CardWidget : public QWidget
{
public:
    CardWidget(const QString&, QWidget* pwgt = nullptr);


private:
    TextureManager _texManager;
};

}


#endif // CARDWIDGET_H
