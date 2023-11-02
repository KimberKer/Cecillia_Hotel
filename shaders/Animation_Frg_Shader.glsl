#version 330 core

out vec4 color;

in vec3 v_Position;
in vec2 v_Spr;

uniform sampler2D u_Spr;
uniform int currentFrame;
uniform int numFrames;
uniform float frameWidth;

void main() {

    color = texture(u_Tex,v_Tex);

    // Calculate the current frame based on the time or other animation logic
    // Calculate the texture coordinates for the current frame
    vec2 frameOffset = vec2(float(currentFrame) * frameWidth, 0.0);
    vec2 adjustedTexCoord = v_Spr * vec2(1.0 / float(numFrames), 1.0) + frameOffset;

    // Sample the sprite sheet using the adjusted texture coordinates
    color = texture(u_Spr, adjustedTexCoord);


}