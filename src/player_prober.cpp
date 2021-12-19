#include "include/player_prober.h"

PlayerProber::PlayerProber(QObject *parent, QString f_hostname, int f_port) :
    QObject(parent)
{
    m_player_timer = new QTimer();
    m_socket = new QTcpSocket();
    connect(m_socket, &QTcpSocket::readyRead,
            this, &PlayerProber::readReady);

    m_player_timer->setInterval(60000);
    m_player_timer->start();

    m_hostname = f_hostname;
    m_port = f_port;
    requestPlayers();
}

PlayerProber::~PlayerProber()
{

    m_player_timer->deleteLater();
    m_socket->deleteLater();
}

void PlayerProber::handle_packet(AOPacket *p_packet)
{
    QString header = p_packet->get_header();
    QStringList f_contents = p_packet->get_contents();
    QString f_packet = p_packet->to_string();

    if (header == "PN") {
        if (f_contents.size() < 2)
            return;
        QStringList split_packet = f_packet.split("#", Qt::SkipEmptyParts);
        emit updatePlayers(split_packet[1].toInt());
        m_socket->disconnectFromHost();
    }
}

void PlayerProber::requestPlayers()
{
    m_socket->connectToHost(m_hostname, m_port, QIODevice::ReadWrite);
    m_socket->waitForConnected();
    m_socket->write(QString("HI#123456#%").toUtf8());
    m_socket->flush();
}

void PlayerProber::readReady()
{
    QByteArray buffer = m_socket->readAll();
    QString in_data = QString::fromUtf8(buffer, buffer.size());

    if (!in_data.endsWith("%")) {
      partial_packet = true;
      temp_packet += in_data;
      return;
    }

    else {
      if (partial_packet) {
        in_data = temp_packet + in_data;
        temp_packet = "";
        partial_packet = false;
      }
    }

    QStringList packet_list =
        in_data.split("%", Qt::SkipEmptyParts);

    for (const QString &packet : packet_list) {
      AOPacket *f_packet = new AOPacket(packet);
      handle_packet(f_packet);
    }
}
