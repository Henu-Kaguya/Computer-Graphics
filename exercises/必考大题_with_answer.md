# 河南大学计算机与信息工程学院 2025~2026 学年第二学期期末复习

## 《 计算机图形学 》期末必考计算大题（含参考答案）

**适用专业：** 计算机科学与技术 / 软件工程 / 人工智能

---

## 一、 中点画线算法与 Bresenham 画线算法

**1. 【中点画线算法原理推导】**
已知直线方程为 $F(x, y) = ax + by + c = 0$，其中 $a = y_0 - y_1$，$b = x_1 - x_0$。假定 $x$ 正向是最大位移方向（斜率在 $0 < k < 1$ 之间）。请完成以下推导：

*(1)* 简述中点画线算法的几何判别准则与算法基本思想。(2分)

> **【参考答案】**
> - **基本思想**：在最大位移方向 $x$ 轴上每次递增一个像素的同时，计算下一像素列的两个备选像素中心的中点 $M(x_p+1, y_p+0.5)$，通过计算中点 $M$ 代入直线方程的函数值符号来判断直线与这两个备选像素的相对距离。
> - **几何判别准则**：
>   - 当 $F(M) < 0$ 时，中点位于直线下方，表明直线更靠近上方像素 $P_u(x_p+1, y_p+1)$，故选取右上像素；
>   - 当 $F(M) \ge 0$ 时，中点位于线上方或直线上，表明直线更靠近下方像素 $P_d(x_p+1, y_p)$，故选取右下像素。

*(2)* 设当前列已绘制像素点为 $(x_p, y_p)$，推导中点判别式递推公式，指出在决策变量 $d \ge 0$ 与 $d < 0$ 时，下一列决策变量 $d_{\text{next}}$ 的更新算式。(4分)

> **【参考答案】**
> - **决策变量定义**：
>   $$
>   d_i = F(x_i+1, y_i+0.5) = a(x_i+1) + b(y_i+0.5) + c
>   $$
> - **当 $d_i < 0$ 时**：选择右上像素 $(x_i+1, y_i+1)$。下一决策变量为：
>   $$
>   d_{i+1} = F(x_i+2, y_i+1.5) = a(x_i+2) + b(y_i+1.5) + c = d_i + a + b
>   $$
>   递增变化量为 $a + b$。
> - **当 $d_i \ge 0$ 时**：选择右下像素 $(x_i+1, y_i)$。下一决策变量为：
>   $$
>   d_{i+1} = F(x_i+2, y_i+0.5) = a(x_i+2) + b(y_i+0.5) + c = d_i + a
>   $$
>   递增变化量为 $a$。

*(3)* 推导为消除浮点运算而经过整数双倍放大后的判别式初值 $d_0$ 公式，并给出下一个像素位置选择的决策依据。(4分)

> **【参考答案】**
> - **初始中点**：首个点为 $(x_0, y_0)$，下一个测试中点为 $(x_0+1, y_0+0.5)$。
> - **浮点判别式初值**：
>   $$
>   d_{\text{start}} = F(x_0+1, y_0+0.5) = a(x_0+1) + b(y_0+0.5) + c
>   $$
>   由于 $F(x_0, y_0) = ax_0 + by_0 + c = 0$，展开后得 $d_{\text{start}} = a + 0.5b$。
> - **双倍放大消除浮点**：定义整数决策变量 $d_i = 2 \cdot F(x_i+1, y_i+0.5)$，则其初值为：
>   $$
>   d_0 = 2a + b
>   $$
>   代入 $a = -\Delta y$，$b = \Delta x$，可得：
>   $$
>   d_0 = \Delta x - 2\Delta y
>   $$
> - **像素选择的决策依据**：
>   - 若 $d_i < 0$，选右上像素 $(x_i+1, y_i+1)$，且下一轮判别式更新为 $d_{i+1} = d_i + 2\Delta x - 2\Delta y$；
>   - 若 $d_i \ge 0$，选右下像素 $(x_i+1, y_i)$，且下一轮判别式更新为 $d_{i+1} = d_i - 2\Delta y$。

<div align="center">
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 600" width="100%" height="100%" style="background-color: #ffffff; max-width: 600px; display: block; margin: auto;">
  <defs>
    <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M 0 0 L 10 5 L 0 10 z" fill="#333333" />
    </marker>
  </defs>
  <text x="400" y="40" style="font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; font-size: 20px; font-weight: bold; fill: #111111; text-anchor: middle;">中点画线法绘制实例演示: P₀(0,0) 到 P₁(5,2)</text>
  <line x1="230" y1="160" x2="230" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="310" y1="160" x2="310" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="390" y1="160" x2="390" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="470" y1="160" x2="470" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="550" y1="160" x2="550" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="630" y1="160" x2="630" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="400" x2="630" y2="400" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="320" x2="630" y2="320" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="240" x2="630" y2="240" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="160" x2="630" y2="160" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="480" x2="550" y2="320" style="stroke: #ff9900; stroke-width: 3; stroke-dasharray: 6,4;" />
  <circle cx="190" cy="440" r="4" style="fill: #990099;" />
  <circle cx="270" cy="440" r="4" style="fill: #990099;" />
  <circle cx="350" cy="360" r="4" style="fill: #990099;" />
  <circle cx="430" cy="360" r="4" style="fill: #990099;" />
  <text x="190" y="430" style="font-family: Arial; font-size: 11px; fill: #990099; text-anchor: middle;">M₁</text>
  <text x="270" y="430" style="font-family: Arial; font-size: 11px; fill: #990099; text-anchor: middle;">M₂</text>
  <text x="350" y="350" style="font-family: Arial; font-size: 11px; fill: #990099; text-anchor: middle;">M₃</text>
  <text x="430" y="350" style="font-family: Arial; font-size: 11px; fill: #990099; text-anchor: middle;">M₄</text>
  <rect x="110" y="440" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
  <rect x="190" y="440" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
  <rect x="270" y="360" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
  <rect x="350" y="360" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
  <rect x="430" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
  <rect x="510" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
  <circle cx="150" cy="480" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="230" cy="480" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="310" cy="400" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="390" cy="400" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="470" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="550" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <text x="150" y="505" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(0,0)</text>
  <text x="230" y="505" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(1,0)</text>
  <text x="310" y="425" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(2,1)</text>
  <text x="390" y="425" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(3,1)</text>
  <text x="470" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(4,2)</text>
  <text x="550" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(5,2)</text>
  <line x1="100" y1="480" x2="680" y2="480" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
  <line x1="150" y1="520" x2="150" y2="120" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
  <text x="675" y="505" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">X</text>
  <text x="130" y="130" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">Y</text>
  <text x="150" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">0</text>
  <text x="230" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
  <text x="310" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
  <text x="390" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
  <text x="470" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">4</text>
  <text x="550" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">5</text>
  <text x="630" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">6</text>
  <text x="125" y="405" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
  <text x="125" y="325" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
  <text x="125" y="245" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
  <g transform="translate(180, 80)">
    <rect x="0" y="0" width="440" height="40" style="fill: #f9f9f9; stroke: #dddddd; stroke-width: 1; rx: 4;" />
    <line x1="15" y1="20" x2="45" y2="20" style="stroke: #ff9900; stroke-width: 3; stroke-dasharray: 4,3;" />
    <text x="55" y="25" style="font-family: Arial; font-size: 12px; fill: #333333;">理想直线 (y = 0.4x)</text>
    <rect x="175" y="12" width="16" height="16" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
    <circle cx="183" cy="20" r="4" style="fill: #2e7d32;" />
    <text x="200" y="25" style="font-family: Arial; font-size: 12px; fill: #333333;">光栅化选择的像素点</text>
    <circle cx="335" cy="20" r="4" style="fill: #990099;" />
    <text x="345" y="25" style="font-family: Arial; font-size: 12px; fill: #333333;">中点判别位置 (M)</text>
  </g>
