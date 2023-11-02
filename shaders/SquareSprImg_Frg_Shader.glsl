#version 330 core

uniform float uv_x;
uniform float uv_y;
uniform float nx_frames;
uniform float ny_frames;


in vec2 TexCoord;
out vec4 frag_color;


uniform sampler2D u_Tex;

void main(){

    float x = 1.0 / nx_frames;
    float y = 1.0 / ny_frames;
    frag_color = texture(u_Tex, TexCoord * vec2(x, y) + vec2(x * uv_x, y * uv_y));
    //frag_color = texture(imgTexture, vec2((TexCoord.x * x) + x * uv_x), (TexCoord.y * y) + y * uv_y);
    //frag_color = texture(imgTexture, vec2((TexCoord / noOfCols) + colIndex), (TexCoord / noOfRows) + rowIndex));
    
}