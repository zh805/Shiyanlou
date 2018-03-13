#ifndef stars_hpp
#define stars_hpp

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

class Star{
public:
  GLfloat radius;//运行半径
  GLfloat speed,selfSpeed;//公转 自转速度
  GLfloat distance;//星球中心与父节点星球中心的距离
  GLfloat rgbaColor[4];//星球的颜色

  Star* parentStar;//父节点颜色

  Star(GLfloat radius,GLfloat distance,GLfloat speed,//构造函数
       GLfloat selfSpeed,Star* parent);

  void drawStar();//对一般的星球的移动 旋转等活动进行绘制

  virtual void draw(){
    drawStar();//提供默认实现 负责调用drawStar()
  }

  virtual void update(long timeSpan);//参数为每次刷新画面时的时间跨度

protected:
  GLfloat alphaSelf, alpha;
};//当前的自转角度  公转角度

class  Planet:public Star{
public:
  Planet(GLfloat radius,GLfloat distance,
    GLfloat speed,GLfloat selfSpeed,
    Star* parent,GLfloat rgbaColor[3]);

void drawPlanet();//增加对具备自身材质的行星绘制材质

virtual void draw(){
  drawPlanet(); drawStar();}//继续向其子类开放重写功能

};

class LightPlanet:public Planet{
public:
  LightPlanet(GLfloat Radius,GLfloat Distance,
    GLfloat Speed,GLfloat SelfSpeed,
    Star* Parent,GLfloat rgbaColor[]);

  void drawLight();//增加对提供光源的恒星绘制光照
  virtual void draw(){
    drawLight();drawPlanet();drawStar();
  }
};

#endif
