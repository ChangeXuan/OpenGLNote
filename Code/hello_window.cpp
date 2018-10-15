// OPENGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// CPP
#include <iostream>

// 声明函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// 设置宽高
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

    // 渲染主循环
    while (!glfwWindowShouldClose(window)) {
        // 外部输入
        processInput(window);

        // 渲染窗口颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 使用双缓冲交换来使图片加载不突兀
        glfwSwapBuffers(window);
        // 检查有没有触发某些事件(键盘输入，鼠标移动)，更新窗口状态
        glfwPollEvents();
    }

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