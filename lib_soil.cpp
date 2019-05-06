#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>


GLuint texture[0];

void resize(int h, int w) {
			glViewport(0, 0, w, h);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(30.0, (float)w / (float)h, 1.0, 80.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
}

static void display(void)
{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();
			glTranslatef(0.0f,0.0f,-5.0f);
			texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
									(
				"avion.jpg",
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
									);
			glBindTexture(GL_TEXTURE_2D, texture[0]);

			//GLfloat colorNiebla[4]={0.5,0.5,0.5,1.0};
			GLfloat colorNiebla[4]={0.4f, 0.7f, 1.0f, 0.2f};
			glFogi ( GL_FOG_MODE, GL_EXP2); // GL_LINEAR, GL_EXP, GL_EXP2
			glFogfv( GL_FOG_COLOR, colorNiebla );
			glFogf ( GL_FOG_DENSITY, 0.10f ); // No necesario para GL_LINEAR
			glHint ( GL_FOG_HINT, GL_FASTEST );
			glFogf ( GL_FOG_START, 0.0f );
			glFogf ( GL_FOG_END, 1.0f );
			glEnable(GL_FOG);


			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f( 1.0, -1.0, -1.0 );
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f( 1.0, 1.0, -1.0 );
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f( -0.5,  0.5, -1.0 );
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f( -1.0, -1.0, -1.0 );
			glEnd();
			glutSwapBuffers();
}

int main(int argc, char **argv)
{
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInit(&argc, argv);
		glutInitWindowSize(600, 600);
		glutCreateWindow("ejemplo1");
		glutReshapeFunc(resize);
		glutDisplayFunc(display);

		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glutMainLoop();
}
