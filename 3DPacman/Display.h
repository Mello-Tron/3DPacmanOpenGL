#ifndef DISPLAY_H
#define DISPLAY_H

//2d health bar
void drawHealthBar(float health) {
	glDisable(GL_DEPTH_TEST);

	const int numDiv = 10;
	const float sep = 0.04;
	const float barHeight = 0.1 / (float)numDiv;
	const float xStart = -1.0;
	const float yStart = 0.5;
	const float xWidth = 0.01;

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	for (float i = 0; i < health; i += (sep + barHeight)) {
		glVertex2f(xStart, yStart + (i/2));
		glVertex2f(xStart + xWidth, yStart + (i / 2));
		glVertex2f(xStart + xWidth, yStart + (i / 2) + barHeight);
		glVertex2f(xStart, yStart + (i / 2) + barHeight);
	}
	glEnd();
	glEnable(GL_DEPTH_TEST);
}

//2d Text
void displayText(float x, float y, int r, int g, int b, const char *string) {
	glDisable(GL_DEPTH_TEST);
	int j = strlen(string);

	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
	glEnable(GL_DEPTH_TEST);
}

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

	moveCamera();

	glDisable(GL_CULL_FACE);

	//draw skybox
	skyboxAngle += 0.002;
	GLfloat skyboxTheta[3] = { theta[0] + skyboxAngle, theta[1], theta[2] + (skyboxAngle * 2.0) };
	go_skybox.draw(skyboxTheta);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//draw maze
	drawMaze(maze);

	//draw tree set 1
	//for (int i = 2; i < 54; i += 2) {
	//	myTree.draw(theta, vec3(float(i), 0.0, 1.5));
	//}

	//draw tree set 2
	//for (int i = 14; i < 26; i += 2) {
	//	myTree.draw(theta, vec3(float(i), 0.0, 4.5));
	//}

	//draw donald 1
	if (!drawDonaldCloseFace) {
		myDonald.draw(theta, donaldPosition);
		myDonald.draw(theta, donaldPosition2);
	}
	else {
		myDonaldClose.draw(theta, donaldPosition);
		myDonaldClose.draw(theta, donaldPosition2);
	}

	//Attempt at 2d graphic
	//vec3 screenPicPosition(at.x, at.y, at.z);
	//screenPic.draw(theta, screenPicPosition);

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