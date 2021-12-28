#version 310 es
#extension GL_EXT_texture_buffer : enable
precision highp float;
precision lowp samplerBuffer;
precision lowp isamplerBuffer;
precision lowp usamplerBuffer;
precision lowp imageBuffer;
precision lowp uimageBuffer;
precision lowp iimageBuffer;
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
//uniform sampler2D Texture;
uniform vec2 iResolution;
uniform float u_Boundary;

//uniform samplerBuffer texture;
uniform int offset;

//image buffer
layout (rgba8,binding=0) uniform imageBuffer texture;
layout (rgba8,binding=1) uniform imageBuffer texture1;

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
	//FragColor = normalize(texelFetch(texture, 0));
	//FragColor = vec4(texelFetch(texture, 0));
	//if(FragColor.r > 50.0)
	//{
	//	FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	//}
	//else
	//{
	//	FragColor = vec4(0.0, 0.0, 1.0, 1.0);
	//}
	//imageStore(texture, 0, vec4(1.0, 0.0, 0.0, 1.0));
	FragColor = imageLoad(texture, 0);
}

//void main()
//{
//
//	float aspectRatio = iResolution.y / iResolution.x;//without this, the effect will be stretched just like texture
//	
//	vec2 texCoord = TexCoord * vec2(1.0, aspectRatio);
//
//	for(int i = 0; i < renderingNum; i++)
//	{
//		vec2 position = vec2(p[i].x, p[i].y);
//		vec2 imouse = (position.xy / iResolution.xy) * vec2(1.0, aspectRatio); 
//		float distance = distance(texCoord, imouse);
//		float iTime = p[i].iTime;
//		if((iTime - u_Boundary) > 0.0 && (distance <= (iTime + u_Boundary) && (distance >= (iTime - u_Boundary))))
//		{
//			float diff = (distance - iTime);
//			//float moveDis = - pow(8 * diff, 3.0);
//			float moveDis = 20.0 * diff * (diff - 0.1) * (diff + 0.1);
//			vec2 unitDirctionVec = normalize(texCoord - imouse);
//			texCoord = texCoord + (unitDirctionVec * moveDis);
//		}
//	}
//
//	texCoord = texCoord / vec2(1.0, aspectRatio);
//	FragColor = texture(Texture, texCoord);
//	//FragColor = vec4(p[0].iTime, 0.0, 0.0, 1.0);
//	
//}