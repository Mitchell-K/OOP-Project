#include "Game.h"

//Delete this
#include <iostream>
using namespace std;

Game::Game(int width, int height) {
	//Constructor

    //Platform
    plat = new Platform("images/plat.jpg", -0.125, -0.81, 0.05, 0.25);
	//Initial x, y coords for ball
	Vec center((plat->getX() + (plat->getW()/2)), (plat->getY() + 0.025 + 0.0001));
	//Ball
	ball = new Ball("images/ball.png", center, 0.025, 10);

	// Load levels
	GameLevel one; one.Load("levels/one.lvl", this->width, this->height * 0.5);
    	//GameLevel two; two.Load("levels/two.lvl", this->width, this->height * 0.5);
    	//GameLevel three; three.Load("levels/three.lvl", this->width, this->height * 0.5);
    	//GameLevel four; four.Load("levels/four.lvl", this->width, this->height * 0.5);
    	levels.push_back(one);
    	//levels.push_back(two);
    	//levels.push_back(three);
    	//levels.push_back(four);
    	level = 0;
	this->width = width;
	this->height = height;

	ballSpeed = 0.005;
	platSpeed = 0.015;
	resetMark = true;	

	lives = 3;
	setLivesDisp("images/lives3.png");

	end = false;
	setEndDisp("images/end.png");

	setBackDisp("images/factory.jpg");
}

Game::Game(const char* platPic, const char* ballPic, const char* backgroundPic) {
	//Constructor

    //Platform
    plat = new Platform(platPic, -0.125, -0.81, 0.05, 0.25);
	//Initial x, y coords for ball
	Vec center((plat->getX() + (plat->getW()/2)), (plat->getY() + 0.025 + 0.0001));
	//Ball
	ball = new Ball(ballPic, center, 0.025, 10);
	

	ballSpeed = 0.005;
	platSpeed = 0.015;
	resetMark = true;	

	lives = 3;
	setLivesDisp("images/lives3.png");

	end = false;
	setEndDisp("images/end.png");

	setBackDisp(backgroundPic);

}

Game::~Game() { 
	//Destructor
	delete plat;
	delete ball;
}

/*
bool Game::isWinner() {

	bool notWin = false;

	for (int i = 0; i < blockVec.size(); i++) {
		if (blockVec.at(i).broke() == false) {
			notWin = true;
			break;
		}
	}

	if (notWin == true)
		return false;
	else 
		return true;
}
*/

