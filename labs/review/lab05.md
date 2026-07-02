# lab05-geometric-transformations 实验考点与编程专项练习

---

## 一、 核心知识点整理

### 5.1 & 5.2 几何变换的类型与矩阵模式
- **平移、缩放与旋转**:
  - `glTranslatef(tx, ty, tz)`: 平移。
  - `glRotatef(angle, x, y, z)`: 旋转。
  - `glScalef(sx, sy, sz)`: 缩放。
- **变换矩阵加载模式**: 几何物体的平移、旋转、缩放都是基于模型视图矩阵。所以绘制前先切换 `glMatrixMode(GL_MODELVIEW)` 并调用 `glLoadIdentity()` 复位。

### 5.3 复合变换 (重点)
- **后乘(右乘)运算机制**: 顶点变换受到矩阵作用的顺序与 OpenGL 书写变换命令的顺序**完全相反**。
- **关于任意点的旋转与缩放**:
  - 比如绕 $(xr, yr)$ 点旋转，实际执行为：平移到原点 $T(-xr, -yr)$ $	o$ 绕原点旋转 $R(angle)$ $	o$ 平移回原位 $T(xr, yr)$。
  - OpenGL 代码书写顺序则是反着的：`glTranslatef(xr, yr, ...)` $	o$ `glRotatef(...)` $	o$ `glTranslatef(-xr, -yr, ...)`。

### 5.4 3D 三维物体与矩阵栈
- **局部坐标隔离保护**:
  - `glPushMatrix()`: 保存当前模型视图矩阵。
  - `glPopMatrix()`: 弹出矩阵，还原前一状态。
  - 用于进行子物体独立变化时，保护父节点的坐标空间。

---

## 二、 编程填空专项练习

### 5.1 & 5.2 多边形平移与旋转练习

```cpp
#include <GL/freeglut.h>

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 切换至模型视图矩阵模式并重置
    (1)
    (2)
    
    // 任务：画出沿 X 轴对称，沿 X 轴正向平移 10.0，Y 轴负向平移 10.0，
    // 缩放因子为 1.5, 2.0, 1.0 的蓝色三角形
    glColor3f(0.0f, 0.0f, 1.0f); // 蓝色
    
    // 根据 OpenGL 反序原则，最先起效的 X 轴对称 (等于绕 X 轴旋转 180 度) 应该写在最后
    // 实际执行顺序：X对称 -> 缩放 -> 平移
    (3) // 1. 执行位移 (X: 10, Y: -10)
    (4) // 2. 执行缩放 (X: 1.5, Y: 2.0, Z: 1.0)
    (5) // 3. 执行对称 (等效于绕 X 轴旋转 180 度)
    
    // 绘制基本三角形
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(40.0f, 0.0f);
    glVertex2f(20.0f, 40.0f);
    glEnd();
    
    glFlush();
}
```

**1.** (1) 处需要切换模型矩阵模式的代码为：（　　）

A）`glMatrixMode(GL_PROJECTION);`　　B）`glMatrixMode(GL_MODELVIEW);`  
C）`glMatrixMode(GL_TEXTURE);`　　D）`glViewport(0, 0, 400, 400);`

**2.** (2) 处重置视图变换矩阵的代码为：（　　）

A）`glLoadIdentity();`　　B）`glPushMatrix();`　　C）`glPopMatrix();`　　D）`glFlush();`

**3.** (3) 处需要补充的平移变换代码为：（　　）

A）`glTranslatef(10.0f, 10.0f, 0.0f);`　　B）`glTranslatef(10.0f, -10.0f, 0.0f);`  
C）`glTranslatef(-10.0f, 10.0f, 0.0f);`　　D）`glTranslatef(-10.0f, -10.0f, 0.0f);`

**4.** (4) 处需要补充的缩放变换代码为：（　　）

A）`glScalef(1.5f, 2.0f, 1.0f);`　　B）`glScalef(1.5f, -2.0f, 1.0f);`  
C）`glScalef(2.0f, 1.5f, 1.0f);`　　D）`glScalef(1.0f, 1.0f, 1.0f);`

**5.** (5) 处需要补充的对称等效变换代码为：（　　）

A）`glRotatef(180.0f, 0.0f, 1.0f, 0.0f);`　　B）`glRotatef(180.0f, 1.0f, 0.0f, 0.0f);`  
C）`glRotatef(180.0f, 0.0f, 0.0f, 1.0f);`　　D）`glScalef(1.0f, 1.0f, 1.0f);`

---

### 5.3 复合变换 (绕任意中心点旋转) 练习

```cpp
#include <GL/freeglut.h>

// 实现绕任意中心点 (xr, yr) 旋转 angle 度的复合变换
void RotateAroundPoint(float angle, float xr, float yr)
{
    // 书写顺序必须与物理执行顺序相反
    // 物理顺序：1. 平移到原点 (-xr, -yr) -> 2. 绕原点旋转 -> 3. 平移回原位 (xr, yr)
    (6) // 对应第三步
    (7) // 对应第二步
    (8) // 对应第一步
}
```

