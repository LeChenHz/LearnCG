#version 330 core
precision highp float;
out vec4 FragColor;

in vec2 TexCoord;
in vec2 Resolution;
in float Time;
// texture samplers
uniform sampler2D backColor;
uniform sampler2D effect1;
uniform vec2 iMouse;



void main()
{

	vec4 effect = texture(effect1, TexCoord);
	effect.a *= 3*(1.0 - Time);
	FragColor = effect;
	
}