</svg>
</div>

<div style="page-break-after: always;"></div>

**2. 【Bresenham 画线算法原理推导】**
已知直线起点为 $P_0(x_0, y_0)$，终点为 $P_1(x_1, y_1)$。假定 $x$ 正向是最大位移方向，且斜率满足 $0 < k < 1$。请完成以下推导：

*(1)* 简述 Bresenham 画线算法通过跟踪误差来逼近理想直线的算法基本思想。(2分)

> **【参考答案】**
> - **核心思想**：Bresenham 算法通过跟踪和累积理想直线与实际像素网格点之间的偏差量（误差）来决定像素选取。
> - **基本思想**：
>   - 在斜率满足 $0 < k < 1$ 时，$x$ 为最大位移方向。因此 $x$ 每步递增 $1$，而 $y$ 坐标的理论值增加 $k$。
>   - 实际像素坐标必须为整数，故下一步绘制像素的纵坐标只能选择保持不变 $y_i$（右侧像素）或递增 $1$ $y_i+1$（右上像素）。
>   - 算法在每一步通过计算理想直线当前位置到上方和下方两个候选像素中心点的距离之差，构造一个**误差决策变量**。当累积误差超过临界值时，像素向 $y$ 正方向递增 $1$ 并减去误差修正值，否则保持不变，以此使绘制的离散折线最逼近理想直线。

*(2)* 设当前列决策变量为 $d_i$，推导下一列决策变量 $d_{i+1}$ 的误差判别递推公式。(4分)

> **【参考答案】**
> 设直线的起点为 $(x_0, y_0)$，终点为 $(x_1, y_1)$，直线的斜截式方程为：
> $$
> y = kx + b
> $$
> 其中 $k = \frac{\Delta y}{\Delta x}$，$\Delta x = x_1 - x_0$，$\Delta y = y_1 - y_0$。
> 
> 假设已确定第 $i$ 步的像素位置为 $(x_i, y_i)$，在下一步 $x_{i+1} = x_i + 1$ 处，理想直线上的 $y$ 值为：
> $$
> y = k(x_i + 1) + b
> $$
> 理想直线与下方候选像素 $y_i$ 及上方候选像素 $y_i + 1$ 的垂直距离分别为 $d_{\text{down}}$ 和 $d_{\text{up}}$：
> - $d_{\text{down}} = y - y_i = k(x_i + 1) + b - y_i$
> - $d_{\text{up}} = (y_i + 1) - y = y_i + 1 - [k(x_i + 1) + b]$
> 
> 构造两者差值作为决策变量 $d_i$：
> $$
> d_i = d_{\text{down}} - d_{\text{up}} = 2k(x_i + 1) + 2b - 2y_i - 1
> $$
> 将 $k = \frac{\Delta y}{\Delta x}$ 代入上式得：
> $$
> d_i = 2\frac{\Delta y}{\Delta x}(x_i + 1) + 2b - 2y_i - 1
> $$
> 同理，写出下一步（$i+1$ 步）的决策变量 $d_{i+1}$（其中 $x_{i+1} = x_i + 1$）：
> $$
> d_{i+1} = 2\frac{\Delta y}{\Delta x}(x_{i+1} + 1) + 2b - 2y_{i+1} - 1
> $$
> 用 $d_{i+1}$ 减去 $d_i$ 进行递推计算：
> $$
> d_{i+1} - d_i = 2\frac{\Delta y}{\Delta x}(x_{i+1} - x_i) - 2(y_{i+1} - y_i) = 2\frac{\Delta y}{\Delta x} - 2(y_{i+1} - y_i)
> $$
> 故决策变量的递推公式为：
> $$
> d_{i+1} = d_i + 2\frac{\Delta y}{\Delta x} - 2(y_{i+1} - y_i)
> $$

*(3)* 说明如何通过消去分母与常数项，将算法改造为纯整数加减与移位运算，并给出整数型初值 $d_0$、决策更新增量以及下一步像素位置的选择依据。(4分)

