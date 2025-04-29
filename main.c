#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float AO, BD, C, ThG, RI;
} Notes;
// ----> O(1)

typedef struct Etudiant {
    int apogee;
    char nom[50];
    char prenom[50];
    int age;
    Notes notes;
    struct Etudiant* suivant;
} Etudiant;
// ----> O(1)

typedef struct {
    Etudiant* tete;
    Etudiant* queue;
    int nef;
} Liste;
// ----> O(1)

float CalculerMoyenne(Notes notes) {
    return (notes.AO + notes.BD + notes.C + notes.ThG + notes.RI) / 5.0;
}
// ----> O(1)

float MoyenneClasse(Liste* liste,FILE* fichier) {
    if (liste->tete == NULL) {
        printf("\nLa liste des etudiants est vide.\n");
        return 0;
    }

    float sommeMoyennes = 0.0;
    int nombreEtudiants = 0;

    Etudiant* etudiant = liste->tete;
    while (etudiant != NULL) {
        sommeMoyennes += CalculerMoyenne(etudiant->notes);
        nombreEtudiants++;
        etudiant = etudiant->suivant;
    }

    if (nombreEtudiants == 0) {
        return 0.0;
    }

    return sommeMoyennes / nombreEtudiants;
}
// ----> O(n)

Etudiant* CreerEtudiant(int apogee, char nom[], char prenom[], int age, Notes notes) {
    Etudiant* etudiant = (Etudiant*)malloc(sizeof(Etudiant));
    etudiant->apogee = apogee;
    strcpy(etudiant->nom, nom);
    strcpy(etudiant->prenom, prenom);
    etudiant->age = age;
    etudiant->notes = notes;
    etudiant->suivant = NULL;
    return etudiant;
}
// ----> O(1)

Liste* CreerListe() {
    Liste* liste = (Liste*)malloc(sizeof(Liste));
    liste->tete = NULL;
    liste->queue = NULL;
    liste->nef = 0;
    return liste;
}
// ----> O(1)

void AjouterEtudiant(Liste* liste) {
    int nombreEtudiants;
    printf("Combien d'etudiants voulez-vous ajouter ? ");
    scanf("%d", &nombreEtudiants);
    for (int i = 0; i < nombreEtudiants; i++) {
        int apogee, age, choix, position = 0;
        char nom[50], prenom[50];
        Notes notes;
        printf("\nEntrez les informations de l'etudiant %d:", i + 1);
        int apogeeExistant;
        do {
            apogeeExistant = 0;
            printf("\nApogee : ");
            scanf("%d", &apogee);
            Etudiant* courant = liste->tete;
            while (courant != NULL) {
                if (courant->apogee == apogee) {
                    apogeeExistant = 1;
                    printf("Ce numero d'apogee existe deja. Veuillez en saisir un autre.\n");
                    break;
                }
                courant = courant->suivant;
            }
        } while (apogeeExistant);
        printf("Nom : ");
        scanf("%s", nom);
        printf("Prenom : ");
        scanf("%s", prenom);
        printf("Age : ");
        scanf("%d", &age);
        printf("Entrez les 5 notes :");
        printf("\nArchitecture des Ordinateurs (AO):");
        scanf("%f",&notes.AO);
        printf("Bases de donnees Relationnelle (BD):");
        scanf("%f",&notes.BD);
        printf("Structure de Donnees en C (C):");
        scanf("%f",&notes.C);
        printf("Theorie des Graphes (ThG):");
        scanf("%f",&notes.ThG);
        printf("Reseaux informatiques (RI):");
        scanf("%f",&notes.RI);
        if (nombreEtudiants == 1) {
            printf("Ou voulez-vous ajouter l'etudiant ?");
            printf("\n1. Debut\n2. Fin\n3. Apres une position specifique");
            do {
                printf("\nVotre choix (1, 2 ou 3) : ");
                if (scanf("%d", &choix) != 1) {
                    printf("\nEntree invalide. Veuillez saisir un nombre.");
                    while (getchar() != '\n');
                    choix = -1;
                }
                else if (choix < 1 || choix > 3) {
                    printf("\nChoix invalide. Veuillez entrer un nombre entre 1 et 3.");
                }
            } while (choix < 1 || choix > 3);
            if (choix == 3) {
                printf("Entrez la position apres laquelle inserer l'etudiant : ");
                scanf("%d", &position);
            }
        }
        else {
            choix = 2;
        }
        Etudiant* etudiant=CreerEtudiant( apogee,  nom,  prenom,  age, notes);
        if (choix == 1) {
            etudiant->suivant = liste->tete;
            liste->tete = etudiant;
            if (liste->queue == NULL) {
                liste->queue = etudiant;
            }
            printf("\nEtudiant %s %s ajoute avec succes\n", etudiant->nom, etudiant->prenom);
        }
        else if (choix == 2 || nombreEtudiants != 1) {
            if (liste->tete == NULL) {
                liste->tete = liste->queue = etudiant;
            }
            else {
                liste->queue->suivant = etudiant;
                liste->queue = etudiant;
            }
        }
        else if (choix == 3) {
            Etudiant* courant = liste->tete;
            for (int i = 1; i < position && courant != NULL; i++) {
                courant = courant->suivant;
            }
            if (courant != NULL) {
                etudiant->suivant = courant->suivant;
                courant->suivant = etudiant;
            }
            else {
                printf("\nPosition invalide. L'etudiant sera ajoute a la fin.");
                if (liste->queue != NULL) {
                    liste->queue->suivant = etudiant;
                    liste->queue = etudiant;
                }
                else {
                    liste->tete = liste->queue = etudiant;
                }
            }
            printf("\nEtudiant %s %s ajoute avec succes\n", etudiant->nom, etudiant->prenom);
        }
        liste->nef++;
    }
    printf("\n%d etudiant(s) ajoute(s) avec succes\n", nombreEtudiants);
}
// ----> O(n)

