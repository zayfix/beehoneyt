#ifndef IHM_H
#define IHM_H

/**
 * @file    Ihm.h
 * @brief   Déclaration de la classe Ihm
 * @author  ACKERMANN Théo
 * @version 0.1
 */

#include <QtWidgets>
#include <QSystemTrayIcon>
#include <QtCharts>
#include <QDebug>
#include <QMessageBox>
#include "ruche.h"

#define NOM_APPLICATION     "Bee Honey't"
#define VERSION_APPLICATION "v0.1"

#define AXE_TEMPERATURE_MIN -10
#define AXE_TEMPERATURE_MAX 50

/**
 * @enum PagesIHM
 * @brief Définit les numéros de page de l'IHM
 *
 */
enum PagesIHM
{
    PAGE_ACCUEIL,       //!< Page principale
    PAGE_MESURES,       //!< Page
    PAGE_TABLEAUX,      //!< Page
    PAGE_GRAPHIQUES,    //!< Page des graphiques
    PAGE_ALERTES,       //!< Page des dernières alertes
    PAGE_REGLAGES_TTN    //!< Page des réglages de TTN
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
 * @version 0.1
 */
class Ihm : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ihm(QWidget *parent = nullptr);
    ~Ihm();

    void initialiserGraphiques();

    void initialiserGraphiqueTemperature();
    void initialiserGraphiqueHumidite();
    void initialiserGraphiqueLuminosite();
    void initialiserGraphiquePression();
    void initialiserGraphiquePoids();
    void initialiserGraphiqueActivite();

    void setValeurGraphique(QLineSeries *serie, int x, int y);

public slots:
    void setValeurTemperatureInterieure(QString nomDeLaRuche, double temperature, QString horodatage);
    void setValeurTemperatureExterieure(QString nomDeLaRuche, double temperature, QString horodatage);
    void setValeurHumidite(QString nomDeLaRuche, double humidite, QString horodatage);
    void setValeurEnsoleillement(QString nomDeLaRuche, int ensoleillement, QString horodatage);
    void setValeurPression(QString nomDeLaRuche, int pression, QString horodatage);
    void setValeurPoids(QString nomDeLaRuche, double poids, QString horodatage);

private slots:
    void on_pushButton_ruches_clicked();
    void on_pushButton_mesures_clicked();
    void on_pushButton_tableaux_clicked();
    void on_pushButton_graphiques_clicked();
    void on_pushButton_alertes_clicked();
    void on_pushButton_nouvelle_ruche_clicked();
    void on_pushButton_reglage_clicked();
    void on_pushButton_supprimer_ruche_clicked();
    void on_pushButton_reglage_ttn_clicked();
    void on_pushButton_connexion_ttn_clicked();
    void on_pushButton_enregistrer_configuration_ttn_clicked();

    void changerAbscisseGraphiques();
    void changerDonneesVueGlobal();
    void changerEtatConnexion(int etat);

    void ajouterNouvelleRuche(Ruche ruche);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::ihm *ui; //!< interface utilisateur
    IHMNouvelleRuche *ihmNouvelleRuche; //!< association vers l'IHM de création d'une nouvelle ruche
    IHMReglageRuche *ihmReglageRuche; //!< association vers l'IHM de réglage d'une ruche
    QSystemTrayIcon *iconeEtatSysteme; //!< entrée dans la barre d'état du système
    Communication *communication;
    Configuration *configuration;
    QVector<Ruche> ruches; //!< les ruches
    QLineSeries *temperatureInterieure; //!< la courbe température intérieure
    QVector<QPointF> mesuresTemperatureInterieure; //!< les mesures pour la courbe température intérieure

    void chargerIconesBoutons();
    void changerApparenceBouton(QString nomBouton);
    void initialiserWidgets();
    void initialiserEvenements();
    void initialiserEntreeBarreEtatSysteme();

    void chargerConfiguration();    
    void demarrerTTN();
    void connecterRuches();

    void afficherGraphiqueTemperatureInterieure();

signals:
    void sauvegarderConfigurationTTN(QString hostname, int port, QString username, QString password);


};

#endif // IHM_H