> **【参考答案】**
> - **1. 消除分母（整数化）**：
>   由于递推公式中含有分数分母 $\Delta x$，为了消除分母，可以对 $d_i$ 同乘以不改变其符号的放大因子 $\Delta x$（因为 $\Delta x > 0$），定义新的整数型决策变量 $D_i = \Delta x \cdot d_i$。
>   两边同乘 $\Delta x$ 改造递推式：
>   $$
>   D_{i+1} = D_i + 2\Delta y - 2\Delta x(y_{i+1} - y_i)
>   $$
> - **2. 下一步像素位置的选择依据与增量更新**：
>   - **若 $D_i < 0$**（即理想直线更接近下方像素）：
>     - 像素选择：$x_{i+1} = x_i + 1$，$y_{i+1} = y_i$
>     - 决策变量更新：$D_{i+1} = D_i + 2\Delta y$
>   - **若 $D_i \ge 0$**（即理想直线更接近上方像素）：
>     - 像素选择：$x_{i+1} = x_i + 1$，$y_{i+1} = y_i + 1$
>     - 决策变量更新：$D_{i+1} = D_i + 2\Delta y - 2\Delta x$
> - **3. 整数型初值 $D_0$ 的推导**：
>   将起点 $P_0(x_0, y_0)$ 代入初始决策变量 $d_0$ 算式。因为该点在理想直线上满足 $y_0 = kx_0 + b$：
>   $$
>   d_0 = 2(kx_0 + b) + 2k - 2y_0 - 1 = 2y_0 + 2k - 2y_0 - 1 = 2k - 1
>   $$
>   代入 $k = \frac{\Delta y}{\Delta x}$ 且同乘 $\Delta x$，得到整数型初值 $D_0$：
>   $$
>   D_0 = \Delta x \cdot \left(2\frac{\Delta y}{\Delta x} - 1\right) = 2\Delta y - \Delta x
>   $$
>   经此改造，公式中只包含 $2\Delta y$ 和 $2\Delta y - 2\Delta x$。由于乘以 2 可以通过左移位运算（`<< 1`）实现，整个算法内部循环完全转化为纯整数的加减与移位操作，极大地提升了计算机的图形渲染效率。

<div align="center">
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 600" width="100%" height="100%" style="background-color: #ffffff; max-width: 600px; display: block; margin: auto;">
  <defs>
    <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M 0 0 L 10 5 L 0 10 z" fill="#333333" />
    </marker>
  </defs>
  <text x="400" y="40" style="font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; font-size: 20px; font-weight: bold; fill: #111111; text-anchor: middle;">Bresenham 原始算法演示: P₀(0,0) 到 P₁(5,2) [d 与 0.5 比较]</text>
  <line x1="230" y1="160" x2="230" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="310" y1="160" x2="310" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="390" y1="160" x2="390" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="470" y1="160" x2="470" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="550" y1="160" x2="550" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="630" y1="160" x2="630" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="400" x2="630" y2="400" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="320" x2="630" y2="320" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="240" x2="630" y2="240" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="160" x2="630" y2="160" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="440" x2="630" y2="440" style="stroke: #bc13fe; stroke-width: 1.5; stroke-dasharray: 8,4,2,4;" />
  <line x1="150" y1="360" x2="630" y2="360" style="stroke: #bc13fe; stroke-width: 1.5; stroke-dasharray: 8,4,2,4;" />
  <text x="640" y="444" style="font-family: Arial; font-size: 12px; fill: #bc13fe; font-weight: bold;">y = 0.5 临界线</text>
  <text x="640" y="364" style="font-family: Arial; font-size: 12px; fill: #bc13fe; font-weight: bold;">y = 1.5 临界线</text>
  <line x1="150" y1="480" x2="550" y2="320" style="stroke: #ff9900; stroke-width: 3.5; stroke-dasharray: 6,4;" />
  <rect x="110" y="440" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="190" y="440" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="270" y="360" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="350" y="360" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="430" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="510" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <circle cx="150" cy="480" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="230" cy="480" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="310" cy="400" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="390" cy="400" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="470" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="550" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <text x="150" y="505" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(0,0)</text>
  <text x="230" y="505" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(1,0)</text>
  <text x="310" y="425" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(2,1)</text>
  <text x="390" y="425" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(3,1)</text>
  <text x="470" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(4,2)</text>
  <text x="550" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(5,2)</text>
  <line x1="100" y1="480" x2="680" y2="480" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
  <line x1="150" y1="520" x2="150" y2="120" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
  <text x="675" y="505" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">X</text>
  <text x="130" y="130" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">Y</text>
  <text x="150" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">0</text>
  <text x="230" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
  <text x="310" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
  <text x="390" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
  <text x="470" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">4</text>
  <text x="550" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">5</text>
  <text x="630" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">6</text>
  <text x="125" y="405" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
  <text x="125" y="325" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
  <text x="125" y="245" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
  <g transform="translate(140, 75)">
    <rect x="0" y="0" width="520" height="40" style="fill: #f9f9f9; stroke: #dddddd; stroke-width: 1; rx: 4;" />
    <line x1="15" y1="20" x2="45" y2="20" style="stroke: #ff9900; stroke-width: 3.5; stroke-dasharray: 4,3;" />
    <text x="55" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">理想直线</text>
    <line x1="140" y1="20" x2="170" y2="20" style="stroke: #bc13fe; stroke-width: 1.5; stroke-dasharray: 5,2,1,2;" />
    <text x="180" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">0.5 误差阈值边界线</text>
    <rect x="315" y="12" width="16" height="16" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
    <circle cx="323" cy="20" r="4" style="fill: #2e7d32;" />
    <text x="340" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">Bresenham选中的离散像素</text>
  </g>
</svg>
</div>

<div style="page-break-after: always;"></div>

**3. 【直线上栅化计算（1,1 至 5,2）】**
已知需要绘制从起点 $P_0(1, 1)$ 到终点 $P_1(5, 2)$ 的直线段。请分别使用中点画线算法和 Bresenham 算法进行光栅化离散点列计算：

*(1)* 采用中点画线算法（双倍放大形式），写出直线方程系数 $a, b$，计算决策变量初值 $d_0$，列出各步决策变量 $d$ 的值与选点结果坐标。(5分)

