// Test.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Quantum.h"
#include "GxObject.hpp"
#include "GxSphere.hpp"
#include "MyGxUpdater.hpp"
#include "GxParticleParticleSpring.hpp"
#include "GxParticleFixedPointSpring.hpp"
#include "GxHalfspaceCube.hpp"
#include "Halfspace.hpp"
#include <iostream>

#include <GL/glew.h>
#ifdef _WIN32
#include <GL/wglew.h>
#endif
#if defined(__APPLE__) || defined(__MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <string>
#include <math.h>
#include <time.h>
#include <vector>

#define SCREEN_X 1024
#define SCREEN_Y 768
#define FPS_UPDATE 500
#define TITLE "Coucou"

int scene = 0;

glm::vec3* fixedPointSpringScene = new glm::vec3(0.0f, 0.5f, -10.0f);
GxSphere* fixedPointSpringSceneGx = NULL;
std::vector<Quantum::Halfspace*> cubeHalfspaces;
GxHalfspaceCube* gxHalfspaceCube = NULL;
glm::vec3 halfspaceCubeRotation = glm::vec3(0);

using namespace Quantum;

int nbFrame = 0;
int timebase = 0;
int lastTime = 0;
float dt = 0.0f;
bool useSameRand = true;

World* world;
std::vector<GxObject*> gxObjects;
glm::vec3 fountainPos = glm::vec3(0);
float fountainSpawnRate = 0.05f;
float lastFountainSpawn = 0.0f;

glm::vec3 velocityJ = glm::vec3(0);
glm::vec3 posJ = glm::vec3(0, 0, 0);
glm::vec2 rightClicPos = glm::vec2(0);
glm::vec2 leftClicPos = glm::vec2(0);
glm::vec3 rotationJ = glm::vec3(0);
float velocityVal = 5.0f;
bool rightClicing = false;
bool leftClicing = false;

void clear()
{
	world->clearBodies();

	for (int i = 0; i < gxObjects.size(); i++)
	{
		delete gxObjects[i];
	}
	gxObjects.clear();

	fixedPointSpringSceneGx = NULL;

	cubeHalfspaces.clear();
	gxHalfspaceCube = NULL;
}

void addParticle()
{
	if (scene == 0)
	{
		Particle* p = new Particle();
		glm::vec3 v = glm::vec3(0);
		p->setPosition(fountainPos);
		p->setAcceleration(v);
		v.x = ((float)(rand() % 1000)) / 333.33f - 1.5f;
		v.y = 8.0f + ((float)(rand() % 1000) / 500.0f - 1.0f);
		v.z = ((float)(rand() % 1000)) / 333.33f - 1.5f;
		p->setVelocity(v);
		p->setRadius(0.1f);

		world->addBody(p);
		GxObject* gxObject = new GxSphere(0.1f);
		gxObjects.push_back(gxObject);
		p->setGxUpdater(new MyGxUpdater(gxObject));

		std::cout << "Nombre de spheres : " << gxObjects.size() << std::endl;
	}
	else if (scene == 1)
	{
		Particle* p = new Particle();
		glm::vec3 v = glm::vec3(0);
		p->setPosition(fountainPos);
		p->setAcceleration(v);
		v.x = ((float)(rand() % 1000)) / 333.33f - 1.5f;
		v.y = 8.0f + ((float)(rand() % 1000) / 500.0f - 1.0f);
		v.z = ((float)(rand() % 1000)) / 333.33f - 1.5f;
		p->setVelocity(v);
		p->setRadius(0.1f);

		world->addBody(p);
		GxObject* gxObject = new GxSphere(0.1f);
		gxObjects.push_back(gxObject);
		p->setGxUpdater(new MyGxUpdater(gxObject));

		DragForce* dragForce = new DragForce(((float)(rand() % 10)) / 10.0f + 0.3f, ((float)(rand() % 10)) / 10.0f + 0.3f);
		world->addForceRegistry(new ForceRegistry(p, dragForce));

		std::cout << "Nombre de spheres : " << gxObjects.size() << std::endl;
	}
	else if (scene == 2) // spring
	{

	}
	else if (scene == 3) // magnetism
	{

	}
	else if (scene == 4)
	{
		glm::vec3 pos;
		pos.x = ((float)((rand() % 10001) - 5000)) / 1000.0f;
		pos.y = ((float)((rand() % 10001) - 5000)) / 1000.0f;
		pos.z = -((float)((rand() % 10001) - 5000)) / 1000.0f;
		Particle* particle = new Particle(pos, 1.0f, glm::vec3(0), glm::vec3(0), 0.99f, (rand() % 2 == 0) ? 5.0f : -5.0f, 0.4f);

		world->addBody(particle);

		GxObject* gxObject = new GxSphere(0.4f);
		gxObjects.push_back(gxObject);
		particle->setGxUpdater(new MyGxUpdater(gxObject));
	}
}

