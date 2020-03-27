#ifndef REGLAGERUCHE_H
#define REGLAGERUCHE_H

/**
 * @file    reglageruche.h
 * @brief   Déclaration de la classe IHMReglageRuche
 * @author  ACKERMANN Théo
 * @version 2.0
 */

#include <QDialog>
#include <QDebug>

namespace Ui {
class reglageRuche;
}

/**
 * @class   IHMReglageRuche
 * @brief   La fenêtre pour changer les réglages de la ruche
 * @author  ACKERMANN Théo
 * @version 2.0
 */

class IHMReglageRuche : public QDialog
{
    Q_OBJECT

public:
    explicit IHMReglageRuche(QWidget *parent = nullptr);
    ~IHMReglageRuche();

private:
    Ui::reglageRuche *ui;
};

#endif // REGLAGERUCHE_H
