#include "configuration.h"

Configuration::Configuration(QObject *parent) : QObject(parent), settings(QDir::currentPath() + "/configuration.ini", QSettings::IniFormat)
{
    qDebug() << Q_FUNC_INFO;
    charger();
}

Configuration::~Configuration()
{
    sauvegarder();
    qDebug() << Q_FUNC_INFO;
}

ConfigurationTTN Configuration::getConfigurationTTN() const
{
    return configurationTTN;
}

QVector<Ruche> Configuration::getRuches() const
{
    return ruches;
}

void Configuration::setConfigurationTTN(ConfigurationTTN configurationTTN)
{
    this->configurationTTN = configurationTTN;
}

void Configuration::setConfigurationTTN(QString hostname, int port, QString username, QString password)
{
    configurationTTN.hostname = hostname;
    configurationTTN.port = port;
    configurationTTN.username = username;
    configurationTTN.password = password;
    qDebug() << Q_FUNC_INFO << configurationTTN.hostname << configurationTTN.port <<  configurationTTN.username << configurationTTN.password;
}

void Configuration::setRuches(QVector<Ruche> ruches)
{
    this->ruches = ruches;
}

void Configuration::charger()
{
    qDebug() << Q_FUNC_INFO << settings.allKeys() << settings.childKeys();
    chargerConfigurationTTN();
    chargerRuches();
}

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
        /**
          * @todo Charger l'ensemble des paramètres d'une ruche
          */
        settings.endGroup();
        ruches.push_back(ruche);
    }
}

void Configuration::sauvegarder()
{
    qDebug() << Q_FUNC_INFO;
    sauvegarderConfigurationTTN();
    sauvegarderRuches();
}

void Configuration::sauvegarderConfigurationTTN()
{
    settings.beginGroup("TTN");
    settings.setValue("Hostname", configurationTTN.hostname);
    settings.setValue("Port", configurationTTN.port);
    settings.setValue("Username", configurationTTN.username);
    settings.setValue("Password", configurationTTN.password);
    settings.endGroup();
}

void Configuration::sauvegarderRuches()
{
    qDebug() << Q_FUNC_INFO << ruches.size();
    for(int i = 0; i < ruches.size(); i++)
    {
        QString nomRuche = "Ruche" + QString::number(i+1);
        settings.beginGroup(nomRuche);
        settings.setValue("Nom", ruches[0].nom);
        settings.setValue("TopicTTN", ruches[0].topicTTN);
        /**
          * @todo Sauvegarder l'ensemble des paramètres d'une ruche
          */
        settings.endGroup();
    }
    settings.setValue("NbRuches", ruches.size());
}