void tryFountain()
{
	lastFountainSpawn += dt;
	while (lastFountainSpawn > fountainSpawnRate)
	{
		addParticle();

		lastFountainSpawn -= fountainSpawnRate;
	}
}

void tryFountainDrag()
{
	lastFountainSpawn += dt;
	while (lastFountainSpawn > fountainSpawnRate)
	{
		addParticle();

		lastFountainSpawn -= fountainSpawnRate;
	}
}

void spawnSpringScene()
{
	std::vector<Particle*> ps;

	//PARTICLES

	ps.push_back(new Particle(glm::vec3(-.25f, 0.12f, -10.0f), 5.0f, glm::vec3(0), glm::vec3(0), 0.99f, 1.0f, 0.1f));
	ps.push_back(new Particle(glm::vec3(.25f, 0.12f, -9.80f), 5.0f, glm::vec3(0), glm::vec3(0), 0.99f, 1.0f, 0.13f));
	ps.push_back(new Particle(glm::vec3(.25f, 0.12f, -10.24f), 5.0f, glm::vec3(0), glm::vec3(0), 0.99f, 1.0f, 0.17f));
	ps.push_back(new Particle(glm::vec3(0.03f, -0.20f, -9.93f), 5.0f, glm::vec3(0), glm::vec3(0), 0.99f, 1.0f, 0.07f));

	// PARTICLES TO WORLD

	world->addBody(ps[0]);
	world->addBody(ps[1]);
	world->addBody(ps[2]);
	world->addBody(ps[3]);

	// GXOBJECTS

	fixedPointSpringSceneGx = new GxSphere(0.02f, glm::vec3(0.0f, 0.0f, 0.0f));
	fixedPointSpringSceneGx->setPosition(*fixedPointSpringScene);
	gxObjects.push_back(fixedPointSpringSceneGx);

	GxObject* gxObject1 = new GxSphere(0.1f);
	gxObjects.push_back(gxObject1);
	ps[0]->setGxUpdater(new MyGxUpdater(gxObject1));

	GxObject* gxObject2 = new GxSphere(0.13f);
	gxObjects.push_back(gxObject2);
	ps[1]->setGxUpdater(new MyGxUpdater(gxObject2));

	GxObject* gxObject3 = new GxSphere(0.17f);
	gxObjects.push_back(gxObject3);
	ps[2]->setGxUpdater(new MyGxUpdater(gxObject3));

	GxObject* gxObject4 = new GxSphere(0.07f);
	gxObjects.push_back(gxObject4);
	ps[3]->setGxUpdater(new MyGxUpdater(gxObject4));

	// ForceRegistries

	float K = 1000.0f;
	
	ForceGenerator* fg = new ParticleFixedPointSpringForce(fixedPointSpringScene, glm::distance(ps[0]->getPosition(), *fixedPointSpringScene), K);
	world->addForceRegistry(new ForceRegistry(ps[0], fg));
	fg = new ParticleFixedPointSpringForce(fixedPointSpringScene, glm::distance(ps[1]->getPosition(), *fixedPointSpringScene), K);
	world->addForceRegistry(new ForceRegistry(ps[1], fg));
	fg = new ParticleFixedPointSpringForce(fixedPointSpringScene, glm::distance(ps[2]->getPosition(), *fixedPointSpringScene), K);
	world->addForceRegistry(new ForceRegistry(ps[2], fg));

	fg = new ParticleParticleSpringForce(ps[1], glm::distance(ps[0]->getPosition(), ps[1]->getPosition()), K);
	world->addForceRegistry(new ForceRegistry(ps[0], fg));
	fg = new ParticleParticleSpringForce(ps[0], glm::distance(ps[1]->getPosition(), ps[0]->getPosition()), K);
	world->addForceRegistry(new ForceRegistry(ps[1], fg));

	fg = new ParticleParticleSpringForce(ps[1], glm::distance(ps[2]->getPosition(), ps[1]->getPosition()), K);
	world->addForceRegistry(new ForceRegistry(ps[2], fg));
	fg = new ParticleParticleSpringForce(ps[2], glm::distance(ps[1]->getPosition(), ps[2]->getPosition()), K);
	world->addForceRegistry(new ForceRegistry(ps[1], fg));

	fg = new ParticleParticleSpringForce(ps[2], glm::distance(ps[0]->getPosition(), ps[2]->getPosition()), K);
	world->addForceRegistry(new ForceRegistry(ps[0], fg));
	fg = new ParticleParticleSpringForce(ps[0], glm::distance(ps[2]->getPosition(), ps[0]->getPosition()), K);
	world->addForceRegistry(new ForceRegistry(ps[2], fg));

	fg = new ParticleParticleSpringForce(ps[0], glm::distance(ps[3]->getPosition(), ps[0]->getPosition()), K);
	world->addForceRegistry(new ForceRegistry(ps[3], fg));
	fg = new ParticleParticleSpringForce(ps[3], glm::distance(ps[0]->getPosition(), ps[3]->getPosition()), K);
	world->addForceRegistry(new ForceRegistry(ps[0], fg));
	fg = new ParticleParticleSpringForce(ps[1], glm::distance(ps[3]->getPosition(), ps[1]->getPosition()), K);
	world->addForceRegistry(new ForceRegistry(ps[3], fg));
	fg = new ParticleParticleSpringForce(ps[3], glm::distance(ps[1]->getPosition(), ps[3]->getPosition()), K);
	world->addForceRegistry(new ForceRegistry(ps[1], fg));
	fg = new ParticleParticleSpringForce(ps[2], glm::distance(ps[3]->getPosition(), ps[2]->getPosition()), K);
	world->addForceRegistry(new ForceRegistry(ps[3], fg));
	fg = new ParticleParticleSpringForce(ps[3], glm::distance(ps[2]->getPosition(), ps[3]->getPosition()), K);
	world->addForceRegistry(new ForceRegistry(ps[2], fg));

	float radius = 0.036f;
	gxObjects.push_back(new GxParticleParticleSpring(ps[0], ps[1], radius));
	gxObjects.push_back(new GxParticleParticleSpring(ps[0], ps[2], radius));
	gxObjects.push_back(new GxParticleParticleSpring(ps[0], ps[3], radius));
	gxObjects.push_back(new GxParticleParticleSpring(ps[1], ps[2], radius));
	gxObjects.push_back(new GxParticleParticleSpring(ps[1], ps[3], radius));
	gxObjects.push_back(new GxParticleParticleSpring(ps[2], ps[3], radius));

	gxObjects.push_back(new GxParticleFixedPointSpring(fixedPointSpringScene, ps[0], radius));
	gxObjects.push_back(new GxParticleFixedPointSpring(fixedPointSpringScene, ps[1], radius));
	gxObjects.push_back(new GxParticleFixedPointSpring(fixedPointSpringScene, ps[2], radius));
}

