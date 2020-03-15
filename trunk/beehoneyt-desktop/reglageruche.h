#ifndef REGLAGERUCHE_H
#define REGLAGERUCHE_H

/**
 * @file    reglageruche.h
 * @brief   Déclaration de la classe IHMReglageRuche
 * @author  ACKERMANN Théo
 * @version 0.1
 */

#include <QDialog>

namespace Ui {
class reglageRuche;
}

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
