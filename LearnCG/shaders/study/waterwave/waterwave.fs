#version 330 core
precision highp float;
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D Texture;
uniform vec2 iResolution;
uniform float u_Boundary;

#define MAX_SIZE 12
struct ClickEffectParams{
	float iTime;
	int x;
	int y;
};

uniform ClickEffectParams p[MAX_SIZE];
uniform int renderingNum;
uniform float test;


void main()
{

	float aspectRatio = iResolution.y / iResolution.x;//without this, the effect will be stretched just like texture
	
	vec2 texCoord = TexCoord * vec2(1.0, aspectRatio);

	for(int i = 0; i < renderingNum; i++)
	{
		vec2 position = vec2(p[i].x, p[i].y);
		vec2 imouse = (position.xy / iResolution.xy) * vec2(1.0, aspectRatio); 
		float distance = distance(texCoord, imouse);
		float iTime = p[i].iTime;
		if((iTime - u_Boundary) > 0.0 && (distance <= (iTime + u_Boundary) && (distance >= (iTime - u_Boundary))))
		{
			float diff = (distance - iTime);
			//float moveDis = - pow(8 * diff, 3.0);
			float moveDis = 20.0 * diff * (diff - 0.1) * (diff + 0.1);
			vec2 unitDirctionVec = normalize(texCoord - imouse);
			texCoord = texCoord + (unitDirctionVec * moveDis);
		}
	}

	texCoord = texCoord / vec2(1.0, aspectRatio);
	FragColor = texture(Texture, texCoord);
	//FragColor = vec4(p[0].iTime, 0.0, 0.0, 1.0);
	
}