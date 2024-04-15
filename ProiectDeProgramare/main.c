/*Fiecare persoană poate împrumute mai multe cărți de la o bibliotecă. O persoană este identificată în
mod unic prin NUME și PRENUME. Fiecare carte este caracterizată prin:
- Titlu
- Autor
- Exemplare disponibile
Pentru fiecare împrumut se va genera o fișă de împrumut ce conține:
- Persoana care efectuează împrumutul
- Cărțile împrumutate:
o Titlul + Autorul cărții
o Numărul de exemplare împrumutate

Totodată, orice persoană poate VIZUALIZA toate împrumuturile realizate de ea, precum și ce cărți
există în bibliotecă și poate căuta o anumită carte după titlu sau autor. Persoana poate restitui cărțile
împrumutate sau adăuga cărți noi în bibliotecă (act de donație).
*/

#include "proiect.h"

int main(int argc, char **argv) {
    citire_fisier(argc,argv);
    int optiune;
    do {
        afiseaza_meniu();
        printf("\nIntroduceti optiunea dorita: ");
        scanf("%d", &optiune);

        switch (optiune) {
            case 1:
                imprumuta_carte();
                break;
            case 2:
                restituie_carte();
                break;
            case 3:
                afiseaza_carti_imprumutate();
                break;
            case 4:
                afiseaza_carti_disponibile();
;                break;
            case 5:
                cauta_carte();
                break;
            case 6:
                printf("La revedere!\n");
                break;
            default:
                printf("Optiune invalida. Va rugam incercati din nou.\n");
        }
    } while (optiune != 6);

    return 0;
}

