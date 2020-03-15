#ifndef NOUVELLERUCHE_H
#define NOUVELLERUCHE_H

/**
 * @file    nouvelleruche.h
 * @brief   Déclaration de la classe IHMNouvelleRuche
 * @author  ACKERMANN Théo
 * @version 0.1
 */

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class nouvelleRuche;
}

class IHMNouvelleRuche : public QDialog
{
    Q_OBJECT

public:
    explicit IHMNouvelleRuche(QWidget *parent = nullptr);
    ~IHMNouvelleRuche();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::nouvelleRuche *ui;

signals:
    void nouvelleRuche(QString, QString);
};

#endif // NOUVELLERUCHE_H
