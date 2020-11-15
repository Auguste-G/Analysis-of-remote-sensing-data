#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lecture_fonction.h"

const SDL_Color SDL_SANS_COULEUR = {-1, -1, -1, -1};
const SDL_Color SDL_NOIR  = {0, 0, 0, 255};
const SDL_Color SDL_BLANC = {255, 255, 255, 255};
const SDL_Color SDL_ROUGE = {255, 0, 0, 255};
const SDL_Color SDL_VERT  = {0, 255, 0, 255};
const SDL_Color SDL_BLEU  = {0, 0, 255, 255};

/**
 * Création d'un menu à choix
 * Retourne le choix de l'utilisateur ([1-6])
 */

int AffichageMenu()
{
    char rep ='\0';

    printf("\n                            ######-Bienvenu dans le menu-######\n");
    printf("                            | 1 : Image normale               |\n");
    printf("                            | 2 : Histogrammes                |\n");
    printf("                            | 3 : Image contrastee            |\n");
    printf("                            | 4 : Image DVI contrastee        |\n");
    printf("                            | 5 : Changer de lieu             |\n");
    printf("                            | 6 : Sortir du programme         |\n");
    printf("                            |                                 |\n");

    printf("                            | Veuillez faire un choix :  ");
    while((rep=getche())<'1' || rep > '6') putch('\a');
        {
        printf("    |\n                            ###################################\n\n");
        return (rep-'0');
        }

}

/**
 * Selection de grignon ou paris
 */
int Choix()
{
    char posi='\0';
    printf("                            Veuillez choisir une destination");
    printf("\n\n                                       0 = Grigron");
    printf("\n                                       1 = Paris");
    printf("\n\n                                     Votre choix :");
    while((posi=getche())<'0' || posi > '1') putch('\a');
        return (posi-'0');

}

/**
 * Récupére les informations du dossier des métadonnées (FDO0003.PER)
 * Affiche l'heure et la date à laquelle les informations ont été enregistré
 * Retourne le nombre de lignes et de colonnes
 */

void LectureMetadonnees(int* nblignes, int* nbcolonnes,int posi)
{
    char date[11], heure[9];

    int y = 0, x =0;
    FILE *ptrf=NULL; /* définition d’un pointeur pour pointer sur le début du fichier à lire */

    if (posi == 0)
        ptrf=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\grignon\\FDO0003.PER","r+b"); /*ouverture du fichier binaire “b” en lecture “r” */
    else
        ptrf=fopen("C:\\Users\\Gardette\\Documents\\APT\\2A\\progammer en C\\Premier_Programme\\test-metadonnées\\paris\\FDO0003.PER","r+b");

    if (ptrf==NULL) {
            printf("NON");
      //  return ;
    }

    fseek(ptrf,160,SEEK_SET);
    /*positionnement du pointeur sur les données à récupérer. On se
    déplace de 160 octets à partir du début du fichier SEEK_SET
    pour pouvoir lire le 161ème octet */

    fread(&y,1,2,ptrf); /* lecture du nombre de lignes : octets 161 et 162 */

    fread(&x,1,2,ptrf);/* idem pour nbcolonnes: octets 163 et 164 */

    fseek(ptrf,92,SEEK_SET); /* lecture de l’heure */
    fread(heure,1,8,ptrf);
    heure[8]='\0';

    fseek(ptrf,72,SEEK_SET);/* lecture de la date à définir */
    fread(date,1,10,ptrf);
    date[10]='\0';

    printf("\n\nLecture des metadonnees\n\n");
    printf("On est le jour %s a l'heure %s\n",date, heure);
    printf("Le document contient %d lignes et %d colonnes\n\n", y, x);

    //Return des valeurs des lignes et colonnes

    *nblignes = y;
    *nbcolonnes = x;

}

/**
 * Récupérée les informations des dossiers binaires transmis par le satellite
 * Stock ces données dans un tableau à deux dimensions
 * La taille du tableau correspond au nombre de ligne et de colonne des métadonnées
 */

