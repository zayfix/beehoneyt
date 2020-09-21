# Présentation

Système autonome permettant de connaître à distance certains paramètres d'une ruche afin d'assurer son suivi et d'évaluer la santé des abeilles.

Version : PC (*desktop*)

## Fichier de configuration

Le fichier `configuration.ini` contient :

* les paramètres de connexion au serveur TTN
* le nombre de ruches
* les paramètres de chaque ruche

```ini
[General]
NbRuches=2

[Ruche1]
Adresse=
Latitude=
Longitude=
MiseEnService=
Nom=Ruche 1
TopicTTN=mes_ruches/devices/ruche_1/up

[Ruche2]
Adresse=
Latitude=
Longitude=
MiseEnService=25/03/2020
Nom=Ruche 2
TopicTTN=mes_ruches/devices/ruche_2/up

[TTN]
Hostname=eu.thethings.network
Password=
Port=1883
Username=mes_ruches
```

## Recette de l'application PC (desktop)

* Consulter les données d'une ruche
* Recevoir les données actuelles des ruches (MQTT/Json)
* Éditer les ruches

### Informations supplémentaires
- Équipe de développement : 
	- Théo Ackermann <theoackrm@gmail.com>
    - Date: 2020
    - Version 0.1
