#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "SolidSphere.h"
#include "Arrow.h"
#include "Light.h"
#include "GameOver.h"
#include "GameClear.h"
#include "Removecontrol.h"
#include "dropcontrol.h"

using namespace std;

//time index
clock_t start = clock();
clock_t endt;
float timebarindex = 0;
int playstarttime;
int playtime;

//window setting
#define WIDTH 660
#define HEIGHT 800
#define boundaryX WIDTH/2
#define boundaryY HEIGHT/2

//frame position
Vector3 startcenter(0, -310, 0);
Vector3 nextspherecenter(-215, -350, 0);
Vector3 textframe(30, 300, 0);

//power setting
float shootpower = 25;
float anglemovementrate = 5;
float timebarrate = 0.7;
float radious = 30;

//objects
vector<SolidSphere> spheres;
vector<SolidSphere> nextspheres;
vector<SolidSphere> droppingspheres;
Light* light;
Material defaultmtl, gameovermtl;
Arrow arrow;
int score= 0;
int highscore = 0;

//detector
GameOver go; GameClear gc;
Removecontrol r;
Dropcontrol d;

void init() {
	//light init
	light = new Light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
	light->setAmbient(0.5, 0.5, 0.5, 1.0);		light->setDiffuse(0.7, 0.7, 0.7, 1.0);		light->setSpecular(1.0, 1.0, 1.0, 1.0);

	//mtl init
	defaultmtl.setEmission(0.1, 0.1, 0.1, 1);	defaultmtl.setAmbient(0.3, 0.3, 0.3, 1);
	defaultmtl.setDiffuse(0.5, 0.5, 0.5, 1);	defaultmtl.setSpecular(1.0, 1.0, 1.0, 1);	defaultmtl.setShininess(10);
		//gameovermtl
	gameovermtl.setEmission(0.1, 0.1, 0.1, 1);	gameovermtl.setAmbient(0.1, 0.1, 0.1, 1);
	gameovermtl.setDiffuse(0.1, 0.1, 0.1, 1);	gameovermtl.setSpecular(1.0, 1.0, 1.0, 1);	gameovermtl.setShininess(10);
	
	//default map
	srand((unsigned int)time(0));

	for (unsigned int i = 0; i < WIDTH / (2 * radious); i++)
		for (unsigned int j = 0; j < 6; j++)
			if ((i != WIDTH / (2 * radious) - 1 or (j % 2) != 1) && (rand() % 100 + 1) <= 80) {
				spheres.push_back(SolidSphere(radious, 50, 10));
				spheres.back().setCenter(Vector3(-boundaryX + radious + 2 * radious * i + (j % 2) * radious, 250 - radious - sqrt(3) * radious * j, 0));
				spheres.back().setVelocity(0, 0, 0);
				spheres.back().setRandomMTL();
				spheres.back().aftercollision();
			};

	//sphere init
	SolidSphere sphere1(radious, 50, 10);
	sphere1.setCenter(startcenter);				sphere1.setVelocity(0, 0, 0);		sphere1.setRandomMTL();		spheres.push_back(sphere1);

	//map spheres erase
	vector<int> mapvec;
	for (unsigned int i = 0; i < spheres.size() - 1; i++)
		if (spheres[i].getCenter()[1] == 250 - radious)
		{spheres[i].setmarked();	mapvec.push_back(i);}
	for (unsigned int i = 0; i < mapvec.size(); i++)
		d(spheres, spheres[mapvec[i]], mapvec);
	for (int i = spheres.size() - 2; i >= 0; i--)
		if (spheres[i].getmarked() == false)
			spheres.erase(spheres.begin() + i);

	//nextsphere init
	SolidSphere nextsphere(radious, 100, 10);
	nextsphere.setCenter(nextspherecenter);		nextsphere.setVelocity(0, 0, 0);	nextsphere.setRandomMTL();		nextspheres.push_back(nextsphere);
	
	//Arrow
	arrow.setArrow(25,50,10,10,100);			arrow.setCenter(startcenter);		arrow.setAngleOfArrow(0);		arrow.setMTL(defaultmtl);
	
	//play time 
	playstarttime = (unsigned int)time(0);
}