void AfficherEtudiants(Liste* liste) {
    if (liste == NULL || liste->tete == NULL) {
        printf("\nLa liste est vide ou invalide.");
        return;
    }
    int choix, critere;
    char valeur[50];
    char valeur1[50],valeur2[50];
    Etudiant* etudiant = liste->tete;
    printf("\nQue voulez-vous afficher ?");
    printf("\n1. Un seul etudiant\n2. Tous les etudiants");
    do {
        printf("\nVotre choix (1 ou 2) : ");
        if (scanf("%d", &choix) != 1) {
            printf("\nEntree invalide. Veuillez saisir un nombre.");
            while (getchar() != '\n');
                choix = -1;
        }
        else if (choix < 1 || choix > 2) {
            printf("\nChoix invalide. Veuillez entrer 1 ou 2.");
        }
    } while (choix < 1 || choix > 2);
    if (choix == 1) {
        printf("Critere pour afficher un etudiant :");
        printf("\n1. Apogee\n2. Nom\n3. Age");
        do {
            printf("\nVotre choix (1, 2 ou 3) : ");
            if (scanf("%d", &critere) != 1) {
                printf("\nEntree invalide. Veuillez saisir un nombre.");
                while (getchar() != '\n');
                critere = -1;
            }
            else if (critere < 1 || critere > 3) {
                printf("\nChoix invalide. Veuillez entrer un nombre entre 1 et 3.");
            }
        } while (critere < 1 || critere > 3);
        printf("Entrez la valeur : ");
        scanf("%s", valeur);
        int trouve = 0;
        Etudiant* candidats[100];
        while (etudiant != NULL) {
            if ((critere == 1 && etudiant->apogee == atoi(valeur)) ||
                (critere == 2 && strcmp(etudiant->nom, valeur) == 0)||
                (critere == 3 && etudiant->age == atoi(valeur))) {
                    candidats[trouve++] = etudiant;
                }
                etudiant = etudiant->suivant;
        }
        if (trouve == 0) {
            printf("\nAucun etudiant trouve.");
            return;
        }
        else if (trouve == 1) {
            etudiant = candidats[0];
            printf("\n\n----Informations pour l'etudiant  ----\n ");
            printf("\nApogee : %d  , Nom : %s  , Prenom : %s  , Age : %d  .\nNotes : AO =%.2f , BD = %.2f , C =%.2f , ThG =%.2f , RI =%.2f",
                       etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age,
                       etudiant->notes.AO, etudiant->notes.BD, etudiant->notes.C,
                       etudiant->notes.ThG, etudiant->notes.RI);
            return;
        }
        else {
            printf("\nPlusieurs etudiants trouves avec ce critere :");
            for (int i = 0; i < trouve; i++) {
                etudiant = candidats[i];
                printf("\nEtudiant %d - Apogee: %d, Nom et prenom: %s %s, Age: %d",i + 1, etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age);
            }
            printf("\nVeuillez selectionner un sous-critere pour identifier un etudiant unique :");
            printf("\n1. Par Apogee\n2. Par Nom et Prenom");
            int sousCritere;
            do {
                printf("\nVotre choix (1 ou 2) : ");
                if (scanf("%d", &sousCritere) != 1) {
                printf("\nEntree invalide. Veuillez saisir un nombre.");
                while (getchar() != '\n');
                sousCritere = -1;
                }
                else if (sousCritere < 1 || sousCritere > 2) {
                    printf("\nChoix invalide. Veuillez entrer 1 ou 2.");
                }
            } while (sousCritere < 1 || sousCritere > 2);
            if(sousCritere == 1){
                    printf("Entrez l'apogee : ");
                    scanf("%s", valeur1);
            }
            else if(sousCritere == 2){
                    printf("Entrez le nom : ");
                    scanf("%s", valeur1);
                    printf("Entrez le prenom : ");
                    scanf("%s", valeur2);
            }
            for (int i = 0; i < trouve; i++) {
                    if ((sousCritere == 1 && candidats[i]->apogee == atoi(valeur1)) ||
                       (sousCritere == 2 && strcmp(candidats[i]->nom, valeur1) == 0 && strcmp(candidats[i]->prenom, valeur2) == 0)) {
                    etudiant = candidats[i];
                    printf("\n\n----Informations pour l'etudiant  ----\n ");
                    printf("\nApogee : %d , Nom : %s , Prenom : %s , Age : %d .\nNotes : AO =%.2f , BD = %.2f , C =%.2f , ThG =%.2f , RI =%.2f",
                       etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age,
                       etudiant->notes.AO, etudiant->notes.BD, etudiant->notes.C,
                       etudiant->notes.ThG, etudiant->notes.RI);
                    return;
                    }
            }
            printf("\nAucun etudiant trouve avec ce sous-critere.");
        }
    }
    else if (choix == 2) {
        printf("\nListe des etudiants :\n");
        printf("=======================================================================================================================\n");
        printf("Apogee\t| Nom    \t| Prenom  \t| Age \t| AO   \t| BD   \t| C    \t| ThG  \t| RI   \n");
        printf("=======================================================================================================================\n");
        while (etudiant != NULL) {
        printf("%d    \t| %s \t| %s  \t| %d  \t| %.2f\t| %.2f\t| %.2f\t| %.2f\t| %.2f  \n",etudiant->apogee, etudiant->nom, etudiant->prenom,
                etudiant->age,etudiant->notes.AO, etudiant->notes.BD, etudiant->notes.C,etudiant->notes.ThG, etudiant->notes.RI);
            etudiant = etudiant->suivant;
        }
        printf("=======================================================================================================================\n");
    }
}
// ----> O(n)

void SupprimerEtudiant(Liste* liste) {
    if (liste == NULL || liste->tete == NULL) {
        printf("\nLa liste est vide ou invalide.");
        return;
    }
    int critere,choix;
    char valeur[50];
    printf("\nQue souhaitez-vous faire ?");
    printf("\n1. Supprimer les notes de l'etudiant\n2. Supprimer l'etudiant");
    do {
        printf("\nVotre choix (1 ou 2) : ");
        if (scanf("%d", &choix) != 1) {
            printf("\nEntree invalide. Veuillez saisir un nombre.");
            while (getchar() != '\n');
            choix = -1;
        }
        else if (choix < 1 || choix > 2) {
            printf("\nChoix invalide. Veuillez entrer 1 ou 2.");
        }
    } while (choix < 1 || choix > 2);
    printf("Critere de suppression :\n");
    printf("1. Apogee\n2. Nom\n3. Age\n");
    do {
        printf("\nVotre choix (1, 2 ou 3) : ");
        if (scanf("%d", &critere) != 1) {
            printf("\nEntree invalide. Veuillez saisir un nombre.");
            while (getchar() != '\n');
            critere = -1;
        }
        else if (critere < 1 || critere > 3) {
            printf("\nChoix invalide. Veuillez entrer un nombre entre 1 et 3.");
        }
    } while (critere < 1 || critere > 3);
    printf("Entrez la valeur a supprimer : ");
    scanf("%s", valeur);
    Etudiant* courant = liste->tete;
    Etudiant* precedent = NULL;
    Etudiant* candidats[100];
    int trouve = 0;
    while (courant != NULL) {
        int match = 0;
        if (critere == 1)
            match = (courant->apogee == atoi(valeur));
        else if (critere == 2)
            match = (strcmp(courant->nom, valeur) == 0);
        else if (critere == 3)
            match = (courant->age == atoi(valeur));
        if (match) {
            candidats[trouve++] = courant;
        }
        courant = courant->suivant;
    }
    if (trouve == 0) {
        printf("\nAucun etudiant trouve avec ce critere.");
        return;
    }
    else if (trouve > 1) {
        printf("\nPlusieurs etudiants trouves avec ce critere.");
        for (int i = 0; i < trouve; i++) {
            courant = candidats[i];
            printf("\nEtudiant: %d. Apogee: %d , Nom et prenom: %s %s , Age: %d",i + 1, courant->apogee, courant->nom, courant->prenom, courant->age);
        }
        printf("\nVeuillez selectionner un sous-critere pour identifier un etudiant unique :");
        printf("\n1. Par Apogee\n2. Par Nom et Prenom");
        int sousCritere;
        do {
            printf("\nVotre choix (1 ou 2) : ");
            if (scanf("%d", &sousCritere) != 1) {
                printf("\nEntree invalide. Veuillez saisir un nombre.");
                while (getchar() != '\n');
                sousCritere = -1;
            }
            else if (sousCritere < 1 || sousCritere > 2) {
                printf("\nChoix invalide. Veuillez entrer 1 ou 2.");
            }
        } while (sousCritere < 1 || sousCritere > 2);
        char sousValeur1[50],sousValeur2[50];
        if(sousCritere == 1){
                    printf("Entrez l'apogee : ");
                    scanf("%s", sousValeur1);
        }
        else if(sousCritere == 2){
                    printf("Entrez le nom : ");
                    scanf("%s", sousValeur1);
                    printf("Entrez le prenom : ");
                    scanf("%s", sousValeur2);
        }
        trouve = 0;
        for (int i = 0; i < 100 && candidats[i] != NULL; i++) {
            if ((sousCritere == 1 && candidats[i]->apogee == atoi(sousValeur1)) ||
                (sousCritere == 2 && strcmp(candidats[i]->nom, sousValeur1) == 0 &&
                 strcmp(candidats[i]->prenom, sousValeur2) == 0)) {
                courant = candidats[i];
                trouve = 1;
                break;
            }
        }
        if (!trouve) {
            printf("\nAucun etudiant trouve avec le sous-critere.");
            return;
        }
    }
    else {
        courant = candidats[0];
    }
    if (choix == 1) {
        courant->notes.AO = -1;
        courant->notes.BD = -1;
        courant->notes.C = -1;
        courant->notes.ThG = -1;
        courant->notes.RI = -1;

        printf("\nLes notes de l'etudiant %s %s ont ete supprimees.\n", courant->nom,courant->prenom);
    }
    else if (choix == 2) {
    precedent = NULL;
    Etudiant* temp = liste->tete;
    while (temp != NULL) {
        if (temp == courant) {
            if (precedent == NULL) {
                liste->tete = courant->suivant;
            }
            else {
                precedent->suivant = courant->suivant;
            }
            free(courant);
            liste->nef--;
            printf("\nL'etudiant %s %s supprime avec succes.",courant->nom,courant->prenom);
            return;
        }
        precedent = temp;
        temp = temp->suivant;
        }
    }
}
// ----> O(n)

