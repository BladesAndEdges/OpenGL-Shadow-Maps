#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inRGB;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord;


//Layout 140 is a memory layout standard. The standard is a set of rules on how data becomes padded etc.
layout (std140, binding = 0) uniform ubo
{
	mat4 model;
	mat4 viewProjection;
	mat4 lightSpaceMatrix;
	vec4 toLightDirection;
};

out vec3 surfaceColour;
out vec3 normalizedNormalInWorldSpace;
out vec2 texCoord;

out vec4 fragPositionInLightSpace;

void main()
{
	gl_Position = viewProjection * model * vec4(inPosition, 1.0);

	surfaceColour = inRGB;

	/*Get the correct world space normal, but keep in mind the model matrix has a scale applied*/
	vec3 normalInWorldSpace = mat3(model) * inNormal;
	normalizedNormalInWorldSpace = normalize(normalInWorldSpace);

	texCoord = inTexCoord;

	fragPositionInLightSpace = lightSpaceMatrix * model * vec4(inPosition, 1.0f);


}