#include "reglageruche.h"
#include "ui_reglageruche.h"
#include <QDebug>

IHMReglageRuche::IHMReglageRuche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reglageRuche)
{
    ui->setupUi(this);
}

IHMReglageRuche::~IHMReglageRuche()
{
    delete ui;
}
