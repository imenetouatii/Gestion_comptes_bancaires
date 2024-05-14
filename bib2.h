#ifndef bib2_H
#define bib2_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bib.h"

#define _MAX 1024

/*---------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------- Declaration des structures----------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------*/

typedef struct Bloc_lovc{
    char tab[_MAX];
    int suiv;
}Bloc_lovc;


typedef struct Entete_lovc{
    int nb;
    int head;
    int tail;
    int nb_enr;
}Entete_lovc;

typedef struct LOVC{
    FILE* f;
    struct Entete_lovc entete;
}LOVC;


/*--------------------------------------------- Variables Globales --------------------------------------------------------*/

Bloc_lovc _buffer;
int nb_lirdir=0;
int nb_ecrirdir=0;

/*---------------------------------------------------------------------------------------------------------------*/
/*------------------------------------ Declaration des fonctions et procedures ----------------------------------*/
/*---------------------------------------------------------------------------------------------------------------*/

//MACHINE ABSTRAITE
void liredir_lovc(LOVC *fichier, int i ,Bloc_lovc *buf);
void ecriredir_lovc(LOVC *fichier, int i,Bloc_lovc *buf);
void aff_entete_lovc(LOVC *fichier,int i , int valeur);
int entete_lovc(LOVC *fichier, int i);
LOVC *ouvrir_lovc(char nom_physique[], char mode);
void fermer_lovc(LOVC *fichier);
void  alloc_bloc_lovc(LOVC *fichier);

//MODULES DU TP
void concat(char result[],long long int cle, float solde);
void ecrire_chaine(LOVC *fichier,int n,  int *i, int *j, char chaine[],int *cpt, Bloc_lovc *buf);
void charge_values(TOF* f_tof, LOVC* f_lovc);
void get_enr(LOVC* file, int pos, char result[]);
void afficher_fichier(LOVC* file);
void get_elements(char result[], char taille[], char efface[], char ccp[], char solde[]);
void get_small_values(LOVC *file);
void get_big_values(LOVC *file);
void recuperer_chaine(LOVC *fichier,int n , int *i, int *j, char chaine[]);
void get_enr_pos(LOVC* file, int pos, char result[], int *posi, int *posj);
void supp_enr(LOVC* file, int i, int j);
void supprimer(LOVC* file, long long int cle);
LOVC* add_montant(LOVC* file);
LOVC* insert(LOVC* file, long long int ccp, float solde);
/*---------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------- MACHINE ABSTRAITE----------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------*/

//Lecture d'un bloc
void liredir_lovc(LOVC *fichier, int i ,Bloc_lovc *buf)
{
 fseek(fichier->f,sizeof(Entete_lovc)+sizeof(Bloc_lovc)*(i-1),SEEK_SET); // Positionnement au debut du bloc numero i
 fread(buf,1,sizeof(Bloc_lovc),fichier->f);       //Lecture d'un bloc de caractere correspondant a la taille du bloc dans le_buffer
 rewind(fichier->f);      // Repositionnement au debut du fichier
 nb_lirdir++;
}

/*--------------------------------------------------------------*/

//Ecriture d'un bloc
void ecriredir_lovc(LOVC *fichier, int i,Bloc_lovc *buf)
{
     fseek(fichier->f,sizeof(Entete_lovc)+sizeof(Bloc_lovc)*(i-1),SEEK_SET); // Positionnement au debut du bloc numero i
     fwrite(buf,1,sizeof(Bloc_lovc),fichier->f);  //Ecriture du contenu du_buffer dans le bloc numero i du fichier
     nb_ecrirdir++;
}

/*--------------------------------------------------------------*/

//Affectation d'une valeur aux elements de l'entete
void aff_entete_lovc(LOVC *fichier,int i , int valeur)
{
    switch(i)
    {
         case 1:
        { fichier->entete.nb=valeur; // Nombre total de blocs alloues dans le fichier
        } break;

         case 2:
        { fichier->entete.head=valeur;  // Numero du bloc representant la TETE du fichier
        } break;

         case 3:
        { fichier->entete.tail=valeur;  // Numero du bloc representant la QUEUE du fichier
        } break;

         case 4:
        { fichier->entete.nb_enr=valeur;  // numero du bloc representatnt la tete duf icheir
        } break;
    };
}

