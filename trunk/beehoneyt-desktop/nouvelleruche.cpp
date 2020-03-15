#include "nouvelleruche.h"
#include "ui_nouvelleruche.h"

IHMNouvelleRuche::IHMNouvelleRuche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nouvelleRuche)
{
    ui->setupUi(this);
    ui->dateEdit_mise_en_service->setDate(QDate::currentDate());
}

IHMNouvelleRuche::~IHMNouvelleRuche()
{
    delete ui;
}

void IHMNouvelleRuche::on_buttonBox_accepted()
{
    if(ui->lineEdit_ttn->text().isEmpty())
        QMessageBox::warning(this,"","Le TTN ne peut être nul !");
        /**
         * @todo Faire en sorte que ça ne ferme pas la fenêtre de création de ruche
         */
    else
        emit nouvelleRuche(ui->lineEdit_nom->text(),ui->lineEdit_ttn->text());
}
