
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include "textures.h"
#include <iostream>
#include <fstream>
using namespace std;

int i = 0, value[15][10];
double eyeX = 2.0;
double eyeY = 10.0;
double eyeZ = 12.0;
int xa = -5;
int za = -2;
int xc = -4;
int zc = -1;
int check_in = 1;

COGLTexture Tex1, Tex2,Tex3;

void InitTextures(void)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	Tex1.LoadFromFile("tex5.bmp");
	Tex2.LoadFromFile("nensan.bmp");
	Tex3.LoadFromFile("tex3.bmp");


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

}

void myInit(void){
     glClearColor( 0.3, 0.0, 0.0, 0.0 );
     glColor3f(0.0, 0.0, 0.0);
     glPointSize( 2.0 );
     glMatrixMode( GL_PROJECTION );
     glLoadIdentity( );
     glOrtho(-10, 15, -10, 10, -1, 0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity( );
}
void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 60.0);
   glMatrixMode (GL_MODELVIEW);
   gluLookAt (eyeX, eyeY,eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
bool status_brick(float ax, float az, float cx, float cz){
	int aa = int (ax-az);
	int cc = int (cx-cz);
	if(abs(aa)==abs(cc)) return true;
	else return false;
}
void drawGround(GLdouble ax, GLdouble az) {// ban co
	double y = -0.3 , cx = ax+1, cz = az+1 ;

    glEnable(GL_TEXTURE_2D);
	Tex2.SetActive();
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0,0.0);
		glVertex3d(ax,0,az);	//a
		glTexCoord2f(1.0,0.0);
		glVertex3d(cx,0,az);	//b
		glTexCoord2f(1.0,1.0);
		glVertex3d(cx,0,cz);	//c
		glTexCoord2f(0.0,1.0);
		glVertex3d(ax,0,cz);	//d
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3d(ax,y,az);	//e
		glVertex3d(cx,y,az);	//f
		glVertex3d(cx,y,cz);	//g
		glVertex3d(ax,y,cz);	//h
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3d(ax,0,az);	//a
		glVertex3d(ax,y,az);	//e
		glVertex3d(ax,y,cz);	//h
		glVertex3d(ax,0,cz);	//d
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3d(cx,0,az);	//b
		glVertex3d(cx,0,cz);	//c
		glVertex3d(cx,y,cz);	//g
		glVertex3d(cx,y,az);	//f
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3d(ax,0,az);	//a
		glVertex3d(cx,0,az);	//b
		glVertex3d(cx,y,az);	//f
		glVertex3d(ax,y,az);	//e
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3d(ax,0,cz);	//d
		glVertex3d(cx,0,cz);	//c
		glVertex3d(cx,y,cz);	//g
		glVertex3d(ax,y,cz);	//h
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void chessValue (char* c) {
     ifstream f;
     f.open (c, ios::in);

     for(int i = 0; i < 15; i++)
             for(int j = 0; j < 10; j++)
                     f >> value[i][j];
}

void drawBrick(float ax, float az, float cx, float cz) {// quan co
	float y = 1;
	if(status_brick(xa,za,xc,zc)) y=2;
	//glBegin(GL_LINE_LOOP);
	glEnable(GL_TEXTURE_2D);
	Tex1.SetActive();
	glBegin(GL_POLYGON);// mat day duoi
		glTexCoord2f(0.0,0.0);
		glVertex3d(ax,0,az);	//a
		glTexCoord2f(0.0,1.0);
		glVertex3d(cx,0,az);	//b
		glTexCoord2f(1.0,1.0);
		glVertex3d(cx,0,cz);	//c
		glTexCoord2f(1.0,0.0);
		glVertex3d(ax,0,cz);	//d
	glEnd();
	Tex1.SetActive();
	glBegin(GL_POLYGON); // mat day tren
		glTexCoord2f(0.0,0.0);
		glVertex3d(ax,y,az);	//e
		glTexCoord2f(0.0,1.0);
		glVertex3d(cx,y,az);	//f
		glTexCoord2f(1.0,1.0);
		glVertex3d(cx,y,cz);	//g
		glTexCoord2f(1.0,0.0);
		glVertex3d(ax,y,cz);	//h
	glEnd();
	Tex1.SetActive();
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0,0.0);
		glVertex3d(ax,0,az);	//a
		glTexCoord2f(0.0,1.0);
		glVertex3d(ax,y,az);	//e
		glTexCoord2f(1.0,1.0);
		glVertex3d(ax,y,cz);	//h
		glTexCoord2f(1.0,0.0);
		glVertex3d(ax,0,cz);	//d
	glEnd();
	Tex1.SetActive();
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0,0.0);
		glVertex3d(cx,0,az);	//b
		glTexCoord2f(0.0,1.0);
		glVertex3d(cx,0,cz);	//c
		glTexCoord2f(1.0,1.0);
		glVertex3d(cx,y,cz);	//g
		glTexCoord2f(1.0,0.0);
		glVertex3d(cx,y,az);	//f
	glEnd();
	Tex1.SetActive();
	glBegin(GL_POLYGON);	//mat sau
		glTexCoord2f(0.0,0.0);
		glVertex3d(ax,0,az);	//a
		glTexCoord2f(0.0,1.0);
		glVertex3d(cx,0,az);	//b
		glTexCoord2f(1.0,1.0);
		glVertex3d(cx,y,az);	//f
		glTexCoord2f(1.0,0.0);
		glVertex3d(ax,y,az);	//e
	glEnd();
	Tex1.SetActive();
	glBegin(GL_POLYGON);	//mat truoc
		glTexCoord2f(0.0,0.0);
		glVertex3d(ax,0,cz);	//d
		glTexCoord2f(0.0,1.0);
		glVertex3d(cx,0,cz);	//c
		glTexCoord2f(1.0,1.0);
		glVertex3d(cx,y,cz);	//g
		glTexCoord2f(1.0,0.0);
		glVertex3d(ax,y,cz);	//h
	glEnd();
	glDisable(GL_TEXTURE_2D);

}
void Brickdone(float ax, float az, float cx, float cz) {// quan co
	float y = 1;
	if(status_brick(xa,za,xc,zc)) y=2;
	//glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);
		glVertex3d(ax,0,az);	//a
		glVertex3d(cx,0,az);	//b
		glVertex3d(cx,0,cz);	//c
		glVertex3d(ax,0,cz);	//d
	glEnd();
	//glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);
		glVertex3d(ax,y,az);	//e
		glVertex3d(cx,y,az);	//f
		glVertex3d(cx,y,cz);	//g
		glVertex3d(ax,y,cz);	//h
	glEnd();
	//glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);
		glVertex3d(ax,0,az);	//a
		glVertex3d(ax,y,az);	//e
		glVertex3d(ax,y,cz);	//h
		glVertex3d(ax,0,cz);	//d
	glEnd();
	//glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);
		glVertex3d(cx,0,az);	//b
		glVertex3d(cx,0,cz);	//c
		glVertex3d(cx,y,cz);	//g
		glVertex3d(cx,y,az);	//f
	glEnd();
	//glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);
		glVertex3d(ax,0,az);	//a
		glVertex3d(cx,0,az);	//b
		glVertex3d(cx,y,az);	//f
		glVertex3d(ax,y,az);	//e
	glEnd();
	//glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);
		glVertex3d(ax,0,cz);	//d
		glVertex3d(cx,0,cz);	//c
		glVertex3d(cx,y,cz);	//g
		glVertex3d(ax,y,cz);	//h
	glEnd();
}
void myDisplay(){
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     //gan trong so cho cac o trong ban co
     chessValue("chess_value.dat");

     //draw ground
     for(int x = -5; x < 10; x++)
             for(int z = -5; z < 5; z++) {
                     if (value[x+5][z+5] ==1)
                       drawGround(x, z);
             }
       //------------------------------------------------------
      // code cua Dung tu phan nay
        if(value[xa+5][za+5]==0)check_in =0;
        if(!status_brick(xa,za,xc,zc))
          if((xa-xc) == 2||(xa-xc) == -2){
                if(value[xc+4][za+5]==0)check_in =0;
          }else{
                if(value[xc+4][zc+4]==0)check_in =0;
          }
        if(status_brick(xa,za,xc,zc)&&(value[xa+5][za+5]==-1))check_in =-1;
      if(check_in == 1){
     	          //glColor3d(1.0,0.0,0.0);
                  drawBrick(xa,za,xc,zc);
      }
      if(check_in == -1){
     	          //glColor3d(1.0,0.0,0.0);
                  Brickdone(xa,za,xc,zc);
      }
      // den phan nay
    //-----------------------------------------------------------
     glutSwapBuffers();
}
static void key1(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
			if(status_brick(xa,za,xc,zc)){
				xa = xa + 1;
				xc = xc + 2;
			}else{
                  if((xa-xc) == 2||(xa-xc) == -2){
                             xa = xa + 2;
                             xc = xc + 1;
                  }else{
                             xa = xa + 1;
                             xc = xc + 1;
                  }
            }
            break;
        case GLUT_KEY_DOWN:
			if(status_brick(xa,za,xc,zc)){
				xa = xa - 2;
				xc = xc - 1;
			}else{
                  if((xa-xc) == 2||(xa-xc) == -2){
                             xa = xa - 1;
                             xc = xc - 2;
                  }else{
                             xa = xa - 1;
                             xc = xc - 1;
                  }
            }
            break;
        case GLUT_KEY_LEFT:
			if(status_brick(xa,za,xc,zc)){
				za = za - 2;
				zc = zc - 1;
			}else{
                  if((za-zc) == 2||(za-zc) == -2){
                             za = za - 1;
                             zc = zc - 2;
                  }else{
                             za = za - 1;
                             zc = zc - 1;
                  }
            }
            break;
        case GLUT_KEY_RIGHT:
           	if(status_brick(xa,za,xc,zc)){
				za = za + 1;
				zc = zc + 2;
			}else{
                  if((za-zc) == 2||(za-zc) == -2){
                             za = za + 2;
                             zc = zc + 1;
                  }else{
                             za = za + 1;
                             zc = zc + 1;
                  }
            }
            break;
        case GLUT_KEY_F2:
             xa=-5,za=-2,xc=-4,zc=-1;
             check_in = 1;
             break;
		default:
			break;
    }
    glutPostRedisplay();
}
static void key2(char unsigned key, int x, int y) {
	switch(key) {
        case 'w':
            eyeX += 0.2;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'x':
            eyeX -= 0.2;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'a':
            eyeY += 0.2;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'd':
            eyeY -= 0.2;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'z':
            eyeZ -= 0.2;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
		case 'c':
            eyeZ += 0.2;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
		default:
			break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv){
    // Controls
	cout << "\t+-----------------------------------------------------------+"	<< endl;
	cout << "\t|                  - Computer Graphics -                    |"	<< endl;
	cout << "\t|            Group 6:                                       |"	<< endl;
	cout << "\t|                    Phung Duy Dung                         |"	<< endl;
	cout << "\t|                    Le Thi Hai                             |"	<< endl;
	cout << "\t|                    Nong Thi Linh                          |"	<< endl;
	cout << "\t|                    Truong Thi Thu                         |"	<< endl;
	cout << "\t+-----------------------------------------------------------+";
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowSize( 1000, 600 );
     glutInitWindowPosition( 10, 15 );
     glutCreateWindow( "Assignment" );
     myInit();
     glFrontFace(GL_CW);
	 glCullFace(GL_BACK);
	 glEnable(GL_DEPTH_TEST);
	 glShadeModel(GL_SMOOTH);
	 InitTextures();
     glutDisplayFunc( myDisplay );
     glutSpecialFunc(key1);
	 glutKeyboardFunc(key2);
     glutReshapeFunc(reshape);
     glutMainLoop();
     return 0;
}
