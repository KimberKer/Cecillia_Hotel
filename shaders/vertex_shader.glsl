#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 u_Transform;

out vec3 v_Position;
out vec4 v_Color;


void main() {

    v_Position = aPos;
    v_Color = aColor;
    gl_Position = u_Transform * vec4(aPos, 1.0);

}