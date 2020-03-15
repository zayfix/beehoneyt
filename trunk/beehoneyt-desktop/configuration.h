#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QDateTime>
#include <QObject>

class Configuration : public QObject
{
    Q_OBJECT

public:
    Configuration(QObject *parent = nullptr);
    ~Configuration();

public slots:
    void sauvegarderConfigurationTTN(QString hostname, int port, QString username, QString password);
    void sauvegarderValeursRuches();

private:
    bool fichierExistant();


};

#endif // CONFIGURATION_H
