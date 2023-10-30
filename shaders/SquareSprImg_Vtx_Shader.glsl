#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

uniform mat4 u_Transform;

out vec2 TexCoord;

void main() {

    //gl_Position = vec4(vertex_position.x + x_dir - 0.5, vertex_position.y + y_dir - 0.5, 0.0, 1.0);
    gl_Position = u_Transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    TexCoord = aTex;

}