void spawnMagnetismScene()
{
	std::vector<Particle*> ps;
	int nbParticles = 36;
	int i, j;

	//PARTICLES

	for (i = 0; i < nbParticles; i++)
	{
		glm::vec3 pos;
		pos.x = ((float)((rand() % 10001) - 5000)) / 1000.0f;
		pos.y = ((float)((rand() % 10001) - 5000)) / 1000.0f;
		pos.z = -((float)((rand() % 10001) + 15000)) / 1000.0f;
		ps.push_back(new Particle(pos, 0.4f, glm::vec3(0), glm::vec3(0), 0.9f, (rand() % 2 == 0) ? 5.0f : -5.0f, 0.3f));
	}

	// PARTICLES TO WORLD

	for (i = 0; i < nbParticles; i++)
	{
		world->addBody(ps[i]);
	}

	// GXOBJECTS
	// positif : rouge
	GxObject* gxObject = NULL;
	glm::vec3 positiv = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 negativ = glm::vec3(0.0f, 0.0f, 1.0f);
	for (i = 0; i < nbParticles; i++)
	{
		gxObject = new GxSphere(0.3f, (ps[i]->getCharge() < 0.0f) ? negativ : positiv);
		gxObjects.push_back(gxObject);
		ps[i]->setGxUpdater(new MyGxUpdater(gxObject));
	}

	// ForceRegistries
	
	ForceGenerator* fg = NULL;
	float K = 0.3f;

	for (i = 0; i < nbParticles; i++)
	{
		for (j = 0; j < nbParticles; j++)
		{
			if (i != j)
			{
				fg = new MagnetismForce(ps[i], K);
				world->addForceRegistry(new ForceRegistry(ps[j], fg));
			}
		}
	}
}

