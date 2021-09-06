#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int tailleSalle = 100;
int nbpersonne = 0;
int entree = 0;
int sortie = 0;
int stop =0;
int seed = 73460; /*A changer au bon vouloir permet de tester en restant aléatoire*/

int randintSalle(){ /*Donne un entier aléatoire de 0 à la taille de la salle*/
  int a = (int)(((float)rand())/RAND_MAX*tailleSalle+0);
  return a;
}

int main()
{
  srand(seed);

  printf("Au départ il y a %i personnes dans la salle d'attente\n",nbpersonne);

  while (stop == 0){

    sortie = randintSalle();
    while ((sortie>nbpersonne)&&(nbpersonne!=0)){
      sortie = randintSalle();
    }

    entree = randintSalle();
    while ((entree+nbpersonne>tailleSalle)&&(nbpersonne!=tailleSalle)){
      entree = randintSalle();
    }

    
    if (nbpersonne-sortie<=0){ 
      sortie = nbpersonne;
      nbpersonne = 0;
    }
    nbpersonne -= sortie;
    printf("\n%i personnes embarquées",sortie);

    nbpersonne += entree;
    printf("\n%i personnes voulant rentrer dans la salle d'attente",entree);
    if (nbpersonne>tailleSalle){ /*Cas surnombre en entree*/
      printf("%i Personnes n'ont pas pu rentrer\n",nbpersonne-tailleSalle);
      nbpersonne = tailleSalle;
    }


    if (nbpersonne==0){printf("La salle d'attente est vide\n");} /*Cas vide*/

    if (nbpersonne==tailleSalle){printf("La salle d'attente est pleine\n");} /*Cas plein*/

    if (nbpersonne>0){printf("\nTaux de remplissage de la salle: %i/%i\n",nbpersonne,tailleSalle);}

    printf("\nVoulez vous continuer ?(0 si oui/1 sinon)");
    scanf("%i", &stop);

    while ((stop!=0)&&(stop!=1)){
      printf("\nValeur invalide veuillez recommencer");
      scanf("%i", &stop);
    }
  }
  return 0;
}