> **【参考答案】**
> - **直线方程系数计算**：
>   - $\Delta x = 5 - 1 = 4$，$\Delta y = 2 - 1 = 1$
>   - 系数：$a = y_0 - y_1 = -1$，$b = x_1 - x_0 = 4$
> - **决策变量初值 $d_0$**：
>   $$
>   d_0 = 2a + b = 2(-1) + 4 = 2
>   $$
> - **递推计算过程**：
>   - **第 $0$ 步**：$x = 1, y = 1$。因为 $d_0 = 2 \ge 0$，选择右下点 $(2, 1)$。
>     更新：$d_1 = d_0 + 2a = 2 - 2 = 0$。
>   - **第 $1$ 步**：$x = 2, y = 1$。因为 $d_1 = 0 \ge 0$，选择右下点 $(3, 1)$。
>     更新：$d_2 = d_1 + 2a = 0 - 2 = -2$。
>   - **第 $2$ 步**：$x = 3, y = 1$。因为 $d_2 = -2 < 0$，选择右上点 $(4, 2)$。
>     更新：$d_3 = d_2 + 2a + 2b = -2 - 2 + 8 = 4$。
>   - **第 $3$ 步**：$x = 4, y = 2$。因为 $d_3 = 4 \ge 0$，选择右下点 $(5, 2)$。
>   - 最终绘制的离散像素点列为：$(1,1), (2,1), (3,1), (4,2), (5,2)$。

*(2)* 采用 Bresenham 算法（整数优化形式），写出误差决策变量初值 $d'_0$、增量项，并列表计算出各步的 $d$ 值判定与最终绘制的离散像素坐标点列 $(x,y)$。(5分)

> **【参考答案】**
> - **决策初值及增量项**：
>   - $\Delta x = 4$, $\Delta y = 1$
>   - 误差初值：$d'_0 = 2\Delta y - \Delta x = 2(1) - 4 = -2$
>   - 增量项：
>     - 若 $d \ge 0$，更新增量为 $2\Delta y - 2\Delta x = 2 - 8 = -6$；
>     - 若 $d < 0$，更新增量为 $2\Delta y = 2$。
> - **Bresenham 递推计算表**：
> 
>   | 步数 | 绘制像素点 $(x, y)$ | 误差判别项 $d$ | 判定条件 | 下一步纵坐标更新 |
>   | :---: | :---: | :---: | :---: | :---: |
>   | 0 | $(1, 1)$ | $-2$ (初值) | $d < 0$ | $y$ 不变 ($y=1$) |
>   | 1 | $(2, 1)$ | $-2 + 2 = 0$ | $d \ge 0$ | $y$ 增 $1$ ($y=2$) |
>   | 2 | $(3, 2)$ | $0 - 6 = -6$ | $d < 0$ | $y$ 不变 ($y=2$) |
>   | 3 | $(4, 2)$ | $-6 + 2 = -4$ | $d < 0$ | $y$ 不变 ($y=2$) |
>   | 4 | $(5, 2)$ | — | 已达终点 | — |
> 
> - 最终生成的离散点列为：$(1,1), (2,1), (3,2), (4,2), (5,2)$。

<div align="center">
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 600" width="100%" height="100%" style="background-color: #ffffff; max-width: 600px; display: block; margin: auto;">
  <defs>
    <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M 0 0 L 10 5 L 0 10 z" fill="#333333" />
    </marker>
  </defs>
  <text x="400" y="40" style="font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; font-size: 20px; font-weight: bold; fill: #111111; text-anchor: middle;">直线上栅化演示: P₀(1,1) 到 P₁(5,2)</text>
  <line x1="230" y1="160" x2="230" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="310" y1="160" x2="310" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="390" y1="160" x2="390" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="470" y1="160" x2="470" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="550" y1="160" x2="550" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="630" y1="160" x2="630" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="400" x2="630" y2="400" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="320" x2="630" y2="320" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="240" x2="630" y2="240" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="160" x2="630" y2="160" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="230" y1="400" x2="550" y2="320" style="stroke: #ff9900; stroke-width: 3.5; stroke-dasharray: 6,4;" />
  <rect x="190" y="360" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="270" y="360" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="350" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="430" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="510" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <circle cx="230" cy="400" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="310" cy="400" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="390" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="470" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="550" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <text x="230" y="425" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(1,1)</text>
  <text x="310" y="425" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(2,1)</text>
  <text x="390" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(3,2)</text>
  <text x="470" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(4,2)</text>
  <text x="550" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(5,2)</text>
  <line x1="100" y1="480" x2="680" y2="480" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
  <line x1="150" y1="520" x2="150" y2="120" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
  <text x="675" y="505" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">X</text>
  <text x="130" y="130" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">Y</text>
  <text x="150" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">0</text>
  <text x="230" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
  <text x="310" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
  <text x="390" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
  <text x="470" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">4</text>
  <text x="550" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">5</text>
  <text x="630" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">6</text>
  <text x="125" y="405" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
  <text x="125" y="325" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
  <text x="125" y="245" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
  <g transform="translate(180, 80)">
    <rect x="0" y="0" width="440" height="40" style="fill: #f9f9f9; stroke: #dddddd; stroke-width: 1; rx: 4;" />
    <line x1="15" y1="20" x2="45" y2="20" style="stroke: #ff9900; stroke-width: 3.5; stroke-dasharray: 4,3;" />
    <text x="55" y="25" style="font-family: Arial; font-size: 12px; fill: #333333;">理想直线 (P₀-P₁)</text>
    <rect x="175" y="12" width="16" height="16" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
    <circle cx="183" cy="20" r="4" style="fill: #2e7d32;" />
    <text x="200" y="25" style="font-family: Arial; font-size: 12px; fill: #333333;">光栅化选择的像素点</text>
  </g>
</svg>
</div>

<div style="page-break-after: always;"></div>

**4. 【直线上栅化计算（0,0 至 5,2）】**
已知直线起点为 $P_0(0,0)$，终点为 $P_1(5,2)$。请分别使用中点画线算法和 Bresenham 算法进行光栅化离散点列计算：

*(1)* 采用中点画线算法（双倍放大形式），写出直线方程系数 $a, b$，计算决策变量初值 $d_0$，列出各步决策变量 $d$ 的值与选点结果坐标。(5分)

