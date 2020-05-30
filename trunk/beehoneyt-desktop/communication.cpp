#include "communication.h"
#include "ihm.h"

/**
 * @file    communication.cpp
 * @brief   Déclaration de la classe Communication
 * @author  ACKERMANN Théo
 * @version 0.2
 */

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

/**
 * @brief Méthode pour se désabonner d'un topic TTN
 * 
 * @param topic
 */
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
    QString nomDeLaRuche;
    QString horodatage;

    qDebug() << Q_FUNC_INFO << json;
    if(!documentJSON.isNull())
    {
        QJsonObject objetJSON = documentJSON.object();
        QStringList listeCles = objetJSON.keys();
        // les clés sont triés alphabétiquement
        for(int i = 0; i < listeCles.count()-1; i++)
        {
            if(listeCles.at(i) == "dev_id")
            {
                nomDeLaRuche = extraireDeviceID(objetJSON, listeCles, i);
            }
            if(listeCles.at(i) == "metadata")
            {                
                horodatage = formaterHorodatage(extraireHorodatage(objetJSON[listeCles.at(i)].toObject()));
            }            
            if(listeCles.at(i) == "payload_fields")
            {
                QJsonObject objet = objetJSON[listeCles.at(i)].toObject();

                if(objet.contains("temperatureInt"))
                {
                    emit nouvelleValeurTemperatureInterieure(nomDeLaRuche, extraireTemperatureInterieure(objet), horodatage);
                }
                if(objet.contains("temperatureExt"))
                {
                    emit nouvelleValeurTemperatureExterieure(nomDeLaRuche, extraireTemperatureExterieure(objet), horodatage);
                }
                if(objet.contains("humiditeInt"))
                {
                    emit nouvelleValeurHumiditeInterieure(nomDeLaRuche, extraireHumiditeInterieure(objet), horodatage);
                }
                if(objet.contains("humiditeExt"))
                {
                    emit nouvelleValeurHumiditeExterieure(nomDeLaRuche, extraireHumiditeExterieure(objet), horodatage);
                }
                if(objet.contains("ensoleillement"))
                {
                    emit nouvelleValeurEnsoleillement(nomDeLaRuche, extraireEnsoleillement(objet), horodatage);
                }
                if(objet.contains("pression"))
                {
                    emit nouvelleValeurPression(nomDeLaRuche, extrairePression(objet), horodatage);
                }
                if(objet.contains("poids"))
                {
                    emit nouvelleValeurPoids(nomDeLaRuche, extrairePoids(objet), horodatage);
                }
                if(objet.contains("charge"))
                {
                    emit nouvelleValeurCharge(nomDeLaRuche, extraireCharge(objet), horodatage);
                }
            }
        }
    }
}

/**
 * @brief Méthode pour extraire le temps de l'objet JSON
 * 
 * @param objetJSON
 * @return QString
 */
QString Communication::extraireHorodatage(QJsonObject objetJSON)
{
    return objetJSON.value(QString("time")).toString();
}

/**
 * @brief Méthode pour extraire le device ID de l'objet JSON
 * 
 * @param objetJSON
 * @param listeCles
 * @param position
 * @return QString
 */
QString Communication::extraireDeviceID(QJsonObject objetJSON, QStringList listeCles, int position)
{
    return objetJSON[listeCles.at(position)].toString();
}

/**
 * @brief Méthode pour extraire la température intérieure de l'objet JSON
 * 
 * @param objetJSON
 * @return double
 */
double Communication::extraireTemperatureInterieure(QJsonObject objetJSON)
{
    return objetJSON.value(QString("temperatureInt")).toDouble();
}

/**
 * @brief Méthode pour extraire la température extérieure de l'objet JSON
 *
 * @param objetJSON
 * @return double
 */
double Communication::extraireTemperatureExterieure(QJsonObject objetJSON)
{
    return objetJSON.value(QString("temperatureExt")).toDouble();
}

/**
 * @brief Méthode pour extraire l'humidité intérieure de l'objet JSON
 * 
 * @param objetJSON
 * @return double
 */
double Communication::extraireHumiditeInterieure(QJsonObject objetJSON)
{
    return objetJSON.value(QString("humiditeInt")).toDouble();
}

/**
 * @brief Méthode pour extraire l'humidité extérieure de l'objet JSON
 *
 * @param objetJSON
 * @return double
 */
double Communication::extraireHumiditeExterieure(QJsonObject objetJSON)
{
    return objetJSON.value(QString("humiditeExt")).toDouble();
}
/**
 * @brief Méthode pour extraire l'ensoleillement de l'objet JSON
 * 
 * @param objetJSON
 * @return int
 */
int Communication::extraireEnsoleillement(QJsonObject objetJSON)
{
    return objetJSON.value(QString("ensoleillement")).toInt();
}

/**
 * @brief Méthode pour extraire la pression de l'objet JSON
 * 
 * @param objetJSON
 * @return int
 */
int Communication::extrairePression(QJsonObject objetJSON)
{
    return objetJSON.value(QString("pression")).toInt();
}

/**
 * @brief Méthode pour extraire le poids le l'objet JSON
 * 
 * @param objetJSON
 * @return double
 */
double Communication::extrairePoids(QJsonObject objetJSON)
{
    return objetJSON.value(QString("poids")).toDouble();
}

/**
 * @brief Méthode pour extraire la charge de la batterie le l'objet JSON
 *
 * @param objetJSON
 * @return int
 */
int Communication::extraireCharge(QJsonObject objetJSON)
{
    return objetJSON.value(QString("charge")).toInt();
}

/**
 * @brief Méthode pour mettre dans le bon format l'horodatage reçu
 * 
 * @param horodatageBrut
 * @return QString
 */
QString Communication::formaterHorodatage(QString horodatageBrut)
{
    QDateTime horodatage = QDateTime::fromString(horodatageBrut, Qt::ISODate).toLocalTime();
    return horodatage.toString("dd/MM/yyyy HH:mm:ss");
}

/**
 * @brief Méthode pour notifier un changement d'état de la connexion TTN
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
