#version 120

attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoords;

varying vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoords = texCoords;
}