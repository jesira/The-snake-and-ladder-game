#include <windows.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include<math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include<cstdlib>
#include<ctime>
#include <unistd.h>

#include "imageloader.h"

using namespace std;



float _cameraAngle = 0.0;
string over="";
float _ang_tri = 0.0;
float move_x = -1.219f, move_y=-1.1f;
float move_x2= -1.219f, move_y2=-1.1f;
int sum_p = 0, sum_q = 0;
bool move_right=true;
bool move_right2=true;
bool move_right_rvs=true;
bool move_right_rvs2=true;
int cnt=0,cnt_rvs=0;
int cnt2=0,es = 0,a=0,_a=0;
int v,v2,rvs=0,tempv = 0,prev_p=0,prev_q=0;
//bool isPlayerOneTurn = true;

bool flag_p = false;
bool flag_q = false;
GLuint _textureIdb,dice1,dice2,dice3,dice4,dice5,dice6,dicetemp,player1;
float _angle = 0;            //The rotation of the box
const float BOX_SIZE =0.7f; //the length of each side of the cube
bool rotatecomplete=false,diceRotate=false;


void updateCn(int value) {
	a += 2.0f;
	if (a > 360) {
		a -= 360;
	}
	_a += 2.0f;
	if (_a > 360) {
		_a -= 360;
	}

	glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, updateCn, 0);
}
void DrawText(const char *text, int length, int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[100];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    gluOrtho2D(0.0, 600.0, 0.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);

    for(int i=0; i<length; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}
void DrawTextBold(const char *text, int length, int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[100];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    gluOrtho2D(0.0, 600.0, 0.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);

    for(int i=0; i<length; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}
void Menu()
{



    string text;

    glColor3f(0.0 ,0.1 ,0.5 );

    text = "Player 1(BLUE) :";
    DrawText(text.data(), text.size(), 550, 288);
    text = "(press [1])";  ///add rgb
    DrawText(text.data(), text.size(), 550, 278);
    text = "Last Move :";
    DrawText(text.data(), text.size(), 550, 268);
////////////////////////
    stringstream conv;
     conv <<  over << endl;
    string  gameOver = conv.str();
    if(gameOver.size()>2)
   {
DrawTextBold(gameOver.data(), gameOver.size(), 550, 380);
text = "WON!!*";
    DrawTextBold(text.data(), text.size(), 550, 355);
   }

    conv.str("");

    conv <<  prev_p << endl;
    string  Score_p = conv.str();
    DrawText(Score_p.data(), Score_p.size(), 550, 258);

    conv.str("");

    glColor3f(.22, .62, .60);

    text = "Player 2(GRAY) :";
    DrawText(text.data(), text.size(), 550, 188);
    text = "(press [2])"; ///add rgb
    DrawText(text.data(), text.size(), 550, 178);
    text = "Last Move :";
    DrawText(text.data(), text.size(), 550, 168);

    conv <<  prev_q << endl;
    string  Score_q = conv.str();
    DrawText(Score_q.data(), Score_q.size(), 550, 158);

    conv.str("");
    glColor3f(1, 1, 1);
    text = "Double press";
    DrawText(text.data(), text.size(), 550, 110);
    text = "(esc) to exit";

    DrawText(text.data(), text.size(), 550, 100);



    glFlush();

}



void drawFront()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, dice6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();
    glutSwapBuffers();
    glutPostRedisplay();
}

void drawScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Menu();

    // GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    //GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat lightPos[] = {1, 0, 0, 1};
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    //drawing board
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glTranslatef(-0.11, 0, -5.0f); ///should be changed
    glScalef(1.8,2,2);///should be changed

    /*  glTranslatef(-0.1, 0, -5.0f); ///should be changed
    glScalef(1,2,2);///should be changed */

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,_textureIdb);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, 1.0, 0.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 1.0, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0,-1.0, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    ///drawing dice

    glPushMatrix();

    glTranslatef(7.5f, 5.0f, -20.0f);
    glRotatef(-_angle, 1.0f, 1.0f, 0.0f);
    glScalef(1.2,1.2,1.2);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, dice1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    //Top face----1
    //glColor3f(1.0f, 1.0f, 0.0f);
    glNormal3f(0.0, 1.0f, 0.0f);
    //glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    //Bottom face---------6
    //glColor3f(1.0f, 0.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, dice6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, -1.0f, 0.0f);
    //glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

    glEnd();

    //Left face----5
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, dice5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(-1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    //Front face-----3


    if(tempv==6)
        dicetemp=dice6;
    else if(tempv==5)
        dicetemp=dice5;
    else if(tempv==4)
        dicetemp=dice4;
    else if(tempv==2)
        dicetemp=dice2;
    else if(tempv==1)
        dicetemp=dice1;
    else
        dicetemp=dice3;



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, dicetemp);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();

    //Right face----2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, dice2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

    glEnd();

    //Back face--------4
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, dice4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    ///player2
    glPushMatrix();
    glTranslatef(move_x+.015, move_y+.03, -3);//Rotate about the the vector (1, 2, 3)
    glColor3f(.11, .31, .30);
    //glutSolidSphere(0.050,30,40);
    glRotated(0,1,0,0);
    glRotated(a,0,0,1);
    glutSolidTorus(0.01,0.055,25,25);
    glColor3f(.22, .62, .60);
    glutSolidSphere(0.050,30,40);
    glPopMatrix();

    ///player1

    glPushMatrix();
    glTranslatef(move_x2+.015, move_y2, -3);//Rotate about the the vector (1, 2, 3)
    glColor3f(0.0 ,0.1 ,0.5 );
    //glutSolidSphere(0.050,30,40);
    glRotated(0,1,0,0);
    glRotated(a,0,0,1);
    glutSolidTorus(0.01,0.055,25,25);
    glColor3f(0.0 ,0.1 ,0.2);
    glutSolidSphere(0.050,30,40);
    glPopMatrix();





    glutSwapBuffers();
}

