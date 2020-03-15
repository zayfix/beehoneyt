#include "configuration.h"

Configuration::Configuration(QObject *parent) : QObject(parent)
{
    if(!fichierExistant())
    {
        QSettings* settings = new QSettings(QDir::currentPath() + "/configuration.ini", QSettings::IniFormat);
        QString temps = QDateTime::currentDateTime().toString();
        settings->setValue("Date_creation_du_fichier", temps);
        settings->sync();
        qDebug() << Q_FUNC_INFO << "Fichier crée.";
    }
}

Configuration::~Configuration()
{

}

void Configuration::sauvegarderConfigurationTTN(QString hostname, int port, QString username, QString password)
{
    QSettings* settings = new QSettings(QDir::currentPath() + "/configuration.ini", QSettings::IniFormat);
    settings->beginGroup("TTN");
    settings->setValue("Hostname",hostname);
    settings->setValue("Port",port);
    settings->setValue("Username",username);
    settings->setValue("Password",password);
    settings->endGroup();
    settings->sync();
}

void Configuration::sauvegarderValeursRuches()
{

}

bool Configuration::fichierExistant()
{
    QString fileName("./configuration.ini");
    QFile file(fileName);
    if(QFileInfo::exists(fileName))
    {
        qDebug() << Q_FUNC_INFO << "Le fichier de configuration existe.";
        return true;
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Le fichier de configuration n'existe pas, création du fichier..";
        return false;
    }
}
