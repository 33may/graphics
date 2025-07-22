#version 330 core // define the version of opengl 3.3

layout (location = 0) in vec3 aPos; // location represents different chunks of data related to single vertex
layout (location = 1) in vec3 aColor; // here location = 0 represents position and location = 1 represents color
layout (location = 2) in vec2 aTex;

out vec3 color; // out means that this values will go to the next phase of rendering pipeline

out vec2 texture_coord;

uniform mat4 camMatrix;

void main(){
    gl_Position = camMatrix * vec4(aPos, 1.0f);
    color = aColor;
    texture_coord = aTex;
}