void lightSetting()
{
    srand(time(0));
    GLfloat ambientIntensity[4] = {1, 0, 0, 1.0};///

    GLfloat position[4] = {0.0, 0.0, 0.0, 0.0};///???

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);// if no vertex shader is active


    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientIntensity);

    glLightfv(GL_LIGHT0, GL_POSITION, position); ///
}



GLuint loadTexture(Image* image)
{
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
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
//Render the images

void initRendering()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.00, 1.0, 200.0);

    //Image* image=loadBMP("C:\\Users\\bakif\\Desktop\\cg\\project\\S_L\\ss.bmp");
    Image* image=loadBMP("C:\\Users\\Ruhi\\Desktop\\S_L-final\\ss.bmp");
    _textureIdb=loadTexture(image);
    delete image;

    //dice1 loading
    image = loadBMP("C:\\Users\\Ruhi\\Desktop\\S_L-final\\dice1.bmp");
    dice1 = loadTexture(image);
    delete image;

    //dice2 loading
    image = loadBMP("C:\\Users\\Ruhi\\Desktop\\S_L-final\\dice2.bmp");
    dice2 = loadTexture(image);
    delete image;

    //dice3 loading
    image = loadBMP("C:\\Users\\Ruhi\\Desktop\\S_L-final\\dice3.bmp");
    dice3 = loadTexture(image);
    delete image;

    //dice4 loading
    image = loadBMP("C:\\Users\\Ruhi\\Desktop\\S_L-final\\dice4.bmp");
    dice4 = loadTexture(image);
    delete image;

    //dice5 loading
    image = loadBMP("C:\\Users\\Ruhi\\Desktop\\S_L-final\\dice5.bmp");
    dice5 = loadTexture(image);
    delete image;

    //dice6 loading
    image = loadBMP("C:\\Users\\Ruhi\\Desktop\\S_L-final\\dice6.bmp");
    dice6 = loadTexture(image);
    delete image;

    /* image = loadBMP("C:\\Users\\Ruhi\\Desktop\\Graphics\\S_L-final\\S_L-final\\player1.bmp");
    player1 = loadTexture(image);
    delete image;

    */
    //have to load other things================
}

//update function , Called every 25 milliseconds
void update(int value)
{
    _angle += 12.0f;
    if (_angle > 360)
    {
        _angle -= 360;
    }

    glutPostRedisplay();
    if(diceRotate)
    {
        glutTimerFunc(25, update, 0);

    }
    //glutTimerFunc(25, update, 0);
}

void update_a(int value_x, int value_y)
{
    glutPostRedisplay();
    glPushMatrix();
    glTranslatef(value_x, value_y, -3);
    glColor3f(1.0,0.0,0);
    glutSolidSphere(0.055,40,50);
    glPopMatrix();

    glutSwapBuffers();
}
void update_b(int value_x, int value_y)
{
    glutPostRedisplay();
    glPushMatrix();
    glTranslatef(value_x, value_y, -3);
    glColor3f(1.0,0.0,0);
    glutSolidSphere(0.055,40,50);
    glPopMatrix();

    glutSwapBuffers();
}

