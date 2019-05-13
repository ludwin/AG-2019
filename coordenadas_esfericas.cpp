//Librerias necesarias para el funcionamiento de OpenGL

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

//Inicializamos variables

float escala=0.25;
int X=700,Y=550;

//Textura
GLuint texture[5];

//planeta y esferas
int planet=1;
int mundo=2;

//luz
GLfloat light_Ambient [4] = { 0.1, 0.1, 0.1, 0.1};
GLfloat light_Diffuse [4] = { 0.4, 0.4, 0.4, 0.4};
GLfloat light_Position [4] = {-20.0, 5.0, 40.0, 5.0};

//materailes
GLfloat MaterialVerde[4] = {0.0, 0.6, 0.0, 0.0 };
GLfloat MaterialRojo [4] = {0.7, 0.0, 0.0, 0.0 };
GLfloat MaterialAzul [4] = {0.0, 0.0, 1.2, 0.0 };
GLfloat MaterialAmarillo[4] = {1.0, 0.65, 0.0 };
GLfloat MaterialBlanco[3]={1,1,1};


//Llamar a la funcion de materiales

void material(GLfloat a,GLfloat b,GLfloat c, GLfloat d, GLfloat e,GLfloat f,GLfloat g,GLfloat h,GLfloat i, GLfloat j)

{
        GLfloat mat_ambient[]    = {a,b,c};
        GLfloat mat_diffuse[]    = {d,e,f};
        GLfloat mat_specular[]   = {g,h,i};
        GLfloat high_shininess[] = { j};
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse );
        glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

}


//Planeta
void planeta()

{
        glNewList(planet,GL_COMPILE);
        glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //textura
        glShadeModel(GL_SMOOTH); //Bordes

        texture[1] = SOIL_load_OGL_texture //Llamamos a la imagen
                     (
                "planisferio.jpg",
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                     );
        glEnable(GL_TEXTURE_2D);

        //usamos la autogeneración de coordenadas
        GLfloat plano_s[4] = {0.5, 0, 0, 0}; // X
        GLfloat plano_t[4] = {0, 2, 0, 0}; // Y
        glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGenfv (GL_S, GL_OBJECT_PLANE, plano_s);
        glEnable (GL_TEXTURE_GEN_S);
        glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGenfv (GL_T, GL_OBJECT_PLANE, plano_t);

        glEnable(GL_TEXTURE_2D);
        glEnable (GL_TEXTURE_GEN_T);

        glutSolidSphere(4.5f,45.0,45.0);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_TEXTURE_GEN_T);


        glPopMatrix();
        glFlush();
        glEndList();
        glutSwapBuffers();


}

//funcion de las esferas llamadas planetas
void planetas()

{
        glNewList(mundo,GL_COMPILE);
        glPushMatrix();
        glShadeModel(GL_SMOOTH); //bordes
        glutSolidSphere(2.5f,70,70);
        glPopMatrix();
        glEndList();
        glutSwapBuffers();
}
void blanco()
{
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MaterialBlanco);

        glutSwapBuffers();
}

//funcion que dibuja la escena
void Scene()

{
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        //Camara
        glLoadIdentity( );
        glTranslatef(0.0f,0.0f,-5.0f);
        glPushMatrix();
        glScalef(escala,escala,escala);

        glPushMatrix();
        glTranslatef(0,0,5);
        glRotatef(5,1.8f,0.0f,0.0f);
        glRotatef(5,0.0f,1.0f,0.0f);
        glCallList(planet);
        glPopMatrix();
        glPushMatrix();

        //Mundo Verde
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MaterialVerde );

        glPopMatrix();
        glPushMatrix();
        glTranslatef(5.0f, 4.0f, 0.0f);
        glCallList(mundo);
        glPopMatrix();
        glPushMatrix();

        //Mundo azul

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MaterialAzul);
        glTranslatef(-1.5f, 5.0f, 0.0f);
        glCallList(mundo);

        //Mundo rojo
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MaterialRojo );
        glTranslatef(9.5,-6.5,0.0f);

        glCallList(mundo);
        glPopMatrix();

        //mundo amarillo
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MaterialAmarillo);
        glTranslatef(-1,-6.5,0.0f);
        glCallList(mundo);
        glPopMatrix();
        blanco ();
        glutSwapBuffers();
}

//Luz

//funcion para la luz

void luz(void)

{

        glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ambient );
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Diffuse );
        glLightfv(GL_LIGHT0, GL_POSITION, light_Position );

}

int main(int a, char *b[])

{
        glutInit(&a,b);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(900,650);
        glutInitWindowPosition(250,250);
        glutCreateWindow("Sistema Solar");
        glutDisplayFunc(Scene);
        glViewport( 0, 0, X, Y );
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity( );
        glFrustum(-(float)X/Y, (float)X/Y, -1.1, 1.0, 1.8, 6000.0);

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity( );
        glEnable(GL_DEPTH_TEST);  //Test de profundidad
        glEnable(GL_LIGHTING); //Habilitar luz
        glEnable(GL_LIGHT0); //Luz iniciada en 0
        glEnable(GL_TEXTURE_2D);
        luz();
        planeta();
        planetas();
        glutMainLoop();
        return 0;
}
