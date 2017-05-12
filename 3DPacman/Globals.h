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
tree myDot(0);
tree myDonald(1);
tree myDonaldClose(1);
graphic2d screenPic(1);
vec3 donaldPosition1 = vec3(16.5, 0.0, 2.75);
//vec3 donaldPosition2 = vec3(16.5, 0.0, 2.75);
//vec3 donaldPosition3 = vec3(16.5, 0.0, 2.75);
//vec3 donaldPosition4 = vec3(16.5, 0.0, 2.75);
float donald1XSpeed = 0.2;
float donald2XSpeed = 0.5;
float donald3XSpeed = 0.5;
float donald4XSpeed = 0.5;
bool drawDonaldCloseFace = false;

string maze;

//Game Logic
int score = 0;

//Sound
sf::Sound sound;
sf::Sound sound2;
sf::Sound soundPacmanChomp;

//String Map of Maze
string row[61] = {
	"##########################NN##########################E",
	"#DDDDDDDDDDDDDDDDDDDDDDD.#NN#DDDDDDDDDDDDDDDDDDDDDDD.#E",
	"#D.........D...........D.#NN#D.........D...........D.#E",
	"#D.########D.##########D.#NN#D.########D.##########D.#E",
	"#D.#NNNNNN#D.#NNNNNNNN#D.#NN#D.#NNNNNN#D.#NNNNNNNN#D.#E",
	"#D.#NNNNNN#D.#NNNNNNNN#D.#NN#D.#NNNNNN#D.#NNNNNNNN#D.#E",
	"#D.#NNNNNN#D.#NNNNNNNN#D.#NN#D.#NNNNNN#D.#NNNNNNNN#D.#E",
	"#D.#NNNNNN#D.#NNNNNNNN#D.#NN#D.#NNNNNN#D.#NNNNNNNN#D.#E",
	"#D.########D.##########D.####D.########D.##########D.#E",
	"#DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD.#E",
	"#D.........D.....D.................D.....D.........D.#E",
	"#D.########D.####D.################D.####D.########D.#E",
	"#D.#NNNNNN#D.#NN#D.#..............#D.#NN#D.#NNNNNN#D.#E",
	"#D.#NNNNNN#D.#NN#D.#..............#D.#NN#D.#NNNNNN#D.#E",
	"#D.########D.#NN#D.################D.#NN#D.########D.#E",
	"#DDDDDDDDDDD.#NN#DDDDDDD.#NN#DDDDDDD.#NN#DDDDDDDDDDD.#E",
	"#..........D.#NN#......D.#NN#D.......#NN#D...........#E",
	"###########D.#NN#######D.#NN#D.#######NN#D.###########E",
	"NNNNNNNNNN#D.#NNNNNNNN#D.#NN#D.#NNNNNNNN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NNNNNNNN#D.#NN#D.#NNNNNNNN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.##########D.####D.##########D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#DDDDDDDDDDDDDDDDDDD.#NN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#D.................D.#NN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#D.#####......#####D.#NN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#D.#..............#D.#NN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#D.#..............#D.#NN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.####D.#..............#D.####D.#NNNNNNNNNNE",
	"NNNNNNNNNN#DDDDDDD.#..............#DDDDDDD.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.....D.#..............#D.....D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.####D.#..............#D.####D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#D.#..............#D.#NN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#D.#..............#D.#NN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#D.################D.#NN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#DDDDDDDDDDDDDDDDDDD.#NN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#D.................D.#NN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#D.################D.#NN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#D.#NNNNNNNNNNNNNN#D.#NN#D.#NNNNNNNNNNE",
	"NNNNNNNNNN#D.#NN#D.#NNNNNNNNNNNNNN#D.#NN#D.#NNNNNNNNNNE",
	"###########D.####D.#######NN#######D.####D.###########E",
	"#DDDDDDDDDDDDDDDDDDDDDDD.#NN#DDDDDDDDDDDDDDDDDDDDDDD.#E",
	"#D.........D...........D.#NN#D...........D.........D.#E",
	"#D.########D.##########D.#NN#D.##########D.########D.#E",
	"#D.#NNNNNN#D.#NNNNNNNN#D.#NN#D.#NNNNNNNN#D.#NNNNNN#D.#E",
	"#D.#NNNNNN#D.#NNNNNNNN#D.#NN#D.#NNNNNNNN#D.#NNNNNN#D.#E",
	"#D.#####NN#D.##########D.####D.##########D.#NN#####D.#E",
	"#DDDDD.#NN#DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD.#NN#DDDDD.#E",
	"#....D.#NN#D.....D.................D.....D.#NN#D.....#E",
	"#####D.#NN#D.####D.################D.####D.#NN#D.#####E",
	"NNNN#D.#NN#D.#NN#D.#NNNNNNNNNNNNNN#D.#NN#D.#NN#D.#NNNNE",
	"NNNN#D.#NN#D.#NN#D.#NNNNNNNNNNNNNN#D.#NN#D.#NN#D.#NNNNE",
	"#####D.####D.#NN#D.#######NN#######D.#NN#D.####D.#####E",
	"#DDDDDDDDDDD.#NN#DDDDDDD.#NN#DDDDDDD.#NN#DDDDDDDDDDD.#E",
	"#D...........#NN#......D.#NN#D.......#NN#..........D.#E",
	"#D.###########NN#######D.#NN#D.#######NN###########D.#E",
	"#D.#NNNNNNNNNNNNNNNNNN#D.#NN#D.#NNNNNNNNNNNNNNNNNN#D.#E",
	"#D.#NNNNNNNNNNNNNNNNNN#D.#NN#D.#NNNNNNNNNNNNNNNNNN#D.#E",
	"#D.####################D.####D.####################D.#E",
	"#DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD.#E",
	"#....................................................#E",
	"######################################################E" };


void CreateStringMaze(string row[])
{
	for (int i = 0; i < 60; i++)
	{
		maze = maze + row[i];
	}
}

#endif