/*--------------------------------------------------------------*/

//Obtention des elements de l'entete
int entete_lovc(LOVC *fichier, int i)
{

    switch(i)
    {
        case 1:
        { return(fichier->entete.nb);
        } break;

         case 2:
        { return(fichier->entete.head);
        } break;

         case 3:
        { return(fichier->entete.tail);
        } break;

         case 4:
        { return(fichier->entete.nb_enr);
        } break;

    };
}

/*--------------------------------------------------------------*/

//Ouverture d'un fichier
LOVC *ouvrir_lovc(char nom_physique[], char mode)
{

    LOVC *fichier=malloc(sizeof(LOVC));            //Allocation  de la structure
    if(!fichier) {printf("UNE ERREUR EST SURVENUE LORS LA CREATION DU FICHIER"); exit; }
    if( (mode=='A') ||  (mode == 'a') )  //Mode ancien
    {
        fichier->f=fopen(nom_physique,"rb+");         //Ouverture du fichier en mode binaire LECTURE et ECRITURE
        fread(&(fichier->entete),sizeof(Entete_lovc),1,fichier->f);  //Chargement de l'entete
    }
    else
    {
        if( (mode=='N') ||  (mode == 'n') )   //Mode nouveau
        {
             fichier->f=fopen(nom_physique,"wb+");      //Ouverture du fichier en mode binaire ECRITURE
             if(!fichier->f) {printf("UNE ERREUR EST SURVENUE LORS LA CREATION DU FICHIER"); exit; }
             fichier->entete.nb = 1;
             fichier->entete.nb_enr = 0;
             fichier->entete.head = 1;
             fichier->entete.tail = 1;
             fwrite(&(fichier->entete),sizeof(Entete_lovc),1,fichier->f);  //Enregistrement de l'entete du fichier

        }
        else    //Format d'ouverture incorrect
        {
            printf("Format d'ouverture incorrect : veuillez reessayer avec  'A' : ancien || 'N' : Nouveau");
        }
    }
    return(fichier);  //Renvoyer la structure creee
}

/*--------------------------------------------------------------*/

//Fermeture d'un fichier
void fermer_lovc(LOVC *fichier)
{
    rewind(fichier->f);   //Positionnement du curseur en debut de fichier
    fwrite(&(fichier->entete),sizeof(Entete_lovc),1,fichier->f); //Sauvegarde de la derniere version de l'entete dans le fichier
    rewind(fichier->f);   //Repositionnement du curseur en debut de fichier
    fclose(fichier->f);   //Fermeture du fichier

}

/*--------------------------------------------------------------*/

//Allocation d'un nouveau bloc + mise a jour des caracteristiques de l'entete
void  alloc_bloc_lovc(LOVC *fichier)
{
        Bloc_lovc *buf=malloc(sizeof(_buffer));       //Allocation du buffer (_buffer)
        liredir_lovc(fichier,fichier->entete.tail,buf);   //Lecture du bloc correspondant a la QUEUE
        buf->suiv=fichier->entete.tail + 1;           //Mise a jour du suvant de la queue (nouvelle queue)
        ecriredir_lovc(fichier,fichier->entete.tail,buf);   //Ecriture de la queue dans le fichier
        aff_entete_lovc(fichier,3,fichier->entete.tail+1);  //Mise a jour du champs TAIL/QUEUE
        buf->suiv=-1;                         //Mise a jour du suivant a NILL
        sprintf(buf->tab,"%s","");               //Vider la chaine du _buffer
        ecriredir_lovc(fichier,fichier->entete.tail,buf);    //Ecriture du_buffer dans la nouvelle queue
        fichier->entete.nb = fichier->entete.nb + 1;     //Mise a jour du nombre de blocs alloues
}


/*---------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------- Modules du TP -----------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------*/


