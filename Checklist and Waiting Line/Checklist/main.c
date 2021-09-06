#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  fp = fopen("checklist.txt", "r");
  int conditionWin = 0;
  int conditionretour = 0;
  int nbelem = 0;
  int ligneDeRetour = 0;
  int ligneActuelle;
  int nbTacheCourante = 0;
  int minimumRetour =0;
  int check = 1 ;

  if (fp == NULL) 
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, fp)) != -1) {nbelem += 1;} /*Compte le nombre d'éléments*/

  fclose(fp);
  
  while (conditionWin == 0){
    ligneActuelle = 0;
    fp = fopen("checklist.txt", "r");
    conditionretour = 0;
    
    while (((read = getline(&line, &len, fp)) != -1)&&(conditionretour==0)) { /* Relecture Fichier */
      ligneActuelle += 1;
      ligneDeRetour = minimumRetour;
      if (ligneActuelle > ligneDeRetour){ /*On est retourné à la ligne voulue*/
        ligneDeRetour = minimumRetour;
        if (line[0] == 't'){ /* line est actuellement une tache*/
          
          nbTacheCourante += 1; /* Permet de compter les élements d'une sous catégorie */
          printf("\nEst ce que la %s  est valide ? (1 pour OK/0 pour NON)\n",line);
          scanf("%i", &check);
          
          if ((ligneActuelle == nbelem)&&(check==1)){conditionWin += 1;} /* réussite car la dernierre tache est valide*/

          while ((check!=0)&&(check!=1)){
            printf("\nValeur invalide veuillez recommencer");
            scanf("%i", &check);
          }
          
          if (check == 0){
            ligneDeRetour = ligneActuelle;
            nbTacheCourante = 0;
            conditionretour = 1;
          }
        }
      }
      if ((line[0] == 'c')&&(check==1)){printf("\n%s",line);}
      if ((line[0] == 's')&&(check==1)){
        minimumRetour = ligneActuelle;
        printf("\n%s",line);
      }
    }
    fclose(fp); /* Fermeture finale */
  };
  printf("\nLe check-up est terminé l'avion est à même de décoller.");
  return 0;
}

