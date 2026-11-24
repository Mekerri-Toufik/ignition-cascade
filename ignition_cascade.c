#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAILLE 8
#define TOURS_MAX 12
#define TOUR_QUARANTAINE 6

typedef enum {
    TERRAIN_NORMAL = 0,
    TERRAIN_ROCHER_INDESTRUCTIBLE, /* X */
    TERRAIN_ROCHER_EXPLOSIF,       /* E */
    TERRAIN_BRULE                  /* ~ */
} TypeTerrain;

typedef enum {
    PERSONNE = 0,
    JOUEUR_1,
    JOUEUR_2
} Proprietaire;

typedef enum {
    MECHE_NORMALE = 0,
    MECHE_ECLAIR,
    MECHE_ANCRE,
    MECHE_HUIT_CASES
} TypeMeche;

typedef struct {
    TypeTerrain terrain;
    Proprietaire proprietaire;
    TypeMeche type_meche;
    int timer;
    bool a_explose_ce_tour;
} Case;

typedef struct {
    int id;
    int score;
    bool joker_eclair_dispo;
    bool joker_ancre_dispo;
    bool joker_huit_dispo;
} Joueur;

typedef struct {
    Case grille[TAILLE][TAILLE];
    Joueur joueurs[2];
    int tour_actuel;
    int joueur_courant;
    int niveau_ia; /* 0 = 2 joueurs humains, 1..3 = IA */
} Partie;

/* Module A : Initialisation & Grille */
void initialiser_partie(Partie *p, int niveau_ia);
void placer_obstacles(Partie *p);
bool dans_grille(int lig, int col);
bool case_est_libre(const Partie *p, int lig, int col);
void afficher_grille(const Partie *p);

/* Module B : Pose & Quarantaine */
bool poser_pion(Partie *p, int lig, int col, int timer, TypeMeche type);
void appliquer_quarantaine(Partie *p);

/* Module C : Explosions par passes (sans FIFO) */
void preparer_explosions(Partie *p);
void propager_onde(Partie *p, int lig, int col, TypeMeche source);
void resoudre_explosions(Partie *p);
void calculer_scores(Partie *p);

/* Module D : IA */
void jouer_tour_ia(Partie *p);

int main(void) {
    Partie partie;
    initialiser_partie(&partie, 0);
    afficher_grille(&partie);
    return 0;
}