void RechercherEtudiant(Liste* liste) {
    if (liste == NULL || liste->tete == NULL) {
        printf("\nLa liste des etudiants est vide.");
        return;
    }
    int critere;
    char valeur[50];
    printf("Critere de recherche :\n");
    printf("1. Apogee\n2. Nom\n3. Age\n");
    do {
        printf("\nVotre choix (1, 2 ou 3) : ");
        if (scanf("%d", &critere) != 1) {
            printf("\nEntree invalide. Veuillez saisir un nombre.");
            while (getchar() != '\n');
            critere = -1;
        }
        else if (critere < 1 || critere > 3) {
            printf("\nChoix invalide. Veuillez entrer un nombre entre 1 et 3.");
        }
    } while (critere < 1 || critere > 3);
    printf("Entrez la valeur a chercher : ");
    scanf("%s", valeur);
    int apogee, age;
    char nom[50], prenom[50];
    Notes notes;
    Etudiant* etudiant = liste->tete;
    int trouve = 0;
    Etudiant* candidats[100];
    int count = 0;
    while (etudiant != NULL) {
        if ((critere == 1 && etudiant->apogee == atoi(valeur)) ||
            (critere == 2 && strcmp(etudiant->nom, valeur) == 0) ||
            (critere == 3 && etudiant->age == atoi(valeur))) {
            candidats[count++] = etudiant;
        }
        etudiant = etudiant->suivant;
    }
    if (count == 0) {
        printf("\nAucun etudiant trouve.");
        return;
    }
    if (count == 1) {
        etudiant = candidats[0];
        printf("\nL'etudiant que vous avez recherche a ete trouve. Voici ses informations :\n");
        printf("\nApogee: %d, Nom: %s, Prenom: %s, Age: %d\nNotes: AO=%.2f, BD=%.2f, C=%.2f, ThG=%.2f, RI=%.2f\nMoyenne=%.2f",
               etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age,
               etudiant->notes.AO, etudiant->notes.BD, etudiant->notes.C,
               etudiant->notes.ThG, etudiant->notes.RI, CalculerMoyenne(etudiant->notes));
    }
    else {
        printf("\nPlusieurs etudiants trouves avec ce critere.");
        for (int i = 0; i < count; i++) {
            etudiant = candidats[i];
            printf("\nEtudiant: %d. Apogee: %d , Nom et Prenom: %s %s , Age: %d",i + 1, etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age);
        }
        int sousCritere;
        printf("\nVeuillez selectionner un sous-critere pour identifier un etudiant unique :");
        printf("\n1. Par Apogee\n2. Par Nom et Prenom");
        do {
            printf("\nVotre choix (1 ou 2) : ");
            if (scanf("%d", &sousCritere) != 1) {
                printf("\nEntree invalide. Veuillez saisir un nombre.");
                while (getchar() != '\n');
                sousCritere = -1;
            }
            else if (sousCritere < 1 || sousCritere > 2) {
                printf("\nChoix invalide. Veuillez entrer 1 ou 2.");
            }
        } while (sousCritere < 1 || sousCritere > 2);
        char sousValeur[50],sousValeur1[50],sousValeur2[50];
        if(sousCritere == 1){
                    printf("Entrez l'apogee : ");
                    scanf("%s", sousValeur);
        }
        else if(sousCritere == 2){
                    printf("Entrez le nom : ");
                    scanf("%s", sousValeur1);
                    printf("Entrez le prenom : ");
                    scanf("%s", sousValeur2);
        }
        for (int i = 0; i < count; i++) {
            if ((sousCritere == 1 && candidats[i]->apogee == atoi(sousValeur)) ||
               (sousCritere == 2 && strcmp(candidats[i]->nom, sousValeur1) == 0 && strcmp(candidats[i]->prenom, sousValeur2) == 0)) {
                etudiant = candidats[i];
                printf("\nL'etudiant que vous avez recherche a ete trouve. Voici ses informations :\n");
                printf("\nApogee: %d, Nom: %s, Prenom: %s, Age: %d\nNotes: AO=%.2f, BD=%.2f, C=%.2f, ThG=%.2f, RI=%.2f\nMoyenne=%.2f",
                       etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age,
                       etudiant->notes.AO, etudiant->notes.BD, etudiant->notes.C,
                       etudiant->notes.ThG, etudiant->notes.RI, CalculerMoyenne(etudiant->notes));
                return;
            }
        }
        printf("\nAucun etudiant avec ce sous-critere.\n");
    }
}
// ----> O(n)