//Construction de la chaine (enregistrement) a ajouter dans le fichier LOVC
//Forme de l'eregistrement : taille efface cle # solde $
void concat(char result[],long long int cle, float solde)
{
    char ch_f[20];
    char solde_f[20];
    char taille_f[4];

    sprintf(ch_f,"%lld",cle);
    sprintf(solde_f,"%.2f",solde);
    sprintf(taille_f,"%d",strlen(ch_f) + strlen(solde_f) + 2);

    sprintf(solde_f,"%.2f",solde);
    strcat(result,taille_f);
    strcat(result,"n");       //Mise a jour du champs efface
    strcat(result,ch_f);
    strcat(result,"#");       //Pour delimiter le champs cle
    strcat(result,solde_f);   //Construction de la chaine finale avec l'ordre suivant taille efface cle solde
    strcat(result,"$");       //Fin de la chaine
}

/*--------------------------------------------------------------*/

// Procedure qui permet d'ecrire n caracteres du buffer
void ecrire_chaine(LOVC *fichier,int n,  int *i, int *j, char chaine[],int *cpt, Bloc_lovc *buf)
{
    int k=0;
    (*cpt)=0;     //Nombre de blocs ajoutes
    for(k=0;k<n;k++)   //Pour se deplacer dans la chaine
    {
        if((*j)<_MAX)  //Si on est toujours dans le bloc courant (on ne depasse pas le max)
        {
            buf->tab[*j]=chaine[k]; //Affectation des caracteres de la chaine dans le_buffer un a un
            (*j)++;                  //Deplacement dans le _buffer
        }
        else                          //Si la chaine a inserer depasse le_buffer
         {
            ecriredir_lovc(fichier,*i,buf);    //Ecriture du _buffer precedent dans le fichier
            alloc_bloc_lovc(fichier);        //Allocation d'un nouveau bloc afin de recevoir le reste de la chaine
            buf->tab[0]=chaine[k];            //Ecrture du kieme caractere de la chaine dans la position 0
            (*j)=1;                          //Passage a la position 1
            (*i)=entete_lovc(fichier,3);     //Deplacement dans les bloc du ficher
            (*cpt)++;     //Incrementation du nombre de blocs alloues
        }
    }
    buf->tab[*j]='\0';   //Fin de la chaine
    fichier->entete.nb_enr++;
}

/*--------------------------------------------------------------*/

//Creation du fichier LOVC a partir du fichier TOF
void charge_values(TOF* f_tof, LOVC* f_lovc)
{
    Bloc buffer;
    long long int ccp;
    float solde;
    char chaine[100];
    int taille;
    int current_i = entete_lovc(f_lovc,2);   //Tete courante du fichier
    int j = 0; //Pour parcourir le buffer
    int cpt = 0;   //Nombre de blocs ajoutes
    for(int k = 1;  k <= f_tof->entete.nb_bloc; k++)
    {
        lireDir(f_tof,k,&buffer);
        for(int p = 0; p <buffer.nb; p++)
        {
            strcpy(chaine,"");
            ccp = buffer.compte[p].num_ccp;
            solde = buffer.compte[p].solde;
            concat(chaine,ccp,solde);
            ecrire_chaine(f_lovc,strlen(chaine),&current_i,&j, chaine, &cpt,&_buffer);
            ecriredir_lovc(f_lovc,current_i,&_buffer);
        }
    }

    printf("\n\n\n                                       %c%c%c%c  LE FICHIER A ETE CREE AVEC SUCCES  %c%c%c%c",16,16,16,16,17,17,17,17);

}

/*--------------------------------------------------------------*/

//Obtention de l'eregistrement de la position POS dans une chaine result
void get_enr(LOVC* file, int pos, char result[])
{
    int i = 1;
    int j = 1;
    int cpt = 0;
    int stop  = 0;
    char temp[3];

    liredir_lovc(file,i,&_buffer);
    while(!stop && i < entete_lovc(file,3))
    {
        if(j <= _MAX)
        {
            if(_buffer.tab[j] == '$')
            {
                if(++cpt == pos)
                {
                    stop = 1;
                }
                else{
                    strcpy(result,"");
                    j++;
                }
            }
            else
            {
                sprintf(temp,"%c", _buffer.tab[j]);
                strcat(result,temp);
                j++;
            }
        }
        else{
            liredir_lovc(file,++i,&_buffer);
            j = 0;
        }
    }
}

/*--------------------------------------------------------------*/

