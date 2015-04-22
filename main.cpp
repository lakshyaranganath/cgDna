#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    output(420, 450, "MENU", fonts[3]);

//    glColor3f(0.6, 0.3, 0.7);
    glColor3f(1, 0.5, 0);
    output(420, 420, "1. DNA", fonts[0]);
    output(420, 390, "2. ADENINE", fonts[0]);
    output(420, 360, "3. THYMINE", fonts[0]);
    output(420, 330, "4. CYTOSINE", fonts[0]);
    output(420, 300, "5. GUANINE", fonts[0]);
    output(420, 270, "ESC. EXIT", fonts[0]);
}

/*--------------------------------------------------------------------------------------*/

void dna()
{
    //put dna page code here
}

/*--------------------------------------------------------------------------------------*/

void adenine()
{
    //put adenine page code here
}

/*--------------------------------------------------------------------------------------*/

void thymine()
{
    //put thymine page code here
}

/*--------------------------------------------------------------------------------------*/

void cytosine()
{
    //put cytosine page code here
}

/*--------------------------------------------------------------------------------------*/

void guanine()
{
    //put guanine page code here
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
    glClearColor(0.8, 0.8, 0.8, 0.8);
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    switch(page)
    {
        case -1: intro();       break;
        case  0: menu();        break;
        case  1: dna();         break;
        case  2: adenine();     break;
        case  3: thymine();     break;
        case  4: cytosine();    break;
        case  5: guanine();     break;
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
            case '2': page=2;	break; //goto adenine
            case '3': page=3;	break; //goto thymine
            case '4': page=4;	break; //goto cytosine
            case '5': page=5;	break; //goto guanine
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

static void SpecialKeyFunc( int Key, int x, int y )
{
    //    switch ( Key ) {
    //        case GLUT_KEY_LEFT:
    //            page=-1;
    //            glutPostRedisplay();
    //            break;
    //        case GLUT_KEY_RIGHT:
    //            page=0;
    //            glutPostRedisplay();
    //            break;
    //    }
}

/*--------------------------------------------------------------------------------------*/

void mouseMenuTrigger(int id)
{
    switch(id)
    {
        case 1: page=1;     break; //goto dna
        case 2: page=2;     break; //goto adenine
        case 3: page=3;     break; //goto thymine
        case 4: page=4;     break; //goto cytosine
        case 5: page=5;     break; //goto guanine
        case 6: exit(0);    //exit application
    }
    glutPostRedisplay();
}

void createMouseMenu()
{
    glutCreateMenu(mouseMenuTrigger);
    glutAddMenuEntry("DNA", 1);
    glutAddMenuEntry("ADENINE", 2);
    glutAddMenuEntry("THYMINE", 3);
    glutAddMenuEntry("CYTOSINE", 4);
    glutAddMenuEntry("GUANINE", 5);
    glutAddMenuEntry("EXIT", 6);
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
  
    glutKeyboardFunc(NormalKey);
    //glutSpecialFunc(SpecialKeyFunc);
    createMouseMenu();

    glutMainLoop();
    return 0;
}