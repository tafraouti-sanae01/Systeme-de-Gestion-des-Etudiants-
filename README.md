# Système de Gestion des Étudiants - ENSA Tétouan

## Description Générale
Un système de gestion académique complet développé en C pour l'École Nationale des Sciences Appliquées de Tétouan. Le système permet une gestion efficace des données des étudiants en première année du cycle d'ingénieur en Génie Informatique, avec un focus particulier sur le suivi des performances académiques.

## Architecture Technique

### 1. Structures de Données
```c
typedef struct {
    float AO, BD, C, ThG, RI;  // Notes des 5 modules
} Notes;

typedef struct Etudiant {
    int apogee;                // Numéro d'apogée unique
    char nom[50];             // Nom de l'étudiant
    char prenom[50];          // Prénom de l'étudiant
    int age;                  // Âge de l'étudiant
    Notes notes;              // Notes des modules
    struct Etudiant* suivant; // Pointeur vers l'étudiant suivant
} Etudiant;

typedef struct {
    Etudiant* tete;           // Pointeur vers le premier étudiant
    Etudiant* queue;          // Pointeur vers le dernier étudiant
    int nef;                  // Nombre d'étudiants dans la liste
} Liste;
```

### 2. Fonctionnalités Détaillées

#### 2.1 Gestion des Étudiants
- **Ajout d'Étudiant**
  - Validation du numéro d'apogée unique
  - Saisie des informations personnelles
  - Saisie des notes pour chaque module
  - Choix de la position d'insertion (début, fin, position spécifique)

- **Modification d'Étudiant**
  - Mise à jour des informations personnelles
  - Modification des notes
  - Validation des modifications

- **Suppression d'Étudiant**
  - Suppression par numéro d'apogée
  - Mise à jour des liens de la liste

#### 2.2 Gestion des Notes
- **Modules Gérés**
  - Architecture des Ordinateurs (AO)
  - Bases de Données Relationnelles (BD)
  - Structure de Données en C (C)
  - Théorie des Graphes (ThG)
  - Réseaux Informatiques (RI)

- **Calculs Automatiques**
  - Moyenne individuelle par étudiant
  - Moyenne générale de la classe
  - Validation des modules (note ≥ 12/20)
  - Mention selon la moyenne (Assez Bien, Bien, etc.)

#### 2.3 Analyses et Statistiques
- **Classements**
  - Meilleur étudiant en moyenne générale
  - Pire étudiant en moyenne générale
  - Trois meilleurs étudiants par module
  - Classement complet de la classe


#### 2.4 Génération de Rapports
- **Rapports Individuels**
  - Informations personnelles
  - Notes détaillées par module
  - Moyenne générale
  - Mention obtenue
  - Statut de validation

- **Rapports de Classe**
  - Moyenne générale de la classe
  - Meilleures et pires moyennes
  - Statistiques globales
  - Classements par module

### 3. Persistance des Données

#### 3.1 Format des Fichiers
- **etudiants.txt**
  - Format : `apogee nom prenom age note_AO note_BD note_C note_ThG note_RI`
  - Stockage des données brutes

- **rapport.txt**
  - Format structuré avec en-têtes
  - Informations détaillées par étudiant
  - Statistiques de classe

#### 3.2 Fonctions de Sauvegarde
- Sauvegarde automatique des modifications
- Chargement des données au démarrage
- Génération de rapports formatés

### 4. Interface Utilisateur

#### 4.1 Menu Principal
- Gestion des étudiants
- Gestion des notes
- Génération de rapports
- Statistiques et analyses
- Sauvegarde et chargement

#### 4.2 Validation des Entrées
- Vérification des formats
- Messages d'erreur explicites
- Confirmation des actions importantes

## Exemple de Données

### Structure des Notes
```
Module                  | Note/Bareme | Résultat
-----------------------|-------------|----------
Architecture (AO)      | 18.00/20    | Valide
Bases de Données (BD)  | 12.00/20    | Valide
Structure C (C)        | 15.00/20    | Valide
Théorie Graphes (ThG)  | 12.00/20    | Valide
Réseaux (RI)           | 11.00/20    | Non valide
```

### Exemple de Rapport
```
Moyenne générale : 13.60/20
Statut : Admis (Assez Bien)
Moyenne classe : 13.41/20
Meilleure moyenne : 13.80/20
Pire moyenne : 13.05/20
```

## Installation et Configuration

### Prérequis
- Compilateur C (gcc recommandé)
- Système d'exploitation compatible
- 100 Mo d'espace disque

### Compilation
```bash
gcc main.c -o gestion_etudiants
```

### Exécution
```bash
./gestion_etudiants
```

## Maintenance et Support
- Sauvegarde régulière des données
- Vérification de l'intégrité des fichiers
- Mise à jour des statistiques

## Auteur
Développé par Sanae Tafraouti
