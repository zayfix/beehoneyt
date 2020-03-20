#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/**
 * @file    communication.h
 * @brief   Déclaration de la classe Communication
 * @author  ACKERMANN Théo
 * @version 0.1
 */

#include <QObject>
#include <QtMqtt/QtMqtt>
#include <QDebug>


class Ihm;

/**
 * @class   Communication
 * @brief   Permet de recevoir les données
 * @author  ACKERMANN Théo
 * @version 0.1
 */

class Communication  : public QObject
{
    Q_OBJECT

public:
    Communication(QObject *parent = nullptr);
    ~Communication();

    void connecterTTN(QString hostname, int port, QString username, QString password);
    void souscrireTopic(QString topic);
    void desabonnerTopic(QString topic);

private:
    QMqttClient *client;
    QMqttSubscription *subscription;
    Ihm *ihm;

public slots:
    void decoderJson(const QByteArray &json);
    void changerEtatConnexion();

signals:
    void nouvelleValeurTemperature(QString nomDeLaRuche, double temperature);
    void nouvelleValeurTemperatureExterieure(QString nomDeLaRuche, double temperatureExterieure);
    void nouvelleValeurEnsoleillement(QString nomDeLaRuche, int ensoleillement);
    void nouvelleValeurHumidite(QString nomDeLaRuche, double humidite);
    void nouvelleValeurPression(QString nomDeLaRuche, int pression);
    void nouvelleValeurPoids(QString nomDeLaRuche, double poids);
    void nouvelEtatConnexion(int etat);
};

#endif // COMMUNICATION_H
