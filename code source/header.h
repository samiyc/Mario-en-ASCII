/*!==================================================================
Nom      : header.h
Projet   : mario
Editeur  : Samuel Yanez-Carbonell
===================================================================*/
#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

//PROTOTYPE DES FONCTIONS ===========================================

//configuration
void lire_fichier_de_config();

//affichage
void reset_tab_screen();
void charger_une_image(char image[], const char filename[]);
void afficher_image(char image[], int x, int y);
void afficher_tab_screen();
char* agrandire_chaine(char chaine[], int longeur_attendu);//pr config.cpp
char* afficher_zero(int valeur, int nb);

//gestion carte
void chargement_de_la_map();
void charger_les_images_pour_la_map();
void afficher_zone_courante(int position_camera);
char get_char_of_bloc_in_map_at_pos(int x, int y);

//gestion clavier
bool up_key();
bool down_key();
bool left_key();
bool right_key();
bool enter_key();

//gestion mario
void deplacement_mario();
void jump_mario();
void images_mario();
void mort_de_mario();
void resurection_de_mario();
void game_over();

//fonction de traitement
bool ground_under();
bool ground_under_unit(int pos_x, int pos_y, int w_size, int h_size);
bool vide_at_left();
bool vide_at_left_unit(int pos_x, int pos_y, int w_size, int h_size);
bool vide_at_right();
bool vide_at_right_unit(int pos_x, int pos_y, int w_size, int h_size);
bool air_over();
bool air_over_unit(int pos_x, int pos_y, int w_size, int h_size);
bool contact_entre_deux_carre(
	int c1_x, int c1_y, int c1_largeur, int c1_hauteur,
	int c2_x, int c2_y, int c2_largeur, int c2_hauteur );

//gestion des événements
void new_evenement(int type, int x, int y);
void sup_evenement(int id);
void sup_old_evenement(int x_min);
void afficher_evenement();
void decaler_evenement(int xdecal);
void animation_evenement();
//********
void contact_avec_evenement();
void contact_evenement_carapace(int id);
//********
bool unit_can_walk_on_a_caisse(int mx, int my, int mw, int mh);
bool no_caisse_at_left();
bool no_caisse_at_left_for_unit(int mx, int my, int mw, int mh);
bool no_caisse_at_right();
bool no_caisse_at_right_for_unit(int mx, int my, int mw, int mh);

//gestion des monstres
void mario_vs_caisse  (int id_evenement);
void mario_vs_or      (int id_evenement);
void mario_vs_check   (int id_evenement);
void mario_vs_monstre1(int id_evenement);
void mario_vs_monstre2(int id_evenement);
void mario_vs_monstre3(int id_evenement);
//********
void deplacement_monstre(int id_evenement);
void deplacement_carapace(int id_evenement);



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#endif // HEADER_H_INCLUDED
