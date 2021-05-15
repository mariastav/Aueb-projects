#pragma once
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "invader.h"
#include "egg.h"

class Game
{
	typedef enum{STATUS_START, STATUS_PLAYING_A, STATUS_PLAYING_B, STATUS_GAMEOVER} status_t;
	//epeidh o player mporei na ksekinaei to paixnidi kai na mhn yparxei h na katastrefete prepei na ton kanoyme pointer
	Player* player = nullptr;
	bool player_initialized = false; //metablhth poy mas deixnei oti o paikths exei dhmiourghthei
	bool debug_mode = false;

	Bullet* bullet = nullptr;
	void spawnBullet();
	void checkBullet();

	Egg* egg = nullptr;
	void spawnEgg();
	void checkEgg();

	//vector <Invader> ve;
	Enemy* meteorite = nullptr;
	Invader* chicken = nullptr;
	int chicken_counter = 2;

	float score = 0.0f;
	float highScore = 0.0f;

	void spawnChicken();
	void checkChicken();

	void spawnMeteorite();
	void checkMeteorite();

	bool checkCollisionPlayer_Meteorite();
	bool checkCollisionPlayer_Chicken();
	bool checkCollisionPlayer_EnemyBullet();
	bool checkCollisionBullet_Meteorite();
	bool checkCollisionBullet_Chicken();
	
	status_t status = STATUS_START;

	unsigned int window_width = WINDOW_WIDTH, window_height = WINDOW_HEIGHT;

	void updateStartScreen();
	void updateLevelAScreen();
	void updateLevelBScreen();
	void updateGameOverScreen();

	void drawStartScreen();
	void drawLevelAScreen();
	void drawLevelBScreen();
	void drawGameOverScreen();

public:
	void setDebugMode(bool d) {
		debug_mode = d;
	}
	bool getDebugMode() const {
		return debug_mode;
	}
	void update();
	void draw();
	void init();
	unsigned int getWindowWidth() { return window_width; }
	unsigned int getWindowHeight() { return window_height; }
	float window2canvasX(float x); //metatroph monadwn
	float window2canvasY(float y);
	//enhmerwnw to game otan h syntetagmenes allazoun
	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w; window_height = h; }
	Game();
	~Game(); //destructor
};