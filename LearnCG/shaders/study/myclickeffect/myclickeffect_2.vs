#version 330 core
precision highp float;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;


uniform vec2 iResolution;
uniform float iTime;
out vec2 Resolution;
out vec2 TexCoord;
out float Time;


void main()
{
	float scale = 0.19 * iTime + 0.01;
	//float scale = 0.05 * iTime + 0.07;

	float aspectRatio = iResolution.x / iResolution.y;
	
	vec3 position = aPos * scale;
	gl_Position = vec4(position, 1.0) * vec4(1.0, aspectRatio, 1.0, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);

	Resolution = iResolution;
	Time = iTime;
}