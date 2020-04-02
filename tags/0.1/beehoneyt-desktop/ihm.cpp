#include "ihm.h"
#include "ui_ihm.h"
#include "nouvelleruche.h"
#include "reglageruche.h"
#include "communication.h"
#include "configuration.h"

/**
 * @file    ihm.cpp
 * @brief   Déclaration de la classe Ihm
 * @author  ACKERMANN Théo
 * @version 0.1
 */

/**
 * @brief Constructeur de la classe Ihm
 * @param parent
 */
Ihm::Ihm(QWidget *parent) :QMainWindow(parent),ui(new Ui::ihm),ihmNouvelleRuche(new IHMNouvelleRuche), iconeEtatSysteme(new QSystemTrayIcon(this)), communication(new Communication(this))
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    chargerIconesBoutons();

    initialiserEvenements();
    initialiserWidgets();

    showMaximized();
}

/**
 * @brief Destructeur de la classe Ihm
 */
Ihm::~Ihm()
{
    delete ihmNouvelleRuche;
    delete ui;
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Bouton/icône affichant l'onglet des données de la ruche selectionné
 */
void Ihm::on_pushButton_ruches_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_ACCUEIL);
    changerApparenceBouton(PagesIHM::PAGE_ACCUEIL);
}

/**
 * @brief Bouton/icône affichant l'onglet des réglages de connexion TTN
 */
void Ihm::on_pushButton_reglage_ttn_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_REGLAGES_TTN);
    changerApparenceBouton(PagesIHM::PAGE_REGLAGES_TTN);
}

/**
 * @brief Méthode pour changer l'apparence des bouton selon le bouton cliqué
 *
 * @param nomBouton
 */
void Ihm::changerApparenceBouton(PagesIHM page)
{
    if(page == PagesIHM::PAGE_ACCUEIL)
    {
        ui->pushButton_ruches->setStyleSheet("background:#666666;");
        ui->pushButton_reglage_ttn->setStyleSheet("");
    }
    if(page == PagesIHM::PAGE_REGLAGES_TTN)
    {
        ui->pushButton_ruches->setStyleSheet("");
        ui->pushButton_reglage_ttn->setStyleSheet("background:#666666;");
    }
}

/**
 * @brief Bouton qui permet de démarrer la connexion avec TTN
 */
void Ihm::on_pushButton_connexion_ttn_clicked()
{
    communication->connecterTTN(ui->lineEdit_host->text(), ui->spinBox_port->value(), ui->lineEdit_username->text(), ui->lineEdit_password->text());
}

/**
 * @brief Bouton qui permet d'ouvrir la fenêtre de création du nouvelle ruche
 */
void Ihm::on_pushButton_nouvelle_ruche_clicked()
{
    ihmNouvelleRuche->exec();
}

/**
 * @brief Change l'état de connexion TTN dans l'IHM
 * @param etat
 */
void Ihm::changerEtatConnexion(int etat)
{
    switch(etat)
    {
        case 0:
            ui->label_etat_connexion->setPixmap(QPixmap(":/off.png"));
            ui->pushButton_connexion_ttn->setText("Connecter");
            break;
        case 1:
            ui->label_etat_connexion->setPixmap(QPixmap(":/connexion.png"));
            break;
        case 2:
            ui->label_etat_connexion->setPixmap(QPixmap(":/on.png"));
            ui->pushButton_connexion_ttn->setText("Déconnecter");
            connecterRuches();
            break;
    }
}

/**
 * @brief Méthode redéfinie qui s'exécute pour chaque évènement reçu par la fenêtre principale
 * @param event
 */
void Ihm::closeEvent(QCloseEvent *event)
{
    if (iconeEtatSysteme->isVisible())
    {
        QMessageBox::information(this, NOM_APPLICATION, "Utiliser le menu Quitter pour mettre fin à l'application.");
        hide();
        event->ignore();
    }
}

/**
 * @brief Méthode pour charger les icônes des boutons
 */
