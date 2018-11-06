#include <windows.h>
#include <iostream>
#include <stdlib.h> //Needed for "exit" function

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"

using namespace std;

int flag = 0;
double angle = 0.0;
bool check = true;
float i,j;

void rotateFunction(int num)
{
    glutPostRedisplay();
    glutTimerFunc(10, rotateFunction, 0.0);
    angle = angle+0.5;
}

//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
					int x, int y) {    //The current mouse coordinates
	switch (key) {
        case 'x':
            flag = 1;
            check = true;
            glutTimerFunc(10, rotateFunction, 0.0);
            break;
        case 'y':
            flag = 2;
            check = true;
            glutTimerFunc(10, rotateFunction, 0.0);
            break;
        case 'z':
            flag = 3;
            check = true;
            glutTimerFunc(10, rotateFunction, 0.0);
            break;
        case 'i':
            check = false;
        default:
            break;
	}
}

GLuint loadTexture(Image* image) {
	GLuint textureId;

	//The first argument is the number of textures we need, and the second is an array where OpenGL will store the id's of the textures.
	glGenTextures(1, &textureId); //Make room for our texture
	// to assign the texture id to our image data.
//	We call glBindTexture(GL_TEXTURE_2D, textureId) to let OpenGL know
// that we want to work with the texture we just created. Then, we call glTexImage2D to load the image into OpenGL.
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId1; //The id of the texture
GLuint _textureId2;

//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.7,0.9,1.0,1.0);

	//Image* image = loadBMP("texture.bmp");
	Image* image1 = loadBMP("C:\\Users\\Shihab\\Documents\\GitHub\\FaisalMosqueDesign\\Images\\grass.bmp");
	Image* image2 = loadBMP("C:\\Users\\Shihab\\Documents\\GitHub\\FaisalMosqueDesign\\Images\\grass.bmp");
	_textureId1 = loadTexture(image1);
	delete image1;
	_textureId2 = loadTexture(image2);
	delete image2;
}

//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   1.0,                   //The near z clipping coordinate
				   200.0);                //The far z clipping coordinate
}

void triangle(float a,float b,float c,float d,float e,float f,float g,float h,float i)
{
    glBegin(GL_TRIANGLES);

    glTexCoord2f(2.0f, 2.0f);
	glVertex3f(a, b, c);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(d, e, f);
	glTexCoord2f(0.0f, 2.0f);
	glVertex3f(g, h, i);

	glEnd();
}

void poly(float a,float b,float c,float d,float e,float f,float g,float h,float i,float j,float k,float l,float m,float n,float o)
{
    glBegin(GL_POLYGON);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(a, b, c);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(d, e, f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(g, h, i);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(j, k, l);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(m, n, o);

    glEnd();
}

void left_poly(float a,float b,float c,float d,float e,float f,float g,float h,float i,float j,float k,float l,float m,float n,float o)
{
    glBegin(GL_POLYGON);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-a, b, c);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-d, e, f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-g, h, i);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-j, k, l);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-m, n, o);

    glEnd();
}

