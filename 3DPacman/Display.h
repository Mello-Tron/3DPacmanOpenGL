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

	glEnable(GL_CULL_FACE);

	//draw skybox
	glCullFace(GL_FRONT);
	skyboxAngle += 0.002;
	GLfloat skyboxTheta[3] = { theta[0] + skyboxAngle, theta[1], theta[2] + (skyboxAngle * 2.0) };
	go_skybox.draw(skyboxTheta);

	//draw maze
	glCullFace(GL_BACK);
	drawMaze(maze);

	glDisable(GL_CULL_FACE);

	//draw dots
	for (int i = 0; i < dots.size(); i++) {
		dots[i].display();
	}

	//draw donald 1
	vec3 nextDonaldPosition = vec3(donaldPosition.x + donaldXSpeed, donaldPosition.y, donaldPosition.z);
	if (!positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z)) {
		donaldPosition = nextDonaldPosition;
	}
	else {
		donaldXSpeed *= -1;

		//SOUND EQUATIONS
		//float distanceBetween = pow((donaldPosition.x - eye.x), 2) + pow((donaldPosition.y - eye.y), 2) + pow((donaldPosition.z - eye.z), 2);
		//distanceBetween /= 10.0;
		//float volume = 100.0;
		//float newVolume = volume - distanceBetween;
		//if (newVolume > 50.0) {
		//	volume = newVolume;
		//}
		//else if (newVolume < 50.0) {
		//	volume = newVolume / 3;
		//}
		//else
		//	volume = newVolume;

		//if (volume < 1.1)
		//	volume = 0.0;
		//else
		//	volume = 12.04*log2(volume) + 20.0;

		//sound2.setVolume(volume);
		//sound2.play();
	}
	myDonald.draw(theta, donaldPosition);

	glEnable(GL_CULL_FACE);

	//Attempt at 2d graphic
	vec3 screenPicPosition(-1.4, 0.8, 0.0);
	screenPic.draw(theta, screenPicPosition);

	//Draw Score
	displayText(-0.9, -0.9, 256.0, 256.0, 256.0, "Score: 0");

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