#ifndef SETUP_H
#define SETUP_H

void init_gl()
{
	glEnable(GL_DEPTH_TEST);
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Initializes all objects in world
// Edited: Patrick H. 4/17
//////////////////////////////////////////////////////////////////////////////////////////////
void init()
{
	init_gl();			    // Setup general OpenGL stuff of the object //could do all of this by creating  skybox.init function that does all 5 things

	go_skybox.init();
	wall.init();
	ground.init();
	myTree.init();
	myDonald.init();
	myDonaldClose.init();
	screenPic.init();

	view = RotateY(15) * view;//rotate eye 30 degrees
	at = eye + view;

	GL_CHECK_ERRORS
}

void checkGlew()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		cerr << "Error: " << glewGetErrorString(err) << endl;
	}
	else {
		if (GLEW_VERSION_3_3)
		{
			cout << "Driver supports OpenGL 3.3\nDetails:" << endl;
		}
	}
	cout << "Using GLEW " << glewGetString(GLEW_VERSION) << endl;
	cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
	cout << "Version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

#endif