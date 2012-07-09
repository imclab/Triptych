#version 120 
uniform mat4 u_modelview_matrix;
uniform mat4 u_projection_matrix;
attribute vec4 a_pos;
attribute vec3 a_norm;

varying vec3 v_norm;

void main() {
	gl_Position = u_projection_matrix * u_modelview_matrix * a_pos;
	v_norm = a_norm;
}