void LectureDonnees0(int** tab,FILE* ptrf, int nblignes, int nbcolonnes)
{
    int mesure=0, k = 0, l = 0, i = 0, j = 0, A =0, Z =0, c = 16,X =0;

    nbcolonnes --;
    nblignes --;

    fseek(ptrf,1280,SEEK_SET);

    while(l<nblignes)//défile les carrés en colonne
        {
            while(k<nbcolonnes) // défile les carrés lignes
            {
                for( i=0; i<c; i++) // défile les colonnes
                {
                    for( j=0; j<c; j++) // défile les lignes
                    {

                        fread(&mesure,1,1,ptrf);
                        tab[l][k]=mesure;
                        Z++;
                        if (k<nbcolonnes)
                            k++;
                        else
                            j=c;

                    }

                    //Test si fin de la carte
                    if ((l==(nblignes)&&(k==nbcolonnes)))
                        i=c;

                    //Test si on a atteint la limite inferieur de la carte
                    else if((l==(nblignes)&&(k<nbcolonnes)))
                    {
                        l -= (l%c);
                        i = c;
                        X = Z % 256;
                        X = 256 - X;
                        Z = Z + X;
                        fseek(ptrf,1280+Z,SEEK_SET);

                    }

                    //Test si on est en bout de ligne de la carte à droite
                    else if ((k==nbcolonnes)&&((l+1)%c!=0))
                    {
                        k -= (k%c);
                        l++;
                        X = Z%16;
                        X = 16 - X;
                        Z = Z + X;
                        fseek(ptrf,1280+Z,SEEK_SET);
                    }

                    //Test si on est en fin d'une ligne de carré à droite
                    else if ((k==nbcolonnes)&&((l+1)%c==0))
                    {
                           i = c;
                           l++;
                           A = l;
                           k = 0;
                           X = Z%256;
                           X = 256 - X;
                           Z = Z + X;
                           fseek(ptrf,1280+Z,SEEK_SET);
                    }

                    //Fin de ligne d'un carré
                    else if ((k<nbcolonnes)&&((l+1)%c!=0)) // Bout de ligne d'un carré
                    {
                        k -= c;
                        l++;
                    }

                    //Fin d'un carré
                    else if ((k<nbcolonnes)&&((l+1)%c==0)) // Dernière bout de ligne d'un carré
                    {
                        i =c;
                        l++;
                        l -= c;

                    }
                }
            }
        }
}

/**
 * Calcul la fréquence des chiffres contenu dans les tableaux à deux dimensions
 * réduit à une taille de 200*200.
 * Renvoie un tableau de la fréquence des chiffres
 */

void Frequence(int** ptr,int* freq)
{
    int i=0, j = 0,c = 0;

    for(i=0;i<200;i++)
    {
        for(j=0;j<200;j++)
        {
            c = ptr[i][j];
            freq[c]++;
        }
    }

}

/**
 * Trouve le chiffre avec la fréquence la plus élevé du tableau de fréquence
 * converti ce chiffre pour pouvoir le lire avec %s
 */

void TrouverMax(int* freq,int* cposimax)
{
    int i = 0, j = 0, nbmax =0, posimax = 0;

    for (i=0;i<100;i++)
    {
        if((freq[i]>nbmax)&&(freq[i]<10000))
        {
            nbmax = freq[i];
            posimax = i;
        }
    }

    sprintf(cposimax,"%d", posimax);

}

/**
 * Créer un tableau indiquant la valeur contrasté d'un chiffre
 */

void Chiffrecontraste(int* freq, int* fcont)
{
    int i = 0, x =0, k = 0;

    for(i=0;i<100;i++)
    {
        if(freq[i]<10000)
            k += freq[i];
        x = ((k*255)/(200*200));
        fcont[i] = x;
    }
}


/** Partir SDL */

