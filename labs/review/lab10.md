# lab10-texture-mapping 实验考点与编程专项练习

---

## 一、 核心知识点整理

### 10.1 纹理映射流程与纹理混合

* **纹理映射步骤**：
  1. `glGenTextures`：生成纹理编号。
  2. `glBindTexture(GL_TEXTURE_2D, ID)`：激活并绑定当前纹理。
  3. `glTexImage2D(...)`：载入图像数据到 GPU。
  4. `glEnable(GL_TEXTURE_2D)`：开启贴图。
* **环境混合模式 (Env Mode)**：
  - `GL_REPLACE`：贴图纹理直接覆盖几何色彩。
  - `GL_MODULATE`：纹理色与光照底色混合（更真实立体）。

### 10.2 纹理过滤与包裹属性

* **包裹模式 (S/T轴)**：`GL_TEXTURE_WRAP_S`，可以设置为 `GL_REPEAT`（重复平铺）或 `GL_CLAMP`（截断）。
* **过滤方式 (Min/Mag Filter)**：
  - `GL_NEAREST`（最近邻，速度快有马赛克）
  - `GL_LINEAR`（双线性插值，平滑边缘）。

### 10.3 多重纹理 (Multitexturing)

* **多层渲染**：在一个几何面上叠加两个或两个以上独立纹理（如墙壁面叠加阴影纹理）。
* **多重纹理单元**：
  - `glActiveTexture(GL_TEXTURE0)`：激活 0 号纹理单元。
  - `glMultiTexCoord2f(GL_TEXTURE0, s, t)`：指定 0 号纹理单元的贴图坐标。

---

## 二、 编程填空专项练习

### 10.1 纹理定义与混合模式练习

```cpp
#include <GL/freeglut.h>

void init(void)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    // 载入纹理图像到显卡
    (1)(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texID);

    // 2. 设置纹理映射混合环境模式为：混合乘法调制模式 (MODULATE)
    (2);

    glBegin(GL_QUADS);
    // 3. 顶点的纹理贴图坐标必须在顶点几何坐标之前指定
    (3); // 对应左下角纹理原点 (0, 0)
    glVertex3f(-1.0f, -1.0f, 0.0f);

    (4); // 对应右下角纹理点 (1, 0)
    glVertex3f(1.0f, -1.0f, 0.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();

    glutSwapBuffers();
}
```

**1. (1) 处需要填入的定义二维纹理图像的函数名为：（　　）**

* A. `glTexImage2D`
* B. `glTexImage1D`
* C. `glTexEnvf`
* D. `glGenTextures`

**2. (2) 处设置纹理调制混合环境模式的代码为：（　　）**

* A. `glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);`
* B. `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);`
* C. `glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);`
* D. `glEnable(GL_MODULATE);`

**3. (3) 处需要填入的指定左下角纹理坐标的代码为：（　　）**

* A. `glTexCoord2f(0.0f, 0.0f);`
* B. `glTexCoord2f(0.0f, 1.0f);`
* C. `glVertex2f(0.0f, 0.0f);`
* D. `glTexCoord2f(1.0f, 1.0f);`

**4. (4) 处需要填入的指定右下角纹理坐标的代码为：（　　）**

* A. `glTexCoord2f(0.0f, 1.0f);`
* B. `glTexCoord2f(1.0f, 0.0f);`
* C. `glTexCoord2f(1.0f, 1.0f);`
* D. `glTexCoord2f(0.0f, 0.0f);`

---

### 10.2 纹理过滤与包裹参数练习

```cpp
#include <GL/freeglut.h>

void setupTextureParameters(void)
{
    glBindTexture(GL_TEXTURE_2D, texID);

    // 5. 设置横轴 S 轴的包裹模式为 REPEAT 重复平铺
    (5)

    // 6. 设置纵轴 T 轴的包裹模式为 CLAMP 截断边缘
    (6)

    // 7. 设置放大过滤模式为 LINEAR 线性插值平滑模式
    (7)

    // 8. 设置缩小过滤模式为 NEAREST 最近邻马赛克模式
    (8)
}
```

**5. (5) 处需要填入的设置 S 轴包裹属性的代码为：（　　）**

* A. `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);`
* B. `glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_WRAP_S, GL_REPEAT);`
* C. `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);`
* D. `glTextureWrap(GL_REPEAT);`

**6. (6) 处需要填入的设置 T 轴包裹属性的代码为：（　　）**

* A. `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);`
* B. `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);`
* C. `glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_WRAP_T, GL_CLAMP);`
* D. `glTextureWrap(GL_CLAMP);`

**7. (7) 处需要填入的设置放大过滤属性的代码为：（　　）**

