#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct aeroport{
  char * nom ;
  char * pays ;
  char * IATA ;
  int numSommet ;
  char * Liaisons;
  int idNoeudPrecedent; /*Emplacement dans tabAero*/
  int nbliaison ;
  int idNoeudsLiaisons[20];
  int parcouru ; /* 0 si non_parcouru 1 si parcouru*/
  int dcentre ;
};

struct aeroport tabAero[20];
int nbaero = 0;
int b = 0;

int LectureListeAeroport(void){
  
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read; 
   
  fp = fopen("aeroports.txt", "r");
  int num = 0;

  while ((read = getline(&line, &len, fp)) != -1) { 
    nbaero++;
    /*Réutilisation et adaptation du code donné en labo de programmation*/
    char *strEmpData = line;
    char *token;
    int i=0;
    char *strArr[3] = {0};
    char* strSplit = strEmpData;
  

    while ((token = strtok_r(strSplit , " ", &strSplit)))
      strArr[i++] = token;

    /*------------------------Fin de Réutilisation-----------------------*/
    tabAero[num].IATA = strdup(strArr[0]);
    tabAero[num].nom = strdup(strArr[1]);
    tabAero[num].pays = strdup(strArr[2]);
    tabAero[num].numSommet = num;
    tabAero[num].nbliaison = 0;
    tabAero[num].parcouru = 0;
    tabAero[num].dcentre = 999; /*On suppose qu'ils sont loin*/
    num ++;
    /*------------------------Fin d'adaptation---------------------------*/
  }
  fclose(fp);
  return 0;
}

int compteLiaisons(char * s){
  int valren = 0;
  int i = 0;
  if (s[0]){valren ++;}
  while ((s[i++]!='\n')&&(i<100)){ /*On compte le premier*/
    if (s[i] ==' '){valren += 1;};} /*On compte les espaces*/
  return valren;
}

int idParNom(char * nom){
  int i = 0;
  if(strcmp("",nom)!=0){
    while(strcmp(tabAero[i].nom,nom)!=0){i++;}
    /*strcmp compare des chaines de caracteres*/
  }
  return i;
}

int remplissageIdsLiaisons(char* chaine,int id){
  int n = 0;int m = 0;int k = 0;int i = 0; /*Compteurs*/
  char token[100] = "";
  int taille = strlen(chaine);
  
  while(n<=taille-1){
    if((chaine[n] ==' ')||(chaine[n] == '\0')){
      tabAero[id].idNoeudsLiaisons[k] = idParNom(token);
      k++;
      for(i=0;i<taille;i++){token[i] = '\0';}; /*token vide*/
      m=0;
      }
    else if(chaine[n] != '\0'){
      token[m]=chaine[n];
      m++;
      }
    n++;
  }
  for(i=0;i<strlen(token);i++){
    if(token[i] == '\n'){token[i-1]='\0';}
  }
  tabAero[id].idNoeudsLiaisons[k] = idParNom(token);
  token[0] = '\0';
  return 0;
}

int LectureListeLiaisons(){
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read; 
  int n = 0;
   
  fp = fopen("liaisons.txt", "r");
  int num = 0;

  while ((read = getline(&line, &len, fp)) != -1) { 
    tabAero[num].Liaisons = strdup(line);
    tabAero[num].nbliaison = compteLiaisons(line);
    remplissageIdsLiaisons(line,num);
    num++;
  }
  fclose(fp);
  return 0;
}

int affichage(int id){
  int i;
  int pos;
  printf("Noeud n°%i Aeroport de %s \n",id,tabAero[id].nom);
  printf("Vols disponibles vers : ");
  for(i=0;i<tabAero[id].nbliaison;){
    pos = tabAero[id].idNoeudsLiaisons[i];
    i++;
    if (tabAero[pos].parcouru == 0){
      printf("%s ",tabAero[pos].nom);
    }
  };
  printf("\n\n");
  return 0;
}

int visiterDFS(int id){ /*id = emplacement du noeud dans tabAero*/
  tabAero[id].parcouru = 1;
  int h = 0;
  affichage(id);
  while(h<tabAero[id].nbliaison){
    int idsuivant = tabAero[id].idNoeudsLiaisons[h];
    if(tabAero[idsuivant].parcouru == 0){ /*Si il n'est pas parcouru*/
      printf("vol : %s --> %s\n",tabAero[id].nom,tabAero[idsuivant].nom);
      visiterDFS(idsuivant);
    }
    h++;
  }
  return 0;
}

int visiterBFS(int id,int s){
  tabAero[id].parcouru = 1;
  tabAero[id].dcentre = s;
  int h = 0;
  while(h<tabAero[id].nbliaison){
    int idsuivant = tabAero[id].idNoeudsLiaisons[h];
    h++;
    if(tabAero[idsuivant].dcentre > tabAero[id].dcentre){
      visiterBFS(idsuivant,s+1);
    } 
  }
  return 0;
}

int parcoursDFS(int id){
  int nbaffichage = 0;
  int depth = 0;
  int n = 0;
  visiterBFS(id,0);
  while(depth<nbaero){
    if((tabAero[n].dcentre == depth)&&(n<nbaero-1)){
      affichage(n);
      tabAero[n].parcouru = 0;
      nbaffichage++;
    }
    n++;
    if(n>nbaero){depth++;n=0;}
  }
  
  return 0;
}

int main() {
  int f = 0;
  LectureListeAeroport();
  LectureListeLiaisons();
  printf("Situation initiale:\n-------(Exo 3.1)----------\n");
  while(b<nbaero){affichage(b);b++;}
  printf("---------(Exo 3.2 DFS)------------\n");
  visiterDFS(4);
  printf("---------(Exo 3.2 BFS)------------\n");
  while(f<=nbaero){
    tabAero[f].parcouru = 0;
    f++;
  }
  parcoursDFS(4);
  return 0;
}