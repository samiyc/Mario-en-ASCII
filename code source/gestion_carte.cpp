/*!==================================================================
Nom      : gestion_carte.cpp
Projet   : mario
Editeur  : Samuel Yanez-Carbonell
===================================================================*/

/// EXEMPLE :
///
///		//initialisation
///		chargement_de_la_map();
///		charger_les_images_pour_la_map();
///
///		//affichage
///		reset_tab_screen();
///
///			afficher_zone_courante(20);
///
///		afficher_tab_screen();
///


//LES VARIABLES GLOBALES ============================================

char tab_map[NB_LONGEUR_NIV_MAX][NB_BLOC_HAUTEUR];
int longeur_map;

//les images de la carte
char img_map_sol   [IMAGE_MAX_SIZE];
char img_map_caisse[IMAGE_MAX_SIZE];
char img_map_or    [IMAGE_MAX_SIZE];
char img_map_check [IMAGE_MAX_SIZE];
char img_map_nuage [IMAGE_MAX_SIZE];
char img_map_decor [IMAGE_MAX_SIZE];
char img_map_monstre_1[IMAGE_MAX_SIZE];
char img_map_monstre_2[IMAGE_MAX_SIZE];
char img_map_monstre_3[IMAGE_MAX_SIZE];
char img_map_monstre_carapace[IMAGE_MAX_SIZE];


///LES FONCTIONS ====================================================

// Cette fonction permet de charger le fichier map.txt
// dans le tableau tab_map
void chargement_de_la_map()
{
	FILE* fichier;
	char chaine[MAX_CHAINE];
	int pointeur;


	if ((fichier = fopen("./data/map.txt", "r")) == NULL)
	{
		printf("\n\n   ERREUR DE LECTURE DU FICHIER MAP.TXT");
	}
	else
	{
		pointeur = -1;
		while(fgets(chaine, (MAX_CHAINE-1), fichier) && (pointeur < NB_LONGEUR_NIV_MAX))
		{
			pointeur++;
			int l = strlen(chaine);
			chaine[l] = '\0';

			for(int i=0; i<NB_BLOC_HAUTEUR; i++)
			{
				tab_map[pointeur][i] = chaine [i];
			}
		}
		longeur_map = pointeur;
		fclose(fichier);
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// Cette fonction regroupe le chargement des différentes images
// permettant d'afficher la carte a l'écran (monstre, nuage, deco...)
void charger_les_images_pour_la_map()
{
	charger_une_image(img_map_sol   , "map/sol.txt");
	charger_une_image(img_map_caisse, "map/caisse.txt");
	charger_une_image(img_map_or    , "map/or.txt");
	charger_une_image(img_map_check , "map/check.txt");
	charger_une_image(img_map_nuage , "map/nuage.txt");
	charger_une_image(img_map_decor , "map/decor.txt");
	charger_une_image(img_map_monstre_1 , "map/monstre1.txt");
	charger_une_image(img_map_monstre_2 , "map/monstre2.txt");
	charger_une_image(img_map_monstre_3 , "map/monstre3.txt");
	charger_une_image(img_map_monstre_carapace , "map/carapace.txt");
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet d'afficher dans le tampon d'affichage tab_screen les différentes
// images qui compose la carte a un endroit donné
// la position de la camera est un décalage en nombre de caractère
// par rapport au début de la partie
void afficher_zone_courante(int position_camera)
{
	int x_tab = position_camera / BLOC_SIZE;
	int xdecal = position_camera % BLOC_SIZE;

	int x_cam, y_cam;

	for(int i=x_tab; ((i<(NB_BLOC_LARGEUR+x_tab)) && (i<longeur_map)); i++)
	{
		x_cam = (i-x_tab)*BLOC_SIZE - xdecal;

		for(int j=0; j<NB_BLOC_HAUTEUR; j++)
		{
			y_cam = HAUTEUR_FENETRE - BLOC_SIZE*j - BLOC_SIZE;

			char c = tab_map[i][j];
			char img_temp[IMAGE_MAX_SIZE];
			int no_paint = 0;

			if (c == conf_car_sol)
			{
				strcpy(img_temp, img_map_sol);
			}
			else if (c == conf_car_caisse)
			{
				//strcpy(img_temp, img_map_caisse);
				new_evenement(E_CAISSE, x_cam, y_cam);
				tab_map[i][j] = ' ';
				no_paint = 1;
			}
			else if (c == conf_car_or)
			{
				//strcpy(img_temp, img_map_or);
				new_evenement(E_OR, x_cam, y_cam);
				tab_map[i][j] = ' ';
				no_paint = 1;
			}
			else if (c == conf_car_check)
			{
				//strcpy(img_temp, img_map_or);
				new_evenement(E_CHECK, x_cam, y_cam);
				tab_map[i][j] = ' ';
				no_paint = 1;
			}
			else if (c == conf_car_nuage)
			{
				strcpy(img_temp, img_map_nuage);
			}
			else if (c == conf_car_decor)
			{
				strcpy(img_temp, img_map_decor);
			}
			else if (c == conf_car_monstre_1)
			{
				//strcpy(img_temp, img_map_monstre_1);
				new_evenement(E_MONSTRE1, x_cam, y_cam);
				tab_map[i][j] = ' ';
				no_paint = 1;
			}
			else if (c == conf_car_monstre_2)
			{
				//strcpy(img_temp, img_map_monstre_2);
				new_evenement(E_MONSTRE2, x_cam, y_cam);
				tab_map[i][j] = ' ';
				no_paint = 1;
			}
			else if (c == conf_car_monstre_3)
			{
				//strcpy(img_temp, img_map_monstre_3);
				new_evenement(E_MONSTRE3, x_cam, y_cam);
				tab_map[i][j] = ' ';
				no_paint = 1;
			}
			else if (c == ' ')
			{
				no_paint = 1;
			}
			else //inconnue
			{
				int pointeur = 0;
				for(int k=0; k<BLOC_SIZE; k++)
				{
					for(int l=0; l<BLOC_SIZE; l++)
					{
						img_temp[pointeur] = '?';
						pointeur++;
					}
					img_temp[pointeur] = '\n';
					pointeur++;
				}
				img_temp[pointeur] = '\0';
			}

			if (!no_paint) afficher_image(img_temp, x_cam, y_cam);
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de recupérer le type de bloc en fonction d'une position
// en nombre de caractère.
// cette fonction est utilisé pour détecter des contact
char get_char_of_bloc_in_map_at_pos(int x, int y) //repere A
{
	int case_x = (pos_camera_x+x) / BLOC_SIZE;
	int case_y = (y) / BLOC_SIZE;

	if ((case_x >= 0) && (case_x <= longeur_map) && (case_y >= 0) && (case_y <= NB_BLOC_HAUTEUR))
	{
		return (tab_map[case_x][case_y]);
	}

	return ('?');
}



