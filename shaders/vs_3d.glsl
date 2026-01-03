#version 400
in vec3 vertex_position;
in vec3 vertex_normal;
in vec3 vertex_colour;
uniform mat4 M;
uniform mat4 P;
uniform mat4 V;
out vec3 colour;
out vec3 Normal; 
out vec3 FragPos;
void main () 
{
 colour = vertex_colour;
 FragPos = vec3(M * vec4(vertex_position, 1.0f));
 Normal = mat3(transpose(inverse(M))) * vertex_normal;
 gl_Position = P*V*M * vec4 (vertex_position, 1.0);
}

