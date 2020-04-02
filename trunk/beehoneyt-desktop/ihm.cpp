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
 * @version 0.2
 */

/**
 * @brief Constructeur de la classe Ihm
 * @param parent
 */
Ihm::Ihm(QWidget *parent) :QMainWindow(parent),ui(new Ui::ihm),ihmNouvelleRuche(new IHMNouvelleRuche),ihmReglageRuche(new IHMReglageRuche()), iconeEtatSysteme(new QSystemTrayIcon(this)), communication(new Communication(this)), configuration(new Configuration(this))
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    chargerConfiguration();
    chargerIconesBoutons();

    initialiserEvenements();
    initialiserWidgets();
    initialiserGraphiques();

    demarrerTTN();

    showMaximized();
}

/**
 * @brief Destructeur de la classe Ihm
 */
Ihm::~Ihm()
{
    delete ihmNouvelleRuche;
    delete ihmReglageRuche;
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
 * @brief Bouton/icône affichant l'onglet des mesures
 */
void Ihm::on_pushButton_mesures_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_VUE_GLOBALE);
    changerApparenceBouton(PagesIHM::PAGE_VUE_GLOBALE);
}

/**
 * @brief Bouton/icône affichant l'onglet des graphiques
 */
void Ihm::on_pushButton_graphiques_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_GRAPHIQUES);
    changerApparenceBouton(PagesIHM::PAGE_GRAPHIQUES);
    afficherGraphiques();
}

/**
 * @brief Bouton/icône affichant l'onglet des alertes
 */
void Ihm::on_pushButton_alertes_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_ALERTES);
    changerApparenceBouton(PagesIHM::PAGE_ALERTES);
}

/**
 * @brief Bouton/icône affichant l'onglet des réglages de connexion TTN
 */
void Ihm::on_pushButton_reglage_ttn_clicked()
{
    chargerConfiguration();
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_REGLAGES_TTN);
    changerApparenceBouton(PagesIHM::PAGE_REGLAGES_TTN);
}

/**
 * @brief Méthode pour changer l'apparence des bouton selon le bouton cliqué
 * @param nomBouton
 */
