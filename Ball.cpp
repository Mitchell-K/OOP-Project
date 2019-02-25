#include "Ball.h"

Ball::Ball(const char* ballPic, const Vec& center, float radius, int resolution=10) {

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    ball_id = SOIL_load_OGL_texture (
        ballPic,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    x = center.getX();
    y = center.getY();
    this->radius = radius;
    this->resolution = resolution;

    rising = true;
    moveLeft = true;

    xinc = 0.0;
    yinc = 0.01;
}

Ball::~Ball() { }

void Ball::reConfig(){
    int half = resolution / 2;
    float xPoints, yPoints;

    points.clear();

    for (int i = 0; i < resolution; i++) {
        //if statemented needed cuz sin(M_PI) is dumb
        if (cos((i * M_PI) / half) == 1 || cos((i * M_PI) / half) == -1) {
            xPoints = ( x + (radius * (cos((i * M_PI) / half))) );
            yPoints = (0.0 + y);
        }
        else {
            xPoints = ( x + (radius * (cos((i * M_PI) / half))) );
            yPoints = ( y + (radius * (sin((i * M_PI) / half))) );
        }
            points.push_back(new Vec(xPoints, yPoints));
    }
}

void Ball::print() {

    glBindTexture( GL_TEXTURE_2D, ball_id );
    glEnable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex2f(x - radius, y - radius);
    
    glTexCoord2f(0, 1);
    glVertex2f(x - radius, y + radius);
    
    glTexCoord2f(1, 1);
    glVertex2f(x + radius, y + radius);
    
    glTexCoord2f(1, 0);
    glVertex2f(x + radius, y - radius);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

bool Ball::contains(float mx, float my) const {
    return mx >= x && mx <= x + radius && my <= y && my >= y - radius;
}

void Ball::jump() {

    if(rising) {
        y += yinc;
        if (moveLeft)
            x -= xinc;
        else
            x += xinc;
    }
    else {
        y -= yinc;
        if (moveLeft)
            x -= xinc;
        else
            x += xinc;
    }
    
    if (y > 0.99) {
    	if (getXinc() == 0.0)
			setXinc(0.01);
        rising = false;
    }
    if ((y - radius) < -0.99) // Maybe delete?
        rising = true;

    if (x < -0.99){
    	if (moveLeft)
        	moveLeft = false;
        else
        	moveLeft = true;
    }
    if (x + radius > 0.99) {
    	if (moveLeft)
        	moveLeft = false;
        else
        	moveLeft = true;
    }
}

void Ball::stop() {
    xinc = 0.0;
    yinc = 0.0;
    rising = true;
}

void Ball::setRadius(float radius) {
    this->radius = radius;
}
void Ball::setX(float x) {
    this->x = x;
}
void Ball::setY(float y) {
    this->y = y;
}
void Ball::setRising(bool rising) {
    this->rising = rising;
}
void Ball::setMoveLeft(bool moveLeft) {
    this->moveLeft = moveLeft;
}
void Ball::setXinc(float xx) {
    if (xinc + xx > 0)
        xinc += xx;
}
void Ball::setYinc(float yy) {
    if (yinc + yy > 0)
        yinc += yy;
}

float Ball::getRadius() const {
    return radius;
}
float Ball::getX() const {
    return x;
}
float Ball::getY() const {
    return y;
}
bool Ball::getRising() const {
    return rising;
}
bool Ball::getMoveLeft() const {
    return moveLeft;
}
float Ball::getXinc() const {
    return xinc;
}
float Ball::getYinc() const {
    return yinc;
}