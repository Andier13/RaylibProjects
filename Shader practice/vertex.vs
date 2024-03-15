#version 400

in vec4 gl_Vertex;

flat out dvec4 gl_Position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * gl_Vertex;
}