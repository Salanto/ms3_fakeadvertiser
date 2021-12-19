#ifndef PLAYER_PROBER_H
#define PLAYER_PROBER_H
#include <QObject>
#include <QTimer>
#include <QUrl>
#include <QTcpSocket>
#include <QString>

#include "include/aopacket.h"


class PlayerProber : public QObject {
    Q_OBJECT
public:
    PlayerProber(QObject* parent = nullptr, QString f_hostname = "localhost", int f_port = 0);
    ~PlayerProber();

private:

    QTcpSocket* m_socket;
    QTimer* m_player_timer;

    QString m_hostname;
    int m_port;

    bool partial_packet = false;
    QString temp_packet;

    void handle_packet(AOPacket* p_packet);

private slots:

    void requestPlayers();
    void readReady();

signals:

    void updatePlayers(int f_players);
};

#endif
