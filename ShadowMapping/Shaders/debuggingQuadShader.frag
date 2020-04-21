#version 450

/*Accept the texture coorindate from the vertex shader*/
in vec2 texCoord;


/*The fragment shader will output a colour of the sampled texture value*/
out vec3 outputColour;

/*Sampler objects, sort of magically work.*/
uniform sampler2D depthTexture;

void main()
{

		/*Given a texture, a sampler object samples the texture at the given coordinate*/
		/*Notice that we only extract the Red channel using ".r". This is because we have a single depth value, which gets stored there.*/
		const float sampledDepthValue = texture(depthTexture, texCoord).r;

		/*Although I am unable to explain why, giving values to be the same everywhere gives you a grayscale-like image*/
		outputColour = vec3(sampledDepthValue, sampledDepthValue, sampledDepthValue);
}