void ModifierEtudiant(Liste* liste) {
    if (liste == NULL || liste->tete == NULL) {
        printf("\nLa liste des etudiants est vide.");
        return;
    }
    int critere,choix;
    char valeur[50];
    printf("\nQue voulez-vous modifier ?");
    printf("\n1. Toutes les informations\n2. Seulement les notes");
    do {
        printf("\nVotre choix (1 ou 2) : ");
        if (scanf("%d", &choix) != 1) {
            printf("\nEntree invalide. Veuillez saisir un nombre.");
            while (getchar() != '\n');
            choix = -1;
        }
        else if (choix < 1 || choix > 2) {
            printf("\nChoix invalide. Veuillez entrer 1 ou 2.");
        }
    } while (choix < 1 || choix > 2);
    printf("\nCritere pour modifier:");
    printf("\n1. Apogee\n2. Nom");
    do {
        printf("\nVotre choix (1 ou 2) : ");
        if (scanf("%d", &critere) != 1) {
            printf("\nEntree invalide. Veuillez saisir un nombre.");
            while (getchar() != '\n');
            critere = -1;
        }
        else if (critere < 1 || critere > 2) {
            printf("\nChoix invalide. Veuillez entrer 1 ou 2.");
        }
    } while (critere < 1 || critere > 2);
    printf("Entrez la valeur : ");
    scanf("%s", valeur);
    Etudiant* courant = liste->tete;
    Etudiant* candidats[100];
    int count = 0;
    while (courant != NULL) {
        if ((critere == 1 && courant->apogee == atoi(valeur)) ||
            (critere == 2 && strcmp(courant->nom, valeur) == 0)) {
                candidats[count++] = courant;
        }
        courant = courant->suivant;
    }
    if (count == 0) {
        printf("\nAucun etudiant trouve avec ce critere.");
        return;
    }
    if (count == 1) {
        courant = candidats[0];
        if (choix == 1) {
            printf("\nEtudiant trouve. Entrez les nouvelles informations :");
            int nouvelApogee;
            int apogeeExistant;
            do {
                apogeeExistant = 0;
                printf("\nEntrez le nouveau numero d'apogee : ");
                scanf("%d", &nouvelApogee);

                Etudiant* temp = liste->tete;
                while (temp != NULL) {
                    if (temp->apogee == nouvelApogee && temp != courant) {
                        apogeeExistant = 1;
                        printf("Ce numero d'apogee existe deja. Veuillez en saisir un autre.\n");
                        break;
                    }
                    temp = temp->suivant;
                }
            } while (apogeeExistant);

            courant->apogee = nouvelApogee;
            printf("Entrez le nouveau nom : ");
            scanf("%s", courant->nom);
            printf("Entrez le nouveau prenom : ");
            scanf("%s", courant->prenom);
            printf("Entrez le nouvel age : ");
            scanf("%d", &courant->age);
            printf("Entrez les nouvelles notes : ");
            printf("\nArchitecture des Ordinateurs (AO):");
            scanf("%f",&courant->notes.AO);
            printf("Bases de donnees Relationnelle (BD):");
            scanf("%f",&courant->notes.BD);
            printf("Structure de Donnees en C (C):");
            scanf("%f",&courant->notes.C);
            printf("Theorie des Graphes (ThG):");
            scanf("%f",&courant->notes.ThG);
            printf("Reseaux informatiques (RI):");
            scanf("%f",&courant->notes.RI);
            printf("\nToutes les informations ont ete modifiees avec succes.\n");
        }
        else if (choix == 2) {
            printf("\nEntrez les nouvelles notes (AO BD C ThG RI) :");
            scanf("%f %f %f %f %f", &courant->notes.AO, &courant->notes.BD, &courant->notes.C, &courant->notes.ThG, &courant->notes.RI);
            printf("\nLes notes ont ete modifiees avec succes.\n");

        }
        return;
    }
    else {
        printf("\nPlusieurs etudiants trouves avec ce critere.");
        for (int i = 0; i < count; i++) {
            courant = candidats[i];
            printf("\nEtudiant: %d. Apogee: %d , Nom et prenom: %s %s , Age: %d",i + 1, courant->apogee, courant->nom, courant->prenom, courant->age);
        }
        printf("\nVeuillez preciser avec un sous-critere :");
        printf("\n1. Par Apogee\n2. Par Nom et Prenom");
        int sousCritere;
        do {
            printf("\nVotre choix (1 ou 2) : ");
            if (scanf("%d", &sousCritere) != 1) {
                printf("\nEntree invalide. Veuillez saisir un nombre.");
            while (getchar() != '\n');
            sousCritere = -1;
            }
            else if (sousCritere < 1 || sousCritere > 2) {
                printf("\nChoix invalide. Veuillez entrer 1 ou 2.");
            }
        } while (sousCritere < 1 || sousCritere > 2);
        char sousValeur1[50],sousValeur2[50];
        if(sousCritere == 1){
                    printf("Entrez l'apogee : ");
                    scanf("%s", sousValeur1);
        }
        else if(sousCritere == 2){
                    printf("Entrez le nom : ");
                    scanf("%s", sousValeur1);
                    printf("Entrez le prenom : ");
                    scanf("%s", sousValeur2);
        }
        for (int i = 0; i < count; i++) {
            if ((sousCritere == 1 && candidats[i]->apogee == atoi(sousValeur1)) ||
               (sousCritere == 2 && strcmp(candidats[i]->nom, sousValeur1) == 0 && strcmp(candidats[i]->prenom, sousValeur2) == 0)) {
                courant = candidats[i];
                if (choix == 1) {
                    printf("\nEtudiant trouve. Entrez les nouvelles informations :");
                    int nouvelApogee;
                    int apogeeExistant;
                    do {
                        apogeeExistant = 0;
                        printf("\nEntrez le nouveau numero d'apogee : ");
                        scanf("%d", &nouvelApogee);

                        Etudiant* temp = liste->tete;
                        while (temp != NULL) {
                            if (temp->apogee == nouvelApogee && temp != courant) {
                            apogeeExistant = 1;
                            printf("Ce numero d'apogee existe deja. Veuillez en saisir un autre.\n");
                             break;
                        }
                    temp = temp->suivant;
                }
            } while (apogeeExistant);

            courant->apogee = nouvelApogee;
                    printf("Entrez le nouveau nom : ");
                    scanf("%s", courant->nom);
                    printf("Entrez le nouveau prenom : ");
                    scanf("%s", courant->prenom);
                    printf("Entrez le nouvel age : ");
                    scanf("%d", &courant->age);
                    printf("Entrez les nouvelles notes : ");
                    printf("\nArchitecture des Ordinateurs (AO):");
                    scanf("%f",&courant->notes.AO);
                    printf("Bases de donnees Relationnelle (BD):");
                    scanf("%f",&courant->notes.BD);
                    printf("Structure de Donnees en C (C):");
                    scanf("%f",&courant->notes.C);
                    printf("Theorie des Graphes (ThG):");
                    scanf("%f",&courant->notes.ThG);
                    printf("Reseaux informatiques (RI):");
                    scanf("%f",&courant->notes.RI);
                    printf("\nToutes les informations ont ete modifiees avec succes.\n");
                }
                else if (choix == 2) {
                    printf("Entrez les nouvelles notes : ");
                    printf("\nArchitecture des Ordinateurs (AO):");
                    scanf("%f",&courant->notes.AO);
                    printf("Bases de donnees Relationnelle (BD):");
                    scanf("%f",&courant->notes.BD);
                    printf("Structure de Donnees en C (C):");
                    scanf("%f",&courant->notes.C);
                    printf("Theorie des Graphes (ThG):");
                    scanf("%f",&courant->notes.ThG);
                    printf("Reseaux informatiques (RI):");
                    scanf("%f",&courant->notes.RI);
                    printf("\nLes notes ont ete modifiees avec succes.\n");
                }
            return;
            }
        }
    printf("\nAucun etudiant trouve avec ce sous-critere.");
    }
}
// ----> O(n)

void MeilleurPireEnMoyenne(Liste* liste) {
    if (liste->tete == NULL) {
        printf("\nLa liste des etudiants est vide.\n");
        return;
    }
    Etudiant* etudiants[liste->nef];
    Etudiant* courant = liste->tete;
    int index = 0;
    while (courant != NULL) {
        etudiants[index++] = courant;
        courant = courant->suivant;
    }

    for (int i = 1; i < index; i++) {
        Etudiant* temp = etudiants[i];
        float tempMoyenne = CalculerMoyenne(temp->notes);
        int j = i - 1;
        while (j >= 0 && CalculerMoyenne(etudiants[j]->notes) < tempMoyenne) {
            etudiants[j + 1] = etudiants[j];
            j--;
        }
        etudiants[j + 1] = temp;
    }
    Etudiant* meilleur = etudiants[0];
    Etudiant* pire = etudiants[index - 1];
    printf("\nMeilleure moyenne : %.2f (%s %s)",CalculerMoyenne(meilleur->notes),meilleur->prenom,meilleur->nom);
    printf("\nPire moyenne      : %.2f (%s %s)",CalculerMoyenne(pire->notes),pire->prenom,pire->nom);
}
// ----> O(n^2)

void MeilleurEtPireEnMoyenne(Liste* liste, FILE* fichier) {
    if (liste->tete == NULL) {
        printf("\nLa liste des etudiants est vide.\n");
        return;
    }

    Etudiant* etudiants[liste->nef];
    Etudiant* courant = liste->tete;
    int index = 0;
    while (courant != NULL) {
        etudiants[index++] = courant;
        courant = courant->suivant;
    }

    for (int i = 1; i < index; i++) {
        Etudiant* temp = etudiants[i];
        float tempMoyenne = CalculerMoyenne(temp->notes);
        int j = i - 1;
        while (j >= 0 && CalculerMoyenne(etudiants[j]->notes) < tempMoyenne) {
            etudiants[j + 1] = etudiants[j];
            j--;
        }
        etudiants[j + 1] = temp;
    }
    Etudiant* meilleur = etudiants[0];
    Etudiant* pire = etudiants[index - 1];
    fprintf(fichier, "\nMeilleure moyenne                   \t: %.2f/20 (%s %s)\n",CalculerMoyenne(meilleur->notes),meilleur->prenom,meilleur->nom);
    fprintf(fichier, "\nPire moyenne                        \t: %.2f/20 (%s %s)\n",CalculerMoyenne(pire->notes),pire->prenom,pire->nom);
}
// ----> O(n^2)

Etudiant* MeilleurParModule(Liste* liste, const char* module) {
    if (liste == NULL || liste->tete == NULL || module == NULL) {
        printf("\nLa liste des etudiants est vide ou le module est invalide.");
        return NULL;
    }
    Etudiant* etudiants[liste->nef];
    Etudiant* courant = liste->tete;
    int index = 0;
    while (courant != NULL) {
        etudiants[index++] = courant;
        courant = courant->suivant;
    }
    for (int i = 1; i < index; i++) {
        Etudiant* tmp = etudiants[i];
        float noteTmp  = 0.0;

        if (strcmp(module, "AO") == 0)
            noteTmp = tmp->notes.AO;
        else if (strcmp(module, "BD") == 0)
            noteTmp = tmp->notes.BD;
        else if (strcmp(module, "C") == 0)
            noteTmp = tmp->notes.C;
        else if (strcmp(module, "ThG") == 0)
            noteTmp = tmp->notes.ThG;
        else if (strcmp(module, "RI") == 0)
            noteTmp = tmp->notes.RI;
        else {
            printf("\nLe module est invalide : %s", module);
            return NULL;
        }

        int j = i - 1;
        while (j >= 0) {
            float noteJ = 0.0;
            if (strcmp(module, "AO") == 0)
                noteJ = etudiants[j]->notes.AO;
            else if (strcmp(module, "BD") == 0)
                noteJ = etudiants[j]->notes.BD;
            else if (strcmp(module, "C") == 0)
                noteJ = etudiants[j]->notes.C;
            else if (strcmp(module, "ThG") == 0)
                noteJ = etudiants[j]->notes.ThG;
            else if (strcmp(module, "RI") == 0)
                noteJ = etudiants[j]->notes.RI;
            if (noteTmp > noteJ) {
                etudiants[j + 1] = etudiants[j];
                j--;
            }
            else {
                break;
            }
        }
        etudiants[j + 1] = tmp;
    }
    return etudiants[0];
}
// ----> O(n^2)

