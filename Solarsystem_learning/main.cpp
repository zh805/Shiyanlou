/*
思路：
1,初始化星球对象
2.初始化OpenGL引擎，实现onDraw和onUpdate;
3.星球应该自己负责处理自己的属性,绕行关系，变换相关绘制，因此在设计星球的类时应该提供一个绘制draw()的方法；
4.星球也应该处理自己自转公转等更新显示的绘制，因此提供更新方法update();
5.在onDraw（）中应该调用星球draw()方法；
6.在onUpdate()中调用星球update()方法；
7.在onKeyboard()调整整个太阳系的显示；
*/
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "solarsystem.hpp"

//创建图形窗口的基本宏
#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 700

SolarSystem solarsystem;
 //用于注册GLUT的回调
void onDisplay(void){
  solarsystem.onDisplay();
}

void onUpdate(void){
  solarsystem.onUpdate();
}

void onKeyboard(unsigned char key,int x,int y) {
  solarsystem.onKeyboard(key,x,y);
}

int main(int argc,char* argv[]){
  glutInit(&argc,argv);    //对GLUT进行初始化，并处理所有的命令行参数
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//使用RGBA模式韩式索引模式；双缓冲窗口
  glutInitWindowPosition(WINDOW_X_POS,WINDOW_Y_POS);//设置窗口被创建时左上角位于屏幕上的位置
  glutCreateWindow("My solarsystem");//窗口的标题
  glutDisplayFunc(onDisplay);//
  glutIdleFunc(onUpdate);
  glutKeyboardFunc(onKeyboard);
  glutMainLoop();
  return 0;
}
