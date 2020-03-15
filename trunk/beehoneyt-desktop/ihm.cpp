#include "ihm.h"
#include "ui_ihm.h"
#include "nouvelleruche.h"
#include "reglageruche.h"
#include "communication.h"
#include "configuration.h"

/**
 * @file    Ihm.cpp
 * @brief   Déclaration de la classe Ihm
 * @author  ACKERMANN Théo
 * @version 0.1
 */

/**
 * @brief Constructeur de la classe Ihm
 * @fn Ihm::Ihm
 * @param parent
 */
Ihm::Ihm(QWidget *parent) :QMainWindow(parent),ui(new Ui::ihm),ihmNouvelleRuche(new IHMNouvelleRuche),ihmReglageRuche(new IHMReglageRuche()), communication(new Communication()), configuration(new Configuration())
{
    ui->setupUi(this);

    chargerIconesBoutons();

    ui->comboBox_liste_ruches->addItem("Nom de la ruche");
    ui->comboBox_donnees_affiche->addItem("Température");
    ui->comboBox_donnees_affiche->addItem("Humidité");

    ui->comboBox_reglages_graphiques->addItem("1 jour");
    ui->comboBox_reglages_graphiques->addItem("7 jours");

    connect(ui->comboBox_reglages_graphiques, SIGNAL(currentIndexChanged(int)), SLOT(changerAbscisseGraphiques()));
    connect(ui->comboBox_donnees_affiche, SIGNAL(currentIndexChanged(int)), SLOT(changerDonneesVueGlobal()));

    connect(this, SIGNAL(sauvegarderConfigurationTTN(QString,int,QString,QString)), configuration, SLOT(sauvegarderConfigurationTTN(QString,int,QString,QString)));

    // Ajouter une nouvelle ruche
    connect(ihmNouvelleRuche, SIGNAL(nouvelleRuche(QString,QString)), this, SLOT(ajouterNouvelleRuche(QString,QString)));

    //Afficher valeur reçu
    connect(communication, SIGNAL(nouvelleValeurTemperature(double)), this, SLOT(setValeurTemperatureInterieure(double)));
    //connect(communication, SIGNAL(nouvelleValeurTemperatureExterieure(double)), this, SLOT(setValeurTemperatureExterieure(double)));
    connect(communication, SIGNAL(nouvelleValeurHumidite(double)), this, SLOT(setValeurHumidite(double)));
    connect(communication, SIGNAL(nouvelleValeurEnsoleillement(int)), this, SLOT(setValeurEnsoleillement(int)));
    connect(communication, SIGNAL(nouvelleValeurPression(int)), this, SLOT(setValeurPression(int)));
    connect(communication, SIGNAL(nouvelleValeurPoids(int)), this, SLOT(setValeurPoids(int)));

    //demarrerGraphiques();
}

/**
 * @brief Destructeur de la classe Ihm
 * @fn Ihm::~Ihm
 */
Ihm::~Ihm()
{
    delete ihmNouvelleRuche;
    delete ihmReglageRuche;
    delete communication;
    delete configuration;
    delete ui;
}

/**
 * @brief Bouton/icone qui permet d'aller sur l'onglet de la ruche
 * @fn Ihm::on_pushButton_ruches_clicked
 */
void Ihm::on_pushButton_ruches_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_ACCUEIL);
    ui->pushButton_ruches->setIcon(QIcon(":/ruches.png"));

    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques_gris.png"));
    ui->pushButton_alertes->setIcon(QIcon(":/alertes_gris.png"));
    ui->pushButton_reglage_ttn->setIcon(QIcon(":/settings_gris.png"));
    ui->pushButton_mesures->setIcon(QIcon(":/view_all_gris.png"));
}

/**
 * @brief
 * @fn Ihm::on_pushButton_mesures_clicked()
 */
void Ihm::on_pushButton_mesures_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_MESURES);
    ui->pushButton_mesures->setIcon(QIcon(":/view_all.png"));

    ui->pushButton_ruches->setIcon(QIcon(":/ruches_gris.png"));
    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques_gris.png"));
    ui->pushButton_alertes->setIcon(QIcon(":/alertes_gris.png"));
    ui->pushButton_reglage_ttn->setIcon(QIcon(":/settings_gris.png"));
}

/**
 * @brief
 * @fn Ihm::on_pushButton_tableaux_clicked()
 */
