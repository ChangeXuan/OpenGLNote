// the headers

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>


// called before main loop
void init() 
{
    glClearColor(0.0, 0.0, 0.0, 0.0);   // set background color
    glEnable(GL_DEPTH_TEST);            // enable depth buffering
    glShadeModel(GL_SMOOTH);            // interpolate colors during rasterization
}

// display a frame
void display()
{
    // clear buffers
    // 清理颜色缓冲和深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 重置坐标
    glLoadIdentity(); // reset transformation

    // draw a triangle
    glBegin(GL_TRIANGLES);
	//glColor4f(1.0,0.0,0.0,1.0);
        glVertex3f(0.0, 0.0, -10.0);
	//glColor4f(0.0,1.0,0.0,1.0);
        glVertex3f(1.0, 0.0, -10.0);
	//glColor4f(0.0,0.0,1.0,1.0);
        glVertex3f(0.0, 1.0, -10.0);
    glEnd();

    // 刷新缓冲
    glutSwapBuffers(); // double buffer flush
}

// called every time window is resized to update projection matrix
// 每当窗口的大小发生变化时调用
void reshape(int w, int h)
{
    // setup image size
    // 设置渲染后的图形的显示空间，这里是整个窗口都显示
    glViewport(0, 0, w, h);
    // 将当前矩阵指定为投影矩阵
    // glMatrixMode函数其实就是对接下来要做什么进行一下声明
    glMatrixMode(GL_PROJECTION);
    // 恢复初始坐标系
    glLoadIdentity();
    
    // setup camera
    // 设置相机的位置
    // 最后两个参数为透视矩阵梯形区域的远近
    // 0.5为梯形的上顶边到相机的距离，1000.0是下底边到相机的距离
    glFrustum(-0.1, 0.1, -float(h)/(10.0*float(w)), float(h)/(10.0*float(w)), 0.5, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// entry point
int main(int argc, char **argv)
{
    
    // initialize GLUT
    // 初始化GLUT()
    glutInit(&argc, argv);
    
    // request double buffer
    // 请求缓冲
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    
    // set window size
    // 设置显示窗口的大小
    glutInitWindowSize(500, 500);
    
    // set window position
    // 设置窗口的位置
    glutInitWindowPosition(0, 0);
    
    // creates a window
    // 创建一个窗口实体，参数为名字
    glutCreateWindow("Ahahaha!");

    // initialize states
    // 初始化状态
    // 设置背景色，设置深度缓冲，设置渲染mode
    init();

    // GLUT callbacks
    // 设置响应回调
    // 当窗口发生变化时调用reshape函数
    glutReshapeFunc(reshape);
    // 当窗口内容重绘，窗口大小改变，窗口重绘时调用display
    glutDisplayFunc(display);


    // start GLUT program
    // 开始运行
    glutMainLoop();
    return 0;
}
