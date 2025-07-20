#version 330 core

out vec4 FragColor;

in vec3 color; // same name as the out from previous step \

in vec2 texture_coord;

uniform sampler2D tex0;

void main(){
    FragColor = texture(tex0, texture_coord);
}