void TroisMeilleursParModule(Liste* liste, const char* module) {
    if (liste == NULL || liste->tete == NULL || module == NULL) {
        printf("Liste vide ou module invalide.\n");
        return;
    }
    Etudiant* etudiants[liste->nef];
    Etudiant* courant = liste->tete;
    int index = 0;
    while (courant != NULL) {
        etudiants[index++] = courant;
        courant = courant->suivant;
    }
    for (int i = 1; i < index; i++) {
        Etudiant* tmp = etudiants[i];
        float noteTmp = 0.0;
        if (strcmp(module, "AO") == 0)
            noteTmp = tmp->notes.AO;
        else if (strcmp(module, "BD") == 0)
            noteTmp = tmp->notes.BD;
        else if (strcmp(module, "C") == 0)
            noteTmp = tmp->notes.C;
        else if (strcmp(module, "ThG") == 0)
            noteTmp = tmp->notes.ThG;
        else if (strcmp(module, "RI") == 0)
            noteTmp = tmp->notes.RI;
        else {
            printf("Module invalide : %s\n", module);
            return;
        }
        int j = i - 1;
        while (j >= 0) {
            float noteJ = 0.0;
            if (strcmp(module, "AO") == 0)
                noteJ = etudiants[j]->notes.AO;
            else if (strcmp(module, "BD") == 0)
                noteJ = etudiants[j]->notes.BD;
            else if (strcmp(module, "C") == 0)
                noteJ = etudiants[j]->notes.C;
            else if (strcmp(module, "ThG") == 0)
                noteJ = etudiants[j]->notes.ThG;
            else if (strcmp(module, "RI") == 0)
                noteJ = etudiants[j]->notes.RI;
            if (noteTmp > noteJ) {
                etudiants[j + 1] = etudiants[j];
                j--;
            }
            else {
                break;
            }
        }
        etudiants[j + 1] = tmp;
    }
    printf("\n\nLes trois meilleurs etudiants en %s sont :", module);
    for (int i = 0; i < 3 && i < index; i++) {
        float meilleureNote = 0.0;

        if (strcmp(module, "AO") == 0)
            meilleureNote = etudiants[i]->notes.AO;
        else if (strcmp(module, "BD") == 0)
            meilleureNote = etudiants[i]->notes.BD;
        else if (strcmp(module, "C") == 0)
            meilleureNote = etudiants[i]->notes.C;
        else if (strcmp(module, "ThG") == 0)
            meilleureNote = etudiants[i]->notes.ThG;
        else if (strcmp(module, "RI") == 0)
            meilleureNote = etudiants[i]->notes.RI;
        printf("\nApogee\t: %d  \t,Nom   \t: %s        \t,Prenom\t: %s     \t,Note  \t: %.2f    \t",etudiants[i]->apogee, etudiants[i]->nom, etudiants[i]->prenom, meilleureNote);
    }
}
// ----> O(n^2)

void TroisMeilleursEnMoyenne(Liste* liste) {
    if (liste == NULL || liste->tete == NULL) {
        printf("\nLa liste des etudiants est vide.");
        return;
    }
    Etudiant* etudiants[liste->nef];
    Etudiant* courant = liste->tete;
    int index = 0;
    while (courant != NULL) {
        etudiants[index++] = courant;
        courant = courant->suivant;
    }
    for (int i = 1; i < index; i++) {
        Etudiant* tmp = etudiants[i];
        int j = i - 1;
        while (j >= 0 && CalculerMoyenne(etudiants[j]->notes) < CalculerMoyenne(tmp->notes)) {
            etudiants[j + 1] = etudiants[j];
            j--;
        }
        etudiants[j + 1] = tmp;
    }
    printf("\nLes trois meilleurs etudiants en moyenne generale sont :\n");
    for (int i = 0; i < 3 && i < index; i++) {
        printf("\nApogee\t: %d  \t,Nom   \t: %s        \t,Prenom\t: %s     \t,Moyenne\t: %.2f    \t",etudiants[i]->apogee, etudiants[i]->nom, etudiants[i]->prenom, CalculerMoyenne(etudiants[i]->notes));
    }
}
// ----> O(n^2)

const char* ValidationModule(float note) {
    if (note >= 12.0) {
        return "Valide";
    }
    else {
        return "Non valide";
    }
}
// ----> O(1)

const char* StatutEtudiantAvecMention(float moyenneGenerale) {
   if (moyenneGenerale < 12.0) {
        return "Ajourne (Passable)";
    }
    else if (moyenneGenerale < 14.0) {
        return "Admis (Assez Bien)";
    }
    else if (moyenneGenerale < 16.0) {
        return "Admis (Bien)";
    }
    else {
        return "Admis (Tres Bien)";
    }
}
// ----> O(1)