void idle() {
	endt = clock();
	if (endt - start > 1000 / 60) {
		//gameclear
		gc(spheres);
		static bool now1 = 0;
		static bool before1 = 0;
		now1= gc.getclear();
		if (gc.getclear() && now1 > before1)
		{
			if (score >= highscore) { highscore = score; };
			playtime = (unsigned int)time(0) - playstarttime;
		}
		before1 = gc.getclear();

		//gameover detection
		go(spheres[spheres.size() - (size(spheres) > 1 ? 2 : 1)], HEIGHT);

		//gameover mtl effect
		static int j = 0;
		static bool now = 0;
		static bool before = 0;
		now = go.getover();
		if (now > before) { j++; };
		before = go.getover(); //gameover될 때마다 j가 1씩 커진다.

		if (go.getover())
		{	static int i = spheres.size() - 1;
			static int jin = j;
			if (jin != j) { i = spheres.size() - 1; jin = j; };
			spheres[i].setMTL(gameovermtl);
			if (i > 0)
				i--;
			if (score >= highscore) { highscore = score; };
		}
		
		//collision handling
		for (unsigned int i = 0; i < spheres.size(); i++)
		{
			spheres[i].move();
			
			if (abs(spheres[i].getCenter()[0]) >= boundaryX - spheres[i].getProperties()[0]) {
				spheres[i].setVelocity(Vector3(-spheres[i].getVelocity()[0], spheres[i].getVelocity()[1], spheres[i].getVelocity()[2]));
			}
			else if ((spheres[i].getCenter()[1] >= boundaryY - 150 - spheres[i].getProperties()[0]) && spheres[i].getmoved() != true) {
				spheres[i].setVelocity(0, 0, 0);
				int xpos_int = (spheres[i].getCenter()[0] + boundaryX) / (2 * radious);
				spheres[i].setCenter(radious * (2 * xpos_int + 1) - boundaryX, 250 - radious, 0);
				spheres[i].aftercollision();
			};
		};
		if (spheres.size() > 2) {
			for (unsigned int i = 0; i < spheres.size() - 2; i++)
				spheres[i].collisionHandling(spheres[spheres.size() - 2]);
		}

		//auto shooting
		if(go.getover() != true && gc.getclear() != true)
			timebarindex = timebarindex + (timebarindex >= 150 ? 0 : timebarrate);
		if (timebarindex >= 150) {
			spheres.back().setVelocity(shootpower * sin(arrow.getAngleOfArrow() / 57.29577951), shootpower * cos(arrow.getAngleOfArrow() / 57.29577951), 0);

			SolidSphere s(radious, 50, 10);
			s.setCenter(startcenter);
			s.setVelocity(0, 0, 0);
			s.setMTL(nextspheres[0].getMTL());
			spheres.push_back(s);

			nextspheres[0].setRandomMTL();

			timebarindex = 0;
		};


		//droppingspheres
		for (unsigned int i = 0; i < droppingspheres.size(); i++)
		{
			droppingspheres[i].move();
			droppingspheres[i].setVelocity(droppingspheres[i].getVelocity()+Vector3(0,-2,0));
			if (droppingspheres[i].getCenter()[1] < -boundaryY - 50) {
				droppingspheres.erase(droppingspheres.begin() + i);
			}
		}
		//remove&drop algorithm
		static bool searched = false;
		static unsigned int spheressize = spheres.size();
		if (spheressize < spheres.size()) {
			searched = false;
			for (unsigned int i = 0; i < spheres.size(); i++) {
				spheres[i].resetremovesearch();
				spheres[i].resetmarked();
			};
		};
		spheressize = spheres.size();
		if (spheres[spheres.size() - (size(spheres) > 1 ? 2 : 1)].getmoved() && searched == false) {
			
			//remove
			vector<int> evec;
			r(spheres, spheres[spheres.size() - (size(spheres) > 1 ? 2 : 1)], evec);

			for (unsigned int i = 0; i < evec.size(); i++) { r(spheres, spheres[evec[i]], evec); };
			sort(evec.begin(), evec.end());

			if (evec.size() >= 2) {
				score += (1 + evec.size()) * 10;
				spheres.erase(spheres.begin() + spheres.size() - (size(spheres) > 1 ? 2 : 1));
				for (int i = evec.size() - 1; i >= 0; i--) {
					spheres.erase(spheres.begin() + evec[i]);
				};
			};
			//drop
			vector<int> dvec;
			for (unsigned int i = 0; i < spheres.size() - 1; i++)
				if (spheres[i].getCenter()[1] == 250 - radious)
				{spheres[i].setmarked();	dvec.push_back(i);}

			for (unsigned int i = 0; i < dvec.size(); i++)
				d(spheres, spheres[dvec[i]], dvec);

			for (int i = spheres.size() - 2; i >= 0; i--)
				if (spheres[i].getmarked() == false)
				{
					droppingspheres.push_back(spheres[i]);
					spheres.erase(spheres.begin() + i);
					score += 10;
				}
			searched = true;
		};

		start = endt;
	}
	glutPostRedisplay();
}

