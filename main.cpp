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
    glColor3ub(52, 73, 94);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void getHexagonPoints(float points[6][2], float x, float y, float side)
{
	points[0][0] = x;
	points[0][1] = y;
	points[1][0] = 0.866*side + x;
	points[1][1] = 0.5*side + y;
	points[2][0] = 0.866*side + x;
	points[2][1] = 1.5*side + y;
	points[3][0] = x;
	points[3][1] = 2.0*side + y;
	points[4][0] = -0.866*side + x;
	points[4][1] = 1.5*side + y;
	points[5][0] = -0.866*side + x;
	points[5][1] = 0.5*side + y;
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
	float hex1[6][2], hex2[6][2];
    //radius and color declarations
    GLubyte red[] = {15, 192, 57, 43};          //oxygen
    GLubyte green[] = {20, 39, 174, 96};        //carbon
    GLubyte blue[] = {20, 41, 128, 185};         //nitrogen
    GLubyte yellow[] = {10, 241, 196, 15};    //hydrogen
    getHexagonPoints(hex1, 125, 325, 75);
    getHexagonPoints(hex2, 525, 75, 75);
    
    //hexagon 1
    drawCircle(hex1[0][0], hex1[0][1], green);
    drawCircle(hex1[1][0], hex1[1][1], blue);
    drawCircle(hex1[2][0], hex1[2][1], green);
    drawCircle(hex1[3][0], hex1[3][1], green);
    drawCircle(hex1[4][0], hex1[4][1], green);
    drawCircle(hex1[5][0], hex1[5][1], blue);
    drawBondLine(hex1[0][0],hex1[0][1],hex1[1][0],hex1[1][1]);
    drawBondLine(hex1[1][0],hex1[1][1],hex1[2][0],hex1[2][1]);
    drawBondLine(hex1[2][0],hex1[2][1],hex1[3][0],hex1[3][1]);
    drawBondLine(hex1[3][0],hex1[3][1],hex1[4][0],hex1[4][1]);
    drawBondLine(hex1[4][0],hex1[4][1],hex1[5][0],hex1[5][1]);
    drawBondLine(hex1[5][0],hex1[5][1],hex1[0][0],hex1[0][1]);

    drawCircle(hex1[0][0], hex1[0][1]-50, red);
    drawBondLine(hex1[0][0],hex1[0][1],hex1[0][0],hex1[0][1]-50);

    drawCircle(hex1[1][0]+25, hex1[1][1]-25, yellow);
    drawBondLine(hex1[1][0],hex1[1][1],hex1[1][0]+25,hex1[1][1]-25);

    drawCircle(hex1[2][0]+40, hex1[2][1]+40, red);
    drawBondLine(hex1[2][0],hex1[2][1],hex1[2][0]+40,hex1[2][1]+40);
    
    drawCircle(hex1[3][0]-20, hex1[3][1]+70, yellow);
    drawCircle(hex1[3][0], hex1[3][1]+50, green);
    drawBondLine(hex1[3][0],hex1[3][1],hex1[3][0],hex1[3][1]+50);
    drawCircle(hex1[2][0]-20, hex1[2][1]+125, yellow);
    drawBondLine(hex1[3][0],hex1[3][1]+50,hex1[2][0]-20,hex1[2][1]+125);

	drawCircle(hex1[4][0]-25,hex1[4][1]+25, yellow);   
    drawBondLine(hex1[4][0],hex1[4][1],hex1[4][0]-25,hex1[4][1]+25);


    //hexagon 2
    drawCircle(hex2[0][0], hex2[0][1], blue);
    drawCircle(hex2[1][0], hex2[1][1], green);
    drawCircle(hex2[2][0], hex2[2][1], green);
    drawCircle(hex2[3][0], hex2[3][1], green);
    drawCircle(hex2[4][0], hex2[4][1], blue);
    drawCircle(hex2[5][0], hex2[5][1], green);
    drawBondLine(hex2[0][0],hex2[0][1],hex2[1][0],hex2[1][1]);
    drawBondLine(hex2[1][0],hex2[1][1],hex2[2][0],hex2[2][1]);
    drawBondLine(hex2[2][0],hex2[2][1],hex2[3][0],hex2[3][1]);
    drawBondLine(hex2[3][0],hex2[3][1],hex2[4][0],hex2[4][1]);
    drawBondLine(hex2[4][0],hex2[4][1],hex2[5][0],hex2[5][1]);
    drawBondLine(hex2[5][0],hex2[5][1],hex2[0][0],hex2[0][1]);

    drawCircle(hex2[1][0]+50, hex2[0][1]+25, blue);
    drawBondLine(hex2[1][0],hex2[1][1],hex2[1][0]+50,hex2[0][1]+25);
    drawCircle(hex2[2][0]+50, hex2[3][1]-25, blue);
    drawBondLine(hex2[2][0],hex2[2][1],hex2[2][0]+50,hex2[3][1]-25);
    drawCircle(hex2[2][0]+75,hex2[2][1]-37.5,green);
    drawBondLine(hex2[1][0]+50,hex2[0][1]+25,hex2[2][0]+75,hex2[2][1]-37.5); 
    drawBondLine(hex2[2][0]+50,hex2[3][1]-25,hex2[2][0]+75,hex2[2][1]-37.5);
    drawCircle(hex2[2][0]+125,hex2[2][1]-37.5,yellow);
    drawBondLine(hex2[2][0]+75,hex2[2][1]-37.5,hex2[2][0]+125,hex2[2][1]-37.5);

    drawCircle(hex2[3][0]-20, hex2[3][1]+70, yellow);
    drawCircle(hex2[3][0], hex2[3][1]+50, blue);
    drawBondLine(hex2[3][0],hex2[3][1],hex2[3][0],hex2[3][1]+50);
    drawCircle(hex2[2][0]-20, hex2[2][1]+125, yellow);
    drawBondLine(hex2[3][0],hex2[3][1]+50,hex2[2][0]-20,hex2[2][1]+125);
    
	drawCircle(hex2[5][0]-25,hex2[5][1]-25, yellow);   
    drawBondLine(hex2[5][0],hex2[5][1],hex2[5][0]-25,hex2[5][1]-25);

    //H-bonds
    drawBondLine(hex1[2][0]+40,hex1[2][1]+40,hex2[3][0]-20, hex2[3][1]+70);
    drawBondLine(hex1[1][0]+25,hex1[1][1]-25,hex2[4][0],hex2[4][1]);
}

