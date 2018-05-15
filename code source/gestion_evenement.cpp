/*!==================================================================
Nom      : fonction_de_traitement.cpp
Projet   : mario
Editeur  : Samuel Yanez-Carbonell
===================================================================*/


//LES VARIABLES GLOBALES ============================================

struct_evenement tab_evenement[MAX_EVENEMENT];


///LES FONCTIONS ====================================================

// permet d'ajouter un évenement dans le tableau des évenements
void new_evenement(int type, int x, int y)//repere A
{
	if (nb_evenement < MAX_EVENEMENT)
	{
		nb_evenement++;
		tab_evenement[nb_evenement-1].type = type;
		tab_evenement[nb_evenement-1].pos_x = x;
		tab_evenement[nb_evenement-1].pos_y = y;
		tab_evenement[nb_evenement-1].ct1 = D_LEFT;
		tab_evenement[nb_evenement-1].ct2 = 0;
		tab_evenement[nb_evenement-1].ct3 = 0;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de supprimer un élement dans la liste des évenements
void sup_evenement(int id)
{
	for(int i=id; i<(nb_evenement-1); i++)
	{
		tab_evenement[i].type = tab_evenement[i+1].type;
		tab_evenement[i].pos_x = tab_evenement[i+1].pos_x;
		tab_evenement[i].pos_y = tab_evenement[i+1].pos_y;
		tab_evenement[i].ct1 = tab_evenement[i+1].ct1;
		tab_evenement[i].ct2 = tab_evenement[i+1].ct2;
		tab_evenement[i].ct3 = tab_evenement[i+1].ct3;
	}
	nb_evenement--;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de supprimer les evenement qui sorte de l'écran sur la gauche
// lorsque leur "pos_x" est inférieur à "x_min"
// cela permet par exemple de laisser un chance a un monstre de rebondire
// contre un mur et ainssi il peut revenir dans la zone visible de l'écran
void sup_old_evenement(int x_min)
{
	for(int i=0; i<nb_evenement; i++)
	{
		if (tab_evenement[i].pos_x < x_min) sup_evenement(i);
		if (tab_evenement[i].pos_y < 0)
		{
			if (tab_evenement[i].type == E_MONSTRE1)  score += conf_val_score_monstre1;
			if (tab_evenement[i].type == E_MONSTRE2) {score += conf_val_score_monstre2; gold += 10;}
			if (tab_evenement[i].type == E_MONSTRE3)  score += conf_val_score_monstre3;
			sup_evenement(i);
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet d'afficher les evenements dans le tampon d'affchage
void afficher_evenement()
{
	char img_temp[IMAGE_MAX_SIZE];

	for(int i=0; i<nb_evenement; i++)
	{
		if (tab_evenement[i].type == E_CAISSE)
		{
			strcpy(img_temp, img_map_caisse);
		}
		else if (tab_evenement[i].type == E_OR)
		{
			strcpy(img_temp, img_map_or);
		}
		else if (tab_evenement[i].type == E_CHECK)
		{
			strcpy(img_temp, img_map_check);
		}
		else if (tab_evenement[i].type == E_MONSTRE1)
		{
			strcpy(img_temp, img_map_monstre_1);
		}
		else if (tab_evenement[i].type == E_MONSTRE2)
		{
			strcpy(img_temp, img_map_monstre_2);
		}
		else if (tab_evenement[i].type == E_MONSTRE3)
		{
			if (tab_evenement[i].ct2 > 0)
			{
				strcpy(img_temp, img_map_monstre_carapace);
			}
			else
			{
				strcpy(img_temp, img_map_monstre_3);
			}
		}

		int x = tab_evenement[i].pos_x;
		int y = tab_evenement[i].pos_y;
		afficher_image(img_temp, x, y);
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de décaler tous les evenement l'orsque la camera se déplace
void decaler_evenement(int xdecal)
{
	for(int i=0; i<nb_evenement; i++)
	{
		tab_evenement[i].pos_x += xdecal;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// gestion des mouvement des évenement
void animation_evenement() //repere B
{
	for(int i=0; i<nb_evenement; i++)
	{
		if (tab_evenement[i].type == E_MONSTRE1)
		{
			deplacement_monstre(i);
		}
		if (tab_evenement[i].type == E_MONSTRE2)
		{
			deplacement_monstre(i);
		}
		if (tab_evenement[i].type == E_MONSTRE3)
		{
			if (tab_evenement[i].ct2 > 0)
			{
				deplacement_carapace(i);
				tab_evenement[i].ct2--;
				contact_evenement_carapace(i);
			}
			else
			{
				deplacement_monstre(i);
			}
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//************************ HEADER REPERE ****************************


// permet de faire intéragire les evenement avec le perssonnage
// retourne l'identifiant de l'evenement avec lequel mario rentre en contact
void contact_avec_evenement()//repere B
{
	int x, y;
	int mx = pos_mario_x;
	int my = HAUTEUR_FENETRE - pos_mario_y;
	int mw = conf_val_largeur_mario;
	int mh = conf_val_hauteur_mario;

	for(int i=0; i<nb_evenement; i++)
	{
		x = tab_evenement[i].pos_x;
		y = tab_evenement[i].pos_y;

#ifndef MODE_DEVELOPER
		if (tab_evenement[i].type == E_CAISSE)
		{
			if(contact_entre_deux_carre(mx, my, mw, mh, x, y, BLOC_SIZE, BLOC_SIZE))
			{
				mario_vs_caisse(i);
			}
		}
		else if (tab_evenement[i].type == E_OR)
		{
			if(contact_entre_deux_carre(mx, my, mw, mh, x, y, BLOC_SIZE, BLOC_SIZE))
			{
				mario_vs_or(i);
			}
		}
#endif
		if (tab_evenement[i].type == E_CHECK)
		{
			if(contact_entre_deux_carre(mx, my, mw, mh, x, y, BLOC_SIZE, BLOC_SIZE))
			{
				mario_vs_check(i);
			}
		}
#ifndef MODE_DEVELOPER
		if (tab_evenement[i].type == E_MONSTRE1)
		{
			int w = conf_val_largeur_monstre1;
			int h = conf_val_hauteur_monstre1;
			int d = conf_val_decal_top_monstre1;

			if(contact_entre_deux_carre(mx, my, mw, mh, x, (y+d), w, h))
			{
				mario_vs_monstre1(i);
			}
		}
		else if (tab_evenement[i].type == E_MONSTRE2)
		{
			int w = conf_val_largeur_monstre2;
			int h = conf_val_hauteur_monstre2;
			int d = conf_val_decal_top_monstre2;

			if(contact_entre_deux_carre(mx, my, mw, mh, x, (y+d), w, h))
			{
				mario_vs_monstre2(i);
			}
		}
		else if (tab_evenement[i].type == E_MONSTRE3)
		{
			int w = conf_val_largeur_monstre3;
			int h = conf_val_hauteur_monstre3;
			int d = conf_val_decal_top_monstre3;

			if(contact_entre_deux_carre(mx, my, mw, mh, x, (y+d), w, h))
			{
				mario_vs_monstre3(i);
			}
		}
#endif
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de tuer les monstre qui rentre en contact avec une carapace
void contact_evenement_carapace(int id)
{
	int x, y;
	int mx = tab_evenement[id].pos_x;
	int my = tab_evenement[id].pos_y;
	int mw = conf_val_largeur_monstre1;
	int mh = conf_val_hauteur_monstre1;

	for(int i=0; i<nb_evenement; i++)
	{
		if (i != id)
		{
			x = tab_evenement[i].pos_x;
			y = tab_evenement[i].pos_y;

			if (tab_evenement[i].type == E_CAISSE)
			{
				if(contact_entre_deux_carre(mx, my, mw, mh, x, y, BLOC_SIZE, BLOC_SIZE))
				{
					sup_evenement(i);
					FXcaisse();
				}
			}
			else if (tab_evenement[i].type == E_MONSTRE1)
			{
				int w = conf_val_largeur_monstre1;
				int h = conf_val_hauteur_monstre1;
				int d = conf_val_decal_top_monstre1;

				if(contact_entre_deux_carre(mx, my, mw, mh, x, (y+d), w, h))
				{
					sup_evenement(i);
					FXkill();
				}
			}
			else if (tab_evenement[i].type == E_MONSTRE2)
			{
				int w = conf_val_largeur_monstre1;
				int h = conf_val_hauteur_monstre1;
				int d = conf_val_decal_top_monstre1;

				if(contact_entre_deux_carre(mx, my, mw, mh, x, (y+d), w, h))
				{
					score += conf_val_score_monstre2; gold += 10;
					sup_evenement(i);
					FXgetcoin();
				}
			}
			else if (tab_evenement[i].type == E_MONSTRE3)
			{
				int w = conf_val_largeur_monstre1;
				int h = conf_val_hauteur_monstre1;
				int d = conf_val_decal_top_monstre1;

				if(contact_entre_deux_carre(mx, my, mw, mh, x, (y+d), w, h))
				{
					sup_evenement(i);
					FXkill();
				}
			}
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//************************ HEADER REPERE ****************************


// cette fonction permet de savoir si mario marche sur une caisse
bool unit_can_walk_on_a_caisse(int mx, int my, int mw, int mh)//repere B
{
	int x, y;

	for(int i=0; i<nb_evenement; i++)
	{
		if (tab_evenement[i].type == E_CAISSE)
		{
			x = tab_evenement[i].pos_x;
			y = tab_evenement[i].pos_y;

			if(contact_entre_deux_carre(mx, my, mw, mh, x, y, BLOC_SIZE, BLOC_SIZE))
			{
				//explosion de la caissse ou non
				if ((my+mh) <= y)
				{
					return (true);
				}
			}
		}
	}
	return (false);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// cette fonction permet de savoir si il a une caisse sur la gauche de mario
bool no_caisse_at_left()
{
	return no_caisse_at_left_for_unit(pos_mario_x, HAUTEUR_FENETRE-pos_mario_y, conf_val_largeur_mario, conf_val_hauteur_mario);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// cette fonction permet de savoir si il a une caisse sur la gauche d'une unité
bool no_caisse_at_left_for_unit(int mx, int my, int mw, int mh)
{
	int x, y;
	mh--;

	for(int i=0; i<nb_evenement; i++)
	{
		if (tab_evenement[i].type == E_CAISSE)
		{
			x = tab_evenement[i].pos_x;
			y = tab_evenement[i].pos_y;

			if(contact_entre_deux_carre(mx-1, my, mw, mh, x, y, BLOC_SIZE, BLOC_SIZE-2))
			{
				return (false);
			}
		}
	}
	return (true);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// cette fonction permet de savoir si il a une caisse sur la gauche de mario
bool no_caisse_at_right()
{
	return no_caisse_at_right_for_unit(pos_mario_x, HAUTEUR_FENETRE-pos_mario_y, conf_val_largeur_mario, conf_val_hauteur_mario);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// cette fonction permet de savoir si il a une caisse sur la gauche d'une unité
bool no_caisse_at_right_for_unit(int mx, int my, int mw, int mh)
{
	int x, y;
	mh--;

	for(int i=0; i<nb_evenement; i++)
	{
		if (tab_evenement[i].type == E_CAISSE)
		{
			x = tab_evenement[i].pos_x;
			y = tab_evenement[i].pos_y;

			if(contact_entre_deux_carre(mx+1, my, mw, mh, x, y, BLOC_SIZE, BLOC_SIZE-2))
			{
				return (false);
			}
		}
	}
	return (true);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