void Specialkeyboard(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT && go.getover()!=true && gc.getclear() != true) { if (arrow.getAngleOfArrow() > -70) { arrow.setAngleOfArrow(arrow.getAngleOfArrow() - anglemovementrate); } }

	else if (key == GLUT_KEY_RIGHT && go.getover() != true && gc.getclear() != true) { if (arrow.getAngleOfArrow() < 70) { arrow.setAngleOfArrow(arrow.getAngleOfArrow() + anglemovementrate); } }
	
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (spheres[spheres.size() - (size(spheres) > 1 ? 2 : 1)].getVelocity()[1] == 0 && go.getover() != true && gc.getclear() !=true) {
		if (key == 32) {
			spheres.back().setVelocity(shootpower * sin(arrow.getAngleOfArrow() / 57.29577951), shootpower * cos(arrow.getAngleOfArrow() / 57.29577951), 0);

			SolidSphere s(radious, 50, 10);

			s.setCenter(startcenter);
			s.setVelocity(0, 0, 0);
			s.setMTL(nextspheres[0].getMTL());

			spheres.push_back(s);
			
			nextspheres[0].setRandomMTL();

			timebarindex = 0;
		};
	};
	if (key == 13 && go.getover()) {
		go.reset();
		while(spheres.size()>0)
			spheres.pop_back();
		nextspheres.pop_back();
		timebarindex = 0;
		score = 0;
		init();
	};
	if (key == 13 && gc.getclear()) {
		gc.reset();
		spheres.pop_back();
		nextspheres.pop_back();
		timebarindex = 0;
		score = 0;
		init();
	};
	if (key == 27) {
		exit(0);
	}
	glutPostRedisplay();
}

void draw_characters(void* font, const char* c, float x, float y, float r, float g, float b) {
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (unsigned int i = 0; i < strlen(c); i++)
		glutBitmapCharacter(font, c[i]);
}

void renderScene() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//boundary
	glBegin(GL_QUADS);
	glColor3f(0.7,0.7,0.7);
	glVertex3f(-boundaryX, -boundaryY + 120, -20);			glVertex3f(-boundaryX, -boundaryY + 110, -20);
	glVertex3f(boundaryX , -boundaryY + 110, -20);			glVertex3f(boundaryX , -boundaryY + 120, -20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-boundaryX, boundaryY - 150, -20);			glVertex3f(-boundaryX, boundaryY - 140, -20);
	glVertex3f(boundaryX , boundaryY - 140, -20);			glVertex3f(boundaryX , boundaryY - 150, -20);
	glEnd();

	//time bar
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(textframe[0] + 10, textframe[1] + 30, -20);						glVertex3f(textframe[0] + 10, textframe[1] + 20, -20);
	glVertex3f(textframe[0] + 160 - timebarindex, textframe[1] + 20, -20);		glVertex3f(textframe[0] + 160 - timebarindex, textframe[1] + 30, -20);
	glEnd();
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//light setting
	light->draw();

	//nextsphere
	nextspheres.back().draw();

	//arrow
	arrow.draw();

	//spheres
	for (auto sph : spheres)
		sph.draw();
	//droppingspheres
	for (auto sph : droppingspheres)
		sph.draw();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
		
	//characters
	if (go.getover() or gc.getclear())
	{
		if (go.getover())
			draw_characters(GLUT_BITMAP_TIMES_ROMAN_24, "Game Over", textframe[0] - 85, textframe[1] - 300, 1 ,0 ,0);
		if (gc.getclear())
		{
			draw_characters(GLUT_BITMAP_TIMES_ROMAN_24, "Game Clear", textframe[0] - 85, textframe[1] - 300, 0, 1, 0);
			draw_characters(GLUT_BITMAP_HELVETICA_18, "PLAY TIME    :        sec", textframe[0] - 110, textframe[1] - 330, 0.5, 1, 0);
			char char_playtime[8] = { 0, };	_itoa_s(playtime, char_playtime, 10);
			draw_characters(GLUT_BITMAP_HELVETICA_18, char_playtime , textframe[0] + 20, textframe[1] - 330, 0.5, 1, 0);
		}

		draw_characters(GLUT_BITMAP_HELVETICA_18, "HIGHSCORE : ", textframe[0] - 110, textframe[1] - 350, 1, 1, 0);
		char char_highscore[8] = { 0, };	_itoa_s(highscore, char_highscore, 10);
		draw_characters(GLUT_BITMAP_HELVETICA_18, char_highscore, textframe[0] + 20, textframe[1]- 350, 1, 1, 0);
		
		static int i;
		if ((gc.getclear() or go.getover()) && i<180)
			draw_characters(GLUT_BITMAP_HELVETICA_18, "Press Enter to Restart", textframe[0] - 120, textframe[1] - 400 ,0,1,1);
		if (i >= 360)
			i = 0;
		i++;
	}
	draw_characters(GLUT_BITMAP_TIMES_ROMAN_24, "SCORE : ", textframe[0] -250, textframe[1]+20, 1, 1, 1);
	char char_score[8] = { 0, };	_itoa_s(score, char_score, 10);
	draw_characters(GLUT_BITMAP_TIMES_ROMAN_24, char_score, textframe[0] - 150, textframe[1] + 20, 1, 1, 1);
	draw_characters(GLUT_BITMAP_HELVETICA_18, "TIME", textframe[0] + 0, textframe[1]+50, 1, 1, 1);
	draw_characters(GLUT_BITMAP_HELVETICA_18, "NEXT", -280, -320, 1, 1, 1);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Bubble Shooter");
	init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(Specialkeyboard);
	glutIdleFunc(idle);
	
	// enter GLUT event processing cycle
	glutMainLoop();
	return 0;
}