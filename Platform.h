#ifndef PLATFORM_H
#define PLATFORM_H

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

class Platform {
    	float x, y, h, w;
    	GLuint plat_id;
public:

	Platform(const char*, float, float, float, float);

	~Platform();

	bool contains(float, float) const;

	void print();
	void move(float);

	void setX(int);
	void setY(int);
	void setH(int);
	void setW(int);

	float getX() const;
	float getY() const;
	float getH() const;
	float getW() const;
};

#endif
