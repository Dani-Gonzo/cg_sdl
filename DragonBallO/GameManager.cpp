#include "GameManager.h"
#include "SDLInit.h"
#include "World.h"
#include "Player.h"
#include "Camera.h"
#include "MoveTrigger.h"
#include "NPC.h"

#define CAMERA_MODE Camera::Mode::PAN
#define SHOW_COLLIDERS false

//Camera dimension...
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

Camera gCamera(CAMERA_MODE);
World gWorld;

static SDLInit sdlInit;

namespace {
	Player player;
	NPC blueDress;
	Sprite tree;
	Sprite boulder;
	Sprite buildingBlueRoof;
	Sprite buildingLibrary;
	Sprite buildingBrickHouse;
	Sprite buildingWoodHouse;
	Sprite blueRoofLeftFence;
	Sprite blueRoofRightFence;
	Sprite woodHouseLeftFence;
	Sprite woodHouseRightFence;
	MoveTrigger moveTrigger;
}

void InitEntities() {
	//Setting path names...

	// Player
	player.SetTexturePath("textures/link_sheet.png");
	sdlInit.LoadTexture(player);
	player.SetPosition({ 320, 239 });
	player.SetSize(60, 65);
	player.ConfigureCollision(true, true, { 1, 14 }, { 31, 18 });

	// Set player sprite sheet texture coordinates
	player.InitSpriteSheet(0, 14, 6);
	player.SetSpriteClip(90, 1, 30, 30, 3);			//up...
	player.SetSpriteClip(90, 31, 30, 30, 17);		//up move...
	player.SetSpriteClip(30, 1, 30, 30, 1);			//down...
	player.SetSpriteClip(30, 31, 30, 30, 15);		//down move...
	player.SetSpriteClip(120, 1, 30, 30, 4);		//right...
	player.SetSpriteClip(120, 31, 30, 30, 18);		//right move...
	player.SetSpriteClip(60, 1, 30, 30, 2);			//left...
	player.SetSpriteClip(60, 31, 30, 30, 16);		//left move...

	player.SetSpriteClip(170, 141, 30, 31, 61);		//first left attack...
	player.SetSpriteClip(173, 109, 30, 30, 48);		//second left attack...
	player.SetSpriteClip(173, 71, 30, 30, 34);		//last left attack...

	player.SetSpriteClip(203, 142, 30, 30, 62);		//last right attack...
	player.SetSpriteClip(203, 109, 30, 30, 49);		//second right attack...
	player.SetSpriteClip(203, 77, 30, 31, 35);		//first right attack...

													//Set sprite sheet anchor positions...
	player.SetAnchorOffset({ -16, -13 }, 61);			//first left attack...
	player.SetAnchorOffset({ -23, -10 }, 48);			//second left attack...
	player.SetAnchorOffset({ -26, -5 }, 34);			//last left attack...

	player.SetAnchorOffset({ 4, 0 }, 62);				//last right attack...
	player.SetAnchorOffset({ 2, -10 }, 49);			//second right attack...
	player.SetAnchorOffset({ -11, -13 }, 35);			//first right attack...=>2
	
	player.AddCollidableEntity(tree);
	player.AddCollidableEntity(boulder);
	player.AddCollidableEntity(buildingBlueRoof);
	player.AddCollidableEntity(buildingLibrary);
	player.AddCollidableEntity(buildingBrickHouse);
	player.AddCollidableEntity(buildingWoodHouse);
	player.AddCollidableEntity(blueRoofLeftFence);
	player.AddCollidableEntity(blueRoofRightFence);
	player.AddCollidableEntity(woodHouseLeftFence);
	player.AddCollidableEntity(woodHouseRightFence);
	player.AddCollidableEntity(moveTrigger);

	// Tree
	tree.SetTexturePath("textures/tree_green.gif");
	sdlInit.LoadTexture(tree);
	tree.SetPosition({ 385, 15 });
	tree.SetSize(96, 117);
	tree.ConfigureCollision(true, false, { 0, 0 }, { 0, 20 });				// Collision set up

	// Boulder
	boulder.SetTexturePath("textures/boulder.png");
	sdlInit.LoadTexture(boulder);
	boulder.SetPosition({ 550, 550 });
	boulder.SetSize(45, 45);
	boulder.ConfigureCollision(false, true);
	
	
	buildingBlueRoof.SetTexturePath("textures/BuildingsSpriteSheet.png");
	buildingLibrary.SetTexturePath("textures/BuildingsSpriteSheet.png");
	buildingBrickHouse.SetTexturePath("textures/BrickHouse.png");
	buildingWoodHouse.SetTexturePath("textures/BuildingsSpriteSheet.png");
	blueRoofLeftFence.SetTexturePath("textures/BuildingsSpriteSheet.png");
	blueRoofRightFence.SetTexturePath("textures/BuildingsSpriteSheet.png");
	woodHouseLeftFence.SetTexturePath("textures/BuildingsSpriteSheet.png");
	woodHouseRightFence.SetTexturePath("textures/BuildingsSpriteSheet.png");
	blueDress.SetTexturePath("textures/People.png");

	//Loading textures...
	
	
	
	sdlInit.LoadTexture(buildingBlueRoof);
	sdlInit.LoadTexture(buildingLibrary);
	sdlInit.LoadTexture(buildingBrickHouse);
	sdlInit.LoadTexture(buildingWoodHouse);
	sdlInit.LoadTexture(blueRoofLeftFence);
	sdlInit.LoadTexture(blueRoofRightFence);
	sdlInit.LoadTexture(woodHouseLeftFence);
	sdlInit.LoadTexture(woodHouseRightFence);
	sdlInit.LoadTexture(blueDress);

	//Setting position information...
	
	
	
	buildingBlueRoof.SetPosition({ 484, 13 });
	buildingLibrary.SetPosition({ 373, 284 });
	buildingBrickHouse.SetPosition({ 24, 11 });
	buildingWoodHouse.SetPosition({ 187, 284 });
	blueRoofLeftFence.SetPosition({ 489, 132 });
	blueRoofRightFence.SetPosition({ 585, 132 });
	woodHouseLeftFence.SetPosition({ 178, 390 });
	woodHouseRightFence.SetPosition({ 271, 390 });
	blueDress.SetPosition({ 550, 200 });
	moveTrigger.SetPosition({ 600, 600 });

	//Setting size information...
	
	
	
	buildingBlueRoof.SetSize(150, 150);
	buildingLibrary.SetSize(150, 150);
	buildingBrickHouse.SetSize(150, 200);
	buildingWoodHouse.SetSize(115, 145);
	blueRoofLeftFence.SetSize(40, 25);
	blueRoofRightFence.SetSize(40, 25);
	woodHouseLeftFence.SetSize(40, 25);
	woodHouseRightFence.SetSize(40, 25);
	blueDress.SetSize(28, 45);
	moveTrigger.SetSize(45, 45);


	//Set sprite sheet texture coordinates...
	buildingBlueRoof.InitSpriteSheet(0, 1, 1);
	buildingBlueRoof.SetSpriteClip(352, 191, 95, 95, 0);

	buildingLibrary.InitSpriteSheet(0, 1, 1);
	buildingLibrary.SetSpriteClip(112, 439, 95, 80, 0);

	buildingWoodHouse.InitSpriteSheet(0, 1, 1);
	buildingWoodHouse.SetSpriteClip(109, 288, 64, 80, 0);

	blueRoofLeftFence.InitSpriteSheet(0, 1, 1);
	blueRoofLeftFence.SetSpriteClip(2, 329, 24, 15, 0);

	blueRoofRightFence.InitSpriteSheet(0, 1, 1);
	blueRoofRightFence.SetSpriteClip(2, 329, 24, 15, 0);

	woodHouseLeftFence.InitSpriteSheet(0, 1, 1);
	woodHouseLeftFence.SetSpriteClip(2, 329, 24, 15, 0);

	woodHouseRightFence.InitSpriteSheet(0, 1, 1);
	woodHouseRightFence.SetSpriteClip(2, 329, 24, 15, 0);

	blueDress.InitSpriteSheet(0, 2, 4);
	blueDress.SetSpriteClip(100, 391, 16, 25, 0);	//right
	blueDress.SetSpriteClip(124, 391, 16, 25, 1);	//right move
	blueDress.SetSpriteClip(100, 424, 16, 25, 2);	//up
	blueDress.SetSpriteClip(124, 424, 16, 25, 3);	//up move
	blueDress.SetSpriteClip(100, 456, 16, 25, 4);	//left
	blueDress.SetSpriteClip(124, 456, 16, 25, 5);	//left move
	blueDress.SetSpriteClip(100, 487, 16, 25, 6);	//down
	blueDress.SetSpriteClip(124, 487, 16, 25, 7);	//down move

	//Setup collision...
	
	
	
	buildingBlueRoof.ConfigureCollision(true, false, { 0, 0 }, { 0, 32 });
	buildingLibrary.ConfigureCollision(true, false, { 0, 1, }, { 0, 35 });
	buildingBrickHouse.ConfigureCollision(true, false, { 0, 0 }, { 0, 88 });
	buildingWoodHouse.ConfigureCollision(true, false, { 0, 0 }, { 0, 35 });
	blueRoofLeftFence.ConfigureCollision(true, false, { 0, 0 }, { 0, 4 });
	blueRoofRightFence.ConfigureCollision(true, false, { 0, 0 }, { 0, 4 });
	woodHouseLeftFence.ConfigureCollision(true, false, { 0, 0 }, { 0, 4 });
	woodHouseRightFence.ConfigureCollision(true, false, { 0, 0 }, { 0, 4 });
	blueDress.ConfigureCollision(true, true);
	moveTrigger.ConfigureCollision(false, false);



	blueDress.AddCollidableEntity(tree);
	blueDress.AddCollidableEntity(boulder);
	blueDress.AddCollidableEntity(buildingBlueRoof);
	blueDress.AddCollidableEntity(buildingLibrary);
	blueDress.AddCollidableEntity(buildingBrickHouse);
	blueDress.AddCollidableEntity(buildingWoodHouse);
	blueDress.AddCollidableEntity(blueRoofLeftFence);
	blueDress.AddCollidableEntity(blueRoofRightFence);
	blueDress.AddCollidableEntity(woodHouseLeftFence);
	blueDress.AddCollidableEntity(woodHouseRightFence);
	blueDress.AddCollidableEntity(player);

	moveTrigger.SetMovePos({960, 200});

	//TODO: Don't hard-code this...
	gWorld.InitWorldGrid({ 0, 70 - 35, 14, 70 - 16});
}

bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup();
	if (initSuccess) {
		InitEntities();
	}

	return initSuccess;
}

void GameManager::Cleanup(){
	sdlInit.CleanupSprite(player);
	sdlInit.CleanupSprite(tree);
	sdlInit.CleanupSprite(boulder);
	sdlInit.CleanupSprite(buildingBlueRoof);
	sdlInit.CleanupSprite(buildingLibrary);
	sdlInit.CleanupSprite(buildingBrickHouse);
	sdlInit.CleanupSprite(buildingWoodHouse);
	sdlInit.CleanupSprite(blueRoofLeftFence);
	sdlInit.CleanupSprite(blueRoofRightFence);
	sdlInit.CleanupSprite(woodHouseLeftFence);
	sdlInit.CleanupSprite(woodHouseRightFence);
	sdlInit.CleanupSprite(blueDress);
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	tree.Update();
	boulder.Update();
	player.Update();
	buildingBlueRoof.Update();
	buildingLibrary.Update();
	buildingBrickHouse.Update();
	buildingWoodHouse.Update();
	blueRoofLeftFence.Update();
	blueRoofRightFence.Update();
	woodHouseLeftFence.Update();
	woodHouseRightFence.Update();
	blueDress.Update();

	//Needs to come last...
	gCamera.LookAt(player);

	gCamera.RestrictTargetToCamera(blueDress);

	sdlInit.Update();
}

