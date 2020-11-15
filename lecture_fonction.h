/**
 * lecture_fonction.h
 * entetes du module de base pour utilisation de la bibliotheque graphique SDL
 * ainsi que les fontions necessaires au programme
 */

/**
 * Création d'un menu à choix
 * Retourne le choix de l'utilisateur ([1-6])
 */

int AffichageMenu();

/**
 * Selection de grignon ou paris
 * Retourne 0 pour grignon et 1 pour paris
 */

int Choix();

/**
 * Récupére et lit les informations du dossier des métadonnées (FDO0003.PER)
 * Affiche l'heure et la date à laquelle les informations ont été enregistré
 * Retourne le nombre de lignes et de colonnes
 */

void LectureMetadonnees(int* nblignes, int* nbcolonnes,int posi);

/**
 * Récupérée les informations des dossiers binaires transmis par le satellite
 * Stock ces données dans un tableau à deux dimensions
 * La taille du tableau correspond au nombre de ligne et de colonne des métadonnées
 */
void LectureDonnees0(int** tab,FILE* ptrf, int nblignes, int nbcolonnes);

/**
 * Calcul la fréquence des chiffres contenu dans les tableaux à deux dimensions
 * réduit à une taille de 200*200.
 * Renvoie un tableau de la fréquence des chiffres
 */

void Frequence(int** ptr,int* freq);

/**
 * Trouve le chiffre avec la fréquence la plus élevé du tableau de fréquence
 * converti ce chiffre pour pouvoir le lire avec %s
 */

void TrouverMax(int* freq, int* cposimax);

/**
 * Créer un tableau indiquant la valeur contrasté d'un chiffre
 */

void Chiffrecontraste(int* freq, int* fcont);




#ifndef LECTURE_FONCTION
#define LECTURE_FONCTION

#define SDL_AVEC_TTF 1
 /* mettre a zero si bibliotheque SDL2_ttf pas disponible */
#define SDL_AVEC_IMG 1
 /* mettre a zero si bibliotheque SDL2_image pas disponible */

#include <SDL2/SDL.h>

#ifndef SDL_VRAI
#define SDL_VRAI 1
#define SDL_FAUX 0
#endif

#define SDL_ERR_INI         1001
#define SDL_ERR_FENETRE     1002
#define SDL_ERR_BOITE_MSG   1003

extern const SDL_Color SDL_SANS_COULEUR ;
extern const SDL_Color SDL_NOIR;
extern const SDL_Color SDL_BLANC;
extern const SDL_Color SDL_ROUGE;
extern const SDL_Color SDL_VERT;
extern const SDL_Color SDL_BLEU;


extern SDL_Window      * SDL_fenetre;  /* fenetre (unique) ouverte avec SDL*/
extern SDL_Renderer    * SDL_rendu;    /* rendu (unique) de la fenetre ouverte avec SDL*/

/* SDL_AVEC_TTF : ecriture de texte avec SDL2_ttf
   ---------------------------------------------------------------------------*/

#if SDL_AVEC_TTF

#include <SDL2/SDL_ttf.h>

#define SDL_TTF_DOSSIER_POLICE  "C:/Windows/Fonts/"
 /* chemin du dossier des polices, avec / a la fin */
#define SDL_TTF_CHEMIN_FICHIER_POLICE  SDL_TTF_DOSSIER_POLICE"arial.ttf"
 /* chemin du fichier de police de caractere implicite */
#define SDL_TTF_TAILLE          24
 /* taille de caractere implicite */
#define SDL_TTF_ERR_INI         2001
#define SDL_TTF_ERR_FONTE       2002

typedef TTF_Font SDL_FONT;

#else

typedef void * SDL_FONT;

#endif /* SDL_AVEC_TTF  ------------------------------------------------------*/

extern SDL_FONT         * SDL_fonte;     /* fonte courante de caractere pour le dessin */


/* SDL_AVEC_IMG : affichage d'image avec SDL2_image
   ---------------------------------------------------------------------------*/

#if SDL_AVEC_IMG

#include <SDL2/SDL_image.h>

#define SDL_IMG_ERR_INI     3001
#define SDL_IMG_FORMATS     ( IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF )

#endif /* SDL_AVEC_IMG -------------------------------------------------------*/

/**
 * production d'un message en trace avec SDL.
 */
extern void SDL_Trace(const char * texte);

/**
 * renvoi la fonte (police de caracteres d'une taille donnee)
 * a partir du fichier et de la taille donnees,
 * si anomalie renvoi de NULL ou si pas SDL_AVEC_TTF.
 */
extern SDL_FONT * SDL_ChargerFonte(const char * chemin_fichier_police, int taille_texte);

