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

    void connexionTTN(QString hostname, int port, QString username, QString password);
    void souscrireTopic(QString topic);

private:
    QString nomDeLaRuche;

    QMqttClient *client;
    QMqttSubscription *subscription;
    Ihm *ihm;

public slots:
    void decoderJson(const QByteArray &json);
    void changementEtat();

signals:
    void nouvelleValeurEnsoleillement(int ensoleillement);
    void nouvelleValeurTemperature(double temperature);
    void nouvelleValeurHumidite(double humidite);
    void nouvelleValeurPression(int pression);
    void nouvelleValeurPoids(int poids);
};

#endif // COMMUNICATION_H
