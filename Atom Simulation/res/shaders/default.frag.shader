#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normals;

const int MAX_ELECTRON_COUNT = 100;	// Keep number of electrons up to date in Specification.h

uniform int u_ElectronCount;
uniform vec3 u_MultipleLightPos[MAX_ELECTRON_COUNT];
uniform vec3 u_MultipleLightColor[MAX_ELECTRON_COUNT];
uniform vec3 u_CamPos;

const float ambient = 0.10f;
const float specularLight = 0.50f;

vec3 PhongLight(vec3 normal, vec3 lightPosition, vec3 lightColor) 
{
    vec3 lightDirection = normalize(lightPosition - v_Position);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.30f;
	vec3 viewDirection = normalize(u_CamPos - v_Position);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

    return v_Color.rgb * lightColor * (diffuse + ambient + specular);
};

void main() 
{
    vec3 normal = normalize(v_Normals);

    vec3 result = vec3(0.0f);

    for(int i = 0; i < u_ElectronCount; i++) 
        result += PhongLight(normal, u_MultipleLightPos[i], u_MultipleLightColor[i]);

    color = vec4(result, 1.0f);
};
