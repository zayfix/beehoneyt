#ifndef RUCHE_H
#define RUCHE_H

#include <QString>

/**
  * @todo Une classe Ruche ?
  */

/**
 * @brief Structure qui définit une ruche
 * @struct Ruche
 */
struct Ruche
{
    QString nom;   //!< le nom de la ruche
    QString topicTTN;   //!< le topic TTN associé à la ruche
    QString miseEnService; //!< la date de mise en service
    QString adresse;   //!< l'adresse
    QString latitude;   //!< la latitude
    QString longitude;   //!< la longitude
};

#endif // RUCHE_H
