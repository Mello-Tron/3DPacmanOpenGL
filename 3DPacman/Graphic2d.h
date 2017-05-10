#ifndef GRAPHIC2D_H
#define GRAPHIC2D_H
#include "GraphicsObject.h"

typedef vec4 point4;
typedef vec4 color4;
GLint angleID2;


// Data vertices for the Tree
point4  graphic2d_vertices[8] = {
	// Quad 1
	point4(-1.0,  1.0, -3.0, 1.0),
	point4(1.0,  1.0, -3.0, 1.0),
	point4(1.0,  -1.0, -3.0, 1.0),
	point4(-1.0,  -1.0, -3.0, 1.0),
	// Quad 2
	point4(0.0,  1.0,  -4.0, 1.0),
	point4(0.0,  1.0,   -2.0, 1.0),
	point4(0.0, -1.0,   -2.0, 1.0),
	point4(0.0, -1.0,  -4.0, 1.0),
};

// RGBA colors_2d
color4 vertex_2d_vertices[4] = {
	color4(0.0, 0.0, 0.0, 1.0),  // black
	color4(1.0, 0.0, 0.0, 1.0),  // red
	color4(1.0, 1.0, 0.0, 1.0),  // yellow
	color4(0.0, 1.0, 0.0, 1.0),  // green
};

// Set up points for the quad as 8 triangles
point4 points_2d[12] = {
	graphic2d_vertices[0] , graphic2d_vertices[2],  graphic2d_vertices[1] ,  // Triangle #1
	graphic2d_vertices[3] , graphic2d_vertices[2],  graphic2d_vertices[0] ,   // Triangle #2
	graphic2d_vertices[4] , graphic2d_vertices[6],  graphic2d_vertices[5] ,  // Triangle #3
	graphic2d_vertices[7] , graphic2d_vertices[6],  graphic2d_vertices[4]    // Triangle #4
};


// Set up colors_2d for the quad as colors_2d for both triangles vertices
color4 colors_2d[12] = {
	// colors_2d for Triangle #1 vertices
	vertex_2d_vertices[0], vertex_2d_vertices[1], vertex_2d_vertices[2],
	// colors_2d for Triangle #2 vertices
	vertex_2d_vertices[0], vertex_2d_vertices[2], vertex_2d_vertices[3],
	// colors_2d for Triangle #3 vertices
	vertex_2d_vertices[0], vertex_2d_vertices[1], vertex_2d_vertices[2],
	// colors_2d for Triangle #4 vertices
	vertex_2d_vertices[0], vertex_2d_vertices[2], vertex_2d_vertices[3]
};


vec2 mapcoords_2d[12] = {
	vec2(0.0,1.0), vec2(0.5,0.0), vec2(0.5,1.0),  // Triangle #5
	vec2(0.0,0.0), vec2(0.5,0.0), vec2(0.0,1.0),  // Triangle #6
	vec2(0.0,1.0), vec2(0.5,0.0), vec2(0.5,1.0),  // Triangle #5
	vec2(0.0,0.0), vec2(0.5,0.0), vec2(0.0,1.0)  // Triangle #6

};


class graphic2d : public graphics_object
{
private:
	int textureChoice;
public:
	graphic2d() : graphics_object("tree") {
		textureChoice = 0;
	}

	graphic2d(int _textureChoice) : graphics_object("tree") {
		textureChoice = _textureChoice;
	}

	void init_data()
	{  // Data hard coded for the "tree"
	}

	void init_VAO()
	{
		// Init the VAO for this object on the graphics card
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GL_CHECK_ERRORS
	}

	void init_VBO()
	{
		// Generate buffers for the tree
		glGenBuffers(3, buffers);

	}

