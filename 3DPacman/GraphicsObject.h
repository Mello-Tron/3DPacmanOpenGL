#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <vector>
using namespace std;

#include "Angel.h"
#include <GL/glew.h> // for OpenGL extensions
#include <GL/glut.h> // for Glut utility kit
#include "texture.h" // for the bitmap texture loader

#define GL_CHECK_ERRORS \
{ \
	int err=glGetError(); \
	if (err!=0) \
	{   cout << "OpenGL Error: " << err << endl; \
		assert(err == GL_NO_ERROR); \
	} \
}

// Graphics Object Data Structure
typedef Angel::vec4 point4;

// Convert vec4 to vec3
#define vec4to3( v ) vec3(v.x,v.y,v.z)

int texture_num = GL_TEXTURE1;

class graphics_object 
{
protected:
	// Data for a graphics object
	string name; 
	vector<point4> vertex;
	vector<point4> normal;
	vector<vec2> mapcoord;


	// Arbitrary number of buffers per object, increase if you need more
	static const int MAX_BUFFERS = 30; 
	static const int MAX_UNIFORMS = 30; 

	GLuint this_texture; 

	// Shader variables for the graphics object
	GLuint program;
	GLuint vao;
	GLuint tex;
	GLuint buffers[MAX_BUFFERS];
	GLuint uniforms[MAX_UNIFORMS];
	GLuint texMapLocation;

public:
	graphics_object( string Name ) : name( Name ) { this_texture = texture_num++; };

	//MUST OVERRIDE THESE FUNCTIONS
	virtual void init_data() = 0;	     // First:  init data function to set up normal and vertex and texture map coords if applicable
	virtual void init_VAO() = 0;         // Second: init VAO function
	virtual void init_VBO() = 0;         // Third:  init VBO function
	virtual void init_shader() = 0;	     // Fourth: init shader function to set up program
	virtual void init_texture_map() = 0; // Fifth:  init texture map function

	virtual void start_shader() = 0;     // Called from Draw: Start the shader for this object
	virtual void stop_shader() = 0;      // Called from Draw: STop the shader for this object

	GLuint get_shader_id() { return program;	}
	virtual void draw() { };      // must override draw 
	virtual void cleanup() = 0;   // must provide a cleanup function

#define MIN_NUMBER 1.0E-5
#define MAX_NUMBER 1.7E308

								  // Find the intersection point on the surface of a polypatch with a ray
	GLfloat intersect(vec4 & P, vec4 & D,
		vec4 & P0, vec4 & P1, vec4 & P2,
		vec4 & N0, vec4 & N1, vec4 & N2)
	{
		vec4 Q;
		vec4 hit;
		GLfloat d, n, a, b;
		GLfloat cx, cy, cz;

		// cout << "P: " << P << " D: " << D << endl;
		// cout << "P0: " << P0 << " P1: " << P1 << "P2: " << P2 << endl;


		// Compute Bi
		vec4 B0 = (P1 - P0);
		vec4 B1 = (P2 - P0);
		vec4 B2 = normalize(cross(B0, B1));

		mat3 B = mat3(vec3(B0[0], B0[1], B0[2]), vec3(B1[0], B1[1], B1[2]), vec3(B2[0], B2[1], B2[3]));
		mat3 Bi = inverse(B);

		vec3 Bi2 = Bi[2];

		d = dot(D, Bi2);

		// reject parallel rays 
		if (fabs(d) <= MIN_NUMBER) return -MAX_NUMBER;

		Q = P0 - P;
		n = dot(Q, Bi[2]);

		GLfloat t = n / d;

		// reject rays originating on a plane containing the triangle 
		if (t <= MIN_NUMBER) return -MAX_NUMBER;

		// calculate position of intersection relative to patch origon 
		hit = (P + (t * D));

		Q = hit - P0;

		a = dot(Q, Bi[0]);
		b = dot(Q, Bi[1]);

		// reject ray as outside the patch 
		if (a < -1.0 - MIN_NUMBER) {
			return -MAX_NUMBER;
		}
		if (b < -1.0 - MIN_NUMBER) {
			return -MAX_NUMBER;
		}
		if ((a + b) > 1.0) {
			return -MAX_NUMBER;
		}

		cx = 1.0 - a - b;
		cy = a;
		cz = b;

		vec4 N = cx * N0 + cy * N1 + cz * N2;
		normalize(N);

		return t;
	}



	bool collision(GLfloat theta[], vec3 translate)
	{
		mat4 mview = modelview * Translate(translate) * Scale(0.5, 0.5, 0.5) * RotateZ(theta[0]) * RotateX(theta[1]) * RotateY(theta[1]);
		vec4 P(0.0, 0.0, 1.0, 1.0);
		vec4 D(0.0, 0.0, -1.0, 0.0);

		// Find the smallest valid t intersection with every triangle in the object
		GLfloat tmin = MAX_NUMBER;
		int imin = -1;
		for (int i = 0; i < vertex.size(); i += 3) {
			vec4 P0 = mview * vertex[i];
			vec4 P1 = mview * vertex[i + 1];
			vec4 P2 = mview * vertex[i + 2];
			vec4 N0 = mview * normal[i];
			vec4 N1 = mview * normal[i + 1];
			vec4 N2 = mview * normal[i + 2];

			GLfloat t = intersect(P, D, P0, P1, P2, N0, N1, N2);
			if (t > -0.1 && t < tmin) {
				tmin = t;
				imin = i / 3;
			}
		}
		if (imin >= -1 && tmin < 2.0) {
			cout << "Hit! triangle " << imin << " with t value of " << tmin << endl;
			return true;
		}
		else {
			cout << "Miss triangle " << imin << " with t value of " << tmin << endl;
			return false;
		}
		return false;
	}

	//Patrick
	void init() {
		init_data();
		init_VAO();
		init_VBO();
		init_shader();
		init_texture_map();
	}

};


#endif