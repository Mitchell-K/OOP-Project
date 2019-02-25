#include "App.h"

static App* singleton;

void movePlat(int value) {
    if (singleton->moving)
        singleton->newGame->moveBall();
    
    if (singleton->left)
        singleton->newGame->movePlatform(-1 * singleton->newGame->getPlatSpeed());
    if (singleton->right)
       singleton->newGame->movePlatform(singleton->newGame->getPlatSpeed());

    if (singleton->left || singleton->right || singleton->moving) {
        singleton->redraw();
        glutTimerFunc(32, movePlat, value);
    }
}

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h) {
    // Initialize state variables
    singleton = this;
    mx = 0.0;
    my = 0.0;

    left = right = false;   //platform movement
    moving = false;         //ball movement


    newGame = new Game(w, h);
    //newGame = new Game("images/plat.jpg", "images/ball.png", "images/factory.jpg");
}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    newGame->draw();

    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::specialKeyPress(int key) {
    if (key == 100) //Move Plat left
        left = true;
    if (key == 102) //Move Plat right
        right = true;

    movePlat(1);
}

void App::specialKeyUp(int key) {
    //Stops moving the platform
    if (key == 100)
        left = false;
    if (key == 102)
        right = false;
}

void App::idle() {
    newGame->collision();
    //if (!newGame->isLoser())              //int and display lives
        //Play end animation        
}

void App::keyPress(unsigned char key) {
    if (key == 27) { //Esc Key
        delete newGame;
        exit(0);
    }

    if (key == ' '){                        //
        moving = true;
        if (newGame->newResetMark())
            movePlat(1);
    }
}
