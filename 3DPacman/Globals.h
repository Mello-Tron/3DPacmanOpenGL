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

string maze;

//String Map of Maze
string row[61][55] = {
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
"######################################################E"};


//String Map of Maze
string row0 = "##########################NN##########################E";
string row1 = "#........................#NN#........................#E";
string row2 = "#........................#NN#........................#E";
string row3 = "#..########..##########..#NN#..########..##########..#E";
string row4 = "#..#NNNNNN#..#NNNNNNNN#..#NN#..#NNNNNN#..#NNNNNNNN#..#E";
string row5 = "#..#NNNNNN#..#NNNNNNNN#..#NN#..#NNNNNN#..#NNNNNNNN#..#E";
string row6 = "#..#NNNNNN#..#NNNNNNNN#..#NN#..#NNNNNN#..#NNNNNNNN#..#E";
string row7 = "#..#NNNNNN#..#NNNNNNNN#..#NN#..#NNNNNN#..#NNNNNNNN#..#E";
string row8 = "#..########..##########..####..########..##########..#E";
string row9 = "#....................................................#E";
string row10 = "#....................................................#E";
string row11 = "#..########..####..################..####..########..#E";
string row12 = "#..#NNNNNN#..#NN#..#..............#..#NN#..#NNNNNN#..#E";
string row13 = "#..#NNNNNN#..#NN#..#..............#..#NN#..#NNNNNN#..#E";
string row14 = "#..########..#NN#..################..#NN#..########..#E";
string row15 = "#............#NN#........#NN#........#NN#............#E";
string row16 = "#............#NN#........#NN#........#NN#............#E";
string row17 = "###########..#NN#######..#NN#..#######NN#..###########E";
string row18 = "NNNNNNNNNN#..#NNNNNNNN#..#NN#..#NNNNNNNN#..#NNNNNNNNNNE";
string row19 = "NNNNNNNNNN#..#NNNNNNNN#..#NN#..#NNNNNNNN#..#NNNNNNNNNN#E";
string row20 = "NNNNNNNNNN#..##########..####..##########..#NNNNNNNNNNE";
string row21 = "NNNNNNNNNN#..#NN#....................#NN#..#NNNNNNNNNNE";
string row22 = "NNNNNNNNNN#..#NN#....................#NN#..#NNNNNNNNNNE";
string row23 = "NNNNNNNNNN#..#NN#..#####......#####..#NN#..#NNNNNNNNNNE";
string row25 = "NNNNNNNNNN#..#NN#..#..............#..#NN#..#NNNNNNNNNNE";
string row26 = "NNNNNNNNNN#..#NN#..#..............#..#NN#..#NNNNNNNNNNE";
string row27 = "NNNNNNNNNN#..####..#..............#..####..#NNNNNNNNNNE";
string row28 = "NNNNNNNNNN#........#..............#........#NNNNNNNNNNE";
string row29 = "NNNNNNNNNN#........#..............#........#NNNNNNNNNNE";
string row30 = "NNNNNNNNNN#..####..#..............#..####..#NNNNNNNNNNE";
string row31 = "NNNNNNNNNN#..#NN#..#..............#..#NN#..#NNNNNNNNNNE";
string row32 = "NNNNNNNNNN#..#NN#..#..............#..#NN#..#NNNNNNNNNNE";
string row33 = "NNNNNNNNNN#..#NN#..################..#NN#..#NNNNNNNNNNE";
string row34 = "NNNNNNNNNN#..#NN#....................#NN#..#NNNNNNNNNNE";
string row35 = "NNNNNNNNNN#..#NN#....................#NN#..#NNNNNNNNNNE";
string row36 = "NNNNNNNNNN#..#NN#..################..#NN#..#NNNNNNNNNNE";
string row37 = "NNNNNNNNNN#..#NN#..#NNNNNNNNNNNNNN#..#NN#..#NNNNNNNNNNE";
string row38 = "NNNNNNNNNN#..#NN#..#NNNNNNNNNNNNNN#..#NN#..#NNNNNNNNNNE";
string row39 = "###########..####..#######NN#######..####..###########E";
string row40 = "#........................#NN#........................#E";
string row41 = "#........................#NN#........................#E";
string row42 = "#..########..##########..#NN#..##########..########..#E";
string row43 = "#..#NNNNNN#..#NNNNNNNN#..#NN#..#NNNNNNNN#..#NNNNNN#..#E";
string row44 = "#..#NNNNNN#..#NNNNNNNN#..#NN#..#NNNNNNNN#..#NNNNNN#..#E";
string row45 = "#..#####NN#..##########..####..##########..#NN#####..#E";
string row46 = "#......#NN#................................#NN#......#E";
string row47 = "#......#NN#................................#NN#......#E";
string row48 = "#####..#NN#..####..################..####..#NN#..#####E";
string row49 = "NNNN#..#NN#..#NN#..#NNNNNNNNNNNNNN#..#NN#..#NN#..#NNNNE";
string row50 = "NNNN#..#NN#..#NN#..#NNNNNNNNNNNNNN#..#NN#..#NN#..#NNNNE";
string row51 = "#####..####..#NN#..#######NN#######..#NN#..####..#####E";
string row52 = "#............#NN#........#NN#........#NN#............#E";
string row53 = "#............#NN#........#NN#........#NN#............#E";
string row54 = "#..###########NN#######..#NN#..#######NN###########..#E";
string row55 = "#..#NNNNNNNNNNNNNNNNNN#..#NN#..#NNNNNNNNNNNNNNNNNN#..#E";
string row56 = "#..#NNNNNNNNNNNNNNNNNN#..#NN#..#NNNNNNNNNNNNNNNNNN#..#E";
string row57 = "#..####################..####..####################..#E";
string row58 = "#....................................................#E";
string row59 = "#....................................................#E";
string row60 = "######################################################E";

void CreateStringMaze(string row[][55])
{
	for (int i = 0; i < 61; i++)
	{
		string maze = maze + row[i][55];
	}
}

//string maze = row0 + row1 + row2 + row3 + row4 + row5 + row6 + row7 + row8 + row9 + row10 + row11 + row12
//+ row13 + row14 + row15 + row16 + row17 + row18 + row19 + row20;
//string maze = "#..#";

#endif