SDL_Window      * SDL_fenetre = NULL;    /* fenetre (unique) ouverte avec SDL*/
SDL_Renderer    * SDL_rendu   = NULL;    /* rendu (unique) de la fenetre ouverte avec SDL*/
SDL_FONT        * SDL_fonte   = NULL;     /* fonte courante de caractere pour le dessin */

/*
 * migration de SDL a SDL 2
 *  https://wiki.libsdl.org/MigrationGuide
 *  surface (stockee dans la memoire principale, RAM)  => texture (stockee dans la carte graphique)
 *  https://www.freepascal-meets-sdl.net/chapter-7-texts-fonts-surface-conversion/
 */

/**
 * production d'un message en trace avec SDL.
 * @date 2020-10-28
 */
void SDL_Trace(const char * texte)
{
    /* SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, texte); */
    SDL_Log(texte);
}

/**
 * renvoi la fonte (police de caracteres d'une taille donnee)
 * a partir du fichier et de la taille donnees,
 * si anomalie renvoi de NULL ou si pas SDL_AVEC_TTF.
 * @date 2020-11-07
 */
SDL_FONT * SDL_ChargerFonte(const char * chemin_fichier_police, int taille_texte)
{
#if SDL_AVEC_TTF
    return TTF_OpenFont(chemin_fichier_police, taille_texte);
#else
    return NULL;
#endif
}

/**
 * initialisation de l'affichage avec SDL,
 * et de la production de texte si SDL_AVEC_TTF,
 * et de la gestion d'image (PNG/JPG/TIFF) si SDL_AVEC_IMG,
 * indication optionnelle du chemin de fichier de la police (ou NULL)
 * et de la taille pour les textes (ou 0),
 * avec valeurs implicites SDL_TTF_CHEMIN_FICHIER_POLICE et SDL_TTF_TAILLE,
 * arret (et trace) si anomalie.
 * @date 2020-11-07
 */
int SDL_Depart(const char * chemin_fichier_police, int taille_texte)
{
    char texte[200] = "?";
    int code = 0;

    /* initialisation globale de SDL */
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        sprintf(texte, "Initialisation impossible de SDL (%s)\n", SDL_GetError() );
        code = SDL_ERR_INI;
    }
#if SDL_AVEC_TTF
    if (0 == code) {
        if ( TTF_Init() < 0 ) {
            sprintf(texte, "Initialisation impossible de TTF (%s)\n", TTF_GetError() );
            code = SDL_TTF_ERR_INI;
        } else {
            /* parametres en option **/
            char chemin_fichier[100] = SDL_TTF_CHEMIN_FICHIER_POLICE;

            if (NULL != chemin_fichier_police) {
                strcat(chemin_fichier, chemin_fichier_police);
            }
            if (0 == taille_texte) {
                taille_texte = SDL_TTF_TAILLE;
            }
            /* initialisation de la police de caractere avec SDL2_ttf */
            SDL_fonte = SDL_ChargerFonte(chemin_fichier, taille_texte);
            if (NULL == SDL_fonte) {
                sprintf(texte, "Initialisation impossible de la fonte dans %s (%s)\n", chemin_fichier_police, TTF_GetError() );
                code = SDL_TTF_ERR_FONTE;
            }
        }
    }
#endif
#if SDL_AVEC_IMG
    if (0 == code) {
        /* initialisation de gestion d'image avec SDL2_image */
        int retour = 0, drapeaux_image = SDL_IMG_FORMATS;

        retour = IMG_Init(drapeaux_image) & drapeaux_image;
        if (retour != drapeaux_image) {
            sprintf(texte, "Initialisation impossible de la prise en charge d'image (%s)\n", IMG_GetError());
            code = SDL_IMG_ERR_INI;
        }
    }
#endif
    if (0 != code) {
        if (SDL_ERR_INI == code) {
            printf(texte);
            exit(code);
        } else {
            SDL_Trace(texte);
            SDL_Arret(code);
        }
     }
}