//Affichage du contenu du fichier
void afficher_fichier(LOVC* file)
{
    int i = 1;
    printf("\t\t\t              %c%c%c%c  Affichage Du contenu du fichier LOVC  %c%c%c%c                    \n\n",16,16,16,16,17,17,17,17);
    if (entete_lovc(file,1) < 4)
    {
    while(i <= entete_lovc(file,1))
    {
        liredir_lovc(file,i, &_buffer);
        printf("\n\n---------------------------------------------------------- Bloc %d -------------------------------------------------------\n\n",i);
        printf("%s", _buffer.tab);
        i++;

    }
    }
    else
    {
        while(i < 4)
    {
        liredir_lovc(file,i, &_buffer);
        printf("\n\n---------------------------------------------------------- Bloc %d ------------------------------------------------------\n\n",i);
        printf("%s", _buffer.tab);
        i++;

    }
    }
}

/*--------------------------------------------------------------*/

//Affichage du contenu d'une ligne
void afficher_ligne(LOVC* file, int ligne)
{
    if(ligne > entete_lovc(file,3)){
        printf("\nLa ligne n'existe pas dans le fichier .");
    }else{
    int i = 1;
    printf("\n\n============================== Affichage de la ligne %d ===================================\n\n", ligne);
    liredir_lovc(file,i, &_buffer);
    printf("%s\n ET Sa longeur est %d", _buffer.tab, strlen(_buffer.tab)); }
}



/*--------------------------------------------------------------*/

//Extraction des elements (champs) d'un enregistrement (Taille, efface, ccp et solde) dans des chaines
void get_elements(char result[], char taille[], char efface[], char ccp[], char solde[])
{
    int pos = 3;
    strncat(taille,result,2);

    char temp[2];
    sprintf(temp,"%c", result[2]);
    strcat(efface,temp);

    while(result[pos] != '#')
    {
        sprintf(temp,"%c", result[pos]);
        strcat(ccp,temp);
        pos++;
    }
    pos++;
    while(result[pos] != '\0')
    {
        sprintf(temp,"%c", result[pos]);
        strcat(solde,temp);
        pos++;
    }
}

/*--------------------------------------------------------------*/

//Obtention et AFFICHAGE des comptes ayant un solde inferieur a 0
void get_small_values(LOVC *file)
{
    float solde = 0;
    char taille[3] = {};
    char efface[2] = {};
    char ccp[30] = {};
    char solde_str[20] = {};
    char eff[2];
    char buf[100];
    int current = 1;
    int cpt=0;

    sprintf(eff,"%c",'o');
    printf("\t\t\t\t     %c%c%c%c  Affichage des comptes et leurs soldes %c%c%c%c \n",16,16,16,16,17,17,17,17);
    for (int i = 1; i < entete_lovc(file,4); i++)
    {
        strcpy(taille ,"") ;
        strcpy(efface ,"") ;
        strcpy(ccp ,"") ;
        strcpy(solde_str ,"") ;
        get_enr(file,i,buf);
        get_elements(buf,taille,efface,ccp,solde_str);

        solde = atof(solde_str);
        if(solde < 0.0 && (!strcmp(efface,eff)==0))
        {
            cpt++;
           printf("\n%d/ %s %c %s DZD",current++,ccp,16,solde_str);        }
    }
    printf("\n\n\n                                      Le nombre de comptes ayant un solde n%cgatif : %d \n",130,cpt);

}

/*--------------------------------------------------------------*/

//Consultation des comptes ayant un solde superieur a la somme demandee
void get_big_values(LOVC *file)
{

    float solde = 0;
    char taille[3] = {};
    char efface[2] = {};
    char ccp[30] = {};
    char solde_str[20] = {};
    int cpt=0;
    char buf[100];
    char eff[2];
    int current = 1;

    printf("\t\t\t\t     %c%c%c%c  Affichage des comptes et leurs soldes %c%c%c%c \n",16,16,16,16,17,17,17,17);
    for (int i = 1; i < entete_lovc(file,4); i++)
    {
        strcpy(taille ,"") ;
        strcpy(efface ,"") ;
        strcpy(ccp ,"") ;
        strcpy(solde_str ,"") ;
        get_enr(file,i,buf);
        get_elements(buf,taille,efface,ccp,solde_str);
        sprintf(eff,"%c",'o');
        solde =atof(solde_str);
        if ((solde >= 1000000.00) && (!strcmp(efface,eff)==0))
        {
             cpt++;
             printf("\n%d/ %s %c %s DZD",current++,ccp,16,solde_str);
        }
    }
    printf("\n\n\nLe nombre de comptes ayant un solde sup%crieur a 1000000.00 : %d \n",130,cpt);
}

