#include "communication.h"
#include "ihm.h"
#include <QDebug>

/**
 * @brief Constructeur de la classe Communication
 *
 * @param parent
 */
Communication::Communication(QObject *parent) : QObject(parent), client(new QMqttClient(this))
{
    qDebug() << Q_FUNC_INFO;
    connect(client, SIGNAL(stateChanged(ClientState)), this, SLOT(changerEtatConnexion()));
    connect(client, SIGNAL(messageReceived(const QByteArray &, const QMqttTopicName &)), this, SLOT(decoderJson(const QByteArray &)));
}

/**
 * @brief Destructeur de la classe Communication
 *
 */
Communication::~Communication()
{
    if(client->state() == QMqttClient::Connected)
    {
        client->disconnectFromHost();
    }
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Méthode pour se connecter à TTN
 *
 * @param hostname
 * @param port
 * @param username
 * @param password
 */
void Communication::connecterTTN(QString hostname, int port, QString username, QString password)
{
    qDebug() << Q_FUNC_INFO << hostname << port << username << password;
    if(client->state() == QMqttClient::Disconnected)
    {
        client->setHostname(hostname);
        client->setPort(port);
        client->setUsername(username);
        client->setPassword(password);
        client->connectToHost();
    }
    else if(client->state() == QMqttClient::Connected)
    {
        client->disconnectFromHost();
    }
}

/**
 * @brief Méthode pour s'abonner à un topic TTN
 *
 * @param topic
 */
void Communication::souscrireTopic(QString topic)
{
    if(client->state() == QMqttClient::Connected)
    {
        subscription = client->subscribe(QMqttTopicFilter(topic));
        qDebug() << Q_FUNC_INFO << topic;
    }
}

void Communication::desabonnerTopic(QString topic)
{
    if(client->state() == QMqttClient::Connected)
    {
        client->unsubscribe(topic);
        qDebug() << Q_FUNC_INFO << topic;
    }
}

/**
 * @brief Méthode pour décoder le JSON reçu
 *
 * @param json
 */
void Communication::decoderJson(const QByteArray &json)
{
    QJsonDocument documentJSON = QJsonDocument::fromJson(json);
    QByteArray payload;
    QString nomDeLaRuche;
    /**
      * @todo Extraire et gérer l'horodatage
      */
    if(!documentJSON.isNull())
    {
        QJsonObject objetJSON = documentJSON.object();
        QStringList listeCles = objetJSON.keys();
        qDebug() << Q_FUNC_INFO << listeCles;
        for(int i = 0; i < listeCles.count()-1; i++)
        {
            if(listeCles.at(i) == "dev_id")
            {
                nomDeLaRuche = objetJSON[listeCles.at(i)].toString();
                qDebug() << Q_FUNC_INFO << nomDeLaRuche;
            }
            if(listeCles.at(i) == "payload_fields")
            {
                qDebug() << Q_FUNC_INFO << "payload_fields" << objetJSON[listeCles.at(i)];
                QJsonObject objet = objetJSON[listeCles.at(i)].toObject();

                if(objet.contains("temperature"))
                {
                    QJsonValue temperature = objet.value(QString("temperature"));
                    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Température :" << temperature.toDouble() << "°C";
                    emit nouvelleValeurTemperature(nomDeLaRuche, temperature.toDouble());
                }
                if(objet.contains("humidite"))
                {
                    QJsonValue humidite = objet.value(QString("humidite"));
                    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Humidité :" << humidite.toDouble() << "%";
                    emit nouvelleValeurHumidite(nomDeLaRuche, humidite.toDouble());
                }
                if(objet.contains("ensoleillement"))
                {
                    QJsonValue ensoleillement = objet.value(QString("ensoleillement"));
                    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Ensoleillement :" << ensoleillement.toInt() << "lux";
                    emit nouvelleValeurEnsoleillement(nomDeLaRuche, ensoleillement.toInt());
                }
                if(objet.contains("pression"))
                {
                    QJsonValue pression = objet.value(QString("pression"));
                    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Pression :" << pression.toInt() << "hPa";
                    emit nouvelleValeurPression(nomDeLaRuche, pression.toInt());
                }
                if(objet.contains("poids"))
                {
                    QJsonValue poids = objet.value(QString("poids"));
                    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Poids :" << poids.toDouble() << "grammes";
                    emit nouvelleValeurPoids(nomDeLaRuche, poids.toDouble());
                }
            }
        }
    }
}

/**
 * @brief Méthodepour notifier un changement d'état de la connexion TTN
 *
 */
void Communication::changerEtatConnexion()
{
    QString message;
    switch(client->state())
    {
        case 0:
            message = "Déconnecté";
            break;
        case 1:
            message = "En cours de connexion";
            break;
        case 2:
            message = "Connecté";
            break;
    }
    qDebug()<< Q_FUNC_INFO << client->state() << message;
    emit nouvelEtatConnexion(client->state());
}
