# lab06-projection-transformations 实验考点与编程专项练习

---

## 一、 核心知识点整理

### 6.1 透视投影 (Perspective Projection)

* **近大远小规律**：投影线汇聚于眼睛（投影中心），离镜头近的物体成像大，远的成像小。
* **视见体**：是一个棱台形状（Frustum）。
* **OpenGL 参数**：
  - `gluPerspective(fovy, aspect, zNear, zFar)`：
  - `fovy`：眼睛张开的角度大小（视野）。
  - `aspect`：屏幕的宽比高。
  - `zNear`/`zFar`: 近/远裁剪截断距离（必须正数）。

### 6.2 平行投影 (Orthographic Projection)

* **比例尺恒定**：投影线互相平行，物体的距离远近不影响它在屏幕上的投影大小，适合工程图表。
* **视见体**：是一个正平行六面体盒子。
* **OpenGL 参数**：`glOrtho(left, right, bottom, top, near, far)`。
* **纵横比拉伸防护**：投影空间的 $X$ 轴盒子边界一般乘以纵横比参数 `aspect` 以避免物体看起来被拉长。

---

## 二、 编程填空专项练习

### 6.1 透视投影设置练习

```cpp
#include <GL/freeglut.h>

void ChangeSize(int w, int h)
{
    if (h == 0) h = 1;
    float aspect = (float)w / h;

    // 1. 指定片元视口映射为整个窗口大小
    (1)

    // 2. 切换到投影矩阵并复位
    (2)
    (3)

    // 3. 设定视角为 45.0 度，纵横比为 aspect，近剪切距离 1.0，远剪切距离 100.0
    (4)

    glMatrixMode(GL_MODELVIEW);
}
```

**1. (1) 处需要填入的视口设置代码为：（　　）**

* A. `glViewport(0, 0, w, h);`
* B. `glutInitWindowSize(w, h);`
* C. `glOrtho(0, w, 0, h, -1, 1);`
* D. `glLoadIdentity();`

**2. (2) 处需要填入的选择投影矩阵模式的代码为：（　　）**

* A. `glMatrixMode(GL_MODELVIEW);`
* B. `glMatrixMode(GL_PROJECTION);`
* C. `glMatrixMode(GL_TEXTURE);`
* D. `glViewport(0, 0, w, h);`

**3. (3) 处需要填入的重置当前投影矩阵的代码为：（　　）**

* A. `glLoadIdentity();`
* B. `glPushMatrix();`
* C. `glPopMatrix();`
* D. `glFlush();`

**4. (4) 处需要填入的设置透视投影的函数代码为：（　　）**

* A. `glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);`
* B. `gluPerspective(45.0f, aspect, 1.0f, 100.0f);`
* C. `gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);`
* D. `glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);`

---

### 6.2 平行投影设置练习

```cpp
#include <GL/freeglut.h>

void SetupOrthographic(int w, int h)
{
    if (h == 0) h = 1;
    float aspect = (float)w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 4. 设置正交视见体盒子：Y 轴范围固定 [-3, 3]，X 轴通过乘上 aspect 动态适配防止拉伸
    if (w <= h)
    {
        // 窗口偏窄，以宽为界
        (5)
    }
    else
    {
        // 窗口偏宽，以高为界（纵横比 aspect 乘在 X 轴范围上）
        (6)
    }

    glMatrixMode(GL_MODELVIEW);
}
```

**5. (5) 处在宽比高偏窄时，为了不发生畸变，设置正交投影盒子的代码为：（　　）**

* A. `glOrtho(-3.0, 3.0, -3.0 / aspect, 3.0 / aspect, 1.0, 100.0);`
* B. `glOrtho(-3.0 * aspect, 3.0 * aspect, -3.0, 3.0, 1.0, 100.0);`
* C. `gluPerspective(45.0, aspect, 1.0, 100.0);`
* D. `glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 100.0);`

**6. (6) 处在宽比高偏宽时，为了不发生畸变，设置正交投影盒子的代码为：（　　）**

* A. `glOrtho(-3.0, 3.0, -3.0 / aspect, 3.0 / aspect, 1.0, 100.0);`
* B. `glOrtho(-3.0 * aspect, 3.0 * aspect, -3.0, 3.0, 1.0, 100.0);`
* C. `glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 100.0);`
* D. `gluPerspective(45.0, aspect, 1.0, 100.0);`

---

## 三、 答案与解析

### 6.1 练习解析

> **【参考答案与解析】**
>
> **1.** 答案：`A`
>
> - **解析**：`glViewport` 设置当前在屏幕窗口的哪一个物理坐标区间内呈现图像。
>
> **2.** 答案：`B`
>
> - **解析**：对所有与视见体、投影类型有关的调用，必须选定 `GL_PROJECTION` 投影矩阵模式。
>
> **3.** 答案：`A`
>
> - **解析**：设定投影参数前调用 `glLoadIdentity()` 消除先前残留的矩阵乘法干扰。
>
> **4.** 答案：`B`
>
> - **解析**：`gluPerspective` 用于快速定义对称透视视图参数。其参数为垂直视野角、长宽比、近剪切面、远剪切面。

### 6.2 练习解析

> **【参考答案与解析】**
>
> **5.** 答案：`A`
>
> - **解析**：当宽比高偏窄时（$aspect < 1.0$），我们应该把缩小的部分应用在 $Y$ 轴的上下界（使 $Y$ 边界除以纵横比而变大），以保证 $X$ 轴能完整显现而内容比例不会挤压变形。故选 A。
>
> **6.** 答案：`B`
>
> - **解析**：偏宽时（$aspect > 1.0$），为了防止横向图像拉宽，我们需要在水平 $X$ 方向的左右边界乘上 `aspect` 以扩大显示范围，即 `glOrtho(-3.0 * aspect, 3.0 * aspect, -3.0, 3.0, 1.0, 100.0);`。