/*--------------------------------------------------------------------------------------*/

void cytosineGuanine()
{
    float hex1[6][2], hex2[6][2];
    //radius and color declarations
    GLubyte red[] = {15, 192, 57, 43};          //oxygen
    GLubyte green[] = {20, 39, 174, 96};        //carbon
    GLubyte blue[] = {20, 41, 128, 185};         //nitrogen
    GLubyte yellow[] = {10, 241, 196, 15};    //hydrogen
    getHexagonPoints(hex1, 125, 325, 75);
    getHexagonPoints(hex2, 525, 75, 75);
    
    //hexagon 1
    drawCircle(hex1[0][0], hex1[0][1], green);
    drawCircle(hex1[1][0], hex1[1][1], blue);
    drawCircle(hex1[2][0], hex1[2][1], green);
    drawCircle(hex1[3][0], hex1[3][1], green);
    drawCircle(hex1[4][0], hex1[4][1], green);
    drawCircle(hex1[5][0], hex1[5][1], blue);
    drawBondLine(hex1[0][0],hex1[0][1],hex1[1][0],hex1[1][1]);
    drawBondLine(hex1[1][0],hex1[1][1],hex1[2][0],hex1[2][1]);
    drawBondLine(hex1[2][0],hex1[2][1],hex1[3][0],hex1[3][1]);
    drawBondLine(hex1[3][0],hex1[3][1],hex1[4][0],hex1[4][1]);
    drawBondLine(hex1[4][0],hex1[4][1],hex1[5][0],hex1[5][1]);
    drawBondLine(hex1[5][0],hex1[5][1],hex1[0][0],hex1[0][1]);

    drawCircle(hex1[0][0], hex1[0][1]-50, red);
    drawBondLine(hex1[0][0],hex1[0][1],hex1[0][0],hex1[0][1]-50);

    drawCircle(hex1[2][0]+40, hex1[2][1]+40, blue);
    drawBondLine(hex1[2][0],hex1[2][1],hex1[2][0]+40,hex1[2][1]+40);
    drawCircle(hex1[2][0]+40,hex1[2][1]+75, yellow);
    drawBondLine(hex1[2][0]+40,hex1[2][1]+40,hex1[2][0]+40,hex1[2][1]+75);
    drawCircle(hex1[2][0]+75,hex1[2][1]+20,yellow);
    drawBondLine(hex1[2][0]+40,hex1[2][1]+40,hex1[2][0]+75,hex1[2][1]+20);
    
    drawCircle(hex1[3][0], hex1[3][1]+50, yellow);
    drawBondLine(hex1[3][0],hex1[3][1],hex1[3][0],hex1[3][1]+50);

	drawCircle(hex1[4][0]-25,hex1[4][1]+25, yellow);   
    drawBondLine(hex1[4][0],hex1[4][1],hex1[4][0]-25,hex1[4][1]+25);


    //hexagon 2
    drawCircle(hex2[0][0], hex2[0][1], blue);
    drawCircle(hex2[1][0], hex2[1][1], green);
    drawCircle(hex2[2][0], hex2[2][1], green);
    drawCircle(hex2[3][0], hex2[3][1], green);
    drawCircle(hex2[4][0], hex2[4][1], blue);
    drawCircle(hex2[5][0], hex2[5][1], green);
    drawBondLine(hex2[0][0],hex2[0][1],hex2[1][0],hex2[1][1]);
    drawBondLine(hex2[1][0],hex2[1][1],hex2[2][0],hex2[2][1]);
    drawBondLine(hex2[2][0],hex2[2][1],hex2[3][0],hex2[3][1]);
    drawBondLine(hex2[3][0],hex2[3][1],hex2[4][0],hex2[4][1]);
    drawBondLine(hex2[4][0],hex2[4][1],hex2[5][0],hex2[5][1]);
    drawBondLine(hex2[5][0],hex2[5][1],hex2[0][0],hex2[0][1]);

    drawCircle(hex2[1][0]+50, hex2[0][1]+25, blue);
    drawBondLine(hex2[1][0],hex2[1][1],hex2[1][0]+50,hex2[0][1]+25);
    drawCircle(hex2[2][0]+50, hex2[3][1]-25, blue);
    drawBondLine(hex2[2][0],hex2[2][1],hex2[2][0]+50,hex2[3][1]-25);
    drawCircle(hex2[2][0]+75,hex2[2][1]-37.5,green);
    drawBondLine(hex2[1][0]+50,hex2[0][1]+25,hex2[2][0]+75,hex2[2][1]-37.5); 
    drawBondLine(hex2[2][0]+50,hex2[3][1]-25,hex2[2][0]+75,hex2[2][1]-37.5);
    drawCircle(hex2[2][0]+125,hex2[2][1]-37.5,yellow);
    drawBondLine(hex2[2][0]+75,hex2[2][1]-37.5,hex2[2][0]+125,hex2[2][1]-37.5);

    drawCircle(hex2[3][0], hex2[3][1]+50, red);
    drawBondLine(hex2[3][0],hex2[3][1],hex2[3][0],hex2[3][1]+50);

    drawCircle(hex2[4][0]-25, hex2[4][1]+25, yellow);
    drawBondLine(hex2[4][0],hex2[4][1],hex2[4][0]-25,hex2[4][1]+25);
	
	drawCircle(hex2[5][0]-50, hex2[0][1], blue);   
    drawBondLine(hex2[5][0],hex2[5][1],hex2[5][0]-50,hex2[0][1]);
    drawCircle(hex2[5][0]-50, hex2[0][1]-35, yellow);
    drawBondLine(hex2[5][0]-50,hex2[0][1],hex2[5][0]-50,hex2[0][1]-35);
    drawCircle(hex2[5][0]-85, hex2[0][1]+35, yellow);
    drawBondLine(hex2[5][0]-50,hex2[0][1],hex2[5][0]-85,hex2[0][1]+35);
    
    //H-bonds
    drawBondLine(hex1[0][0], hex1[0][1]-50, hex2[5][0]-85, hex2[0][1]+35);
    drawBondLine(hex1[1][0], hex1[1][1], hex2[4][0]-25, hex2[4][1]+25);
    drawBondLine(hex1[2][0]+75, hex1[2][1]+20, hex2[3][0], hex2[3][1]+50);
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
    glutKeyboardFunc(NormalKey);
    createMouseMenu();

    glutMainLoop();
    return 0;
}