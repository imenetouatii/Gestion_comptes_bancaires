#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib.h"
#include "bib2.h"
#include "interface.h"


int main()
{
char cadre1[]={201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187,'\0'};
char cadre2[]={200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188,'\0'};
char choix;
char choix2;
char choix3;
char choix4;
TOF *f;
LOVC *output;
int n;
float taux;
float solde0;
long long int numccp;
long long int numccp2;

ouvrir(&f, "ccp_solde.bin",'N');
LOVC *g = ouvrir_lovc("ccp_solde2.bin",'N');

jump :
cadre();
Color(9,0);
printf("         Quittez le programme en appuyant sur 0 \n");
printf("                 Entrez 1 ou 2 afin de consulter le service du mois qui vous int%cresse : ",130);
Color(15,0);
choix = getch();
printf("\n");
switch(choix)
{
    case '1' : goto jump2 ; break;
    case '2' : goto jump3 ; break;
    case '0' : system("cls");goto fin; break;
    default: system("cls");goto jump; break;
}

jump2 :
system("cls");
menu1();
choix2 = getch();
switch(choix2)
{
case '1':
   system("cls");
   printf("\t\t\t\t        %s\n",cadre1);
   printf("\t\t\t\t        %c   1 %c Cr%cation du fichier CCP_solde    %c\n",186,16,130,186);
   printf("\t\t\t\t        %s\n\n",cadre2);
    printf("\n");
    printf("\nEntrez le nombre d'enregistrements que vous souhaitez mettre dans le fichier : ");
    scanf("%d",&n);
    printf("Entrez le taux de chargement (compris entre 0 et 1) souhait%c : ",130);
    scanf("%f",&taux);
    Color(12,0);
    charge_initial(f,n,taux);
    Color(15,0);
    printf("\n");
    system("pause");
    goto jump2;
    break;

case '2' :
    system("cls");
    printf("\t\t\t\t        %s\n",cadre1);
    printf("\t\t\t\t        %c   2 %c Cr%cation du fichier virements    %c\n",186,16,130,186);
    printf("\t\t\t\t        %s\n\n",cadre2);
    montant_ajouter(f);
    Color(12,0);
    printf("\n\n\n                                       %c%c%c%c  LE FICHIER A ETE CREE AVEC SUCCES  %c%c%c%c",16,16,16,16,17,17,17,17);
    Color(15,0);
    printf("\n\n\n\n");
    system("pause");
    goto jump2;
    break;

case '3' :
    system("cls");
    printf("\t\t\t\t        %s\n",cadre1);//                            %c
    printf("\t\t\t\t        %c   3 %c R%calisation des virements        %c\n",186,16,130,186);
    printf("\t\t\t\t        %s\n\n",cadre2);
    printf("\n\n\n\t\t\t\t            ");
    Color(0,7);
    printf("Veuillez patienter un instant ... \n\n");
    Color(15,0);
    ajouter_virement(f);
    Color(12,0);
    printf("\n\n\n                                   %c%c%c%c  LES VIREMENTS ONT ETE EFFECTUES AVEC SUCCES  %c%c%c%c",16,16,16,16,17,17,17,17);
    Color(15,0);
    printf("\n\n\n\n");
    system("pause");
    goto jump2;
    break;

case '4' :
    system("cls");
    goto jump;
    break;

default :
    system("cls");
    goto jump;
    break;
}

jump3 :
system("cls");
menu2();
choix3 = getch();
switch(choix3)
{
case '1':
    system("cls");
    printf("\t\t\t\t        %s\n",cadre1);//                            %c
    printf("\t\t\t\t        %c   1 %c C%cation du fichier ccp_solde2    %c\n",186,16,130,186);
    printf("\t\t\t\t        %s\n\n",cadre2);
    charge_values(f,g);
    printf("\n\n\n\n");
    system("pause");
    goto jump3;
    break;

case '2':
    system("cls");
    printf("\t\t\t\t        %s\n",cadre1);//                            %c
    printf("\t\t\t\t        %c   2 %c R%calisation des virements        %c\n",186,16,130,186);
    printf("\t\t\t\t        %s\n\n",cadre2);
    printf("\n\n\n\n");
    printf("\t\t\t\t           ");
    Color(0,7);
    printf("Veuillez patienter un instant ... \n\n");
    Color(15,0);
    output=add_montant(g);
    Color(12,0);
    printf("\n\n\n                                %c%c%c%c  LES VIREMENTS ONT ETE EFFECTUES AVEC SUCCES  %c%c%c%c",16,16,16,16,17,17,17,17);
    Color(15,0);
    printf("\n\n\n\n");
    printf("\n\n\n\n");
    system("pause");
    goto jump3;
    break;

case '3':
    system("cls");
    printf("\t\t\t\t        %s\n",cadre1);//                            %c
    printf("\t\t\t\t        %c   3 %c C%cation d'un compte CCP          %c\n",186,16,130,186);
    printf("\t\t\t\t        %s\n\n",cadre2);
    printf("\n\n\n\n");
    printf("   Entrez le num%cro du compte CCP que vous souhaitez cr%cer : ",130,130);
    scanf("%lld", &numccp2);
    printf("\n   Entrez le solde initial du compte : ");
    scanf("%f", &solde0);
    insert(g,numccp2,solde0);
    printf("\n\n\n");
    Color(12,0);
    printf("\n\n\n                            %c%c%c%c  LA CREATION DE VOTRE COMPTE A ETE EFFECTUEE AVEC SUCCES  %c%c%c%c",16,16,16,16,17,17,17,17);
    Color(15,0);
    printf("\n\n\n\n");
    system("pause");
    goto jump3;
    break;

case '4':
    system("cls");
    printf("\t\t\t\t        %s\n",cadre1);//                            %c
    printf("\t\t\t\t        %c   4 %c Suppresion d'un compte CCP       %c\n",186,16,186);
    printf("\t\t\t\t        %s\n\n",cadre2);
    printf("\n\n\n\n         Entrez le num%cro du compte CCP que vous d%csirez supprimer : ",130,130);
    scanf("%lld",&numccp);
    printf("\n\n\n                 ");
    Color(0,12);
    printf("Veuillez patienter s'il vous plait, cette op%cration peut prendre un certain temps...",130);
    Color(15,0);
    supprimer(output,numccp);
    printf("\n\n\n\n");
    system("pause");
    goto jump3;
    break;

case '5':
    jump4:
    system("cls");
    printf("\t\t\t\t        %s\n",cadre1);//                            %c
    printf("\t\t\t\t        %c   5 %c Consultation des comptes ccp     %c\n",186,16,186);
    printf("\t\t\t\t        %s\n\n",cadre2);
    printf("\n\n");
    printf("       %s                      %s\n",cadre1,cadre1);
    printf("       %c   1 %c Solde Sup%crieur a 1000000.00DZD  %c                      %c            2 %c Solde n%cgatif           %c\n",186,16,130,186,186,16,130,186);
    printf("       %s                      %s\n",cadre2,cadre2);
    printf("\n\n");
    Color(12,0);
    printf("\t\t\t\t        %s\n",cadre1);
   printf("\t\t\t\t        %c     3 %c Retour au menu pr%ccedant       %c\n",186,16,130,186);
   printf("\t\t\t\t        %s\n\n",cadre2);
   Color(15,0);
    printf("\n\n\t\t\t\t\t           Que voulez-vous faire ?\n");
    printf("\t\t\t\t\t            ");
    Color(0,14);
    printf("Entrez votre choix : ");
    Color(15,0);

    choix4=getch();
    switch(choix4)
    {
     case '1':
    system("cls");
    printf("\t\t\t\t        %s\n",cadre1);//                            %c
    printf("\t\t\t\t        %c   Solde superieur a 1000000.00 DZD     %c\n",186,186);
    printf("\t\t\t\t        %s\n\n",cadre2);
    get_big_values(g);
    printf("\n\n\n");
    system("pause");
    goto jump4;
    break;

     case '2':
    system("cls");
    printf("\t\t\t\t        %s\n",cadre1);//                            %c
    printf("\t\t\t\t        %c              Solde negatif             %c\n",186,186);
    printf("\t\t\t\t        %s\n\n",cadre2);
    get_small_values(g);
    printf("\n\n\n");
    system("pause");
    goto jump4;
    break;

     case '3':
    goto jump3;
    break;

     default:
    goto jump3;
    break;
    }

case '6':
   system("cls");
   printf("\t\t\t\t        %s\n",cadre1);
   printf("\t\t\t\t        %c             6 %c Affichage              %c\n",186,16,186);
   printf("\t\t\t\t        %s\n\n",cadre2);
   printf("\n\n");
       printf("\t\t\t                %c%c%c%c  Affichage du contenu de l'entete  %c%c%c%c                    \n\n",16,16,16,16,17,17,17,17);

   printf("\t\t\t\t        %s\n",cadre1);
   printf("\t\t\t\t        %c  %c Nombre de blocs : %d                 %c\n",186,16,entete_lovc(g,1),186);
   printf("\t\t\t\t        %c  %c Bloc de tete    : %d                 %c\n",186,16,entete_lovc(g,2),186);
   printf("\t\t\t\t        %c  %c Bloc de queue   : %d                 %c\n",186,16,entete_lovc(g,3),186);
   printf("\t\t\t\t        %c  %c Espace vide 1 du dernier bloc : %d   %c\n",186,16,entete_lovc(g,1),186);
   printf("\t\t\t\t        %s\n\n",cadre2);
   printf("\n\n");
   afficher_fichier(output);
   printf("\n\n");
   Color(12,0);
   printf("     %c Nombre de LirDire : %d",16,nb_lirdir);
   printf("     %c Nombre de EcrirDire : %d",16,nb_ecrirdir);
   Color(15,0);
   printf("\n\n\n\n");
   system("pause");
   goto jump3;
   break;

case '7':
    system("cls");
    goto jump;
    break;

default :
    system("cls");
    goto jump;
    break;
}

fin :
    fermer(f);
    fermer_lovc(g);
    fermer_lovc(output);
    return 0;
}
