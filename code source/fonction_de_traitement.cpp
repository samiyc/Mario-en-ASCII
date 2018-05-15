/*!==================================================================
Nom      : fonction_de_traitement.cpp
Projet   : mario
Editeur  : Samuel Yanez-Carbonell
===================================================================*/

///LES FONCTIONS ====================================================

// permet de savoir si mario marche sur le sol
bool ground_under()
{
	return ground_under_unit(pos_mario_x, pos_mario_y, conf_val_largeur_mario, conf_val_hauteur_mario);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de determiner si une unité peut marcher sur le sol
bool ground_under_unit(int pos_x, int pos_y, int w_size, int h_size) //repere A
{
	int x;
	int y;
	char c;

	//on verifi si il y a un bloc sous le pied gauche de mario
	x = pos_x;
	y = pos_y - h_size - 1;
	c = get_char_of_bloc_in_map_at_pos(x, y);
	if (c == '#') return (true);

	//on verifi si il y a un bloc sous le pied gauche de mario
	x = pos_x + w_size / 2;
	c = get_char_of_bloc_in_map_at_pos(x, y);
	if (c == '#') return (true);

	//on verifi si il y a un bloc sous le pied droite de mario
	x = pos_x + w_size;
	c = get_char_of_bloc_in_map_at_pos(x, y);
	if (c == '#') return (true);

	if (unit_can_walk_on_a_caisse(pos_x, HAUTEUR_FENETRE-pos_y, w_size, h_size)) return (true);

	return (false);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de determiner si mario peur reculer
bool vide_at_left()
{
	return vide_at_left_unit(pos_mario_x, pos_mario_y, conf_val_largeur_mario, conf_val_hauteur_mario);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de determiner si une unité peur reculer
bool vide_at_left_unit(int pos_x, int pos_y, int w_size, int h_size) //repere A
{
	int x;
	int y;
	char c;

	//on verifi si il y a un bloc sous le pied gauche de mario
	x = pos_x - 1;
	y = pos_y;
	c = get_char_of_bloc_in_map_at_pos(x, y);
	if (c == '#') return (false);

	//on verifi si il y a un bloc sous le pied droite de mario
	y = pos_y - h_size;
	c = get_char_of_bloc_in_map_at_pos(x, y);
	if (c == '#') return (false);

	return (true);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de determiner si mario peur avancer vers la droite
bool vide_at_right()
{
	return vide_at_right_unit(pos_mario_x, pos_mario_y, conf_val_largeur_mario, conf_val_hauteur_mario);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de determiner si une unité peur avancer vers la droite
bool vide_at_right_unit(int pos_x, int pos_y, int w_size, int h_size) //repere A
{
	int x;
	int y;
	char c;

	//on verifi si il y a un bloc sous le pied gauche de l'unit
	x = pos_x + w_size + 1;
	y = pos_y;
	c = get_char_of_bloc_in_map_at_pos(x, y);
	if (c == '#') return (false);

	//on verifi si il y a un bloc sous le pied droite de l'unit
	y = pos_y - h_size;
	c = get_char_of_bloc_in_map_at_pos(x, y);
	if (c == '#') return (false);

	return (true);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de savoir si mario a un bloc au dessus de la tete
bool air_over()
{
	return air_over_unit(pos_mario_x, pos_mario_y, conf_val_largeur_mario, conf_val_hauteur_mario);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de savoir si une unité a un bloc au dessus de la tete
bool air_over_unit(int pos_x, int pos_y, int w_size, int h_size) //repere A
{
	int x;
	int y;
	char c;

	//haut dessus a gauche
	x = pos_x;
	y = pos_y;
	c = get_char_of_bloc_in_map_at_pos(x, y);
	if (c == '#') return (false);

	//au dessus au milieu
	x = pos_x + w_size / 2;
	c = get_char_of_bloc_in_map_at_pos(x, y);
	if (c == '#') return (false);

	//au dessus a droite
	x = pos_x + w_size;
	c = get_char_of_bloc_in_map_at_pos(x, y);
	if (c == '#') return (false);

	return (true);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// permet de detecter le contact entre deux carré
bool contact_entre_deux_carre(
int c1_x, int c1_y, int c1_largeur, int c1_hauteur,
int c2_x, int c2_y, int c2_largeur, int c2_hauteur )
{
	int c2_x2 = c2_x + c2_largeur;
	int c2_y2 = c2_y + c2_hauteur;

	int a, b;

	//angle supérieur gauche du premier carré
	a = c1_x;
	b = c1_y;
	if ((a >= c2_x) && (a <= c2_x2) && (b >= c2_y) && (b <= c2_y2))
	{
		return (true);
	}

	//angle supérieur droite du premier carré
	a = c1_x + c1_largeur;
	b = c1_y;
	if ((a >= c2_x) && (a <= c2_x2) && (b >= c2_y) && (b <= c2_y2))
	{
		return (true);
	}

	//angle inférieur droite du premier carré
	a = c1_x + c1_largeur;
	b = c1_y + c1_hauteur;
	if ((a >= c2_x) && (a <= c2_x2) && (b >= c2_y) && (b <= c2_y2))
	{
		return (true);
	}

	//angle inférieur gauche du premier carré
	a = c1_x;
	b = c1_y + c1_hauteur;
	if ((a >= c2_x) && (a <= c2_x2) && (b >= c2_y) && (b <= c2_y2))
	{
		return (true);
	}

	return (false);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




