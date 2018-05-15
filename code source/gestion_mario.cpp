/*!==================================================================
Nom      : affichage.cpp
Projet   : mario
Editeur  : Samuel Yanez-Carbonell
===================================================================*/


//LES VARIABLES GLOBALES ============================================

int pos_mario_x;
int pos_mario_y;

int gold, life, jump, score;

long t_start;
long t_end;
long t_toto;

int last_direction;
int last_image_mario;

char img_mario[IMAGE_MAX_SIZE];
char img_mario_left [IMAGE_MAX_SIZE];
char img_mario_right[IMAGE_MAX_SIZE];
char img_mario_left_jump [IMAGE_MAX_SIZE];
char img_mario_right_jump[IMAGE_MAX_SIZE];
char img_game_over[IMAGE_MAX_SIZE];


///LES FONCTIONS ====================================================

void deplacement_mario()
{
	//mario est bloqué contre le bord gauche de la fenetre
	if (pos_mario_x < 0)
	{
		pos_mario_x = 0;
	}

	//quand mario avance la fenetre avance
	if (pos_mario_x > ((LARGEUR_FENETRE*2)/3))
	{
		pos_mario_x--;
		pos_camera_x++;
		decaler_evenement(-1);
	}

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void jump_mario()
{
	if(jump > 0)
	{
		if (air_over())
		{
			pos_mario_y++;
			jump--;
		}
		else
		{
			jump = 0;
		}
	}
	else
	{
		//sur le sol ?
		if (!ground_under())
		{
			pos_mario_y --;
		}
		if (pos_mario_y < 0) //pos_mario_y > BLOC_SIZE+5 //!ground_under()
		{
			mort_de_mario();
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void images_mario()
{
	if (last_direction == D_RIGHT)
	{
		if (jump > 0)
		{
			if (last_image_mario != 1)
			{
				last_image_mario = 1;
				strcpy(img_mario, img_mario_right_jump);
			}
		}
		else
		{
			if (last_image_mario != 2)
			{
				last_image_mario = 2;
				strcpy(img_mario, img_mario_right);
			}
		}
	}
	else// D_LEFT
	{
		if (jump > 0)
		{
			if (last_image_mario != 3)
			{
				last_image_mario = 3;
				strcpy(img_mario, img_mario_left_jump);
			}
		}
		else
		{
			if (last_image_mario != 4)
			{
				last_image_mario = 4;
				strcpy(img_mario, img_mario_left);
			}
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void mort_de_mario()
{
	char chaine[MAX_CHAINE];

	FXdie();
	Sleep(1000);

	afficher_image(img_mario_right, LARGEUR_FENETRE/2-5-conf_val_largeur_mario, HAUTEUR_FENETRE/2-conf_val_hauteur_mario+1);
	sprintf(chaine, "X     %d", life);
	afficher_image(chaine, LARGEUR_FENETRE/2, HAUTEUR_FENETRE/2);
	afficher_tab_screen();
	Sleep(2000);

	#ifndef MODE_DEVELOPER
	life--;
	#endif

	afficher_image(img_mario_right, LARGEUR_FENETRE/2-5-conf_val_largeur_mario, HAUTEUR_FENETRE/2-conf_val_hauteur_mario+1);
	sprintf(chaine, "X     %d", life);
	afficher_image(chaine, LARGEUR_FENETRE/2, HAUTEUR_FENETRE/2);
	afficher_tab_screen();
	Sleep(2000);

	if (life > 0)
	{
		resurection_de_mario();
	}
	else
	{
		game_over();
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void resurection_de_mario()
{
	//initialisation des variables
	last_direction = D_RIGHT;
	last_image_mario = 0;

	if(pos_last_check_x > -1)
	{
		pos_camera_x = pos_last_check_cam;
		pos_mario_x = pos_last_check_x;
		pos_mario_y = pos_last_check_y;
	}
	else
	{
		pos_camera_x = 0;
		pos_mario_x = 7;
		pos_mario_y = BLOC_SIZE+5;
	}
	jump = 0;


	//initialisation de la carte
	chargement_de_la_map();

	//initialisation du personnage
	strcpy(img_mario, img_mario_right);

	//reset les evenement
	nb_evenement = 0;

	FXbackFx();
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void game_over()
{
	//init
	char chaine[MAX_CHAINE];
	int var1 = 0;
	int var2 = 0;
	int var3 = 0;

	time(&t_end);
	t_toto = (t_end - t_start);

	while((var1 != score) || (var2 != t_toto))
	{
		//fin du décompte
		sprintf(chaine, "Appuyez sur enter pour recommencer");
		afficher_image(chaine, ((LARGEUR_FENETRE/2)-(strlen(chaine)/2)+1), HAUTEUR_FENETRE-5);
		if (enter_key())
		{
			var1 = score;
			var2 = t_toto;
		}

		//Le message GAME OVER
		afficher_image(img_game_over, LARGEUR_FENETRE/2-28, HAUTEUR_FENETRE/4);

		//Les Stats
		if (var1 < score) var1 += ((score-var1)/20+1);
		sprintf(chaine, "SCORE : %s%d", afficher_zero(var1, 6), var1);
		afficher_image(chaine, LARGEUR_FENETRE/2-5, HAUTEUR_FENETRE/2-5);

		if (var2 < t_toto) var2 += ((t_toto-var2)/20+1);
		sprintf(chaine, "TIME  : %dMin %dsec", var2/60, var2%60);
		afficher_image(chaine, LARGEUR_FENETRE/2-5, HAUTEUR_FENETRE/2);

		var3 = var1 - var2;
		if (var3<0) var3 = 0;
		sprintf(chaine, "TOTAL : %6d", var3);
		afficher_image(chaine, LARGEUR_FENETRE/2-5, HAUTEUR_FENETRE/2+5);

		//affichage
		afficher_tab_screen();
		Sleep(20);
	}

	Sleep(100);
	while(!enter_key()) Sleep(10);
	Sleep(100);

	//reset des variables
	score = 0;
	life = 3;
	gold = 3;
	pos_last_check_x = -1;
	pos_last_check_y = -1;
	pos_last_check_cam = -1;
	time(&t_start);

	//Restart
	resurection_de_mario();
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%