void Ihm::changerApparenceBouton(PagesIHM page)
{
    if(page == PagesIHM::PAGE_ACCUEIL)
    {
        ui->pushButton_ruches->setStyleSheet("background:#666666;");
        ui->pushButton_mesures->setStyleSheet("");
        ui->pushButton_graphiques->setStyleSheet("");
        ui->pushButton_alertes->setStyleSheet("");
        ui->pushButton_reglage_ttn->setStyleSheet("");
    }
    if(page == PagesIHM::PAGE_VUE_GLOBALE)
    {
        ui->pushButton_ruches->setStyleSheet("");
        ui->pushButton_mesures->setStyleSheet("background:#666666;");
        ui->pushButton_graphiques->setStyleSheet("");
        ui->pushButton_alertes->setStyleSheet("");
        ui->pushButton_reglage_ttn->setStyleSheet("");
    }
    if(page == PagesIHM::PAGE_GRAPHIQUES)
    {
        ui->pushButton_ruches->setStyleSheet("");
        ui->pushButton_mesures->setStyleSheet("");
        ui->pushButton_graphiques->setStyleSheet("background:#666666;");
        ui->pushButton_alertes->setStyleSheet("");
        ui->pushButton_reglage_ttn->setStyleSheet("");
    }
    if(page == PagesIHM::PAGE_ALERTES)
    {
        ui->pushButton_ruches->setStyleSheet("");
        ui->pushButton_mesures->setStyleSheet("");
        ui->pushButton_graphiques->setStyleSheet("");
        ui->pushButton_alertes->setStyleSheet("background:#666666;");
        ui->pushButton_reglage_ttn->setStyleSheet("");
    }
    if(page == PagesIHM::PAGE_REGLAGES_TTN)
    {
        ui->pushButton_ruches->setStyleSheet("");
        ui->pushButton_mesures->setStyleSheet("");
        ui->pushButton_graphiques->setStyleSheet("");
        ui->pushButton_alertes->setStyleSheet("");
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
 * @brief Bouton qui permet d'ouvrir la fenêtre des réglages de la ruche
 */
void Ihm::on_pushButton_reglage_clicked()
{
    ihmReglageRuche->exec();
}

/**
 * @brief Bouton qui permet de supprimer la ruche selectionné
 */
void Ihm::on_pushButton_supprimer_ruche_clicked()
{
    QMessageBox::StandardButton reponse;
    QString nom_ruche = ui->comboBox_liste_ruches->currentText();
    QString question = "Êtes-vous sûr de vouloir supprimer la ruche '" + nom_ruche + "' ?";
    reponse = QMessageBox::question(this,"",question,QMessageBox::Yes|QMessageBox::No);

    if(reponse == QMessageBox::Yes)
    {
        qDebug() << Q_FUNC_INFO << "reponse : Oui";        
        communication->desabonnerTopic(ruches[ui->comboBox_liste_ruches->currentIndex()].topicTTN);
        ruches.remove(ui->comboBox_liste_ruches->currentIndex());
        configuration->setRuches(ruches);
        ui->comboBox_liste_ruches->removeItem(ui->comboBox_liste_ruches->currentIndex());
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "reponse : Non";
    }
}

/**
 * @brief Méthode qui initialise les graphiques
 */
void Ihm::initialiserGraphiques()
{
    initialiserGraphiqueTemperatures();
    initialiserGraphiqueHumidite();
    initialiserGraphiqueEnsoleillement();
    initialiserGraphiquePression();
    initialiserGraphiquePoids();
    //initialiserGraphiqueActivite();
}

/**
 * @brief Méthode qui affiche les nouvelles valeurs dans le graphique
 */
void Ihm::afficherGraphiques()
{
    afficherGraphiqueTemperatureInterieure();
    afficherGraphiqueTemperatureExterieure();
    afficherGraphiqueHumidite();
    afficherGraphiqueEnsoleillement();
    afficherGraphiquePression();
    afficherGraphiquePoids();
}

/**
 * @brief Méthode qui initialise le graphique des températures
 */
void Ihm::initialiserGraphiqueTemperatures()
{
    temperatureInterieure = new QLineSeries();
    temperatureInterieure->setName("Intérieure");
    temperatureInterieure->setPointsVisible(true);

    temperatureExterieure = new QLineSeries();
    temperatureExterieure->setName("Extérieure");
    temperatureExterieure->setPointsVisible(true);

    /* Valeurs de test
    temperatureExterieure->append(0, 35);
    temperatureExterieure->append(1, 37);
    temperatureExterieure->append(2, 35);
    temperatureExterieure->append(3, 34);
    temperatureExterieure->append(4, 31);*/

    QChart *chart = new QChart();
    chart->legend()->show();
    chart->addSeries(temperatureInterieure);
    chart->addSeries(temperatureExterieure);

    chart->createDefaultAxes();
    chart->setTitle("Températures");
    ui->chartView_temperature->setChart(chart);
    ui->chartView_temperature->setRenderHint(QPainter::Antialiasing);

    /**
     * @todo Faire un axeX commun pour tout les graphiques
     */
    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("dd/MM");
    axisX->setTitleText("Jours");
    // ou :
    //axisX->setTickCount(10);
    //axisX->setFormat("hh:mm");
    //axisX->setTitleText("Heure");
    axisX->setMin(QDateTime::currentDateTime().addDays(-3));
    axisX->setMax(QDateTime::currentDateTime().addDays(3));

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("°C");
    axisY->setTickCount((((AXE_TEMPERATURE_MAX - (AXE_TEMPERATURE_MIN))*2)/10)+1);
    axisY->setMin(AXE_TEMPERATURE_MIN);
    axisY->setMax(AXE_TEMPERATURE_MAX);

    chart->setAxisY(axisY);
    chart->setAxisX(axisX);    
}

/**
 * @brief Méthode qui initialise le graphique d'humidité
 */
void Ihm::initialiserGraphiqueHumidite()
{
    humidite = new QLineSeries();
    /* Valeurs de test
    humidite->append(0, 27);
    humidite->append(1, 26);
    humidite->append(2, 28);
    humidite->append(3, 31);
    humidite->append(4, 24);*/

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(humidite);
    chart->setTitle("Humidité");
    ui->chartView_humidite->setChart(chart);
    ui->chartView_humidite->setRenderHint(QPainter::Antialiasing);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("dd/MM");
    axisX->setTitleText("Jours");
    // ou :
    //axisX->setTickCount(10);
    //axisX->setFormat("hh:mm");
    //axisX->setTitleText("Heure");
    axisX->setMin(QDateTime::currentDateTime().addDays(-3));
    axisX->setMax(QDateTime::currentDateTime().addDays(3));

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("%");
    axisY->setTickCount((((AXE_TEMPERATURE_MAX - (AXE_TEMPERATURE_MIN))*2)/10)+1);
    axisY->setMin(AXE_TEMPERATURE_MIN);
    axisY->setMax(AXE_TEMPERATURE_MAX);

    chart->setAxisY(axisY);
    chart->setAxisX(axisX);
}

/**
 * @brief Méthode qui initialise le graphique de l'ensoleillement
 */
void Ihm::initialiserGraphiqueEnsoleillement()
{
    ensoleillement = new QLineSeries();

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(ensoleillement);
    chart->setTitle("Ensoleillement");
    ui->chartView_ensoleillement->setChart(chart);
    ui->chartView_ensoleillement->setRenderHint(QPainter::Antialiasing);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("dd/MM");
    axisX->setTitleText("Jours");
    // ou :
    //axisX->setTickCount(10);
    //axisX->setFormat("hh:mm");
    //axisX->setTitleText("Heure");

    axisX->setMin(QDateTime::currentDateTime().addDays(-3));
    axisX->setMax(QDateTime::currentDateTime().addDays(3));

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("lux");
    axisY->setMin(0);
    axisY->setMax(500);

    chart->setAxisY(axisY);
    chart->setAxisX(axisX);
}

/**
 * @brief Méthode qui initialise le graphique de la pression
 */
void Ihm::initialiserGraphiquePression()
{
    pression = new QLineSeries();
    // Valeurs de test
    pression->append(0, 321);
    pression->append(1, 354);
    pression->append(2, 396);
    pression->append(3, 348);
    pression->append(4, 240);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(pression);
    chart->setTitle("Pression");
    ui->chartView_pression->setChart(chart);
    ui->chartView_pression->setRenderHint(QPainter::Antialiasing);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("dd/MM");
    axisX->setTitleText("Jours");
    // ou :
    //axisX->setTickCount(10);
    //axisX->setFormat("hh:mm");
    //axisX->setTitleText("Heure");

    axisX->setMin(QDateTime::currentDateTime().addDays(-3));
    axisX->setMax(QDateTime::currentDateTime().addDays(3));

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("hPa");
    axisY->setMin(0);
    axisY->setMax(500);

    chart->setAxisY(axisY);
    chart->setAxisX(axisX);
}

/**
 * @brief Méthode qui initialise le graphique du poids
 */
void Ihm::initialiserGraphiquePoids()
{
    poids = new QLineSeries();
    // Valeurs de test
    poids->append(0, 321);
    poids->append(1, 354);
    poids->append(2, 396);
    poids->append(3, 348);
    poids->append(4, 240);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(poids);
    chart->setTitle("Poids");
    ui->chartView_poids->setChart(chart);
    ui->chartView_poids->setRenderHint(QPainter::Antialiasing);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("dd/MM");
    axisX->setTitleText("Jours");
    // ou :
    //axisX->setTickCount(10);
    //axisX->setFormat("hh:mm");
    //axisX->setTitleText("Heure");

    axisX->setMin(QDateTime::currentDateTime().addDays(-3));
    axisX->setMax(QDateTime::currentDateTime().addDays(3));

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Kg");
    axisY->setMin(0);
    axisY->setMax(500);

    chart->setAxisY(axisY);
    chart->setAxisX(axisX);
}

/**
 * @brief Méthode qui permet de change l'abscisse des graphiques
 */
void Ihm::changerAbscisseGraphiques()
{
    switch(ui->comboBox_reglages_graphiques->currentIndex())
    {
        case 0:
            qDebug() << Q_FUNC_INFO << "reponse : 1j";
            //axisX->setTickCount(10);
            //axisX->setFormat("hh:mm");
            //axisX->setTitleText("Heure");
            break;
        case 1:
            qDebug() << Q_FUNC_INFO << "reponse : 7j";
            //axisX->setTickCount(7);
            //axisX->setFormat("dd/MM");
            //axisX->setTitleText("Jours");
            break;
        default:
            qDebug() << Q_FUNC_INFO << ui->comboBox_reglages_graphiques->currentIndex();
     }
}

/**
 * @brief Méthode permettant de changer la données affiché sur la vue globale
 */
void Ihm::changerDonneesVueGlobale()
{
    switch(ui->comboBox_donnees_affiche->currentIndex())
    {
        case 0:
            qDebug() << Q_FUNC_INFO << "Temperature";
            break;
        case 1:
            qDebug() << Q_FUNC_INFO << "Humidité";
            break;
        default:
            qDebug() << Q_FUNC_INFO << ui->comboBox_reglages_graphiques->currentIndex();
     }
}

/**
 * @brief Change l'état de connexion TTN dans l'IHM
 * 
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
 * 
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
    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques.png"));
    ui->pushButton_alertes->setIcon(QIcon(":/alertes.png"));
    ui->pushButton_reglage_ttn->setIcon(QIcon(":/reglages.png"));
    ui->pushButton_mesures->setIcon(QIcon(":/vue_globale.png"));
}

/**
 * @brief Initialise les différents widgets de l'IHM
 */
void Ihm::initialiserWidgets()
{
    this->setWindowTitle(NOM_APPLICATION);
    ui->label_version->setText(VERSION_APPLICATION);

    ui->comboBox_liste_ruches->addItem("Nom de la ruche");

    ui->comboBox_reglages_graphiques->addItem("1 jour");
    ui->comboBox_reglages_graphiques->addItem("7 jours");

    ui->comboBox_donnees_affiche->addItem("Température");
    ui->comboBox_donnees_affiche->addItem("Humidité");
}

/**
 * @brief Assure la connexion signal/slot
 */
void Ihm::initialiserEvenements()
{
    connect(ui->comboBox_reglages_graphiques, SIGNAL(currentIndexChanged(int)), SLOT(changerAbscisseGraphiques()));
    connect(ui->comboBox_donnees_affiche, SIGNAL(currentIndexChanged(int)), SLOT(changerDonneesVueGlobale()));

    // Configuration
    connect(this, SIGNAL(sauvegarderConfigurationTTN(QString,int,QString,QString)), configuration, SLOT(setConfigurationTTN(QString,int,QString,QString)));

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
 * @brief Méthode pour définir la température intérieure dans l'IHM
 * 
 * @param temperatureInterieure
 */
void Ihm::setValeurTemperatureInterieure(QString nomDeLaRuche, double temperatureInterieure, QString horodatage)
{
    if(ruches[ui->comboBox_liste_ruches->currentIndex()].topicTTN.contains(nomDeLaRuche))
    {
        ui->lcdNumber_temperature_interieure->display(temperatureInterieure);
        QString temps = horodatage;
        ui->label_maj_temp_int->setText(temps);
    }
    /**
     * @todo Intégrer l'horodatage pour la mesure (cf. toMSecsSinceEpoch() de la classe QDateTime) pour l'instant l'axe X est une valeur 0,1, ...
     */
    QPointF mesure(mesuresTemperatureInterieure.size(), temperatureInterieure);
    mesuresTemperatureInterieure.push_back(mesure);
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
    if(ruches[ui->comboBox_liste_ruches->currentIndex()].topicTTN.contains(nomDeLaRuche))
    {
        ui->lcdNumber_temperature_exterieure->display(temperatureExterieure);
        QString temps = horodatage;
        ui->label_maj_temp_ext->setText(temps);
    }
    QPointF mesure(mesuresTemperatureExterieure.size(), temperatureExterieure);
    mesuresTemperatureExterieure.push_back(mesure);
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
    if(ruches[ui->comboBox_liste_ruches->currentIndex()].topicTTN.contains(nomDeLaRuche))
    {
        ui->lcdNumber_humidite->display(humidite);
        QString temps = horodatage;
        ui->label_maj_humidite->setText(temps);
    }
    QPointF mesure(mesuresHumidite.size(), humidite);
    mesuresHumidite.push_back(mesure);
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
    if(ruches[ui->comboBox_liste_ruches->currentIndex()].topicTTN.contains(nomDeLaRuche))
    {
        ui->lcdNumber_ensoleillement->display(ensoleillement);
        QString temps = horodatage;
        ui->label_maj_luminosite->setText(temps);
    }
    QPointF mesure(mesuresEnsoleillement.size(), ensoleillement);
    mesuresEnsoleillement.push_back(mesure);
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
    if(ruches[ui->comboBox_liste_ruches->currentIndex()].topicTTN.contains(nomDeLaRuche))
    {
        ui->lcdNumber_pression->display(pression);
        QString temps = horodatage;
        ui->label_maj_pression->setText(temps);
    }
    QPointF mesure(mesuresPression.size(), pression);
    mesuresPression.push_back(mesure);
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
    if(ruches[ui->comboBox_liste_ruches->currentIndex()].topicTTN.contains(nomDeLaRuche))
    {
        ui->lcdNumber_poids->display(poids);
        QString temps = horodatage;
        ui->label_maj_poids->setText(temps);
    }
    QPointF mesure(mesuresPoids.size(), poids);
    mesuresPoids.push_back(mesure);
    qDebug() << Q_FUNC_INFO << nomDeLaRuche << "Nouveau poids :" << poids;
}

/**
 * @brief Bouton pour enregistrer la configuration TTN dans le fichier INI
 */
void Ihm::on_pushButton_enregistrer_configuration_ttn_clicked()
{
    emit sauvegarderConfigurationTTN(ui->lineEdit_host->text(), ui->spinBox_port->value(), ui->lineEdit_username->text(), ui->lineEdit_password->text());
}

/**
 * @brief Méthode pour ajouter une nouvelle ruche
 * 
 * @param ruche
 */
void Ihm::ajouterNouvelleRuche(Ruche ruche)
{
    qDebug() << Q_FUNC_INFO << ruche.nom << ruche.topicTTN;
    if(ui->comboBox_liste_ruches->currentText() == "Nom de la ruche")
        ui->comboBox_liste_ruches->clear();
    ui->comboBox_liste_ruches->addItem(ruche.nom);
    communication->souscrireTopic(ruche.topicTTN);
    ruches.push_back(ruche);
    configuration->setRuches(ruches);
}

/**
 * @brief Méthode pour charger la configuration TTN
 */
void Ihm::chargerConfiguration()
{
    ConfigurationTTN configurationTTN = configuration->getConfigurationTTN();
    ui->lineEdit_host->setText(configurationTTN.hostname);
    ui->spinBox_port->setValue(configurationTTN.port);
    ui->lineEdit_username->setText(configurationTTN.username);
    ui->lineEdit_password->setText(configurationTTN.password);

    ruches = configuration->getRuches();
}

/**
 * @brief Méthode pour démarrer TTN
 */
void Ihm::demarrerTTN()
{
    ConfigurationTTN configurationTTN = configuration->getConfigurationTTN();
    communication->connecterTTN(configurationTTN.hostname, configurationTTN.port, configurationTTN.username, configurationTTN.password);
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
 * @brief Méthode qui met à jour les mesures de la température intérieure dans le graphique associée
 */
void Ihm::afficherGraphiqueTemperatureInterieure()
{
    temperatureInterieure->clear();
    for(int i=0;i<mesuresTemperatureInterieure.size();i++)
        temperatureInterieure->append(mesuresTemperatureInterieure[i]);
}

/**
 * @brief Méthode qui met à jour les mesures de la température extérieure dans le graphique associée
 */
void Ihm::afficherGraphiqueTemperatureExterieure()
{
    temperatureExterieure->clear();
    for(int i=0;i<mesuresTemperatureExterieure.size();i++)
        temperatureExterieure->append(mesuresTemperatureExterieure[i]);
}

/**
 * @brief Méthode qui met à jour les mesures de l'humidité dans le graphique associée
 */
void Ihm::afficherGraphiqueHumidite()
{
    humidite->clear();
    for(int i=0;i<mesuresHumidite.size();i++)
        humidite->append(mesuresHumidite[i]);
}

/**
 * @brief Méthode qui met à jour les mesures de l'ensoleillement dans le graphique associée
 */
void Ihm::afficherGraphiqueEnsoleillement()
{
    ensoleillement->clear();
    for(int i=0;i<mesuresEnsoleillement.size();i++)
        ensoleillement->append(mesuresEnsoleillement[i]);
}

/**
 * @brief Méthode qui met à jour les mesures de la pression dans le graphique associée
 */
void Ihm::afficherGraphiquePression()
{
    pression->clear();
    for(int i=0;i<mesuresPression.size();i++)
        pression->append(mesuresPression[i]);
}

/**
 * @brief Méthode qui met à jour les mesures du poids dans le graphique associée
 */
void Ihm::afficherGraphiquePoids()
{
    poids->clear();
    for(int i=0;i<mesuresPoids.size();i++)
        poids->append(mesuresPoids[i]);
}
