# lab04-line-clipping 实验考点与编程专项练习

---

## 一、 核心知识点整理

### 4.1 Cohen-Sutherland 直线段编码裁剪算法
- **空间划分为9个区**: 每个区赋予一个 4 位编码（上下左右，即 `TOP`、`BOTTOM`、`RIGHT`、`LEFT`）。
  - **LEFT**: $x < x_{\min}$ (0001)
  - **RIGHT**: $x > x_{\max}$ (0010)
  - **BOTTOM**: $y < y_{\min}$ (0100)
  - **TOP**: $y > y_{\max}$ (1000)
- **快速可见性裁剪逻辑**:
  - **简取**: `(code0 | code1) == 0`，直线完全在窗口内。
  - **简弃**: `(code0 & code1) != 0`，两端点同在窗口的某侧之外，不绘制。
- **分段求交**: 重复求出线段与窗口边界的交点，更新外部端点并重新编码。

### 4.2 Liang-Barsky 参数化直线段裁剪算法
- **引入参数方程**: 将线段表达为 $x = x_0 + u \Delta x$，$y = y_0 + u \Delta y$ ($0 \le u \le 1$)。
- **裁剪条件**: $u p_i \le q_i$。其包含四个参数边界条件。
- **决定参数范围**:
  - $p_i < 0$: 直线段从窗口外延伸至窗口内，用于更新进入点参数 $u_1 = \max(u_1, r_i)$。
  - $p_i > 0$: 直线段从窗口内延伸至窗口外，用于更新退出点参数 $u_2 = \min(u_2, r_i)$。
  - 若最终计算出的参数满足 $u_1 > u_2$，说明线段完全位于窗口之外。

---

## 二、 编程填空专项练习

### 4.1 Cohen-Sutherland 直线段裁剪算法练习

```cpp
#define LEFT   1   // 0001
#define RIGHT  2   // 0010
#define BOTTOM 4   // 0100
#define TOP    8   // 1000

// 1. 计算给定顶点的 Cohen-Sutherland 4位区域编码
int CompCode(float x, float y, float xmin, float xmax, float ymin, float ymax)
{
    int code = 0;
    if (x < xmin)      code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    
    if (y < ymin)      (1) // 处于下边界之外
    else if (y > ymax) (2) // 处于上边界之外
    
    return code;
}

// 2. 编码裁剪算法主体
bool CohenSutherlandClip(float& x0, float& y0, float& x1, float& y1, 
                          float xmin, float xmax, float ymin, float ymax)
{
    int code0 = CompCode(x0, y0, xmin, xmax, ymin, ymax);
    int code1 = CompCode(x1, y1, xmin, xmax, ymin, ymax);
    bool accept = false;

    while (true)
    {
        if ((3)) // 简取
        {
            accept = true;
            break;
        }
        else if ((4)) // 简弃
        {
            break;
        }
        else
        {
            // 不满足简取和简弃，至少一个端点在窗口外部，在此求交省略...
            break;
        }
    }
    return accept;
}
```

**1.** (1) 处对下边界外的顶点进行编码的代码为：（　　）

A）`code |= BOTTOM;`　　B）`code &= BOTTOM;`　　C）`code = BOTTOM;`　　D）`code |= TOP;`

**2.** (2) 处对上边界外的顶点进行编码的代码为：（　　）

A）`code |= BOTTOM;`　　B）`code |= TOP;`　　C）`code &= TOP;`　　D）`code = TOP;`

**3.** (3) 处“简取”的逻辑判断条件为：（　　）

A）`code0 & code1 == 0`　　B）`(code0 | code1) == 0`　　C）`code0 != 0 && code1 != 0`　　D）`code0 == code1`

**4.** (4) 处“简弃”的逻辑判断条件为：（　　）

A）`(code0 & code1) != 0`　　B）`code0 | code1 != 0`　　C）`code0 == 0 || code1 == 0`　　D）`code0 != code1`

---

### 4.2 Liang-Barsky 参数化直线段裁剪算法练习