**6.** (6) 处需要补充的第一条 OpenGL 复合变换代码为：（　　）

A）`glTranslatef(-xr, -yr, 0.0f);`　　B）`glTranslatef(xr, yr, 0.0f);`  
C）`glRotatef(angle, 0.0f, 0.0f, 1.0f);`　　D）`glLoadIdentity();`

**7.** (7) 处需要补充的第二条 OpenGL 复合变换代码为：（　　）

A）`glTranslatef(xr, yr, 0.0f);`　　B）`glRotatef(angle, 0.0f, 0.0f, 1.0f);`  
C）`glRotatef(angle, 1.0f, 0.0f, 0.0f);`　　D）`glTranslatef(-xr, -yr, 0.0f);`

**8.** (8) 处需要补充的第三条 OpenGL 复合变换代码为：（　　）

A）`glTranslatef(xr, yr, 0.0f);`　　B）`glRotatef(angle, 0.0f, 0.0f, 1.0f);`  
C）`glTranslatef(-xr, -yr, 0.0f);`　　D）`glScalef(-xr, -yr, 1.0f);`

---

### 5.4 3D 三维空间几何变换与矩阵栈练习

```cpp
#include <GL/freeglut.h>

// 绘制一个三维立方体，并使用矩阵栈保护局部空间
void DrawRobotFinger()
{
    (9) // 1. 保存当前的模型视图矩阵状态
    
    // 局部位移和缩放变换
    glTranslatef(1.0f, 0.0f, 0.0f);
    glScalef(2.0f, 0.5f, 0.5f);
    
    // 绘制实心立方体
    (10)(1.0);
    
    (11) // 2. 还原之前的模型视图矩阵，消除本子物体变换对后续绘制的影响
}
```

**9.** (9) 处保护矩阵状态压栈的代码为：（　　）

A）`glPopMatrix();`　　B）`glPushMatrix();`  
C）`glLoadIdentity();`　　D）`glMatrixMode(GL_MODELVIEW);`

**10.** (10) 处绘制大小为 1.0 的实心立方体的 GLUT 函数名为：（　　）

A）`glutSolidTeapot`　　B）`glutSolidSphere`  
C）`glutSolidCube`　　D）`glutWireCube`

**11.** (11) 处弹出矩阵恢复状态的代码为：（　　）

A）`glPushMatrix();`　　B）`glPopMatrix();`  
C）`glLoadIdentity();`　　D）`glFlush();`

---

## 三、 答案与解析

### 5.1 & 5.2 练习解析
**1.** 答案：B  
解析：几何变换属于模型空间操作，必须选择 `GL_MODELVIEW` 模型视图矩阵模式。  
**2.** 答案：A  
解析：`glLoadIdentity()` 会把当前的变换矩阵清空并重置为单位矩阵，作为计算几何坐标的初始状态。  
**3.** 答案：B  
解析：朝 $X$ 正向平移 $10.0$，而 $Y$ 轴负向平移 $10.0$。对应的位移代码应为 `glTranslatef(10.0f, -10.0f, 0.0f);`。  
**4.** 答案：A  
解析：根据缩放参数 $sx=1.5, sy=2.0, sz=1.0$，选择 `glScalef(1.5f, 2.0f, 1.0f);`。  
**5.** 答案：B  
解析：关于 $X$ 轴对称等于让顶点绕着 $X$ 轴旋转 $180$ 度，使 $Y, Z$ 坐标变为原来的相反数。其旋转轴向量为 $(1.0, 0.0, 0.0)$，所以是 `glRotatef(180.0f, 1.0f, 0.0f, 0.0f);`。

### 5.3 练习解析
**6.** 答案：B  
解析：绕任意点 $(xr, yr)$ 旋转三部曲的最后一步是平移回原处：`glTranslatef(xr, yr, 0.0f)`，依反序原则应该第一个书写。  
**7.** 答案：B  
解析：中间步骤是绕原点进行 $z$ 轴旋转，即 `glRotatef(angle, 0.0f, 0.0f, 1.0f)`。  
**8.** 答案：C  
解析：第一步是平移将旋转中心移到原点：`glTranslatef(-xr, -yr, 0.0f)`，写在复合序列的最后。

### 5.4 练习解析
**9.** 答案：B  
解析：`glPushMatrix()` 会把当前矩阵状态压入矩阵栈保护。  
**10.** 答案：C  
解析：绘制实体实心立方体的函数名是 `glutSolidCube(size)`。  
**11.** 答案：B  
解析：`glPopMatrix()` 会弹出栈顶矩阵并重置当前矩阵值，消除了本模块内的位移对外部的污染。