void GenererRapport(Liste* liste, const char *fichier) {
    printf("\nRapport academique complet :\n");
    if (liste == NULL || liste->tete == NULL) {
        printf("\nLa liste des etudiants est vide.");
        return;
    }
    int choix, critere;
    char valeur[50];
    char valeur1[50],valeur2[50];
    Etudiant* etudiant = liste->tete;
    printf("\nQue voulez-vous afficher ?");
    printf("\n1. Un seul etudiant\n2. Tous les etudiants");
    do {
        printf("\nVotre choix (1 ou 2) : ");
        if (scanf("%d", &choix) != 1) {
            printf("\nEntree invalide. Veuillez saisir un nombre.");
            while (getchar() != '\n');
            choix = -1;
        }
        else if (choix < 1 || choix > 2) {
            printf("\nChoix invalide. Veuillez entrer 1 ou 2.");
        }
    } while (choix < 1 || choix > 2);
    if (choix == 1) {
        printf("\nCritere pour afficher un etudiant :");
        printf("\n1. Apogee\n2. Nom\n3. Age");
        do {
            printf("\nVotre choix (1, 2 ou 3) : ");
            if (scanf("%d", &critere) != 1) {
                printf("\nEntree invalide. Veuillez saisir un nombre.");
                while (getchar() != '\n');
                critere = -1;
            }
            else if (critere < 1 || critere > 3) {
                printf("\nChoix invalide. Veuillez entrer un nombre entre 1 et 3.");
            }
        } while (critere < 1 || critere > 3);
        printf("Entrez la valeur : ");
        scanf("%s", valeur);
        int trouve = 0;
        Etudiant* candidats[100];
        while (etudiant != NULL) {
            if ((critere == 1 && etudiant->apogee == atoi(valeur)) ||
                (critere == 2 && strcmp(etudiant->nom, valeur) == 0)||
                (critere == 3 && etudiant->age == atoi(valeur))) {
                    candidats[trouve++] = etudiant;
                }
                etudiant = etudiant->suivant;
        }
        if (trouve == 0) {
            printf("Aucun etudiant trouve.");
            return;
        }
        else if (trouve == 1) {
            etudiant = candidats[0];
            printf("\n\n----Rapport academique complet pour etudiant  ----\n ");
            printf("\nApogee                       \t: %d\nNom                            \t: %s\nPrenom                         \t: %s\nAge                            \t: %d",etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age);
            printf("\nLes notes                      \t:");
            printf("\nArchitecture des Ordinateurs   \t: %.2f/20  (%s)", etudiant->notes.AO, ValidationModule(etudiant->notes.AO));
            printf("\nBases de donnees Relationnelle \t: %.2f/20  (%s)", etudiant->notes.BD, ValidationModule(etudiant->notes.BD));
            printf("\nStructure de Donnees en C      \t: %.2f/20  (%s)", etudiant->notes.C, ValidationModule(etudiant->notes.C));
            printf("\nTheorie des Graphes            \t: %.2f/20  (%s)", etudiant->notes.ThG, ValidationModule(etudiant->notes.ThG));
            printf("\nReseaux informatiques          \t: %.2f/20  (%s)", etudiant->notes.RI, ValidationModule(etudiant->notes.RI));
            printf("\n\nMoyenne generale               \t: %.2f/20   %s\n", CalculerMoyenne(etudiant->notes),StatutEtudiantAvecMention(CalculerMoyenne(etudiant->notes)));
            char fichier[100];
            sprintf(fichier,"%s.%s_rapport.txt",etudiant->nom,etudiant->prenom);
            FILE *f = fopen(fichier, "w");
            if (f == NULL) {
            printf("\nErreur lors de l'ouverture du fichier.");
            return ;
            }
            if (etudiant != NULL) {
                 fprintf(f,"-------------------------------------------------------------------------------------------------------------------------------------------------------------");
                 fprintf(f,"\n| Universite Abdelmalek Essaadi                                                                                                                             |");
                 fprintf(f,"\n|                                                                Annee Universitaire :2024/2025                                                             |");
                 fprintf(f,"\n-------------------------------------------------------------------------------------------------------------------------------------------------------------");
                 fprintf(f,"\nEcole Nationale des Sciences Appliquees Tetouan");
                 fprintf(f,"\n                                                                ----------------------------------");
                 fprintf(f,"\n                                                               |   RAPPORT ACADEMIQUE COMPLET    |");
                 fprintf(f,"\n                                                                ----------------------------------");
                 fprintf(f,"\n                                                                      -----------------------");
                 fprintf(f,"\n                                                                      |      SEMESTRE 1     |");
                 fprintf(f,"\n                                                                      -----------------------");
                 fprintf(f, "\n\nApogee                       \t: %d\nNom                            \t: %s\nPrenom                         \t: %s\nAge                            \t: %d",etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age);
                 fprintf(f,"\n\nInscrite en 1re annee du Cycle d'Ingenieur : Genie Informatique 1");
                 fprintf(f,"\nA obtenu les notes suivantes   \t:");
                 fprintf(f,"\n-------------------------------------------------------------------------------------------------------");
                 fprintf(f,"\n                                    \t|Note/Bareme\t|Resultat         \t|Semestre             |");
                 fprintf(f,"\n------------------------------------------------------------------------------------------------------|");
                 fprintf(f,"\nArchitecture des Ordinateurs        \t| %.2f/20   \t| %s        \t| S1 2024/25          |", etudiant->notes.AO, ValidationModule(etudiant->notes.AO));
                 fprintf(f,"\nBases de donnees Relationnelle      \t| %.2f/20   \t| %s        \t| S1 2024/25          |", etudiant->notes.BD, ValidationModule(etudiant->notes.BD));
                 fprintf(f,"\nStructure de Donnees en C           \t| %.2f/20   \t| %s        \t| S1 2024/25          |", etudiant->notes.C, ValidationModule(etudiant->notes.C));
                 fprintf(f,"\nTheorie des Graphes                 \t| %.2f/20   \t| %s        \t| S1 2024/25          |", etudiant->notes.ThG, ValidationModule(etudiant->notes.ThG));
                 fprintf(f,"\nReseaux informatiques               \t| %.2f/20   \t| %s        \t| S1 2024/25          |", etudiant->notes.RI, ValidationModule(etudiant->notes.RI));
                 fprintf(f,"\n-------------------------------------------------------------------------------------------------------");
                 fprintf(f,"\n\nMoyenne generale                    \t: %.2f/20   \t  %s\n", CalculerMoyenne(etudiant->notes),StatutEtudiantAvecMention(CalculerMoyenne(etudiant->notes)));
                 fprintf(f,  "\nMoyenne generale de la classe       \t: %.2f/20\n",MoyenneClasse(liste, f));
                 MeilleurEtPireEnMoyenne(liste, f);
                 printf("\n\nRapport genere avec succes dans le fichier '%s'.", fichier);
                 fclose(f);
            }
            return;
        }
        else {
            printf("\nPlusieurs etudiants trouves avec ce critere :");
            for (int i = 0; i < trouve; i++) {
                etudiant = candidats[i];
                printf("\nEtudiant %d - Apogee: %d, Nom et prenom: %s %s, Age: %d",i + 1, etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age);
            }
            printf("\nVeuillez selectionner un sous-critere pour identifier un etudiant unique :");
            printf("\n1. Par Apogee\n2. Par Nom et Prenom");
            printf("\nVotre choix : ");
            int sousCritere;
            do {
                printf("\nVotre choix (1 ou 2) : ");
                if (scanf("%d", &sousCritere) != 1) {
                printf("\nEntree invalide. Veuillez saisir un nombre.");
                while (getchar() != '\n');
                sousCritere = -1;
                }
                else if (sousCritere < 1 || sousCritere > 2) {
                    printf("\nChoix invalide. Veuillez entrer 1 ou 2.");
                }
            } while (sousCritere < 1 || sousCritere > 2);
            if(sousCritere == 1){
                    printf("Entrez l'apogee : ");
                    scanf("%s", valeur1);
            }
            else if(sousCritere == 2){
                    printf("Entrez le nom : ");
                    scanf("%s", valeur1);
                    printf("Entrez le prenom : ");
                    scanf("%s", valeur2);
            }
            for (int i = 0; i < trouve; i++) {
                if ((sousCritere == 1 && candidats[i]->apogee == atoi(valeur1)) ||
                       (sousCritere == 2 && strcmp(candidats[i]->nom, valeur1) == 0 && strcmp(candidats[i]->prenom, valeur2) == 0)) {
                    etudiant = candidats[i];
                    printf("\n\n----Rapport academique complet pour etudiant  ----\n ");
                    printf("\nApogee                       \t: %d\nNom                            \t: %s\nPrenom                         \t: %s\nAge                            \t: %d",etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age);
                    printf("\nLes notes                      \t:");
                    printf("\nArchitecture des Ordinateurs   \t: %.2f/20  (%s)", etudiant->notes.AO, ValidationModule(etudiant->notes.AO));
                    printf("\nBases de donnees Relationnelle \t: %.2f/20  (%s)", etudiant->notes.BD, ValidationModule(etudiant->notes.BD));
                    printf("\nStructure de Donnees en C      \t: %.2f/20  (%s)", etudiant->notes.C, ValidationModule(etudiant->notes.C));
                    printf("\nTheorie des Graphes            \t: %.2f/20  (%s)", etudiant->notes.ThG, ValidationModule(etudiant->notes.ThG));
                    printf("\nReseaux informatiques          \t: %.2f/20  (%s)", etudiant->notes.RI, ValidationModule(etudiant->notes.RI));
                    printf("\n\nMoyenne generale               \t: %.2f/20   %s\n", CalculerMoyenne(etudiant->notes),StatutEtudiantAvecMention(CalculerMoyenne(etudiant->notes)));
                    char fichier[100];
                    sprintf(fichier,"%s.%s_rapport.txt",etudiant->nom,etudiant->prenom);
                    FILE *f = fopen(fichier, "w");
                        if (f == NULL) {
                        printf("\nErreur lors de l'ouverture du fichier.");
                        return ;
                        }
                    if (etudiant != NULL) {
                        fprintf(f,"-------------------------------------------------------------------------------------------------------------------------------------------------------------");
                        fprintf(f,"\n| Universite Abdelmalek Essaadi                                                                                                                             |");
                        fprintf(f,"\n|                                                                Annee Universitaire :2024/2025                                                             |");
                        fprintf(f,"\n-------------------------------------------------------------------------------------------------------------------------------------------------------------");
                        fprintf(f,"\nEcole Nationale des Sciences Appliquees Tetouan");
                        fprintf(f,"\n                                                                ----------------------------------");
                        fprintf(f,"\n                                                               |   RAPPORT ACADEMIQUE COMPLET    |");
                        fprintf(f,"\n                                                                ----------------------------------");
                        fprintf(f,"\n                                                                      -----------------------");
                        fprintf(f,"\n                                                                      |      SEMESTRE 1     |");
                        fprintf(f,"\n                                                                      -----------------------");
                        fprintf(f, "\n\nApogee                       \t: %d\nNom                            \t: %s\nPrenom                         \t: %s\nAge                            \t: %d",etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age);
                        fprintf(f,"\n\nInscrite en 1re annee du Cycle d'Ingenieur : Genie Informatique 1");
                        fprintf(f,"\nA obtenu les notes suivantes   \t:");
                        fprintf(f,"\n-------------------------------------------------------------------------------------------------------");
                        fprintf(f,"\n                                    \t|Note/Bareme\t|Resultat         \t|Semestre             |");
                        fprintf(f,"\n------------------------------------------------------------------------------------------------------|");
                        fprintf(f,"\nArchitecture des Ordinateurs        \t| %.2f/20   \t| %s        \t| S1 2024/25          |", etudiant->notes.AO, ValidationModule(etudiant->notes.AO));
                        fprintf(f,"\nBases de donnees Relationnelle      \t| %.2f/20   \t| %s        \t| S1 2024/25          |", etudiant->notes.BD, ValidationModule(etudiant->notes.BD));
                        fprintf(f,"\nStructure de Donnees en C           \t| %.2f/20   \t| %s        \t| S1 2024/25          |", etudiant->notes.C, ValidationModule(etudiant->notes.C));
                        fprintf(f,"\nTheorie des Graphes                 \t| %.2f/20   \t| %s        \t| S1 2024/25          |", etudiant->notes.ThG, ValidationModule(etudiant->notes.ThG));
                        fprintf(f,"\nReseaux informatiques               \t| %.2f/20   \t| %s        \t| S1 2024/25          |", etudiant->notes.RI, ValidationModule(etudiant->notes.RI));
                        fprintf(f,"\n-------------------------------------------------------------------------------------------------------");
                        fprintf(f,"\n\nMoyenne generale                    \t: %.2f/20   \t  %s\n", CalculerMoyenne(etudiant->notes),StatutEtudiantAvecMention(CalculerMoyenne(etudiant->notes)));
                        fprintf(f,  "\nMoyenne generale de la classe       \t: %.2f/20\n ",MoyenneClasse(liste, f));
                        MeilleurEtPireEnMoyenne(liste, f);
                        printf("\n\nRapport genere avec succes dans le fichier '%s'.", fichier);
                        fclose(f);
                    }
                    else {
                            printf("\nAucun etudiant trouve avec ce sous-critere.");
                    }
                    return;
                }
            }
        }
    }
    else if (choix == 2) {
        FILE *f = fopen(fichier, "w");
        if (f == NULL) {
        printf("\nErreur lors de l'ouverture du fichier.");
        return ;
        }
        fprintf(f,"===================================================================================================================================================================================================================================================\n");
        fprintf(f,"                                              LA LISTE DES RAPPORTS ACADEMIQUES DES ETUDIANTS ");
        fprintf(f,"\n================================================================================================================================================================================================================================================");
        printf("\n\nListe des etudiants :");
        while (etudiant != NULL) {
            for(int i=0 ;i<liste->nef;i++){
                printf("\n\n\n----Rapport academique complet pour etudiant:%d----",i+1);
                printf("\n\nApogee                       \t: %d\nNom                            \t: %s\nPrenom                         \t: %s\nAge                            \t: %d",etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age);
                printf("\nLes notes                      \t:");
                printf("\nArchitecture des Ordinateurs   \t: %.2f/20  (%s)", etudiant->notes.AO, ValidationModule(etudiant->notes.AO));
                printf("\nBases de donnees Relationnelle \t: %.2f/20  (%s)", etudiant->notes.BD, ValidationModule(etudiant->notes.BD));
                printf("\nStructure de Donnees en C      \t: %.2f/20  (%s)", etudiant->notes.C, ValidationModule(etudiant->notes.C));
                printf("\nTheorie des Graphes            \t: %.2f/20  (%s)", etudiant->notes.ThG, ValidationModule(etudiant->notes.ThG));
                printf("\nReseaux informatiques          \t: %.2f/20  (%s)", etudiant->notes.RI, ValidationModule(etudiant->notes.RI));
                printf("\n\nMoyenne generale               \t: %.2f/20   %s\n", CalculerMoyenne(etudiant->notes),StatutEtudiantAvecMention(CalculerMoyenne(etudiant->notes)));
                etudiant = etudiant->suivant;
            }
        }
        printf("\n\n---- Trois meilleurs etudiants par module ----\n");
        printf("La signification de chaque module :\nAO : Architecture des Ordinateurs, BD : Bases de Donnees Relationnelles, C : Structure de Donnees en C,\nThG : Theorie des Graphes, RI : Reseaux Informatiques.");
        const char* modules[] = {"AO", "BD", "C", "ThG", "RI"};
        for (int i = 0; i < 5; i++) {
        TroisMeilleursParModule(liste, modules[i]);
        }
        printf("\n\n\n---- Trois meilleurs etudiants en moyenne generale ----");
        TroisMeilleursEnMoyenne(liste);
        Etudiant *actuel = liste->tete;
        while (actuel != NULL) {
            fprintf(f,"\n\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------------");
            fprintf(f,"\n| Universite Abdelmalek Essaadi                                                                                                                             |");
            fprintf(f,"\n|                                                                Annee Universitaire :2024/2025                                                             |");
            fprintf(f,"\n-------------------------------------------------------------------------------------------------------------------------------------------------------------");
            fprintf(f,"\nEcole Nationale des Sciences Appliquees Tetouan");
            fprintf(f,"\n                                                                ----------------------------------");
            fprintf(f,"\n                                                               |   RAPPORT ACADEMIQUE COMPLET    |");
            fprintf(f,"\n                                                                ----------------------------------");
            fprintf(f,"\n                                                                      -----------------------");
            fprintf(f,"\n                                                                      |      SEMESTRE 1     |");
            fprintf(f,"\n                                                                      -----------------------");
            fprintf(f, "\n\nApogee                       \t: %d\nNom                            \t: %s\nPrenom                         \t: %s\nAge                            \t: %d",actuel->apogee, actuel->nom, actuel->prenom, actuel->age);
            fprintf(f,"\n\nInscrite en 1re annee du Cycle d'Ingenieur : Genie Informatique 1");
            fprintf(f,"\nA obtenu les notes suivantes   \t:");
            fprintf(f,"\n-------------------------------------------------------------------------------------------------------");
            fprintf(f,"\n                                    \t|Note/Bareme\t|Resultat         \t|Semestre             |");
            fprintf(f,"\n------------------------------------------------------------------------------------------------------|");
            fprintf(f,"\nArchitecture des Ordinateurs        \t| %.2f/20   \t| %s        \t| S1 2024/25          |", actuel->notes.AO, ValidationModule(actuel->notes.AO));
            fprintf(f,"\nBases de donnees Relationnelle      \t| %.2f/20   \t| %s        \t| S1 2024/25          |", actuel->notes.BD, ValidationModule(actuel->notes.BD));
            fprintf(f,"\nStructure de Donnees en C           \t| %.2f/20   \t| %s        \t| S1 2024/25          |", actuel->notes.C, ValidationModule(actuel->notes.C));
            fprintf(f,"\nTheorie des Graphes                 \t| %.2f/20   \t| %s        \t| S1 2024/25          |", actuel->notes.ThG, ValidationModule(actuel->notes.ThG));
            fprintf(f,"\nReseaux informatiques               \t| %.2f/20   \t| %s        \t| S1 2024/25          |", actuel->notes.RI, ValidationModule(actuel->notes.RI));
            fprintf(f,"\n-------------------------------------------------------------------------------------------------------");
            fprintf(f,"\n\nMoyenne generale                    \t: %.2f/20   \t  %s\n", CalculerMoyenne(actuel->notes),StatutEtudiantAvecMention(CalculerMoyenne(actuel->notes)));
            fprintf(f,  "\nMoyenne generale de la classe       \t: %.2f/20\n",MoyenneClasse(liste, f));
            MeilleurEtPireEnMoyenne(liste, f);
            actuel = actuel->suivant;
            fprintf(f,"\n\n====================================================================================================================================================================================================================================\n\n");
        }
        MeilleurEtPireEnMoyenne(liste, f);
        fprintf(f,  "\nMoyenne generale de la classe       \t: %.2f/20\n",MoyenneClasse(liste, f));
        fprintf(f, "\nMeilleur etudiant par module:");
        fprintf(f,"\nLa signification de chaque module :\nAO : Architecture des Ordinateurs, BD : Bases de Donnees Relationnelles, C : Structure de Donnees en C, ThG : Theorie des Graphes, RI : Reseaux Informatiques.");
        for (int i = 0; i < 5; i++) {
            Etudiant* meilleurParModule = MeilleurParModule(liste, modules[i]);
            if (meilleurParModule != NULL) {
                fprintf(f, "\n%s\t: Apogee \t: %d , Nom et Prenom \t: %s %s     , Note \t: %.2f", modules[i], meilleurParModule->apogee, meilleurParModule->nom, meilleurParModule->prenom,
                    (strcmp(modules[i], "AO") == 0) ? meilleurParModule->notes.AO :
                    (strcmp(modules[i], "BD") == 0) ? meilleurParModule->notes.BD :
                    (strcmp(modules[i], "C") == 0) ? meilleurParModule->notes.C :
                    (strcmp(modules[i], "ThG") == 0) ? meilleurParModule->notes.ThG : meilleurParModule->notes.RI);
            }
        }
        fprintf(f,"\n\n====================================================================================================================================================================================================================================\n\n");
        fclose(f);
        printf("\n\nRapport genere avec succes dans le fichier '%s'.", fichier);
    }
    else {
        printf("\nChoix invalide.");
    }
}
// ----> O(n)