void quad(float a,float b,float c,float d,float e,float f,float g,float h,float i,float j,float k,float l)
{
    glBegin(GL_POLYGON);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(a, b, c);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(d, e, f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(g, h, i);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(j, k, l);

    glEnd();
}

void line(float a,float b,float c,float d,float e,float f)
{
    glBegin(GL_LINES);

    glVertex3f(a, b, c);
    glVertex3f(d, e, f);

    glEnd();
}

void left_line(float a,float b,float c,float d,float e,float f)
{
    glBegin(GL_LINES);

    glVertex3f(-a, b, c);
    glVertex3f(-d, e, f);

    glEnd();
}

void minar_triangle(float a,float b,float c,float d,float e,float f,float g,float h,float i)
{
    glBegin(GL_TRIANGLES);

    glTexCoord2f(1.0f, 1.0f);
	glVertex3f(a, b, c);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(d, e, f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(g, h, i);

	glEnd();
}

void minar_quad(float a,float b,float c,float d,float e,float f,float g,float h,float i,float j,float k,float l)
{
    glBegin(GL_POLYGON);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(a, b, c);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(d, e, f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(g, h, i);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(j, k, l);

    glEnd();
}

void minar()
{
    glColor3f(0.9,0.9,0.9);
    minar_quad(1.9,0.5,0.7,2.0,0.5,0.7,2.0,2.5,0.7,1.9,2.5,0.7);
    minar_quad(2.1,0.5,0.7,2.2,0.5,0.7,2.2,2.5,0.7,2.1,2.5,0.7);

    glColor3f(0.0,0.0,0.0);
    minar_quad(2.0,2.4,0.7,2.1,2.4,0.7,2.1,2.5,0.7,2.0,2.5,0.7);

    for(i=0,j=2.25;i<12;i++,j=j-0.15)
    {
        minar_quad(2.0,j,0.7,2.1,j,0.7,2.1,j+0.05,0.7,2.0,j+0.05,0.7);
    }

    glColor3f(1.0,1.0,1.0);
    minar_quad(2.033,0.5,0.6999,2.067,0.5,0.6999,2.067,2.5,0.6999,2.033,2.5,0.6999);
    minar_quad(1.9,0.0,0.8,2.2,0.0,0.8,2.1,0.5,0.7,2.0,0.5,0.7);

    glColor3f(0.9,0.9,0.9);
    minar_quad(1.8,0.0,0.8,1.9,0.0,0.8,2.0,0.5,0.7,1.9,0.5,0.7);
    minar_quad(2.2,0.0,0.8,2.3,0.0,0.8,2.2,0.5,0.7,2.1,0.5,0.7);


    glColor3f(0.9,0.9,0.9);
    minar_triangle(1.9,2.5,0.7,2.0,2.5,0.7,2.05,3.25,0.55);
    minar_triangle(2.1,2.5,0.7,2.2,2.5,0.7,2.05,3.25,0.55);

    glColor3f(0.0,0.0,0.0);
    minar_triangle(2.025,2.8,0.65,2.075,2.8,0.65,2.05,3.25,0.55);
}

void back_minar()
{
    glColor3f(0.9,0.9,0.9);
    minar_quad(1.9,0.5,0.4,2.0,0.5,0.4,2.0,2.5,0.4,1.9,2.5,0.4);
    minar_quad(2.1,0.5,0.4,2.2,0.5,0.4,2.2,2.5,0.4,2.1,2.5,0.4);

    glColor3f(0.0,0.0,0.0);
    minar_quad(2.0,2.4,0.4,2.1,2.4,0.4,2.1,2.5,0.4,2.0,2.5,0.4);

    for(i=0,j=2.25;i<12;i++,j=j-0.15)
    {
        minar_quad(2.0,j,0.4,2.1,j,0.4,2.1,j+0.05,0.4,2.0,j+0.05,0.4);
    }

    glColor3f(1.0,1.0,1.0);
    minar_quad(2.033,0.5,0.4111,2.067,0.5,0.4111,2.067,2.5,0.4111,2.033,2.5,0.4111);
    minar_quad(1.9,0.0,0.3,2.2,0.0,0.3,2.1,0.5,0.4,2.0,0.5,0.4);

    glColor3f(0.9,0.9,0.9);
    minar_quad(1.8,0.0,0.3,1.9,0.0,0.3,2.0,0.5,0.4,1.9,0.5,0.4);
    minar_quad(2.2,0.0,0.3,2.3,0.0,0.3,2.2,0.5,0.4,2.1,0.5,0.4);

    glColor3f(0.9,0.9,0.9);
    minar_triangle(1.9,2.5,0.4,2.0,2.5,0.4,2.05,3.25,0.55);
    minar_triangle(2.1,2.5,0.4,2.2,2.5,0.4,2.05,3.25,0.55);

    glColor3f(0.0,0.0,0.0);
    minar_triangle(2.025,2.8,0.45,2.075,2.8,0.45,2.05,3.25,0.55);
}

void left_minar()
{
    glColor3f(0.9,0.9,0.9);
    minar_quad(1.9,0.5,0.7,1.9,0.5,0.6,1.9,2.5,0.6,1.9,2.5,0.7);
    minar_quad(1.9,0.5,0.5,1.9,0.5,0.4,1.9,2.5,0.4,1.9,2.5,0.5);

    glColor3f(0.0,0.0,0.0);
    minar_quad(1.9,2.4,0.6,1.9,2.4,0.5,1.9,2.5,0.5,1.9,2.5,0.6);

    for(i=0,j=2.25;i<12;i++,j=j-0.15)
    {
        minar_quad(1.9,j,0.6,1.9,j,0.5,1.9,j+0.05,0.5,1.9,j+0.05,0.6);
    }

    glColor3f(1.0,1.0,1.0);
    minar_quad(1.901,0.5,0.567,1.901,0.5,0.533,1.901,2.5,0.533,1.901,2.5,0.567);
    minar_quad(1.8,0.0,0.7,1.8,0.0,0.4,1.9,0.5,0.5,1.9,0.5,0.6);

    glColor3f(0.9,0.9,0.9);
    minar_quad(1.8,0.0,0.8,1.8,0.0,0.7,1.9,0.5,0.6,1.9,0.5,0.7);
    minar_quad(1.8,0.0,0.4,1.8,0.0,0.3,1.9,0.5,0.4,1.9,0.5,0.5);

    glColor3f(0.9,0.9,0.9);
    minar_triangle(1.9,2.5,0.7,1.9,2.5,0.6,2.05,3.25,0.55);
    minar_triangle(1.9,2.5,0.5,1.9,2.5,0.4,2.05,3.25,0.55);

    glColor3f(0.0,0.0,0.0);
    minar_triangle(1.95,2.8,0.575,1.95,2.8,0.525,2.05,3.25,0.55);
}

void right_minar()
{
    glColor3f(0.9,0.9,0.9);
    minar_quad(2.2,0.5,0.7,2.2,0.5,0.6,2.2,2.5,0.6,2.2,2.5,0.7);
    minar_quad(2.2,0.5,0.5,2.2,0.5,0.4,2.2,2.5,0.4,2.2,2.5,0.5);

    glColor3f(0.0,0.0,0.0);
    minar_quad(2.2,2.4,0.6,2.2,2.4,0.5,2.2,2.5,0.5,2.2,2.5,0.6);

    for(i=0,j=2.25;i<12;i++,j=j-0.15)
    {
        minar_quad(2.2,j,0.6,2.2,j,0.5,2.2,j+0.05,0.5,2.2,j+0.05,0.6);
    }

    glColor3f(1.0,1.0,1.0);
    minar_quad(2.199,0.5,0.567,2.199,0.5,0.533,2.199,2.5,0.533,2.199,2.5,0.567);
    minar_quad(2.3,0.0,0.7,2.3,0.0,0.4,2.2,0.5,0.5,2.2,0.5,0.6);

    glColor3f(0.9,0.9,0.9);
    minar_quad(2.3,0.0,0.8,2.3,0.0,0.7,2.2,0.5,0.6,2.2,0.5,0.7);
    minar_quad(2.3,0.0,0.4,2.3,0.0,0.3,2.2,0.5,0.4,2.2,0.5,0.5);

    glColor3f(0.9,0.9,0.9);
    minar_triangle(2.2,2.5,0.7,2.2,2.5,0.6,2.05,3.25,0.55);
    minar_triangle(2.2,2.5,0.5,2.2,2.5,0.4,2.05,3.25,0.55);

    glColor3f(0.0,0.0,0.0);
    minar_triangle(2.15,2.8,0.575,2.15,2.8,0.525,2.05,3.25,0.55);
}

void view()
{
    //-------------------Front View Right Side Start----------------------------

    glColor3f(1.0,1.0,1.0);
    poly(0.015,0.0,0.1,0.125,0.0,0.1,0.125,1.05,0.1,0.05,1.2,0.1,0.015,1.0,0.1);
    poly(0.145,0.0,0.1,0.27,0.0,0.1,0.27,0.95,0.1,0.195,1.1,0.1,0.145,0.9,0.1);
    poly(0.29,0.0,0.1,0.415,0.0,0.1,0.415,0.85,0.1,0.34,1.0,0.1,0.29,0.8,0.1);
    poly(0.435,0.0,0.1,0.56,0.0,0.1,0.56,0.75,0.1,0.485,0.9,0.1,0.435,0.7,0.1);
    poly(0.58,0.0,0.1,0.705,0.0,0.1,0.705,0.65,0.1,0.63,0.8,0.1,0.58,0.6,0.1);
    poly(0.725,0.0,0.1,0.85,0.0,0.1,0.85,0.55,0.1,0.775,0.7,0.1,0.725,0.5,0.1);
    poly(0.87,0.0,0.1,0.995,0.0,0.1,0.995,0.45,0.1,0.92,0.6,0.1,0.87,0.4,0.1);
    poly(1.015,0.0,0.1,1.14,0.0,0.1,1.14,0.35,0.1,1.065,0.5,0.1,1.015,0.3,0.1);
    poly(1.16,0.0,0.1,1.285,0.0,0.1,1.285,0.25,0.1,1.21,0.4,0.1,1.16,0.2,0.1);
    poly(1.305,0.0,0.1,1.43,0.0,0.1,1.43,0.15,0.1,1.355,0.3,0.1,1.305,0.1,0.1);

    glColor3f(0.f,0.0f,0.0f);
    triangle(0.0, 0.0, 0.0, 1.8, 0.0, 0.0, 0.0, 1.25, 0.0);

    glColor3f(1.0, 1.0, 1.0);

    for(i=19,j=0.09;i>0;i--,j=j+0.09)
    {
        if(i<=4)
            line(0.0,i*0.05,0.05,1.4,i*0.05,0.05);
        else
            line(0.0,i*0.05,0.05,j,i*0.05,0.05);
    }

    //-----------------Gray Color Er Small Triangle -----------------
    glColor3f(0.9,0.9,0.9);
    triangle(0.0,1.25,0.0,1.8,0.0,0.0,0.0,1.35,0.0);

    //-----------------White Roof---------------
    glColor3f(1.0,1.0,1.0);
    triangle(0.0,1.35,0.2,1.8,0.0,0.2,0.0,2.0,-1.8);

    //-----------------Join of Two Roof (Right)---------------
    glColor3f(0.0,1.0,0.9);
    triangle(1.8,0.0,0.0,1.8,0.0,0.2,0.0,2.0,-1.8);

    //------------- Line from Roof Center to Front (Right)-----------
    glColor3f(0.9,0.9,0.9);
    quad(0.0,1.35,0.2,0.03,1.35,0.2,0.03,2.0,-1.8,0.0,2.0,-1.8);

    //--------------- Roof 4 quad----------------------
    glColor3f(0.9,1.0,0.9);
    quad(0.0,2.0,-1.8,0.0,2.1,-1.8,0.2,2.3,-1.6,0.2,1.8,-1.6);

    //Minar Front Side
    minar();
    //End of Minar Front Side

    //Minar Back Side
    back_minar();
    //End of Minar Back Side

    //Minar Left Side
    left_minar();
    //End of Minal Left Side

    //Minar Right Side
    right_minar();
    //End of Minar Right Side

    //--------------------End of Front View Right Side--------------------------------------


    //---------------------Front View Left Side Start---------------------------------------

    glColor3f(0.f,0.0f,0.0f);
    triangle(0.015, 0.0, -0.0, -1.8, 0.0, -0.0, 0.015, 1.25, -0.0);

    glColor3f(1.0,1.0,1.0);
    left_poly(0.0,0.0,0.1,0.125,0.0,0.1,0.125,1.05,0.1,0.05,1.2,0.1,0.0,1.0,0.1);
    left_poly(0.145,0.0,0.1,0.27,0.0,0.1,0.27,0.95,0.1,0.195,1.1,0.1,0.145,0.9,0.1);
    left_poly(0.29,0.0,0.1,0.415,0.0,0.1,0.415,0.85,0.1,0.34,1.0,0.1,0.29,0.8,0.1);
    left_poly(0.435,0.0,0.1,0.56,0.0,0.1,0.56,0.75,0.1,0.485,0.9,0.1,0.435,0.7,0.1);
    left_poly(0.58,0.0,0.1,0.705,0.0,0.1,0.705,0.65,0.1,0.63,0.8,0.1,0.58,0.6,0.1);
    left_poly(0.725,0.0,0.1,0.85,0.0,0.1,0.85,0.55,0.1,0.775,0.7,0.1,0.725,0.5,0.1);
    left_poly(0.87,0.0,0.1,0.995,0.0,0.1,0.995,0.45,0.1,0.92,0.6,0.1,0.87,0.4,0.1);
    left_poly(1.015,0.0,0.1,1.14,0.0,0.1,1.14,0.35,0.1,1.065,0.5,0.1,1.015,0.3,0.1);
    left_poly(1.16,0.0,0.1,1.285,0.0,0.1,1.285,0.25,0.1,1.21,0.4,0.1,1.16,0.2,0.1);
    left_poly(1.305,0.0,0.1,1.43,0.0,0.1,1.43,0.15,0.1,1.355,0.3,0.1,1.305,0.1,0.1);

    for(i=19,j=0.09;i>0;i--,j=j+0.09)
    {
        if(i<=4)
            left_line(0.0,i*0.05,0.05,1.4,i*0.05,0.05);
        else
            left_line(0.0,i*0.05,0.05,j,i*0.05,0.05);
    }

    glColor3f(0.9,0.9,0.9);
    triangle(0.0,1.25,0.0,-1.8,0.0,0.0,0.0,1.35,0.0);

    glColor3f(1.0,1.0,1.0);
    triangle(0.0,1.35,0.2,-1.8,0.0,0.2,0.0,2.0,-1.8);

    //------------------Join of Two Roof (Left)---------------
    glColor3f(0.0,1.0,0.9);
    triangle(-1.8,0.0,0.0,-1.8,0.0,0.2,0.0,2.0,-1.8);


    //---------Line from Roof Center to Front (Left)-------------
    glColor3f(0.9,0.9,0.9);
    quad(0.0,1.35,0.2,-0.03,1.35,0.2,-0.03,2.0,-1.8,0.0,2.0,-1.8);

    //--------------------End of Front View Left Side--------------------------------------

}

//Draws the 3D scene
void drawScene() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	//On to drawScene. We start by calling glEnable(GL_TEXTURE_2D) to enable applying textures
    //and glBindTexture(GL_TEXTURE_2D, _textureId) to tell OpenGL that we want to use the texture with id _textureId.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId1);

	//The first call tells OpenGL to use the blocky mapping (GL_NEAREST)
    //when the texture is far away from us, and the second call tells it to use blocky mapping when the texture is close.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTranslatef(0.0, -1.5, -6.0); //Translation
    //glRotatef(45.0,0.0,0.0,-5.0); //Rotation

    if(flag == 1 && check)
        glRotatef(angle, 1.0, 0.0, 0.0);
    if(flag == 2 && check)
        glRotatef(angle, 0.0, 1.0, 0.0);
    if(flag == 3 && check)
        glRotatef(angle,0.0, 0.0, 1.0);

    //-------------------Front View Draw Start---------------------
    view();
    //---------------------End of Front View-------------------------

    //---------------------Right View Draw Start-------------------------
    glRotatef(90,0.0,1.0,0.0);
    glTranslatef(1.8,0.0,0.0);
    glTranslatef(0.0,0.0,1.8);
    view();
    //----------------------End of Right View--------------------------

    //----------------------Back View Draw Start-------------------------
    glRotatef(90,0.0,1.0,0.0);
    glTranslatef(1.8,0.0,0.0);
    glTranslatef(0.0,0.0,1.8);
    view();
    //---------------------End of Back View--------------------------

    //---------------------Left View Draw Start------------------------
    glRotatef(90,0.0,1.0,0.0);
    glTranslatef(1.8,0.0,0.0);
    glTranslatef(0.0,0.0,1.8);
    view();
    //---------------------End of Left View--------------------------

    //----------Center Moon Draw-------------
    glColor3f(0.1,0.1,0.1);
    glTranslatef(0.0,2.3,-1.8);
    glScaled(.1,.6,.1);
    glutSolidSphere(0.5,20,20);
    //----------End of Center Moon Draw-------------

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId2);

	//The first call tells OpenGL to use the blocky mapping (GL_NEAREST)
    //when the texture is far away from us, and the second call tells it to use blocky mapping when the texture is close.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
	glColor3f(1.f,1.0f,1.0f);

	glTexCoord2f(0.0f, 10.0f);
	glVertex3f(-40.0f, -3.9f, 40.0f);
	glTexCoord2f(10.0f, 10.0f);
	glVertex3f(-40.0f, -3.9f, -40.0f);
	glTexCoord2f(10.0f, 0.0f);
	glVertex3f(40.0f, -3.9f, -40.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(40.0f, -3.9f, 40.0f);
	glEnd();

	glutSwapBuffers(); //Send the 3D scene to the screen
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 650); //Set the window size

	//Create the window
	glutCreateWindow("Basic Shapes");
	initRendering(); //Initialize rendering

	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}









