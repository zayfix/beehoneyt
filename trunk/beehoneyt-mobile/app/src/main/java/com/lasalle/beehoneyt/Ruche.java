package com.lasalle.beehoneyt;

/**
 * @file Ruche.java
 * @brief Déclaration de la classe Ruche
 * @author Ethan VILLESSECHE
 */

import java.io.Serializable;

/**
 * @class Ruche
 * @brief Déclaration de la classe Ruche
 */
public class Ruche implements Serializable
{
    /**
     * Attributs
     */
    private String nom; //!< Le nom de la ruche
    private String infos; //!< Les informations sur la ruche
    private int poids; //!< Le poids de la ruche

    /**
     * @brief Constructeur de la classe Ruche
     *
     * @fn Ruche::Ruche(String nom, String infos, int poids)
     * @param nom
     * @param infos
     * @param poids
     */
    public Ruche(String nom, String infos, int poids)
    {
        this.nom = nom;
        this.infos = infos;
        this.poids = poids;
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

    public void setInfos(String Infos)
    {
        this.infos = Infos;
    }

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

    public String getInfos()
    {
        return infos;
    }

    public int getPoids()
    {
        return poids;
    }
}
