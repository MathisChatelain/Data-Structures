#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

struct Fleur{ /* TAD des fleur*/
  char nom[20];
  int  numero;
};

void ajoutFleur(void){ /* Ajout de fleur au fichier data.txt */
  int petales = 0;

  char nom[20];
  printf("\nQuel est le nom de la fleur à ajouter ?");
  scanf("%s", nom);

  int c;
  printf("Combien de pétales ?");
  scanf("%i", &c);
  petales += c;

  char epines[3];
  printf("Est elle épineuse ?");
  scanf("%s", epines);

  FILE * fp;
  fp = fopen("data.txt", "a");
    if (fp == NULL)
        exit(EXIT_FAILURE);
  
  fprintf(fp,"\n%s,%i,%s",nom,petales,epines);

  fclose(fp);
}

void affichage(void) /* Affiche le contenu du fichier data.txt */
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("data.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) { 
        printf("%s", line);
    }
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}

void insertionFleur(void) /*Fonctionne mais mal implementé simplifiable*/
{
    int id = 1;
    int pos = 1;
    printf("A quelle ligne insérer la fleur ?");
    scanf("%i",&id);

    FILE * fp;
    FILE * fcopy;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("data.txt", "r");
    fcopy = fopen("data_insertion.txt","w");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        if (pos == id){
          int petales = 0;

          char nom[20];
          printf("\nQuel est le nom de la fleur à ajouter ?");
          scanf("%s", nom);

          int c;
          printf("Combien de pétales ?");
          scanf("%i", &c);
          petales += c;

          char epines[3];
          printf("Est elle épineuse ?");
          scanf("%s", epines);

          fprintf(fcopy,"%s,%i,%s\n",nom,petales,epines);
        }
        fprintf(fcopy,"%s",line);
        pos += 1; 
    }
    fprintf(fp,"%s",line);
    fclose(fp);
    fclose(fcopy);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
    
}

void affichageLigneSeule(void)
{
    int ligneaff = 0;
    int p = 1;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("data.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int k;
    printf("Quelle ligne voulez vous afficher ?");
    scanf("%i", &k);
    ligneaff += k;

    while ((read = getline(&line, &len, fp)) != -1) { 
      if (p == ligneaff)
        printf("%s", line);
      p += 1;
    }
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}

int main(void) /* Affichage du fichier puis édition */
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int exe ;
  
    fp = fopen("data.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int k;
    while (exe != 0){
      printf("\nQue voulez vous faire (entrer un nombre) ?\n");
      printf("0)Fin d'édition\n1)Affichage global\n2)Ajouter une fleur\n");
      printf("3)Affichage par indice\n4)Insertion nouvelle fleur\n");
      scanf("%i", &k);

      if ((k != 1)&&(k != 2)&&(k!=0)&&(k!=3)&&(k!=4)){ /* gestion des erreurs */
        k = 0;
      }
      if (k == 1){
        affichage();
      }
      if (k == 2){
        ajoutFleur();
      }
      if (k == 3){
        affichageLigneSeule();
      }
      if (k == 4){
        insertionFleur();
      }

      exe = k;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}