/*--------------------------------------------------------------*/

//Recuperation d'une chaine de caracteres
void recuperer_chaine(LOVC *fichier,int n , int *i, int *j, char chaine[]) //
{

    int k=0;
    sprintf(chaine,"%s","");
    liredir_lovc(fichier,(*i), &_buffer);
    for(k=0;k<n;k++)                        //Parcours de la chaine
    {                                       // indice de parcours de la chaine resultat et j celui du tableau
        if((*j)<=_MAX)                      //Si on est toujours dans le bloc courant
        {                                  //Le caractere 99 correspond a la fin de la chaine dans le tableau
            chaine[k]=_buffer.tab[*j] ;      //Recuperation du caractere dans la position k de la chaine
            (*j)++;                       //Deplacement d'une position dans le buffer
        }
        else                             //Si on a depasse la taille du bloc
        {
            (*i)=_buffer.suiv;    //Passe au bloc suivant
            liredir_lovc(fichier,(*i),&_buffer);   //Lecture
            chaine[k]=_buffer.tab[0];       //Recuperation du premier caractere du tableau de carractere correspondant au kieme car de la chaine
            (*j)=1;                      //Positionnement du second caractere dans le nouveau buffer
        }
    }
    chaine[k] = '\0';
}

/*--------------------------------------------------------------*/


long long int accounts[50];
int cursour = 0;

//Obtenir un enregistrement a la position specifiee
void get_enr_pos(LOVC* file, int pos, char result[], int *posi, int *posj)
{
    int i = 1;
    int j = 1;
    int cpt = 0;
    int stop = 0;
    char temp[3];

    liredir_lovc(file,i,&_buffer);
    while(!stop && i < entete_lovc(file,3))
    {
        if(j <= _MAX)
        {
            if(_buffer.tab[j] == '$')
            {
                if(++cpt == pos)
                {
                    *posi = i;
                    *posj = j;
                    stop = 1;
                }
                else{
                    strcpy(result,"");
                    j++;
                }
            }
            else
            {
                sprintf(temp,"%c", _buffer.tab[j]);
                strcat(result,temp);
                j++;
            }
        }
        else{
            liredir_lovc(file,++i,&_buffer);
            j = 0;
        }
    }
     if(_buffer.tab[*posj] > 0)
        {
            (*posj)--;
        }
        else{
            liredir_lovc(file,--(*posi),&_buffer);
            *posj = _MAX;
        }
    while(_buffer.tab[*posj] != '$')
    {
        if(_buffer.tab[*posj] > 0)
        {
            (*posj)--;
        }
        else{
            liredir_lovc(file,--(*posi),&_buffer);
            *posj = _MAX;
        }
    }
    if(_buffer.tab[*posj] <= _MAX)
        {
            (*posj)++;
        }
        else{
            liredir_lovc(file,++(*posi),&_buffer);
            *posj = 0;
        }
}

/*--------------------------------------------------------------*/

//Supression d'un enregistrement
void supp_enr(LOVC* file, int i, int j)
{
    liredir_lovc(file,i,&_buffer);
    //printf("\nresult->%sdans i->%d  et j->%d",result,i,j);
    if(j + 2 > _MAX)
    {
        liredir_lovc(file,++i,&_buffer);
        j = (j + 2) % _MAX;
        _buffer.tab[j] = 'o';

    }else{
        _buffer.tab[j + 2] = 'o';
    }
    ecriredir_lovc(file,i,&_buffer);
}

/*--------------------------------------------------------------*/

