#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

uniform mat4 u_Transform;




out vec2 v_Tex;

void main() {

    v_Tex = aTex;
    gl_Position = u_Transform * vec4(aPos, 1.0);

}