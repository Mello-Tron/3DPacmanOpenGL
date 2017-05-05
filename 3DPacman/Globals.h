#ifndef GLOBALS_H
#define GLOBALS_H

#include<SFML/Audio.hpp>

GLfloat  zoom = 1.0;         // Translation factor
vec4 view(6.5, 0.0, 2.75, 0.0);

GLfloat  fovy = 60.0;		 // Field-of-view in Y direction angle (in degrees)
GLfloat  aspect = 1.0;       // Viewport aspect ratio
GLfloat  zNear = 0.01, zFar = 1000.0;

GLfloat dir = 1.0;
GLfloat theta[] = { 0.0,0.0,0.0 };
GLint axis = 1;

// The global SkyBox Object
SkyBox go_skybox;
GLfloat skyboxAngle = 0.0;

// The Camera
point4  eye(6.5, 0.0, 2.75, 0.0);
point4  at(6.5, 0.0, 2.75, 1.0);
vec4    up(0.0, 1.0, 0.0, 0.0);
point4  ns_eye(6.5, 0.0, 4.75, 1.0);
point4  ns_at(6.5, 0.0, 3.75, 1.0);
vec4	ns_view(6.5, 0.0, 1.75, 0.0);
GLfloat a = 0.003125; // acceleration
GLfloat v = 0.0; // velocity
bool goForward = false;
bool goReverse = false;
bool strafeLeft = false;
bool strafeRight = false;
float cameraSpeed = 0.011;

//Maze Objects
Brick wall(1);
Brick ground(0);
tree myTree(0);
tree myDonald(1);
tree myDonaldClose(1);
graphic2d screenPic(1);
vec3 donaldPosition = vec3(16.5, 0.0, 2.75);
float donaldXSpeed = 0.5;
vec3 donaldPosition2 = vec3(26.5, 0.0, 2.75);
bool drawDonaldCloseFace = false;

string maze;

//Sound
sf::Sound sound;
sf::Sound sound2;

//String Map of Maze
string row[61] = {
	"##########################NN##########################E",
	"#........................#NN#........................#E",
	"#........................#NN#........................#E",
	"#..########..##########..#NN#..########..##########..#E",
	"#..#NNNNNN#..#NNNNNNNN#..#NN#..#NNNNNN#..#NNNNNNNN#..#E",
	"#..#NNNNNN#..#NNNNNNNN#..#NN#..#NNNNNN#..#NNNNNNNN#..#E",
	"#..#NNNNNN#..#NNNNNNNN#..#NN#..#NNNNNN#..#NNNNNNNN#..#E",
	"#..#NNNNNN#..#NNNNNNNN#..#NN#..#NNNNNN#..#NNNNNNNN#..#E",
	"#..########..##########..####..########..##########..#E",
	"#....................................................#E",
	"#....................................................#E",
	"#..########..####..################..####..########..#E",
	"#..#NNNNNN#..#NN#..#..............#..#NN#..#NNNNNN#..#E",
	"#..#NNNNNN#..#NN#..#..............#..#NN#..#NNNNNN#..#E",
	"#..########..#NN#..################..#NN#..########..#E",
	"#............#NN#........#NN#........#NN#............#E",
	"#............#NN#........#NN#........#NN#............#E",
	"###########..#NN#######..#NN#..#######NN#..###########E",
	"NNNNNNNNNN#..#NNNNNNNN#..#NN#..#NNNNNNNN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NNNNNNNN#..#NN#..#NNNNNNNN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..##########..####..##########..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#....................#NN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#....................#NN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#..#####......#####..#NN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#..#..............#..#NN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#..#..............#..#NN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..####..#..............#..####..#NNNNNNNNNNE",
	"NNNNNNNNNN#........#..............#........#NNNNNNNNNNE",
	"NNNNNNNNNN#........#..............#........#NNNNNNNNNNE",
	"NNNNNNNNNN#..####..#..............#..####..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#..#..............#..#NN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#..#..............#..#NN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#..################..#NN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#....................#NN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#....................#NN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#..################..#NN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#..#NNNNNNNNNNNNNN#..#NN#..#NNNNNNNNNNE",
	"NNNNNNNNNN#..#NN#..#NNNNNNNNNNNNNN#..#NN#..#NNNNNNNNNNE",
	"###########..####..#######NN#######..####..###########E",
	"#........................#NN#........................#E",
	"#........................#NN#........................#E",
	"#..########..##########..#NN#..##########..########..#E",
	"#..#NNNNNN#..#NNNNNNNN#..#NN#..#NNNNNNNN#..#NNNNNN#..#E",
	"#..#NNNNNN#..#NNNNNNNN#..#NN#..#NNNNNNNN#..#NNNNNN#..#E",
	"#..#####NN#..##########..####..##########..#NN#####..#E",
	"#......#NN#................................#NN#......#E",
	"#......#NN#................................#NN#......#E",
	"#####..#NN#..####..################..####..#NN#..#####E",
	"NNNN#..#NN#..#NN#..#NNNNNNNNNNNNNN#..#NN#..#NN#..#NNNNE",
	"NNNN#..#NN#..#NN#..#NNNNNNNNNNNNNN#..#NN#..#NN#..#NNNNE",
	"#####..####..#NN#..#######NN#######..#NN#..####..#####E",
	"#............#NN#........#NN#........#NN#............#E",
	"#............#NN#........#NN#........#NN#............#E",
	"#..###########NN#######..#NN#..#######NN###########..#E",
	"#..#NNNNNNNNNNNNNNNNNN#..#NN#..#NNNNNNNNNNNNNNNNNN#..#E",
	"#..#NNNNNNNNNNNNNNNNNN#..#NN#..#NNNNNNNNNNNNNNNNNN#..#E",
	"#..####################..####..####################..#E",
	"#....................................................#E",
	"#....................................................#E",
	"######################################################E" };


void CreateStringMaze(string row[])
{
	for (int i = 0; i < 61; i++)
	{
		maze = maze + row[i];
	}
}

#endif