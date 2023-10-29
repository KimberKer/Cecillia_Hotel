#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aSpr;

uniform mat4 u_Transform;

out vec3 v_Position;
out vec2 v_Spr;

void main() {

    v_Position = aPos;
    v_Spr = aSpr;
    gl_Position = u_Transform * vec4(aPos, 1.0);

}