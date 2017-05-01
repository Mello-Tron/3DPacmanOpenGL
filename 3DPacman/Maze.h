#ifndef MAZE_H
#define MAZE_H

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Takes in a string representing a maze and places wall objects accordingly
// Input: (string) maze - a string representing a maze (# = wall, . = no wall, E = end of row)
// Author: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
void drawMaze(string &maze) {
	float posX = 0.0;
	float posZ = 0.0;

	for (int i = 0; i < maze.size(); i++) {
		if (maze[i] == '#') {
			wall.draw(theta, vec3(posX, 0.0, posZ));
			posX += 2.0;
		}
		else if (maze[i] == 'E') {
			posX = 0.0;
			posZ += 2.0;
		}
		else if (maze[i] == '.') {
			ground.draw(theta, vec3(posX, -2.0, posZ));
			posX += 2.0;
		}
		else {
			posX += 2.0;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Return the total number of "#"s in a string (a.k.a. the number of walls in the maze)
// Input: (string) a - the maze string
// Author: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
int countWallsInString(string a) {
	int total = 0;

	for (int i = 0; i < a.size(); i++) {
		if (a[i] == '#')
			total++;
	}

	return total;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Return the total number of "."s in a string (a.k.a. the number of empty spaces in the maze)
// Input: (string) a - the maze string
// Author: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
int countEmptySpacesInString(string a) {
	int total = 0;

	for (int i = 0; i < a.size(); i++) {
		if (a[i] == '.')
			total++;
	}

	return total;
}

#endif