/**
 * arret de l'affichage avec SDL,
 * sortie du programme avec le code indique.
 * @date 2020-11-05
 */
void SDL_Arret(int code)
{
    if (NULL != SDL_fenetre) {
        SDL_DestroyWindow(SDL_fenetre);
    }
    if (NULL != SDL_rendu) {
        SDL_DestroyRenderer(SDL_rendu);
    }
#if SDL_AVEC_TTF
    TTF_CloseFont(SDL_fonte);
    TTF_Quit();
#endif
#if SDL_AVEC_IMG
    IMG_Quit();
#endif
    SDL_Quit();
    exit(code);
}

/**
 * arret de l'affichage avec SDL,
 * @date 2020-11-05
 */
void SDL_Fermer()
{
    if (NULL != SDL_fenetre) {
        SDL_DestroyWindow(SDL_fenetre);
    }
    if (NULL != SDL_rendu) {
        SDL_DestroyRenderer(SDL_rendu);
    }
#if SDL_AVEC_TTF
    TTF_CloseFont(SDL_fonte);
    TTF_Quit();
#endif
#if SDL_AVEC_IMG
    IMG_Quit();
#endif
    SDL_Quit();
}

/**
 * creation d'une fenetre avec titre, hauteur et largeur (en pixels),
 * pour un dessin en blanc sur fond noir,
 * SDL_fenetre pointe vers la fenetre creee et
 * SDL_Rendu vers le rendu associe,
 * sinon arret sur anomalie.
 * @date 2020-11-05
 */

void SDL_CreerFenetreRendu(const char * titre, int largeur, int hauteur)
{
    SDL_Window * fenetre;
    SDL_Renderer * rendu;
    char texte[200];

    SDL_fenetre = NULL;
    SDL_rendu = NULL;
    if ( SDL_CreateWindowAndRenderer(largeur, hauteur, 0, & fenetre, & rendu) < 0 ) {
        sprintf( texte, "Creation impossible de fenetre avec rendu, en %u x %u (%s)\n",
                 largeur, hauteur, SDL_GetError() );
        SDL_Trace(texte);
        SDL_Arret(SDL_ERR_FENETRE);
    }
    SDL_fenetre = fenetre;
    SDL_rendu = rendu;
    /* fixation du titre de la fenetre */
    SDL_SetWindowTitle(SDL_fenetre, titre);
    /* ecriture sur le rendu en blanc sur fond noir */
    SDL_SetRenderDrawColor(SDL_rendu, 0, 0, 0, 0);
    SDL_RenderClear(SDL_rendu);
    SDL_SetRenderDrawColor(SDL_rendu, 255, 255, 255, 255);
    SDL_RenderPresent(SDL_rendu);
}

/**
 * affichage d'un message dans une boite de dialogue,
 * avec en option fixation de son titre et du libelle de validation
 * (valeurs implicites si NULL).
 * @date 2020-11-05
 */
void SDL_BoiteMsg(const char * message, const char * titre, const char * libelleValidation)
{
    char texte_titre[100] = "Information", texte_libelle[100] = "Continuer";
    int idBouton;

    /* parametres en option **/
    if (NULL != titre) {
        strcpy(texte_titre, titre);
    }
    if (NULL != libelleValidation) {
        strcpy(texte_libelle, libelleValidation);
    }
    /* construction de la boite */
    const SDL_MessageBoxButtonData boutons[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, texte_libelle }
    };
    const SDL_MessageBoxData parametres = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        texte_titre, /* .title */
        message, /* .message */
        SDL_arraysize(boutons), /* .numbuttons */
        boutons, /* .buttons */
        NULL /* .colorScheme */
    };
    /* affichage de la boite */
    if ( SDL_ShowMessageBox( & parametres, & idBouton) < 0 ) {
        SDL_Trace("anomalie en affichage du message");
        SDL_Arret(SDL_ERR_BOITE_MSG);
    }
}