> **【参考答案】**
> - **直线参数计算**：
>   - $\Delta x = 5$, $\Delta y = 2$
>   - 直线系数：$a = y_0 - y_1 = -2$，$b = x_1 - x_0 = 5$
> - **中点判别式初值 $d_0$**：
>   $$
>   d_0 = \Delta x - 2\Delta y = 5 - 2(2) = 1
>   $$
> - **递推更新算式**：
>   - 当 $d_i \ge 0 \implies$ 下一步选右下点，且 $d_{i+1} = d_i + 2a = d_i - 4$；
>   - 当 $d_i < 0 \implies$ 下一步选右上点，且 $d_{i+1} = d_i + 2a + 2b = d_i + 6$。
> - **递推计算过程**：
>   - **第 $0$ 步**：$x = 0, y = 0$。因为 $d_0 = 1 \ge 0$，选择右下点 $(1,0)$。
>     更新：$d_1 = 1 - 4 = -3$。
>   - **第 $1$ 步**：$x = 1, y = 0$。因为 $d_1 = -3 < 0$，选择右上点 $(2,1)$。
>     更新：$d_2 = -3 + 6 = 3$。
>   - **第 $2$ 步**：$x = 2, y = 1$。因为 $d_2 = 3 \ge 0$，选择右下点 $(3,1)$。
>     更新：$d_3 = 3 - 4 = -1$。
>   - **第 $3$ 步**：$x = 3, y = 1$。因为 $d_3 = -1 < 0$，选择右上点 $(4,2)$。
>     更新：$d_4 = -1 + 6 = 5$。
>   - **第 $4$ 步**：$x = 4, y = 2$。因为 $d_4 = 5 \ge 0$，选择右下点 $(5,2)$。
>   - 最终中点画线法的点列为：$(0,0), (1,0), (2,1), (3,1), (4,2), (5,2)$。

*(2)* 采用 Bresenham 算法（整数优化形式），写出误差项初值 $d'_0$，列出各步的 $d$ 值更新与绘制点坐标 $(x,y)$ 的完整递推计算过程表格。(5分)

> **【参考答案】**
> - **Bresenham 参量**：
>   - $\Delta x = 5$, $\Delta y = 2$
>   - 误差初值：$d_0 = 2\Delta y - \Delta x = 2(2) - 5 = -1$
>   - 决策更新增量：当 $d \ge 0$ 时为 $2\Delta y - 2\Delta x = -6$；当 $d < 0$ 时为 $2\Delta y = 4$。
> - **Bresenham 递推计算表**：
> 
>   | 步数 | 绘制像素点坐标 $(x, y)$ | 误差项 $d$ | 判定条件 | 下一步纵坐标更新 |
>   | :---: | :---: | :---: | :---: | :---: |
>   | 0 | $(0, 0)$ | $-1$ | $d < 0$ | $y$ 不变 ($y=0$) |
>   | 1 | $(1, 0)$ | $-1 + 4 = 3$ | $d \ge 0$ | $y$ 递增 $1$ ($y=1$) |
>   | 2 | $(2, 1)$ | $3 - 6 = -3$ | $d < 0$ | $y$ 不变 ($y=1$) |
>   | 3 | $(3, 1)$ | $-3 + 4 = 1$ | $d \ge 0$ | $y$ 递增 $1$ ($y=2$) |
>   | 4 | $(4, 2)$ | $1 - 6 = -5$ | $d < 0$ | $y$ 不变 ($y=2$) |
>   | 5 | $(5, 2)$ | — | 已达终点 | — |
> 
> - 最终离散点列为：$(0,0), (1,0), (2,1), (3,1), (4,2), (5,2)$。

<div align="center">
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 600" width="100%" height="100%" style="background-color: #ffffff; max-width: 600px; display: block; margin: auto;">
  <defs>
    <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M 0 0 L 10 5 L 0 10 z" fill="#333333" />
    </marker>
  </defs>
  <text x="400" y="40" style="font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; font-size: 20px; font-weight: bold; fill: #111111; text-anchor: middle;">中点画线与Bresenham算法离散像素点分布 (0,0) 到 (5,2)</text>
  <line x1="230" y1="160" x2="230" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="310" y1="160" x2="310" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="390" y1="160" x2="390" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="470" y1="160" x2="470" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="550" y1="160" x2="550" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="630" y1="160" x2="630" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="400" x2="630" y2="400" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="320" x2="630" y2="320" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="240" x2="630" y2="240" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="160" x2="630" y2="160" style="stroke: #e0e0e0; stroke-width: 1;" />
  <line x1="150" y1="480" x2="550" y2="320" style="stroke: #ff9900; stroke-width: 3.5; stroke-dasharray: 6,4;" />
  <rect x="110" y="440" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="190" y="440" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="270" y="360" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="350" y="360" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="430" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <rect x="510" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
  <circle cx="150" cy="480" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="230" cy="480" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="310" cy="400" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="390" cy="400" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="470" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <circle cx="550" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
  <text x="150" y="505" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(0,0)</text>
  <text x="230" y="505" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(1,0)</text>
  <text x="310" y="425" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(2,1)</text>
  <text x="390" y="425" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(3,1)</text>
  <text x="470" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(4,2)</text>
  <text x="550" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(5,2)</text>
  <line x1="100" y1="480" x2="680" y2="480" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
  <line x1="150" y1="520" x2="150" y2="120" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
  <text x="675" y="505" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">X</text>
  <text x="130" y="130" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">Y</text>
  <text x="150" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">0</text>
  <text x="230" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
  <text x="310" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
  <text x="390" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
  <text x="470" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">4</text>
  <text x="550" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">5</text>
  <text x="630" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">6</text>
  <text x="125" y="405" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
  <text x="125" y="325" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
  <text x="125" y="245" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
  <g transform="translate(180, 80)">
    <rect x="0" y="0" width="440" height="40" style="fill: #f9f9f9; stroke: #dddddd; stroke-width: 1; rx: 4;" />
    <line x1="15" y1="20" x2="45" y2="20" style="stroke: #ff9900; stroke-width: 3.5; stroke-dasharray: 4,3;" />
    <text x="55" y="25" style="font-family: Arial; font-size: 12px; fill: #333333;">理想直线</text>
    <rect x="175" y="12" width="16" height="16" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
    <circle cx="183" cy="20" r="4" style="fill: #2e7d32;" />
    <text x="200" y="25" style="font-family: Arial; font-size: 12px; fill: #333333;">光栅化选择的像素点</text>
  </g>
</svg>
</div>

---

## 二、 改进的活动边表填充算法

<div style="page-break-after: always;"></div>

