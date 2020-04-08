\mainpage Le projet 

\tableofcontents

Système autonome permettant de connaître à distance certains paramètres d'une ruche afin d'assurer son suivi et d'évaluer la santé des abeilles.

\section section_tdm Table des matières
- \ref page_README
- \ref page_changelog
- \ref page_about
- \ref page_licence

\section section_infos Informations

\author Théo Ackermann <theoackrm@gmail.com>
\date 2020
\version 0.1
\see https://svn.riouxsvn.com/


\page page_README README

[TOC]

# Projet {#projet}

## Présentation {#presentation}

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

## Recette de l'application PC (desktop) {#recette}

* Consulter les données d'une ruche
* Recevoir les données actuelles des ruches (MQTT/Json)
* Éditer les ruches

## Informations {#informations}

\author Théo Ackermann <theoackrm@gmail.com>
\date 2020
\version 0.2
\see https://svn.riouxsvn.com/bee-honey-t


\page page_about A propos

\author Théo Ackermann <theoackrm@gmail.com>
\date 2020
\version 0.2
\see https://svn.riouxsvn.com/bee-honey-t


\page page_licence Licence GPL

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
