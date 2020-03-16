#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QDateTime>
#include <QObject>
#include "ruche.h"

/**
 * @brief Structure qui définit la configuration MQTT pour se connecter au réseau TheThingsNetwork (TTN)
 * @struct ConfigurationTTN
 */
struct ConfigurationTTN
{
    QString hostname;   //!< le nom du serveur TTN
    int port;           //!< le numero de port TTN
    QString username;   //!< le compte d'accès TTN
    QString password;   //!< le mote de passe du compte TTN
};

class Configuration : public QObject
{
    Q_OBJECT

public:
    Configuration(QObject *parent = nullptr);
    ~Configuration();

    ConfigurationTTN getConfigurationTTN() const;
    QVector<Ruche> getRuches() const;

public slots:
    void setConfigurationTTN(ConfigurationTTN configurationTTN);
    void setConfigurationTTN(QString hostname, int port, QString username, QString password);
    void setRuches(QVector<Ruche> ruches);

private:
    QSettings settings; //!< objet pour gérer un fichier .ini
    ConfigurationTTN configurationTTN; //!< configuration MQTT pour se connecter au réseau TheThingsNetwork (TTN)
    QVector<Ruche> ruches;

    void charger();
    void chargerConfigurationTTN();
    void chargerRuches();
    void sauvegarder();
    void sauvegarderConfigurationTTN();
    void sauvegarderRuches();
};

#endif // CONFIGURATION_H
