#ifndef NOUVELLERUCHE_H
#define NOUVELLERUCHE_H

/**
 * @file    nouvelleruche.h
 * @brief   Déclaration de la classe IHMNouvelleRuche
 * @author  ACKERMANN Théo
 * @version 0.2
 */

#include <QDialog>
#include <QCloseEvent>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include "ruche.h"

namespace Ui {
class nouvelleRuche;
}


/**
 * @class   IHMNouvelleRuche
 * @brief   La fenêtre pour créer une nouvelle ruche
 * @author  ACKERMANN Théo
 * @version 0.2
 */

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
    void on_buttonBox_rejected();
    void verifier();

private:
    Ui::nouvelleRuche *ui;              //!< interface
    void nettoyerIHM();

signals:
    void nouvelleRuche(Ruche);
};

#endif // NOUVELLERUCHE_H
