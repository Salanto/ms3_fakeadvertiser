#ifndef FAKE_ADVERTISER_H
#define FAKE_ADVERTISER_H
#include <QtNetwork>
#include <QObject>

class FakeAdvertiser : public QObject {
    Q_OBJECT

public:
    FakeAdvertiser(QObject* parent = nullptr);
    ~FakeAdvertiser();


public slots:

    /**
     * @brief Establishes a connection with masterserver to register or update the listing on the masterserver.
     */
    void msAdvertiseServer();

    /**
     * @brief Reads the information send as a reply for further error handling.
     * @param reply Response data from the masterserver. Information contained is send to the console if debug is enabled.
     */
    void msRequestFinished(QNetworkReply *f_reply);

private:

    /**
     * @brief Pointer to the network manager, necessary to execute POST requests to the masterserver.
     */
    QNetworkAccessManager* m_manager;

    /**
     * @brief Name of the server send to the masterserver. Changing this will change the display name in the serverlist
     */
    QString m_name = "Hope Despair Force";

    /**
     * @brief Description of the server that is displayed in the client when the server is selected.
     */
    QString m_description = "A server for chilling, casing, venting, roleplaying, jamming, gaming, and more! If you'd like to appeal a ban and have no discord, appeal at our appeal email at AOHDF-Unban@yandex.com. [ Rules - https://t.ly/LBkOm ] [ Discord - https://discord.gg/vUXADkz ]";

    /**
     * @brief Client port for the AO2-Client.
     */
    int m_port = 6881;

    /**
     * @brief Websocket proxy port for WebAO users.
     */
    int m_ws_port = 6682;

    /**
     * @brief Maximum amount of clients that can be connected to the server.
     */
    int m_players = 200;

    /**
     * @brief URL of the masterserver that m_manager posts to. This is almost never changed.
     */
    QUrl m_masterserver = QString("https://servers.aceattorneyonline.com/servers");

    /**
     * @brief Advertised IP Address to masterserver
     */
    QString m_ipaddress = "83.136.252.90";

    /**
     * @brief Controls if network replies are printed to console. Should only be true if issues communicating with masterserver appear.
     */
    bool m_debug = true;

    /**
     * @brief Timer to advertise the server every 5 minutes
     */
    QTimer* m_advertisement_timer;
};

#endif //FAKE_ADVERTISER_H
