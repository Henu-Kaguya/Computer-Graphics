# lab02-polygon-filling 实验考点与编程专项练习

---

## 一、 核心知识点整理

### 2.1 活动边表扫描填充算法

* **扫描转换算法的基本设计**：逐行利用扫描线求交点，配对并填色。
- **活动边表 (AET - Active Edge Table)** 节点成员:
  - `yMax`：边的最大 $y$ 值。
  - `x`：当前扫描线与该边交点的 $x$ 坐标。
  - `dx`：边的斜率的倒数 ($dx = 1/k = \Delta x / \Delta y$)，用于递增更新 $x$。
* **交点坐标递推**：扫描线每行递增 1 像素，即新交点 $x = x_{old} + dx$。

### 2.2 种子填充算法

* **四连通种子填充**：从给定的内部点 $(x, y)$ 出发，如果它不是边界色且未被填色，则填充它，并向其上、下、左、右四个相邻像素递归延伸。
* **与八连通的差别**：8 连通还要向四个对角线方向延伸。四连通可以穿过对角线缝隙，被八连通边界阻挡。

### 2.3 边界多边形与扫描线种子填充

* **扫描线种子填充**：它是对简单种子填充算法的优化，通过沿水平扫描线段填充，大大减少了递归栈深度。
* **执行过程**：沿扫描线向左右填色，直到遇到边界点，并将相邻两行中的非边界线段区间段的左/右侧像素作为新种子压入栈中。

---

## 二、 编程填空专项练习

### 2.1 扫描线算法中的活动边表更新练习

```cpp
#include <stdio.h>

struct Edge
{
    int yMax;     // 边的最大 y 坐标
    float x;      // 扫描线与当前边的交点 x 坐标
    float dx;     // 斜率倒数 (1/k)
    Edge* next;
};

// 在扫描线 y 递增 1 时，更新活动边表 (AET) 链表中各交点 x 值
void UpdateAET(Edge* aet)
{
    Edge* p = aet;
    while (p != NULL)
    {
        (1) // 递增更新 x 坐标
        p = p->next;
    }
}
```

**1. (1) 处需要填写的 $x$ 坐标累加增量公式代码为：（　　）**

* A. `p->x += p->dx;`
* B. `p->x += 1.0f / p->dx;`
* C. `p->x = p->yMax;`
* D. `p->x += 1.0f;`

---

### 2.2 简单四连通种子填充练习

```cpp
struct Color { unsigned char r, g, b; };
bool ColorEqual(Color a, Color b);

// 四连通递归填充算法
void FloodFill4(int x, int y, Color fillColor, Color boundaryColor)
{
    Color current = GetPixelColor(x, y);
    // 判断当前像素是否不需要填充（既不是边界色，也未被填色）
    if ((2) && (3))
    {
        SetPixelColor(x, y, fillColor);

        // 递归填充相邻的四个方向
        (4)(x + 1, y, fillColor, boundaryColor); // 右
        (4)(x - 1, y, fillColor, boundaryColor); // 左
        (4)(x, y + 1, fillColor, boundaryColor); // 上
        (4)(x, y - 1, fillColor, boundaryColor); // 下
    }
}
```

**2. (2) 处应填写的判断不是边界色的条件为：（　　）**

* A. `!ColorEqual(current, boundaryColor)`
* B. `ColorEqual(current, boundaryColor)`
* C. `ColorEqual(current, fillColor)`
* D. `!ColorEqual(current, fillColor)`

**3. (3) 处应填写的判断未被填充色的条件为：（　　）**

* A. `ColorEqual(current, boundaryColor)`
* B. `!ColorEqual(current, fillColor)`
* C. `ColorEqual(current, fillColor)`
* D. `!ColorEqual(current, boundaryColor)`

**4. (4) 处应填写的递归调用函数名为：（　　）**

* A. `SetPixelColor`
* B. `FloodFill4`
* C. `FloodFill8`
* D. `UpdateAET`

---

### 2.3 边界生成与扫描线填充练习

```cpp
#include <stack>
using namespace std;

struct Point { int x, y; Point(int xx, int yy): x(xx), y(yy){} };
int vis[400][400]; // 0 为未填充/空白，1 为边界/已填充

// 扫描线种子填充函数的内部处理
void ScanLineFlood(int x, int y)
{
    stack<Point> s;
    s.push(Point(x, y));
    while (!s.empty())
    {
        Point p = s.top();
        s.pop();

        int left, right;
        // 1. 向左填充直到遇到边界 1
        for (left = p.x; (5); left--)
        {
            vis[left][p.y] = 1;
        }

        // 2. 向右填充直到遇到边界 1
        for (right = p.x + 1; (6); right++)
        {
            vis[right][p.y] = 1;
        }

        // 3. 在相邻上下两行探测新种子并入栈
        FindNewSeed(s, left, right, (7)); // 寻找下一行的种子
        FindNewSeed(s, left, right, (8)); // 寻找上一行的种子
    }
}
```

**5. (5) 处循环向左填充非边界像素的逻辑判定为：（　　）**

* A. `vis[left][p.y] != 1`
* B. `vis[left][p.y] == 1`
* C. `left >= 0`
* D. `vis[left][p.y] == 0`

**6. (6) 处循环向右填充非边界像素的逻辑判定为：（　　）**

* A. `vis[right][p.y] == 1`
* B. `vis[right][p.y] != 1`
* C. `right < 400`
* D. `vis[right][p.y] == 0`

**7. (7) 处传入的下一扫描线位置为：（　　）**

* A. `p.y`
* B. `p.y - 1`
* C. `p.y + 1`
* D. `p.x - 1`

**8. (8) 处传入的上一扫描线位置为：（　　）**

* A. `p.y + 1`
* B. `p.y - 1`
* C. `p.y`
* D. `p.x + 1`

---

## 三、 答案与解析

### 2.1 练习解析

> **【参考答案与解析】**
>
> **1.** 答案：`A`
>
> - **解析**：当扫描线 $y$ 递增 1 时，交点 $x$ 坐标的递增差值为直线的 $\Delta x / \Delta y = 1/k = dx$。所以新交点坐标为 `p->x += p->dx`。

### 2.2 练习解析

> **【参考答案与解析】**
>
> **2.** 答案：`A`
>
> - **解析**：当前像素不能是边界的颜色，即不等于 `boundaryColor`，用 `!ColorEqual` 判断。
>
> **3.** 答案：`B`
>
> - **解析**：同时它不能已经被着上要填充的目标颜色，避免造成死循环，因此为 `!ColorEqual(current, fillColor)`。
>
> **4.** 答案：`B`
>
> - **解析**：属于递归调用，在填充当前点后，调用自身 `FloodFill4` 递归分析临近四个方向。

### 2.3 练习解析

> **【参考答案与解析】**
>
> **5.** 答案：`A`
>
> - **解析**：向左寻找并填充，直到遇到边界值 `1`，所以循环执行的判断条件为 `vis[left][p.y] != 1`。
>
> **6.** 答案：`B`
>
> - **解析**：同理，向右扩展直至遇到边界，条件为 `vis[right][p.y] != 1`。
>
> **7.** 答案：`B`
>
> - **解析**：在当前行的下一行查找新种子像素段，对应的行号为 `p.y - 1`。
>
> **8.** 答案：`A`
>
> - **解析**：在当前行的上一行查找新种子像素段，对应的行号为 `p.y + 1`。
