#ifndef CAMERA_H
#define CAMERA_H

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Returns true if there is a collision between where the camera is going and any wall
// Input: (int) direction - the direction the camera is moving, case 0 = forwards, case 1 = reverse
// Author: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
bool cameraIsCollidingGrid(int direction) {
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
// Purpose: Based on status of W/S/A/D keys, move the camera forward, in reverse or not at all,
//  (cont): Called by display()
// Author: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
void moveCamera() {
	if (goForward == true)
	{
		if (!cameraIsCollidingGrid(0)) {
			eye = eye + cameraSpeed*view;
			at = at + cameraSpeed*view;
		}
	}

	if (goReverse == true)
	{
		if (!cameraIsCollidingGrid(1)) {
			eye = eye - cameraSpeed*view;
			at = at - cameraSpeed*view;
		}
	}

	if (strafeLeft == true)
	{
		//...
	}

	if (strafeRight == true) {
		//...
	}
}

#endif