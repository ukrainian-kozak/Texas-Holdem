#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QString>
#include <QPixmap>
#include <QPalette>

namespace gm
{

class TextureManager
{
public:
    TextureManager();

    QPalette upload(const QString&);
};

}


#endif // TEXTUREMANAGER_H
