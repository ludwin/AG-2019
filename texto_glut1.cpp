#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdio>

float xrot = 0.00, yrot = 0.00, zoom = -30;

void text()
{
    char text[32];
    sprintf(text, "X:%.0f Y:%.0f", xrot, yrot);
    glColor3f(0, 0, 0);
    glRasterPos3f( -30 , 15 , zoom);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0, 0, zoom);

    // Escribir el texto despues de la transformación
    text();

    glRotatef(xrot, 1, 0, 0);
    glRotatef(yrot, 0, 1, 0);

    // color de la figura
    glColor3f(0.0, 0.5, 0.9);
    glutSolidCone(8,8,10,10);

    glFlush();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor( 1, 1, 1, 1);
    glClearDepth( 1.0 );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_LIGHT0);
}

void reshape(int w, int h)
{
    float aspectRatio = (float)w/(float)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspectRatio, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {

    case 27:
        exit(0);
    }
    glutPostRedisplay();
}

// Función para controlar teclas especiales
void specialKeys( int key, int x, int y )
{

    //  Flecha derecha: aumentar rotación 7 grados
    if (key == GLUT_KEY_RIGHT)
         yrot -= 1.0;

    //  Flecha izquierda: rotación en eje Y negativo 7 grados
    else if (key == GLUT_KEY_LEFT)
        yrot += 1.0;
    //  Flecha arriba: rotación en eje X positivo 7 grados
    else if (key == GLUT_KEY_UP)
         xrot += 1.0;
    //  Flecha abajo: rotación en eje X negativo 7 grados
    else if (key == GLUT_KEY_DOWN)
         xrot -= 1.0;

    //  Tecla especial F2 : rotación en eje Z positivo 7 grados

    //  Solicitar actualización de visualización
    glutPostRedisplay();

}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(400, 300);
    glutCreateWindow("Bitmap Ejemplo de texto");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
