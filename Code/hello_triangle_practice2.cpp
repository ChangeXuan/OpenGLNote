#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// 声明函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// 设置宽高
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// shader代码
const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"	gl_Posion = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";

int main() {

    // 初始化和配置glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 判断是否是macOS
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLTRUE);
    #endif

    // 使用glfw创建窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 设置该窗口为主上下文
    glfwMakeContextCurrent(window);
    // 设置当窗口发生变化时的回调函数
    // 第一次创建窗口时也会调用回调函数
    glfwSetFrameBufferSizeCallback(window,framebuffer_size_callback);

    // 加载全局的OpenGL函数指针
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //如果想要渲染，则至少需要一个顶点着色器和一个片段着色器
    // 创建一个顶点着色器
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 将shader代码附加到着色器对象上
    // 第二个参数是差un地源码字符串的数量
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // 编译shader源码
    glCompileShader(vertexShader)
    int success;
    char infoLog[512];
    // 获取当前的顶点着色器是否编译失败
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
    	// 获取当前顶点着色器失败的日志信息
    	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 创建一个片段着色器
    // 片段着色器所做的是计算像素最后输出的颜色
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
    	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 创建一个shader程序对象
    int shaderProgram = glCreateProgram();
    // 依次把顶点着色器和片段着色器附加到shader程序对象上
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // 连接shader程序对象上的所有shader程序
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
    	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 因为已经连接到shader程序对象
    // 所有之前的着色器可以进行删除
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 第一个三角形
    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    // 第二个三角形
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };

    // 初始化顶点缓冲对象和顶点数组对象
    unsigned int VBOs[2], VAOs[2];
    // 生成VAO对象
    glGenVertexArrays(2, VAOs);
    // 生成VBO对象
    glGenBuffers(2, VBOs);

    // 第一个三角形
    // 绑定VAO
    glBindVertexArray(VAOs[0]);
    // 把VBO绑定到GL_ARRAY_BUFFER目标上
    // 从这一刻起，我们使用任何缓冲都会用来配置当前绑定的缓冲(VBO)
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    // 把我们定义的数据刷到VBO缓冲上
    // GL_STATIC_DRAW ->	数据不会或几乎不会发生改变
    // GL_DYNAMIC_DRAW ->	数据会被改变很多
    // GL_STREAM_DRAW ->	数据每次绘制都会发生改变
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

    // 第一个参数指定我们要配置的顶点属性
    // 第一个参数中的0，对应了顶点着色器中的location
    // 第二个参数是指定顶点属性的大小
    // 第三个参数是指定顶点数据的类型
    // 第四个参数是是否标准化(0-1)
    // 第五个参数是步长
    // 第六个参数是表示位置数据在缓冲中的起始位置的偏移量
    // 该函数处理的VBO是调用该函数前绑定的GL_ARRAY_BUFFER
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    // 启用顶点属性
    glEnableVertexAttribArray(0);

    // 第二个三角形
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // 渲染主循环
    while (!glfwWindowShouldClose(window)) {
        // 外部输入
        processInput(window);

        // 渲染窗口颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 绘制三角形
        glUseProgram(shaderProgram);
        // 第一个
        glBindVertexArray(VAOs[0])
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // 第二个
        glBindVertexArray(VAOs[1])
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 使用双缓冲交换来使图片加载不突兀
        glfwSwapBuffers(window);
        // 检查有没有触发某些事件(键盘输入，鼠标移动)，更新窗口状态
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, &VAOs);
    glDeleteBbuffers(2, &VBOs);

    // 终止并释放资源
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    // 检测键盘上的esc键是否被按下
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        // 关闭当前的窗口
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // 设置openGL渲染的可见范围
    glViewport(0,0,width,height);
}