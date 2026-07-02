# lab07-3d-modeling 实验考点与编程专项练习

---

## 一、 核心知识点整理

### 7.1 观察矩阵视角设置 (gluLookAt)
- **相机的概念**: 将相机移到某个位置看往某个焦点，相机的参数决定了物体的摆放视图。
- **gluLookAt 参数含义**:
  - `(eyex, eyey, eyez)`: 视点相机坐标位置。
  - `(centerx, centery, centerz)`: 看向的目标焦点位置。
  - `(upx, upy, upz)`: 相机竖直朝上的朝向向量（默认多为 $Y$ 轴正方向 `(0.0, 1.0, 0.0)`）。

### 7.2 几何形体产生 (二次曲面与球体)
- **二次曲面库 (GLU Quadrics)**:
  - OpenGL 无法直接绘制曲面结构，需要借助二次曲面指针变量。
  - **步骤**:
    1. 分配状态指针：`GLUquadricObj* sphere = gluNewQuadric();`
    2. 执行曲面渲染：`gluSphere(sphere, radius, slices, stacks)`（定义半径、切片和高度网格线条数）。
    3. 销毁防止泄漏：`gluDeleteQuadric(sphere)`。

---

## 二、 编程填空专项练习

### 7.1 Viewpoint 观察相机位置练习

```cpp
#include <GL/freeglut.h>

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // 1. 设置观察相机：位置点位于 (0, 0, 5)，看向原点 (0, 0, 0)，
    // 相机自身正上方向量指向 Y 轴正半轴 (0.0, 1.0, 0.0)
    (1)
    
    // 2. 绘制一个大小为 1.0 的网格线框茶壶
    glColor3f(1.0f, 0.0f, 0.0f); // 红色线框
    (2)
    
    glutSwapBuffers();
}
```

**1.** (1) 处需要填入的视点观察矩阵设置代码为：（　　）

A）`gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 5.0, 0.0, 1.0, 0.0);`  
B）`gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);`  
C）`gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);`  
D）`glViewport(0, 0, 5, 0);`

**2.** (2) 处绘制线框茶壶的内置 GLUT 函数为：（　　）

A）`glutSolidTeapot(1.0);`　　B）`glutWireTeapot(1.0);`  
C）`glutWireSphere(1.0, 20, 20);`　　D）`glutWireCube(1.0);`

---

### 7.2 GLU 二次曲面球体生成练习

```cpp
#include <GL/freeglut.h>

void drawSphere(void)
{
    // 3. 申请分配二次曲面对象指针
    GLUquadricObj* quad = (3);
    
    glColor3f(0.0f, 1.0f, 1.0f); // 青色
    
    // 4. 渲染一个球体，半径为 2.0f，横纵网格细分密度都为 30
    (4)
    
    // 5. 释放释放曲面对象占用的内存，防止泄露
    (5)
}
```

**3.** (3) 处需要填入的二次曲面初始化函数为：（　　）

A）`gluSphere();`　　B）`gluNewQuadric();`  
C）`new GLUquadricObj();`　　D）`malloc(sizeof(GLUquadricObj));`

**4.** (4) 处执行球体渲染的函数代码为：（　　）

A）`gluSphere(quad, 2.0f, 30, 30);`　　B）`glutWireSphere(2.0, 30, 30);`  
C）`gluSphere(2.0f, 30, 30, quad);`　　D）`glutSolidSphere(2.0, 30, 30);`

**5.** (5) 处销毁释放二次曲面指针对象的代码为：（　　）

A）`free(quad);`　　B）`delete quad;`  
C）`gluDeleteQuadric(quad);`　　D）`quad = NULL;`

---

## 三、 答案与解析

### 7.1 练习解析
**1.** 答案：B  
解析：`gluLookAt` 前三个参数是眼睛位置，即 `(0, 0, 5)`；中间三个参数是观察的参考焦点，即 `(0, 0, 0)`；最后三个参数是相机的正上方向量，即 `(0, 1, 0)`。  
**2.** 答案：B  
解析：`glutWireTeapot(size)` 用于绘制线框结构的茶壶模型。

### 7.2 练习解析
**3.** 答案：B  
解析：二次曲面的申请分配必须通过专有函数 `gluNewQuadric()` 来执行并返回相应指针。  
**4.** 答案：A  
解析：`gluSphere(quad, radius, slices, stacks)` 的第一个参数必须是创建好的 `GLUquadricObj` 状态指针。  
**5.** 答案：C  
解析：二次曲面所占用的内存必须通过 `gluDeleteQuadric(quad)` 专用函数完成清理，不能直接使用 `free` 或 `delete`。
