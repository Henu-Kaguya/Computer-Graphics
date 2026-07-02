# lab08-3d-rendering 实验考点与编程专项练习

---

## 一、 核心知识点整理

### 8.1 三维消隐与深度测试 (Z-Buffer)

* **消隐的作用**：剔除遮挡的多边形背部表面。
* **图像空间消隐**：**Z-Buffer (深度缓存)** 算法。
* **Z-Buffer 数据结构**：
  - `ColorBuffer`：保存屏幕每个像素的颜色。
  - `DepthBuffer`：保存每个像素当前的可见最小深度 $Z$ 值。
* **深度检查比较公式 (核心)**：
  - 初始将 `zbuffer` 填充极远值（最小）。
  - 对于多边形在该处的每个像素点 $(x, y)$ 进行深度插值计算得出 $z$ 值。
* **判断**：如果当前计算出来的深度值更近，即满足：$z > zbuffer(x, y)$，则说明其在可见面上。
* **更新**：执行深度替换 `zbuffer(x, y) = z` 并刷新图像颜色 `colorBuffer(x, y) = color`。

---

## 二、 编程填空专项练习

### 8.1 Z-Buffer 算法计算实现练习

```cpp
struct Vec3f { float x, y, z; };
struct Color { unsigned char r, g, b; };
struct Triangle { Vec3f pts[3]; Color c; };

// 扫描三角形并在图像上进行 Z-Buffer 消隐测试
// zbuffer 大小为 w * h，初始被填充了 -99999.0f (远裁剪面)
void RenderTriangleZBuffer(Triangle t, float* zbuffer, Color* colorBuffer, int w, int h)
{
    // 包围盒内进行片元遍历
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            if (IsInsideTriangle(x, y, t))
            {
                // 1. 计算当前 (x, y) 位置处的三角形插值深度 z
                float z = InterpolateDepth(x, y, t);
                int idx = y * w + x;

                // 2. 如果当前 z 更靠近相机 (深度越大表示离视点越近)
                if ((1))
                {
                    (2) // 3. 更新深度缓存的值
                    (3) // 4. 更新颜色缓存的值
                }
            }
        }
    }
}
```

**1. (1) 处进行 Z-Buffer 深度检测的逻辑表达式为：（　　）**

* A. `z < zbuffer[idx]`
* B. `z > zbuffer[idx]`
* C. `z == zbuffer[idx]`
* D. `z != -99999.0f`

**2. (2) 处更新深度缓冲区的操作为：（　　）**

* A. `z = zbuffer[idx];`
* B. `zbuffer[idx] = z;`
* C. `zbuffer[idx] = -99999.0f;`
* D. `zbuffer[idx] = 1.0f;`

**3. (3) 处更新颜色缓冲区的操作为：（　　）**

* A. `colorBuffer[idx] = t.c;`
* B. `t.c = colorBuffer[idx];`
* C. `SetPixelColor(x, y, t.c);`
* D. `A 和 C 均正确`

---

## 三、 答案与解析

### 8.1 练习解析

> **【参考答案与解析】**
>
> **1.** 答案：`B`
>
> - **解析**：Z-Buffer 的深度缓冲存储的是可见物体的最大 $z$ 值（离眼睛最近）。只有当新计算的 $z$ 大于已有值时，新的表面才会挡在前面的表面之前。
>
> **2.** 答案：`B`
>
> - **解析**：检测到更近表面时，应该将深度缓冲的值更新为当前的最新深度值：`zbuffer[idx] = z;`。
>
> **3.** 答案：`A`
>
> - **解析**：深度更新的同时，对应的图像颜色缓冲也必须更新为该顶点的材质颜色，故使用一维指针赋值 `colorBuffer[idx] = t.c;`。