void Ihm::on_pushButton_tableaux_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_TABLEAUX);

    ui->pushButton_ruches->setIcon(QIcon(":/ruches_gris.png"));
    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques_gris.png"));
    ui->pushButton_alertes->setIcon(QIcon(":/alertes_gris.png"));
    ui->pushButton_reglage_ttn->setIcon(QIcon(":/settings_gris.png"));
    ui->pushButton_mesures->setIcon(QIcon(":/view_all_gris.png"));
}

/**
 * @brief Bouton/icone qui permet d'aller sur l'onglet des graphiques
 * @fn Ihm::on_pushButton_graphiques_clicked()
 */
void Ihm::on_pushButton_graphiques_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_GRAPHIQUES);
    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques.png"));

    ui->pushButton_ruches->setIcon(QIcon(":/ruches_gris.png"));
    ui->pushButton_alertes->setIcon(QIcon(":/alertes_gris.png"));
    ui->pushButton_reglage_ttn->setIcon(QIcon(":/settings_gris.png"));
    ui->pushButton_mesures->setIcon(QIcon(":/view_all_gris.png"));
}

/**
 * @brief Bouton/icone qui permet d'aller sur l'onglet des alertes
 * @fn Ihm::on_pushButton_alertes_clicked()
 */
void Ihm::on_pushButton_alertes_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_ALERTES);
    ui->pushButton_alertes->setIcon(QIcon(":/alertes.png"));

    ui->pushButton_ruches->setIcon(QIcon(":/ruches_gris.png"));
    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques_gris.png"));
    ui->pushButton_reglage_ttn->setIcon(QIcon(":/settings_gris.png"));
    ui->pushButton_mesures->setIcon(QIcon(":/view_all_gris.png"));
}

/**
 * @brief Bouton/icone qui permet d'aller sur l'onglet des réglages TTN
 * @fn Ihm::on_pushButton_reglage_ttn_clicked()
 */
void Ihm::on_pushButton_reglage_ttn_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_REGLAGES_TTN);
    ui->pushButton_reglage_ttn->setIcon(QIcon(":/settings.png"));

    ui->pushButton_ruches->setIcon(QIcon(":/ruches_gris.png"));
    ui->pushButton_alertes->setIcon(QIcon(":/alertes_gris.png"));
    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques_gris.png"));
    ui->pushButton_mesures->setIcon(QIcon(":/view_all_gris.png"));
}

/**
 * @brief Bouton qui permet de démarrer la connexion avec TTN
 * @fn Ihm::on_pushButton_connexion_ttn_clicked()
 */
void Ihm::on_pushButton_connexion_ttn_clicked()
{
    communication->connexionTTN(ui->lineEdit_host->text(), ui->spinBox_port->value(), ui->lineEdit_username->text(), ui->lineEdit_password->text());
}

/**
 * @brief Bouton qui permet de s'abonner à un topic TTN
 * @fn Ihm::on_pushButton_subscribe_ttn_clicked()
 */
void Ihm::on_pushButton_subscribe_ttn_clicked()
{
    communication->souscrireTopic(ui->lineEdit_topic->text());
}

/**
 * @brief Bouton qui permet d'ouvrir la fenêtre de création du nouvelle ruche
 *
 */
void Ihm::on_pushButton_nouvelle_ruche_clicked()
{
    ihmNouvelleRuche->exec();
}

/**
 * @brief Bouton qui permet d'ouvrir la fenêtre des réglages de la ruche
 *
 */
void Ihm::on_pushButton_reglage_clicked()
{
    ihmReglageRuche->exec();
}

/**
 * @brief Bouton qui permet de supprimer la ruche selectionné
 *
 */
void Ihm::on_pushButton_supprimer_ruche_clicked()
{
    QMessageBox::StandardButton reponse;
    QString nom_ruche = ui->comboBox_liste_ruches->currentText();
    QString question = "Êtes-vous sûr de vouloir supprimer la " + nom_ruche + " ?";
    reponse = QMessageBox::question(this,"",question,QMessageBox::Yes|QMessageBox::No);

    if(reponse == QMessageBox::Yes)
    {
        qDebug() << Q_FUNC_INFO << "reponse : Oui";
        ui->comboBox_liste_ruches->removeItem(ui->comboBox_liste_ruches->currentIndex());
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "reponse : Non";
    }
}

