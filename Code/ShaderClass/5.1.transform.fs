#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// 0.2表示，第一张贴图占80%，第二张占20%
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}