#include "stars.hpp"
#include <cmath>

#define PI 3.141592635

Star::Star(GLfloat radius,GLfloat distance,GLfloat speed,GLfloat selfSpeed,Star* parent){
  this->radius = radius;
  this->selfSpeed = selfSpeed;
  this->alphaSelf = this->alpha = 0;
  this->distance = distance;

  for(int i= 0;i < 4,i++;)
    this->rgbaColor[i] = 1.0f;

  this->parentStar = parent;
  if(speed > 0)
    this->speed = 360.0f / speed;
  else
    this->speed = 0.0f;
}

void Star::drawStar(){

  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);

  int n = 1440;

  glPushMatrix();//保存OpenGL当前的工作环境
  {
    // 公转

    // 如果是行星，且距离不为0，那么 且向原点平移一个半径
    // 这部分用于处理卫星
    if (parentStar != 0 && parentStar -> distance >0){
      //将绘制的图形沿Z轴旋转alpha
      glRotatef(parentStar -> alpha,0,0,1);
      //X轴方向上平移distance,y,z 方向不变
      glTranslatef(parentStar ->distance,0.0,0.0);
    }
    //绘制运行轨道
    glBegin(GL_LINES);
    for(int i=0;i<n;++i)
      glVertex2f(distance * cos(2*PI*i/n),distance*sin(2*PI*i/n));
    glEnd();
    glRotatef(alpha,0,0,1);
    glTranslatef(distance,0.0,0.0);
    glRotatef(alphaSelf,0,0,1);
    //绘制行星颜色
    glColor3f(rgbaColor[0],rgbaColor[1],rgbaColor[2]);
    glutSolidSphere(radius,40,32);
  }
  glPopMatrix();//恢复当前矩阵环境
}

void Star::update(long timeSpan){
  alpha += timeSpan * speed;
  alphaSelf += selfSpeed;
}

Planet::Planet(GLfloat radius,GLfloat distance,GLfloat speed,
  GLfloat selfSpeed,Star* parent,GLfloat rgbaColor[3]):
  Star(radius,distance,speed,selfSpeed,parent){
    rgbaColor[0] = rgbaColor [0];
    rgbaColor[1] = rgbaColor [1];
    rgbaColor[2] = rgbaColor [2];
    rgbaColor[3] = 1.0f;
  }
//不发光的星球
void Planet::drawPlanet(){
  GLfloat mat_ambient[] = {0.0f,0.0f,0.5f,1.0f};
  GLfloat mat_diffuse[] = {0.0f,0.0f,0.5f,1.0f};
  GLfloat mat_specular[] = {0.0f,0.0f,1.0f,1.0f};
  GLfloat mat_emission[] = {rgbaColor[0],rgbaColor[1],rgbaColor[2],rgbaColor[3]};
  GLfloat mat_shininess = 90.0f;

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);
  glMaterialf(GL_FRONT,GL_SHININESS,mat_shininess);
}

LightPlanet::LightPlanet(GLfloat radius,GLfloat distance,GLfloat speed,
  GLfloat selfSpeed,Star* parent,GLfloat rgbaColor[3]):
  Planet(radius,distance,speed,selfSpeed,parent,rgbaColor){
    ;
  }

void LightPlanet::drawLight(){

  GLfloat light_position[] = {0.0f,0.0f,0.0f,1.0f};
  GLfloat light_ambient[] = {0.0f,0.0f,0.0f,1.0f};
  GLfloat light_diffuse[] = {1.0f,1.0f,1.0f,1.0f};
  GLfloat light_specular[] = {1.0f,1.0f,1.0f,1.0f};
  glLightfv(GL_LIGHT0,GL_POSITION,light_position);
  glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);

}
