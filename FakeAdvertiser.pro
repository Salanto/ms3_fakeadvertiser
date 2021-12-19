QT -= gui
QT += network

CONFIG += c++17 console
CONFIG -= app_bundle

CONFIG -= \
        copy_dir_files \
        debug_and_release \
        debug_and_release_target

DESTDIR = $$PWD/bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/main.cpp \
        src/fake_advertiser.cpp \
        src/player_prober.cpp \
        src/aopacket.cpp

HEADERS += \
        include/fake_advertiser.h \
        include/player_prober.h \
        include/aopacket.h
