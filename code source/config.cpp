/*!==================================================================
Nom      : config.cpp
Projet   : mario
Editeur  : Samuel Yanez-Carbonell
===================================================================*/

//#define FINAL_MODE

//LES VARIABLES GLOBALES ============================================

int conf_val_volume;

int conf_car_invisible;
int conf_car_sol;
int conf_car_caisse;
int conf_car_or;
int conf_car_check;
int conf_car_nuage;
int conf_car_decor;
int conf_car_monstre_1;
int conf_car_monstre_2;
int conf_car_monstre_3;

int conf_val_jump;
int conf_val_hauteur_mario;
int conf_val_largeur_mario;

int conf_val_hauteur_monstre1;
int conf_val_largeur_monstre1;
int conf_val_decal_top_monstre1;
int conf_val_hauteur_monstre2;
int conf_val_largeur_monstre2;
int conf_val_decal_top_monstre2;
int conf_val_hauteur_monstre3;
int conf_val_largeur_monstre3;
int conf_val_decal_top_monstre3;

int conf_val_score_or;
int conf_val_score_monstre1;
int conf_val_score_monstre2;
int conf_val_score_monstre3;


///LES FONCTIONS ====================================================

// Cette fonction permet de lire le fichier config.txt
void lire_fichier_de_config()
{
    //#define FINAL_MODE

    FILE *f_fichier;
    char s_tampon[MAX_CHAINE];
    char s_fonction[MAX_CHAINE];
    char s_valeur  [MAX_CHAINE];

	#ifdef FINAL_MODE
    printf("#\n#> Lecture du fichier de configuration <");
    #endif

    if ((f_fichier = fopen("./data/config.txt", "r")) == NULL)
    {
        printf("\n\nERREUR : impossible d'acceder au fichier config.txt\n\n");
        system("pause");
        exit(-1);
    }
    while(fgets(s_tampon, MAX_CHAINE-1, f_fichier))
    {
        #ifdef FINAL_MODE
        Sleep(50);
        #endif

        if ((s_tampon[0] != '#') && (s_tampon[0] != '\n'))
        {

			sscanf(s_tampon, "%s : %s;", s_fonction, s_valeur);

			#ifdef FINAL_MODE
			printf("\n# %s  =>  %s", agrandire_chaine(s_fonction, 20), s_valeur);
			#endif

			if (strcmp(s_fonction, "valeur-volume") == 0)
			{
				conf_val_volume = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "caractere-invisible") == 0)
			{
				conf_car_invisible = s_valeur[0];
			}
			else if (strcmp(s_fonction, "caractere-sol") == 0)
			{
				conf_car_sol = s_valeur[0];
			}
			else if (strcmp(s_fonction, "caractere-caisse") == 0)
			{
				conf_car_caisse = s_valeur[0];
			}
			else if (strcmp(s_fonction, "caractere-or") == 0)
			{
				conf_car_or = s_valeur[0];
			}
			else if (strcmp(s_fonction, "caractere-check") == 0)
			{
				conf_car_check = s_valeur[0];
			}
			else if (strcmp(s_fonction, "caractere-nuage") == 0)
			{
				conf_car_nuage = s_valeur[0];
			}
			else if (strcmp(s_fonction, "caractere-decor") == 0)
			{
				conf_car_decor = s_valeur[0];
			}
			else if (strcmp(s_fonction, "caractere-monstre-1") == 0)
			{
				conf_car_monstre_1 = s_valeur[0];
			}
			else if (strcmp(s_fonction, "caractere-monstre-2") == 0)
			{
				conf_car_monstre_2 = s_valeur[0];
			}
			else if (strcmp(s_fonction, "caractere-monstre-3") == 0)
			{
				conf_car_monstre_3 = s_valeur[0];
			}
			else if (strcmp(s_fonction, "valeur-jump-mario") == 0)//Mario
			{
				conf_val_jump = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-hauteur-mario") == 0)
			{
				conf_val_hauteur_mario = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-largeur-mario") == 0)
			{
				conf_val_largeur_mario = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-hauteur-monstre1") == 0)//H & L & decal Top
			{
				conf_val_hauteur_monstre1 = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-largeur-monstre1") == 0)
			{
				conf_val_largeur_monstre1 = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-decal-top-monstre1") == 0)
			{
				conf_val_decal_top_monstre1 = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-hauteur-monstre2") == 0)//H & L & decal Top
			{
				conf_val_hauteur_monstre2 = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-largeur-monstre2") == 0)
			{
				conf_val_largeur_monstre2 = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-decal-top-monstre2") == 0)
			{
				conf_val_decal_top_monstre2 = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-hauteur-monstre3") == 0)//H & L & decal Top
			{
				conf_val_hauteur_monstre3 = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-largeur-monstre3") == 0)
			{
				conf_val_largeur_monstre3 = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-decal-top-monstre3") == 0)
			{
				conf_val_decal_top_monstre3 = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-score-or") == 0)
			{
				conf_val_score_or = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-score-monstre1") == 0)
			{
				conf_val_score_monstre1 = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-score-monstre2") == 0)
			{
				conf_val_score_monstre2 = atoi(s_valeur);
			}
			else if (strcmp(s_fonction, "valeur-score-monstre3") == 0)
			{
				conf_val_score_monstre3 = atoi(s_valeur);
			}
        }
        else
        {
        	#ifdef FINAL_MODE
			if (s_tampon[0] == '\n') printf("\n#");
			#endif
        }

    }//fin while
    fclose(f_fichier);

    #ifdef FINAL_MODE
    Sleep(50);
    printf("\n#");
    printf("\n#  (appuyez sur enter pour continuer)");
    getchar();
    Sleep(100);
    #endif
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



