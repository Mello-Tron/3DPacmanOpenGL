#ifndef DOT_H
#define DOT_H

class Dot;

vector<Dot> dots;

class Dot {
public:
	bool isVisible;
	vec3 pos;

	Dot() {
		isVisible = true;
		pos = vec3(0.0, 0.0, 0.0);
	}

	Dot(vec3 _pos) {
		isVisible = true;
		pos = _pos;
	}

	void display() {
		if (isVisible) {
			glDisable(GL_CULL_FACE);
			myDot.draw(theta, pos);
			glEnable(GL_CULL_FACE);
		}
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Populates vector of dots
// Input: (string) maze - a string representing a maze (# = wall, . = no wall, E = end of row)
//////////////////////////////////////////////////////////////////////////////////////////////
void populateDots(string &maze) {
	float posX = 0.0;
	float posZ = 0.0;

	for (int i = 0; i < maze.size(); i++) {
		if (maze[i] == '#') {
			//wall.draw(theta, vec3(posX, 0.0, posZ));
			posX += 2.0;
		}
		else if (maze[i] == 'E') {
			posX = 0.0;
			posZ += 2.0;
		}
		else if (maze[i] == '.') {
			//ground.draw(theta, vec3(posX, -2.0, posZ));

			posX += 2.0;
		}
		else if (maze[i] == 'D') {
			//ground.draw(theta, vec3(posX, -2.0, posZ));

			//add dot to vector of dots
			//myDot.draw(theta, vec3(posX + 1.0, 0.0, posZ + 1.0));
			Dot newDot(vec3(posX + 1.0, 0.0, posZ + 1.0));
			dots.push_back(newDot);

			posX += 2.0;
		}
		else {
			posX += 2.0;
		}
	}
}

#endif