void GameManager::Render(){
	sdlInit.Render();

	sdlInit.DrawSprite(tree);
	sdlInit.DrawSprite(boulder);
	sdlInit.DrawSprite(buildingBlueRoof);
	sdlInit.DrawSprite(buildingLibrary);
	sdlInit.DrawSprite(buildingBrickHouse);
	sdlInit.DrawSprite(buildingWoodHouse);
	sdlInit.DrawSprite(blueRoofLeftFence);
	sdlInit.DrawSprite(blueRoofRightFence);
	sdlInit.DrawSprite(woodHouseLeftFence);
	sdlInit.DrawSprite(woodHouseRightFence);
	sdlInit.DrawSprite(blueDress);
	sdlInit.DrawSprite(player);


	//Needs to come last...
	if (SHOW_COLLIDERS) {
		sdlInit.DrawEntityCollider(moveTrigger);
		sdlInit.DrawEntityCollider(tree);
		sdlInit.DrawEntityCollider(boulder);
		sdlInit.DrawEntityCollider(buildingBlueRoof);
		sdlInit.DrawEntityCollider(buildingLibrary);
		sdlInit.DrawEntityCollider(buildingBrickHouse);
		sdlInit.DrawEntityCollider(buildingWoodHouse);
		sdlInit.DrawEntityCollider(blueRoofLeftFence);
		sdlInit.DrawEntityCollider(blueRoofRightFence);
		sdlInit.DrawEntityCollider(woodHouseLeftFence);
		sdlInit.DrawEntityCollider(woodHouseRightFence);
		sdlInit.DrawEntityCollider(blueDress);
		sdlInit.DrawEntityCollider(player);
	}
}