#version 330 core

#define PI 3.141592653589793

#define EXPLOSION_COUNT 1.0
#define SPARKS_PER_EXPLOSION 256.0
#define EXPLOSION_DURATION 15.0
#define EXPLOSION_SPEED 15.0
#define EXPLOSION_RADIUS_THESHOLD 0.02

#define MOD3 vec3(0.1031, 0.11369, 0.13787)

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
// texture samplers
uniform sampler2D Texture;
uniform vec2 iResolution;
uniform float iTime;
uniform vec2 iMouse;
uniform bool render;

vec3 hash(float p)
{
	vec3 p3 = fract(vec3(p) * MOD3);
    p3 += dot(p3, p3.yzx + 19.19);
    return fract(vec3((p3.x + p3.y) * p3.z, (p3.x + p3.z) * p3.y, (p3.y + p3.z) * p3.x));
}

void main()
{
	float aspectRatio = iResolution.x / iResolution.y;
	vec2 uv = gl_FragCoord.xy /  iResolution.y;
	float t = mod(iTime + 10.0, 7200.0);
	vec3 col =vec3(0.0);
	vec2 origin = vec2(0.0);
	//if(render)
	//{
	for(float j = 0.; j < EXPLOSION_COUNT; ++j)
	{
		vec3 oh = hash((j + 1234.1939) * 641.6974);
		//origin = vec2(oh.x, oh.y) * 0.6 + 0.2;
		origin = iMouse.xy / iResolution.xy;
		origin.y = 1.0 - origin.y;
		origin.x *= aspectRatio;

		//test 1  Ö±½Ót ¾²Ö¹
		t += (j + 1.0) * 9.6491 * oh.z;
		for(float i = 0.; i < SPARKS_PER_EXPLOSION; ++i)
		{
			//test 2
			vec3 h = hash(j * 963.31 + i + 497.8943);
			float a = h.x * PI * 2.0;//random angle
			float rScale = h.y * EXPLOSION_RADIUS_THESHOLD; // radius scale
			//loop based on time
			if(mod(t * EXPLOSION_SPEED, EXPLOSION_DURATION) > 2.0)
			{
				float r = mod(t * EXPLOSION_SPEED, EXPLOSION_DURATION) * rScale;
				vec2 sparkPos = vec2(r * cos(a), r * sin(a));
				sparkPos.y -= pow(max(0.0, sparkPos.x), 4.0); //fake gravity

				//test 3
				float spark = 0.0002/pow(max(0.0, length(uv - sparkPos - origin)), 1.65);

				float sd = 2.0 * length(origin-sparkPos);
                float shimmer = max(0.0, sqrt(sd) * (sin((t + h.y * 2.0 * PI) * 20.0)));
                float shimmerThreshold = EXPLOSION_DURATION * 0.32;

				float fade = max(0.0, (EXPLOSION_DURATION - 5.0) * rScale - r);

				//oh -- color
				vec3 m_color = hash(iTime);
				col += mix(spark, shimmer * spark, smoothstep(shimmerThreshold * rScale, (shimmerThreshold + 1.0) * rScale , r)) * fade * m_color;
			}
		}
	}
	//}
	//col = max(vec3(0.1), col);
	//col += vec3(0.12, 0.06, 0.02) * (1.0 - uv.y);
	FragColor = vec4(col, 1.0) + texture(Texture, TexCoord);

	//FragColor = texture(Texture, TexCoord);
}