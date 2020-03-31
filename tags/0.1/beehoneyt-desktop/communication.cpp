#include "communication.h"
#include "ihm.h"

/**
 * @brief Constructeur de la classe Communication
 * @fn Communication::Communication
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
 * @fn Communication::~Communication
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
 * @fn Communication::connecterTTN
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
 * @fn Communication::souscrireTopic
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
 * @fn Communication::desabonnerTopic
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
 * @fn Communication::decoderJson
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

                if(objet.contains("temperature"))
                {
                    emit nouvelleValeurTemperature(nomDeLaRuche, extraireTemperature(objet), horodatage);
                }
                if(objet.contains("humidite"))
                {
                    emit nouvelleValeurHumidite(nomDeLaRuche, extraireHumidite(objet), horodatage);
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
            }
        }
    }
}

/**
 * @brief Méthode pour extraire le temps de l'objet JSON
 * @fn Communication::extraireHorodatage
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
 * @fn Communication::extraireDeviceID
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
 * @brief Méthode pour extraire la temperature de l'objet JSON
 * @fn Communication::extraireTemperature
 * 
 * @param objetJSON
 * @return double
 */
double Communication::extraireTemperature(QJsonObject objetJSON)
{
    return objetJSON.value(QString("temperature")).toDouble();
}

/**
 * @brief Méthode pour extraire l'humidité de l'objet JSON
 * @fn Communication::extraireHumidite
 * 
 * @param objetJSON
 * @return double
 */
double Communication::extraireHumidite(QJsonObject objetJSON)
{
    return objetJSON.value(QString("humidite")).toDouble();
}

/**
 * @brief Méthode pour extraire l'ensoleillement de l'objet JSON
 * @fn Communication::extraireEnsoleillement
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
 * @fn Communication::extrairePression
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
 * @fn Communication::extrairePoids
 * 
 * @param objetJSON
 * @return double
 */
double Communication::extrairePoids(QJsonObject objetJSON)
{
    return objetJSON.value(QString("poids")).toDouble();
}

/**
 * @brief Méthode pour mettre dans le bon format l'horodatage reçu
 * @fn Communication::formaterHorodatage
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
 * @fn Communication::changerEtatConnexion
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