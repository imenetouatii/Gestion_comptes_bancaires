#ifndef bib_H
#define bib_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/*---------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------- Déclaration des structures----------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------- PARTIE I ---------------------------------------------------------*/
#define MAX 1000

typedef struct Ccp{
    long long int num_ccp;
    float solde ;
    int efface;
}Ccp;

typedef struct Bloc{
    Ccp compte[MAX];
    int nb;
}Bloc;

typedef struct Entete{
    int nb_bloc;
    int nb_insere;
}Entete;

typedef struct TOF{
    FILE* f;
    struct Entete entete;
}TOF;

/*---------------------------------------------------------------------------------------------------------------*/
    Bloc buffer;
/*---------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------*/
/*------------------------------------ Déclaration des fonctions et procédures ----------------------------------*/
/*---------------------------------------------------------------------------------------------------------------*/

//machine abstraite :
int ouvrir(TOF **f,char *chemin,char mode);
void fermer(TOF *f);
void lireDir(TOF *f,int N_Bloc,Bloc *buffer);
void ecrireDir(TOF *f,int N_Bloc,Bloc *buffer);
int entete(TOF *f,int i);
void aff_entete(TOF *f, int i, int val);
int alloc_bloc(TOF *f);

//Procedures et Fonctions du tp :
void charge_initial(TOF *f, int n, float limit);
long dicho( TOF* f,long long int val, int *trouv, long *i, int *j );
void montant_ajouter(TOF* f);
char* extraire_mot(char* str,int position);
void ajouter_virement(TOF* Test);
void parcours(TOF *f);


/*---------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------- MACHINE ABSTRAITE----------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------*/

// Fonction d'ouverture d'un fichier
int ouvrir(TOF **f,char *chemin,char mode)
{
    *f = malloc(sizeof(TOF));
    char s[3];

    if((mode == 'A') || (mode == 'a')) sprintf(s,"rb+");
    else if ((mode == 'N') || (mode == 'n')) sprintf(s,"wb+");
    else return 0;

    (*f)->f = fopen(chemin, s);
    if((*f)->f == NULL)   return 0;

    if((mode == 'A') || (mode == 'a'))
    {
        fread(&((*f)->entete), sizeof(Entete), 1, (*f)->f);
    }
    else if ((mode == 'N') || (mode == 'n'))
    {
        (*f)->entete.nb_bloc = 0;
        (*f)->entete.nb_insere = 0;
    }
    return 1;
}

/*--------------------------------------------------------------------------------------------------------------------------*/

// Fonction de fermeture d'un fichier
void fermer(TOF *f)
{
    //Sauvegarde de l'entete
    rewind(f->f);
    fwrite(&(f->entete), sizeof(Entete), 1, f->f);
    fclose(f->f);
    free(f);
}
/*---------------------------------------------------------------------------------------------------------------------------*/

// Fonction de lecture d'un bloc
void lireDir(TOF *f,int N_Bloc,Bloc *buffer)
{
    if(N_Bloc <= (f->entete).nb_bloc)
    {
        fseek(f->f, sizeof(Entete) + (N_Bloc-1) * sizeof(Bloc),SEEK_SET);
        fread(buffer, 1, sizeof(Bloc), f->f);
    }
}
/*---------------------------------------------------------------------------------------------------------------------------*/


//Fonction d'ecriture d'un bloc
void ecrireDir(TOF *f,int N_Bloc,Bloc *buffer)
{
        fseek(f->f, sizeof(Entete) + (N_Bloc-1) * sizeof(Bloc),SEEK_SET);
        fwrite(buffer, 1, sizeof(Bloc), f->f);
}

/*--------------------------------------------------------------*/

// Fonction qui renvoit le contenu de l'entete
int entete(TOF *f,int i)
{
    if(i == 1) return (f->entete).nb_bloc;
    else if(i == 2) return (f->entete).nb_insere;
    else return -1;
}
/*--------------------------------------------------------------*/

// Fonction d'affectation d'une valeur a l'entete
void aff_entete(TOF *f, int i, int val)
{
    if(i == 1) (f->entete).nb_bloc = val;
    else if(i == 2) (f->entete).nb_insere = val;
}
/*--------------------------------------------------------------*/

// Fonction d'allocation d'un bloc
int alloc_bloc(TOF *f)
{
    aff_entete(f,1,entete(f,1)+1);
    return entete(f,1);
}


/*---------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------- Modules du TP -----------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------*/


