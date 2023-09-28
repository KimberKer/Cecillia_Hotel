#version 330 core

out vec4 color;


in vec2 v_Tex;

uniform sampler2D u_Tex;
uniform vec2 u_TexCoordOffset;



void main() {

    vec2 newTex = v_Tex + u_TexCoordOffset;
    color = texture(u_Tex,newTex);

}