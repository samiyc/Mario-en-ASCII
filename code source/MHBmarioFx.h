/*!==================================================================
Nom      : MHBmarioFx.h
Projet   : mario
Editeur  : Hugo Bouyssou
===================================================================*/

/// EXEMPLE :
///
///		//initialisation
///		FXinit();
///		FXbackFx();   //lancement de la musique de fond
///
///		//boucle principale
///		while(!echap_key())
///    	{
///        FXcaisse();   Sleep(2000);//mario casse une caisse
///        FXdie();      Sleep(2000);//mario meur ( la musique de fond s'arrete )
///        FXbackFx();   Sleep(2000);//on relance la musique de fond
///        FXgetcoin();  Sleep(2000);//mario ramasse une pièce
///        FXjump();     Sleep(2000);//mario saute
///        FXkill();     Sleep(2000);//mario tue un monstre
///        FXpause();    Sleep(3000);//mise en pause
///        FXpause();    Sleep(2000);//fin de la pause
///        FXuplife();   Sleep(2000);//mario gagne une vie
///    	}
///
///		// fin
/// 	FXexit();

//LES INCLUDES ======================================================
#include <fmod.h>

#define MON_CANAL 5

//LES PROTOTYPES ====================================================
void FXinit();
void FXexit();

void FXcaisse();
void FXdie();
void FXgetcoin();
void FXjump();
void FXkill();
void FXpause();
void FXuplife();

void FX_backFx();

//LES VARIBLES GLOBALES =============================================
FMUSIC_MODULE *fx_backFx = NULL;

FSOUND_STREAM *fx_caisse = NULL;
FSOUND_STREAM *fx_die = NULL;
FSOUND_STREAM *fx_getcoin = NULL;
FSOUND_STREAM *fx_jump = NULL;
FSOUND_STREAM *fx_kill = NULL;
FSOUND_STREAM *fx_pause = NULL;
FSOUND_STREAM *fx_uplife = NULL;

int isplay=0;
int ispaused=1;


///INIT & EXIT ====================================================

// Cette fonction permet de lancer l'api FMOD et s'occupe du chargement
// des différents fichiers de son
void FXinit()
{

    //intialisation Fmod
    FSOUND_Init(44100, 32, 0);


	//initialisation des son
    fx_caisse  = FSOUND_Stream_Open("data/son/caisse.wav" , FSOUND_NORMAL, 0, 0);
    fx_die     = FSOUND_Stream_Open("data/son/die.wav"    , FSOUND_NORMAL, 0, 0);
    fx_getcoin = FSOUND_Stream_Open("data/son/getcoin.wav", FSOUND_NORMAL, 0, 0);
    fx_jump    = FSOUND_Stream_Open("data/son/jump.wav"   , FSOUND_NORMAL, 0, 0);
    fx_kill    = FSOUND_Stream_Open("data/son/kill.wav"   , FSOUND_NORMAL, 0, 0);
    fx_pause   = FSOUND_Stream_Open("data/son/pause.wav"  , FSOUND_NORMAL, 0, 0);
    fx_uplife  = FSOUND_Stream_Open("data/son/uplife.wav" , FSOUND_NORMAL, 0, 0);


    fx_backFx = FMUSIC_LoadSong("data/son/backFx.mid");
    FMUSIC_SetMasterVolume(fx_backFx, conf_val_volume*2/3);
}

// Permet de fermer correctement l'api FMOD
// ainssi que les fichiers ouvert lors de l'initialisation
void FXexit()
{
    FSOUND_Stream_Stop(fx_caisse); FSOUND_Stream_Close(fx_caisse);
    FSOUND_Stream_Stop(fx_die); FSOUND_Stream_Close(fx_die);
    FSOUND_Stream_Stop(fx_getcoin); FSOUND_Stream_Close(fx_getcoin);
    FSOUND_Stream_Stop(fx_jump); FSOUND_Stream_Close(fx_jump);
    FSOUND_Stream_Stop(fx_kill); FSOUND_Stream_Close(fx_kill);
    FSOUND_Stream_Stop(fx_pause); FSOUND_Stream_Close(fx_pause);
    FSOUND_Stream_Stop(fx_uplife); FSOUND_Stream_Close(fx_uplife);

    FMUSIC_StopSong(fx_backFx); FMUSIC_FreeSong(fx_backFx);

    FSOUND_Close();
}


///LES FONCTION PERMETTANT DE JOUER DU SON ==========================

//mario casse une caisse
void FXcaisse()
{
    FSOUND_Stream_Play(MON_CANAL, fx_caisse);
    FSOUND_SetVolume(MON_CANAL, conf_val_volume);
}

//mario meur ( la musique de fond s'arrete )
void FXdie()
{
    FMUSIC_SetPaused(fx_backFx, 1);
    FSOUND_Stream_Play(MON_CANAL, fx_die);
    FSOUND_SetVolume(MON_CANAL, 150);
}

//mario ramasse une pièce
void FXgetcoin()
{
    FSOUND_Stream_Play(MON_CANAL, fx_getcoin);
    FSOUND_SetVolume(MON_CANAL, conf_val_volume/3);
}

//mario saute
void FXjump()
{
    FSOUND_Stream_Play(MON_CANAL, fx_jump);
    FSOUND_SetVolume(MON_CANAL, conf_val_volume);
}

//mario tue un monstre
void FXkill()
{
    FSOUND_Stream_Play(MON_CANAL, fx_kill);
    FSOUND_SetVolume(MON_CANAL, conf_val_volume);
}

//mise en pause / fin de la pause
void FXpause()
{
    if(ispaused==1)
    {
		FSOUND_Stream_Play(MON_CANAL, fx_pause);
		FSOUND_SetVolume(MON_CANAL, conf_val_volume);
		FMUSIC_SetPaused(fx_backFx, 1);
		ispaused=0;
    }
    else
    {
		FSOUND_Stream_Play(MON_CANAL, fx_pause);
		FSOUND_SetVolume(MON_CANAL, conf_val_volume);
		FMUSIC_SetPaused(fx_backFx, 0);
		ispaused=1;
    }

}

//mario gagne une vie
void FXuplife()
{
    FSOUND_Stream_Play(MON_CANAL, fx_uplife);
    FSOUND_SetVolume(MON_CANAL, conf_val_volume);
}

//lancement de la musique de fond
void FXbackFx()
{

    if(isplay==0)
    {
		FMUSIC_PlaySong(fx_backFx);
		FMUSIC_SetLooping(fx_backFx, 1);
    }
    else
    {
		FMUSIC_SetPaused(fx_backFx, 0);
    }
    isplay=1;
}