/**
 * @brief Méthode qui initialise les graphiques
 * @fn Ihm::demarrerGraphiques
 */
void Ihm::demarrerGraphiques()
{
    graphiqueTemperature();
    graphiqueHumidite();
    graphiqueLuminosite();
    //graphiquePression();
    //graphiquePoids();
    //graphiqueActivite();
}

/**
 * @brief Méthode qui initialise le graphique de température
 * @fn Ihm::graphiqueTemperature
 */
void Ihm::graphiqueTemperature()
{
    QLineSeries *temperatureInterieure = new QLineSeries();
    temperatureInterieure->setName("Intérieure");
    // Valeurs de test
    temperatureInterieure->append(0, 27);
    temperatureInterieure->append(1, 26);
    temperatureInterieure->append(2, 28);
    temperatureInterieure->append(3, 31);
    temperatureInterieure->append(4, 24);

    QLineSeries *temperatureExterieure = new QLineSeries();
    temperatureExterieure->setName("Extérieure");
    // Valeurs de test
    temperatureExterieure->append(0, 35);
    temperatureExterieure->append(1, 37);
    temperatureExterieure->append(2, 35);
    temperatureExterieure->append(3, 34);
    temperatureExterieure->append(4, 31);

    QChart *chart = new QChart();
    chart->legend()->show();
    chart->addSeries(temperatureInterieure);
    chart->addSeries(temperatureExterieure);

    chart->createDefaultAxes();
    chart->setTitle("Températures");
    ui->chartView_temperature->setChart(chart);
    ui->chartView_temperature->setRenderHint(QPainter::Antialiasing);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("dd.MM");
    axisX->setTitleText("Jours");
    axisX->setMin(QDateTime::currentDateTime().addDays(-3));
    axisX->setMax(QDateTime::currentDateTime().addDays(3));

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("°C");
    axisY->setMin(-10);
    axisY->setMax(45);

    chart->setAxisY(axisY);
    chart->setAxisX(axisX);
}

/**
 * @brief Méthode qui initialise le graphique d'humidité
 * @fn Ihm::graphiqueHumidite
 */
void Ihm::graphiqueHumidite()
{
    QLineSeries *humidite = new QLineSeries();
    // Valeurs de test
    humidite->append(0, 27);
    humidite->append(1, 26);
    humidite->append(2, 28);
    humidite->append(3, 31);
    humidite->append(4, 24);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(humidite);
    chart->setTitle("Humidité");
    ui->chartView_humidite->setChart(chart);
    ui->chartView_humidite->setRenderHint(QPainter::Antialiasing);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("dd.MM");
    axisX->setTitleText("Jours");
    axisX->setMin(QDateTime::currentDateTime().addDays(-3));
    axisX->setMax(QDateTime::currentDateTime().addDays(3));

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("%");
    axisY->setMin(0);
    axisY->setMax(100);

    chart->setAxisY(axisY);
    chart->setAxisX(axisX);
    //humidite->attachAxis(axisX);
}

void Ihm::graphiqueLuminosite()
{
    QLineSeries *luminosite = new QLineSeries();
    // Valeurs de test
    luminosite->append(0, 321);
    luminosite->append(1, 354);
    luminosite->append(2, 396);
    luminosite->append(3, 348);
    luminosite->append(4, 240);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(luminosite);
    chart->setTitle("Luminosité");
    ui->chartView_luminosite->setChart(chart);
    ui->chartView_luminosite->setRenderHint(QPainter::Antialiasing);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("dd.MM");
    axisX->setTitleText("Jours");
    axisX->setMin(QDateTime::currentDateTime().addDays(-3));
    axisX->setMax(QDateTime::currentDateTime().addDays(3));

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("lux");
    axisY->setMin(0);
    axisY->setMax(500);

    chart->setAxisY(axisY);
    chart->setAxisX(axisX);
    //luminosite->attachAxis(axisX);
}

void Ihm::changerAbscisseGraphiques()
{
    switch(ui->comboBox_reglages_graphiques->currentIndex())
    {
        case 0:
            qDebug() << Q_FUNC_INFO << "reponse : 1j";
            break;
        case 1:
            qDebug() << Q_FUNC_INFO << "reponse : 7j";
            break;
        default:
            qDebug() << Q_FUNC_INFO << ui->comboBox_reglages_graphiques->currentIndex();
     }
}

