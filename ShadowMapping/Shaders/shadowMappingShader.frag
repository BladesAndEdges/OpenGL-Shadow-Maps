#version 450


// Simply put, this shader implements the shadow mapping technique, and simple Phong lighting. 
// Specular lighting was ignored, since I tought it was not neccessary if the light never moves place. 

in vec3 surfaceColour;
in vec3 normalizedNormalInWorldSpace;
in vec2 texCoord;

in vec4 fragPositionInLightSpace;

//Layout 140 is a memory layout standard. The standard is a set of rules on how data becomes padded etc.
layout (std140, binding = 0) uniform ubo
{
	mat4 model;
	mat4 viewProjection;
	mat4 lightSpaceMatrix;
	vec4 toLightDirection;
};

out vec3 outputColour;

uniform sampler2D shadowMap;

void main()
{
	
	/*Takes us into clip space between [-1,1]*/
	const vec3 normalizedFragPosition = fragPositionInLightSpace.xyz / fragPositionInLightSpace.w;

	/*Gets a shadow map coordinate, within [0,1]*/
	float fragmentDepth = (normalizedFragPosition.z * 0.5) + 0.5;
	const vec2 shadowMapTexCoord = (normalizedFragPosition.xy * 0.5) + 0.5;

	/*A bias value is used for ???*/
	const float biasValue = 0.005f;

	/*Sample the shadow map, using the value in xy*/
	const float depthStored = texture(shadowMap, shadowMapTexCoord.xy).r + biasValue;

	/*Check if the fragment is in shadow or not, by comparing the value stored in the shadow map is less than the z value of the fragment*/
	const float isShadowed = depthStored > fragmentDepth ? 1.0f : 0.0f;

	/*White light*/
	const vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);

	/*Ambient intensity*/
	const float ambientIntensity = 0.2f;

	const vec3 ambient = ambientIntensity * lightColour;

	const vec3 ambientTerm = ambient * surfaceColour;


	/*Diffuse*/

	/*The result from the dot product for diffuse computation*/
	float diffuseDotProduct = max(dot( vec3(toLightDirection), normalizedNormalInWorldSpace), 0.0f);

	/*The diffuse lighting*/
	vec3 diffuseTerm = diffuseDotProduct * surfaceColour;


	/*The final colour is determined by weather the fragment is in shadow or not*/
	/*If it is in shadow, it will get multiplied by vec3(0.0f, 0.0f, 0.0f) and appear fully black*/
	outputColour = isShadowed * (ambientTerm + diffuseTerm);
}