```cpp
// Liang-Barsky 算法内部裁剪测试函数
// 如果进入值 u1 大于退出值 u2，返回 false 表示直线不可见
bool ClipTest(float p, float q, float& u1, float& u2)
{
    float r = q / p;
    if (p < 0.0f) // 直线从外部指向内部（寻找最大进入参数 u1）
    {
        if (r > u2) return false;
        else if (r > u1)
        {
            (5); // 更新 u1 边界
        }
    }
    else if (p > 0.0f) // 直线从内部指向外部（寻找最小退出参数 u2）
    {
        if (r < u1) return false;
        else if (r < u2)
        {
            (6); // 更新 u2 边界
        }
    }
    else if (q < 0.0f) // p=0 代表与边界平行，若 q < 0 说明线在窗口外，不可见
    {
        return false;
    }
    return true;
}

// 主算法逻辑
bool LiangBarskyClip(float x0, float y0, float x1, float y1, float xmin, float xmax, float ymin, float ymax)
{
    float u1 = 0.0f, u2 = 1.0f;
    float dx = x1 - x0;
    float dy = y1 - y0;
    
    // 对四条边界调用裁剪测试函数更新 u1, u2 参数
    if (ClipTest(-dx, x0 - xmin, u1, u2)) // 左
    if (ClipTest(dx, xmax - x0, u1, u2))   // 右
    if (ClipTest(-dy, y0 - ymin, u1, u2)) // 下
    if (ClipTest(dy, ymax - y0, u1, u2))   // 上
    {
        // 如果线段是可见的，根据最终裁剪参数 u1 和 u2 计算新坐标位置
        (7) = x0 + u1 * dx;
        (8) = y0 + u1 * dy;
        // 计算退出点坐标省略...
        return true;
    }
    return false;
}
```

**5.** (5) 处更新进入参数 $u_1$ 的代码为：（　　）

A）`u1 = r;`　　B）`u2 = r;`　　C）`u1 = u2;`　　D）`u1 = 0.0f;`

**6.** (6) 处更新退出参数 $u_2$ 的代码为：（　　）

A）`u1 = r;`　　B）`u2 = r;`　　C）`u2 = u1;`　　D）`u2 = 1.0f;`

**7.** (7) 处需要赋给新顶点的进入点 $X$ 坐标变量为：（　　）

A）`x0`　　B）`x1`　　C）`xmin`　　D）`xmax`

**8.** (8) 处需要赋给新顶点的进入点 $Y$ 坐标变量为：（　　）

A）`ymin`　　B）`ymax`　　C）`y0`　　D）`y1`

---

## 三、 答案与解析

### 4.1 练习解析
**1.** 答案：A  
解析：下边界外部用 `BOTTOM` (值为4) 标记，需要使用位或运算符 `|=` 保留原状态并叠加此标记。  
**2.** 答案：B  
解析：上边界外部用 `TOP` (值为8) 标记，同理使用 `code |= TOP;`。  
**3.** 答案：B  
解析：如果两端点的 outcode 按位或为 0，表明都在内部，即 `(code0 | code1) == 0`，代表线段无需裁剪直接保留。  
**4.** 答案：A  
解析：如果两端点同时属于某个外部区域（按位与不为 0），代表它在某一边界线外，可立即舍弃。

### 4.2 练习解析
**5.** 答案：A  
解析：$p < 0$ 表示线段从外面穿过边界线向里，为进入点。它对进入参数 $u_1$ 进行更新：取较大值 $u_1 = \max(u_1, r)$，因已通过 `if (r > u1)` 判定，直接赋值 `u1 = r`。  
**6.** 答案：B  
解析：$p > 0$ 表示线段从里向外，属于退出点。它更新退出参数 $u_2$：取较小值 $u_2 = \min(u_2, r)$，故直接赋值 `u2 = r`。  
**7.** 答案：A  
解析：当进入点参数 $u_1$ 确定后，它所对应的新线段起始点坐标需要覆盖原来的坐标。因此，为 `x0` 重新计算赋值：`x0 = x0 + u1 * dx;`。  
**8.** 答案：C  
解析：同样地，对应的新线段起始点 $Y$ 坐标也需要覆盖为 `y0`：`y0 = y0 + u1 * dy;`。
