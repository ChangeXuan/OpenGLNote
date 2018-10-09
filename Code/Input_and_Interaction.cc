#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

// 正方体的顶点数据
GLFloat vertices[8][3] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0},
                          {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, 
                          {-1.0, -1.0, 1.0},{1.0, -1.0, 1.0}, 
                          {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}}; 
// 各顶点的颜色数据
GLfloat colors[8][3] = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
                        {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, 
                        {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, 
                        {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};

void myReshape(int w,int h) {
    GLFloat aspect = (Glfloat)w/(GLfloat)h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w<=h) {
        glOrtho(-2.0,2.0,-2.0/aspect,2.0/aspect,-10.0,10.0);
    } else {
        glOrtho(-2.0*aspect,2.0*aspect,-2.0,2.0,-10.0,10.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

// 使用色彩数组和顶点数组来构建一个多边形
void face(int a,int b,int c) {
    glBegin(GL_POLYGON);
        glColor3f(colors[a]);
        glVertex3f(vertices[a]);
        glColor3fv(colors[b]);
        glVertex3fv(vertices[b]);
        glColor3fv(colors[c]);
        glVertex3fv(vertices[c]);
        glColor3fv(colors[d]);
        glVertex3fv(vertices[d]); 
    glEnd();
}
// 构建一个彩色立方体
void colorcube(void) {
    face(0,3,2,1);
    face(2,3,7,6);
    face(0,4,7,3);
    face(1,2,6,5);
    face(4,5,6,7);
    face(0,1,5,4); 
}
// 表示三个轴的旋转角度
GLFloat theta[3] = {0.0,0.0,0.0};
void display(void) {
    glClear(CL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);
    colorcube();
    glutSwapBuffers()
}

// 默认旋转速度的参数
GLfloat delta = 2.0;
// 默认旋转的轴
GLint axis = 2;
void spinCube(void) {
    theta[axis] += delta;
    if (theta[axis] > 360.0) {
        theta[axis] -= 360.0;
    }
    //重新渲染
    glutPostRedisplay();
}

// 鼠标操作
void mouse(int btn,int state,int x,int y) {
    // 左键按下
    if ((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        axis = 0;
    }
    // 中键按下
    if ((btn == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN)) {
        axis = 1;
    }
    //右键按下
    if ((btn == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
        axis = 2;
    }
}

bool stop = false;
// 键盘操作
void keyboard(unsigned char key,int x,int y) {
    // 输入q或Q退出
    if (key == 'q' || key == 'Q') {
        exit(0);
    }
    // 按空格改变标志量
    if (key == ' ') {
        stop = !stop;
    }
    // 使用标志量来判断是否进行旋转动画
    if (stop) {
        glutIdleFunc(NULL);
    } else {
        glutIdleFunc(spinCube);
    }
}

int main(int argc,char **argv) {
    glutInit(&argc ,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    glutInitWindowSize(500,500);
    glutCreateWindow("Cube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display)
    glutIdleFunc(spinCube);
    // 鼠标响应
    glutMouseFunc(mouse);
    // 键盘响应
    glutKeyboardFunc(keyboard);

    // enable depth buffering
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