/**
 * effacer tout le contenu du rendu,
 * selon la couleur de trace courante.
 * @date 2020-11-06
 */
void SDL_EffacerRendu()
{
    SDL_RenderClear(SDL_rendu);
}

/**
 * renvoi de la couleur courante de dessin
 * @date 2020-11-07
 */
SDL_Color SDL_CouleurDessin()
{
    char texte[100]= "";
    SDL_Color couleur;

    if ( 0 != SDL_GetRenderDrawColor(SDL_rendu, & couleur.r, & couleur.g, & couleur.b, & couleur.a) ) {
        sprintf( texte, "acquisition de le couleur courante impossible (%s)\n", SDL_GetError() );
        SDL_Trace(texte);
    }
    return couleur;
}

/**
 * changer la couleur de dessin
 * @date 2020-11-06
 */
void SDL_ChangerCouleurDessin(SDL_Color couleur)
{
    char texte[100]= "";

    if ( 0 != SDL_SetRenderDrawColor(SDL_rendu, couleur.r, couleur.g, couleur.b, couleur.a) ) {
        sprintf( texte, "changement de couleur {%d, %d, %d, %d} impossible (%s)\n",
                 couleur.r, couleur.g, couleur.b, couleur.a, SDL_GetError() );
        SDL_Trace(texte);
    }
}

/**
 * comparaison des deux couleurs donnees,
 * renvoi SDL_VRAI si identiques, SDL_FAUX sinon.
 * @date 2020-11-07
 */
int SDL_EgaliteCouleur(SDL_Color couleur1, SDL_Color couleur2)
{
    return ( couleur1.r == couleur2.r
          && couleur1.g == couleur2.g
          && couleur1.b == couleur2.b
          && couleur1.a == couleur2.a ) ? SDL_VRAI : SDL_FAUX;
}

/**
 * dessiner un point en (x, y),
 * selon la couleur indiquee ou si SDL_SANS_COULEUR la couleur courante.
 * @date 2020-11-07
 */
void SDL_DessinerPoint(int x, int y, SDL_Color couleur)
{
    SDL_Color couleur_anterieure ;
    int bascule = 0;

    bascule = ( SDL_FAUX == SDL_EgaliteCouleur(SDL_SANS_COULEUR, couleur)  );
    if (bascule) {
        /* basculement de couleur */
        couleur_anterieure = SDL_CouleurDessin();
        SDL_ChangerCouleurDessin(couleur);
    }
    SDL_RenderDrawPoint(SDL_rendu, x, y);
    if (bascule) {
        /* retour a la couleur anterieure */
        SDL_ChangerCouleurDessin(couleur_anterieure);
    }
    SDL_RenderPresent(SDL_rendu);
}

/**
 * dessiner une ligne du point en (x1, y1) vers (x2, y2)
 * selon la couleur indiquee ou si SDL_SANS_COULEUR la couleur courante.
 * @date 2020-11-07
 */
void SDL_DessinerLigne(int x1, int y1, int x2, int y2, SDL_Color couleur)
{
    SDL_Color couleur_anterieure ;
    int bascule = 0;

    bascule = ( SDL_FAUX == SDL_EgaliteCouleur(SDL_SANS_COULEUR, couleur)  );
    if (bascule) {
        /* basculement de couleur */
        couleur_anterieure = SDL_CouleurDessin();
        SDL_ChangerCouleurDessin(couleur);
    }
    SDL_RenderDrawLine(SDL_rendu, x1, y1, x2, y2);
    if (bascule) {
        /* retour a la couleur anterieure */
        SDL_ChangerCouleurDessin(couleur_anterieure);
    }
    SDL_RenderPresent(SDL_rendu);
}

/**
 * dessiner un cadre de rectangle en (x, y) avec largeur x hauteur pixels
 * selon la couleur indiquee ou si SDL_SANS_COULEUR la couleur courante.
 * @date 2020-11-07
 */
