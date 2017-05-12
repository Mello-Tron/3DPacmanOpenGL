#ifndef DISPLAY_H
#define DISPLAY_H

int rand_int;
int GhostDirection1 = 1;
int GhostDirection2 = 1;
int GhostDirection3 = 1;
int GhostDirection4 = 1;

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
	vec3 nextGhostPos;
	vec3 nextGhostPos2;
	vec3 nextGhostPos3;
	vec3 nextGhostPos4;

	if(GhostDirection1 == 1 || GhostDirection1 == 3)
		nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z+ donald1XSpeed);
	if(GhostDirection1 == 2  || GhostDirection1 == 4)
		nextGhostPos = vec3(GhostPos1.x + donald1XSpeed,GhostPos1.y,GhostPos1.z);

	if (!positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8)) {
		GhostPos1 = nextGhostPos;

		//SOUND EQUATIONS
		float distanceBetween = pow((GhostPos1.x - eye.x), 2) + pow((GhostPos1.y - eye.y), 2) + pow((GhostPos1.z - eye.z), 2);
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
		if (GhostDirection1 == 1)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection1 = 3;
				nextGhostPos = vec3(GhostPos1.x + donald1XSpeed,GhostPos1.y,GhostPos1.z);
				if (positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextGhostPos = vec3(GhostPos1.x + donald1XSpeed,GhostPos1.y,GhostPos1.z);
				}
				GhostPos1 = nextGhostPos;
			}
			else if (rand_int > 0 && rand_int <6)
			{
				GhostDirection1 = 4;
				nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z - donald1XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z - donald1XSpeed);
				}
				GhostPos1 = nextGhostPos;
			}
			else if (rand_int >=6 )
			{
				GhostDirection1 = 2;
				nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z + donald1XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z + donald1XSpeed);
				}
				GhostPos1 = nextGhostPos;
			}
		}
		else if (GhostDirection1 == 2)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection1 = 4;
				nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z + donald1XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z + donald1XSpeed);
				}
				GhostPos1 = nextGhostPos;
			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection1 = 3;
				nextGhostPos = vec3(GhostPos1.x - donald1XSpeed,GhostPos1.y,GhostPos1.z);
				if (positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextGhostPos = vec3(GhostPos1.x - donald1XSpeed,GhostPos1.y,GhostPos1.z);
				}
				GhostPos1 = nextGhostPos;
			}
			else if (rand_int >= 6)
			{
				GhostDirection1 = 1;
				nextGhostPos = vec3(GhostPos1.x + donald1XSpeed,GhostPos1.y,GhostPos1.z);
				if (positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextGhostPos = vec3(GhostPos1.x + donald1XSpeed,GhostPos1.y,GhostPos1.z);
				}
				GhostPos1 = nextGhostPos;
			}
		}
		else if (GhostDirection1 == 3)
		{
			rand_int = rand() % 10;
		 if (rand_int == 0)
		{
			GhostDirection1 = 1;
			nextGhostPos = vec3(GhostPos1.x + donald1XSpeed,GhostPos1.y,GhostPos1.z);
			if (positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8))
			{
				donald1XSpeed *= -1;
				nextGhostPos = vec3(GhostPos1.x + donald1XSpeed,GhostPos1.y,GhostPos1.z);
			}
			GhostPos1 = nextGhostPos;
		}
		else if (rand_int > 0 && rand_int < 6)
		{
			GhostDirection1 = 4;
			nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z - donald1XSpeed);
			if (positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8))
			{
				donald1XSpeed *= -1;
				nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z - donald1XSpeed);
			}
			GhostPos1 = nextGhostPos;
		}
		else if (rand_int >= 6)
		{
			GhostDirection1 = 2;
			nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z + donald1XSpeed);
			if (positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8))
			{
				donald1XSpeed *= -1;
				nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z + donald1XSpeed);
			}
			GhostPos1 = nextGhostPos;
		}
		}
		else if (GhostDirection1 == 4)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection1 = 2;
				nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z + donald1XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextGhostPos = vec3(GhostPos1.x,GhostPos1.y,GhostPos1.z + donald1XSpeed);
				}
				GhostPos1 = nextGhostPos;
				
			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection1 = 1;
				nextGhostPos = vec3(GhostPos1.x - donald1XSpeed,GhostPos1.y,GhostPos1.z);
				if (positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextGhostPos = vec3(GhostPos1.x - donald1XSpeed,GhostPos1.y,GhostPos1.z);
				}
				GhostPos1 = nextGhostPos;
			}
			else if (rand_int >= 6)
			{
				GhostDirection1 = 3;
				nextGhostPos = vec3(GhostPos1.x + donald1XSpeed,GhostPos1.y,GhostPos1.z);
				if (positionIsCollidingWallGrid(nextGhostPos.x, nextGhostPos.y, nextGhostPos.z, 1.8))
				{
					donald1XSpeed *= -1;
					nextGhostPos = vec3(GhostPos1.x + donald1XSpeed,GhostPos1.y,GhostPos1.z);
				}
				GhostPos1 = nextGhostPos;
			}
		}	
	}

	if (GhostDirection2 == 1 || GhostDirection2 == 3)
		nextGhostPos2 = vec3(GhostPos2.x , GhostPos2.y, GhostPos2.z + donald2XSpeed);
	if (GhostDirection2 == 2 || GhostDirection2 == 4)
		nextGhostPos2 = vec3(GhostPos2.x + donald2XSpeed, GhostPos2.y, GhostPos2.z);

	if (!positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8)) {
		GhostPos2 = nextGhostPos2;

		//SOUND EQUATIONS
		float distanceBetween = pow((GhostPos2.x - eye.x), 2) + pow((GhostPos2.y - eye.y), 2) + pow((GhostPos2.z - eye.z), 2);
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
		if (GhostDirection2 == 1)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection2 = 3;
				nextGhostPos2 = vec3(GhostPos2.x + donald2XSpeed, GhostPos2.y, GhostPos2.z);
				if (positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8))
				{
					donald2XSpeed *= -1;
					nextGhostPos2 = vec3(GhostPos2.x + donald2XSpeed, GhostPos2.y, GhostPos2.z);
				}
				GhostPos2 = nextGhostPos2;
			}
			else if (rand_int > 0 && rand_int <6)
			{
				GhostDirection2 = 4;
				nextGhostPos2 = vec3(GhostPos2.x, GhostPos2.y, GhostPos2.z - donald2XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8))
				{
					donald2XSpeed *= -1;
					nextGhostPos2 = vec3(GhostPos2.x, GhostPos2.y, GhostPos2.z - donald2XSpeed);
				}
				GhostPos2 = nextGhostPos2;
			}
			else if (rand_int >= 6)
			{
				GhostDirection2 = 2;
				nextGhostPos2 = vec3(GhostPos2.x, GhostPos2.y, GhostPos2.z + donald2XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8))
				{
					donald2XSpeed *= -1;
					nextGhostPos2 = vec3(GhostPos2.x, GhostPos2.y, GhostPos2.z + donald2XSpeed);
				}
				GhostPos2 = nextGhostPos2;
			}
		}
		else if (GhostDirection2 == 2)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection2 = 4;
				nextGhostPos2 = vec3(GhostPos2.x, GhostPos2.y, GhostPos2.z + donald2XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8))
				{
					donald2XSpeed *= -1;
					nextGhostPos2 = vec3(GhostPos2.x, GhostPos2.y, GhostPos2.z + donald2XSpeed);
				}
				GhostPos2 = nextGhostPos2;
			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection2 = 3;
				nextGhostPos2 = vec3(GhostPos2.x - donald2XSpeed, GhostPos2.y, GhostPos2.z);
				if (positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8))
				{
					donald2XSpeed *= -1;
					nextGhostPos2 = vec3(GhostPos2.x - donald2XSpeed, GhostPos2.y, GhostPos2.z);
				}
				GhostPos2 = nextGhostPos2;
			}
			else if (rand_int >= 6)
			{
				GhostDirection2 = 1;
				nextGhostPos2 = vec3(GhostPos2.x + donald2XSpeed, GhostPos2.y, GhostPos2.z);
				if (positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8))
				{
					donald2XSpeed *= -1;
					nextGhostPos2 = vec3(GhostPos2.x + donald2XSpeed, GhostPos2.y, GhostPos2.z);
				}
				GhostPos2 = nextGhostPos2;
			}
		}
		else if (GhostDirection2 == 3)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection2 = 1;
				nextGhostPos2 = vec3(GhostPos2.x + donald2XSpeed, GhostPos2.y, GhostPos2.z);
				if (positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8))
				{
					donald2XSpeed *= -1;
					nextGhostPos2 = vec3(GhostPos2.x + donald2XSpeed, GhostPos2.y, GhostPos2.z);
				}
				GhostPos2 = nextGhostPos2;
			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection2 = 4;
				nextGhostPos2 = vec3(GhostPos2.x, GhostPos2.y, GhostPos2.z - donald2XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8))
				{
					donald2XSpeed *= -1;
					nextGhostPos2 = vec3(GhostPos2.x, GhostPos2.y, GhostPos2.z - donald2XSpeed);
				}
				GhostPos2 = nextGhostPos2;
			}
			else if (rand_int >= 6)
			{
				GhostDirection2 = 2;
				nextGhostPos2 = vec3(GhostPos2.x, GhostPos2.y, GhostPos2.z + donald2XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8))
				{
					donald2XSpeed *= -1;
					nextGhostPos2 = vec3(GhostPos2.x, GhostPos2.y, GhostPos2.z + donald2XSpeed);
				}
				GhostPos2 = nextGhostPos2;
			}
		}
		else if (GhostDirection2 == 4)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection2 = 2;
				nextGhostPos2 = vec3(GhostPos2.x, GhostPos2.y, GhostPos2.z + donald2XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8))
				{
					donald2XSpeed *= -1;
					nextGhostPos2 = vec3(GhostPos2.x, GhostPos2.y, GhostPos2.z + donald2XSpeed);
				}
				GhostPos2 = nextGhostPos2;

			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection2 = 1;
				nextGhostPos2 = vec3(GhostPos2.x - donald2XSpeed, GhostPos2.y, GhostPos2.z);
				if (positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8))
				{
					donald2XSpeed *= -1;
					nextGhostPos2 = vec3(GhostPos2.x - donald2XSpeed, GhostPos2.y, GhostPos2.z);
				}
				GhostPos2 = nextGhostPos2;
			}
			else if (rand_int >= 6)
			{
				GhostDirection2 = 3;
				nextGhostPos2 = vec3(GhostPos2.x + donald2XSpeed, GhostPos2.y, GhostPos2.z);
				if (positionIsCollidingWallGrid(nextGhostPos2.x, nextGhostPos2.y, nextGhostPos2.z, 1.8))
				{
					donald2XSpeed *= -1;
					nextGhostPos2 = vec3(GhostPos2.x + donald2XSpeed, GhostPos2.y, GhostPos2.z);
				}
				GhostPos2 = nextGhostPos2;
			}
		}
	}

	
	if (GhostDirection3 == 1 || GhostDirection3 == 3)
		nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z + donald3XSpeed);
	if (GhostDirection3 == 2 || GhostDirection3 == 4)
		nextGhostPos3 = vec3(GhostPos3.x + donald3XSpeed, GhostPos3.y, GhostPos3.z);

	if (!positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8)) {
		GhostPos3 = nextGhostPos3;

		//SOUND EQUATIONS
		float distanceBetween = pow((GhostPos3.x - eye.x), 2) + pow((GhostPos3.y - eye.y), 2) + pow((GhostPos3.z - eye.z), 2);
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
		if (GhostDirection3 == 1)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection3 = 3;
				nextGhostPos3 = vec3(GhostPos3.x + donald3XSpeed, GhostPos3.y, GhostPos3.z);
				if (positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8))
				{
					donald3XSpeed *= -1;
					nextGhostPos3 = vec3(GhostPos3.x + donald3XSpeed, GhostPos3.y, GhostPos3.z);
				}
				GhostPos3 = nextGhostPos3;
			}
			else if (rand_int > 0 && rand_int <6)
			{
				GhostDirection3 = 4;
				nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z - donald3XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8))
				{
					donald3XSpeed *= -1;
					nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z - donald3XSpeed);
				}
				GhostPos3 = nextGhostPos3;
			}
			else if (rand_int >= 6)
			{
				GhostDirection3 = 2;
				nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z + donald3XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8))
				{
					donald3XSpeed *= -1;
					nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z + donald3XSpeed);
				}
				GhostPos3 = nextGhostPos3;
			}
		}
		else if (GhostDirection3 == 2)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection3 = 4;
				nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z + donald3XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8))
				{
					donald3XSpeed *= -1;
					nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z + donald3XSpeed);
				}
				GhostPos3 = nextGhostPos3;
			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection3 = 3;
				nextGhostPos3 = vec3(GhostPos3.x - donald3XSpeed, GhostPos3.y, GhostPos3.z);
				if (positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8))
				{
					donald3XSpeed *= -1;
					nextGhostPos3 = vec3(GhostPos3.x - donald3XSpeed, GhostPos3.y, GhostPos3.z);
				}
				GhostPos3 = nextGhostPos3;
			}
			else if (rand_int >= 6)
			{
				GhostDirection3 = 1;
				nextGhostPos3 = vec3(GhostPos3.x + donald3XSpeed, GhostPos3.y, GhostPos3.z);
				if (positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8))
				{
					donald3XSpeed *= -1;
					nextGhostPos3 = vec3(GhostPos3.x + donald3XSpeed, GhostPos3.y, GhostPos3.z);
				}
				GhostPos3 = nextGhostPos3;
			}
		}
		else if (GhostDirection3 == 3)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection3 = 1;
				nextGhostPos3 = vec3(GhostPos3.x + donald3XSpeed, GhostPos3.y, GhostPos3.z);
				if (positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8))
				{
					donald3XSpeed *= -1;
					nextGhostPos3 = vec3(GhostPos3.x + donald3XSpeed, GhostPos3.y, GhostPos3.z);
				}
				GhostPos3 = nextGhostPos3;
			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection3 = 4;
				nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z - donald3XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8))
				{
					donald3XSpeed *= -1;
					nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z - donald3XSpeed);
				}
				GhostPos3 = nextGhostPos3;
			}
			else if (rand_int >= 6)
			{
				GhostDirection3 = 2;
				nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z + donald3XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8))
				{
					donald3XSpeed *= -1;
					nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z + donald3XSpeed);
				}
				GhostPos3 = nextGhostPos3;
			}
		}
		else if (GhostDirection3 == 4)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection3 = 2;
				nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z + donald3XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8))
				{
					donald3XSpeed *= -1;
					nextGhostPos3 = vec3(GhostPos3.x, GhostPos3.y, GhostPos3.z + donald3XSpeed);
				}
				GhostPos3 = nextGhostPos3;

			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection3 = 1;
				nextGhostPos3 = vec3(GhostPos3.x - donald3XSpeed, GhostPos3.y, GhostPos3.z);
				if (positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8))
				{
					donald3XSpeed *= -1;
					nextGhostPos3 = vec3(GhostPos3.x - donald3XSpeed, GhostPos3.y, GhostPos3.z);
				}
				GhostPos3 = nextGhostPos3;
			}
			else if (rand_int >= 6)
			{
				GhostDirection3 = 3;
				nextGhostPos3 = vec3(GhostPos3.x + donald3XSpeed, GhostPos3.y, GhostPos3.z);
				if (positionIsCollidingWallGrid(nextGhostPos3.x, nextGhostPos3.y, nextGhostPos3.z, 1.8))
				{
					donald3XSpeed *= -1;
					nextGhostPos3 = vec3(GhostPos3.x + donald3XSpeed, GhostPos3.y, GhostPos3.z);
				}
				GhostPos3 = nextGhostPos3;
			}
		}
	}

	if (GhostDirection4 == 1 || GhostDirection4 == 3)
		nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z + donald4XSpeed);
	if (GhostDirection4 == 2 || GhostDirection4 == 4)
		nextGhostPos4 = vec3(GhostPos4.x + donald4XSpeed, GhostPos4.y, GhostPos4.z );

	if (!positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8)) {
		GhostPos4 = nextGhostPos4;

		//SOUND EQUATIONS
		float distanceBetween = pow((GhostPos4.x - eye.x), 2) + pow((GhostPos4.y - eye.y), 2) + pow((GhostPos4.z - eye.z), 2);
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
		if (GhostDirection4 == 1)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection4 = 3;
				nextGhostPos4 = vec3(GhostPos4.x + donald4XSpeed, GhostPos4.y, GhostPos4.z);
				if (positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8))
				{
					donald4XSpeed *= -1;
					nextGhostPos4 = vec3(GhostPos4.x + donald4XSpeed, GhostPos4.y, GhostPos4.z);
				}
				GhostPos4 = nextGhostPos4;
			}
			else if (rand_int > 0 && rand_int <6)
			{
				GhostDirection4 = 4;
				nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z - donald4XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8))
				{
					donald4XSpeed *= -1;
					nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z - donald4XSpeed);
				}
				GhostPos4 = nextGhostPos4;
			}
			else if (rand_int >= 6)
			{
				GhostDirection4 = 2;
				nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z + donald4XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8))
				{
					donald4XSpeed *= -1;
					nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z + donald4XSpeed);
				}
				GhostPos4 = nextGhostPos4;
			}
		}
		else if (GhostDirection4 == 2)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection4 = 4;
				nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z + donald4XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8))
				{
					donald4XSpeed *= -1;
					nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z + donald4XSpeed);
				}
				GhostPos4 = nextGhostPos4;
			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection4 = 3;
				nextGhostPos4 = vec3(GhostPos4.x - donald4XSpeed, GhostPos4.y, GhostPos4.z);
				if (positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8))
				{
					donald4XSpeed *= -1;
					nextGhostPos4 = vec3(GhostPos4.x - donald4XSpeed, GhostPos4.y, GhostPos4.z);
				}
				GhostPos4 = nextGhostPos4;
			}
			else if (rand_int >= 6)
			{
				GhostDirection4 = 1;
				nextGhostPos4 = vec3(GhostPos4.x + donald4XSpeed, GhostPos4.y, GhostPos4.z);
				if (positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8))
				{
					donald4XSpeed *= -1;
					nextGhostPos4 = vec3(GhostPos4.x + donald4XSpeed, GhostPos4.y, GhostPos4.z);
				}
				GhostPos4 = nextGhostPos4;
			}
		}
		else if (GhostDirection4 == 3)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection4 = 1;
				nextGhostPos4 = vec3(GhostPos4.x + donald4XSpeed, GhostPos4.y, GhostPos4.z);
				if (positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8))
				{
					donald4XSpeed *= -1;
					nextGhostPos4 = vec3(GhostPos4.x + donald4XSpeed, GhostPos4.y, GhostPos4.z);
				}
				GhostPos4 = nextGhostPos4;
			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection4 = 4;
				nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z - donald4XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8))
				{
					donald4XSpeed *= -1;
					nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z - donald4XSpeed);
				}
				GhostPos4 = nextGhostPos4;
			}
			else if (rand_int >= 6)
			{
				GhostDirection4 = 2;
				nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z + donald4XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8))
				{
					donald4XSpeed *= -1;
					nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z + donald4XSpeed);
				}
				GhostPos4 = nextGhostPos4;
			}
		}
		else if (GhostDirection4 == 4)
		{
			rand_int = rand() % 10;
			if (rand_int == 0)
			{
				GhostDirection4 = 2;
				nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z + donald4XSpeed);
				if (positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8))
				{
					donald4XSpeed *= -1;
					nextGhostPos4 = vec3(GhostPos4.x, GhostPos4.y, GhostPos4.z + donald4XSpeed);
				}
				GhostPos4 = nextGhostPos4;

			}
			else if (rand_int > 0 && rand_int < 6)
			{
				GhostDirection4 = 1;
				nextGhostPos4 = vec3(GhostPos4.x - donald4XSpeed, GhostPos4.y, GhostPos4.z);
				if (positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8))
				{
					donald4XSpeed *= -1;
					nextGhostPos4 = vec3(GhostPos4.x - donald4XSpeed, GhostPos4.y, GhostPos4.z);
				}
				GhostPos4 = nextGhostPos4;
			}
			else if (rand_int >= 6)
			{
				GhostDirection4 = 3;
				nextGhostPos4 = vec3(GhostPos4.x + donald4XSpeed, GhostPos4.y, GhostPos4.z);
				if (positionIsCollidingWallGrid(nextGhostPos4.x, nextGhostPos4.y, nextGhostPos4.z, 1.8))
				{
					donald4XSpeed *= -1;
					nextGhostPos4 = vec3(GhostPos4.x + donald4XSpeed, GhostPos4.y, GhostPos4.z);
				}
				GhostPos4 = nextGhostPos4;
			}
		}
	}

	myDonald.draw(theta, GhostPos1);
	myDonald.draw(theta, GhostPos2);
	myDonald.draw(theta, GhostPos3);
	myDonald.draw(theta, GhostPos4);

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