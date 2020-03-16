#include "nouvelleruche.h"
#include "ui_nouvelleruche.h"
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

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

IHMNouvelleRuche::~IHMNouvelleRuche()
{
    delete ui;
}

void IHMNouvelleRuche::closeEvent(QCloseEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    if(ui->lineEdit_ttn->text().isEmpty())
        event->ignore();
}

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
