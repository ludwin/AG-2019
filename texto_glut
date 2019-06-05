#include <string.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
int IdMain;
int IdSub;

static double tiempo = 0.0;
static double angulo = 0.0;
static char label[100];
void dibujarCadena (char *s)
{
 unsigned int i;
 for (i = 0; i < strlen (s); i++)
 glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
}
void pintarventana(void)
{
 glutSetWindow (IdMain);
 glClearColor(1.0F, 1.0F, 1.0F,1.0F);
 glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glLoadIdentity ();
 glPushMatrix ();
 glRotatef (angulo, 0.0, 0.0, 1.0);
 glBegin (GL_POLYGON);

 glColor3f (1.0F, 0.0F, 0.0F);
 glVertex2f(0.0F, 0.5F);
 glColor3f (0.0F, 1.0F, 0.0F);
 glVertex2f(0.5F,0.5F);
 glColor3f (0.0F, 0.0F, 1.0F);
 glVertex2f(0.5F,0.0F);
 glColor3f (1.0F, 0.0F, 0.0F);
 glVertex2f(0.0F,0.0F);
 glEnd ();
 glPopMatrix ();
 glutSwapBuffers ();
}
void pintarsubventana ()
{
 glutSetWindow (IdSub);
 glClearColor (1.0, 1.0, 1.0, 0.0);
 glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glColor3f (0.0F, 0.0F, 0.0F);
 glBegin (GL_LINE_LOOP);
 glVertex2f (0.0F, 0.0F);
 glVertex2f (0.0F, 0.99F);
 glVertex2f (0.999F, 0.99F);
 glVertex2f (0.999F, 0.0F);
 glEnd ();

 glColor3f (1.0F, 0.0F, 1.0F);
 sprintf (label, " Subventana ");
 glRasterPos2f (0.40F, 0.70F);
 dibujarCadena (label);
 sprintf (label, " de OpenGL creada con GLUT ");
 glRasterPos2f (0.33F, 0.35F);
 dibujarCadena (label);
 glutSwapBuffers ();
}
void tamanoventana (int w, int h) {
 glViewport (0, 0, w, h);
 glMatrixMode (GL_PROJECTION);
 glLoadIdentity ();
 gluOrtho2D (-1.0F, 1.0F,-1.0F, 1.0F);
 glMatrixMode (GL_MODELVIEW);
 glLoadIdentity ();
 glutSetWindow (IdSub);
 glutReshapeWindow (w -10, h / 10);
 glutPositionWindow (5, 5);
 glutSetWindow (IdMain);
}
void tamanosubventana (int w, int h) {
 glViewport (0, 0, w, h);
 glMatrixMode (GL_PROJECTION);
 glLoadIdentity ();
 gluOrtho2D (0.0F, 1.0F, 0.0F, 1.0F);
}
void teclado (unsigned char key, int x, int y) {
 static int info_banner = 1;
 switch (key)
 {
 case 'i':
 case 'I':
 if (info_banner) {
 glutSetWindow (IdSub);
 glutHideWindow ();
 }
 else
{
 glutSetWindow (IdSub);
 glutShowWindow ();
}
 info_banner = !info_banner;
 break;
 case 'q':
 case 'Q':
 exit (0);
 break;
 }
}
void idle (void)
{
 angulo += 5.0;
 tiempo += 0.1;
 glutSetWindow (IdMain);
 glutPostRedisplay ();
 glutSetWindow (IdSub);
 glutPostRedisplay ();
}
int main (int argc, char **argv)
{
 glutInit (&argc, argv);
 glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
 glutInitWindowPosition (20, 20);
 glutInitWindowSize (600, 600);
 IdMain = glutCreateWindow ("Ventana con Textos");
 glutDisplayFunc (pintarventana);
 glutReshapeFunc (tamanoventana);
 glutKeyboardFunc (teclado);
 glutIdleFunc (idle);
 IdSub = glutCreateSubWindow (IdMain, 20, 20, 600 - 10, 600 / 10);
 glutDisplayFunc (pintarsubventana);
 glutReshapeFunc (tamanosubventana);
 glutMainLoop ();
 return 0;
}
