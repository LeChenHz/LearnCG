#version 330 core
precision highp float;
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D back;


void main()
{
	FragColor = texture(back, TexCoord);
}