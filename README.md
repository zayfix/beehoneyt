# Projet Bee-Honey’t

### Présentation

Il s’agit de réaliser un système autonome permettant de connaître à distance certains paramètres d’une ruche afin d’assurer son suivi et d’évaluer la santé des abeilles. Le projet consiste donc à équiper une ruche d’abeilles en y ajoutant des capteurs pour permettre d’obtenir différentes informations telles que la température intérieure, l’humidité, le poids et le comptage des abeilles.

![](https://i.ibb.co/BgQvnQ2/1.png)

La ruche connectée doit permettre à l’apiculteur d’optimiser le suivi de ses abeilles :

- L’orientation et luminosité permettent d’optimiser son rendement et d’influer sur la période de pollinisation des abeilles au cours de la journée.
- L’humidité et la température signalent, par exemple, s’il faut donner à boire aux abeilles ou si la ruche peut être ouverte.
- La masse témoigne de la santé de la colonie et de l’état de la production.
- La pression atmosphérique et l’humidité préviennent d’un changement météorologique qui provoquerait un changement de comportement et un rassemblement de la colonie dans la ruche.

![](https://i.ibb.co/pWr1Zz8/2.png)

Le système « ruches connectées » doit donc réaliser les missions suivantes :

- L’envoi à intervalles réguliers (15 min) des mesures effectuées suivantes :
    - Température intérieure et extérieure,
    - Humidité relative intérieure et extérieure,
    - Pression atmosphérique,
    - Poids de la ruche,
    - Ensoleillement.
    
    - L’affichage des mesures et des alertes en temps réel
    - L’affichage sous forme de vues graphiques des mesures (récapitulatifs journaliers : moyennes, min, max pour chaque heure sur les 7 derniers jours) et éventuellement l’historique des alertes.
    - L’alerte en cas de variation brutale d’une grandeur mesurée (perte de poids soudaine) ou de dépassement de seuils.
    - L’alerte pourra être signalée sous la forme d’un email​ ou d’un message SMS.
    
![](https://i.ibb.co/MnS0LmC/3.png)

### Répartitions des tâches par étudiant

- Etudiant 1 (EC) :
    - Mesurer les grandeurs température, humidité, pression atmosphérique, et ensoleillement de la ruche (option)
    - Mesurer le poids de la ruche
    - Transmettre les données au PC

- Etudiant 2 (IR) : Application PC
    - Consulter les données d’une ruche (vue “temps réel” + description + affichage des alertes)
    - Recevoir les données actuelles des ruches (MQTT/Json)
    - Récupérer les données enregistrées (HTTP/Json)
    - Éditer les ruches
    - Paramétrer une nouvelle ruche et les alertes
    - Option : Déclencher les alertes (par email)

- Etudiant 3 (IR) : Application mobile
    - Consulter les données d’une ruche (vue “temps réel” + description + affichage des alertes)
    - Recevoir les données actuelles des ruches (MQTT/Json)
    - Récupérer les données enregistrées (HTTP/Json)
    - Éditer les ruches
    - Paramétrer une nouvelle ruche et les alertes
    - Option : Déclencher les alertes (par sms)
	
### Informations supplémentaires
- Date de début : 06/02/2020 
- Équipe de développement : 
	- ACKERMANN Théo, e-mail: theoackrm@gmail.com
	- VILLESSECHE Ethan, e-mail: villesseche.ethan@gmail.com

    
### Contraintes d’environnement (IR)
    
| Ressource        | Version      |
| ------|-----|
| OS 	    | GNU/Linux Ubuntu 16.04 LTS |
| SGBDR     | À définir : MySQL, SQLite, … |
| EDI 	    | Qt Creator et Qt Designer |
| API 	    | Qt 5 |
   
### Revues (IR)
- [Revue n°2](http://tvaira.free.fr/projets/projet-revue2.html) [[PDF]](http://tvaira.free.fr/projets/projet-revue2.pdf)
- [Revue n°3](http://tvaira.free.fr/projets/projet-revue3.html) [[PDF]](http://tvaira.free.fr/projets/projet-revue3.pdf)

[Cahier des charges](http://tvaira.free.fr/projets/cdc-2020/cdc-bee-honey-t-2020.pdf)
