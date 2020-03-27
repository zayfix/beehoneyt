#ifndef IHM_H
#define IHM_H

/**
 * @file    Ihm.h
 * @brief   Déclaration de la classe Ihm
 * @author  ACKERMANN Théo
 * @version 1.0
 */

#include <QtWidgets>
#include <QSystemTrayIcon>
#include <QtCharts>
#include <QDebug>
#include <QMessageBox>
#include "ruche.h"

#define NOM_APPLICATION     "Bee Honey't"
#define VERSION_APPLICATION "v1.0"

/**
 * @enum PagesIHM
 * @brief Définit les numéros de page de l'IHM
 *
 */
enum PagesIHM
{
    PAGE_ACCUEIL,       //!< Page principale
    PAGE_REGLAGES_TTN    //!< Page des réglages de TTN
};

class IHMNouvelleRuche;
class Communication;

namespace Ui {
class ihm;
}

/**
 * @class   Ihm
 * @brief   La fenêtre principale de l'application
 * @author  ACKERMANN Théo
 * @version 1.0
 */
class Ihm : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ihm(QWidget *parent = nullptr);
    ~Ihm();

public slots:
    void setValeurTemperatureInterieure(QString nomDeLaRuche, double temperature, QString horodatage);
    void setValeurTemperatureExterieure(QString nomDeLaRuche, double temperature, QString horodatage);
    void setValeurHumidite(QString nomDeLaRuche, double humidite, QString horodatage);
    void setValeurEnsoleillement(QString nomDeLaRuche, int ensoleillement, QString horodatage);
    void setValeurPression(QString nomDeLaRuche, int pression, QString horodatage);
    void setValeurPoids(QString nomDeLaRuche, double poids, QString horodatage);

private slots:
    void on_pushButton_ruches_clicked();
    void on_pushButton_nouvelle_ruche_clicked();
    void on_pushButton_reglage_ttn_clicked();
    void on_pushButton_connexion_ttn_clicked();

    void changerEtatConnexion(int etat);

    void ajouterNouvelleRuche(Ruche ruche);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::ihm *ui; //!< interface utilisateur
    IHMNouvelleRuche *ihmNouvelleRuche; //!< association vers l'IHM de création d'une nouvelle ruche
    QSystemTrayIcon *iconeEtatSysteme; //!< entrée dans la barre d'état du système
    Communication *communication;
    QVector<Ruche> ruches; //!< les ruches

    void chargerIconesBoutons();
    void changerApparenceBouton(PagesIHM);
    void initialiserWidgets();
    void initialiserEvenements();
    void initialiserEntreeBarreEtatSysteme();
    void connecterRuches();

};

#endif // IHM_H