void SDL_DessinerCadreRectangle(int x, int y, int largeur, int hauteur, SDL_Color couleur)
{
    SDL_Rect rectangle = {x, y, largeur, hauteur};
    SDL_Color couleur_anterieure ;
    int bascule = 0;

    bascule = ( SDL_FAUX == SDL_EgaliteCouleur(SDL_SANS_COULEUR, couleur)  );
    if (bascule) {
        /* basculement de couleur */
        couleur_anterieure = SDL_CouleurDessin();
        SDL_ChangerCouleurDessin(couleur);
    }
    SDL_RenderDrawRect(SDL_rendu, & rectangle);
    if (bascule) {
        /* retour a la couleur anterieure */
        SDL_ChangerCouleurDessin(couleur_anterieure);
    }
    SDL_RenderPresent(SDL_rendu);
}

/**
 * dessiner un fond de rectangle en (x, y) avec largeur x hauteur pixels
 * selon la couleur indiquee ou si SDL_SANS_COULEUR la couleur courante.
 * @date 2020-11-07
 */
void SDL_DessinerFondRectangle(int x, int y, int largeur, int hauteur, SDL_Color couleur)
{
    SDL_Rect rectangle = {x, y, largeur, hauteur};
    SDL_Color couleur_anterieure ;
    int bascule = 0;

    bascule = ( SDL_FAUX == SDL_EgaliteCouleur(SDL_SANS_COULEUR, couleur)  );
    if (bascule) {
        /* basculement de couleur */
        couleur_anterieure = SDL_CouleurDessin();
        SDL_ChangerCouleurDessin(couleur);
    }
    SDL_RenderFillRect(SDL_rendu, & rectangle);
    if (bascule) {
        /* retour a la couleur anterieure */
        SDL_ChangerCouleurDessin(couleur_anterieure);
    }
    SDL_RenderPresent(SDL_rendu);
}

/**
 * determination de la position courante de la souris,
 * resultats via les pointeurs en parametres.
 * @date 2020-10-28
 */
void SDL_PositionSouris(int * ptrX, int * ptrY)
{
    SDL_GetMouseState(ptrX, ptrY);
}

/**
 * attente du prochain evenement,
 * resultat via le pointeur en parametre.
 * @date 2020-10-28
 */
void SDL_AttendreEvent(SDL_Event * ptrEvenement)
{
    SDL_WaitEvent(ptrEvenement);
}

/**
 * renvoi du texte de la touche frappee au clavier,
 * sous la forme d'une chaine de caracteres contenant
 * soit un seul caractere ASCII comme "M",
 * soit une ou plusieurs notations de code hexadecimauxcomme
 * a partir de l'evenement associe en parametre,
 * resultat avec le pointeur vers le texte.
 * @date 2020-11-07
 */
char * SDL_TexteClavier(SDL_Event ptr_event)
{
    char * ptr_texte = "", * ptr_car = '\0';
    int taille_texte_lu = 0, taille_texte_hexa = 0;
    size_t longueur = 0;

    taille_texte_lu = strlen(ptr_event.text.text);
    if ( 1 == taille_texte_lu  &&  128 > * ptr_event.text.text ) {
        /* simple symbole ASCII */
        ptr_texte = malloc(2);
        strcpy(ptr_texte, ptr_event.text.text);
    } else {
        /* symbole pas ASCII, sans doute Unicode -> \x....
           source : PrintText() dans checkkeys.c  de SDL2, test */
        taille_texte_hexa = taille_texte_lu * 6 + 1;
        ptr_texte = malloc( taille_texte_hexa * sizeof(char) );
        memset(ptr_texte, '\0', taille_texte_hexa);
        for ( ptr_car = ptr_event.text.text; * ptr_car; ++ ptr_car ) {
            longueur = SDL_strlen(ptr_texte);
            sprintf(ptr_texte + longueur, "\\x%.2X", (unsigned char) * ptr_car);
            /* SDL_snprintf(ptr_texte + longueur, sizeof(ptr_texte) - longueur, ); */
        }
    }
    return ptr_texte;
}

