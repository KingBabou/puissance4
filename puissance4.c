#include <stdio.h>
#include <stdlib.h>

#define NBLARGEUR 7
#define NBHAUTEUR 7

#define couleur(param) printf("\033[%dm", param);
//30 Noir -- 31 Rouge -- 32 Vert -- 33 Jaune -- 34 Bleu -- 35 Magenta -- 36 Cyan -- 37 Blanc

void init (char t[NBLARGEUR][NBHAUTEUR]) {
	int i, j;
	for (i = 0; i < NBLARGEUR; i++) {
		for (j = 0; j < NBHAUTEUR; j++) {
			t[i][j] = '*';
		}
	}
}

void afficher(char t[NBLARGEUR][NBHAUTEUR]) {
	int i, j;
	printf(" --------------------- \n");
	for (i = 0; i < NBLARGEUR; i++) {
		printf("|");
		for (j = 0; j < NBHAUTEUR; j++) {
			if (t[i][j] == 'O') {
				couleur(33);
			} else if (t[i][j] == 'X') {
				couleur(31);
			} else {
				couleur(37);
			}
			printf(" %c ", t[i][j]);
			couleur(37);
			if (j == NBHAUTEUR-1) printf("|\n");
		}
	}
	printf(" --------------------- \n");
	printf("  1  2  3  4  5  6  7  \n");
}

int ajouter(char t[NBLARGEUR][NBHAUTEUR], int c, char j) {
	int i;
	int depassement = 1;
	for (i = NBLARGEUR-1; i >= 0; i--) {
		if (t[i][c] == '*') {
			t[i][c] = j;
			depassement = 0;
			break;
		}
	}
	return depassement;
}

int verification(char t[NBLARGEUR][NBHAUTEUR], char c) {
	int i, j;
	int g = (c == 'O') ? 1 : 2;
	for (i = 0; i < NBLARGEUR; i++) {
		for (j = 0; j < NBHAUTEUR; j++) {
			if (i+3 < NBLARGEUR && t[i][j] == c && t[i+1][j] == c && t[i+2][j] == c && t[i+3][j] == c) return g;
			if (j+3 < NBHAUTEUR && t[i][j] == c && t[i][j+1] == c && t[i][j+2] == c && t[i][j+3] == c) return g;
			if (i-3 >= 0 && j+3 < NBHAUTEUR && t[i][j] == c && t[i-1][j+1] == c && t[i-2][j+2] == c && t[i-3][j+3] == c) return g;
			if (i+3 < NBLARGEUR && j+3 < NBHAUTEUR && t[i][j] == c && t[i+1][j+1] == c && t[i+2][j+2] == c && t[i+3][j+3] == c) return g;
		}
	}
	return 0;
}

int main() {

	char tableau[NBLARGEUR][NBHAUTEUR];

	char joueur;
	char* choix = malloc(sizeof(char));
	int quitte = 0, depassement, i, colonne;
	int score1 = 0, score2 = 0, gagnant = -1, coups = 0;
	
	while (!quitte) {
		if (gagnant != 0) {
			if (score1 == 0 && score2 == 0) joueur = 'O';
			else if (gagnant == 1) joueur = 'X';
			else if (gagnant == 2) joueur = 'O';
			gagnant = 0;
			init(tableau);
			afficher(tableau);
		} else {
			if (!depassement) joueur = (joueur == 'O') ? 'X' : 'O';
		}
		printf("Choisir une colonne : ");
		scanf("%s", choix);
		while (choix[0] < 49 || choix[0] > 55) {
			printf("Choisir une colonne : ");
			scanf("%s", choix);
		}
		colonne = choix[0] - 48;
		depassement = ajouter(tableau, colonne-1, joueur);
		if (!depassement) coups++;
		afficher(tableau);
		gagnant = verification(tableau, joueur);
		if (gagnant != 0) {
			if (gagnant == 1) score1++;
			else if (gagnant == 2) score2++;
			printf("Score : ");
			couleur(33);
			printf("O ");
			couleur(37);
			printf("%d | %d", score1, score2);
			couleur(31)
			printf(" X\n");
			couleur(37);
			printf("Voulez vous relancez ? (oui / non)\n");
			char *reponse = malloc(sizeof(char)*10);
			scanf("%s", reponse);
			if (strcmp(reponse, "non") == 0) quitte = 1;
			else for (i = 0; i < 40; i++) printf("\n");
			free(reponse);
			coups = 0;
		}
		if (coups == NBLARGEUR * NBHAUTEUR) {
			printf("Match nul\n");
			printf("Score : ");
			couleur(33);
			printf("O ");
			couleur(37);
			printf("%d | %d", score1, score2);
			couleur(31)
			printf(" X\n");
			couleur(37);
			printf("Voulez vous relancez ? (oui / non)\n");
			char *reponse = malloc(sizeof(char)*10);
			scanf("%s", reponse);
			if (strcmp(reponse, "non") == 0) quitte = 1;
			else for (i = 0; i < 40; i++) printf("\n");
			free(reponse);
			coups = 0;
			gagnant = -1;
		}
	}
	free(choix);

}