void spawnCubeScene()
{
	std::vector<Particle*> ps;
	int nbParticles = 100;
	int i, j;

	// PARTICLES

	for (i = 0; i < nbParticles; i++)
	{
		glm::vec3 pos;
		pos.x = ((float)((rand() % 10001) - 5000)) / 1000.0f;
		pos.y = ((float)((rand() % 10001) - 5000)) / 1000.0f;
		pos.z = -((float)((rand() % 10001) - 5000)) / 1000.0f;
		ps.push_back(new Particle(pos, 1.0f, glm::vec3(0), glm::vec3(0), 0.99f, (rand() % 2 == 0) ? 5.0f : -5.0f, 0.4f));
	}

	// PARTICLES TO WORLD

	for (i = 0; i < nbParticles; i++)
	{
		world->addBody(ps[i]);
	}

	// CUBE

	cubeHalfspaces.push_back(new Halfspace(glm::vec3(0, 1, 0), -6.0f));
	cubeHalfspaces.push_back(new Halfspace(glm::vec3(0, -1, 0), -6.0f));
	cubeHalfspaces.push_back(new Halfspace(glm::vec3(1, 0, 0), -6.0f));
	cubeHalfspaces.push_back(new Halfspace(glm::vec3(-1, 0, 0), -6.0f));
	cubeHalfspaces.push_back(new Halfspace(glm::vec3(0, 0, 1), -6.0f));
	cubeHalfspaces.push_back(new Halfspace(glm::vec3(0, 0, -1), -6.0f));
	// CUBE TO WORLD

	for (int i = 0; i < cubeHalfspaces.size(); i++)
	{
		world->addBody(cubeHalfspaces[i]);
	}
	gxHalfspaceCube = new GxHalfspaceCube(6.0f, glm::vec3(0.0f, 0.0f, 0.0f), halfspaceCubeRotation);
	gxObjects.push_back(gxHalfspaceCube);

	// GXOBJECTS

	GxObject* gxObject = NULL;
	for (i = 0; i < nbParticles; i++)
	{
		gxObject = new GxSphere(0.4f);
		gxObjects.push_back(gxObject);
		ps[i]->setGxUpdater(new MyGxUpdater(gxObject));
	}
}

