#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <windows.h>
#include "IL/il.h"
using namespace std;

#define PDD pair <double, double>
#define PI 2.0 * acos(0.0)
#define groundLimit 100

bool isInRange(double x, double l, double r) {
	return (x >= l && x <= r);
}

double degToRad(double x) {
	return (PI/180.0)*x;
}

double getRandom(int l, int r) {
	return (l + (rand()%(r - l))) * 1.0;
}

double getSquare(double x) {
	return x * x;
}

double dis(double x1, double y1, double x2, double y2) {
	return sqrt(getSquare(x1 - x2) + getSquare(y1 - y2));
}

class Color {
public:
	double r, g, b, a;
	Color(double _r = 0, double _g = 0, double _b = 0, double a = 1) {
		r = _r / 255.0;
		g = _g / 255.0;
		b = _b / 255.0;
	}
};

class Position {
public:
	double x, y;
	Position(double _x = 0, double _y = 0) {
		x = _x / 700;
		y = _y / 700;
	}
};

void drawText(string s, double x, double y) {
	glColor3f(1, 0, 0);
	glRasterPos2f(x,y);
	for (char c:s) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
	}
}

void setDefault(Position pos, double angle, Color col) {
	glColor3f(col.r, col.g, col.b);
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle, 0, 0, 1);
}

void circle(double r, Position pos, double angle, Color col) {
	glPushMatrix();
	double step = PI/1000;

	setDefault(pos, angle, col);

	glBegin(GL_TRIANGLES);
		for (double i = 0; i < 2.0 * PI; i += step) {
			glVertex2f(0, 0);
			glVertex2f(r * cos(i), r * sin(i));
			glVertex2f(r * cos(i + step), r * sin(i + step));
		}
	glEnd();
	glPopMatrix();
}

void Rectangle(double h, double w, Position pos, double angle, Color col) {
	glPushMatrix();

	w /= 2;
	h /= 2;
	setDefault(pos, angle, col);

	glBegin(GL_POLYGON);
		glVertex2f(w, -h);
		glVertex2f(w, h);
		glVertex2f(-w, h);
		glVertex2f(-w, -h);
	glEnd();
	glPopMatrix();
}

double sq(double x) {
	return x * x;
}

void ellipse(double A, double B, Position pos, double angle, Color col) {
	glPushMatrix();
	setDefault(pos, angle, col);

	glBegin(GL_POLYGON);
		for (double x = -A; x <= A; x += 0.001) {
			glVertex2f(x, -B * sqrt(1 - sq(x) / sq(A)));
		}

		for (double x = A; x >= -A; x -= 0.001) {
			glVertex2f(x, +B * sqrt(1 - sq(x) / sq(A)));
		}
	glEnd();
	glPopMatrix();
}

void cloud(Position pos) {
	Color w = Color(255, 255, 255);
	glPushMatrix();
		setDefault(pos, 0, w);
		double r = 40;
		circle(r, Position(0, 10), 0, w);
		circle(r, Position(60, 0), 0, w);
		circle(r, Position(-60, 0), 0, w);
	glPopMatrix();
}

void hill(int x) {
	Color w = Color(79, 17, 138);
	glPushMatrix();
		setDefault(Position(x, groundLimit), 0, w);
		ellipse(10, 20, Position(0, 80), 0, Color(171, 129, 235));
		ellipse(8, 20, Position(10, 80), 40, Color(171, 129, 235));
		ellipse(8, 20, Position(-10, 80), -40, Color(171, 129, 235));

		setDefault(Position(), 0, w);
		glBegin(GL_TRIANGLES);
			glVertex2f(-80, 0);
			glVertex2f(80, 0);
			glVertex2f(0, 100);
		glEnd();
	glPopMatrix();
}

void drawBackground() {
	cloud(Position(0, 500));
	cloud(Position(-500, 600));
	cloud(Position(-400, 400));
	cloud(Position(-200, 250));
	cloud(Position(100, 700));
	cloud(Position(300, 600));
	cloud(Position(350, 300));
	cloud(Position(700, 400));

	hill(0);
	hill(-200);
	hill(-450);
	hill(-650);
	hill(250);
	hill(450);
	hill(700);

//	circle(50, PosCition(0, 500), 0, Color(255, 255, 255));
	Rectangle(1400, INT_MAX, Position(0, 700+groundLimit), 0, Color(135, 206, 235));
	Rectangle(1400, INT_MAX, Position(0, groundLimit - 700), 0, Color(81, 153, 0));
	cloud(Position(0, 500));
}
#endif // SHAPE_H_INCLUDED
