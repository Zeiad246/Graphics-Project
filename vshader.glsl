#version 330 core


in vec3 vertexPosition, vertexNormal;

uniform mat4 trans;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal, position;


void main()
{
    normal = mat3(transpose(inverse(trans))) * vertexNormal;
	position = vec3(trans * vec4(vertexPosition, 1.0));
    gl_Position = projection * view * trans * vec4(vertexPosition, 1.0);
    
}


