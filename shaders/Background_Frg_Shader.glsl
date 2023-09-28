#version 330 core

out vec4 color;

in vec3 v_Position;
in vec2 v_Tex;

uniform sampler2D u_Tex;
uniform float u_Cols;
uniform float u_Rows;


void main() {

    vec2 newTex = vec2 (v_Tex.x * u_Cols, v_Tex.y*u_Rows);
    color = texture(u_Tex,newTex);

}