void Ihm::chargerIconesBoutons()
{
    ui->pushButton_ruches->setIcon(QIcon(":/ruche.png"));
    ui->pushButton_reglage_ttn->setIcon(QIcon(":/reglages.png"));
}

/**
 * @brief Initialise les différents widgets de l'IHM
 */
void Ihm::initialiserWidgets()
{
    this->setWindowTitle(NOM_APPLICATION);
    ui->label_version->setText(VERSION_APPLICATION);

    chargerIconesBoutons();
    ui->comboBox_liste_ruches->addItem("Nom de la ruche");
}

/**
 * @brief Assure la connexion signal/slot
 */
void Ihm::initialiserEvenements()
{
    // Ajouter une nouvelle ruche
    connect(ihmNouvelleRuche, SIGNAL(nouvelleRuche(Ruche)), this, SLOT(ajouterNouvelleRuche(Ruche)));

    // Afficher valeur reçue TTN
    connect(communication, SIGNAL(nouvelleValeurTemperature(QString,double,QString)), this, SLOT(setValeurTemperatureInterieure(QString,double,QString)));
    connect(communication, SIGNAL(nouvelleValeurTemperatureExterieure(QString,double,QString)), this, SLOT(setValeurTemperatureExterieure(QString,double,QString)));
    connect(communication, SIGNAL(nouvelleValeurHumidite(QString,double,QString)), this, SLOT(setValeurHumidite(QString,double,QString)));
    connect(communication, SIGNAL(nouvelleValeurEnsoleillement(QString,int,QString)), this, SLOT(setValeurEnsoleillement(QString,int,QString)));
    connect(communication, SIGNAL(nouvelleValeurPression(QString,int,QString)), this, SLOT(setValeurPression(QString,int,QString)));
    connect(communication, SIGNAL(nouvelleValeurPoids(QString,double,QString)), this, SLOT(setValeurPoids(QString,double,QString)));

    // Communication
    connect(communication, SIGNAL(nouvelEtatConnexion(int)), this, SLOT(changerEtatConnexion(int)));
}

/**
 * @brief Initialise l'entrée dans la barre d'état du système
 */
void Ihm::initialiserEntreeBarreEtatSysteme()
{
    // Crée les actions pour l'application
    QAction *actionMinimiser = new QAction(QString::fromUtf8("Minimiser"), this);
    QAction *actionMaximiser = new QAction(QString::fromUtf8("Maximiser"), this);
    QAction *actionRestaurer = new QAction(QString::fromUtf8("Restaurer"), this);
    QAction *actionQuitter = new QAction(QString::fromUtf8("&Quitter"), this);

    // Connecte les actions
    connect(actionMinimiser, SIGNAL(triggered(bool)), this, SLOT(hide()));
    connect(actionMaximiser, SIGNAL(triggered(bool)), this, SLOT(showMaximized()));
    connect(actionRestaurer, SIGNAL(triggered(bool)), this, SLOT(showNormal()));
    connect(actionQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));

    // Crée le menu pour l'entrée dans la barre d'état système
    QMenu * menuEtatSysteme = new QMenu(this);
    menuEtatSysteme->addAction(actionMinimiser);
    menuEtatSysteme->addAction(actionMaximiser);
    menuEtatSysteme->addAction(actionRestaurer);
    menuEtatSysteme->addSeparator();
    menuEtatSysteme->addAction(actionQuitter);

    // Crée l'entrée pour la barre d'état système
    iconeEtatSysteme->setContextMenu(menuEtatSysteme);
    iconeEtatSysteme->setToolTip(NOM_APPLICATION);
    // Crée l'icône pour la barre d'état système
    QIcon iconeRuche(":/ruche.png");
    iconeEtatSysteme->setIcon(iconeRuche);
    setWindowIcon(iconeRuche);

    iconeEtatSysteme->show();
}

/**
 * @brief Méthode pour ajouter une nouvelle ruche
 * @param ruche
 */
