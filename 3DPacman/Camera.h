#ifndef CAMERA_H
#define CAMERA_H

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Returns true if there is a collision between the given position and any wall (GRID system)
// Author: Patrick H. 5/4
//////////////////////////////////////////////////////////////////////////////////////////////
bool positionIsCollidingWallGrid(float myX, float myY, float myZ, float size) {
	float posX = 0.0;
	float posZ = 0.0;
	bool isCollision = false;
	//float size = 1.8;
	float size2 = 6.5;

	for (int i = 0; i < maze.size(); i++) {
		if (maze[i] == '#') {
			if (myX < (posX + size) && myX >(posX - size) && myZ < (posZ + size) && myZ >(posZ - size)) {
				isCollision = true;
				break;
			}

			posX += 2.0;
		}
		else if (maze[i] == 'E') {
			posX = 0.0;
			posZ += 2.0;
		}
		else {
			posX += 2.0;
		}
	}

	return isCollision;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Returns true if there is a collision between where the camera is going and any wall (GRID system)
// Input: (int) direction - the direction the camera is moving, case 0 = forwards, case 1 = reverse
// Author: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
bool cameraIsCollidingWallGrid(int direction) {
	float posX = 0.0;
	float posZ = 0.0;
	bool isCollision = false;
	float size = 1.8;
	float size2 = 6.5;

	vec4 eye2;

	switch (direction) {
	case 0: //forward
		eye2 = eye + cameraSpeed*view;
		break;
	case 1: //reverse
		eye2 = eye - cameraSpeed*view;
		break;
	default:
		//invalid
		break;
	}

	vec3 nextPos = (eye2.x, eye2.y, eye2.z);

	for (int i = 0; i < maze.size(); i++) {
		if (maze[i] == '#') {
			if (eye2.x < (posX + size) && eye2.x >(posX - size) && eye2.z < (posZ + size) && eye2.z >(posZ - size)) {
				isCollision = true;
				break;
			}

			posX += 2.0;
		}
		else if (maze[i] == 'E') {
			posX = 0.0;
			posZ += 2.0;
		}
		else {
			posX += 2.0;
		}
	}

	return isCollision;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Returns true if there is a collision between where the camera is going and a position
//////////////////////////////////////////////////////////////////////////////////////////////////
bool cameraIsCollidingPosition(int direction, float posX, float posZ, float size) {
	//float posX = 0.0;
	//float posZ = 0.0;
	bool isCollision = false;
	//float size = 1.8;
	//float size2 = 6.5;

	vec4 eye2;

	switch (direction) {
	case 0: //forward
		eye2 = eye + cameraSpeed*view;
		break;
	case 1: //reverse
		eye2 = eye - cameraSpeed*view;
		break;
	default:
		//invalid
		break;
	}

	vec3 nextPos = (eye2.x, eye2.y, eye2.z);

	if (eye2.x < (posX + size) && eye2.x >(posX - size) && eye2.z < (posZ + size) && eye2.z >(posZ - size)) {
		isCollision = true;
	}

	return isCollision;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Returns true if there is a collision between where the camera is going and any wall (GRID system)
// Input: (int) direction - the direction the camera is moving, case 0 = forwards, case 1 = reverse
// Author: Patrick H. 4/17
// Idea for v3: use floor/ceiling instead of for loop for z value & access rows[] not by for loop
//////////////////////////////////////////////////////////////////////////////////////////////
bool cameraIsCollidingWallGridV2(int direction) {
	float posZ = 0.0;
	bool isCollision = false;
	float size = 1.8;

	vec4 eye2;

	switch (direction) {
	case 0: //forward
		eye2 = eye + cameraSpeed*view;
		break;
	case 1: //reverse
		eye2 = eye - cameraSpeed*view;
		break;
	default:
		//invalid
		break;
	}

	vec3 nextPos = (eye2.x, eye2.y, eye2.z);

	for (int i = 0; i < maze.size(); i++) {
		if (eye2.z > ((i*2) - size) && eye2.z < ((i*2) + size)) {
			int e = 0;
			for (int j = 0; j < maze.size(); j++) {
				if (maze[j] == 'E') {
					e++;
				}
				if (e == i) {
					float posX = 0.0;
					j++;
					while (maze[j] != 'E') {
						if (maze[j] == '#' && eye2.x < (posX + size) && eye2.x > (posX - size)) {
							isCollision = true;
						}
						j++;
						posX += 2.0;
					}
					break;
				}
			}
			break;
		}
	}

	return isCollision;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Returns true if there is a collision between where the camera is going and any wall (RAY intersection)
// Author: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
bool cameraIsCollidingWallRay() {
	float posX = 0.0;
	float posZ = 0.0;
	bool isCollision = false;
	float size = 2.0;

	for (int i = 0; i < maze.size(); i++) {
		if (maze[i] == '#') {
			if ((eye.x > posX - size) && (eye.x < posX + size) && (eye.z > posZ - size) && (eye.z < posZ + size)) {
				if (wall.collision(theta, vec3(posX, 0.0, posZ))) {
					isCollision = true;
					break;
				}
			}

			posX += 2.0;
		}
		else if (maze[i] == 'E') {
			posX = 0.0;
			posZ += 2.0;
		}
		else {
			posX += 2.0;
		}
	}

	return isCollision;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Moves camera forwards || backwards || strafeleft || straferight, if there is no collision (GRID system)
// Author: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
void gridCollision() {
	if (goForward == true)
	{
		if (!cameraIsCollidingWallGrid(0)) {
			eye = eye + cameraSpeed*view;
			at = at + cameraSpeed*view;
		}

		if (cameraIsCollidingPosition(0, GhostPos1.x, GhostPos1.z, 2.0) || cameraIsCollidingPosition(0, GhostPos2.x, GhostPos2.z, 2.0) || cameraIsCollidingPosition(0, GhostPos3.x, GhostPos3.z, 2.0) || cameraIsCollidingPosition(0, GhostPos4.x, GhostPos4.z, 2.0)) {	
			eye = vec4(50.0, 0.0, 66.0, 0.0);
			at = vec4(50.0, 0.0, 66.0, 1.0);
			view = vec4(6.5, 0.0, 2.75, 0.0);
			up = vec4(0.0, 1.0, 0.0, 0.0);
			health--;
		}
	}

	if (goReverse == true)
	{
		if (!cameraIsCollidingWallGrid(1)) {
			eye = eye - cameraSpeed*view;
			at = at - cameraSpeed*view;
		}
	}

	if (strafeLeft == true)
	{
		//...
	}

	if (strafeRight == true)
	{
		//...
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Moves camera forwards || backwards || strafeleft || straferight, if there is no collision (RAY intersection)
// Author: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
void rayCollision() {
	if (!cameraIsCollidingWallRay()) {
		if (goForward == true)
		{
			eye = eye + cameraSpeed*view;
			at = at + cameraSpeed*view;
		}

		if (goReverse == true)
		{
			eye = eye - cameraSpeed*view;
			at = at - cameraSpeed*view;
		}

		if (strafeLeft == true)
		{
			//...
		}

		if (strafeRight == true) {
			//...
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Based on status of W/S/A/D keys, move the camera forward, in reverse or not at all,
//  (cont): Called by display()
// Author: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
void moveCamera() {
	//rayCollision();
	gridCollision();
}

#endif