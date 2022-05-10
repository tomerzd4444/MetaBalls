#include "Blob.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <cstdlib>

const int randPerc = 500;
const float randDiv = 10000;
const float rad = 0.15;

MetaBalls::Blob::Blob()
{
	this->pos = new float[2]{ rand() % randPerc / randDiv - randPerc / (2 * randDiv), rand() % randPerc / randDiv - randPerc / (2 * randDiv) };
	this->vel = new float[2]{ rand() % randPerc / randDiv - randPerc / (2 * randDiv), rand() % randPerc / randDiv - randPerc / (2 * randDiv) };
	this->r = rad;
}

MetaBalls::Blob::Blob(float position[])
{
	this->pos = position;
	this->vel = new float[2]{ rand() % randPerc / randDiv - randPerc / (2 * randDiv), rand() % randPerc / randDiv - randPerc / (2 * randDiv) };
	this->r = rad;
}

MetaBalls::Blob::Blob(float x, float y)
{
	this->pos = new float[2]{ x, y };
	this->vel = new float[2]{ rand() % randPerc / randDiv - randPerc / (2 * randDiv), rand() % randPerc / randDiv - randPerc / (2 * randDiv) };
	this->r = rad;
}

void MetaBalls::Blob::show()
{
	int iter = 100;
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 1);
	for (int i = 0; i < iter; i++) {
		float theta = 2.0f * 3.14159265f * float(i) / float(iter);
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(x + pos[0], y + pos[1]);
	}
	glEnd();
}

void MetaBalls::Blob::update()
{
	pos[0] += vel[0];
	pos[1] += vel[1];
	if (pos[0] > 1 - r || pos[0] < -1 + r) {
		vel[0] *= -1;
	}
	if (pos[1] > 1 - r || pos[1] < -1 + r) {
		vel[1] *= -1;
	}
}
