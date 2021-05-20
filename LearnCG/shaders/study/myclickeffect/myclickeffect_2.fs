#version 330 core
precision highp float;
out vec4 FragColor;

in vec2 TexCoord;
in vec2 Resolution;
in float Time;
// texture samplers
uniform sampler2D backColor;
uniform sampler2D effect2;
uniform vec2 iMouse;



void main()
{
	//float aspectRatio = Resolution.y / Resolution.x;//without this, the effect will be stretched just like texture	
	//vec2 texCoord = TexCoord * vec2(1.0, aspectRatio);
	//texCoord = texCoord / vec2(1.0, aspectRatio);

	vec4 effect = texture(effect2, TexCoord);
	effect.a *= 3*(1.0 - Time);
	FragColor = effect;
	
}