void Game::setBackDisp(const char* bgPic) {
	//Sets background image
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    background_id = SOIL_load_OGL_texture (
    	bgPic,
    	SOIL_LOAD_AUTO,
    	SOIL_CREATE_NEW_ID,
     	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void Game::displayBackground() {
	//Displays background image
	glBindTexture( GL_TEXTURE_2D, background_id );
    glEnable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex2f(-1.0, -1.0);
    
    glTexCoord2f(0, 1);
    glVertex2f(-1.0, 1.0);
    
    glTexCoord2f(1, 1);
    glVertex2f(1.0, 1.0);
    
    glTexCoord2f(1, 0);
    glVertex2f(1.0, -1.0);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void Game::setLivesDisp(const char* livesPic) {
	//Sets lives image
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    lives_id = SOIL_load_OGL_texture (
    	livesPic,
    	SOIL_LOAD_AUTO,
    	SOIL_CREATE_NEW_ID,
     	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void Game::displayLives() {
	//Displays lives image
	glBindTexture( GL_TEXTURE_2D, lives_id );
    glEnable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex2f(0.7, 0.7);
    
    glTexCoord2f(0, 1);
    glVertex2f(0.7, 1.0);
    
    glTexCoord2f(1, 1);
    glVertex2f(1.0, 1.0);
    
    glTexCoord2f(1, 0);
    glVertex2f(1.0, 0.7);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void Game::draw() {
	//Main draw fcn
	displayBackground();

	plat->print();
	ball->print();
	levels[level].draw();

	displayLives();

	if (end)
		displayEnd();
}

void Game::resetLevel(){
    if (this->level == 0)this->levels[0].Load("levels/one.lvl", this->width, this->height * 0.5f);
    else if (this->level == 1)
        this->levels[1].Load("levels/two.lvl", this->width, this->height * 0.5f);
    else if (this->level == 2)
        this->levels[2].Load("levels/three.lvl", this->width, this->height * 0.5f);
    else if (this->level == 3)
        this->levels[3].Load("levels/four.lvl", this->width, this->height * 0.5f);
}

void Game::movePlatform(float m) {
	//moves the plat if game is still in progress
	if (end == true)
		end = true;
	else {
		plat->move(m);
		if (resetMark == true) {
			ball->setX(plat->getX() + (plat->getW()/2));
			ball->setY(plat->getY() + ball->getRadius() + 0.0001);
			ball->print();
		}
	}
}

void Game::moveBall() {
	//Moves the ball if game is still in progress
	if (end == true)
		end = true;
	else
		ball->jump();
}

void Game::collision(){
	//Collision of the ball with the platforms and blocks
	float mx = ball->getX();
	float my = ball->getY();
	float rad = ball->getRadius();

	if (plat->contains((mx - rad), (my - rad)) || plat->contains((mx + rad), (my - rad))) {
		//Ball hits platform

		if (ball->getXinc() == 0.0)	//Incase of reset allows ball to move in x direction
			ball->setXinc(0.01);

		ball->setRising(true);

		if (mx > plat->getX() && mx <= (plat->getX() + (plat->getW() / 2))) {
			if (ball->getMoveLeft())
				ball->setXinc(ballSpeed);

			if (!(ball->getMoveLeft()))
				ball->setXinc(-1 * ballSpeed);
		}
		else if (mx > (plat->getX() + (plat->getW() / 2)) && mx <= (plat->getX() + plat->getW())){
			if (ball->getMoveLeft())
				ball->setXinc(-1 * ballSpeed);

			if (!(ball->getMoveLeft()))
				ball->setXinc(ballSpeed);
		}

	}
/*
	for (Brick &box : levels[level].bricks) {
            if (!box.isDestroyed()) {
		// If collision is true
                if (box.contains((mx - rad), (my - rad)) || box.contains((mx + rad), (my - rad))) {
                    // Destroy block if not solid
                    if (!box.isSolid()) {
                        box.setDestroyed(true);
                    //spawnPowerUps(box);
                    }
		}
                // Collision resolution
		if (ball->getMoveLeft())
		    ball->setMoveLeft(false);

		if (!(ball->getMoveLeft()))
		    ball->setMoveLeft(true);

		if (ball->getRising())
		    ball->setRising(false);

		if (!(ball->getRising()))
		    ball->setRising(true);
      
            }
        }
*/

	if (my < (plat->getY() - plat->getH())) {
		reset();	//Resets if ball goes under platform
		--lives;

		if (lives == 2)
			setLivesDisp("images/lives2.png");
		if (lives == 1)
			setLivesDisp("images/lives1.png");
		if (lives == 0)
			end = true;
	}
}

void Game::reset() {
	//Resets the game after each life is lost
	ball->setX(plat->getX() + (plat->getW()/2));
	ball->setY(plat->getY() + ball->getRadius() + 0.0001);
	ball->stop();
	ball->print();
	resetMark = true;
}

void Game::setEndDisp(const char* endPic) {
	//Sets end game image
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    end_id = SOIL_load_OGL_texture (
    	endPic,
    	SOIL_LOAD_AUTO,
    	SOIL_CREATE_NEW_ID,
     	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void Game::displayEnd() {
	//Displays end game image
	glBindTexture( GL_TEXTURE_2D, end_id );
    glEnable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex2f(-0.2, -0.2);
    
    glTexCoord2f(0, 1);
    glVertex2f(-0.2, 0.2);
    
    glTexCoord2f(1, 1);
    glVertex2f(0.2, 0.2);
    
    glTexCoord2f(1, 0);
    glVertex2f(0.2, -0.2);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

bool Game::newResetMark() {
	if (resetMark) {
		ball->setYinc(2 * ballSpeed);
		resetMark = false;
		return true;
	}
	return false;
}

void Game::setBallSpeed(float ballSpeed) {
	this->ballSpeed = ballSpeed;
}
void Game::setPlatSpeed(float platSpeed) {
	this->platSpeed = platSpeed;
}

float Game::getBallSpeed() const {
	return ballSpeed;
}
float Game::getPlatSpeed() const {
	return platSpeed;
}

