#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define RUTA_AUDIO "imperial.wav" //nombre del archivo de audio
using namespace std;

int frameNumber;   // Numero de frames
float scale = 2;  // escala en  x, y, and z
float rotateX, rotateY;  // variables para rotación con teclas especiales

// funcion para cargar audio
void my_audio_callback(void *userdata, Uint8 *stream, int len);

// variables para audio
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play


void display() {
        // LLamada a función dibujo
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION); // Set up the projection.
        glLoadIdentity();
        glOrtho(-scale,scale,-scale,scale,-2*scale,2*scale);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();     // configuración de matrix de identidad.
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
        for (int i=3; i<=100; i++) {
                rotateY=rotateY-= i;
        }
        //Verificamos el numero de frames para detener animación
        if(frameNumber==1000)
        {
                pauseAnimation();
                //si se detiene la animacion detenemos el audio
                SDL_PauseAudio(1);
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
        if ( !animating ) {
                animating = 1;
                glutTimerFunc(30, timerFunction, 1);
        }
}



// ------------- Manejo de Teclado-----------------------------------------------

void key(unsigned char key, int x, int y) {
        // La animación inicia al presionar la tecla espaciadora de igual forma se detiene
        if ( key == ' ' && animating==1) {
                pauseAnimation();
                SDL_PauseAudio(1);
        }
        else
        {
                startAnimation();
                SDL_PauseAudio(0);
        }
        if (key == 27) {
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
        glutCreateWindow("OpenGL Audio");
        // sonido
        // Inicializar SDL.
        if (SDL_Init(SDL_INIT_AUDIO) < 0)
                return 1;

        // Variables locales
        static Uint32 wav_length; // Longitud de nuestra muestra
        static Uint8 *wav_buffer; // Buffer que contiene nuestro archivo de audio
        static SDL_AudioSpec wav_spec; // Las especificaciones de nuestra pieza de música

        /* Cargar el WAV */
        // Las especificaciones, la longitud y el búfer de nuestro wav se llenan
        if( SDL_LoadWAV(RUTA_AUDIO, &wav_spec, &wav_buffer, &wav_length) == NULL )
        {
                return 1;
        }
        // Establecer la función de devolución de llamada
        wav_spec.callback = my_audio_callback;
        wav_spec.userdata = NULL;

        // Establecer nuestras variables estáticas globales
        audio_pos = wav_buffer; // Copia el buffer de sonido
        audio_len = wav_length; // Copia la longitud del archivo

        /*Abrir el dispositivo de audio */
        if ( SDL_OpenAudio(&wav_spec, NULL) < 0 )
        {
                fprintf(stderr, "No se pudo abrir el audio: %s\n", SDL_GetError());
                exit(-1);
        }

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

        // Descomentar si queremos que la animación y el audio inicie al levantar el script
        //startAnimation();
        /* Empezar a sonar */
        //SDL_PauseAudio(0);
        glutMainLoop();
        return 0;


        //SDL_PauseAudio(0);
        while ( audio_len > 0 )
        {
                SDL_Delay(100); // espera un segundo para la pausa
        }
        SDL_CloseAudio();
        SDL_FreeWAV(wav_buffer);
}

//Función de devolución de llamada de audio donde se recoren los valores del bufer
void my_audio_callback(void *userdata, Uint8 *stream, int len)
{

        if (audio_len ==0)
                return;

        len = ( len > audio_len ? audio_len : len );

        SDL_memcpy (stream, audio_pos, len); // Simplemente copie desde un buffer en el otro
        //SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME / 2); // Mezclar de un buffer a otro

        audio_pos += len;
        audio_len -= len;
}
