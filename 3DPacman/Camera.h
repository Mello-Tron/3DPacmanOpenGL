#ifndef CAMERA_H
#define CAMERA_H

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

	if (eye2.x < (donaldPosition.x + size2) && eye2.x >(donaldPosition.x - size2) && eye2.z < (donaldPosition.z + size2) && eye2.z >(donaldPosition.z - size2)) {
		drawDonaldCloseFace = true;
	}
	else if (eye2.x < (donaldPosition2.x + size2) && eye2.x >(donaldPosition2.x - size2) && eye2.z < (donaldPosition2.z + size2) && eye2.z >(donaldPosition2.z - size2)) {
		drawDonaldCloseFace = true;
	}
	else
		drawDonaldCloseFace = false;

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
		//if (!cameraIsCollidingWallGrid(0)) {
			eye = eye + cameraSpeed*view;
			at = at + cameraSpeed*view;
		//}
	}

	if (goReverse == true)
	{
		//if (!cameraIsCollidingWallGrid(1)) {
			eye = eye - cameraSpeed*view;
			at = at - cameraSpeed*view;
		//}
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