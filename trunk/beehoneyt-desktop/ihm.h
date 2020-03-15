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
#include <QMessageBox>
#include <QDebug>

#define NOM_APPLICATION     "Bee Honey't"
#define VERSION_APPLICATION "v0.1"

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

    void demarrerGraphiques();

    void graphiqueTemperature();
    void graphiqueHumidite();
    void graphiqueLuminosite();
    void graphiquePression();
    void graphiquePoids();
    void graphiqueActivite();

    void setValeurGraphique(QLineSeries *serie, int x, int y);

public slots:
    void setValeurTemperatureInterieure(double temperature);
    //void setValeurTemperatureExterieure(double temperature);
    void setValeurHumidite(double humidite);
    void setValeurEnsoleillement(int ensoleillement);
    void setValeurPression(int pression);
    void setValeurPoids(int poids);

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
    void on_pushButton_subscribe_ttn_clicked();
    void on_pushButton_enregistrer_configuration_ttn_clicked();

    void changerAbscisseGraphiques();
    void changerDonneesVueGlobal();

    void ajouterNouvelleRuche(QString, QString);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::ihm *ui; //!< interface utilisateur
    IHMNouvelleRuche *ihmNouvelleRuche; //!< association vers l'IHM de création d'une nouvelle ruche
    IHMReglageRuche *ihmReglageRuche; //!< association vers l'IHM de réglage d'une ruche
    QSystemTrayIcon *iconeEtatSysteme; //!< entrée dans la barre d'état du système
    Communication *communication;
    Configuration *configuration;

    void chargerIconesBoutons();
    void initialiserWidgets();
    void initialiserEvenements();
    void initialiserEntreeBarreEtatSysteme();

signals:
    void sauvegarderConfigurationTTN(QString hostname, int port, QString username, QString password);


};

#endif // IHM_H
