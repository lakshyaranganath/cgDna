#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*---------------------------------------------------------------------------------------*/
/*							   DECLARATIONS												 */
/*---------------------------------------------------------------------------------------*/

void *fonts[]=
{
    GLUT_BITMAP_9_BY_15,
    GLUT_BITMAP_TIMES_ROMAN_10,
    GLUT_BITMAP_TIMES_ROMAN_24,
    GLUT_BITMAP_HELVETICA_18,
    GLUT_BITMAP_HELVETICA_12
};

#define PI 3.1415926
int page=-1; //start at intro page
float theta=1;


/*---------------------------------------------------------------------------------------*/
/*							   HELPER FUNCTIONS									         */
/*---------------------------------------------------------------------------------------*/

//for printing text
void output(int x, int y, char *string, void *font)
{
    int len, i;
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(font, string[i]);
    }
}

void drawHelixStrand(float cx, float cy, float r, float angle=0)
{
	float x, y, z, theta;
	int i, n = 565;
	angle = angle * PI / 180.0;
	glBegin(GL_LINE_STRIP);
	    for(i=0; i<n; i++)
	    {
	    	theta = 2.0 * PI * i / n;
	    	x = cx - (r * sinf(1 * theta + angle));
	    	y = cy + i;
	    	z = r * cosf(1 * theta + angle);

	    	glVertex3f(x, y, z);
	    }
    glEnd();
}

void drawSphere(float x, float y, float z)
{
    glTranslatef(x, y, z);
    glutSolidSphere(7, 20, 20);
    glTranslatef(-x, -y, -z);
}

void drawHelixLine(float cx, float cy, float r, float angle=180)
{
	float x1, x2, y1, y2, z1, z2, theta;
	int i, n = 565;
	angle = angle * PI / 180.0;
    for(i=0; i<n; i+=n/10)
    {
        glColor3ub(46, 204, 113);
        
		glBegin(GL_LINE_STRIP);
	    	theta = 2.0 * PI * i / n;
	    	x1 = cx - (r * sinf(1 * theta));
	    	y1 = cy + i;
	    	z1 = r * cosf(1 * theta);

	    	x2 = cx - (r * sinf(1 * theta + angle));
	    	y2 = cy + i;
	    	z2 = r * cosf(1 * theta + angle);

	    	glVertex3f(x1, y1, z1);
	    	glVertex3f(x2, y2, z2);
			
		glEnd();

        glColor3ub(52, 73, 94);
        drawSphere(x1, y1, z1);
        drawSphere(x2, y2, z2);
    }
}

