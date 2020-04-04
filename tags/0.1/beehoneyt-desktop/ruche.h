#ifndef RUCHE_H
#define RUCHE_H

/**
 * @file    ruche.h
 * @brief   Déclaration de la structure Ruche
 * @author  ACKERMANN Théo
 * @version 0.2
 */

#include <QString>

/**
 * @brief Structure qui définit une ruche
 * @struct Ruche
 */
struct Ruche
{
    QString nom;            //!< le nom de la ruche
    QString topicTTN;       //!< le topic TTN associé à la ruche
    QString miseEnService;  //!< la date de mise en service
    QString adresse;        //!< l'adresse
    QString latitude;       //!< la latitude
    QString longitude;      //!< la longitude
    bool operator==(const Ruche &r) const
    {
        // le nom aussi ?
        if(this->topicTTN != r.topicTTN)
                return false;
        return true;
    }
    bool operator!=(const Ruche &r) const
    {
        return !(*this == r);
    }
};

#endif // RUCHE_H
