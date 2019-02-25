#ifndef SHAPES_H
#define SHAPES_H

class Shapes {
protected:
	float r, g, b;

public:

	Shapes();

	Shapes(float, float, float);

	~Shapes();

	void setR(int); 
	void setG(int);
	void setB(int);

	float getR() const;
	float getG() const;
	float getB() const;

};

#endif