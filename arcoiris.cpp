#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



GLuint texture[0];

void resize(int h, int w) {
  glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-5.0f);

    unsigned char ArcoIris[8][3] = {
		{ 0x3f, 0x00, 0x3f }, // Violeta oscuro
		{ 0x7f, 0x00, 0x7f }, // Violeta
		{ 0xbf, 0x00, 0xbf }, // Malva
		{ 0x00, 0x00, 0xff }, // Azul
		{ 0x00, 0xff, 0x00 }, // Verde
		{ 0xff, 0xff, 0x00 }, // Amarillo
		{ 0xff, 0x7f, 0x00 }, // Naranja
		{ 0xff, 0x00, 0x00 } // Rojo
	};

	    // Indicamos el tipo de filtrado
		glEnable(GL_TEXTURE_1D);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// Creamos la textura
		glTexImage1D(GL_TEXTURE_1D,0,3,8,0,GL_RGB,GL_UNSIGNED_BYTE,ArcoIris);
		// Indicamos el modo de mapeo
		//(volcar el valor de los texels directamente sobre los pixels)
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

		glBegin(GL_QUADS);
		glTexCoord1f (0.0);
		glVertex3f (0, 0, 0);
		glTexCoord1f (1.0);
		glVertex3f (0.8, 0, 0);
		//glTexCoord1f (0.5);
		glVertex3f (0.8, 0.8, 0);
		glTexCoord1f (0.0);
		glVertex3f (0, 0.8, 0);
		glEnd();
		glutSwapBuffers();


}

int main(int argc, char **argv)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("ejmplo1");
    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    //Agregado para texturas
    glEnable (GL_TEXTURE_1D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glutMainLoop();
}
