package com.lasalle.beehoneyt;

/**
 * @file Ruche.java
 * @brief Déclaration de la classe Ruche
 * @author Ethan VILLESSECHE
 */

import android.util.Log;
import java.io.Serializable;

/**
 * @class Ruche
 * @brief Déclaration de la classe Ruche
 */
public class Ruche implements Serializable
{
    /**
     * Constantes
     */
    private static final String TAG = "Ruche";
    /**
     * Attributs
     */
    private String nom; //!< Le nom de la ruche.
    private String deviceID; //!< l'id de la ruche
    private String infos; //!< Les informations sur la ruche
    private int poids; //!< Le poids de la ruche
    boolean abonne; //!< Indique si la ruche est abonné à un topic

    /**
     * @brief Constructeur de la classe Ruche
     *
     * @fn Ruche::Ruche(String nom, String infos, int poids)
     * @param nom
     * @param deviceID
     */
    public Ruche(String nom, String deviceID)
    {
        Log.d(TAG, "Ruche : " + nom + " - DeviceID : " + deviceID + " " + this);
        this.nom = nom;
        this.deviceID = deviceID;
        this.abonne = false;
    }

    /**
     * @brief Mutateur set du nom de la ruche
     *
     * @fn Ruche::setNom(String nom)
     * @param nom le nouveau nom de la ruche
     */
    public void setNom(String nom)
    {
        this.nom = nom;
    }

    /**
     * @brief Mutateur set du device id de la ruche
     *
     * @param deviceID le nouveau device id de la ruche
     */
    public void setDeviceID(String deviceID)
    {
        this.deviceID = deviceID;
    }

    /**
     * @brief Mutateur set des informations de la ruche
     *
     * @param Infos les nouvelles informations de la ruche
     */
    public void setInfos(String Infos)
    {
        this.infos = Infos;
    }

    /**
     * @brief Mutateur set du poids de la ruche
     *
     * @param Poids le nouveau poids de la ruche
     */
    public void setPoids(int Poids)
    {
        this.poids = Poids;
    }


    /**
     * @brief Accesseur get du nom de la ruche
     *
     * @fn Ruche::getNom()
     * @return String le nom de la ruche
     */
    public String getNom()
    {
        return nom;
    }

    /**
     * @brief Accesseur get du device id de la ruche
     *
     * @fn Ruche::getDeviceID()
     * @return String le device id de la ruche
     */
    public String getDeviceID()
    {
        return deviceID;
    }

    /**
     * @brief Accesseur get des information de la ruche
     *
     * @fn Ruche::getInfos()
     * @return String les information  de la ruche
     */
    public String getInfos()
    {
        return infos;
    }

    /**
     * @brief Accesseur get du poids de la ruche
     *
     * @fn Ruche::getPoids()
     * @return String le poids de la ruche
     */
    public int getPoids()
    {
        return poids;
    }

    /**
     * @brief Accesseur get de abonne
     *a
     * @return boolean abonne
     */
    public boolean estAbonne()
    {
        return abonne;
    }

    /**
     * @brief Permet de s'abonner au topic TTN du deviceID de la ruche
     *
     */
    public void souscrireTopic()
    {
        if(!abonne)
        {
            CommunicationMQTT.souscrireTopic(deviceID);
            abonne = true;
            Log.d(TAG, "Souscrire au topic : " + deviceID);
        }
    }
}
