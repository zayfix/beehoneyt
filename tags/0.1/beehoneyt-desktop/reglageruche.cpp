#include "reglageruche.h"
#include "ui_reglageruche.h"
#include <QDebug>

/**
 * @brief Constructeur de la classe IHMReglageRuche
 * @fn IHMReglageRuche::IHMReglageRuche
 * @param parent
 */
IHMReglageRuche::IHMReglageRuche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reglageRuche)
{
    ui->setupUi(this);
}

/**
 * @brief Destructeur de la classe IHMReglageRuche
 * @fn IHMReglageRuche::~IHMReglageRuche
 */
IHMReglageRuche::~IHMReglageRuche()
{
    delete ui;
}
