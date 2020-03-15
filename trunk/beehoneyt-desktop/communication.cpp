#include "communication.h"
#include "ihm.h"

Communication::Communication(QObject *parent) : QObject(parent), client(new QMqttClient(this))
{
    connect(client, SIGNAL(stateChanged(ClientState)), this, SLOT(changementEtat()));
    connect(client, SIGNAL(messageReceived(const QByteArray &, const QMqttTopicName &)), this, SLOT(decoderJson(const QByteArray &)));
}

Communication::~Communication()
{
    client->disconnectFromHost();
    delete client;
}

void Communication::connexionTTN(QString hostname, int port, QString username, QString password)
{
    client->setHostname(hostname);
    client->setPort(port);
    client->setUsername(username);
    client->setPassword(password);
    client->connectToHost();
    qDebug() << Q_FUNC_INFO << hostname << port << username << password;
}

void Communication::souscrireTopic(QString topic)
{
    subscription = client->subscribe(QMqttTopicFilter(topic));
    qDebug() << Q_FUNC_INFO << topic;
}

void Communication::decoderJson(const QByteArray &json)
{
    QJsonDocument documentJSON = QJsonDocument::fromJson(json);
    QByteArray payload;
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
                    emit nouvelleValeurTemperature(temperature.toDouble());
                }
                if(objet.contains("humidite"))
                {
                    QJsonValue humidite = objet.value(QString("humidite"));
                    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Humidité :" << humidite.toDouble() << "%";
                    emit nouvelleValeurHumidite(humidite.toDouble());
                }
                if(objet.contains("ensoleillement"))
                {
                    QJsonValue ensoleillement = objet.value(QString("ensoleillement"));
                    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Ensoleillement :" << ensoleillement.toInt() << "lux";
                    emit nouvelleValeurEnsoleillement(ensoleillement.toInt());
                }
                if(objet.contains("pression"))
                {
                    QJsonValue pression = objet.value(QString("pression"));
                    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Pression :" << pression.toInt() << "Pa";
                    emit nouvelleValeurPression(pression.toInt());
                }
                if(objet.contains("poids"))
                {
                    QJsonValue poids = objet.value(QString("poids"));
                    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Poids :" << poids.toInt() << "grammes";
                    emit nouvelleValeurPoids(poids.toInt());
                }
            }
        }
    }
}

void Communication::changementEtat()
{
    QString message;
    switch(client->state())
    {
        case 0: message = "Déconnecté"; break;
        case 1: message = "En cours de connexion"; break;
        case 2: message = "Connecté"; break;
    }
    qDebug()<< Q_FUNC_INFO << client->state() << message;
}
