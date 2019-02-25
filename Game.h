#ifndef GAME_H
#define GAME_H

//#include "Block.h"
#include "Ball.h"
#include "Platform.h"
#include "GameLevel.h"
#include <vector>


#if defined WIN32
#include <freeglut.h>
#include "../windows/SOIL.h"
#elif defined __APPLE__
#include <GLUT/glut.h>
#include <SOIL.h>
#else
#include <GL/freeglut.h>
#include <SOIL.h>
#endif

class Game {
    Platform* plat;
    Ball* ball;

    std::vector<GameLevel> levels;
    int width, height;
    int level;

    float ballSpeed;
    float platSpeed;

    bool resetMark;

    int lives;
    bool end;
	GLuint lives_id;
	GLuint end_id;
	GLuint background_id;

	void setLivesDisp(const char*);
	void displayLives();

	void setEndDisp(const char*);
	void displayEnd();

	void setBackDisp(const char*);
	void displayBackground();

public:

	Game(int, int);

	Game(const char*, const char*, const char*);

	~Game();

	//bool isWinner();	//Checks if all the blocks are broken

	void draw();

	void movePlatform(float);
	void moveBall();

	void collision();
	void resetLevel();

	void reset();

	bool newResetMark();

	void setBallSpeed(float);
	void setPlatSpeed(float);

	float getBallSpeed() const;
	float getPlatSpeed() const;
};

#endif
