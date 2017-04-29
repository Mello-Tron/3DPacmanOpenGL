#ifndef DISPLAY_H
#define DISPLAY_H

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Called whenever GLUT determines the window needs to be redisplayed,
//  (cont): Draws all objects and determines movement of camera
// Edited: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  /*clear the window */

	projection = Perspective(fovy, aspect, zNear, zFar);
	modelview = Translate(0.0, 0.0, 1.0)*LookAt(eye, at, up);

	//draw skybox
	skyboxAngle += 0.002;
	GLfloat skyboxTheta[3] = { theta[0] + skyboxAngle, theta[1], theta[2] + (skyboxAngle * 2.0) };
	go_skybox.draw(skyboxTheta);

	//draw maze
	drawMaze(maze);

	//draw tree set 1
	for (int i = 2; i < 54; i += 2) {
		myTree.draw(theta, vec3(float(i), 0.0, 1.5));
	}

	//draw tree set 2
	for (int i = 14; i < 26; i += 2) {
		myTree.draw(theta, vec3(float(i), 0.0, 4.5));
	}

	//draw donald 1
	if (!drawDonaldCloseFace) {
		myDonald.draw(theta, donaldPosition);
		myDonald.draw(theta, donaldPosition2);
	}
	else {
		myDonaldClose.draw(theta, donaldPosition);
		myDonaldClose.draw(theta, donaldPosition2);
	}

	moveCamera();

	// swap the buffers
	glutSwapBuffers();

	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	aspect = GLfloat(w) / h;
}

#endif