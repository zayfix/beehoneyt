#ifndef REGLAGERUCHE_H
#define REGLAGERUCHE_H

/**
 * @file    reglageruche.h
 * @brief   Déclaration de la classe IHMReglageRuche
 * @author  ACKERMANN Théo
 * @version 0.2
 */

#include <QDialog>
#include <QDebug>

class Ihm;

namespace Ui {
class reglageRuche;
}

/**
 * @class   IHMReglageRuche
 * @brief   La fenêtre pour changer les réglages de la ruche
 * @author  ACKERMANN Théo
 * @version 0.2
 */

class IHMReglageRuche : public QDialog
{
    Q_OBJECT

public:
    explicit IHMReglageRuche(QWidget *parent = nullptr);
    ~IHMReglageRuche();

    void recupererInfoRuche(QString);

private:
    Ui::reglageRuche *ui;           //!< interface
    Ihm *ihm;
};

#endif // REGLAGERUCHE_H
