/*!==================================================================
Nom      : gestion_clavier.cpp
Projet   : mario
Editeur  : Samuel Yanez-Carbonell
===================================================================*/


//LES VARIABLES GLOBALES ============================================
SHORT Mask = 32768;


///LES FONCTIONS ====================================================

// ces fonction permettent de détecter si l'utilisateur appuy
// sur une touche directionnelle
bool up_key()
{
	return (GetKeyState(VK_UP) & Mask);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

bool down_key()
{
	if (GetKeyState(VK_DOWN) & Mask) return (true);
	return (false);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

bool left_key()
{
	if (GetKeyState(VK_LEFT) & Mask) return (true);
	return (false);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

bool right_key()
{
	if (GetKeyState(VK_RIGHT) & Mask) return (true);
	return (false);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// si l'utilisateur appuy sur la touche entrer
bool enter_key()
{
	if (GetKeyState(VK_RETURN) & Mask) return (true);
	return (false);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// si l'utilisateur appuy sur la touche echap
bool echap_key()
{
	if (GetKeyState(VK_ESCAPE) & Mask) return (true);
	return (false);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