	void init_shader()
	{
		program = InitShader("vshader32.glsl", "fshader32.glsl");
		glUseProgram(program);
		GL_CHECK_ERRORS
			uniforms[0] = glGetAttribLocation(program, "vPosition");
		uniforms[1] = glGetAttribLocation(program, "vColor");
		uniforms[2] = glGetAttribLocation(program, "vMapCoord");
		uniforms[3] = glGetUniformLocation(program, "angle");
		uniforms[4] = glGetUniformLocation(program, "ModelView");
		uniforms[5] = glGetUniformLocation(program, "Projection");
		GL_CHECK_ERRORS

			// Buffer for the points
			glEnableVertexAttribArray(uniforms[0]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points_2d), &(points_2d[0]), GL_STATIC_DRAW);
		glVertexAttribPointer(uniforms[0], 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		GL_CHECK_ERRORS

			// Buffer for the colors_2d
			glEnableVertexAttribArray(uniforms[1]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors_2d), &(colors_2d[0]), GL_STATIC_DRAW);
		glVertexAttribPointer(uniforms[1], 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		GL_CHECK_ERRORS

			if (textureChoice > 0) {
				vec2 nothing = (0.0, 0.0);
				for (int i = 6; i < 12; i++) {
					mapcoords_2d[i] = nothing;
				}
			}

		// Buffer for the mapcoord
		glEnableVertexAttribArray(uniforms[2]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(mapcoords_2d), &(mapcoords_2d[0]), GL_STATIC_DRAW);
		glVertexAttribPointer(uniforms[2], 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		GL_CHECK_ERRORS

			// Send down the initial angle
			glUniform1f(uniforms[3], 0.0f);
		GL_CHECK_ERRORS
	}

	void init_texture_map()
	{
		glActiveTexture(this_texture);
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		if (textureChoice == 0) {
			int TreeTex = MyLoadBitmap("trees.bmp", GL_TEXTURE_2D, true);
		}
		else if (textureChoice == 1) {
			int TreeTex = MyLoadBitmap("pacmanhealth.bmp", GL_TEXTURE_2D, true);
		}
		else if (textureChoice == 2) {
			int TreeTex = MyLoadBitmap("trees3.bmp", GL_TEXTURE_2D, true);
		}

		GL_CHECK_ERRORS

			texMapLocation = glGetUniformLocation(program, "texMap");
		glUniform1i(texMapLocation, tex);
		GL_CHECK_ERRORS

			texMapLocation = glGetUniformLocation(program, "texMap");
		glUniform1i(texMapLocation, tex);
		GL_CHECK_ERRORS
	}

	void start_shader()
	{
		glBindVertexArray(vao);
		glUseProgram(program);

		glEnable(GL_TEXTURE_2D);
		glActiveTexture(this_texture);
		glBindTexture(GL_TEXTURE_2D, tex);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Prevent alpha values of less than 0.1 from writing out the the depth test buffer.
		glAlphaFunc(GL_GREATER, 0.1);
		glEnable(GL_ALPHA_TEST);

		// Initialize Z-Buffering
		glEnable(GL_DEPTH_TEST);

	}

	void stop_shader()
	{
		glUseProgram(0);
		glBindVertexArray(0);
		GL_CHECK_ERRORS
	}

	void draw(GLfloat mytheta[], vec3 translate)
	{
		start_shader();
		glDisable(GL_DEPTH_TEST);

		GLfloat myScaleX = 0.5;
		GLfloat myScaleY = 1.5;
		GLfloat myScaleZ = 0.5;

		if (textureChoice > 0) {
			//Donald!
			myScaleX = 0.5;
			myScaleY = 1.0;
			myScaleZ = 0.5;
		}

		mat4 identity = mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		mat4 typical = modelview * Translate(translate) * Scale(1.0, 1.0, 1.0) * RotateZ(mytheta[0]) * RotateX(mytheta[1]) * RotateY(mytheta[1]);

		// ship down the new the projection and viewing matrices
		glUniformMatrix4fv(uniforms[4], 1, GL_TRUE, identity * Translate(translate) * Scale(0.1, 0.2, 0.25));
		GL_CHECK_ERRORS

			glUniformMatrix4fv(uniforms[5], 1, GL_TRUE, projection);
		GL_CHECK_ERRORS

			glDrawArrays(GL_TRIANGLES, 0, sizeof(points_2d) / 3);    // draw the points
		GL_CHECK_ERRORS

			glEnable(GL_DEPTH_TEST);
			stop_shader();
	}

	void cleanup()
	{
		glDeleteProgram(program);
		glDeleteTextures(1, &tex);
		glDeleteBuffers(3, buffers);
		glDeleteVertexArrays(1, &vao);
	}


};
#endif