* A. `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);`
* B. `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);`
* C. `glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_MAG_FILTER, GL_LINEAR);`
* D. `glEnable(GL_LINEAR);`

**8. (8) 处需要填入的设置缩小过滤属性的代码为：（　　）**

* A. `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);`
* B. `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);`
* C. `glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_MIN_FILTER, GL_NEAREST);`
* D. `glEnable(GL_NEAREST);`

---

### 10.3 多重纹理单元渲染练习

```cpp
#include <GL/freeglut.h>

void drawMultiTexturePlane(void)
{
    glBegin(GL_QUADS);

    // 9. 对应左下角几何点，指定 0 号纹理坐标 (0.0, 0.0) 和 1 号纹理坐标 (0.0, 0.0)
    (9)(GL_TEXTURE0, 0.0f, 0.0f);
    (10)(GL_TEXTURE1, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);

    // 10. 对应右上角几何点，指定 0 号纹理坐标 (1.0, 1.0) 和 1 号纹理坐标 (1.0, 1.0)
    (11)(GL_TEXTURE0, 1.0f, 1.0f);
    (12)(GL_TEXTURE1, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);

    glEnd();
}
```

**9. (9) 处指定多重纹理坐标单元 0 映射坐标的函数名为：（　　）**

* A. `glTexCoord2f`
* B. `glMultiTexCoord2f`
* C. `glMultiTexCoord2d`
* D. `glActiveTexture`

**10. (10) 处指定多重纹理坐标单元 1 映射坐标的函数名为：（　　）**

* A. `glTexCoord2f`
* B. `glMultiTexCoord2f`
* C. `glMultiTexCoord2i`
* D. `glActiveTexture`

**11. (11) 处指定多重纹理坐标单元 0 的函数为：（　　）**

* A. `glTexCoord2f`
* B. `glMultiTexCoord2f`
* C. `glMultiTexCoord2d`
* D. `glActiveTexture`

**12. (12) 处指定多重纹理坐标单元 1 的函数为：（　　）**

* A. `glTexCoord2f`
* B. `glMultiTexCoord2f`
* C. `glActiveTexture`
* D. `glMultiTexCoord2d`

---

## 三、 答案与解析

### 10.1 练习解析

> **【参考答案与解析】**
>
> **1.** 答案：`A`
>
> - **解析**：定义二维纹理像素块并载入底层的函数是 `glTexImage2D`。
>
> **2.** 答案：`A`
>
> - **解析**：设置纹理混合模式（Modulate 调制混合）的函数是 `glTexEnvf`。
>
> **3.** 答案：`A`
>
> - **解析**：纹理图片左下角对应的纹理坐标值是原点 `(0.0f, 0.0f)`。
>
> **4.** 答案：`B`
>
> - **解析**：右下角对应的是 $S$ 轴满量 $1.0$，$T$ 轴起点 $0.0$，即 `(1.0f, 0.0f)`。

### 10.2 练习解析

> **【参考答案与解析】**
>
> **5.** 答案：`A`
>
> - **解析**：使用 `glTexParameteri` 设置纹理包裹参数，`GL_TEXTURE_WRAP_S` 代表 S 方向，`GL_REPEAT` 代表重复。
>
> **6.** 答案：`A`
>
> - **解析**：包裹参数 `GL_TEXTURE_WRAP_T` 代表 T 轴垂直方向，`GL_CLAMP` 用于边界截断拉伸。
>
> **7.** 答案：`A`
>
> - **解析**：`GL_TEXTURE_MAG_FILTER` 用于设置纹理放大过滤器，`GL_LINEAR` 代表双线性过滤。
>
> **8.** 答案：`B`
>
> - **解析**：`GL_TEXTURE_MIN_FILTER` 用于设置纹理缩小过滤器，`GL_NEAREST` 代表最邻近插值过滤。

### 10.3 练习解析

> **【参考答案与解析】**
>
> **9.** 答案：`B`
>
> - **解析**：在多重纹理渲染下，指定纹理坐标不能直接调用 `glTexCoord`，而是必须使用 `glMultiTexCoord2f(texture_unit, s, t)`。
>
> **10.** 答案：`B`
>
> - **解析**：同理，给 1 号纹理单元指定贴图映射也应该调用 `glMultiTexCoord2f`，前缀参数改为 `GL_TEXTURE1`。
>
> **11.** 答案：`B`
>
> - **解析**：对所有多重纹理节点指定坐标，其统一函数均是 `glMultiTexCoord2f`。
>
> **12.** 答案：`B`
>
> - **解析**：同上，不管是 0 还是 1 号纹理单元，其三维坐标映射函数名均为 `glMultiTexCoord2f`。
