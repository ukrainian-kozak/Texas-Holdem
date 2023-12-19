QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card.cpp \
    cardcontainer.cpp \
    cardwidget.cpp \
    dealer.cpp \
    deck.cpp \
    gameinfo.cpp \
    gametimer.cpp \
    gamewindow.cpp \
    main.cpp \
    menuwindow.cpp \
    player.cpp \
    playerwidget.cpp \
    pokerai.cpp \
    pokerhand.cpp \
    pokertable.cpp \
    pokertablewidget.cpp \
    texturemanager.cpp


HEADERS += \
    card.h \
    cardcontainer.h \
    cardwidget.h \
    dealer.h \
    deck.h \
    gameinfo.h \
    gametimer.h \
    gamewindow.h \
    menuwindow.h \
    player.h \
    playerwidget.h \
    pokerai.h \
    pokerhand.h \
    pokertable.h \
    pokertablewidget.h \
    texturemanager.h

FORMS +=

TRANSLATIONS += \
    poker_desktop_uk_UA.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    cards_img.qrc \
    img.qrc
