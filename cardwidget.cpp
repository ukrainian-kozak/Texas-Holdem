#include "cardwidget.h"


namespace gm
{

CardWidget::CardWidget(const QString& path, QWidget* pwgt)
{
    setPalette(_texManager.upload(path));

    setMinimumSize(40, 54);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    resize(100, 144);
}

}
