# lab01-opengl-drawing 实验考点与编程专项练习

---

## 一、 核心知识点整理

### 1.1 OpenGL 点的绘制
- **基本渲染框架**: 在 GLUT 窗口系统下，通过 `glutDisplayFunc` 注册回调函数进行重绘。
- **清除屏幕与缓冲区**: `glClearColor(r, g, b, a)` 设置清屏颜色，`glClear(GL_COLOR_BUFFER_BIT)` 执行清空。
- **基本几何点绘制**: `glPointSize(size)` 设置点尺寸，`glBegin(GL_POINTS)` 和 `glEnd()` 包围顶点坐标函数 `glVertex2f(x, y)` 进行渲染。

### 1.2 OpenGL 像素位置
- **绘制四边形与三角形**:
  - `glBegin(GL_QUADS)`: 依次指定四个顶点顺时针或逆时针绘制一个凸四边形。
  - `glBegin(GL_TRIANGLES)`: 依次指定三个顶点绘制三角形。
- **色彩模式设置**:
  - `glShadeModel(GL_FLAT)`: 单色平坦着色模式，多边形颜色由最后一个顶点决定。
  - `glShadeModel(GL_SMOOTH)`: 平滑着色（双线性颜色插值）模式，多边形内部过渡平滑，顶点的颜色渐变。

### 1.3 OpenGL 线段绘制
- **快捷图元绘制**: `glRectf(x1, y1, x2, y2)` 直接绘制对角顶点为 $(x1, y1)$ 和 $(x2, y2)$ 的矩形。
- **线段绘制**: `glBegin(GL_LINES)` 用于绘制独立线段，每两个顶点组成一条直线段。
- **强制硬件刷新**: `glFlush()` 刷新渲染管线，确保单缓冲模式下的图形命令立即送显。

---

## 二、 编程填空专项练习

### 1.1 OpenGL 点的绘制练习

```cpp
#include <GL/freeglut.h>

void init(void)
{
    (1) // 设置背景清屏颜色为黑色
    (2) // 设置绘制点的直径为 3 像素
}

void display(void)
{
    (3) // 清空颜色缓冲区
    (4) // 开启点图元绘制
    glColor3f(1.0f, 0.0f, 0.0f); // 红色
    glVertex2f(0.0f, 0.0f); // 原点
    glEnd();
    glFlush();
}
```

**1.** (1) 处需要补充的设置清屏颜色的代码为：（　　）

A）`glClearColor(0.0f, 0.0f, 0.0f, 0.0f);`　　B）`glClear(GL_COLOR_BUFFER_BIT);`  
C）`glPointSize(3.0f);`　　D）`glFlush();`

**2.** (2) 处需要补充的设置点大小的代码为：（　　）

A）`glLineWidth(3.0f);`　　B）`glPointSize(3.0f);`  
C）`glViewport(0, 0, 3, 3);`　　D）`glBegin(GL_POINTS);`

**3.** (3) 处清除颜色缓存的代码为：（　　）

A）`glFlush();`　　B）`glClear(GL_COLOR_BUFFER_BIT);`  
C）`glClear(GL_DEPTH_BUFFER_BIT);`　　D）`glutSwapBuffers();`

**4.** (4) 处开启点绘制的函数代码为：（　　）

A）`glBegin(GL_POINTS);`　　B）`glBegin(GL_LINES);`  
C）`glBegin(GL_POLYGON);`　　D）`glBegin(GL_QUADS);`

---

### 1.2 OpenGL 像素位置练习

```cpp
#include <GL/freeglut.h>

void myDisplay(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 绘制一个白色的对角顶点为 (-0.5, -0.5) 和 (0.5, 0.5) 的正方形
    glColor3f(1.0f, 1.0f, 1.0f);
    (5) // 开启四边形绘制
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f(-0.5f,  0.5f);
    (6) // 结束绘制
    
    // 开启平滑渐变插值着色，绘制一个红-绿-蓝三色渐变的三角形
    (7) // 设置着色模型为平滑过渡模式
    (8) // 开启三角形绘制
    glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.8f, -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.8f, -0.5f);
    glEnd();
    
    glFlush();
}
```

**5.** (5) 处需要补充的图元开始代码为：（　　）

A）`glBegin(GL_TRIANGLES);`　　B）`glBegin(GL_QUADS);`  
C）`glBegin(GL_POLYGON);`　　D）`glBegin(GL_LINES);`

**6.** (6) 处配合结束图形绘制的函数代码为：（　　）

