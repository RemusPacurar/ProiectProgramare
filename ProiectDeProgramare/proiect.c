#include "proiect.h"

 char nume_utilizator[50];
 char prenume_utilizator[50];


 char carti[100][100];
 char autori[100][100];
 int exemplare_disponibile[100];
 int numar_carti = 0;

 char carti_imprumutate[10][100][100];
 char autori_imprumutate[10][100][100];
 int exemplare_imprumutate[10][100];
 int numar_imprumut = 0;

void trim(char *str);

void citire_fisier(int argc, char **argv)
{
    if (argc == 3) {
        strcpy(nume_utilizator, argv[1]);
        strcpy(prenume_utilizator, argv[2]);
    }
    else
    {
        printf("Introduceti numele si prenumele dumneavoastra: ");
        scanf("%s %s", nume_utilizator, prenume_utilizator);

    }


    // Copy the first name and last name from command-line arguments
    //strcpy(nume_utilizator, argv[1]);
    //strcpy(prenume_utilizator, argv[2]);

    // File handling and other initializations
    FILE *carti_file = fopen("carti.txt", "r");
    if (carti_file == NULL) {
        printf("Eroare la deschiderea fisierului 'carti.txt'.\n");
    }

    FILE *imprumuturi_file = fopen("imprumuturi.txt", "r");
    if (imprumuturi_file == NULL) {
        printf("Eroare la deschiderea fisierului 'imprumuturi.txt'.\n");
    }


    char line[256];
    while (fgets(line, sizeof(line), carti_file)) {
        char *titlu = strtok(line, ",");
        char *autor = strtok(NULL, ",");
        char *exemplare = strtok(NULL, ".");
        if (titlu != NULL && autor != NULL && exemplare != NULL) {
            char *end;
            while (isspace(*titlu)) titlu++;
            end = titlu + strlen(titlu) - 1;
            while (end > titlu && isspace(*end)) end--;
            *(end + 1) = '\0';

            while (isspace(*autor)) autor++;
            end = autor + strlen(autor) - 1;
            while (end > autor && isspace(*end)) end--;
            *(end + 1) = '\0';

            int exemplare_val = atoi(exemplare);

            strcpy(carti[numar_carti], titlu);
            strcpy(autori[numar_carti], autor);
            exemplare_disponibile[numar_carti] = exemplare_val;

            numar_carti++;
        }
    }

    while (fgets(carti_imprumutate[numar_imprumut][0], 100, imprumuturi_file) != NULL) {
        trim(carti_imprumutate[numar_imprumut][0]);
        fgets(autori_imprumutate[numar_imprumut][0], 100, imprumuturi_file);
        trim(autori_imprumutate[numar_imprumut][0]);
        fscanf(imprumuturi_file, "%d\n", &exemplare_imprumutate[numar_imprumut][0]);
        numar_imprumut++;
    }

    fclose(carti_file);
    fclose(imprumuturi_file);

}
void afiseaza_meniu() {

    printf("\nMeniu:\n");
    printf("1. Imprumuta carti\n");
    printf("2. Restituie/Doneaza carti\n");
    printf("3. Vizualizeaza cartile imprumutate\n");
    printf("4. Vizualizeaza carti disponibile in biblioteca\n");
    printf("5. Cauta carti\n");
    printf("6. Iesire\n");
}

void trim(char *str) {
    int start = 0, end = strlen(str) - 1;
    while (isspace(str[start])) start++;
    while ((end >= start) && isspace(str[end])) end--;
    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
}

void imprumuta_carte() {
    system("cls"); // Curăță ecranul consolei
    char titlu[100];
    char autor[100];
    int numar_exemplare;

    printf("Introduceti titlul cartii: ");
    scanf(" %[^\n]", titlu);
    trim(titlu);
    printf("Introduceti autorul cartii: ");
    scanf(" %[^\n]", autor);
    trim(autor);
    printf("Introduceti numarul de exemplare dorit: ");
    scanf("%d", &numar_exemplare);

    for (int i = 0; i < numar_carti; i++) {
        if (strcmp(carti[i], titlu) == 0 && strcmp(autori[i], autor) == 0) {
            if (exemplare_disponibile[i] >= numar_exemplare) {
                strcpy(carti_imprumutate[numar_imprumut][0], carti[i]);
                strcpy(autori_imprumutate[numar_imprumut][0], autori[i]);
                exemplare_imprumutate[numar_imprumut][0] = numar_exemplare;
                exemplare_disponibile[i] -= numar_exemplare;
                numar_imprumut++;
                printf("Cartea '%s' a fost imprumutata cu succes.\n", titlu);
            } else {
                printf("Nu sunt suficiente exemplare disponibile pentru '%s'.\n", titlu);
            }
            return;
        }
    }
    printf("Cartea '%s' de catre '%s' nu a fost gasita in biblioteca.\n", titlu, autor);
}



