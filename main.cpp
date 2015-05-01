#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int page=-1; //start at intro page

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

void drawHelixLine(float cx, float cy, float r, float angle=0)
{
	float x1, x2, y1, y2, z1, z2, theta;
	int i, n = 565;
	angle = angle * PI / 180.0;
    for(i=0; i<n; i+=35)
    {
        glColor3f(0.75, 0.75, 0.0);
        
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

        glColor3f(0.25, 0.25, 0.25);
        drawSphere(x1, y1, z1);
        drawSphere(x2, y2, z2);

    }
}

/*---------------------------------------------------------------------------------------*/
/*                                PAGES                                                  */
/*---------------------------------------------------------------------------------------*/
                                                                                      
void intro()
{
    glColor3f(0.8, 0.1, 0.2);
    output(350, 580, "DNA - Deoxyribonucleic Acid", fonts[2]);

    glColor3f(1, 0.5, 0);
    output(420, 450, "Damini Cousik", fonts[3]);
    output(420, 380, "Lakshya Ranganath", fonts[3]);
    output(420, 310, "Peri Nikhil", fonts[3]);

    glColor3f(0.5, 0.6, 0.1);
    output(420, 430, "1DS12CS023", fonts[0]);
    output(420, 360, "1DS12CS045", fonts[0]);
    output(420, 290, "1DS12CS061", fonts[0]);

    glColor3f(0.1, 0.1, 0.1);
    output(370, 125, "Press any key to continue...", fonts[0]);
}

/*--------------------------------------------------------------------------------------*/
                                                                                      
void menu()
{
    glColor3f(0.8, 0.1, 0.2);
    output(350, 580, "DNA - Deoxyribonucleic Acid", fonts[2]);

    glColor3f(0.5, 0.6, 0.1);
    output(420, 450, "Menu", fonts[3]);

    glColor3f(1, 0.5, 0);
    output(420, 420, "1. DNA", fonts[0]);
    output(420, 390, "2. Adenine-Thymine", fonts[0]);
    output(420, 360, "3. Cytosine-Guanine", fonts[0]);
    output(420, 330, "ESC. Exit", fonts[0]);
}

/*--------------------------------------------------------------------------------------*/

void dna()
{
    float cx = 500, cy = 50, r=100;

    glLineWidth(5.0);

    glColor3f(0.0, 0.0, 0.75);
    drawHelixStrand(cx, cy, r, 0);
    glColor3f(0.75, 0.0, 0.0);
    drawHelixStrand(cx, cy, r, 138);
    glColor3f(0.75, 0.75, 0.0);
    drawHelixLine(cx, cy, r, 138);
    
    glTranslatef(cx, cy, 0);
    glRotatef(1, 0, 1, 0);
    glTranslatef(-cx, -cy, 0);
    
    glFlush();
    glutPostRedisplay();
}

/*--------------------------------------------------------------------------------------*/

void adenineThymine()
{
    //put adenineThymine page code here
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
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
  
    glutKeyboardFunc(NormalKey);
    createMouseMenu();

    glutMainLoop();
    return 0;
}