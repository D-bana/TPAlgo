#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000

/* P1-Q1
 * le nombre chromatique d'un graphe non orienté est le plus petit nombre de couleurs nécessaires pour colorer 
 * les sommets du graphe de telle sorte que deux sommets adjacents n'aient pas la même couleur. 
 * Le nombre chromatique dépend de la structure du graphe et peut être calculé pour des graphes particuliers, 
 * tels que les graphes complets, les graphes bipartis et les graphes réguliers. 
 * Un graphe dont le nombre chromatique est égal à la taille maximale d'une clique est appelé un graphe parfait, 
 * et un exemple de graphe parfait est le graphe de Turán.
 */

// Fonction qui colorie le graphe en utilisant une heuristique gloutonne
void color_graph(int **adjacency_matrix, int *vertices, int n) {
    int i, j, k, color;
    int colors[MAX_VERTICES];

    // Initialisation des couleurs des sommets à 0 (non colorié)
    for (i = 0; i < n; i++) {
        colors[i] = 0;
    }

    // Coloriage des sommets
    for (i = 0; i < n; i++) {
        // Détermination des couleurs déjà utilisées pour les voisins
        int used_colors[MAX_VERTICES] = {0};

        // Parcours des voisins du sommet i pour déterminer les couleurs déjà utilisées
        for (j = 0; j < n; j++) {
            if (adjacency_matrix[i][j] == 1 && colors[j] != 0) {
                used_colors[colors[j]] = 1;
            }
        }

        // Choix de la plus petite couleur disponible
        color = 1;
        while (used_colors[color]) {
            color++;
        }

        // Coloriage du sommet i
        colors[i] = color;
    }

    // Affichage des couleurs attribuées à chaque sommet
    for (i = 0; i < n; i++) {
        printf("Sommet %d colorié en %d\n", vertices[i], colors[i]);
    }
}

/*P1-Q3
 * Un graphe planaire est un graphe qui peut être dessiné sur un plan sans que ses arêtes ne se croisent.
 * Le théorème des quatre couleurs stipule que tout graphe planaire peut être colorié avec au plus 4 couleurs, mais il peut exister des graphes non planaires nécessitant plus de 4 couleurs pour être coloriés.
 */

int main() {
    return 0;
}
