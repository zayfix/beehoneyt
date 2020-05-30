#ifndef IHM_H
#define IHM_H

/**
 * @file    Ihm.h
 * @brief   Déclaration de la classe Ihm
 * @author  ACKERMANN Théo
 * @version 0.2
 */

#include <QtWidgets>
#include <QSystemTrayIcon>
#include <QtCharts>
#include <QDebug>
#include <QMessageBox>
#include "ruche.h"

#define NOM_APPLICATION     "Bee Honey't"
#define VERSION_APPLICATION "v0.2"

#define AXE_TEMPERATURE_MIN -10
#define AXE_TEMPERATURE_MAX 50

/**
 * @enum PagesIHM
 * @brief Définit les numéros de page de l'IHM
 */
enum PagesIHM
{
    PAGE_ACCUEIL,       //!< Page principale
    PAGE_VUE_GLOBALE,   //!< Page de la vue globale
    PAGE_GRAPHIQUES,    //!< Page des graphiques
    PAGE_ALERTES,       //!< Page des dernières alertes
    PAGE_REGLAGES_TTN   //!< Page des réglages de TTN
};

class IHMNouvelleRuche;
class IHMReglageRuche;
class Communication;
class Configuration;

namespace Ui {
class ihm;
}

/**
 * @class   Ihm
 * @brief   La fenêtre principale de l'application
 * @author  ACKERMANN Théo
 * @version 0.2
 */

class Ihm : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ihm(QWidget *parent = nullptr);
    ~Ihm();

    void initialiserGraphiques();

    void initialiserGraphiqueTemperatures();
    void initialiserGraphiqueHumidite();
    void initialiserGraphiqueEnsoleillement();
    void initialiserGraphiquePression();
    void initialiserGraphiquePoids();
    void initialiserGraphiqueActivite();

    QString getNomRuche();

public slots:
    void setValeurTemperatureInterieure(QString nomDeLaRuche, double temperatureInterieure, QString horodatage);
    void setValeurTemperatureExterieure(QString nomDeLaRuche, double temperatureExterieure, QString horodatage);
    void setValeurHumidite(QString nomDeLaRuche, double humidite, QString horodatage);
    void setValeurEnsoleillement(QString nomDeLaRuche, int ensoleillement, QString horodatage);
    void setValeurPression(QString nomDeLaRuche, int pression, QString horodatage);
    void setValeurPoids(QString nomDeLaRuche, double poids, QString horodatage);

private slots:
    void on_pushButton_ruches_clicked();
    void on_pushButton_mesures_clicked();
    void on_pushButton_graphiques_clicked();
    void on_pushButton_alertes_clicked();
    void on_pushButton_nouvelle_ruche_clicked();
    void on_pushButton_reglage_clicked();
    void on_pushButton_supprimer_ruche_clicked();
    void on_pushButton_reglage_ttn_clicked();
    void on_pushButton_connexion_ttn_clicked();
    void on_pushButton_enregistrer_configuration_ttn_clicked();

    void changerAbscisseGraphiques();
    void changerDonneesVueGlobale();
    void changerEtatConnexion(int etat);

    void ajouterNouvelleRuche(Ruche ruche);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::ihm *ui;                                    //!< interface utilisateur
    IHMNouvelleRuche *ihmNouvelleRuche;             //!< association vers l'IHM de création d'une nouvelle ruche
    IHMReglageRuche *ihmReglageRuche;               //!< association vers l'IHM de réglage d'une ruche
    QSystemTrayIcon *iconeEtatSysteme;              //!< entrée dans la barre d'état du système
    Communication *communication;                   //!< association vers la classe Communication
    Configuration *configuration;                   //!< association vers la classe Configuration
    QVector<Ruche> ruches;                          //!< les ruches

    QLineSeries *temperatureInterieure;             //!< La courbe de la température intérieure.
    QVector<QPointF> mesuresTemperatureInterieure;  //!< Les mesures pour la courbe de la température intérieure.

    QLineSeries *temperatureExterieure;             //!< La courbe de la température extérieure.
    QVector<QPointF> mesuresTemperatureExterieure;  //!< Les mesures pour la courbe de la température extérieure.

    QLineSeries *humidite;                          //!< La courbe de l'humidite.
    QVector<QPointF> mesuresHumidite;               //!< Les mesures pour la courbe de l'humidité.

    QLineSeries *ensoleillement;                    //!< La courbe de l'ensoleillement.
    QVector<QPointF> mesuresEnsoleillement;         //!< Les mesures pour la courbe de l'ensoleillement.

    QLineSeries *pression;                          //!< La courbe de la pression.
    QVector<QPointF> mesuresPression;               //!< Les mesures pour la courbe de la pression.

    QLineSeries *poids;                             //!< La courbe du poids.
    QVector<QPointF> mesuresPoids;                  //!< Les mesures pour la courbe du poids.

    void chargerIconesBoutons();
    void changerApparenceBouton(PagesIHM);
    void initialiserWidgets();
    void initialiserEvenements();
    void initialiserEntreeBarreEtatSysteme();

    void chargerConfiguration();    
    void demarrerTTN();
    void connecterRuches();

    void afficherGraphiqueTemperatureInterieure();
    void afficherGraphiqueTemperatureExterieure();
    void afficherGraphiqueHumidite();
    void actualiserGraphiqueEnsoleillement();
    void afficherGraphiquePression();
    void afficherGraphiquePoids();

signals:
    void sauvegarderConfigurationTTN(QString hostname, int port, QString username, QString password);

};

#endif // IHM_H
