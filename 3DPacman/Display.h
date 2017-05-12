#ifndef DISPLAY_H
#define DISPLAY_H

int rand_int;
int GhostDirection = 1;

int randomator()
{
	srand((unsigned)time(0));
	return 0;
}
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
void displayText(float x, float y, GLfloat r, GLfloat g, GLfloat b, string mystring) {
	glDisable(GL_DEPTH_TEST);
	int j = mystring.length();

	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, mystring[i]);
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
	randomator();
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



	//draw donald 1
	vec3 nextDonaldPosition;
	if(GhostDirection == 1 || GhostDirection == 3)
		nextDonaldPosition = vec3(donaldPosition1.x + donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
	if(GhostDirection == 2  || GhostDirection == 4)
		nextDonaldPosition = vec3(donaldPosition1.x ,donaldPosition1.y,donaldPosition1.z + donald1XSpeed);

	if (!positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8)) {
		donaldPosition1 = nextDonaldPosition;

		//SOUND EQUATIONS
		float distanceBetween = pow((donaldPosition1.x - eye.x), 2) + pow((donaldPosition1.y - eye.y), 2) + pow((donaldPosition1.z - eye.z), 2);
		distanceBetween /= 10.0;
		float volume = 100.0;
		float newVolume = volume - distanceBetween;
		if (newVolume > 50.0) {
			volume = newVolume;
		}
		else if (newVolume < 50.0) {
			volume = newVolume / 3;
		}
		else
			volume = newVolume;

		if (volume < 1.1)
			volume = 0.0;
		else
			volume = 12.04*log2(volume) + 20.0;

		sound2.setVolume(volume);
		sound2.play();
	}
	else {
		if (GhostDirection == 1)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection = 3;
				nextDonaldPosition = vec3(donaldPosition1.x + donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
				if (positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextDonaldPosition = vec3(donaldPosition1.x + donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
				}
				donaldPosition1 = nextDonaldPosition;
			}
			else if (rand_int > 0 && rand_int <6)
			{
				GhostDirection = 4;
				nextDonaldPosition = vec3(donaldPosition1.x,donaldPosition1.y,donaldPosition1.z - donald1XSpeed);
				if (positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextDonaldPosition = vec3(donaldPosition1.x,donaldPosition1.y,donaldPosition1.z - donald1XSpeed);
				}
				donaldPosition1 = nextDonaldPosition;
			}
			else if (rand_int >=6 )
			{
				GhostDirection = 2;
				nextDonaldPosition = vec3(donaldPosition1.x,donaldPosition1.y,donaldPosition1.z + donald1XSpeed);
				if (positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextDonaldPosition = vec3(donaldPosition1.x,donaldPosition1.y,donaldPosition1.z + donald1XSpeed);
				}
				donaldPosition1 = nextDonaldPosition;
			}
		}
		else if (GhostDirection == 2)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection = 4;
				nextDonaldPosition = vec3(donaldPosition1.x,donaldPosition1.y,donaldPosition1.z + donald1XSpeed);
				if (positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextDonaldPosition = vec3(donaldPosition1.x,donaldPosition1.y,donaldPosition1.z + donald1XSpeed);
				}
				donaldPosition1 = nextDonaldPosition;
			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection = 3;
				nextDonaldPosition = vec3(donaldPosition1.x - donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
				if (positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextDonaldPosition = vec3(donaldPosition1.x - donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
				}
				donaldPosition1 = nextDonaldPosition;
			}
			else if (rand_int >= 6)
			{
				GhostDirection = 1;
				nextDonaldPosition = vec3(donaldPosition1.x + donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
				if (positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextDonaldPosition = vec3(donaldPosition1.x + donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
				}
				donaldPosition1 = nextDonaldPosition;
			}
		}
		else if (GhostDirection == 3)
		{
			rand_int = rand() % 10;
		 if (rand_int == 0)
		{
			GhostDirection = 1;
			nextDonaldPosition = vec3(donaldPosition1.x + donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
			if (positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8))
			{
				donald1XSpeed *= -1;
				nextDonaldPosition = vec3(donaldPosition1.x + donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
			}
			donaldPosition1 = nextDonaldPosition;
		}
		else if (rand_int > 0 && rand_int < 6)
		{
			GhostDirection = 4;
			nextDonaldPosition = vec3(donaldPosition1.x,donaldPosition1.y,donaldPosition1.z - donald1XSpeed);
			if (positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8))
			{
				donald1XSpeed *= -1;
				nextDonaldPosition = vec3(donaldPosition1.x,donaldPosition1.y,donaldPosition1.z - donald1XSpeed);
			}
			donaldPosition1 = nextDonaldPosition;
		}
		else if (rand_int >= 6)
		{
			GhostDirection = 2;
			nextDonaldPosition = vec3(donaldPosition1.x,donaldPosition1.y,donaldPosition1.z + donald1XSpeed);
			if (positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8))
			{
				donald1XSpeed *= -1;
				nextDonaldPosition = vec3(donaldPosition1.x,donaldPosition1.y,donaldPosition1.z + donald1XSpeed);
			}
			donaldPosition1 = nextDonaldPosition;
		}
		}
		else if (GhostDirection == 4)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection = 2;
				nextDonaldPosition = vec3(donaldPosition1.x,donaldPosition1.y,donaldPosition1.z + donald1XSpeed);
				if (positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextDonaldPosition = vec3(donaldPosition1.x,donaldPosition1.y,donaldPosition1.z + donald1XSpeed);
				}
				donaldPosition1 = nextDonaldPosition;
				
			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection = 1;
				nextDonaldPosition = vec3(donaldPosition1.x - donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
				if (positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextDonaldPosition = vec3(donaldPosition1.x - donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
				}
				donaldPosition1 = nextDonaldPosition;
			}
			else if (rand_int >= 6)
			{
				GhostDirection = 3;
				nextDonaldPosition = vec3(donaldPosition1.x + donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
				if (positionIsCollidingWallGrid(nextDonaldPosition.x, nextDonaldPosition.y, nextDonaldPosition.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextDonaldPosition = vec3(donaldPosition1.x + donald1XSpeed,donaldPosition1.y,donaldPosition1.z);
				}
				donaldPosition1 = nextDonaldPosition;
			}
		}
		
		cout << rand_int << endl;
		
	}
	myDonald.draw(theta,donaldPosition1);

	glEnable(GL_CULL_FACE);

	//draw dots
	int direction = -1;
	if (goForward == true)
		direction = 0;
	else if (goReverse == true)
		direction = 1;

	for (int i = 0; i < dots.size(); i++) {
		if (direction != -1) {
			//cout << "direction = " << direction << endl;
			if (cameraIsCollidingPosition(direction, dots[i].pos.x, dots[i].pos.z, 0.4) && dots[i].isVisible) {
				//cout << "HIT" << endl;
				soundPacmanChomp.play();
				dots[i].isVisible = false;
				score += 1;
			}
		}

		dots[i].display();
	}

	//Draw health
	vec3 screenPicPosition(-1.45, 0.8, 0.0);
	screenPic.draw(theta, screenPicPosition);
	vec3 screenPicPosition2(-1.25, 0.8, 0.0);
	screenPic.draw(theta, screenPicPosition2);
	vec3 screenPicPosition3(-1.05, 0.8, 0.0);
	screenPic.draw(theta, screenPicPosition3);

	//Draw Score
	string scoreText = "Score: " + to_string(score);
	displayText(-0.94, 0.6, 0.5, 0.1, 1.0, scoreText);

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