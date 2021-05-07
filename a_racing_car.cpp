/*********************************************************************************
  *Copyright(C),None
  *FileName:  OpenGLDemo.cpp
  *Author:  Collapsar-G
  *Version:  1.0.0
  *Date:  2021.5.7
  *Description:  实现了
     
  *Others:  
  *Todo:
    1. 利用Gl/Glu/Glut库，编写一个OpenGL程序，实现以下功能：
        1.1. 设计并绘制一辆汽车模型以及一个简单的直线跑道；其中，车轮可以用glutCylinder来绘制。
        1.2. 缺省视图是从外面一个固定的视点观察汽车和跑道；
	    1.3. 利用鼠标和键盘控制汽车前进、后退、转弯、加速和减速；
	    1.4. 制作一个弹出菜单，上面的菜单项用来控制车身和车轮的颜色以及退出程序；
	    1.5. 定义对应于ReShape事件的回调函数，使得当用户改变窗口的大小时，显示的汽车不会变形。
    2. 扩展部分
        2.1. 采用弯曲的封闭的跑道。
	    2.2. 轮胎画成封闭的形状。以上例子画出的只是一个两端开放的圆柱面, 你们可以使用gluDisk(…) 将圆柱体两端封闭。
	    2.3. 在路边设置一些路标，对于地面、跑道和天空进行纹理映射等以增强逼真度。
	    2.4. 除了缺省视图之外，支持第二种视图：坐在车内从驾驶座位向前看的视图。两种视图之间用“t”键进行切换。
	    2.5. 使用光照进行渲染。
  * Function:
    1. int main()：项目入口


**********************************************************************************/
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <cmath>
#include <Windows.h>
#include <Gl/glut.h> 
#define MAX_CHAR 128
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;
/*
int   DrawGLScene(GLvoid)               //   从这里开始进行所有的绘制 
{
    gluCylinder(quadratic, 0.6f, 0.6f, 0.4f, 32, 32);//画圆柱 
}

GLUquadricObj* quadratic;

int   InitGL(GLvoid) //   此处开始对OpenGL进行所有设置 
{
    quadratic = gluNewQuadric(); //   创建二次几何体 
}

int main(int argc, char* argv[]) //
{
    return 0;
}
*/
#define ESCAPE 0

/* The number of our GLUT window */
int window;

/* rotation angle for the triangle. */
float rtri = 0.0f;

/* rotation angle for the quadrilateral. */
float rquad = 0.0f;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
// We call this right after our OpenGL window is created.
void InitGL(int Width, int Height)
{
    // This Will Clear The Background Color To Black
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);                // Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);                // The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);            // Enables Depth Testing
    glShadeModel(GL_SMOOTH);            // Enables Smooth Color Shading

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                // Reset The Projection Matrix

    gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
    if (Height == 0)                // Prevent A Divide By Zero If The Window Is Too Small
        Height = 1;

    glViewport(0, 0, Width, Height);        // Reset The Current Viewport And Perspective Transformation

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

float ballX = -0.5f;
float ballY = 0.0f;
float ballZ = 0.0f;

void drawBall(void) {
    glColor3f(0.0, 1.0, 0.0); //set ball colour
    glTranslatef(ballX, ballY, ballZ); //moving it toward the screen a bit on creation
    //glRotatef(ballX,ballX,ballY,ballZ);
    glutSolidSphere(0.3, 20, 20); //create ball.
    glTranslatef(ballX + 1.5, ballY, ballZ); //moving it toward the screen a bit on creation
    glutSolidSphere(0.3, 20, 20); //
}


/* The main drawing function. */
void DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        // Clear The Screen And The Depth Buffer
    glLoadIdentity();                // Reset The View

    glTranslatef(rtri, 0.0f, -6.0f);        // Move Left 1.5 Units And Into The Screen 6.0

    //glRotatef(rtri,1.0f,0.0f,0.0f);        // Rotate The Triangle On The Y axis
    // draw a triangle (in smooth coloring mode)
    glBegin(GL_POLYGON);                // start drawing a polygon
    glColor3f(1.0f, 0.0f, 0.0f);            // Set The Color To Red
    glVertex3f(-1.0f, 1.0f, 0.0f);        // Top left
    glVertex3f(0.4f, 1.0f, 0.0f);

    glVertex3f(1.0f, 0.4f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);            // Set The Color To Green
    glVertex3f(1.0f, 0.0f, 0.0f);        // Bottom Right
    glColor3f(0.0f, 0.0f, 1.0f);            // Set The Color To Blue
    glVertex3f(-1.0f, 0.0f, 0.0f);// Bottom Left    

    //glVertex3f();
    glEnd();                    // we're done with the polygon (smooth color interpolation)
    drawBall();

    rtri += 0.005f;                    // Increase The Rotation Variable For The Triangle
    if (rtri > 2)
        rtri = -2.0f;
    rquad -= 15.0f;                    // Decrease The Rotation Variable For The Quad

    // swap the buffers to display, since double buffering is used.
    glutSwapBuffers();
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y)
{
    /* sleep to avoid thrashing this procedure */
   // usleep(100);

    /* If escape is pressed, kill everything. */
    if (key == ESCAPE)
    {
        /* shut down our window */
        glutDestroyWindow(window);

        /* exit the program...normal termination. */
        exit(0);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

    /* get a 640 x 480 window */
    glutInitWindowSize(640, 480);

    /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(0, 0);

    /* Open a window */
    window = glutCreateWindow("Moving Car");

    /* Register the function to do all our OpenGL drawing. */
    glutDisplayFunc(&DrawGLScene);

    /* Go fullscreen.  This is as soon as possible. */
    //glutFullScreen();

    /* Even if there are no events, redraw our gl scene. */
    glutIdleFunc(&DrawGLScene);

    /* Register the function called when our window is resized. */
    glutReshapeFunc(&ReSizeGLScene);

    /* Register the function called when the keyboard is pressed. */
    glutKeyboardFunc(&keyPressed);

    /* Initialize our window. */
    InitGL(640, 480);

    /* Start Event Processing Engine */
    glutMainLoop();

    return 1;
}