#version 330 core

out vec4 color;

in vec3 v_Position;
in vec2 v_Tex;

uniform sampler2D u_Tex;

void main() {

    color = texture(u_Tex,v_Tex);

}