void handleKeypress(unsigned char key, int x, int y)
{

    switch (key)
    {
    case 27:
        es++;
        if(es==2){
            exit(0);
        }
        break;
    case 50: //Q
        if(!flag_q)
        {
            if (!diceRotate) //start rotate
            {
                diceRotate=true;
                glutTimerFunc(25,update,0) ;///
                drawFront();
            }
            else//stop rotating
            {
                flag_q = true;
                flag_p = false;
                diceRotate=false;
                _angle=0;
                prev_p=sum_p;
                v=rand() % 6 + 1;
                tempv = v;


                //cout<<v;
                /// 95,89,98 check snake

                sum_q+=v;
                ///ladder
                if(sum_q==4) //v=4
                {
                    v+=10; //v== 14
                    sum_q+=10; //v == 18
                }
                else if(sum_q==9)
                {
                    v+=22;
                    sum_q+=22;
                }
                else if(sum_q==18)
                {
                    v+=27;
                    sum_q+=27;
                }
                else if(sum_q==21)
                {
                    v+=21;
                    sum_q+=21;
                }
                else if(sum_q==28)
                {
                    v+=56;
                    sum_q+=56;
                }
                else if(sum_q==51)
                {
                    v+=16;
                    sum_q+=16;
                }
                else if(sum_q==71)
                {
                    v+=20;
                    sum_q+=20;
                }
                else if(sum_q==78)
                {
                    v+=19;
                    sum_q+=19;
                }
                ///snake
                if(sum_q==26)
                {
                    // move to 11
                    rvs = 11;
                    sum_q-=15;
                }
                else if(sum_q==52)
                {
                    //move to 29
                    rvs=29;
                    sum_q-=23;
                }
                else if(sum_q==62)
                {
                    //move to 19
                    rvs=19;
                    sum_q-=43;
                }
                else if(sum_q==66)
                {
                    //move to 59
                    rvs=59;
                    sum_q-=7;
                }
                else if(sum_q==74)
                {
                    //move to 17
                    rvs=17;
                    sum_q-=57;
                }
                else if(sum_q==89)
                {
                    //move to 69
                    rvs=69;
                    sum_q-=20;
                }
                else if(sum_q==95)
                {
                    //move to 75
                    rvs=75;
                    sum_q-=20;
                }
                else if(sum_q==98)
                {
                    //move to 79
                    rvs=79;
                    sum_q-=19;
                }

                ///MOVE
                if(sum_q>100)
                {
                    sum_q-=v;
                }
                else
                {
                    for(int i=1; i<=v; i++)
                    {
                        if(move_right)
                        {

                            if(cnt<10)
                            {
                                move_x+=0.215;
                                update_a(move_x, move_y);
                                cnt++;
                            }
                            else
                            {
                                move_x+=0.215;
                                update_a(move_x, move_y);
                                move_right=false;
                                move_x-=0.215;
                                move_y+=0.24;
                                cnt=1;
                            }
                        }
                        else
                        {
                            if(cnt<10)
                            {
                                move_x-=0.215f;
                                update_a(move_x, move_y);
                                cnt++;
                            }
                            else
                            {
                                move_x-=0.215f;
                                update_a(move_x, move_y);
                                move_x+=0.215f;
                                move_right=true;
                                move_y+=0.24f;
                                cnt=1;
                            }
                        }
                    }
                }

                if(rvs>0) /// dice on snake
                {
                    cnt=0;
                    move_right=true;
                    move_x = -1.219f;
                    move_y=-1.1f;
                    for(int i=1; i<=rvs; i++)
                    {
                        if(move_right)
                        {

                            if(cnt<10)
                            {
                                move_x+=0.215;
                                update_a(move_x, move_y);
                                cnt++;
                            }
                            else
                            {
                                move_x+=0.215;
                                update_a(move_x, move_y);
                                move_right=false;
                                move_x-=0.215;
                                move_y+=0.24;
                                cnt=1;
                            }
                        }
                        else
                        {
                            if(cnt<10)
                            {
                                move_x-=0.215f;
                                update_a(move_x, move_y);
                                cnt++;
                            }
                            else
                            {
                                move_x-=0.215f;
                                update_a(move_x, move_y);
                                move_x+=0.215f;
                                move_right=true;
                                move_y+=0.24f;
                                cnt=1;
                            }
                        }
                    }
                }
                rvs=0;
                cout<<"\n sum q :"<<sum_q<<endl;
                if(sum_q==100)
                {
                    over = "PLAYER 2";
                    cout<<"player 2 wins"<<endl;
                    flag_p = true;
                    flag_q = true;
                }
            }
        }
        break;

    case 49:  //1
        if(!flag_p)
        {
            if (!diceRotate) //start rotate
            {
                diceRotate=true;
                glutTimerFunc(25,update, 0) ;
                drawFront();
            }
            else //stop rotating
            {
                flag_p = true;
                flag_q = false;
                diceRotate=false;
////////////////////
                _angle=0;
                prev_q=sum_q;
                v=rand() % 6 + 1;
                tempv = v;
                //cout<<v;
                /// 95,89,98 check snake

                sum_p+=v;
                ///ladder
                if(sum_p==4) //v=4
                {
                    v+=10; //v== 14
                    sum_p+=10; //v == 18
                }
                else if(sum_p==9)
                {
                    v+=22;
                    sum_p+=22;
                }
                else if(sum_p==18)
                {
                    v+=27;
                    sum_p+=27;
                }
                else if(sum_p==21)
                {
                    v+=21;
                    sum_p+=21;
                }
                else if(sum_p==28)
                {
                    v+=56;
                    sum_p+=56;
                }
                else if(sum_p==51)
                {
                    v+=16;
                    sum_p+=16;
                }
                else if(sum_p==71)
                {
                    v+=20;
                    sum_p+=20;
                }
                else if(sum_p==78)
                {
                    v+=19;
                    sum_p+=19;
                }
                ///snake
                else if(sum_p==26)
                {
                    // move to 11
                    rvs = 11;
                    sum_p-=15;
                }
                else if(sum_p==52)
                {
                    //move to 29
                    rvs=29;
                    sum_p-=23;
                }
                else if(sum_p==62)
                {
                    //move to 19
                    rvs=19;
                    sum_p-=43;
                }
                else if(sum_p==66)
                {
                    //move to 59
                    rvs=59;
                    sum_p-=7;
                }
                else if(sum_p==74)
                {
                    //move to 17
                    rvs=17;
                    sum_p-=57;
                }
                else if(sum_p==89)
                {
                    //move to 69
                    rvs=69;
                    sum_p-=20;
                }
                else if(sum_p==95)
                {
                    //move to 75
                    rvs=75;
                    sum_p-=20;
                }
                else if(sum_p==98)
                {
                    //move to 79
                    rvs=79;
                    sum_p-=19;
                }

                ///MOVE
                if(sum_p>100)
                {
                    sum_p-=v;
                }
                else
                {
                    for(int i=1; i<=v; i++)
                    {
                        if(move_right2)
                        {

                            if(cnt2<10)
                            {
                                move_x2+=0.215;
                                update_b(move_x2, move_y2);
                                cnt2++;
                            }
                            else
                            {
                                move_x2+=0.215;
                                update_b(move_x2, move_y2);
                                move_right2=false;
                                move_x2-=0.215;
                                move_y2+=0.24;
                                cnt2=1;
                            }
                        }
                        else
                        {
                            if(cnt2<10)
                            {
                                move_x2-=0.215f;
                                update_b(move_x2, move_y2);
                                cnt2++;
                            }
                            else
                            {
                                move_x2-=0.215f;
                                update_b(move_x2, move_y2);
                                move_x2+=0.215f;
                                move_right2=true;
                                move_y2+=0.24f;
                                cnt2=1;
                            }
                        }
                    }
                }

                if(rvs>0) /// dice on snake
                {
                    cnt2=0;
                    move_right2=true;
                    move_x2 = -1.219f;
                    move_y2=-1.1f;
                    for(int i=1; i<=rvs; i++)
                    {
                        if(move_right2)
                        {

                            if(cnt2<10)
                            {
                                move_x2+=0.215;
                                update_b(move_x2, move_y2);
                                cnt2++;
                            }
                            else
                            {
                                move_x2+=0.215;
                                update_b(move_x2, move_y2);
                                move_right2=false;
                                move_x2-=0.215;
                                move_y2+=0.24;
                                cnt2=1;
                            }
                        }
                        else
                        {
                            if(cnt2<10)
                            {
                                move_x2-=0.215f;
                                update_b(move_x2, move_y2);
                                cnt2++;
                            }
                            else
                            {
                                move_x2-=0.215f;
                                update_b(move_x2, move_y2);
                                move_x2+=0.215f;
                                move_right2=true;
                                move_y2+=0.24f;
                                cnt2=1;
                            }
                        }
                    }
                }
                rvs=0;
                cout<<"sum p :"<<sum_p<<endl;
                if(sum_p==100)
                {
                    over = "PLAYER 1";
                    cout<<"player 1 wins"<<endl;
                    flag_p = true;
                    flag_q = true;


                }
            }
        }
        break;

    }
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Snake and Ladder");
    lightSetting();
    initRendering();
    glutFullScreen();
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(25, update, 0);
    glutTimerFunc(25, updateCn, 0); //Add a timer
    glutMainLoop();
    return 0;
}


///yellow = p, red q






