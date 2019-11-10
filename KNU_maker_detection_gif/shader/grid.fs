#version 130

in vec3 outColor;
// Output data
out vec4 color;

uniform sampler2D textureSampler;

void main() {
	// Output color = red 
	//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	color = vec4(outColor, 1.0f);
	//color = texture(textureSampler, UV).rgb;
}
