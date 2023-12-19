#include "texturemanager.h"


namespace gm
{

TextureManager::TextureManager()
{
}

QPalette TextureManager::upload(const QString& path)
{
    QPixmap img(path);
    QPalette palette;
    palette.setBrush(QPalette::Window, img);
    return palette;

}

}