void sauvegarderEtudiants(Liste* liste, const char *fichier) {
    FILE *f = fopen(fichier, "w");
    if (fichier == NULL) {
        printf("\nErreur lors de l'ouverture du fichier.");
        return ;
    }
    Etudiant *etudiant = liste->tete;
    while (etudiant != NULL) {
        fprintf(f, "\n%d %s %s %d %.2f %.2f %.2f %.2f %.2f",
                etudiant->apogee, etudiant->nom, etudiant->prenom, etudiant->age,
                etudiant->notes.AO, etudiant->notes.BD, etudiant->notes.C,
                etudiant->notes.ThG, etudiant->notes.RI);
        etudiant = etudiant->suivant;
    }
    fclose(f);
}
// ----> O(n)

Liste * chargerEtudiants() {
    Liste* liste = CreerListe();
    FILE *f = fopen("etudiants.txt", "r");
    if (!f) {
        printf("\nFichier introuvable.");
    }
    Etudiant * etudiant;
    int apogee, age;
    char nom[50], prenom[50];
    Notes notes;
    while (fscanf(f, "%d %s %s %d %f %f %f %f %f",  &apogee, nom, prenom, &age,&notes.AO, &notes.BD, &notes.C, &notes.ThG, &notes.RI) != EOF) {
        Etudiant* etudiant = CreerEtudiant(apogee, nom, prenom, age, notes);
        if (liste->tete == NULL) {
            liste->tete = liste->queue = etudiant;
        }
        else {
            liste->queue->suivant = etudiant;
            liste->queue = etudiant;
        }
        liste->nef++;
             etudiant = etudiant->suivant;
    }
    fclose(f);
    return liste ;
}
// ----> O(n)

