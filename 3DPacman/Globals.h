#ifndef GLOBALS_H
#define GLOBALS_H

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
tree myDonald(2);
tree myDonaldClose(1);
graphic2d screenPic(1);
vec3 donaldPosition = vec3(56.0, 0.2, 3.0);
vec3 donaldPosition2 = vec3(21.0, 0.2, 25.0);
bool drawDonaldCloseFace = false;

//String Map of Maze
string row0 = "####################################################E";
string row1 = "#........................##........................#E";
string row2 = "#........................##........................#E";
string row3 = "#..########..##########..##..########..##########..#E";
string row4 = "#..#NNNNNN#..#NNNNNNNN#..##..#NNNNNN#..#NNNNNNNN#..#E";
string row5 = "#..#NNNNNN#..#NNNNNNNN#..##..#NNNNNN#..#NNNNNNNN#..#E";
string row6 = "#..#NNNNNN#..#NNNNNNNN#..##..#NNNNNN#..#NNNNNNNN#..#E";
string row7 = "#..#NNNNNN#..#NNNNNNNN#..##..#NNNNNN#..#NNNNNNNN#..#E";
string row8 = "#..########..##########..##..########..##########..#E";
string row9 = "#..................................................#E";
string row10 = "#..................................................#E";
string row11 = "#..########..####..##############..####..########..#E";
string row12 = "#..#NNNNNN#..#NN#..#............#..#NN#..#NNNNNN#..#E";
string row13 = "#..#NNNNNN#..#NN#..#............#..#NN#..#NNNNNN#..#E";
string row14 = "#..########..#NN#..##############..#NN#..########..#E";
string row15 = "#............#NN#........##........#NN#............#E";
string row16 = "#............#NN#........##........#NN#............#E";
string row17 = "###########..#NN#######..##..#######NN#..###########E";
string row18 = "#NNNNNNNNN#..#NNNNNNNN#..##..#NNNNNNNN#..#NNNNNNNNN#E";
string row19 = "#NNNNNNNNN#..#NNNNNNNN#..##..#NNNNNNNN#..#NNNNNNNNN#E";
string row20 = "#NNNNNNNNN#..##########..##..##########..#NNNNNNNNN#E";

string maze = row0 + row1 + row2 + row3 + row4 + row5 + row6 + row7 + row8 + row9 + row10 + row11 + row12
+ row13 + row14 + row15 + row16 + row17 + row18 + row19 + row20;
//string maze = "#..#";

#endif