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

	go_skybox.init_data();	        // Setup the data for the this object
	go_skybox.init_VAO();           // Initialize the vertex array object for this object
	go_skybox.init_VBO();			// Initialize the data buffers for this object
	go_skybox.init_shader();		// Initialize the shader objects and textures for skybox
	go_skybox.init_texture_map();	// Initialize the texture map for this object

	wall.init_data();
	wall.init_VAO();
	wall.init_VBO();
	wall.init_shader();
	wall.init_texture_map();

	ground.init_data();
	ground.init_VAO();
	ground.init_VBO();
	ground.init_shader();
	ground.init_texture_map();

	myTree.init_data();
	myTree.init_VAO();
	myTree.init_VBO();
	myTree.init_shader();
	myTree.init_texture_map();

	myDonald.init_data();
	myDonald.init_VAO();
	myDonald.init_VBO();
	myDonald.init_shader();
	myDonald.init_texture_map();

	myDonaldClose.init_data();
	myDonaldClose.init_VAO();
	myDonaldClose.init_VBO();
	myDonaldClose.init_shader();
	myDonaldClose.init_texture_map();

	//Initialize all the wall objects for the maze
	//for (int i = 0; i < walls.size(); i++) {
	//	walls[i]->init_data();	     
	//	walls[i]->init_VAO();          
	//	walls[i]->init_VBO();			
	//	walls[i]->init_shader();		
	//	walls[i]->init_texture_map();	
	//}

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