void restituie_carte() {
    system("cls"); // Curăță ecranul consolei
    int optiune;
    printf("1. Restituie cartea imprumutata\n");
    printf("2. Doneaza o carte catre biblioteca\n");
    printf("Introduceti optiunea dorita: ");
    scanf("%d", &optiune);

    switch (optiune) {
        case 1:
            {
                int index_imprumut;
                printf("Introduceti indexul de imprumut pentru restituire: ");
                scanf("%d", &index_imprumut);

                if (index_imprumut >= 0 && index_imprumut < numar_imprumut) {
                    for (int i = 0; i < numar_carti; i++) {
                        if (strcmp(carti[i], carti_imprumutate[index_imprumut][0]) == 0 && strcmp(autori[i], autori_imprumutate[index_imprumut][0]) == 0) {
                            exemplare_disponibile[i] += exemplare_imprumutate[index_imprumut][0];
                            break;
                        }
                    }
                    for (int i = index_imprumut; i < numar_imprumut - 1; i++) {
                        strcpy(carti_imprumutate[i][0], carti_imprumutate[i + 1][0]);
                        strcpy(autori_imprumutate[i][0], autori_imprumutate[i + 1][0]);
                        exemplare_imprumutate[i][0] = exemplare_imprumutate[i + 1][0];
                    }
                    numar_imprumut--;
                    printf("Restituire efectuata cu succes.\n");
                } else {
                    printf("Indexul de imprumut este invalid.\n");
                }
            }
            break;
        case 2:
            // Implementarea funcției de donare este inclusă aici
            {
                system("cls"); // Curăță ecranul consolei
                char titlu[100];
                char autor[100];
                int numar_exemplare;

                printf("Introduceti titlul cartii: ");
                scanf(" %[^\n]", titlu);
                trim(titlu);
                printf("Introduceti autorul cartii: ");
                scanf(" %[^\n]", autor);
                trim(autor);
                printf("Introduceti numarul de exemplare donat: ");
                scanf("%d", &numar_exemplare);

                FILE *carti_file = fopen("carti.txt", "a");
                if (carti_file == NULL) {
                    printf("Eroare la deschiderea fisierului 'carti.txt' pentru adaugare carti donate.\n");
                    return;
                }

                fprintf(carti_file, "%s, %s, %d.\n", titlu, autor, numar_exemplare);
                fclose(carti_file);

                printf("Cartea '%s' a fost donata cu succes.\n", titlu);
            }
            break;
        default:
            printf("Optiune invalida.\n");
    }
}



void afiseaza_carti_imprumutate() {
    system("cls"); // Curăță ecranul consolei
    printf("Cartile imprumutate de %s %s:\n", nume_utilizator, prenume_utilizator);
    for (int i = 1; i < numar_imprumut; i++) {
        printf("Imprumutul %d:\n", i);
        for (int j = 0; j < numar_carti; j++) {
            if (exemplare_imprumutate[i][j] > 0) {
                printf("- %s de catre %s (%d exemplare)\n", carti_imprumutate[i][j], autori_imprumutate[i][j], exemplare_imprumutate[i][j]);
            }
        }
    }
}

void afiseaza_carti_disponibile() {
    system("cls"); // Curăță ecranul consolei
    printf("Carti disponibile in biblioteca:\n");
    for (int i = 0; i < numar_carti; i++) {
        printf("- %s de catre %s (%d exemplare)\n", carti[i], autori[i], exemplare_disponibile[i]);
    }
}

void cauta_carte() {
    system("cls"); // Curăță ecranul consolei
    char cautare[100 + 100];
    int carte_existenta = 0; // Inițializăm variabila carte_existenta la 0

    printf("Introduceti (titlul) sau (autorul) sau (titlul,autorul) cautat: ");
    scanf(" %[^\n]", cautare);


    char *titlu = strtok(cautare, ",");
    char *autor = strtok(NULL, ",");

    if (autor == NULL) {
        // Cautare doar dupa titlu
        printf("Rezultatele cautarii pentru '%s':\n", titlu);
        for (int i = 0; i < numar_carti; i++) {
            if (strstr(carti[i], titlu) != NULL || strstr(autori[i], titlu) != NULL) {
                printf("- %s de catre %s (%d exemplare)\n", carti[i], autori[i], exemplare_disponibile[i]);
                carte_existenta = 1;
            }
        }
    } else {
        // Cautare dupa titlu si autor
        printf("Rezultatele cautarii pentru '%s' de catre '%s':\n", titlu, autor);
        for (int i = 0; i < numar_carti; i++) {
            if (strstr(carti[i], titlu) != NULL && strstr(autori[i], autor) != NULL) {
                printf("- %s de catre %s (%d exemplare)\n", carti[i], autori[i], exemplare_disponibile[i]);
                carte_existenta = 1;
            }
        }
    }

    if (carte_existenta == 0) {
        printf("Nu exista cartea cautata.\n");
    }
}




