#ifndef NOUVELLERUCHE_H
#define NOUVELLERUCHE_H

/**
 * @file    nouvelleruche.h
 * @brief   Déclaration de la classe IHMNouvelleRuche
 * @author  ACKERMANN Théo
 * @version 0.1
 */

#include <QDialog>
#include <QCloseEvent>
#include "ruche.h"

namespace Ui {
class nouvelleRuche;
}

class IHMNouvelleRuche : public QDialog
{
    Q_OBJECT

public:
    explicit IHMNouvelleRuche(QWidget *parent = nullptr);
    ~IHMNouvelleRuche();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_buttonBox_accepted();
    void verifier();

private:
    Ui::nouvelleRuche *ui;

signals:
    void nouvelleRuche(Ruche);
};

#endif // NOUVELLERUCHE_H