// Chargement intial du fichier CCP_COMPTE.bin
void charge_initial(TOF *f, int n, float limit)
{
    Bloc buffer;
    Ccp ccp_temp;
    int j = 0, i = 1;
    ccp_temp.num_ccp = 000000111111;
    ccp_temp.solde = -1000,00;
    srand(time(0));

    for (int k = 0; k < n; k++){
        if(j <= MAX*limit)
        {
            buffer.compte[j] = ccp_temp;
            j++;
        }

        else
        {
            buffer.nb = j-1;
            ecrireDir(f,i,&buffer);
            buffer.compte[0] = ccp_temp;
            i++;
            j = 1;
        }
        ccp_temp.num_ccp += rand() % 1000;
        ccp_temp.solde = (rand() % 999999 - 1000) * 0.86;
    }
    buffer.nb = j+1;
    ecrireDir(f,i,&buffer);
    aff_entete(f,1,i);
    aff_entete(f,2,n);
    printf("\n\n\n                                       %c%c%c%c  LE FICHIER A ETE CREE AVEC SUCCES  %c%c%c%c",16,16,16,16,17,17,17,17);
    printf("\n");
    printf("\nLe nombre d'enregistrements crees est : %d ",n);
    printf("\nLe nombre de blocs crees est : %d \n\n",entete(f,1));
}

/*--------------------------------------------------------------*/


// Recherche dichotomique
long dicho( TOF* f,long long int val, int *trouv, long *i, int *j )
{
   Bloc buf;
   long bi, bs, cpt; // bf : borne inferieure, bs : borne superieure
   int stop, inf, sup;

   bi = 1;
   bs = entete(f,1);
   *trouv = 0;
   stop = 0;
   cpt = 0; // compteur de lectures physiques

   while ( bi <= bs && !*trouv && !stop )
    {
	*i = (bi + bs) / 2;		// le milieu entre bi et bs
	lireDir( f, *i, &buf ); cpt++; 	// lecture du bloc du milieu
	if ( val < buf.compte[0].num_ccp )
	   bs = *i - 1;		// la recherche continue dans la premiere moitie
	else
	   if ( val > buf.compte[ buf.nb-1 ].num_ccp )
	      	bi = *i + 1;	// la recherche continue dans la seconde moitie
	   else
	   {
		stop = 1;	// recherche interne dans buff (bloc du milieu)
	    inf = 0;
		sup = buf.nb-1;
		while ( inf <= sup && !*trouv ) {
		   *j = (inf + sup) / 2;
		   if ( val == buf.compte[*j].num_ccp ) *trouv = 1;
		   else
			if ( val < buf.compte[*j].num_ccp )
			   sup = *j - 1;
			else
			   inf = *j + 1;
	   	} // while interne
		if ( inf > sup ) *j = inf;
	   }
   } // while externe
   if ( bi > bs ) {
	*i = bi;
	*j = 0;
   }
   return cpt;
} // dicho

/*--------------------------------------------------------------*/

//Creation du fichier virements
void montant_ajouter(TOF* f)
{
    FILE* file = fopen("virements.txt","w");
    int nombre_bloc = entete(f,1);
    Bloc Buffer;
    srand(0);
    for(int i = 1; i < nombre_bloc; i++)
        {
        lireDir(f,i,&Buffer);
        for(int j = 0 ; j < Buffer.nb ; j++)
            {
            if( rand()%100 > 50)
            {
            fprintf(file,"%llu %0.2f\n", Buffer.compte[j].num_ccp,(float)(rand() % 99999)/3);
            }
            }
        }
    fclose(file);
}

/*--------------------------------------------------------------*/

// Fonction qui extrait un mot
char* extraire_mot(char* str,int position)
{
   if(position > strlen(str)) return NULL;
  // const char s[2] = "";
   char *token;
   /* get the first token */
   token = strtok(str, " ");
   int j;
   for(j = 0; j < position-1;j++){
      token = strtok(NULL," ");
   }
   return token;
}

/*--------------------------------------------------------------*/

// Procedure qui fait le virement du fichier texte vers le fichier binaire
void ajouter_virement(TOF* f)
{
    FILE* fvir = NULL;  //Fichier qui contient les virements
    Bloc buffer;
    fvir = fopen("virements.txt","r");
    char ligne[256],ligne2[256];
    float solde;
    long long int ccp;
    int j,trouv;
    long i;

    while(fgets(ligne,256,fvir))
    {
        strcpy(ligne2,ligne);
        ccp = atoll(extraire_mot(ligne,1));
        dicho(f,ccp,&trouv,&i,&j);
        if(trouv != 0){
            lireDir(f,i,&buffer);
            solde = (float)atof(extraire_mot(ligne2,2));
            buffer.compte[j].solde += solde;
            ecrireDir(f,j,&buffer);
        }
    }

    fclose(fvir);
}

void afficher(TOF *f, int n)
{
   long i;
   int j;
   Bloc buf;

    printf("\nLe contenu apres la reorganisation:\n");

    for (i=1;i<=(buf.nb);i++)
    {
        lireDir(f,i,&buf);
        printf(" [ ");
        for (j=0;j<n;j++)
        {
            printf(" %d ",buf.compte[j]);
        }
        printf(" ]");
    }
}


#endif


