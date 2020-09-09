#include "person.h"

#define height 700
#define width 700
#define personMovementSpeed 10
#define minDifference 100.0
#define moveMentSpeed 6
#define enemyFrequency 100

int cnt = 0, score = 0;
Person p;
bool u, d, r, l, gameOver = 0;
double angle = 0, pos = 0.0;
vector <Kunai> kunaies;
vector <Person> enemies;
double prevX = 1000.0, prevY = 1000.0;
double prevTimeMouseCLicked = -0.5;

double getTime() {
	return (long long)clock() * 1000 / CLOCKS_PER_SEC;
}

void MyKeyboardFunc(unsigned char key, int x, int y) {
	if (key == 'w')	u = 1;
	if (key == 'a') l = 1;
	if (key == 'd') r = 1;
	if (key == 's') d = 1;
}

void MyMouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && fabs(getTime() - prevTimeMouseCLicked) >= minDifference) {
		kunaies.push_back(Kunai(p.x - 20, p.y - 100, 1));
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && fabs(getTime() - prevTimeMouseCLicked) >= minDifference) {
		kunaies.push_back(Kunai(p.x + 20, p.y - 100, -1));
	}
}

void MyKeyboardUpFunc(unsigned char key, int x, int y) {
	if (key == 'w')	u = 0;
	if (key == 'a') l = 0;
	if (key == 'd') r = 0;
	if (key == 's') d = 0;
}

void init() {
    glClearColor(0.0, 0.7, 0.0, 1.0);
    glMatrixMode(GLUT_SINGLE|GLUT_RGB);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
    glOrtho(-height, height, -width, width, 0.0, 1.0);
	glutKeyboardFunc(MyKeyboardFunc);
	glutMouseFunc(MyMouseFunc);
	glutKeyboardUpFunc(MyKeyboardUpFunc);
	srand((unsigned) time(0));
//	ILboolean s;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (!gameOver) {
		p.draw();
		for (auto k:kunaies) {
			k.draw();
		}
    }
    else {
		drawText("Game Over", -50,  600);
    }

    for (auto e:enemies) {
		e.draw();
    }

	string sc;
	stringstream ss;
	ss << score;
	ss >> sc;

	string s = "Score : " + sc;
    drawText(s, 500, 650);

//	texture = LoadTexture("C:\\wazedrifat\\vscode\\opengl\\try2\\Attack__001.png", 50, 50);
//	glEnable( GL_TEXTURE_2D );
//	FreeTexture( texture );
    drawBackground();
    glutSwapBuffers();
    glFlush();
}

void reShape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    gluOrtho2D(0, 1000, 0, 500);

    glMatrixMode(GL_MODELVIEW);

}

void timer(int userLessValue) {
	glutPostRedisplay();

	for (int i = 0; i < kunaies.size();) {
		Kunai &k = kunaies[i];
		k.x += k.mult * 15.0;

		bool hit = 0;
		for (int j = 0; j < enemies.size(); j++) {
			Person &e = enemies[j];
			if (k.xRight() >= e.xLeft() && k.xLeft() <= e.xRight() && k.yDown() <= e.yUp() && k.yUp() >= e.yDown()) {
				enemies.erase(enemies.begin() + j);
				score++;
				hit = 1;
				break;
			}
		}

		if (hit || k.x >= 700) {
			kunaies.erase(kunaies.begin() + i);
		}
		else {
			i++;
		}
    }

    if (u && p.y <= groundLimit + 200)	p.y += moveMentSpeed;
    if (d && p.y >= -500)	p.y -= moveMentSpeed;
    if (r && p.x <= 650)	p.x += moveMentSpeed;
    if (l && p.x >= -650)	p.x -= moveMentSpeed;

    if (enemies.size() < 3)		cnt++;

    if (cnt == enemyFrequency) {
		cnt = 0;
		enemies.push_back(Person(getRandom(300, 650), getRandom(-500, groundLimit + 200), Color(getRandom(50, 200), getRandom(50, 200), getRandom(50, 200))));
    }

	if (gameOver)	return;

	for (auto &e:enemies) {
		double xDif = (p.x - e.x), yDif = (p.y - e.y);

		e.x += fabs(xDif)/(1.5 * xDif);
		e.y += fabs(yDif)/(1.5 * yDif);

		if (e.xRight() >= p.xLeft() && e.xLeft() <= p.xRight() && e.yDown() <= p.yUp() && e.yUp() >= p.yDown()) {
			gameOver = 1;
			kunaies.clear();
			break;
		}
	}

	glutTimerFunc(1000/60, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);

    glutInitWindowPosition(300, 0);
    glutInitWindowSize(height, width);
    glutCreateWindow("window 1");

    glutDisplayFunc(display);
    glutReshapeFunc(reShape);
    glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
}