**5. 【改进的活动边表（AET）多边形填充】**
已知某多边形的顶点坐标分别为：$A(2, 1)$、$B(6, 1)$、$C(6, 5)$、$D(4, 3)$、$E(2, 5)$、$F(1, 4)$。若采用多边形扫描转换的改进活动边表算法进行填充，且边表与活动边表的结点结构统一规定为：`[y_max | x_ymin | 1/k | next]`（其中 $y_{\max}$ 为边最大纵坐标，$x_{ymin}$ 为边最小纵坐标处的横坐标，$1/k$ 为边斜率的倒数）。请完成以下设计计算：

*(1)* 构建该多边形的完整边表（ET 表），标明每个扫描线链表的挂接边及其具体参数。(5分)

> **【参考答案】**
> - **各边参数提取分析**：
>   - $AB$ 边：端点 $(2,1)$ 和 $(6,1)$，水平边，不装入边表 ET。
>   - $BC$ 边：端点 $(6,1)$ 和 $(6,5)$，$y_{min}=1, y_{max}=5, x_{ymin}=6, 1/k=0$。
>   - $FA$ 边：端点 $(1,4)$ 和 $(2,1)$，$y_{min}=1, y_{max}=4, x_{ymin}=2, 1/k = \frac{1-2}{4-1} = -1/3$。
>   - $CD$ 边：端点 $(4,3)$ 和 $(6,5)$，$y_{min}=3, y_{max}=5, x_{ymin}=4, 1/k = \frac{6-4}{5-3} = 1$。
>   - $DE$ 边：端点 $(4,3)$ 和 $(2,5)$，$y_{min}=3, y_{max}=5, x_{ymin}=4, 1/k = \frac{2-4}{5-3} = -1$。
>   - $EF$ 边：端点 $(1,4)$ 和 $(2,5)$，$y_{min}=4, y_{max}=5, x_{ymin}=1, 1/k = \frac{2-1}{5-4} = 1$。
> - **按 $y_{\min}$ 挂接并排序构建 ET 表**：
>   - $ET[1] \to [4 \mid 2 \mid -1/3] \to [5 \mid 6 \mid 0]$
>   - $ET[2] \to \text{null}$
>   - $ET[3] \to [5 \mid 4 \mid -1] \to [5 \mid 4 \mid 1]$
>   - $ET[4] \to [5 \mid 1 \mid 1]$
>   - $ET[5] \to \text{null}$

*(2)* 写出扫描线从下往上递增到 $y = 3$ 时的活动边表（AET 表）的各个结点参数状态（按 $x$ 值从小到大排序）。(3分)

> **【参考答案】**
> - **递推过程**：
>   - **$y=1$ 时**：调入 $ET[1]$，AET 为 $[4 \mid 2 \mid -1/3] \to [5 \mid 6 \mid 0]$。
>   - **$y=2$ 时**：更新交点横坐标 $x_{y=2} = x_{y=1} + 1/k$。
>     - $FA$ 边：$x = 2 - 1/3 = 5/3 \approx 1.67$；
>     - $BC$ 边：$x = 6 + 0 = 6$。
>     AET 为 $[4 \mid 5/3 \mid -1/3] \to [5 \mid 6 \mid 0]$。
>   - **$y=3$ 时**：
>     - 递增更新：$FA$ 边 $x = 5/3 - 1/3 = 4/3 \approx 1.33$；$BC$ 边 $x = 6 + 0 = 6$。
>     - 调入 $ET[3]$ 新边：$DE[5 \mid 4 \mid -1]$ 和 $CD[5 \mid 4 \mid 1]$。
>     - 合并后按当前 $x$ 值升序重排：$FA$ ($x=4/3$) $\to$ $DE$ ($x=4$) $\to$ $CD$ ($x=4$) $\to$ $BC$ ($x=6$)。
>   - **$y=3$ 时的 AET 状态为**：
>     $$
>     AET \to [4 \mid 4/3 \mid -1/3] \to [5 \mid 4 \mid -1] \to [5 \mid 4 \mid 1] \to [5 \mid 6 \mid 0]
>     $$
>     （或小数记为：$[4 \mid 1.33 \mid -0.33] \to [5 \mid 4 \mid -1] \to [5 \mid 4 \mid 1] \to [5 \mid 6 \mid 0]$）

*(3)* 写出扫描线 $y = 3$ 时的有效填充像素区间。(2分)

> **【参考答案】**
> - AET表对应 $y=3$ 时的 $x$ 轴四个交点为：$x_1 = 4/3 \approx 1.33$，$x_2 = 4$，$x_3 = 4$，$x_4 = 6$。
> - 配对填充段：$[1.33, 4]$ 和 $[4, 6]$。
> - 按扫描线像素取整规则（通常为左闭右开原则 $[x_i, x_{i+1})$，即区间右端交点处像素不着色）：
>   - 区间一 $[1.33, 4)$ 填充像素横坐标为：$x = 2, 3$。
>   - 区间二 $[4, 6)$ 填充像素横坐标为：$x = 4, 5$。
> - 综合所得，扫描线 $y=3$ 时的有效填充像素横坐标区间为 $[2, 6)$ 内的整数，即像素横坐标为：
>   $$
>   x = 2, 3, 4, 5
>   $$

