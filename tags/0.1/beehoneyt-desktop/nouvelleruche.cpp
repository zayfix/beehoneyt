#include "nouvelleruche.h"
#include "ui_nouvelleruche.h"

/**
 * @file    nouvelleruche.cpp
 * @brief   Déclaration de la classe IHMNouvelleRuche
 * @author  ACKERMANN Théo
 * @version 0.1
 */

/**
 * @brief Constructeur de la classe IHMNouvelleRuche
 * @fn IHMNouvelleRuche::IHMNouvelleRuche
 * @param parent
 */
IHMNouvelleRuche::IHMNouvelleRuche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nouvelleRuche)
{
    ui->setupUi(this);
    ui->dateEdit_mise_en_service->setDate(QDate::currentDate());
    QPushButton *ok = ui->buttonBox->button(QDialogButtonBox::Ok);
    ok->setEnabled(false);
    connect(ui->lineEdit_ttn, SIGNAL(textChanged(QString)), this, SLOT(verifier()));
}

/**
 * @brief Destructeur de la classe IHMNouvelleRuche
 * @fn IHMNouvelleRuche::~IHMNouvelleRuche
 */
IHMNouvelleRuche::~IHMNouvelleRuche()
{
    delete ui;
}

/**
 * @brief Méthode pour empêcher la fermeture de la fenetre si la ligne de TTN est vide.
 * @fn IHMNouvelleRuche::closeEvent
 * @param event
 */
void IHMNouvelleRuche::closeEvent(QCloseEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    if(ui->lineEdit_ttn->text().isEmpty())
    {
        event->ignore();
        ui->label_affichage_erreur->setText("Veuillez renseigner un topic TTN.");
    }
}

/**
 * @brief Méthode qui est effectuée si le bouton de confirmation de la fenêtre est pressé.
 * @fn IHMNouvelleRuche::on_buttonBox_accepted()
 */
void IHMNouvelleRuche::on_buttonBox_accepted()
{
    Ruche ruche;
    ruche.nom = ui->lineEdit_nom->text();
    ruche.topicTTN = ui->lineEdit_ttn->text();
    ruche.adresse = ui->lineEdit_adresse->text();
    ruche.miseEnService = ui->dateEdit_mise_en_service->date().toString("dd/MM/yyyy");
    ruche.latitude = ui->lineEdit_latitude->text();
    ruche.longitude = ui->lineEdit_longitude->text();
    emit nouvelleRuche(ruche);
}

/**
 * @brief Méthode qui est effectuée si le bouton d'annulation de la fenêtre est pressé.
 * @fn IHMNouvelleRuche::on_buttonBox_rejected()
 */
void IHMNouvelleRuche::on_buttonBox_rejected()
{
    nettoyerIHM();
}

/**
 * @brief Méthode pour activer/désactiver le bouton de confirmation selon si une valeur de topic TTN a été entrée.
 * @fn IHMNouvelleRuche::verifier()
 */
void IHMNouvelleRuche::verifier()
{
    QPushButton *ok = ui->buttonBox->button(QDialogButtonBox::Ok);
    if(!ui->lineEdit_ttn->text().isEmpty())
    {
        ok->setEnabled(true);
    }
    else
    {
        ok->setEnabled(false);
    }
}

/**
 * @brief Méthode pour supprimer les données entré dans l'IHM
 * @fn IHMNouvelleRuche:::nettoyerIHM()
 */
void IHMNouvelleRuche::nettoyerIHM()
{
    ui->lineEdit_nom->clear();
    ui->lineEdit_ttn->clear();
    ui->lineEdit_adresse->clear();
    ui->lineEdit_longitude->clear();
    ui->lineEdit_latitude->clear();

    ui->label_affichage_erreur->clear();
}