A）`glFlush();`　　B）`glEnd();`　　C）`glFinish();`　　D）`glutPostRedisplay();`

**7.** (7) 处指定平滑着色模型的函数代码为：（　　）

A）`glShadingModel(GL_FLAT);`　　B）`glShadingModel(GL_SMOOTH);`  
C）`glShadingModel(GL_SMOOTH_SHADE);`　_D）`glEnable(GL_SMOOTH);`

**8.** (8) 处开始绘制三角形的图元定义代码为：（　　）

A）`glBegin(GL_TRIANGLES);`　　B）`glBegin(GL_TRIANGLE_STRIP);`  
C）`glBegin(GL_POLYGON);`　　D）`glBegin(GL_LINES);`

---

### 1.3 OpenGL 线段绘制练习

```cpp
#include <GL/freeglut.h>

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 1. 绘制一个红色矩形，对角顶点为 (25, 25) 和 (75, 75)
    glColor3f(1.0f, 0.0f, 0.0f);
    (9) // 调用矩形快捷绘制API
    
    // 2. 绘制一个绿色的粗点，大小为 10，坐标为 (0, 0)
    glPointSize(10.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);
    (10) // 顶点坐标
    glEnd();
    
    // 3. 绘制一条绿色的线段，两端点为 (100, 0) 和 (180, 240)
    (11) // 开启线段图元绘制
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(100.0f, 0.0f);
    glVertex2f(180.0f, 240.0f);
    glEnd();
    
    (12) // 强制执行缓存区管线命令刷新
}
```

**9.** (9) 处需要补充的矩形快捷绘制代码为：（　　）

A）`glRectf(25.0f, 25.0f, 75.0f, 75.0f);`　　B）`glDrawRect(25, 25, 75, 75);`  
C）`glBegin(GL_QUADS);`　　D）`glViewport(25, 25, 75, 75);`

**10.** (10) 处绘制顶点的坐标代码为：（　　）

A）`glVertex3f(0.0, 0.0, 0.0);`　　B）`glVertex2f(0.0f, 0.0f);`  
C）`glVertex2i(0, 0);`　　D）`以上均可`

**11.** (11) 处需要选择的绘制线段图元命令为：（　　）

A）`glBegin(GL_LINES);`　　B）`glBegin(GL_LINE_STRIP);`  
C）`glBegin(GL_LINE_LOOP);`　　D）`glBegin(GL_POINTS);`

**12.** (12) 处使命令立即送往硬件渲染的刷新指令为：（　　）

A）`glFinish();`　　B）`glFlush();`　　C）`glutSwapBuffers();`　　D）`glLoadIdentity();`

---

## 三、 答案与解析

### 1.1 练习解析
**1.** 答案：A  
解析：`glClearColor(r, g, b, a)` 是用来设置清屏时被写入的背景颜色的，黑色对应红绿蓝通道均为 0。  
**2.** 答案：B  
解析：OpenGL 使用 `glPointSize` 设置点大小，使用 `glLineWidth` 设置线宽。  
**3.** 答案：B  
解析：`glClear(GL_COLOR_BUFFER_BIT)` 用于将屏幕上的颜色信息清空，重置为 `glClearColor` 设置的背景色。  
**4.** 答案：A  
解析：绘制离散点选择的图元类型标志是 `GL_POINTS`。

### 1.2 练习解析
**5.** 答案：B  
解析：画四边形应该使用 `GL_QUADS` 作为 `glBegin` 的参数类型。  
**6.** 答案：B  
解析：`glBegin` 和 `glEnd` 必须成对出现，用来包裹顶点函数群。  
**7.** 答案：B  
解析：设置 Gouraud 双线性平滑颜色渐变模式使用 `glShadingModel(GL_SMOOTH)`，单色则是 `GL_FLAT`。  
**8.** 答案：A  
解析：绘制独立的三角形要传入图元类型 `GL_TRIANGLES`。

### 1.3 练习解析
**9.** 答案：A  
解析：`glRectf(x1, y1, x2, y2)` 是快速绘制平行于坐标轴的矩形实心图形的函数。  
**10.** 答案：D  
解析：绘制点可以使用 $x, y$ 两个参数的 float 型，亦可以使用带 $z$ 轴的三参数版 `3f` 或整数版 `2i`，它们都能将顶点定位于原点。  
**11.** 答案：A  
解析：`GL_LINES` 会把每两个顶点解释为一条线段，而 `GL_LINE_STRIP` 会串联成折线。  
**12.** 答案：B  
解析：在单缓冲渲染中，通常使用 `glFlush()` 强制发出指令。
