/*!==================================================================
Nom      : affichage.cpp
Projet   : mario
Editeur  : Samuel Yanez-Carbonell
===================================================================*/

/// EXEMPLE :
///
///		//initialisation
///		char mon_image[IMAGE_MAX_SIZE];
///     charger_une_image(mon_image, "mon_image.jpg");
///
///		//affichage
///		reset_tab_screen();
///
///			afficher_image(mon_image, 5, 6);
///			afficher_image(mon_image, 20, 30);
///			...
///		afficher_tab_screen();
///


//LES VARIABLES GLOBALES ============================================

char tab_screen[HAUTEUR_FENETRE+2][LARGEUR_FENETRE];
int pos_camera_x;


///LES FONCTIONS ====================================================

// permet d'effacer le contenu du tampon
// d'affichage nommé tab_screen
void reset_tab_screen()
{
    for(int i=0; i<HAUTEUR_FENETRE; i++)
    {
        for(int j=0; j<LARGEUR_FENETRE; j++)
        {
            tab_screen[i][j] = ' ';
        }
    }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// Cette fonction permet de charger une image
// l'image ascii est stocker dans le premier paramètre "image[]"
void charger_une_image(char image[], const char filename[])
{
    FILE* fichier;
    int nb_ligne;
    char chaine[MAX_CHAINE];

    image[0] = '\0';
    strcpy(chaine, "data/image/");
    strcat(chaine, filename);
    if ((fichier = fopen(chaine, "r")) == NULL)
    {
        strcpy(image, chaine);
        strcat(image, "\nintrouvable");
    }
    else
    {
        nb_ligne = 0;
		while(fgets(chaine, (MAX_CHAINE-1), fichier) && (nb_ligne < IMAGE_YMAX))
		{
			int l = strlen(chaine);

			if (l > IMAGE_XMAX)
			{
			    l = IMAGE_XMAX+1;
			    chaine[l-1] = '\n';
			}
			chaine[l] = '\0';

            strcat(image, chaine);

            nb_ligne ++;
		}


		fclose(fichier);
    }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// cette fonction permet d'afficher une image dans le tampon d'affichage
// pour que l'image s'affche a l'écran, il faudra utiliser la fonction
// "afficher_tab_screen".
// les paramètres x, y permette de choisir l'enplacement ou sera afficher
// l'image. les position sont en nombre de caractère
void afficher_image(char image[], int x, int y)
{
    int l = strlen(image);
    int pointeur = 0;

    for(int nb_ligne=y; (pointeur < l); nb_ligne++)
    {
        for(int nb_col=x; ((image[pointeur] != '\n') && (pointeur < l)); nb_col++)
        {
            if ((nb_col >= 0) && (nb_ligne >= 0) && (nb_col < LARGEUR_FENETRE) && (nb_ligne < HAUTEUR_FENETRE))
            {
            	if (image[pointeur] != conf_car_invisible)// conf_car_invisible
                tab_screen[nb_ligne][nb_col] = image[pointeur];
            }
            pointeur++;
        }
        pointeur++;
    }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// cette fonction permet de mettre a jour l'image affiché à lécran dans
// la console avec le contenu du tampon d'affichage tab_screen
void afficher_tab_screen()
{
    char chaine[LARGEUR_FENETRE*(HAUTEUR_FENETRE+2)];
    int pointeur = 0;

    for(int i=0; i<HAUTEUR_FENETRE; i++)
    {
        for(int j=0; j<LARGEUR_FENETRE; j++)
        {
            chaine[pointeur] = tab_screen[i][j];
            pointeur++;
        }

        chaine[pointeur] = '\n';
        pointeur++;
    }
    chaine[pointeur] = '\0';

    system("cls");
    puts(chaine);
    reset_tab_screen();
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// cette fonction permet de rendre plus lisible l'affichage des valeur
// du fichier de config en alignant les chaines sur la meme longueur
char* agrandire_chaine(char chaine[], int longeur_attendu)
{
	char temp[MAX_CHAINE];
	strncpy(temp, chaine, MAX_CHAINE-1);
	temp[MAX_CHAINE-1] = '\0';

	int l = strlen(chaine);
	for(int i=l; i<longeur_attendu; i++)
	{
		temp[i] = ' ';
	}
	temp[longeur_attendu] = '\0';

	return (temp);
}

// permet d'afficher les zero devant le nombre lors de l'affichage
// ex: printf("SCORE : %s%d", afficher_zero(score, 5), score);
char* afficher_zero(int valeur, int nb)
{
	char chaine[MAX_CHAINE];
	int cmpt = 0;
	int temp;


	for(int i=(nb-1); i>=0; i--)
	{
		temp = valeur/pow(10, i);
		if (temp == 0)
		{
			chaine[cmpt] = '0';
			cmpt++;
		}
		else
		{
			i = -1;
		}
	}

	if (valeur > 0)
	{
		chaine[cmpt] = '\0';
	}
	else
	{
		chaine[cmpt-1] = '\0';
	}

	return (chaine);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