/**
 * ACTION EFFECTIVE SEULEMENT SI TTF
 * ecriture d'un message sur le rendu de la fenetre,
 * selon les coordonnees indiquees et
 * la fonte indiquee ou si NULL la fonte courante,
 * la couleur indiquee ou si SDL_SANS_COULEUR la couleur courante.
 * et selon les police et taille courantes.
 * @date 2020-11-07
 */
void SDL_EcrireTexte(const char * message, int x_origine, int y_origine, SDL_FONT * fonte, SDL_Color couleur)
{
#if SDL_AVEC_TTF
    SDL_Surface * surface_texte;
    SDL_Texture * texture_texte;
    SDL_Rect position;
    char texte[200];

    if ( SDL_VRAI == SDL_EgaliteCouleur(SDL_SANS_COULEUR, couleur) ) {
        /* couleur implicite */
        couleur = SDL_CouleurDessin();
    }
    if (NULL == fonte){
        fonte = SDL_fonte;
    }
    surface_texte = TTF_RenderText_Blended(fonte, message, couleur);
    if (NULL == surface_texte) {
        sprintf( texte, "Anomalie de SDL_EcrireTexte (surface : %s)\n", TTF_GetError() );
        SDL_Trace(texte);
    } else {
        /* https://www.freepascal-meets-sdl.net/chapter-7-texts-fonts-surface-conversion/ */
        texture_texte = SDL_CreateTextureFromSurface(SDL_rendu, surface_texte);
        if (NULL == texture_texte) {
            sprintf( texte, "Anomalie de SDL_EcrireTexte (texture : %s)\n", TTF_GetError() );
            SDL_Trace(texte);
        } else {
            SDL_QueryTexture(texture_texte, NULL, NULL, & position.w, & position.h);
            position.x = x_origine;
            position.y = y_origine;
            SDL_RenderCopy(SDL_rendu, texture_texte, NULL, & position);
            SDL_RenderPresent(SDL_rendu);
            SDL_DestroyTexture(texture_texte);
        }
        SDL_FreeSurface(surface_texte);
    }
#endif
}

/**
 * ACTION EFFECTIVE SEULEMENT SI SDL_AVEC_IMG
 * affichage d'une image sur le rendu de la fenetre,
 * au format PNG ou JPG ou TIFF,
 * selon les coordonnees indiquees,
 * Avertissement possible à ignorer en cas d'image PNG :
 *  "libpng warning: iCCP: known incorrect sRGB profile".
 * @date 2020-11-05
 */
void SDL_AfficherImage(const char * chemin_fichier_image, int x_origine, int y_origine)
{
#if SDL_AVEC_IMG
    SDL_Surface * surface_image;
    SDL_Texture * texture_image;
    SDL_Rect position;
    char texte[200];

    surface_image = IMG_Load(chemin_fichier_image);
    if (NULL == surface_image) {
        sprintf( texte, "Anomalie de SDL_AfficherImage (chargement : %s)\n", IMG_GetError() );
        SDL_Trace(texte);
    } else {
        texture_image = SDL_CreateTextureFromSurface(SDL_rendu, surface_image);
        if (NULL == texture_image) {
            sprintf( texte, "Anomalie de SDL_EcrireTexte (texture : %s)\n", TTF_GetError() );
            SDL_Trace(texte);
        } else {
            SDL_QueryTexture(texture_image, NULL, NULL, & position.w, & position.h);
            position.x = x_origine;
            position.y = y_origine;
            sprintf(texte, "image %s : %u x %u pixels\n", chemin_fichier_image, position.w, position.h);
            SDL_Trace(texte);
            SDL_RenderCopy(SDL_rendu, texture_image, NULL, & position);
            SDL_RenderPresent(SDL_rendu);
            SDL_DestroyTexture(texture_image);
        }
        SDL_FreeSurface(surface_image);
    }
#endif
}

/* fin */


