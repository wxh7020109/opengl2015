#include <GL/glut.h>
#include<windows.h>
#include <SDL.h>
#include "stdafx.h"
#include <iostream>
#include <gl/GL.h>
#include <gl/GLU.h>


static GLfloat sunRevolute   = 0.0f;	//太阳自传天数
static GLfloat earthRevolute = 0.0f;	//地球自传天数
static GLfloat earthRotate   = 200.0f;	//地球公转天数
static GLfloat moonRevolute  = 0.0f;	//月球自传天数
static GLfloat moonRotate    = 10.0f;	//月球公转天数


static int day = 0; // day 的变化：从 0 到 359

GLUquadricObj *sunQuadObj; //创建二次方程对象
SDL_Surface *sunSurface = NULL;
GLuint sunTexture;

GLUquadricObj *earthQuadObj;
SDL_Surface *earthSurface;
GLuint earthTexture;

GLUquadricObj *moonQuadObj;
SDL_Surface *moonSurface;
GLuint moonTexture




void ShutdownRC()
{
	glDeleteTextures(1, &sunTexture);
	glDeleteTextures(1, &earthTexture);
	glDeleteTextures(1, &moonTexture);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
}

void myDisplay(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75,1,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,20,-25,0,0,0,0,-1,0);

	// 定义太阳光源
	{
	GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	}

	// 定义太阳的材质并绘制太阳
	{
	GLfloat sun_mat_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_diffuse[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_shininess = 10.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);
	glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glutWireSphere(7, 200, 200);
	}

	// 定义地球的材质并绘制地球
	{
	GLfloat earth_mat_ambient[] = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat earth_mat_diffuse[] = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat earth_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat earth_mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
	glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(12.0f, 0.0f, 0.0f);
	glutWireSphere(2, 200, 200);
	}

	//定义月亮的材质并绘制月亮
	{
	GLfloat moon_mat_ambient[] = {1.0f, 1.0f, 0.0f, 1.0f};
	GLfloat moon_mat_diffuse[] = {1.0f, 1.0f, 0.0f, 1.0f};
	GLfloat moon_mat_specular[] = {1.0f, 1.0f, 0.0f, 1.0f};
	GLfloat moon_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat moon_mat_shininess = 50.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, moon_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, moon_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, moon_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, moon_mat_shininess);
	glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(5.0f, 0.0f, 0.0f);
	glutWireSphere(1, 100, 100);
	}
	glFlush();
	glutSwapBuffers();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
		2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
		2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void rotateObj(GLfloat *rot, GLfloat angle)
{
	*rot+=0.01f;
	if (*rot>=angle)
	{
		*rot -= angle;
	}
}

void renderScene(void)
{
	rotateObj(&sunRevolute, 30.0f);
	rotateObj(&earthRevolute, 1.0f);
	rotateObj(&earthRotate, 360.0f);
	rotateObj(&moonRevolute, 27.0f);
	rotateObj(&moonRotate, 27.0f);
	myDisplay();
}

void myIdle(void)
{

++day;
if( day >= 360 )
	day = 0;
Sleep(100);
myDisplay();
}

void init()
{
	sunQuadObj = gluNewQuadric();
	gluQuadricNormals(sunQuadObj, GLU_SMOOTH);
	gluQuadricTexture(sunQuadObj, GL_TRUE);

	moonQuadObj = gluNewQuadric();
	gluQuadricNormals(moonQuadObj, GLU_SMOOTH);
	gluQuadricTexture(moonQuadObj, GLU_TRUE);

	earthQuadObj = gluNewQuadric();
	gluQuadricNormals(earthQuadObj, GLU_SMOOTH);
	gluQuadricTexture(earthQuadObj, GLU_TRUE);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	sunSurface = SDL_LoadBMP("Sun.bmp");
	glGenTextures(1,&sunTexture);
	glBindTexture(GL_TEXTURE_2D, sunTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, sunSurface->w, sunSurface->h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, sunSurface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	earthSurface = SDL_LoadBMP("Earth.bmp");
	printf("------------%p\n",earthSurface);
	glGenTextures(1,&earthTexture);
	glBindTexture(GL_TEXTURE_2D, earthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, earthSurface->w, earthSurface->h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, earthSurface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	moonSurface = SDL_LoadBMP("Moon.bmp");
	glGenTextures(1,&moonTexture);
	glBindTexture(GL_TEXTURE_2D, moonTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, moonSurface->w, moonSurface->h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, moonSurface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_2D);
}

int main(int argc, char *argv[])
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
glutInitWindowPosition(100, 100);
glutInitWindowSize(500, 500);
glutCreateWindow("太阳、地球、月亮");
init();
glutReshapeFunc(myReshape);
glutDisplayFunc(&myDisplay);
glutIdleFunc(&myIdle); 
glutMainLoop();
ShutdownRC();
return 0;
}
