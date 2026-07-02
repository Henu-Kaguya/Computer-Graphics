# lab09-lighting-and-shading 实验考点与编程专项练习

---

## 一、 核心知识点整理

### 9.1 OpenGL 材质与光照设置

* **系统使能**：`glEnable(GL_LIGHTING)` 开启固定流水线光照计算，`glEnable(GL_LIGHT0)` 启用 0 号光源。
* **光源参数**：`glLightfv(GL_LIGHT0, GL_POSITION, pos)`。`pos[3] = 0.0` 代表平行光，`1.0` 代表点光源。
* **材质设置**：
  - `glMaterialfv(GL_FRONT, GL_DIFFUSE, color)`：漫反射颜色率。
  - `glMaterialf(GL_FRONT, GL_SHININESS, exponent)`：设置高光指数（Shininess 范围 $[0, 128]$）。

### 9.2 镜面反射高光 (Specular Reflection)

* **耀眼反光**：高光反映的是视线方向与光线出射方向（或半角向量与法线）的近似吻合程度。
* **光泽度控制**：高光敏感指数 $n$ 越大，反光区越亮，高光亮斑越小。

### 9.3 漫反射与法向量

* **漫反射规律**：漫反射颜色强度与光照向量和顶点法线的夹角余弦相关，公式为：$I_{diff} = I_p K_d (L \cdot N)$。
* **法线指定**：必须为几何体的每个面或每个顶点指定正确的法向量 `glNormal3f(nx, ny, nz)`，否则光照明暗计算会出错。

---

## 二、 编程填空专项练习

### 9.1 & 9.2 OpenGL 材质与高光设置练习

```cpp
#include <GL/freeglut.h>

void init(void)
{
    glEnable(GL_DEPTH_TEST);

    // 1. 开启光照总开关，并开启 0 号光源
    (1)
    (2)

    // 设置 0 号光源属性
    GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f }; // 平行光
    GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f }; // 漫反射白光
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 镜面反射白光
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // 2. 设置物体材质漫反射和镜面反光属性，设定高光指数为 64
    GLfloat mat_diffuse[]  = { 0.95f, 0.72f, 0.18f, 1.0f }; // 金色漫反射
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };    // 白色高光

    (3) // 材质漫反射
    (4) // 材质镜面反射
    (5) // 设置高光指数（光泽度）为 64.0f
}
```

**1. (1) 处需要填入的开启光照系统总开关代码为：（　　）**

* A. `glEnable(GL_LIGHTING);`
* B. `glEnable(GL_LIGHT0);`
* C. `glShadingModel(GL_SMOOTH);`
* D. `glMaterialfv(...);`

**2. (2) 处需要填入的开启 0 号光源开关代码为：（　　）**

* A. `glEnable(GL_LIGHTING);`
* B. `glEnable(GL_LIGHT0);`
* C. `glLightfv(...);`
* D. `glMaterialfv(...);`

**3. (3) 处需要填入的设置金色漫反射材质代码为：（　　）**

* A. `glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse);`
* B. `glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);`
* C. `glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);`
* D. `glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse);`

**4. (4) 处需要填入的设置镜面反光白光材质代码为：（　　）**

* A. `glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);`
* B. `glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);`
* C. `glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);`
* D. `glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);`

**5. (5) 处设置高光亮斑指数（SHININESS）的代码为：（　　）**

* A. `glMaterialfv(GL_FRONT, GL_SHININESS, 64.0f);`
* B. `glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);`
* C. `glLightf(GL_LIGHT0, GL_SHININESS, 64.0f);`
* D. `glMaterialf(GL_FRONT, GL_SPECULAR, 64.0f);`

---

### 9.3 漫反射与法向量绘制练习

```cpp
#include <GL/freeglut.h>

void drawCubeFace(void)
{
    // 3. 设置多边形着色模式为平滑的 Gouraud 颜色插值模式
    (6)

    glBegin(GL_QUADS);

    // 4. 绘制前表面时，必须指定朝向它的法向量：垂直指向 Z 轴正半轴 (0, 0, 1)
    (7)

    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glEnd();
}
```

**6. (6) 处设置平滑着色模型的函数代码为：（　　）**

* A. `glShadingModel(GL_SMOOTH);`
* B. `glShadingModel(GL_FLAT);`
* C. `glShadingModel(GL_PHONG);`
* D. `glEnable(GL_SMOOTH);`

**7. (7) 处指定当前多边形顶点法向量的函数代码为：（　　）**

* A. `glNormal3f(0.0f, 0.0f, 1.0f);`
* B. `glNormal3d(0.0, 0.0, 1.0);`
* C. `glVertex3f(0.0, 0.0, 1.0);`
* D. `A 和 B 均正确`

---

## 三、 答案与解析

### 9.1 & 9.2 练习解析

> **【参考答案与解析】**
>
> **1.** 答案：`A`
>
> - **解析**：开启 `GL_LIGHTING` 用于激活 OpenGL 的内部光照方程计算逻辑。
>
> **2.** 答案：`B`
>
> - **解析**：开启特定的独立光源必须使用 `glEnable(GL_LIGHT0)`。
>
> **3.** 答案：`B`
>
> - **解析**：设置材质的漫反射率需要传入 `GL_DIFFUSE` 参数，并将颜色向量赋给前向表面 `GL_FRONT`。
>
> **4.** 答案：`A`
>
> - **解析**：设置镜面高光颜色反射需要传入 `GL_SPECULAR` 参数值。
>
> **5.** 答案：`B`
>
> - **解析**：`GL_SHININESS` 属性对应的是标量浮点数值（镜面反光指数），应该调用带单浮点参数的 `glMaterialf` 函数。

### 9.3 练习解析

> **【参考答案与解析】**
>
> **6.** 答案：`A`
>
> - **解析**：`GL_SMOOTH` 对应的着色机制是 Gouraud 顶点着色平滑过渡。
>
> **7.** 答案：`D`
>
> - **解析**：法向量指定函数是 `glNormal3f` 或 `glNormal3d`，其输入参数表示该顶点的法向量指向。D 选项包含了单双精度两种重载版，均可。
