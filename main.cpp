/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
vector<int> arr;
vector<int> arrSorted;
int c=0;
int ci=1, key, j;
int delay = 100;
void sortOneStep(){
    key = arrSorted[ci];
    j = ci - 1;
    while (j >= 0 && arrSorted[j] > key)
    {
        arrSorted[j + 1] = arrSorted[j];
        j = j - 1;
    }
    arrSorted[j + 1] = key;
    ci++;

}

void drawLine(int x , int l , int color){
    if(color == 0){
        glColor3f(1,0,0);
    }
    else{
        glColor3f(1,1,1);
    }
    glBegin(GL_LINES);
        glVertex2f(x,0);
        glVertex2f(x,l);
    glEnd();

}

void drawLine1(int x , int l){
    cout<<"red";
    drawLine(j+50,500,1);

}
void timerfun2(int){
drawLine1(j,500);
}

 void timerfun(int)
{
    glutTimerFunc(delay,timerfun,0);
    glutPostRedisplay();
    if( ci < arrSorted.size()){
        sortOneStep();
    }else{return;}
    cout<<arr[ci]<<":"<<c++<<"\n";

}

void generateRandomArray(){
    srand(time(0));
    arr.clear();
    for(int i=0;i<400;i++){
        int randmNumn = rand()%400 + 1;
        arr.push_back(randmNumn);
	}
	arrSorted = arr;

}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);

    for(int i=0;i<arrSorted.size();i++){
        if(i==ci){
            drawLine(i+50,arrSorted[i],0);
        }
        drawLine(i+50,arrSorted[i],1);
    }
    glutSwapBuffers();
}


/*static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'r':
            glutPostRedisplay();
            break;

    }

    glutPostRedisplay();
}*/


static void idle(void)
{
    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    generateRandomArray();
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("sV");

    //glutReshapeFunc(resize);
    glutDisplayFunc(display);
  //  glutKeyboardFunc(key);
    glutTimerFunc(1000,timerfun,0);
   // glutIdleFunc(idle);

    glClearColor(0,0,0,0);
    gluOrtho2D(0,500,0,500);
    glutMainLoop();

    return EXIT_SUCCESS;
}