void render()
{
	if (scene == 0)
	{
		tryFountain();
	}
	else if (scene == 1)
	{
		tryFountainDrag();
	}

	world->integrate(dt);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float cosb = cos(rotationJ.y * PI / 180.0);
	float sinb = sin(rotationJ.y * PI / 180.0);

	posJ.x += (cosb * velocityJ.x - sinb * velocityJ.z) * dt;
	posJ.y += velocityJ.y * dt;
	posJ.z += (sinb * velocityJ.x + cosb * velocityJ.z) * dt;

	//glTranslatef(-posJ.x, -posJ.y, -posJ.z);
	glRotatef(rotationJ.z, 0, 0, 1);
	glRotatef(rotationJ.x, 1, 0, 0);
	glRotatef(rotationJ.y, 0, 1, 0);

	for (int i = 0; i < gxObjects.size(); i++)
	{
		gxObjects[i]->draw(posJ);
	}

	glutSwapBuffers();
}

void initGL(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_X, SCREEN_Y);
	glutCreateWindow(TITLE);
	glewInit();

	glClearColor(0.72, 0.72, 0.72, 1.0);

	float aspect = (float)SCREEN_X / (float)SCREEN_Y;
	glViewport(0, 0, SCREEN_X, SCREEN_Y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, aspect, 0.1, 100.0);

	glEnable(GL_DEPTH_TEST);
}

void idlefunc()
{
	nbFrame++;
	int time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		int fps = nbFrame * (1000.0f / (float)(time - timebase));
		
		timebase = time;
		nbFrame = 0;

		std::string s = TITLE;
		s += " - ";
		s += std::to_string(fps);
		s += " fps";

		const char *c = s.data();

		glutSetWindowTitle(c);


	}
	dt = (float)(time - lastTime) / 1000.0f;
	lastTime = time;
	glutPostRedisplay();
}

void toggleScene(int n)
{
	clear();
	rotationJ = glm::vec3(0);
	posJ = glm::vec3(0);
	scene = n;

	if (useSameRand)
	{
		srand(363636);
	}

	if (n == 0)
	{
		world->useGravity(true);
		world->useCollision(false);
	}
	else if (n == 1)
	{
		world->useGravity(true);
		world->useCollision(false);
	}
	else if (n == 2)
	{
		delete fixedPointSpringScene;
		fixedPointSpringScene = new glm::vec3(0.0f, 0.5f, -10.0f);
		world->useGravity(true);
		world->useCollision(true);
		spawnSpringScene();
	}
	else if (scene == 3)
	{
		world->useGravity(false);
		world->useCollision(true);
		spawnMagnetismScene();
	}
	else if (scene == 4)
	{
		posJ = glm::vec3(0, -1.0f, 25.0f);
		halfspaceCubeRotation = glm::vec3(0);
		world->useGravity(true);
		world->useCollision(true);
		spawnCubeScene();
	}
}

void keyfunc(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(EXIT_SUCCESS);
			break;
		case 'z':
			velocityJ.z = -velocityVal;
			break;
		case 's':
			velocityJ.z = velocityVal;
			break;
		case 'q':
			velocityJ.x = -velocityVal;
			break;
		case 'd':
			velocityJ.x = velocityVal;
			break;
		case 'a':
			velocityJ.y = velocityVal;
			break;
		case 'e':
			velocityJ.y = -velocityVal;
			break;
		case 'g':
			world->useGravity(!world->isUsingGravity());
			break;
		case 'c' :
			world->useCollision(!world->isUsingCollision());
			break;
		case 'v' :
			world->setDeterministe(!world->isDeterministe());
			//toggleScene(scene);
			break;
		case 'r' :
			useSameRand = !useSameRand;
			break;
		case '0' :
			toggleScene(0);
			break;
		case '1':
			toggleScene(1);
			break;
		case '2':
			toggleScene(2);
			break;
		case '3':
			toggleScene(3);
			break;
		case '4':
			toggleScene(4);
			break;
		case '+':
			addParticle();
			break;
	}
}

void keyupfunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 'z':
		velocityJ.z = 0.0f;
		break;
	case 's':
		velocityJ.z = 0.0f;
		break;
	case 'q':
		velocityJ.x = 0.0f;
		break;
	case 'd':
		velocityJ.x = 0.0f;
		break;
	case 'a':
		velocityJ.y = 0.0f;
		break;
	case 'e':
		velocityJ.y = 0.0f;
		break;
	}
}

