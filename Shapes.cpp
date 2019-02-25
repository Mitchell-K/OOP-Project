#include "Shapes.h"

Shapes::Shapes() {
	r = 1.0;
	g = 1.0;
	b = 1.0;
}

Shapes::Shapes(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

Shapes::~Shapes() { }


void Shapes::setR(int r) {
	this->r = r;
}
void Shapes::setG(int g) {
	this->g = g;
}
void Shapes::setB(int b) {
	this->b = b;
}

float Shapes::getR() const {
	return r;
}
float Shapes::getG() const {
	return g;
}
float Shapes::getB() const {
	return b;
}