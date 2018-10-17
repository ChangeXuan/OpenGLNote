// 使用out关键字把顶点位置输出到片段着色器，
// 并将片段的颜色设置为与顶点位置相等

// 以下为顶点shader代码
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourPosition;

void main()
{
    gl_Position = vec4(aPos, 1.0); 
    ourPosition = aPos;
}

// 以下为片段shader代码
#version 330 core
out vec4 FragColor;
in vec3 ourPosition;

void main()
{
    FragColor = vec4(ourPosition, 1.0);  