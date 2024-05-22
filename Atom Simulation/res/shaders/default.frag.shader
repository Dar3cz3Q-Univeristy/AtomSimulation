#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normals;
in vec4 v_FragPositionLight;

uniform vec3 u_LightPosition;
uniform vec3 u_CamPos;
uniform sampler2D u_ShadowMap;

vec4 LightColor = vec4(1.0f);

vec4 SpotLight() 
{
    // controls how big the area that is lit up is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(v_Normals);
	vec3 lightDirection = normalize(u_LightPosition - v_Position);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specular = 0.0f;
	if (diffuse != 0.0f)
	{
		float specularLight = 0.50f;
		vec3 viewDirection = normalize(u_CamPos - v_Position);
		vec3 halfwayVec = normalize(viewDirection + lightDirection);
		float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
		specular = specAmount * specularLight;
	};

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	// Shadow value
	float shadow = 0.0f;
	// Sets lightCoords to cull space
	vec3 lightCoords = v_FragPositionLight.xyz / v_FragPositionLight.w;
	if(lightCoords.z <= 1.0f)
	{
		// Get from [-1, 1] range to [0, 1] range just like the shadow map
		lightCoords = (lightCoords + 1.0f) / 2.0f;
		float currentDepth = lightCoords.z;
		// Prevents shadow acne
		float bias = max(0.00025f * (1.0f - dot(normal, lightDirection)), 0.000005f);

		// Smoothens out the shadows
		int sampleRadius = 4;
		vec2 pixelSize = 1.0 / textureSize(u_ShadowMap, 0);
		for(int y = -sampleRadius; y <= sampleRadius; y++)
		{
		    for(int x = -sampleRadius; x <= sampleRadius; x++)
		    {
		        float closestDepth = texture(u_ShadowMap, lightCoords.xy + vec2(x, y) * pixelSize).r;
				if (currentDepth > closestDepth + bias)
					shadow += 1.0f;     
		    }    
		}
		// Get average shadow
		shadow /= pow((sampleRadius * 2 + 1), 2);
	}

	return (v_Color * (diffuse * (1.0f - shadow) * inten + ambient) + v_Color.r * specular * (1.0f - shadow) * inten) * LightColor;
};

void main()
{
	color = SpotLight();
}
