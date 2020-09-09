#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "Shape.h"

class Person {
public:
	double x, y;
	Color bodyColor, clothColor;
	Person(double _x = 0, double _y = 0, Color c = Color(34, 179, 121)) {
		x = _x;
		y = _y;
		bodyColor = Color(255, 227, 159);
		clothColor = c;
	}

	double xLeft() {
		return x - 40;
	}

	double xRight() {
		return x + 40;
	}

	double yUp() {
		return y + 50;
	}

	double yDown() {
		return y - 230;
	}

	void draw() {
		glPushMatrix();
		setDefault(Position(x, y), 0, Color());

		circle(5, Position(-15, 10), 0, Color(0, 0, 1));	//	left eye
		circle(5, Position(15, 10), 0, Color(0, 0, 1));		//	right eye
		glBegin(GL_POLYGON);
			glColor3f(bodyColor.r, bodyColor.g, bodyColor.b);
			double r = 50.0;
			for (double x = r; x >= r/1.3; x -= 0.01) {
				glVertex2f(x, sqrt(r*r - x * x));
			}
			for (double x = -r/1.3; x >= -r; x -=0.01) {
				glVertex2f(x, sqrt(r*r - x*x));
			}
		glEnd();

		circle(50, Position(), 0, clothColor);	//	head
		ellipse(30, 70, Position(0, -100), 0, clothColor);	//	body

		ellipse(10, 40, Position(40, -100), 30, clothColor);	//	left hand
		ellipse(10, 40, Position(-40, -100), -30, clothColor);	//	right hand


		ellipse(10, 50, Position(30, -180), 30, clothColor);	//	left leg
		ellipse(10, 50, Position(-30, -180), -30, clothColor);	//	right leg
		Rectangle(30, 30, Position(0, -155), 0, clothColor);
		glPopMatrix();
	}
};

class Kunai {
public:
	double x, y;
	int mult;
	Kunai(double _x = 0, double _y = 0, int m = 1.0) {
		x = _x;
		y = _y;
		mult = m;
	}

	double xLeft() {
		if (mult == 1) {
			return x - 4;
		}
		else {
			return x - 70;
		}
	}

	double xRight() {
		if (mult == 1) {
			return x + 70;
		}
		else {
			return x + 4;
		}
	}

	double yUp() {
		return y + 8;
	}

	double yDown() {
		return y - 8;
	}

	void draw() {
		glPushMatrix();
		setDefault(Position(x, y), 0, Color());

		circle(4, Position(0, 0), 0, Color(255, 255, 255));
		circle(8, Position(0, 0), 0, Color(0, 0, 0));

		if (mult == 1) {
			Rectangle(10, 20, Position(10, 0), 0, Color(255, 0, 0));
			setDefault(Position(), 0, Color(0, 0, 0));
			glBegin(GL_TRIANGLES);
				glVertex2f(20, 8);
				glVertex2f(20, -8);
				glVertex2f(70, 0);
			glEnd();
		}
		else {
			Rectangle(10, 20, Position(-10, 0), 0, Color(255, 0, 0));
			setDefault(Position(), 0, Color(0, 0, 0));
			glBegin(GL_TRIANGLES);
				glVertex2f(-70, 0);
				glVertex2f(-20, -8);
				glVertex2f(-20, 8);
			glEnd();
		}
		glPopMatrix();
	}
};
#endif // PERSON_H_INCLUDED