<div align="center">
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 450 380" width="100%" height="100%" style="background-color: #ffffff; max-width: 500px; display: block; margin: auto;">
  <line x1="90" y1="40" x2="90" y2="320" stroke="#e5e7eb" stroke-width="1" />
  <line x1="130" y1="40" x2="130" y2="320" stroke="#e5e7eb" stroke-width="1" />
  <line x1="170" y1="40" x2="170" y2="320" stroke="#e5e7eb" stroke-width="1" />
  <line x1="210" y1="40" x2="210" y2="320" stroke="#e5e7eb" stroke-width="1" />
  <line x1="250" y1="40" x2="250" y2="320" stroke="#e5e7eb" stroke-width="1" />
  <line x1="290" y1="40" x2="290" y2="320" stroke="#e5e7eb" stroke-width="1" />
  <line x1="330" y1="40" x2="330" y2="320" stroke="#e5e7eb" stroke-width="1" />
  <line x1="370" y1="40" x2="370" y2="320" stroke="#e5e7eb" stroke-width="1" />
  <line x1="50" y1="280" x2="380" y2="280" stroke="#e5e7eb" stroke-width="1" />
  <line x1="50" y1="240" x2="380" y2="240" stroke="#e5e7eb" stroke-width="1" />
  <line x1="50" y1="200" x2="380" y2="200" stroke="#e5e7eb" stroke-width="1" />
  <line x1="50" y1="160" x2="380" y2="160" stroke="#e5e7eb" stroke-width="1" />
  <line x1="50" y1="120" x2="380" y2="120" stroke="#e5e7eb" stroke-width="1" />
  <line x1="50" y1="80" x2="380" y2="80" stroke="#e5e7eb" stroke-width="1" />
  <line x1="50" y1="40" x2="380" y2="40" stroke="#e5e7eb" stroke-width="1" />
  <line x1="40" y1="320" x2="380" y2="320" stroke="#374151" stroke-width="2" />
  <polygon points="380,320 372,316 372,324" fill="#374151" />
  <text x="385" y="325" font-family="sans-serif" font-size="14" fill="#374151">x</text>
  <line x1="50" y1="330" x2="50" y2="40" stroke="#374151" stroke-width="2" />
  <polygon points="50,40 46,48 54,48" fill="#374151" />
  <text x="45" y="30" font-family="sans-serif" font-size="14" fill="#374151">y</text>
  <text x="40" y="335" font-family="sans-serif" font-size="12" fill="#6b7280">0</text>
  <text x="85" y="335" font-family="sans-serif" font-size="12" fill="#6b7280">1</text>
  <text x="125" y="335" font-family="sans-serif" font-size="12" fill="#6b7280">2</text>
  <text x="165" y="335" font-family="sans-serif" font-size="12" fill="#6b7280">3</text>
  <text x="205" y="335" font-family="sans-serif" font-size="12" fill="#6b7280">4</text>
  <text x="245" y="335" font-family="sans-serif" font-size="12" fill="#6b7280">5</text>
  <text x="285" y="335" font-family="sans-serif" font-size="12" fill="#6b7280">6</text>
  <text x="325" y="335" font-family="sans-serif" font-size="12" fill="#6b7280">7</text>
  <text x="365" y="335" font-family="sans-serif" font-size="12" fill="#6b7280">8</text>
  <text x="30" y="285" font-family="sans-serif" font-size="12" fill="#6b7280">1</text>
  <text x="30" y="245" font-family="sans-serif" font-size="12" fill="#6b7280">2</text>
  <text x="30" y="205" font-family="sans-serif" font-size="12" fill="#6b7280">3</text>
  <text x="30" y="165" font-family="sans-serif" font-size="12" fill="#6b7280">4</text>
  <text x="30" y="125" font-family="sans-serif" font-size="12" fill="#6b7280">5</text>
  <text x="30" y="85" font-family="sans-serif" font-size="12" fill="#6b7280">6</text>
  <polygon points="130,280 290,280 290,120 210,200 130,120 90,160" fill="#93c5fd" fill-opacity="0.3" stroke="#2563eb" stroke-width="2" />
  <circle cx="130" cy="280" r="4" fill="#1d4ed8" />
  <text x="135" y="295" font-family="sans-serif" font-size="12" fill="#1e3a8a">A(2, 1)</text>
  <circle cx="290" cy="280" r="4" fill="#1d4ed8" />
  <text x="295" y="295" font-family="sans-serif" font-size="12" fill="#1e3a8a">B(6, 1)</text>
  <circle cx="290" cy="120" r="4" fill="#1d4ed8" />
  <text x="295" y="115" font-family="sans-serif" font-size="12" fill="#1e3a8a">C(6, 5)</text>
  <circle cx="210" cy="200" r="4" fill="#1d4ed8" />
  <text x="215" y="215" font-family="sans-serif" font-size="12" fill="#1e3a8a">D(4, 3)</text>
  <circle cx="130" cy="120" r="4" fill="#1d4ed8" />
  <text x="120" y="110" font-family="sans-serif" font-size="12" fill="#1e3a8a">E(2, 5)</text>
  <circle cx="90" cy="160" r="4" fill="#1d4ed8" />
  <text x="65" y="155" font-family="sans-serif" font-size="12" fill="#1e3a8a">F(1, 4)</text>
</svg>
</div>

---

## 三、 Liang-Barsky 算法直线裁剪

<div style="page-break-after: always;"></div>

**6. 【Liang-Barsky 直线段裁剪算法计算】**
已知裁剪窗口为一个矩形区域，其边界值分别为：$x_{w\min} = 0$，$x_{w\max} = 2$，$y_{w\min} = 0$，$y_{w\max} = 2$。待裁剪直线段的起点坐标为 $A(1, -1)$，终点坐标为 $B(2, 3)$。请完成以下分析与计算：

*(1)* 写出 Liang-Barsky 算法的参数化线段表达式，并计算出直线段与四个裁剪边界对应的参数组 $p_k$ 与 $q_k \quad (k=1,2,3,4)$。(4分)

> **【参考答案】**
> - **参数化线段表达式**：
>   - 直线起点 $A(1,-1)$，终点 $B(2,3)$，横纵坐标位移量为：$\Delta x = 2 - 1 = 1$，$\Delta y = 3 - (-1) = 4$。
>   - 直线的参数化方程为：
>     $$
>     \begin{cases}
>     x = 1 + u \cdot 1 \\
>     y = -1 + u \cdot 4
>     \end{cases} \quad (0 \le u \le 1)
>     $$
> - **边界参数组 $p_k$ 与 $q_k$ 的计算**（根据公式 $u \cdot p_k \le q_k$）：
>   - **左边界** ($k=1$, $x_{w\min}=0$):
>     $$
>     p_1 = -\Delta x = -1, \quad q_1 = x_0 - x_{w\min} = 1 - 0 = 1
>     $$
>   - **右边界** ($k=2$, $x_{w\max}=2$):
>     $$
>     p_2 = \Delta x = 1, \quad q_2 = x_{w\max} - x_0 = 2 - 1 = 1
>     $$
>   - **下边界** ($k=3$, $y_{w\min}=0$):
>     $$
>     p_3 = -\Delta y = -4, \quad q_3 = y_0 - y_{w\min} = -1 - 0 = -1
>     $$
>   - **上边界** ($k=4$, $y_{w\max}=2$):
>     $$
>     p_4 = \Delta y = 4, \quad q_4 = y_{w\max} - y_0 = 2 - (-1) = 3
>     $$

