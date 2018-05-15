/*!==================================================================
Nom      : main.cpp
Projet   : mario
Editeur  : Samuel Yanez-Carbonell
version  : 1.0
===================================================================*/
#include "constantes.h"
#include "header.h"

//#define MODE_DEVELOPER

//LES VARIABLES GLOBALES ============================================
int nb_evenement;
int pos_last_check_cam = -1;
int pos_last_check_x = -1;
int pos_last_check_y = -1;

//LES FONCTIONS ANNEXE ===================================================
#include "config.cpp"
#include "MHBmarioFx.h"

#include "affichage.cpp"
#include "gestion_carte.cpp"
#include "gestion_clavier.cpp"
#include "gestion_mario.cpp"
#include "fonction_de_traitement.cpp"
#include "gestion_evenement.cpp"
#include "gestion_monstre.cpp"



///#####################  FONCTION PRINCIPALE  ######################
int main()
{
	///LES VARIABLES ================================================

	//les entiers
	int compteur = 0;
	int last_score;

	//les chaines
	char chaine[MAX_CHAINE];

	//les images
	char img_loading[IMAGE_MAX_SIZE];
	char img_menu[IMAGE_MAX_SIZE];


	///chargement du fichier de config
    lire_fichier_de_config();


    ///LES INITIALISATIONS ==========================================
    {
		system("mode 125");

		//initialisation des variables
		gold = 0;
		life = 3;
		jump = 0;
		score = 0;
		last_score = 0;
		pos_last_check_x = -1;
		pos_last_check_y = -1;
		pos_last_check_cam = -1;

		last_direction = D_RIGHT;
		last_image_mario = 0;

		pos_mario_x = 7;//7
		pos_mario_y = BLOC_SIZE+5;
		pos_camera_x = 0;

		//initialisation de la carte
		chargement_de_la_map();
		charger_les_images_pour_la_map();

		//chargement des images
		charger_une_image(img_loading, "loading.txt");
		charger_une_image(img_menu, "menu.txt");
		charger_une_image(img_game_over, "game_over.txt");
		charger_une_image(img_mario_left, "mario/mario_left.txt");
		charger_une_image(img_mario_left_jump, "mario/mario_left_jump.txt");
		charger_une_image(img_mario_right, "mario/mario_right.txt");
		charger_une_image(img_mario_right_jump, "mario/mario_right_jump.txt");


		//initialisation du personnage
		strcpy(img_mario, img_mario_right);

		//initialisation de l'affichage
		reset_tab_screen();

		//chargement de l'api FMOD & les fichiers son
		afficher_image(img_loading, LARGEUR_FENETRE/2-15, HAUTEUR_FENETRE/2-1);
		afficher_tab_screen();
		FXinit();
		FXbackFx();

		//le menu
		afficher_image(img_menu, 0, 0);
		afficher_tab_screen();
		while (!enter_key()) Sleep(10);//PAUSE

		time(&t_start);
    }


    ///#####################  BOUCLE PRINCIPALE  ####################
	while(1)
	{
		compteur++;

		///SAISI CLAVIER ============================================
		{
			if (left_key() && vide_at_left() && no_caisse_at_left())//LEFT
			{
				pos_mario_x--;
				last_direction = D_LEFT;
			}
			else if (right_key() && vide_at_right() && no_caisse_at_right())//RIGHT
			{
				pos_mario_x++;
				last_direction = D_RIGHT;
			}
			if (up_key() && (jump == 0) && ground_under())//UP
			{
				jump = conf_val_jump;
				FXjump();
			}
			else if (down_key())//DOWN
			{
				jump = 0;
				if (!ground_under())pos_mario_y --;
			}

			//PAUSE
			else if (echap_key())
			{
				FXpause();
				afficher_image("PAUSE", LARGEUR_FENETRE/2-3, HAUTEUR_FENETRE/2);
				afficher_tab_screen();
				Sleep(100);
				while(!echap_key()) Sleep(10);
				Sleep(100);
				FXpause();
			}
		}

		///TRAITEMENT ===============================================
		{
			//deplacement
			deplacement_mario();

			//jump
			jump_mario();

			//gestion des images du perso
			images_mario();

			//gestion de l'or
			if (gold >= 100)
			{
				life++;
				gold = 0;
				FXuplife();
			}

		}//fin du traitement

		///AFFICHAGE ================================================
		{
			//le fond
			afficher_zone_courante(pos_camera_x);

			//le personnage
			afficher_image(img_mario, pos_mario_x, HAUTEUR_FENETRE - pos_mario_y);

			//afficher les evenements
			sup_old_evenement(-20);
			if((compteur%2) == 0) animation_evenement();
			contact_avec_evenement();
			afficher_evenement();

			//affichages des infos utiles
			if (last_score < score) last_score += ((score-last_score)/20+1);
			if (score < last_score) last_score = score;
			sprintf(chaine, "VIE : %d       SCORE : %s%d", life, afficher_zero(last_score, 6), last_score);
			afficher_image(chaine, 8, 5);

			time(&t_end); t_toto = (t_end - t_start);
			sprintf(chaine, "TIME : %dMin %dsec       PIECE : %s%d", t_toto/60, t_toto%60, afficher_zero(gold, 3), gold);
			afficher_image(chaine, LARGEUR_FENETRE-5-strlen(chaine), 5);

			//maj affichage
			afficher_tab_screen();

			//printf("test: %d", conf_val_volume);

			Sleep(10);

		}//fin de l'affichage

	}//fin de la boucle principale

    return 0;
}//fin de la fonction main