void Ihm::changerDonneesVueGlobal()
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
 * @brief Méthode redéfinie qui s'exécute pour chaque évènement reçu par la fenêtre principale
 * @fn Ihm::closeEvent
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
 * @brief Méthode qui permet de mettre une valeur dans un graphique
 * @param serie
 * @param x
 * @param y
 */
void Ihm::setValeurGraphique(QLineSeries *serie, int x, int y)
{
    serie->append(x,y);
}

void Ihm::chargerIconesBoutons()
{
    ui->pushButton_ruches->setIcon(QIcon(":/ruches.png"));
    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques_gris.png"));
    ui->pushButton_alertes->setIcon(QIcon(":/alertes_gris.png"));
    ui->pushButton_reglage_ttn->setIcon(QIcon(":/settings_gris.png"));
    ui->pushButton_mesures->setIcon(QIcon(":/view_all_gris.png"));
}

/**
 * @brief Initialise les différents widgets de l'IHM
 * @fn Ihm::initialiserWidgets
 */
void Ihm::initialiserWidgets()
{
    this->setWindowTitle(NOM_APPLICATION);
    ui->label_version->setText(VERSION_APPLICATION);

    chargerIconesBoutons();
    ui->comboBox_liste_ruches->addItem("Nom de la ruche");
    ui->comboBox_reglages_graphiques->addItem("1 jour");
    ui->comboBox_reglages_graphiques->addItem("7 jours");

    //showMaximized();
}

/**
 * @brief Assure la connexion signal/slot
 * @fn Ihm::initialiserEvenements
 */
void Ihm::initialiserEvenements()
{
    connect(ui->comboBox_reglages_graphiques, SIGNAL(currentIndexChanged(int)), SLOT(changerAbscisseGraphiques()));
}

/**
 * @brief Initialise l'entrée dans la barre d'état du système
 * @fn Ihm::initialiserEntreeBarreEtatSysteme
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
    iconeEtatSysteme = new QSystemTrayIcon(this);
    iconeEtatSysteme->setContextMenu(menuEtatSysteme);
    iconeEtatSysteme->setToolTip(NOM_APPLICATION);
    // Crée l'icône pour la barre d'état système
    QIcon iconeRuche(":/ruches.png");
    iconeEtatSysteme->setIcon(iconeRuche);
    setWindowIcon(iconeRuche);

    iconeEtatSysteme->show();
}

void Ihm::setValeurTemperatureInterieure(double temperatureInterieure)
{
    ui->lcdNumber_temperature_interieure->display(temperatureInterieure);
    qDebug() << Q_FUNC_INFO << "Nouvelle température intérieure :" << temperatureInterieure;
}
/*
void Ihm::setValeurTemperatureExterieure(double temperatureExterieure)
{
    ui->lcdNumber_temperature_exterieure->display(temperatureExterieure);
    qDebug() << Q_FUNC_INFO << "Nouvelle température extérieure :" << temperatureExterieure;
}
*/
void Ihm::setValeurHumidite(double humidite)
{
    ui->lcdNumber_humidite->display(humidite);
    qDebug() << Q_FUNC_INFO << "Nouvelle humidité :" << humidite;
}

void Ihm::setValeurEnsoleillement(int ensoleillement)
{
    ui->lcdNumber_ensoleillement->display(ensoleillement);
    qDebug() << Q_FUNC_INFO << "Nouvelle ensoleillement :" << ensoleillement;
}

void Ihm::setValeurPression(int pression)
{
    ui->lcdNumber_pression->display(pression);
    qDebug() << Q_FUNC_INFO << "Nouvelle pression :" << pression;
}

void Ihm::setValeurPoids(int poids)
{
    ui->lcdNumber_poids->display(poids);
    qDebug() << Q_FUNC_INFO << "Nouveau poids :" << poids;
}

void Ihm::on_pushButton_enregistrer_configuration_ttn_clicked()
{
    emit sauvegarderConfigurationTTN(ui->lineEdit_host->text(), ui->spinBox_port->value(), ui->lineEdit_username->text(), ui->lineEdit_password->text());
}

void Ihm::ajouterNouvelleRuche(QString nom, QString ttn)
{
    if(ui->comboBox_liste_ruches->currentText() == "Nom de la ruche")
        ui->comboBox_liste_ruches->clear();
    ui->comboBox_liste_ruches->addItem(nom);
    communication->souscrireTopic(ttn);
}
