#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_Transform;

out vec3 v_Position;

void main() {

    v_Position = aPos;
    gl_Position = u_Transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);

}