//Supression d'un enregistrement dans le fichier
void supprimer(LOVC* file, long long int cle)
{
    int stop = 0;
    int j = 1;

    int posi = 0, posj = 0;
    char result[100];

    long long int ccp = 0;
    char taille[3] = {};
    char efface[2] = {};
    char ccp_str[30] = {};
    char solde[20] = {};

    int isFound = 0;
    int current = 0;
    while(!isFound && current <= cursour)
    {
        if(cle == accounts[current])
        {
            isFound = 1;
        }
        else{current++;};
    }

    if(isFound){
        printf("\n\n\n                            %c%c%c%c  LA SUPPRESSION DU COMPTE A ETE EFFECTUEE AVEC SUCCES  %c%c%c%c",16,16,16,16,17,17,17,17);
    }else{
    while(!stop && j < entete_lovc(file,4))
    {

        strcpy(taille ,"") ;
        strcpy(efface ,"") ;
        strcpy(ccp_str ,"") ;
        strcpy(solde ,"") ;
        strcpy(result,"");


        get_enr_pos(file,j,result,&posi,&posj);
        get_elements(result,taille,efface,ccp_str,solde);

        ccp = atoll(ccp_str);

        if(ccp == cle)
        {
            supp_enr(file,posi,posj);
            stop = 1;
        }
        j++;
    }
    }
    if(ccp != cle && !isFound)
    {
        printf("\n\n\n\n                              !! LE COMPTE N'EXISTE PAS DANS LE FICHIER !! ");
    }
}

/*--------------------------------------------------------------*/

//Effectuer les virements dans le fichier LOVC
LOVC* add_montant(LOVC* file)
{

    LOVC* output;
    output = ouvrir_lovc("ccp_soldevir.bin",'n');

    FILE* f_vir = fopen("virements.txt","r");
    char chaine1[100] = {};
    char chaine2[100] = {};
    char ccp[50] = {}, solde[50] = {};
    int cpt = 1;

    char result[150];
    char taille[3] = {};
    char efface[2] = {};
    char ccp_str[30] = {};
    char solde_str[20] = {};
    char last_string[100] = {};

    int i = 1,  j = 0;
    int w = 0;

    while(fgets(chaine1,100,f_vir))
    {
        strcpy(taille ,"") ;
        strcpy(efface ,"") ;
        strcpy(ccp_str ,"") ;
        strcpy(solde_str ,"") ;
        strcpy(last_string,"");
        strcpy(chaine2,chaine1);
        strcpy(ccp, extraire_mot(chaine1,1));
        strcpy(solde, extraire_mot(chaine2,2));

        get_enr(file,cpt, result);
        get_elements(result,taille,efface,ccp_str,solde_str);

        concat(last_string,atoll(ccp), atof(solde) + atof(solde_str));
        ecrire_chaine(output,sizeof(last_string), &i,&j,last_string,&w,&_buffer);
        cpt++;
    }

    fclose(f_vir);

    return output;
}

/*--------------------------------------------------------------*/

//Insertion d'un compte
LOVC* insert(LOVC* file, long long int ccp, float solde)
{

    LOVC* out = ouvrir_lovc("ccp_soldeinser.bin",'n');
    int pos = 1;
    int i = 1;
    int j = 0;
    char result[150] = {};
    char taille[3] = {};
    char efface[2] = {};
    char ccp_str[30] = {};
    char solde_str[20] = {};
    accounts[cursour++] = ccp;
    long long int it_ccp;
    int once = 0;
    char last_string[150] = {};
    concat(last_string,ccp,solde);
    int counter = 0;
    while(pos <= entete_lovc(file,4))
    {
        strcpy(taille ,"") ;
        strcpy(efface ,"") ;
        strcpy(ccp_str ,"") ;
        strcpy(solde_str ,"") ;
        strcpy(result,"");
        get_enr(file,pos,result);
        get_elements(result,taille,efface,ccp_str,solde_str);

        if(ccp <= atoll(ccp_str) && !once)
        {
            once = 1;
            ecrire_chaine(out,strlen(last_string),&i,&j,last_string,&counter,&_buffer);
        }else{
        ecrire_chaine(out,strlen(result),&i,&j,result,&counter,&_buffer);
        pos++;
        }
    }
    aff_entete_lovc(out,4,entete_lovc(out,4) + 1);
    printf("\n     Compte ajout%c",130);
    return out;
}
/*--------------------------------------------------------------*/




#endif

