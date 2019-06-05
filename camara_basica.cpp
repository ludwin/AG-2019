#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdlib.h>
#include <math.h>

GLuint texture[0];
// variables que representan direccion de la camara
float lx=0.0f,lz=-1.0f;
// XZ posicion de la camara
float x=0.0f,z=5.0f;

// angulo de rotación
float angulo = 0.0f;

void piramide()
{
  glColor3f(1.0f, 1.0f, 1.0f);
  // Dibujamos el triangulo
  glTranslatef(0.0f ,0.75f, 0.0f);
  glRotatef (-90,10.0,0.1,0.0);
  glutSolidCone(1, 2, 20, 20);
  glPushMatrix();
  glPopMatrix();
  glColor3f(1.0f, 1.0f , 1.0f);
}

void camara(int w, int h)
{

// Evitar una división por cero, cuando la ventana es demasiado pequeña
// (No permitir una ventana de alto 0).
if (h == 0)
h = 1;
float proporcion = w * 1.0 / h;

// Usando Matrix proyección
glMatrixMode(GL_PROJECTION);

// Reseteando la Matrix
glLoadIdentity();

// configurar el viewport para una ventana completa
glViewport(0, 0, w, h);

// Configurando las perspectivas.
gluPerspective(45.0f, proporcion, 0.1f, 100.0f);

// Regresar la vista a Modelview
glMatrixMode(GL_MODELVIEW);
}

void escena(void)
{
  // Borrar Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Reseteando transformaciones
  glLoadIdentity();
  // Configurando camara
  gluLookAt(	x, 1.0f, z,
  x+lx, 1.0f, z+lz,
  0.0f, 1.0f, 0.0f);

  // Aplicando textura

  texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
   (
       "piso1.bmp",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
   );
 //glColor3f(0.9f, 0.9f, 0.9f);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 100.0f, 0.0f, 100.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
  glEnd();

// Dibujando piramides
  for(int i = -2; i < 2; i++)
    for(int j=-2; j < 2; j++) {
      glPushMatrix();
      glTranslatef(i*15.0,0,j * 15.0);
      piramide();
      glPopMatrix();
}

glutSwapBuffers();
}

void salir(unsigned char key, int x, int y)
{
  if (key == 27)
  exit(0);
}

void keyboard(int key, int xx, int yy)
{
  float fraccion = 0.1f;

  switch (key) {
    case GLUT_KEY_LEFT :
      angulo -= 0.01f;
      lx = sin(angulo);
      lz = -cos(angulo);
    break;
    case GLUT_KEY_RIGHT :
      angulo += 0.01f;
      lx = sin(angulo);
      lz = -cos(angulo);
    break;
      case GLUT_KEY_UP :
      x += lx * fraccion;
      z += lz * fraccion;
    break;
      case GLUT_KEY_DOWN :
      x -= lx * fraccion;
      z -= lz * fraccion;
    break;
    }
}

int main(int argc, char **argv)
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(500,500);
  glutCreateWindow("Manejo de camara");

  // register callbacks
  glutDisplayFunc(escena);
  glutReshapeFunc(camara);
  glutIdleFunc(escena);
  glutKeyboardFunc(salir);
  glutSpecialFunc(keyboard);

  // OpenGL init
  glEnable(GL_DEPTH_TEST);
  //Para texturas
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glutMainLoop();
  return 1;
}
