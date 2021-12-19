#include "include/fake_advertiser.h"


FakeAdvertiser::FakeAdvertiser(QObject *parent) :
    QObject(parent)
{
    m_manager = new QNetworkAccessManager();
    connect(m_manager, &QNetworkAccessManager::finished,
            this, &FakeAdvertiser::msRequestFinished);

   m_advertisement_timer = new QTimer();
   connect(m_advertisement_timer, &QTimer::timeout,
           this, &FakeAdvertiser::msAdvertiseServer);
   m_advertisement_timer->setInterval(300000);
   m_advertisement_timer->start();

   m_player_prober = new PlayerProber(this, m_ipaddress, m_port);
   connect(m_player_prober, &PlayerProber::updatePlayers,
           this, &FakeAdvertiser::msUpdatePlayers);
}

FakeAdvertiser::~FakeAdvertiser()
{
    //Lazy cleanup
    m_manager->deleteLater();
    m_advertisement_timer->deleteLater();
}

void FakeAdvertiser::msAdvertiseServer()
{
    if (m_masterserver.isValid()) {

        QUrl url(m_masterserver);
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject l_json;
        l_json["ip"] = m_ipaddress;
        l_json["port"] = m_port;
        if (m_ws_port != -1) {
            l_json["ws_port"] = m_ws_port;
        }

        l_json["players"] = m_players;
        l_json["name"] = m_name;

        if (!m_description.isEmpty()) {
        l_json["description"] = m_description;
        }

        m_manager->post(request, QJsonDocument(l_json).toJson());

        if (m_debug)
            qDebug().noquote() << "Advertised Server";
        return;
    }
    if (m_debug)
        qWarning().noquote() << "Unable to advertise. Masterserver URL '" + m_masterserver.toString() + "' is not valid.";
    return;

}

void FakeAdvertiser::msRequestFinished(QNetworkReply *f_reply)
{
    if (m_debug) {
        if (f_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
            qDebug().noquote() << "Succesfully advertised server.";
        }
        else {
            QJsonDocument json = QJsonDocument::fromJson(f_reply->readAll());
            if (json.isNull()) {
                qCritical().noquote() << "Invalid JSON response from" << f_reply->url();
                f_reply->deleteLater();
                return;
            }

            qDebug().noquote() << "Got valid response from" << f_reply->url();
            qDebug() << json;
        }
    }
    f_reply->deleteLater();
}

void FakeAdvertiser::msUpdatePlayers(int f_players)
{
    m_players = f_players;
    msAdvertiseServer();
    m_advertisement_timer->setInterval(300000);
    m_advertisement_timer->start();
}