void drawCircle(float cx, float cy, GLubyte color[])
{
    float x, y, theta, r=color[0];
    int i, n=720;
    glColor3ub(color[1],color[2],color[3]);
    glBegin(GL_POLYGON);
    for(i=0; i<n; i++)
    {
        theta = 2.0 * PI * i / n;
        x = r * sinf(theta);
        y = r * cosf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawBondLine(float x1, float y1, float x2, float y2)
{
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

/*---------------------------------------------------------------------------------------*/
/*                                PAGES                                                  */
/*---------------------------------------------------------------------------------------*/
                                                                                      
void intro()
{
    glColor3ub(52, 73, 94);
    output(370, 580, "DNA - Deoxyribonucleic Acid", fonts[2]);

    glColor3ub(231, 76, 60);
    output(420, 450, "Damini Cousik", fonts[3]);
    output(420, 380, "Lakshya Ranganath", fonts[3]);
    output(420, 310, "Peri Nikhil", fonts[3]);

    glColor3ub(39, 174, 96);
    output(420, 430, "1DS12CS023", fonts[0]);
    output(420, 360, "1DS12CS045", fonts[0]);
    output(420, 290, "1DS12CS061", fonts[0]);

    glColor3ub(52, 73, 94);
    output(370, 125, "Press any key to continue...", fonts[0]);
}

/*--------------------------------------------------------------------------------------*/
                                                                                      
void menu()
{
    glColor3ub(52, 73, 94);
    output(370, 580, "DNA - Deoxyribonucleic Acid", fonts[2]);

    glColor3ub(39, 174, 96);
    output(420, 450, "Menu", fonts[3]);

    glColor3ub(231, 76, 60);
    output(420, 420, "1. DNA", fonts[0]);
    output(420, 390, "2. Adenine-Thymine", fonts[0]);
    output(420, 360, "3. Cytosine-Guanine", fonts[0]);
    output(420, 330, "ESC. Exit", fonts[0]);
}

/*--------------------------------------------------------------------------------------*/

void dna()
{
    float cx = 90, cy = 140, r=100;

    glLineWidth(5.0);

    glPushMatrix();   
     
        glRotatef(45, 0, 0, -1);
        
        glPushMatrix();
 
            glTranslatef(cx, cy, 0);
            glRotatef(theta, 0.0, 1.0, 0.0);
            
            glColor3ub(52, 152, 219);
            drawHelixStrand(0, cy, r, 0);
            glColor3ub(231, 76, 60);
            drawHelixStrand(0, cy, r, 138);
            drawHelixLine(0, cy, r, 138);

            glTranslatef(-cx, -cy, 0); 
            glutPostRedisplay();  

        glPopMatrix();
    
    glPopMatrix();
    
    theta+=0.75;
    glutPostRedisplay();
}

/*--------------------------------------------------------------------------------------*/

void adenineThymine()
{
    //radius and color declarations
    GLubyte red[] = {15, 255, 0, 0};          //oxygen
    GLubyte green[] = {20, 0, 255, 0};        //carbon
    GLubyte blue[] = {20, 0, 0, 255};         //nitrogen
    GLubyte white[] = {10, 255, 255, 255};    //hydrogen
    
    drawCircle(500, 500, red);
    drawCircle(500, 400, green);
    drawCircle(500, 300, blue);
    drawCircle(500, 200, white);
    drawBondLine(500,500,750,750);
}

/*--------------------------------------------------------------------------------------*/

void cytosineGuanine()
{
    //put cytosineGuanine page code here
}


/*---------------------------------------------------------------------------------------*/
/*                              DISPLAY FUNCTION                                         */
/*---------------------------------------------------------------------------------------*/

void display(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1000, 0.0, 650,-2000,1500);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.9, 0.9, 0.9, 0.9);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    switch(page)
    {
        case -1: intro();           break;
        case  0: menu();            break;
        case  1: dna();             break;
        case  2: adenineThymine();  break;
        case  3: cytosineGuanine(); break;
    }


    glFlush();
    glutSwapBuffers();
}

void reshape (int w,int h)
{
    glViewport(0, 0, w, h);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w/ (GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

/*---------------------------------------------------------------------------------------*/
/*							KEY/MOUSE-MENU FUNCTIONS									 */
/*---------------------------------------------------------------------------------------*/

void NormalKey(GLubyte key, GLint x, GLint y)
{
    //ESC to exit application
    if(key==27)
        exit(0);

    //at intro
    if(page==-1)
    {
        //if any key is pressed then goto menu
        page=0;
        glutPostRedisplay();
    }

    //at menu
    else if(page==0)
    {
        switch(key)
        {
            case '1': page=1;	break; //goto dna
            case '2': page=2;	break; //goto adenineThymine
            case '3': page=3;	break; //goto cytosineGuanine
            case 'i':
            case 'I': page=-1;	break; //go back to intro
        }
        glutPostRedisplay();
    }

    //at any page
    else
    {
        if(key=='m' || key=='M')
        {
            //go back to menu
            page=0;
            glutPostRedisplay();
        }
    }
    
}

/*--------------------------------------------------------------------------------------*/

void mouseMenuTrigger(int id)
{
    switch(id)
    {
        case 1: page=1;     break; //goto dna
        case 2: page=2;     break; //goto adenineThymine
        case 3: page=3;     break; //goto cytosineGuanine
        case 4: exit(0);    //exit application
    }
    glutPostRedisplay();
}

void createMouseMenu()
{
    glutCreateMenu(mouseMenuTrigger);
    glutAddMenuEntry("DNA", 1);
    glutAddMenuEntry("Adenine-Thymine", 2);
    glutAddMenuEntry("Cytosine-Guanine", 3);
    glutAddMenuEntry("Exit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/*---------------------------------------------------------------------------------------*/
/*							MAIN FUNCTION                                                */
/*---------------------------------------------------------------------------------------*/

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize(1024,768);
    glutInitWindowPosition(0,0);
    glutCreateWindow("DNA");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glEnable(GL_DEPTH_TEST);
  
    glutKeyboardFunc(NormalKey);
    createMouseMenu();

    glutMainLoop();
    return 0;
}