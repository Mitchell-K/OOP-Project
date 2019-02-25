#include "Brick.h"

Brick::Brick(const char* brick_id, float x, float y, float h, float w, float r, float g, float b){

    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->r = r;
    this->g = g;
    this->b = b;

    this->brick_id = SOIL_load_OGL_texture (
        brick_id,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    solid = destroyed = false;
}



void Brick::draw(){
    
    glBindTexture( GL_TEXTURE_2D, brick_id );
    glEnable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);
    glColor4f(r, g, b, 1);
    glTexCoord2f(0, 0);
    glVertex2f(x, y - h);
    
    glTexCoord2f(0, 1);
    glVertex2f(x, y);
    
    glTexCoord2f(1, 1);
    glVertex2f(x + w, y);
    
    glTexCoord2f(1, 0);
    glVertex2f(x + w, y - h);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);	
}



void Brick::setBrick_id(GLuint){}
void Brick::setSolid(bool boo){solid = boo;}
void Brick::setDestroyed(bool boo){destroyed = boo;}

float Brick::getX() const{return x;}
float Brick::getY() const{return y;}
float Brick::getH() const{return h;}
float Brick::getW() const{return w;}

bool Brick::isSolid() const{return solid;}
bool Brick::isDestroyed() const{return destroyed;}
bool Brick::contains(float mx, float my) const {
    return mx >= x && mx <= x + w && my <= y && my >= y - h;
}
