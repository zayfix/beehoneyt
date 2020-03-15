package com.lasalle.beehoneyt;

public class Ruche {

    private String Nom;

    private String Infos;

    private int Poids;


    public Ruche(String Nom, String Infos, int Poids)
    {
        this.Nom = Nom;
        this.Infos = Infos;
        this.Poids = Poids;
    }

    public void setNom(String Nom)
    {
        this.Nom = Nom;
    }

    public void setInfos(String Infos)
    {
        this.Infos = Infos;
    }

    public void setPoids(int Poids)
    {
        this.Poids = Poids;
    }

    public String getNom()
    {
        return Nom;
    }

    public String getInfos()
    {
        return Infos;
    }

    public int getPoids()
    {
        return Poids;
    }


}