void menu() {
    Liste* listeEtudiants =chargerEtudiants();
    int choix, critere, position, apogee, age;
    char nom[50], prenom[50], valeur[50];
    Notes notes;
    Etudiant* etudiant;
    do {
        printf("\n\n----- MENU PRINCIPAL -----\n");
        printf("\n1. Ajouter un etudiant");
        printf("\n2. Rechercher un etudiant");
        printf("\n3. Afficher un etudiant unique ou tous les etudiants");
        printf("\n4. Supprimer un etudiant");
        printf("\n5. Modifier toutes les informations d'un etudiant ou seulement les notes");
        printf("\n6. Afficher les trois meilleurs par module");
        printf("\n7. Afficher les trois meilleurs en moyenne generale");
        printf("\n8. Generer un rapport academique");
        printf("\n0. Quitter");
        printf("\nVotre choix : ");
        if (scanf("%d", &choix) != 1) {
            printf("Entree invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choix) {
            case 1:
                printf("---- AJOUTE D'UN ETUDIANT ----\n");
                AjouterEtudiant(listeEtudiants);
                break;
            case 2:
                printf("---- RECHERCHE D'UN ETUDIANT ----\n");
                RechercherEtudiant(listeEtudiants);
                break;
            case 3:
                printf("---- AFFICHAGE UN ETUDIANT OU TOUS LES ETUDIANTS ----\n");
                AfficherEtudiants(listeEtudiants);
                break;
            case 4:
                printf("---- SUPPRESSION D'UN ETUDIANT ----\n");
                SupprimerEtudiant(listeEtudiants);
                break;

            case 5:
                printf("---- MODIFICATION TOUTES LES INFORMATIONS D'UN ETUDIANT OU SEULEMENT LES NOTES ----\n");
                ModifierEtudiant(listeEtudiants);
                break;
            case 6:
                printf("---- AFFICHAGE LES TROIS MEILLEURS PAR MODULE  ----\n");
                printf("\nLa signification de chaque module :\nAO : Architecture des Ordinateurs, BD : Bases de Donnees Relationnelles, C : Structure de Donnees en C, ThG : Theorie des Graphes, RI : Reseaux Informatiques.");
                printf("\nEntrez le module pour afficher les trois meilleurs (AO, BD, C, ThG, RI) : ");
                scanf("%s", valeur);
                TroisMeilleursParModule(listeEtudiants, valeur);
                break;
            case 7:
                printf("---- AFFICHAGE LES TROIS MEILLEURS EN MOYENNE GENERALE ----\n");
                TroisMeilleursEnMoyenne(listeEtudiants);
                break;
            case 8:
                printf("---- RAPPORT ACADEMIQUE ----\n");
                GenererRapport(listeEtudiants, "rapport.txt");
                break;
                printf("Merci d'avoir utilise le programme. Au revoir !\n");
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    sauvegarderEtudiants(listeEtudiants, "etudiants.txt");
    }while (choix !=0);

}

int main() {
    menu();
    return 0;
}

/* La complexité totale de ce code est:----> O(n^2)
* Les opérations plus complexes, comme "MeilleurParModule" ou "TroisMeilleursEnMoyenne", ont une complexité quadratique (O(n^2)),
* car elles impliquent plusieurs parcours et comparaisons Tri par insertion.

/* J'ai choisi des listes simplement chaînées dans mon projet. Voici quelques justifications pour appuyer ce choix :
   1-Dynamisme : Contrairement aux tableaux, les listes chainees permettent d'ajouter ou de supprimer des etudiants sans avoir a redimensionner la structure, ce qui est particulierement utile lorsque le nombre d'etudiants peut varier.

   2-Utilisation efficace de la memoire : Les listes chainees n'ont pas besoin d'un bloc contigu de memoire, ce qui permet une meilleure utilisation de la memoire, surtout lorsque les donnees sont dispersees.

   3-Insertion et suppression rapides : Les operations d'insertion et de suppression d'etudiants dans une liste chainee sont generalement plus rapides que dans un tableau, car elles ne necessitent pas de decalage des elements.

   4-Facilite d'extension : Il est facile d'etendre une liste chainee en ajoutant de nouveaux noeuds, ce qui est ideal pour des applications ou la taille des donnees n'est pas fixe.

   5-Acces sequentiel : Les listes chainees permettent un acces sequentiel aux elements, ce qui est suffisant pour de nombreuses applications, comme le traitement des donnees d'etudiants. */

/* Role des listes chainees dans le code :
    1-Stockage dynamique des donnees : Dans le code fourni, les listes chainees sont utilisees pour stocker dynamiquement les informations des etudiants. Chaque etudiant est represente par un noeud dans la liste, ce qui permet de gerer facilement un nombre variable d'etudiants.

    2-Facilite de gestion des etudiants : Les fonctions sauvegarderEtudiants et chargerEtudiants exploitent la structure de la liste chainee pour parcourir et manipuler les donnees des etudiants. Cela permet de lire et d'ecrire les informations de maniere efficace.

    3-Maintien de l'ordre : Les listes chainees conservent l'ordre d'insertion des etudiants, ce qui est essentiel pour certaines operations, comme le tri ou l'affichage des resultats.*/