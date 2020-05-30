#include "reglageruche.h"
#include "ui_reglageruche.h"
#include "ihm.h"

/**
 * @file    reglageruche.cpp
 * @brief   Déclaration de la classe IHMReglageRuche
 * @author  ACKERMANN Théo
 * @version 0.2
 */

/**
 * @brief Constructeur de la classe IHMReglageRuche
 * 
 * @param parent
 */
IHMReglageRuche::IHMReglageRuche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reglageRuche)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Destructeur de la classe IHMReglageRuche
 */
IHMReglageRuche::~IHMReglageRuche()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}

void IHMReglageRuche::recupererInfoRuche(QString nomRuche)
{
    qDebug() << Q_FUNC_INFO;
    ui->lineEdit_nomRuche->setText(nomRuche);

}