void Ihm::ajouterNouvelleRuche(Ruche ruche)
{
    qDebug() << Q_FUNC_INFO << ruche.nom << ruche.topicTTN;
    if(ui->comboBox_liste_ruches->currentText() == "Nom de la ruche")
        ui->comboBox_liste_ruches->clear();
    ui->comboBox_liste_ruches->addItem(ruche.nom);
    communication->souscrireTopic(ruche.topicTTN);
}

/**
 * @brief Méthode pour s'abonner à un topic
 */
void Ihm::connecterRuches()
{
    qDebug() << Q_FUNC_INFO << ruches.size();
    if(ruches.size() > 0)
        ui->comboBox_liste_ruches->clear();
    for(int i = 0; i < ruches.size(); i++)
    {
        qDebug() << Q_FUNC_INFO << ruches[i].nom << ruches[i].topicTTN;
        communication->souscrireTopic(ruches[i].topicTTN);
        ui->comboBox_liste_ruches->addItem(ruches[i].nom);
    }
}

/**
 * @brief Méthode pour définir la température intérieure dans l'IHM
 *
 * @param nomDeLaRuche
 * @param temperatureInterieure
 * @param horodatage
 */
void Ihm::setValeurTemperatureInterieure(QString nomDeLaRuche, double temperatureInterieure, QString horodatage)
{
    ui->lcdNumber_temperature_interieure->display(temperatureInterieure);
    QString temps = horodatage;
    ui->label_maj_temp_int->setText(temps);
    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Nouvelle température intérieure :" << temperatureInterieure;
}

/**
 * @brief Méthode pour définir la température extérieure dans l'IHM
 *
 * @param nomDeLaRuche
 * @param temperatureInterieure
 * @param horodatage
 */
void Ihm::setValeurTemperatureExterieure(QString nomDeLaRuche, double temperatureExterieure, QString horodatage)
{
    ui->lcdNumber_temperature_exterieure->display(temperatureExterieure);
    QString temps = horodatage;
    ui->label_maj_temp_ext->setText(temps);
    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Nouvelle température extérieure :" << temperatureExterieure;
}


/**
 * @brief Méthode pour définir l'humidite dans l'IHM
 *
 * @param nomDeLaRuche
 * @param humidite
 * @param horodatage
 */
void Ihm::setValeurHumidite(QString nomDeLaRuche, double humidite, QString horodatage)
{
    ui->lcdNumber_humidite->display(humidite);
    QString temps = horodatage;
    ui->label_maj_humidite->setText(temps);
    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Nouvelle humidité :" << humidite;
}

/**
 * @brief Méthode pour définir l'ensoleillement dans l'IHM
 *
 * @param nomDeLaRuche
 * @param ensoleillement
 * @param horodatage
 */
void Ihm::setValeurEnsoleillement(QString nomDeLaRuche, int ensoleillement, QString horodatage)
{
    ui->lcdNumber_ensoleillement->display(ensoleillement);
    QString temps = horodatage;
    ui->label_maj_luminosite->setText(temps);
    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Nouvelle ensoleillement :" << ensoleillement;
}

/**
 * @brief Méthode pour définir la pression dans l'IHM
 *
 * @param nomDeLaRuche
 * @param pression
 * @param horodatage
 */
void Ihm::setValeurPression(QString nomDeLaRuche, int pression, QString horodatage)
{
    ui->lcdNumber_pression->display(pression);
    QString temps = horodatage;
    ui->label_maj_pression->setText(temps);
    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Nouvelle pression :" << pression;
}

/**
 * @brief Méthode pour définir le poids dans l'IHM
 *
 * @param nomDeLaRuche
 * @param poids
 * @param horodatage
 */
void Ihm::setValeurPoids(QString nomDeLaRuche, double poids, QString horodatage)
{
    poids = poids*0.001; // valeur à un dixième
    ui->lcdNumber_poids->display(poids);
    QString temps = horodatage;
    ui->label_maj_poids->setText(temps);
    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Nouveau poids :" << poids;
}
