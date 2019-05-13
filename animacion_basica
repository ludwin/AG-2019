#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

using namespace std;

int frameNumber;   // Numero de frames 

float scale = 2;  // escala en  x, y, and z

float rotateX, rotateY;  // variables para rotación con teclas especiales 

void display() {
       // LLamada a función dibujo 

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);  // Set up the projection.
    glLoadIdentity();
    glOrtho(-scale,scale,-scale,scale,-2*scale,2*scale);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();             // configuración de matrix de identidad. 
    glRotatef(rotateY,0,1,0);
    glRotatef(rotateX,1,0,0);

    // Agregar Codigo acá, para dibujar
    glColor3f(1.0,0.0,0.0);
    glutWireTeapot(1.0);
    glFlush ();
    glutSwapBuffers();    
}


// --------------- Para animación  ------------------------------------------

int animating = 0;      // 0 sin animación 
                        // Se cambia con la llamada a las funciones startAnimation() and pauseAnimation()

void pauseAnimation() {
       // Llamamo a la función para detener la animación 
    animating = 0;
}

void updateFrame() {
   // En esta funcion agregamos el codigo que hara la secuencia de cada escena como si fuera un fotograma 
  
	glColor3f(0.0,1.0,0.0);
	//Hacemos que la tetera gire 
	for (int i=3; i<=100; i++){
		rotateY=rotateY-= i;
	}
   //Verificamos el numero de frames para detener animación 
   if(frameNumber==200)
		{
			pauseAnimation();
			frameNumber=0;
		}
  //Almacenamos el numero de frames 
  frameNumber++;
  printf ("Numero de Frame: %d \n", frameNumber);
}

void timerFunction(int timerID) {
      // Invocamos la funcion para controlar el tiempo de la ejecucion de funciones 
    if (animating) {
        updateFrame();
        glutTimerFunc(30, timerFunction, 0);
        glutPostRedisplay();
    }
}

void startAnimation() {
      // llamamos la función para iniciar la animación 
   if ( ! animating ) {
       animating = 1;
       glutTimerFunc(30, timerFunction, 1);
   }
}



// ------------- Manejo de Teclado-----------------------------------------------

void key(unsigned char key, int x, int y) {
        // La animación inicia al presionar la tecla espaciadora de igual forma se detiene
    if ( key == ' ' ) {
		if ( animating )
		   pauseAnimation();
	
		else
		   startAnimation();
	}
	if (key == 27){
		exit(0);
	}
}

void special(int key, int x, int y) {
		   // control de teclas especiales 
    if ( key == GLUT_KEY_LEFT )
       rotateY -= 15;
    else if ( key == GLUT_KEY_RIGHT )
       rotateY += 15;
    else if ( key == GLUT_KEY_DOWN)
       rotateX += 15;
    else if ( key == GLUT_KEY_UP )
       rotateX -= 15;
    else if ( key == GLUT_KEY_HOME )
       rotateX = rotateY = 0;
    glutPostRedisplay();
}

// ----------------------  Funcion principal ------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL Tetera");
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(special);
    glEnable(GL_DEPTH_TEST);

    frameNumber = 0;
    rotateX = rotateY = 0;
    
    // Activar iluminación 
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    
    // Descomentar si queremos que la animación inicie al levantar el script
    startAnimation();

    glutMainLoop();
    return 0;
}
