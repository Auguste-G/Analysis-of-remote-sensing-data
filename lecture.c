#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lecture_fonction.h"

const SDL_Color SDL_FOND_HAUT = {0XBF, 0XC9, 0XD9, 255};

int main( int nbParam, char *tabParam[] )
{

    //Dessin

    printf("\n                    PROJET DE L'UC : PROGRAMMER EN LANGAGE C                    \n");
    printf("            Une introduction a l'analyse de dnnees de la teledetection          \n\n");

    printf("        .               .                   .       .      .     .      .       \n");
    printf("                .    .         .    .            .     ______                   \n");
    printf("            .           .             .               ////////                  \n");
    printf("                      .    .   ________   .  .      /////////     .    .        \n");
    printf("                 .            |.###### **        ./////////    .                \n");
    printf("          .                 .##      ### |*    /////////                       \n");
    printf("             .       .    .##         ###|# */////////       .     .   .       \n");
    printf("                          ##.  SPOT   ###|#///////// .     .                   \n");
    printf("           .    .         ##          ###|/////////                .            \n");
    printf("                   .       ##        ###//######/   .                           \n");
    printf("        .                    ##.###.##//#########,     .     .                  \n");
    printf("                .           .     # //////#####   #                 .    .      \n");
    printf("                             .    ///////// ### ' #    .                       \n");
    printf("            .        .          /////////     ###         .                  \n");
    printf("                              /////////                              .          \n");
    printf("                       .   ./////////     .     .                               \n");
    printf("               .           --------   .                  ..             .       \n");
    printf("        .               .        .         .                       .            \n");
    printf("                              ________________________                          \n");
    printf("      ____________------------                        -------------_________    \n");



    //Déclaration des variables

    int nblignes = 0, nbcolonnes = 0, i = 0, j=0, c =0, n =0, posi = 0;
    int x_souris = 0, y_souris = 0;

    //Choix de la ville
    posi = Choix();

    //Lecture des métadonnées
    LectureMetadonnees(&nblignes,&nbcolonnes, posi);

    /* Lecture des données */

    //déclaration des variables et affectation de la mémoire
    int **ptr1 = NULL, **ptr2 = NULL, **ptr3 = NULL;

    ptr1 =(int**)malloc(nblignes*sizeof(int*));
    ptr2 =(int**)malloc(nblignes*sizeof(int*));
    ptr3 =(int**)malloc(nblignes*sizeof(int*));

    if((ptr1==NULL)||(ptr2==NULL)||(ptr1==NULL)) //Test si mémoire non attribuée
        exit(0);


    for(i=0; i < nblignes; i++)
    {
        ptr1[i]=(int*)malloc(nbcolonnes*sizeof(int));
        ptr2[i]=(int*)malloc(nbcolonnes*sizeof(int));
        ptr3[i]=(int*)malloc(nbcolonnes*sizeof(int));

        if((ptr1[i]==NULL)||(ptr2[i]==NULL)||(ptr3[i]==NULL))
                exit(0);

        memset(ptr1[i],0,nbcolonnes*sizeof(int));
        memset(ptr2[i],0,nbcolonnes*sizeof(int));
        memset(ptr3[i],0,nbcolonnes*sizeof(int));
    }

    //Ouverture des fichiers
    FILE *ptrf1=NULL, *ptrf2=NULL, *ptrf3=NULL; /* définition d’un pointeur pour pointer sur le début du fichier à lire */

   if (posi == 0) //cas de grignon
        {
            ptrf1=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\grignon\\FDO0000.PER","r+b");
            ptrf2=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\grignon\\FDO0001.PER","r+b");
            ptrf3=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\grignon\\FDO0002.PER","r+b");
        }
    else
        {
            ptrf1=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\paris\\FDO0000.PER","r+b");
            ptrf2=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\paris\\FDO0001.PER","r+b");
            ptrf3=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\paris\\FDO0002.PER","r+b");
        }

    if ((ptrf1==NULL)||(ptrf2==NULL)||(ptrf3==NULL))  /* Test si erreur à l’ouverture du fichier */
        return 0;

    //récupération des données
    LectureDonnees0(ptr1,ptrf1, nblignes, nbcolonnes);
    LectureDonnees0(ptr2,ptrf2, nblignes, nbcolonnes);
    LectureDonnees0(ptr3,ptrf3, nblignes, nbcolonnes);

    // fermeture des fichiers
    fclose(ptrf1);
    fclose(ptrf2);
    fclose(ptrf3);

    printf("\nLes donnees sont extraites");



    /* Calcul de la fréquence, Max de fréquence et Valeurs contrastées*/


    // Déclaration des variables et affectation mémoire


    int *Freq1 = malloc(100 * sizeof(int));
    int *Freq2 = malloc(100 * sizeof(int));
    int *Freq3 = malloc(100 * sizeof(int));

    for(i=0;i<100;i++) // Pourquoi je suis obligé de faire ça pour avoir des 0 à chaque ligne ???
    {
        Freq1[i]=0;
        Freq2[i]=0;
        Freq3[i]=0;
    }


    int *Fcos1 = malloc(100 * sizeof(int));
    int *Fcos2 = malloc(100 * sizeof(int));
    int *Fcos3 = malloc(100 * sizeof(int));

    int Max1[3], Max2[3], Max3[3];

    //Récupération des fréquences

    Frequence(ptr1,Freq1);
    Frequence(ptr2,Freq2);
    Frequence(ptr3,Freq3);

    //Trouver la position avec le maximum de fréquence

    TrouverMax(Freq1,Max1);
    TrouverMax(Freq2,Max2);
    TrouverMax(Freq3,Max3);

    //Récupération chiffres constrastés
    Chiffrecontraste(Freq1,Fcos1);
    Chiffrecontraste(Freq2,Fcos2);
    Chiffrecontraste(Freq3,Fcos3);


    int rep = 0;

    do
    {
        rep = AffichageMenu();
        switch(rep)
        {
            case 1 :
            {
               //Affichage carte

                SDL_Event evenement;
                int fin = SDL_FAUX, crayon = SDL_FAUX, couleur = 0;
                char texte[100] = "", saisie[100] = "";

                /* Initialisation de SDL  */
                SDL_Depart(NULL, 14);

                /* creation de la fenetre avec son "rendu" */
                SDL_CreerFenetreRendu("Image Normale", nbcolonnes, nblignes);
                SDL_Trace("Fenetre ouverte");

                /* information d'usage */

                for(i=0 ; i<nblignes ; i++)
                {
                    for(j=0; j<nbcolonnes ; j++)
                    {
                        SDL_Color couleur = {ptr2[i][j],ptr1[i][j],ptr3[i][j],255}; //rouge, vert , bleu
                        SDL_ChangerCouleurDessin(couleur);
                        SDL_RenderDrawPoint(SDL_rendu,j,i);
                    }
                }
                SDL_DessinerFondRectangle(40,240,50,3,SDL_VERT);
                SDL_EcrireTexte("1 km",45,225,NULL,SDL_VERT);
                SDL_RenderPresent(SDL_rendu);

                /* iteration d'acquisition des evenements de la fenetre */
                while ( ! fin )
                {
                    SDL_AttendreEvent( & evenement );
                    switch(evenement.type)
                    {
                        case SDL_QUIT :
                            /* fermeture de la fenetre */
                            fin = SDL_VRAI;
                            break;

                        case SDL_TEXTINPUT :
                            /* frappe d'une touche au clavier */
                            strcpy( saisie, SDL_TexteClavier(evenement) );
                            sprintf(texte, "frappe au clavier -> <<%s>>", saisie);
                            SDL_Trace(texte);
                            if ( 0 == strcmp(saisie, " ") ) {
                                fin = SDL_VRAI;}
                            break;

                        case SDL_WINDOWEVENT : case SDL_TEXTEDITING :
                        case SDL_KEYDOWN : case SDL_KEYUP :
                            /* neutralisation de ces evenements annexes */
                            break;

                    }
                }

                /* fermeture progressive */
                SDL_EffacerRendu();
                SDL_Fermer();

                break;
            }
            case 2 :
            {
                //Affichage Histo

                SDL_Event evenement;
                int fin = SDL_FAUX, crayon = SDL_FAUX, couleur = 0;
                char texte[100] = "", saisie[100] = "";

                /* Initialisation de SDL  */
                SDL_Depart(NULL, 14);

                /* creation de la fenetre avec son "rendu" */
                SDL_CreerFenetreRendu("Histogrammes de la repartition des couleurs",900,350);
                SDL_Trace("Fenetre ouverte");

                /* affichage d'image et de texte */


                SDL_DessinerFondRectangle(0, 0, 900, 350, SDL_FOND_HAUT);
                SDL_EcrireTexte("Rouge",125 , 50, NULL, SDL_ROUGE);
                SDL_EcrireTexte("Vert",425 , 50, NULL, SDL_VERT);
                SDL_EcrireTexte("Bleu",725 , 50, NULL, SDL_BLEU);
                SDL_DessinerFondRectangle(50, 100, 200, 200, SDL_SANS_COULEUR);
                SDL_DessinerFondRectangle(350, 100, 200, 200, SDL_SANS_COULEUR);
                SDL_DessinerFondRectangle(650, 100, 200, 200, SDL_SANS_COULEUR);
                SDL_DessinerCadreRectangle(375, 18, 170, 20, SDL_NOIR);
                SDL_EcrireTexte("Touche Espace pour finir", 380, 20, NULL, SDL_NOIR);

                //Histo Rouge
                j = 0;
                c = 0;
                n = 0;
                for(i=0;i<100;i++)
                {
                    if(Freq2[i]>10&&Freq2[i]<100000)
                    {
                        SDL_DessinerFondRectangle(100+(2*j), 300, 2, (-Freq2[i]/40),SDL_ROUGE);
                        j++;
                    }
                }
                SDL_EcrireTexte(Max2,115 , 310, NULL, SDL_ROUGE);


                //Histo Vert
                j = 0;
                for(i=0;i<100;i++)
                {
                    if(Freq1[i]>10&&Freq1[i]<100000)
                    {
                        SDL_DessinerFondRectangle(400+(2*j), 300, 2, (-Freq1[i]/35),SDL_VERT);
                        j++;
                    }

                }
                SDL_EcrireTexte(Max1,415 , 310, NULL, SDL_VERT);

                //Histo Bleu
                j = 0;
                for(i=0;i<100;i++)
                {
                    if(Freq3[i]>10&&Freq3[i]<100000)
                    {
                        SDL_DessinerFondRectangle(700+j, 300, 1, (-Freq3[i]/15),SDL_BLEU);
                        j++;
                    }

                }
                SDL_EcrireTexte(Max3,715 , 310, NULL, SDL_BLEU);



                while ( ! fin )
                {
                    SDL_AttendreEvent( & evenement );
                    switch(evenement.type)
                    {
                        case SDL_QUIT :

                            /* fermeture de la fenetre */
                            fin = SDL_VRAI;
                            break;

                        case SDL_TEXTINPUT :
                            /* frappe d'une touche au clavier */
                            strcpy( saisie, SDL_TexteClavier(evenement) );
                            sprintf(texte, "frappe au clavier -> <<%s>>", saisie);
                            SDL_Trace(texte);
                            if ( 0 == strcmp(saisie, " ") ) {
                                fin = SDL_VRAI;}
                            break;

                        case SDL_MOUSEBUTTONUP :

                            SDL_PositionSouris( & x_souris, & y_souris );
                            if ((y_souris > 18 && y_souris < 38) && (x_souris > 375 &&x_souris <545))
                            {
                                fin = SDL_VRAI;
                            }
                            break;

                        case SDL_WINDOWEVENT : case SDL_TEXTEDITING :
                        case SDL_KEYDOWN : case SDL_KEYUP :
                            /* neutralisation de ces evenements annexes */
                            break;

                    }
                }

                /* fermeture */
                SDL_EffacerRendu();
                SDL_Fermer();

            break;

            }
            case 3 :
            {
                //Affichage carte

                SDL_Event evenement;
                int fin = SDL_FAUX, crayon = SDL_FAUX, couleur = 0;
                char texte[100] = "", saisie[100] = "";

                /* Initialisation de SDL  */
                SDL_Depart(NULL, 14);

                /* creation de la fenetre avec son "rendu" */
                SDL_CreerFenetreRendu("Image Contrastee", nbcolonnes, nblignes);
                SDL_Trace("Fenetre ouverte");

                /* information d'usage */

                for(i=0 ; i<nblignes ; i++)
                {
                    for(j=0; j<nbcolonnes ; j++)
                    {
                        SDL_Color couleur = {Fcos2[ptr2[i][j]],Fcos1[ptr1[i][j]],Fcos3[ptr3[i][j]],255}; //rouge, vert , bleu
                        SDL_ChangerCouleurDessin(couleur);
                        SDL_RenderDrawPoint(SDL_rendu,j,i);

                    }
                }
                SDL_DessinerFondRectangle(40,240,50,3,SDL_NOIR);
                SDL_EcrireTexte("1 km",45,225,NULL,SDL_NOIR);
                SDL_RenderPresent(SDL_rendu);

                /* iteration d'acquisition des evenements de la fenetre */
                while ( ! fin )
                {
                    SDL_AttendreEvent( & evenement );
                    switch(evenement.type)
                    {
                        case SDL_QUIT :
                            /* fermeture de la fenetre */
                            fin = SDL_VRAI;
                            break;

                        case SDL_TEXTINPUT :
                            /* frappe d'une touche au clavier */
                            strcpy( saisie, SDL_TexteClavier(evenement) );
                            sprintf(texte, "frappe au clavier -> <<%s>>", saisie);
                            SDL_Trace(texte);
                            if ( 0 == strcmp(saisie, " ") ) {
                                fin = SDL_VRAI;}
                            break;

                        case SDL_WINDOWEVENT : case SDL_TEXTEDITING :
                        case SDL_KEYDOWN : case SDL_KEYUP :
                            /* neutralisation de ces evenements annexes */
                            break;
                    }
                }

                /* fermeture */
                SDL_EffacerRendu();
                SDL_Fermer();

                break;
            }
            case 4 :
            {
                //Affichage carte

                SDL_Event evenement;
                int fin = SDL_FAUX, crayon = SDL_FAUX, couleur = 0;
                char texte[100] = "", saisie[100] = "";

                /* Initialisation de SDL  */
                SDL_Depart(NULL, 14);

                /* creation de la fenetre avec son "rendu" */
                SDL_CreerFenetreRendu("DVI Contraste", nbcolonnes, nblignes);
                SDL_Trace("Fenetre ouverte");

                /* information d'usage */

                int d = 0;
                for(i=0 ; i<nblignes ; i++)
                {
                    for(j=0; j<nbcolonnes ; j++)
                    {
                        if ((Fcos2[ptr2[i][j]]+Fcos3[ptr3[i][j]])!=0)  //NDVI contrasté
                            d = ((Fcos3[ptr3[i][j]]*150-Fcos2[ptr2[i][j]]*150)/(Fcos2[ptr2[i][j]]+Fcos3[ptr3[i][j]]));
                        /**if ((ptr2[i][j]+ptr3[i][j])!=0) // NDVI non contrasté
                            d = ((ptr3[i][j]*255-ptr2[i][j]*255)/(ptr2[i][j]+ptr3[i][j]));*/
                        else
                            d = -1;
                        SDL_Color couleur = {d,d,d,255}; //rouge, vert , bleu
                        SDL_ChangerCouleurDessin(couleur);
                        SDL_RenderDrawPoint(SDL_rendu,j,i);

                    }
                }
                SDL_DessinerFondRectangle(40,240,50,3,SDL_ROUGE);
                SDL_EcrireTexte("1 km",45,225,NULL,SDL_ROUGE);
                SDL_RenderPresent(SDL_rendu);

                /* iteration d'acquisition des evenements de la fenetre */
                while ( ! fin )
                {
                    SDL_AttendreEvent( & evenement );
                    switch(evenement.type)
                    {
                        case SDL_QUIT :
                            /* fermeture de la fenetre */
                            fin = SDL_VRAI;
                            break;

                        case SDL_TEXTINPUT :
                            /* frappe d'une touche au clavier */
                            strcpy( saisie, SDL_TexteClavier(evenement) );
                            sprintf(texte, "frappe au clavier -> <<%s>>", saisie);
                            SDL_Trace(texte);
                            if ( 0 == strcmp(saisie, " ") ) {
                                fin = SDL_VRAI;}
                            break;

                        case SDL_WINDOWEVENT : case SDL_TEXTEDITING :
                        case SDL_KEYDOWN : case SDL_KEYUP :
                            /* neutralisation de ces evenements annexes */
                            break;
                    }
                }

                /* fermeture */
                SDL_EffacerRendu();
                SDL_Fermer();

                break;
            }
            case 5 :
            {
                //Choix de la ville
                posi = Choix();

                //Lecture des métadonnées
                LectureMetadonnees(&nblignes,&nbcolonnes, posi);

                //affectation de la mémoire

                ptr1 =(int**)malloc(nblignes*sizeof(int*));
                ptr2 =(int**)malloc(nblignes*sizeof(int*));
                ptr3 =(int**)malloc(nblignes*sizeof(int*));

                if((ptr1==NULL)||(ptr2==NULL)||(ptr1==NULL)) //Test si mémoire non attribuée
                    exit(0);


                for(i=0; i < nblignes; i++)
                {
                    ptr1[i]=(int*)malloc(nbcolonnes*sizeof(int));
                    ptr2[i]=(int*)malloc(nbcolonnes*sizeof(int));
                    ptr3[i]=(int*)malloc(nbcolonnes*sizeof(int));

                    if((ptr1[i]==NULL)||(ptr2[i]==NULL)||(ptr3[i]==NULL))
                            exit(0);

                    memset(ptr1[i],0,nbcolonnes*sizeof(int));
                    memset(ptr2[i],0,nbcolonnes*sizeof(int));
                    memset(ptr3[i],0,nbcolonnes*sizeof(int));
                }

                //Ouverture des fichiers

               if (posi == 0) //cas de grignon
                    {
                        ptrf1=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\grignon\\FDO0000.PER","r+b");
                        ptrf2=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\grignon\\FDO0001.PER","r+b");
                        ptrf3=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\grignon\\FDO0002.PER","r+b");
                    }
                else
                    {
                        ptrf1=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\paris\\FDO0000.PER","r+b");
                        ptrf2=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\paris\\FDO0001.PER","r+b");
                        ptrf3=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\paris\\FDO0002.PER","r+b");
                    }

                if ((ptrf1==NULL)||(ptrf2==NULL)||(ptrf3==NULL))  /* Test si erreur à l’ouverture du fichier */
                    return 0;

                //récupération des données
                LectureDonnees0(ptr1,ptrf1, nblignes, nbcolonnes);
                LectureDonnees0(ptr2,ptrf2, nblignes, nbcolonnes);
                LectureDonnees0(ptr3,ptrf3, nblignes, nbcolonnes);

                // fermeture des fichiers
                fclose(ptrf1);
                fclose(ptrf2);
                fclose(ptrf3);

                printf("\nLes donnees sont extraites");



                /* Calcul de la fréquence, Max de fréquence et Valeurs contrastées*/


                // Déclaration des variables et affectation mémoire



                for(i=0;i<100;i++) // Pourquoi je suis obligé de faire ça pour avoir des 0 à chaque ligne ???
                {
                    Freq1[i]=0;
                    Freq2[i]=0;
                    Freq3[i]=0;
                }


                //Récupération des fréquences

                Frequence(ptr1,Freq1);
                Frequence(ptr2,Freq2);
                Frequence(ptr3,Freq3);

                //Trouver la position avec le maximum de fréquence

                TrouverMax(Freq1,Max1);
                TrouverMax(Freq2,Max2);
                TrouverMax(Freq3,Max3);

                //Récupération chiffres constrastés
                Chiffrecontraste(Freq1,Fcos1);
                Chiffrecontraste(Freq2,Fcos2);
                Chiffrecontraste(Freq3,Fcos3);


                break;
            }

        }

    }while(rep!=6);

    //libération de la mémoire

    for(i=0;i<nblignes;i++)
        free(ptr1[i]);
    free(ptr1);

    for(i=0;i<nblignes;i++)
        free(ptr2[i]);
    free(ptr2);

    for(i=0;i<nblignes;i++)
        free(ptr3[i]);
    free(ptr3);

    free(Freq1);
    free(Freq2);
    free(Freq3);
    free(Fcos1);
    free(Fcos2);
    free(Fcos3);

    printf("\n\n                                 Au-revoir a bientot !\n\n");

    return 0;

}


