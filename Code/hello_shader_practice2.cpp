// 使用uniform定义一个水平偏移量，
// 在顶点着色器中使用这个偏移量把三角形移动到屏幕右侧

// 以下代码在cpp文件的渲染循环中调用
float offset = 0.5f;
ourShader.setFloat("xOffset", offset);

// 以下代码为顶点shader代码
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float xOffset;

void main()
{
    gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0); // add the xOffset to the x position of the vertex position
    ourColor = aColor;
}