/**
 * initialisation de l'affichage avec SDL,
 * et de la production de texte si SDL_AVEC_TTF,
 * et de la gestion d'image (PNG/JPG/TIFF) si SDL_AVEC_IMG,
 * indication optionnelle du chemin de fichier de la police (ou NULL)
 * et de la taille pour les textes (ou 0),
 * avec valeurs implicites SDL_TTF_CHEMIN_FICHIER_POLICE et SDL_TTF_TAILLE,
 * arret (et trace) si anomalie.
 */
extern int SDL_Depart(const char * chemin_fichier_police, int taille_texte);

/**
 * arret de l'affichage avec SDL et TTF,
 * sortie du programme avec le code indique.
 */
extern void SDL_Arret(int code);

/**
 * arret de l'affichage avec SDL,
 * @date 2020-11-05
 */
void SDL_Fermer();

/**
 * creation d'une fenetre avec titre, hauteur et largeur (en pixels),
 * pour un dessin en blanc sur fond noir,
 * SDL_fenetre pointe vers la fenetre creee et
 * SDL_Rendu vers le rendu associe,
 * sinon arret sur anomalie.
 */
extern void SDL_CreerFenetreRendu(const char * titre, int largeur, int hauteur);

/**
 * affichage d'un message dans une boite de dialogue,
 * avec en option fixation de son titre et du libelle de validation
 * (valeurs implicites si NULL).
*/
extern void SDL_BoiteMsg(const char * message, const char * titre, const char * libelleValidation);


/**
 * effacer tout le contenu du rendu
 * selon la couleur de trace courante.
 */
extern void SDL_EffacerRendu();

/**
 * renvoi de la couleur courante de dessin
 */
extern SDL_Color SDL_CouleurDessin();

/**
 * changer la couleur de dessin
 */
extern void SDL_ChangerCouleurDessin(SDL_Color couleur);

/**
 * comparaison des deux couleurs donnees,
 * renvoi 1 si identiques, 0 sinon.
 */
extern int SDL_EgaliteCouleur(SDL_Color couleur1, SDL_Color couleur2);

/**
 * dessiner un point en (x, y),
 * selon la couleur indiquee ou si SDL_SANS_COULEUR la couleur courante.
 */
extern void SDL_DessinerPoint(int x, int y, SDL_Color couleur);

/**
 * dessiner une ligne du point en (x1, y1) vers (x2, y2)
 * selon la couleur indiquee ou si SDL_SANS_COULEUR la couleur courante.
 */
extern void SDL_DessinerLigne(int x1, int y1, int x2, int y2, SDL_Color couleur);

/**
 * dessiner un cadre de rectangle en (x, y) avec largeur x hauteur pixels
 * selon la couleur indiquee ou si SDL_SANS_COULEUR la couleur courante.
 */
extern void SDL_DessinerCadreRectangle(int x, int y, int largeur, int hauteur, SDL_Color couleur);

/**
 * dessiner un fond de rectangle en (x, y) avec largeur x hauteur pixels
 * selon la couleur indiquee ou si SDL_SANS_COULEUR la couleur courante.
 */
extern void SDL_DessinerFondRectangle(int x, int y, int largeur, int hauteur, SDL_Color couleur);

/**
 * determination de la position courante de la souris,
 * resultats via les pointeurs en parametres.
 */
extern void SDL_PositionSouris(int * ptrX, int * ptrY);

/**
 * attente du prochain evenement,
 * resultat via le pointeur en parametre.
 */
extern void SDL_AttendreEvent(SDL_Event * ptrEvenement);

/**
 * renvoi du texte de la touche frappee au clavier,
 * sous la forme d'une chaine de caracteres contenant
 * soit un seul caractere ASCII comme "M",
 * soit une ou plusieurs notations de code hexadecimauxcomme
 * a partir de l'evenement associe en parametre,
 * resultat avec le pointeur vers le texte.
 */
extern char * SDL_TexteClavier(SDL_Event ptr_event);

/**
 * ACTION EFFECTIVE SEULEMENT SI TTF
 * ecriture d'un message sur le rendu de la fenetre,
 * selon les coordonnees indiquees et
 * la fonte indiquee ou si NULL la fonte courante,
 * la couleur indiquee ou si SDL_SANS_COULEUR la couleur courante.
 * et selon les police et taille courantes.
 * @date 2020-11-06
 */
extern void SDL_EcrireTexte(const char * message, int x_origine, int y_origine, SDL_FONT * fonte, SDL_Color couleur);

/**
 * ACTION EFFECTIVE SEULEMENT SI SDL_AVEC_IMG
 * affichage d'une image sur le rendu de la fenetre,
 * au format PNG ou JPG ou TIFF,
 * selon les coordonnees indiquees,
 * Avertissement possible à ignorer en cas d'image PNG :
 *  "libpng warning: iCCP: known incorrect sRGB profile".
 */
extern void SDL_AfficherImage(const char * chemin_fichier_image, int x_origine, int y_origine);


#endif
