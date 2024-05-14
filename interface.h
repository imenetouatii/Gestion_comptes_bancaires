#ifndef interface_H
#define interface_H
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<windows.h>


void Color(int couleurDuTexte,int couleurDeFond);
void cadre();
void menu1();
void menu2();


void Color(int couleurDuTexte,int couleurDeFond)
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}


void cadre()
 {

    char cadre1[]={201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187,'\0'};
    char  cadre2[]={200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188,'\0'};
    Color(9,0);
    printf(" %s\n",cadre1);
    printf(" %c$$ $$ $                                                                                                      $ $$ $$%c\n",186,186);
    printf(" %c$$$ $$ $                 ######  ####  #####   ###  ###  ##  ####  ####        ######   ####                $ $$ $$$%c\n",186,186);
    printf(" %c$$$$ $$ $                ###     ##    ##  #   ##    ##  ##  ##    ##          ##   #   ##                 $ $$ $$$$%c\n",186,186);
    printf(" %c$$$$$ $$ $                 ##    ####  #####    ##  ##   ##  ##    ####        ##   #   ####              $ $$ $$$$$%c\n",186,186);
    printf(" %c$$$$$$ $$ $                ###   ##    ##  ##    ####    ##  ##    ##          ##   #   ##               $ $$ $$$$$$%c\n",186,186);
    printf(" %c$$$$$$$ $$ $             #####   ####  ##   ##    ##     ##  ####  ####        ######   ####            $ $$ $$$$$$$%c\n",186,186);
    printf(" %c$$$$$$$$ $$ $                                                                                          $ $$ $$$$$$$$%c\n",186,186);
    printf(" %c$$$$$$$$ $$ $                                                                                          $ $$ $$$$$$$$%c\n",186,186);
    printf(" %c$$$$$$$ $$ $     ###  ###  ##  #####   ####  ###   ###  ####  ##  ##  ######      ####  ####  ######    $ $$ $$$$$$$%c\n",186,186);
    printf(" %c$$$$$$ $$ $      ##    ##  ##  ##  #   ##    #### ####  ##    ### ##    ##        ##    ##    ##   #     $ $$ $$$$$$%c\n",186,186);
    printf(" %c$$$$$ $$ $        ##  ##   ##  #####   ####  #########  ####  ######    ##        ##    ##    ######      $ $$ $$$$$%c\n",186,186);
    printf(" %c$$$$ $$ $          ####    ##  ##  ##  ##    ###   ###  ##    ### ##    ##        ##    ##    ##           $ $$ $$$$%c\n",186,186);
    printf(" %c$$$ $$ $            ##     ##  ##   ## ####  ###   ###  ####  ##  ##    ##        ####  ####  ##            $ $$ $$$%c\n",186,186);
    printf(" %c$$ $$ $                                                                                                      $ $$ $$%c\n",186,186);
    printf(" %s\n\n",cadre2);
    Color(15,0);
    printf("\t\t\t\t\t       %c%c%c%c%c%c%c Bienvenue %c%c%c%c%c%c%c \n\n",16,16,16,16,16,16,16,17,17,17,17,17,17,17);
    printf("\t      ");
    Color(0,7);
    printf("Nous proposons deux services de virement qui correspondent aux parties 1 et 2 du TP dans l'ordre \n");
    Color(15,0);
    printf("              ");
    Color(0,8);
    printf("IMPORTANT : Vous devez obligatoirement ex%ccuter la PARTIE 1 afin de faire fonctionner la PARTIE 2.\n",130);
    Color(15,0);
    printf("                        ");
    Color(0,8);
    printf("Si vous QUITTEZ le programme il faut TOUT REFAIRE A NOUVEAU (PARTIES 1 et 2) !!! \n\n",130);
    Color(15,0);
    printf("\t\t           %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                          %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c   \n",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
    printf("\t\t           %c (1) Mois courant %c                          %c (2) Mois suivant %c    ",179,179,179,179);
    printf("\t\t                                   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                          %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c   \n",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
    printf("\n");
    printf("\t");

 }


 void menu1()
 {
   char cadre1[]={201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187,'\0'};
   char cadre2[]={200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188,'\0'};
   printf("\n");
   printf("\t\t %c                               %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                               %c\n",4,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,4);
   printf("\t\t   %c                             %c%c MENU DES OPERATIONS %c%c                             %c\n",4,248,250,250,248,4);
   printf("\t\t %c                               %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                               %c\n",4,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,4);
   printf("                   %c                                                                                   %c\n",4,4);
   printf("                 %c                                                                                       %c\n",4,4);
   Color(9,0);
   printf("\t\t   %c                    %s                     %c\n",4,cadre1,4);
   printf("\t\t %c                      %c   1 %c Cr%cation du fichier CCP_solde    %c                       %c\n",4,186,16,130,186,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre2,4);
   printf("                 %c                                                                                       %c\n",4,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre1,4);
   printf("\t\t %c                      %c  2 %c Cr%cation du fichier des virements %c                       %c\n",4,186,16,130,186,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre2,4);
   printf("                 %c                                                                                       %c\n",4,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre1,4);
   printf("\t\t %c                      %c  3 %c R%calisation des virements         %c                       %c\n",4,186,16,130,186,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre2,4);
   printf("                 %c                                                                                       %c\n",4,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre1,4);
   printf("\t\t %c                      %c  4 %c Retour au menu principal          %c                       %c\n",4,186,16,186,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre2,4);
   printf("                 %c                                                                                       %c\n",4,4);
   printf("                   %c                                                                                   %c\n",4,4);
   printf("                 %c                                                                                       %c\n\n\n",4,4);
   printf("\t\t\t        ");
   Color(0,1);
   printf("Entrez le num%cro de l'op%cration que vous voulez effectuer : ",130,130);
   Color(15,0);


}


void menu2()
 {
   char cadre1[]={201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187,'\0'};
   char cadre2[]={200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188,'\0'};
   printf("\n");
   printf("\t\t %c                               %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                               %c\n",4,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,4);
   printf("\t\t   %c                             %c%c MENU DES OPERATIONS %c%c                             %c\n",4,248,250,250,248,4);
   printf("\t\t %c                               %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                               %c\n",4,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,250,248,4);
   printf("                   %c                                                                                   %c\n",4,4);
   printf("                 %c                                                                                       %c\n",4,4);
   Color(6,0);
   printf("\t\t   %c                    %s                     %c\n",4,cadre1,4);
   printf("\t\t %c                      %c  1 %c Cr%cation du fichier CCP_solde2    %c                       %c\n",4,186,16,130,186,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre2,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre1,4);
   printf("\t\t %c                      %c  2 %c R%calisation des virements         %c                       %c\n",4,186,16,130,186,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre2,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre1,4);
   printf("\t\t %c                      %c  3 %c Cr%cation d'un compte CCP          %c                       %c\n",4,186,16,130,186,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre2,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre1,4);
   printf("\t\t %c                      %c  4 %c Suppression d'un compte CCP       %c                       %c\n",4,186,16,186,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre2,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre1,4);
   printf("\t\t %c                      %c  5 %c Consultation de comptes CCP       %c                       %c\n",4,186,16,186,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre2,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre1,4);
   printf("\t\t %c                      %c  6 %c Affichage                         %c                       %c\n",4,186,16,186,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre2,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre1,4);
   printf("\t\t %c                      %c  7 %c Retour au menu principal          %c                       %c\n",4,186,16,186,4);
   printf("\t\t   %c                    %s                     %c\n",4,cadre2,4);
   printf("\n");
   printf("\t\t\t     ");
   Color(0,7);
   printf("      Entrez le num%cro de l'op%cration que vous voulez effectuer : ",130,130);
   Color(15,0);

}


#endif

