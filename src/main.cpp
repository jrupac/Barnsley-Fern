#define GLUT_DISABLE_ATEXIT_HACK

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include <string>

#define WINDOW_X 800
#define WINDOW_Y 800

#define INIT_X -6.00
#define INIT_Y -1.00
#define FINAL_X 6.00
#define FINAL_Y 11.00

#define PRECISION 0.001
#define ITR 300

using namespace std;

struct Point
{
    public: 
        float x;
        float y;
};

Point p;

vector<Point> _points;
vector<short> _colors;

float _slope_x, _slope_y , _intercept_x, _intercept_y;

void keyboardFunc(unsigned char key, int x, int y) {}

void mouseFunc(int button, int state, int x, int y) {}

void reshapeFunc(int w, int h) 
{
    if (h == 0)
            h = 1;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ((float)w)/((float)h), 1, 200);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0,
            0.0, 0.0,0.0,
            0.0, 0.0, 0.0);    
}

void passiveMotionFunc(int x, int y) {}

void displayFunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    gluOrtho2D(-WINDOW_X/2, WINDOW_X/2, -WINDOW_Y/2, WINDOW_Y/2);
    
    for(int i = 0; i < _points.size(); i++)
    {
        //glPushMatrix();
        
        glColor3f(0.0f, 1.0f, 0.0f); 
        glBegin(GL_POINTS);
            glVertex2f(_points[i].x*_slope_x + _intercept_x, 
                       _points[i].y*_slope_y + _intercept_y);
        glEnd();
        
        //glColor3f(_colors[i]/(float)ITR, _colors[i]/(float)ITR,_colors[i]/(float)ITR);
        //glBegin(GL_QUADS);
            //glVertex2f(0.0f, 0.0f);
            //glVertex2f(1.0f, 0.0f);
            //glVertex2f(1.0f, 1.0f);
            //glVertex2f(0.0f, 1.0f);
        //glEnd();
        
        //glPopMatrix();
    } 
                           
    glFlush();
    glutSwapBuffers();
}

void initRendering() 
{
    glDisable(GLUT_DEPTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    
    p.x = 0.0f;
    p.y = 0.0f;
    _points.push_back(p);
    
    _slope_x = WINDOW_X/(FINAL_X - INIT_X);
    _slope_y = WINDOW_Y/(FINAL_Y - INIT_Y);
    
    _intercept_x = -WINDOW_X/2 - (_slope_x)*INIT_X;
    _intercept_y = -WINDOW_Y/2 - (_slope_y)*INIT_Y;    
    
}

void update(int value) 
{   
    int _rand = rand() % 100;
    float _temp_x = p.x, _temp_y = p.y;
    
    if(_rand == 0)
    {
        p.x = 0.0f;
        p.y = 0.16f*_temp_y;   
    }
    if(_rand >= 1 && _rand <= 6)
    {
        p.x = 0.2f*_temp_x - 0.26f*_temp_y;
        p.y = 0.23f*_temp_x + 0.22f*_temp_y + 1.6f;
    }
    if(_rand >= 7 && _rand <= 14)
    {
        p.x = -0.15f*_temp_x + 0.28f*_temp_y;
        p.y = 0.26f*_temp_x + 0.24f*_temp_y + 0.44f;
    }
    if(_rand >= 15 && _rand <= 99)
    {
        p.x = 0.85f*_temp_x + 0.04f*_temp_y;
        p.y = -0.04f*_temp_x + 0.85f*_temp_y + 1.6f;
    }        
    
    _points.push_back(p);
    
    glutPostRedisplay();
    glutTimerFunc(5, update, 0);    
}

int main( int argc, char** argv ) 
{ 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_X,WINDOW_Y);

    glutCreateWindow("Fern Fractal");
    initRendering();

    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);
    glutReshapeFunc(reshapeFunc);
    glutMouseFunc(mouseFunc);
    glutPassiveMotionFunc(passiveMotionFunc);

    glutTimerFunc(5, update, 0);
    glutMainLoop();
   
    return 0; 
}
