#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "Angel.h";
#include <GL/glew.h> // for OpenGL extensions
#include <GL/glut.h> // for Glut utility kit
#include "texture.h" // for the bitmap texture loader

// Global Projection Matrices
mat4 projection, modelview, translate;

//Kent Header Files
#include "GraphicsObject.h"
#include "SkyBox.h"
#include "Brick.h"
#include "tree.h"
#include "Zebra.h"
#include "Graphic2d.h"

//Custom Header Files
#include "Globals.h"
#include "Maze.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Camera.h"
#include "Setup.h"
#include "Shutdown.h"
#include "Dot.h"
#include "Display.h"

//Audio
#include <SFML/Audio.hpp>

int main(int argc, char **argv)
{
	atexit(OnShutdown);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow( "Pacman3D" );

	checkGlew();
    init();
    glutReshapeFunc(myReshape);
	CreateStringMaze(row);
	glutDisplayFunc(display);
	glutSpecialFunc(arrowKey);
	
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMove);
	glutSetCursor(GLUT_CURSOR_NONE);

    glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyRelease);

	glutFullScreen();

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("pacman_beginning.wav"))
		return -1;
	sound.setBuffer(buffer);

	sf::SoundBuffer buffer2;
	if (!buffer2.loadFromFile("pacman_eatghost.wav"))
		return -1;
	sound2.setBuffer(buffer2);

	sf::SoundBuffer buffer3;
	if (!buffer3.loadFromFile("pacman_chomp.wav"))
		return -1;
	soundPacmanChomp.setBuffer(buffer3);

	sound.play();

	//populateDots
	populateDots(maze);

    glutMainLoop();

    return 0;
}
