/*!==================================================================
Nom      : historique.h
Projet   : mario
Editeur  : Samuel Yanez-Carbonell
===================================================================*/

///LES FONCTIONS ====================================================

// ces différentes fonctions sont appelé lorsque mario rentre en contact
// avec (un/une) : caisse, pièce, monstre1, monstre2, monstr3

void mario_vs_caisse(int id_evenement)
{
	int mx = pos_mario_x;
	int my = HAUTEUR_FENETRE - pos_mario_y;
	int mw = conf_val_largeur_mario;
	int mh = conf_val_hauteur_mario;

	int x = tab_evenement[id_evenement].pos_x;
	int y = tab_evenement[id_evenement].pos_y;

	//explosion de la caissse ou non
	if ((jump > 0) && (my > (y + BLOC_SIZE - 1)))
	{
		jump = 0;
		sup_evenement(id_evenement);
		FXcaisse();
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void mario_vs_or(int id_evenement)
{
	//mario gagne de l'or
	gold++;
	score += conf_val_score_or;
	sup_evenement(id_evenement);
	FXgetcoin();
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void mario_vs_check(int id_evenement)
{
	//mario gagne passe un check
	pos_last_check_cam = pos_camera_x;
	pos_last_check_x = tab_evenement[id_evenement].pos_x;
	pos_last_check_y = HAUTEUR_FENETRE - tab_evenement[id_evenement].pos_y + conf_val_hauteur_mario + BLOC_SIZE;
	sup_evenement(id_evenement);
	FXgetcoin();
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void mario_vs_monstre1(int id_evenement)
{
	//en fonction de la position de marion et de l'unité
	//soit mario meurt ou bien l'unité
	if ((pos_mario_y-conf_val_hauteur_mario+3) >= (HAUTEUR_FENETRE-tab_evenement[id_evenement].pos_y))
	{
		score += conf_val_score_monstre1;
		jump = conf_val_jump*2/3;
		sup_evenement(id_evenement);
		FXkill();
	}
	else
	{
		mort_de_mario();
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void mario_vs_monstre2(int id_evenement)
{
	//mort soudaine de mario
	mort_de_mario();
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void mario_vs_monstre3(int id_evenement)
{
	//mort de mario ou bien transformation en coquille
	if (tab_evenement[id_evenement].ct2 == 0)
	{
		if ((pos_mario_y-conf_val_hauteur_mario+3) >= (HAUTEUR_FENETRE-tab_evenement[id_evenement].pos_y))
		{
			tab_evenement[id_evenement].ct1 = last_direction;
			tab_evenement[id_evenement].ct2 = 150;
			//score += conf_val_score_monstre3;
			jump = conf_val_jump*2/3;
			pos_mario_y = HAUTEUR_FENETRE-tab_evenement[id_evenement].pos_y+conf_val_hauteur_mario-1;
			FXkill();
		}
		else
		{
			mort_de_mario();
		}
	}
	else
	{
		if ((pos_mario_y-conf_val_hauteur_mario+3) >= (HAUTEUR_FENETRE-tab_evenement[id_evenement].pos_y))
		{
			tab_evenement[id_evenement].ct1 = last_direction;
			jump = conf_val_jump*2/3;
			pos_mario_y = HAUTEUR_FENETRE-tab_evenement[id_evenement].pos_y+conf_val_hauteur_mario-1;
			FXkill();
		}
		else
		{
			mort_de_mario();
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//************************ HEADER REPERE ****************************

void deplacement_monstre(int id_evenement)
{
	int i = id_evenement;
	int w = conf_val_largeur_monstre1;
	int h = conf_val_hauteur_monstre1;
	int x = tab_evenement[i].pos_x;
	int y = HAUTEUR_FENETRE - tab_evenement[i].pos_y - h;

	if (!ground_under_unit(x, y, w, h))
	{
		tab_evenement[i].pos_y++;
		y++;
	}

	if (tab_evenement[i].ct1 == D_LEFT)
	{
		if (vide_at_left_unit(x, y, w, h) && ground_under_unit(x - w, y, w, h) && no_caisse_at_left_for_unit(x, tab_evenement[i].pos_y, w, h))
		{
			tab_evenement[i].pos_x--;
			x--;
		}
		else
		{
			tab_evenement[i].ct1 = D_RIGHT;
		}
	}
	else
	{
		if (vide_at_right_unit(x, y, w, h) && ground_under_unit(x + w, y, w, h) && no_caisse_at_right_for_unit(x, tab_evenement[i].pos_y, w, h))
		{
			tab_evenement[i].pos_x++;
			x++;
		}
		else
		{
			tab_evenement[i].ct1 = D_LEFT;
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void deplacement_carapace(int id_evenement)
{
	int i = id_evenement;
	int w = conf_val_largeur_monstre1;
	int h = conf_val_hauteur_monstre1;
	int x = tab_evenement[i].pos_x;
	int y = HAUTEUR_FENETRE - tab_evenement[i].pos_y - h;

	if (!ground_under_unit(x, y, w, h))
	{
		tab_evenement[i].pos_y++;
		y++;
	}

	if (tab_evenement[i].ct1 == D_LEFT)
	{
		if (vide_at_left_unit(x, y, w, h))
		{
			tab_evenement[i].pos_x--;
			x--;
		}
		else
		{
			tab_evenement[i].ct1 = D_RIGHT;
		}
	}
	else
	{
		if (vide_at_right_unit(x, y, w, h))
		{
			tab_evenement[i].pos_x++;
			x++;
		}
		else
		{
			tab_evenement[i].ct1 = D_LEFT;
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

