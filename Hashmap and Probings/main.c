#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int lentab = 1000000;
char * tableHachage[lentab] = {0};
char * tableHProbing[lentab] = {0};
char * tableHProbQuad[lentab] = {0};
char * tableDoubleH[lentab] = {0};
char test[100] = "ZOEADAMS";
char lettresH1[27] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char lettresH2[27] = " AZERTYUIOPQSDFGHJKLMWXCVBN";


long int Code(char c,char lettres[27]){
  long int valren = 0;
  long int k = 0;

  while(k<=26){
    if(lettres[k]==c){valren = k;}
    k++;
  }
  return valren;
}

long int CodeMot(char mot[100],char lettres[27]){
  long int valren = 0;
  long int i = 1;
  long int exp = 0;
  long int idmax = strlen(mot);

  while(i<=idmax){
    exp = round(pow(26,i-1));
    valren += Code(mot[i-1],lettres)*exp;
    i++;
  }
  return valren;
}

long int hachage(char mot[100]){
  long int valren = 0;
  valren = CodeMot(mot,lettresH1)%lentab; /*% pour modulo*/
  return valren;
}

long int hachage2(char mot[100]){
  long int valren = 0;
  valren = CodeMot(mot,lettresH2)%lentab; /*% pour modulo*/
  return valren;
}

long int nbvaleursTable(char * table[]){
  long int valren = 0;
  int k = 0;
  while(k <= lentab){
    if (table[k] != NULL){valren ++;}
    k++;
  }
  return valren;
}

int RemplissageTable(void){
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  fp = fopen("passagers.txt", "r");
  long int h = 0;
  long int nbcollisions = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    h = hachage(line);
    if(h<0){h = h*(-1);}
    if(tableHachage[h] != NULL){nbcollisions++;}
    tableHachage[h] = strdup(line);
  }
  fclose(fp);
  printf("Number of collisions : %li\n",nbcollisions);
  return 0;
}

int RemplissageTableProbing(void){
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  fp = fopen("passagers.txt", "r");
  long int h = 0;
  long int i = 0;
  long int nbcollisions = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    i = 0;
    h = hachage(line);
    if(h<0){h = h*(-1);}
    while(tableHProbing[h+i] != NULL){
      nbcollisions++;
      i++;
      }
    tableHProbing[h+i] = strdup(line);
  }
  fclose(fp);
  printf("Number of collisions : %li\n",nbcollisions);
  return 0;
}

int RemplissageTableProbingQuadratique(void){
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  fp = fopen("passagers.txt", "r");
  long int h = 0;long int i = 0;long int k = 0;long int exp = 0;
  long int nbcollisions = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    i = 0;
    exp = 0;
    k=3;
    h = hachage(line);
    if(h<0){h = -h;}
    while(tableHProbQuad[h+exp] != NULL){
      nbcollisions++;
      if(i==1){exp = 1;}
      i++;
      exp = exp*3;
      if(h+exp>=lentab){h=k;exp=0;i=0;k+=2;}/*paire si trop grand*/
      }
    tableHProbQuad[h+exp] = strdup(line);
  }
  fclose(fp);
  printf("Number of collisions : %li\n",nbcollisions);
  return 0;
}

int RemplissageDoubleH(void){
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  fp = fopen("passagers.txt", "r");
  long int h = 0;
  long int h2 = 0;
  long int i = 0;
  long int tot = 0;
  long int nbcollisions = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    i = 0;
    h = hachage(line);
    h2 = floor(hachage2(line)/(lentab/10));
    if(h<0){h = -h;}
    if(h2<0){h2 = -h2;}
    //if(tot>=lentab){h=0;}//
    while(tableDoubleH[tot] != NULL){
      if(h2==0){h2=1;}
      nbcollisions++;
      i++;
      tot = h+(i*h2);
      }
    tableDoubleH[tot] = strdup(line);
  }
  fclose(fp);
  printf("Number of collisions : %li\n",nbcollisions);
  return 0;
}

int agglo(char * table[]){
  long int agg[10] = {0,0,0,0,0,0,0,0,0,0};
  int k = 0;
  int id = 0;
  float arrondi = 0;
  while(k <= lentab){
    arrondi = k;
    if(table[k]!=NULL){
      arrondi = arrondi/(lentab/10) ;
      id = floor(arrondi);
      agg[id]++;
    }
    k++;
  }
  printf("Decilian partition :\n");
  for (k = 0; k < 10; k++){printf("%li ", agg[k]);}
  printf("\n");
  return 0;
}

int main(void) {
  //Partie a)//
  printf("a)\nWord : %s\n",test);
  printf("Code(Word) : %li\n",CodeMot(test,lettresH1));
  printf("Hash(Word) : %li\n\nb)\n",hachage(test));
  //Partie b)//
  printf("-Reading : passagers.txt\n");
  printf("-Filling (without linear probing)\n");
  RemplissageTable();
  agglo(tableHachage);
  printf("Number of unique values in the table : %li/100000\n\nc)\n",nbvaleursTable(tableHachage));
  //Partie c)//
  printf("-Reading : passagers.txt\n");
  printf("-Filling (linear probing)\n");
  RemplissageTableProbing();
  agglo(tableHProbing);
  printf("Number of unique values in the table : %li/100000\n\nd)\n",nbvaleursTable(tableHProbing));
  //Partie d)//
  printf("-Reading : passagers.txt\n");
  printf("-Filling (quadratic probing)\n");
  RemplissageTableProbingQuadratique();
  agglo(tableHProbQuad);
  printf("Number of unique values in the table : %li/100000\n\ne)\n",nbvaleursTable(tableHProbQuad));
  //Partie e)//
  printf("-Reading : passagers.txt\n");
  printf("-Filling (double Hash)\n");
  RemplissageDoubleH();
  agglo(tableDoubleH);
  printf("Number of unique values in the table : %li/100000\n",nbvaleursTable(tableDoubleH));

  return 0;
}