void mousefunc(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		leftClicPos.x = x;
		leftClicPos.y = y;
		leftClicing = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		leftClicing = false;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		rightClicPos.x = x;
		rightClicPos.y = y;
		rightClicing = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		rightClicing = false;
	}

	/*if (button == 3) //WHEEL UP
	{
	zoomz += 0.1;
	if (zoomz > 0.0)
	zoomz = 0.0;
	}

	if (button == 4) //WHEEL DOWN
	{
	zoomz -= 0.1;
	if (zoomz < -10.0)
	zoomz = -10.0;
	}*/

	//glutPostRedisplay();
}

glm::vec3 applyRotationZXY(glm::vec3 vector, float angleZ, float angleX, float angleY)
{
	glm::vec3 res = vector;
	float theta = angleZ * PI / 180.0f;
	//rot Z
	res.x = vector.x * cos(theta) - vector.y * sin(theta);
	res.y = vector.x * sin(theta) + vector.y * cos(theta);

	glm::vec3 ress = res;
	theta = angleX * PI / 180.0f;
	//rot X
	ress.y = res.y * cos(theta) - res.z * sin(theta);
	ress.z = res.y * sin(theta) + res.z * cos(theta);

	glm::vec3 resss = ress;
	theta = angleY * PI / 180.0f;
	//rot Y
	resss.x = ress.x * cos(theta) + ress.z * sin(theta);
	resss.z = -ress.x * sin(theta) + ress.z * cos(theta);

	return resss;
}

void motionfunc(int x, int y)
{
	if (leftClicing && (x != leftClicPos.x || y != leftClicPos.y))
	{
		if (scene == 2)
		{
			float velocityX = (float)(x - leftClicPos.x) / 120.5f;
			float velocityY = -(float)(y - leftClicPos.y) / 120.5f;

			float cosb = cos(rotationJ.y * PI / 180.0);
			float sinb = sin(rotationJ.y * PI / 180.0);

			fixedPointSpringScene->x += (cosb * velocityX);
			fixedPointSpringScene->y += velocityY;
			fixedPointSpringScene->z += (sinb * velocityX);

			fixedPointSpringSceneGx->setPosition(*fixedPointSpringScene);
		}
		else if (scene == 4)
		{
			float velocityY = (float)(x - leftClicPos.x) / 12.5f;
			float velocityX = (float)(y - leftClicPos.y) / 12.5f;

			float cosb = cos(rotationJ.y * PI / 180.0);
			float sinb = sin(rotationJ.y * PI / 180.0);

			float velocityZ = (sinb * velocityX);
			velocityX = (cosb * velocityX);

			gxHalfspaceCube->setRotation(halfspaceCubeRotation);
			gxHalfspaceCube->rotateZXY(velocityZ, velocityX, velocityY);

			for (int i = 0; i < 6; i++)
				cubeHalfspaces[i]->m_normal = applyRotationZXY(cubeHalfspaces[i]->m_normal, velocityZ, velocityX, velocityY);
		}

		leftClicPos.x = x;
		leftClicPos.y = y;
	}

	if (rightClicing && (x != rightClicPos.x || y != rightClicPos.y))
	{
		rotationJ.y += (float)(x - rightClicPos.x) / 12.5f;
		rotationJ.x += (float)(y - rightClicPos.y) / 12.5f;

		rightClicPos.x = x;
		rightClicPos.y = y;
	}

	//glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	initGL(argc, argv);
	glutDisplayFunc(render);
	glutIdleFunc(idlefunc);
	glutKeyboardFunc(keyfunc);
	glutKeyboardUpFunc(keyupfunc);
	glutMouseFunc(mousefunc);
	glutMotionFunc(motionfunc);

	world = new World();

	fountainPos.z = -10.0f;
	fountainPos.y = -2.0f;

	toggleScene(scene);

	GLint GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK) {
		printf("ERROR: %s\n", glewGetErrorString(GlewInitResult));
	}

	// enter GLUT event processing cycle
	lastTime = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();

	delete world;

	return 0;
}

