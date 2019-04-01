#include <GL/gl.h>
#include <GL/glut.h>

void init(void)
{
    glEnable(GL_LIGHTING); //activa la fuente de luz 
    glEnable(GL_LIGHT0); //Activamos las luces en 0
    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TES
  	// Queremos que se dibujen las caras frontales
  	// y con un color solido de relleno.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void reshape(int w, int h)
{
    glViewport(0, 0,  (GLsizei) w, (GLsizei) h);
  // Activamos la matriz de proyeccion.
    glMatrixMode(GL_PROJECTION);
  // "limpiamos" esta con la matriz identidad.
    glLoadIdentity();
  // Usamos proyeccion ortogonal
    glOrtho(-300, 300, -300, 300, -300, 300);
  // Activamos la matriz de modelado/visionado.
    glMatrixMode(GL_MODELVIEW);
  // "Limpiamos" la matriz
    glLoadIdentity();
}

void display(void)
{
// Propiedades del material

    GLfloat mat_ambient[] = { 0.329412f, 0.223529f, 0.027451f};
    GLfloat mat_diffuse[] = { 0.780392f, 0.568627f, 0.113725f};
    GLfloat mat_specular[] = { 0.992157f, 0.941176f, 0.807843f};
    GLfloat shine[] = {27.8974f};


// "Limpiamos" el frame buffer con el color de "Clear", en este
// caso negro.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW_MATRIX );
    glLoadIdentity();

// Rotacion de 25 grados en torno al eje x
    glRotated(25.0, 1.0, 0.0, 0.0);
// Rotacion de -30 grados en torno al eje y
    glRotated(-30.0, 0.0, 1.0, 0.0);
// Dibujamos una "Tetera" y le aplico el material
    glPushMatrix();
//setMaterial
    glutSolidTeapot(125.0);
    glFlush();
}


int main(int argc, char **argv)
{
// Inicializo OpenGL
    glutInit(&argc, argv);
// Activamos buffer simple y colores del tipo RGB
    glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH);
// Definimos una ventana de medidas 800 x 600 como ventana
// de visualizacion en pixels
    glutInitWindowSize (800, 600);
// Posicionamos la ventana en la esquina superior izquierda de
// la pantalla.
    glutInitWindowPosition (0, 0);
// Creamos literalmente la ventana y le adjudicamos el nombre que se
// observara en su barra de titulo.
    glutCreateWindow ("Tetera");
// Inicializamos el sistema
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
