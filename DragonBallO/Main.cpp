#include "GameManager.h"
#include <windows.h>


extern bool gQuitGame;

int main( int argc, char* args[] )
{
	// TODO: Change to more universal way
	char* WAV = "C:\\Users\\student\\Desktop\\cg_sdl\\DragonBallO\\music\\The Legend of Zelda A Link to the Past Music Kakariko Village.wav";
	PlaySound(WAV, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	GameManager gameManager;

	if(gameManager.Init()){
		while (!gQuitGame) {
			gameManager.Update();
			gameManager.Render();
		}
	}

	gameManager.Cleanup();

	return 0;
}