#include "configuration.h"

/**
 * @file    configuration.cpp
 * @brief   Déclaration de la classe Configuration
 * @author  ACKERMANN Théo
 * @version 0.1
 */

/**
 * @brief Constructeur de la classe Configuration
 *
 * @param parent
 */
Configuration::Configuration(QObject *parent) : QObject(parent), settings(QDir::currentPath() + "/configuration.ini", QSettings::IniFormat)
{
    qDebug() << Q_FUNC_INFO;
    charger();
}

/**
 * @brief Destructeur de la classe Configuration
 *
 */
Configuration::~Configuration()
{
    sauvegarder();
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Méthode pour définir une configuration TTN
 *
 * @param configurationTTN
 */
void Configuration::setConfigurationTTN(ConfigurationTTN configurationTTN)
{
    this->configurationTTN = configurationTTN;
}

/**
 * @brief Méthode pour définir une configuration TTN
 *
 * @param hostname
 * @param port
 * @param username
 * @param password
 */
void Configuration::setConfigurationTTN(QString hostname, int port, QString username, QString password)
{
    configurationTTN.hostname = hostname;
    configurationTTN.port = port;
    configurationTTN.username = username;
    configurationTTN.password = password;
    qDebug() << Q_FUNC_INFO << configurationTTN.hostname << configurationTTN.port <<  configurationTTN.username << configurationTTN.password;
}

/**
 * @brief Méthode pour récupérer la configuration TTN
 *
 * @return ConfigurationTTN
 */
ConfigurationTTN Configuration::getConfigurationTTN() const
{
    return configurationTTN;
}

/**
 * @brief Méthode pour définir une ruche
 *
 * @param ruches
 */
void Configuration::setRuches(QVector<Ruche> ruches)
{
    this->ruches = ruches;
}

/**
 * @brief Méthode pour récupérer une ruche
 *
 * @return QVector<Ruche>
 */
QVector<Ruche> Configuration::getRuches() const
{
    return ruches;
}

/**
 * @brief Méthode qui retourne le topic TTN d'une ruche
 *
 * @param ruche
 * @return QString
 */
QString Configuration::getTopicRuche(QString ruche)
{
    ruche = ruche.replace(" ","");
    ruche = ruche + "/TopicTTN";
    return settings.value(ruche).toString();
}
/**
 * @brief Méthode pour charger la configuration TTN et les ruches depuis le fichier INI
 *
 */
void Configuration::charger()
{
    qDebug() << Q_FUNC_INFO << settings.allKeys() << settings.childKeys();
    chargerConfigurationTTN();
    chargerRuches();
}

/**
 * @brief Méthode pour charger la configuration TTN
 *
 */
void Configuration::chargerConfigurationTTN()
{
    settings.beginGroup("TTN");
    configurationTTN.hostname = settings.value("Hostname").toString();
    configurationTTN.port = settings.value("Port").toInt();
    configurationTTN.username = settings.value("Username").toString();
    configurationTTN.password = settings.value("Password").toString();
    settings.endGroup();
    settings.sync();
    qDebug() << Q_FUNC_INFO << configurationTTN.hostname << configurationTTN.port <<  configurationTTN.username << configurationTTN.password;
}

/**
 * @brief Méthode pour charger les ruches depuis le fichier INI
 *
 */
void Configuration::chargerRuches()
{
    int nbRuches = settings.value("NbRuches", 0).toInt();
    qDebug() << Q_FUNC_INFO << nbRuches;
    for(int i = 0; i < nbRuches; i++)
    {
        Ruche ruche;
        QString nomRuche = "Ruche" + QString::number(i+1);
        settings.beginGroup(nomRuche);
        ruche.nom = settings.value("Nom").toString();
        ruche.topicTTN = settings.value("TopicTTN").toString();
        ruche.miseEnService = settings.value("MiseEnService").toString();
        ruche.adresse = settings.value("Adresse").toString();
        ruche.latitude = settings.value("Latitude").toString();
        ruche.longitude = settings.value("Longitude").toString();
        settings.endGroup();
        ruches.push_back(ruche);
    }
}

/**
 * @brief Méthode pour sauvegarder la configuration TTN et les ruches dans le fichier INI
 *
 */
void Configuration::sauvegarder()
{
    qDebug() << Q_FUNC_INFO;
    sauvegarderConfigurationTTN();
    sauvegarderRuches();
}

/**
 * @brief Méthode pour sauvegarder la configuration TTN dans le fichier INI
 *
 */
void Configuration::sauvegarderConfigurationTTN()
{
    settings.beginGroup("TTN");
    settings.setValue("Hostname", configurationTTN.hostname);
    settings.setValue("Port", configurationTTN.port);
    settings.setValue("Username", configurationTTN.username);
    settings.setValue("Password", configurationTTN.password);
    settings.endGroup();
}

/**
 * @brief Méthode pour sauvegarder les ruches dans le fichier INI
 *
 */
void Configuration::sauvegarderRuches()
{
    qDebug() << Q_FUNC_INFO << ruches.size();
    for(int i = 0; i < ruches.size(); i++)
    {
        QString nomRuche = "Ruche" + QString::number(i+1);
        settings.beginGroup(nomRuche);
        settings.setValue("Nom", ruches[i].nom);
        settings.setValue("TopicTTN", ruches[i].topicTTN);
        settings.setValue("MiseEnService", ruches[i].miseEnService);
        settings.setValue("Adresse", ruches[i].adresse);
        settings.setValue("Latitude", ruches[i].latitude);
        settings.setValue("Longitude", ruches[i].longitude);
        settings.endGroup();
    }
    settings.setValue("NbRuches", ruches.size());
}