*(2)* 计算得出入点参数 $u_{\max}$ 与出点参数 $u_{\min}$，写出详细的边界相交类型判定过程。(4分)

> **【参考答案】**
> - **判定规则**：
>   - 若 $p_k < 0$，该边界对应的交点为由外到内的“入点”，用于更新 $u_{\max}$；
>   - 若 $p_k > 0$，该边界对应的交点为由内到外的“出点”，用于更新 $u_{\min}$；
>   - 若 $p_k = 0$ 且 $q_k < 0$，线段完全在窗口外部平行，直接拒绝。
> - **计算各交点参数并分类**：
>   - **入点组** ($p_k < 0$):
>     - 左边界交点 ($k=1$): $u_1 = q_1/p_1 = -1$
>     - 下边界交点 ($k=3$): $u_3 = q_3/p_3 = -1/(-4) = 0.25$
>     - 入点决策参数：
>       $$
>       u_{\max} = \max(0, u_1, u_3) = \max(0, -1, 0.25) = 0.25
>       $$
>   - **出点组** ($p_k > 0$):
>     - 右边界交点 ($k=2$): $u_2 = q_2/p_2 = 1$
>     - 上边界交点 ($k=4$): $u_4 = q_4/p_4 = 3/4 = 0.75$
>     - 出点决策参数：
>       $$
>       u_{\min} = \min(1, u_2, u_4) = \min(1, 1, 0.75) = 0.75
>       $$

*(3)* 根据 Liang-Barsky 算法的裁剪准则，判定该线段是否被接受，并求出窗口内部裁剪后的端点实际坐标值。(2分)

> **【参考答案】**
> - **线段可接受判定**：
>   - 因为 $u_{\max} = 0.25 \le u_{\min} = 0.75$，所以该线段在窗口内存在可见段，**应该接受该线段**。
>   - 其有效的可见参数段范围为：$u \in [0.25, 0.75]$。
> - **裁剪后端点实际坐标计算**：
>   - 将 $u = u_{\max} = 0.25$ 代入参数方程，求得裁剪后起点 $P_1$：
>     $$
>     x_1 = 1 + 0.25 \times 1 = 1.25, \quad y_1 = -1 + 0.25 \times 4 = 0
>     $$
>     即 $P_1(1.25, 0)$。
>   - 将 $u = u_{\min} = 0.75$ 代入参数方程，求得裁剪后终点 $P_2$：
>     $$
>     x_2 = 1 + 0.75 \times 1 = 1.75, \quad y_2 = -1 + 0.75 \times 4 = 2
>     $$
>     即 $P_2(1.75, 2)$。
>   - 最终裁剪窗口内部的线段端点坐标分别为：$(1.25, 0)$ 和 $(1.75, 2)$。

<div align="center">
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 400 400" width="100%" height="100%" style="background-color: #ffffff; max-width: 500px; display: block; margin: auto;">
  <line x1="60" y1="20" x2="60" y2="380" stroke="#e5e7eb" stroke-width="1" />
  <line x1="180" y1="20" x2="180" y2="380" stroke="#e5e7eb" stroke-width="1" />
  <line x1="240" y1="20" x2="240" y2="380" stroke="#e5e7eb" stroke-width="1" />
  <line x1="300" y1="20" x2="300" y2="380" stroke="#e5e7eb" stroke-width="1" />
  <line x1="360" y1="20" x2="360" y2="380" stroke="#e5e7eb" stroke-width="1" />
  <line x1="30" y1="380" x2="370" y2="380" stroke="#e5e7eb" stroke-width="1" />
  <line x1="30" y1="320" x2="370" y2="320" stroke="#e5e7eb" stroke-width="1" />
  <line x1="30" y1="200" x2="370" y2="200" stroke="#e5e7eb" stroke-width="1" />
  <line x1="30" y1="140" x2="370" y2="140" stroke="#e5e7eb" stroke-width="1" />
  <line x1="30" y1="80" x2="370" y2="80" stroke="#e5e7eb" stroke-width="1" />
  <line x1="30" y1="20" x2="370" y2="20" stroke="#e5e7eb" stroke-width="1" />
  <rect x="120" y="140" width="120" height="120" fill="#22c55e" fill-opacity="0.1" stroke="#16a34a" stroke-width="2" />
  <line x1="30" y1="260" x2="340" y2="260" stroke="#374151" stroke-width="2" />
  <polygon points="340,260 332,256 332,264" fill="#374151" />
  <text x="345" y="265" font-family="sans-serif" font-size="14" fill="#374151">x</text>
  <line x1="120" y1="375" x2="120" y2="30" stroke="#374151" stroke-width="2" />
  <polygon points="120,30 116,38 124,38" fill="#374151" />
  <text x="115" y="20" font-family="sans-serif" font-size="14" fill="#374151">y</text>
  <text x="50" y="275" font-family="sans-serif" font-size="12" fill="#6b7280">-1</text>
  <text x="110" y="275" font-family="sans-serif" font-size="12" fill="#6b7280">0</text>
  <text x="175" y="275" font-family="sans-serif" font-size="12" fill="#6b7280">1</text>
  <text x="235" y="275" font-family="sans-serif" font-size="12" fill="#6b7280">2</text>
  <text x="295" y="275" font-family="sans-serif" font-size="12" fill="#6b7280">3</text>
  <text x="100" y="325" font-family="sans-serif" font-size="12" fill="#6b7280">-1</text>
  <text x="100" y="205" font-family="sans-serif" font-size="12" fill="#6b7280">1</text>
  <text x="100" y="145" font-family="sans-serif" font-size="12" fill="#6b7280">2</text>
  <text x="100" y="85" font-family="sans-serif" font-size="12" fill="#6b7280">3</text>
  <line x1="180" y1="320" x2="240" y2="80" stroke="#2563eb" stroke-width="3" />
  <circle cx="180" cy="320" r="4" fill="#ef4444" />
  <text x="190" y="325" font-family="sans-serif" font-size="12" fill="#ef4444">A(1, -1)</text>
  <circle cx="240" cy="80" r="4" fill="#ef4444" />
  <text x="245" y="75" font-family="sans-serif" font-size="12" fill="#ef4444">B(2, 3)</text>
  <text x="130" y="160" font-family="sans-serif" font-size="12" fill="#16a34a">Window</text>
</svg>
</div>
