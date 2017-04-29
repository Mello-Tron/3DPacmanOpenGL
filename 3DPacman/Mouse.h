#ifndef MOUSE_H
#define MOUSE_H

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Called by GLUT when the mouse moves within the window whether buttons are pressed or not
// Input: (int) x - x location of mouse when key is pressed, (int) y - y location of mouse when key is pressed
// Author: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
void mouseMove(int x, int y)
{
	//zoom = ( 10.0 / 500.0 ) * y +2.0;  // compute zoom factor 
	int centerX = 600;
	int centerY = 350;
	int sensitivity = 1;
	float xRotate = 2.5;
	float yRotate = 0.16;

	if (x - centerX > sensitivity) {
		view = RotateY(-xRotate) * view;//rotate eye -3 degrees
		GLfloat temp = at.y;
		at = eye + view;
		at.y = temp;
	}
	else if (x - centerX < -sensitivity) {
		view = RotateY(xRotate) * view;//rotate eye 3 degrees
		GLfloat temp = at.y;
		at = eye + view;
		at.y = temp;
	}

	if (y - centerY > sensitivity) {
		at.y -= yRotate;
	}
	else if (y - centerY < -sensitivity) {
		at.y += yRotate;
	}

	if (x != centerX || y != centerY) {
		glutWarpPointer(centerX, centerY);
		glutPostRedisplay();
	}
}

#endif