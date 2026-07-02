# 计算机图形学期末复习提纲与考点详析 (2026_review_Sonder9999)

---

# 考试基本信息

## 一、 考试范围与重点章节

* **第 1 章**：绪论（基础概念与学科关联）
* **第 2 章**：图形系统（帧缓存计算与流水线阶段）
* **第 3 章**：二维基本图形光栅化与裁剪 (**重点**，包含中点法、Bresenham、多边形扫描转换、Liang-Barsky、多边形裁剪)
* **第 4 章**：图形几何变换 (**重点**，包含齐次坐标、复合变换、OpenGL 变换应用)
* **第 5 章**：三维观察 (**重点**，包含投影分类、透视投影、灭点、三视图)
* **第 6 章**：三维造型（实体造型、细分与 CSG 方法）
* **第 7 章**：真实感图形技术 (**重点**，包含 Z-Buffer 消隐、光照模型、三种着色算法、光线跟踪)

---

## 二、 题型分布与分值

* **单选题 (30分)**：$15 \times 2'$，包括程序代码选择 5 题
* **判断题 (10分)**：$10 \times 1'$
* **简答题 (30分)**：$5 \times 6'$
* **综合计算题 (30分)**：$3 \times 10'$，典型题型包括：
  - **画线算法**：中点画线算法、Bresenham 画线算法的基本思想、判别式递推及画点位置计算。
  - **多边形填充**：改进的活动边表（AET）算法，手动补充或构建 ET 表与 AET 表。
  - **裁剪算法**：Liang-Barsky 算法裁剪直线段的参数计算与执行过程。

---

# 第 1 章 绪论

* **计算机图形学的定义**：

  - 计算机图形学（Computer Graphics, 简称 CG）是研究如何利用计算机将**数学模型**或**几何数据**转换为**图形/图像**并在显示设备上显示的学科。
* **主要研究内容**：

  - **建模 (Modeling)**：如何在计算机中表示和存储三维物体的几何形状（如多边形网格、曲面、实体表示）。
  - **渲染 (Rendering)**：如何根据光照、材质、视角计算物体的颜色和阴影，生成具有真实感的图像。
  - **动画 (Animation)**：如何模拟物体随时间变化的位置、形状和外观。
  - **人机交互 (Interaction)**：用户与图形系统进行实时交互的软硬件技术。
* **与相关学科之间的关联与区别**：

  | 学科名称                     | 输入内容          | 输出内容                | 典型任务与研究方向             |
  | :--------------------------- | :---------------- | :---------------------- | :----------------------------- |
  | **计算机图形学 (CG)**  | 几何模型/描述数据 | 图像                    | 场景渲染、游戏开发、动画制作   |
  | **数字图像处理 (DIP)** | 图像              | 图像                    | 图像增强、去噪、滤波、图像分割 |
  | **计算机视觉 (CV)**    | 图像/视频         | 物理场景的描述/三维模型 | 目标检测、人脸识别、三维重建   |
  | **计算几何 (CGGeo)**   | 几何问题描述      | 几何算法/数据结构       | 碰撞检测、网格剖分、凸包计算   |
  | **模式识别 (PR)**      | 图像/特征数据     | 类别标签/决策判断       | 字符识别、分类器设计、数据分析 |
* **学科流向示意图**：

  ```mermaid
  graph TD
      Model["几何模型 (数学描述)"] -->|计算机图形学 CG| Image["图像 (像素阵列)"]
      Image -->|计算机视觉 CV / 模式识别 PR| Model
      Image -->|图像处理 DIP| Image2["处理后的图像"]
  ```
* **计算机图形学的核心目标**：

  - **逼真度 (Realism)**：生成与真实世界难以区分的图像。
  - **交互性 (Interactivity)**：系统对用户操作的实时响应能力（通常要求达到 $30\text{ fps}$ 以上）。
  - **计算效率 (Efficiency)**：在有限的时间与硬件资源内完成图形的生成与渲染。
* **计算机图形学的应用领域**：

  - **计算机辅助设计与制造 (CAD/CAM)**：飞机、汽车、建筑物的结构设计。
  - **科学计算可视化**：将复杂的数据（医学 MRI、气象风向、物理仿真）以直观图形展现。
  - **虚拟现实 (VR) 与增强现实 (AR)**：构建沉浸式交互场景。
  - **数字娱乐与影视游戏**：电影特效、3D 游戏引擎开发。
  - **用户图形界面 (GUI)**：现代操作系统及应用的人机交互媒介。
* **计算机图形学的发展历程**：

  - **矢量/画笔式显示时代**：通过电子束在示波器上绘制线段，刷新率受限，不支持面填充。
  - **光栅扫描显示时代**：引入帧缓存概念，逐像素扫描，支持复杂色彩与实体填充。
  - **GPU 与硬件加速时代**：专用图形芯片的出现，使得大规模并行矩阵计算与实时光追成为现实。

---

# 第 2 章 图形系统

* **计算机图形系统的组成分类**：

  - **图形硬件系统**：包括输入设备、输出设备、图形处理器（GPU）、系统内存以及帧缓存（Frame Buffer）。
  - **图形软件系统**：包括图形应用软件（如 AutoCAD、Blender）和图形支撑软件/API（如 OpenGL、DirectX、Vulkan）。
* **常见的图形输入、输出设备**：

  - **输入设备**：键盘、二维鼠标、图形输入板/数位板（Tablet）、三维扫描仪、数据手套。
  - **输出设备**：液晶显示器（LCD）、有机发光二极管显示器（OLED）、投影仪、阴极射线管显示器（CRT，历史）、绘图仪。
* **光栅扫描显示系统的组成**：

  - 核心组件包括：**系统 CPU**、**系统内存**、**图形处理器 (GPU)**、**帧缓存 (Frame Buffer)**、**视频控制器 (Video Controller)** 以及 **显示监视器**。
  - 视频控制器以固定的刷新频率（如 $60\text{Hz}$）循环读取帧缓存中的像素值，通过数模转换（DAC）送往显示器显示。
* **帧缓存的概念和大小的计算**：

  - **帧缓存 (Frame Buffer)**：用于存储屏幕上所有像素颜色或灰度值的专用内存区域。
  - **计算公式**：

    $$
    V \ge M \times N \times \lceil \log_2 K \rceil
    $$

    其中，$M \times N$ 为屏幕分辨率（列数 $\times$ 行数），$K$ 为显示颜色的种类数（或灰度级数），$\lceil \log_2 K \rceil$ 为每个像素占用的位数（Bit Depth，位深）。
  - **注意单位换算**：

    - $1\text{ Byte} = 8\text{ bits}$；
    - $1\text{ KB} = 1024\text{ Bytes}$；
    - $1\text{ MB} = 1024\text{ KB} = 1024 \times 1024\text{ Bytes}$。

  > [!IMPORTANT]
  > **典型例题**：若显示器的分辨率为 $1024 \times 768$，能显示 $256$ 级灰度。求所需的最小帧缓存容量。
  >
  > - **解答步骤**：
  >   1. 灰度级 $K = 256$，则位深为 $\log_2 256 = 8\text{ bits}$（即 $1\text{ Byte}$）。
  >   2. 帧缓存总容量：
  >
  >      $$
  >      V = 1024 \times 768 \times 8\text{ bits} = 786,432\text{ Bytes}
  >      $$
  >   3. 换算为 KB/MB：
  >
  >      $$
  >      V = \frac{786,432}{1024} = 768\text{ KB} = 0.75\text{ MB}
  >      $$
  >
* **常见的图形应用软件和图形支撑软件**：

  - **支撑软件 (Graphics Library API)**：OpenGL、WebGL、Direct3D、Vulkan、Metal。
  - **应用软件**：AutoCAD（工程设计）、Blender/3ds Max/Maya（3D建模与动画）、Photoshop（图像编辑）。
* **图形流水线 (Graphics Pipeline) 的三个阶段及其作用**：

  ```mermaid
  graph LR
      AppStage["应用程序阶段<br>(Application)"] --> GeoStage["几何阶段<br>(Geometry)"]
      GeoStage --> RasterStage["光栅化与像素处理阶段<br>(Rasterization / Pixel Processing)"]
  ```

  - **应用程序阶段 (Application Stage)**：
    - *运行设备*：CPU。
    - *主要作用*：场景物理模拟、碰撞检测、视锥体粗选剔除、用户输入响应、加速判定算法执行，向几何阶段发送需要绘制的几何图元。
  - **几何阶段 (Geometry Stage)**：
    - *运行设备*：GPU 顶点着色器（Vertex Shader）等。
    - *主要作用*：进行顶点坐标变换（包括模型变换、观察变换、投影变换）、顶点光照计算与明暗处理、裁剪剔除视锥体外的非可见物体、最终的屏幕视口映射。
  - **光栅化与像素处理阶段 (Rasterization / Pixel Processing Stage)**：
    - *运行设备*：GPU 片段着色器（Fragment/Pixel Shader）等。
    - *主要作用*：将连续的三角形网格图元离散化为离散的片元/像素，在片元之间进行属性的线性插值（如纹理坐标、法向），执行纹理采样、光照模型逐像素计算，进行深度测试（Z-Buffer 消隐）、模板测试和 Alpha 混合，最终将颜色结果写入帧缓存供显示。

---

# 第 3 章 二维基本图形光栅化与裁剪

## 一、 直线段与圆弧光栅化算法

### 1. DDA (数值微分) 画线法

- **基本思想**：利用微分方程 $y_{i+1} = y_i + k \cdot \Delta x$，通过逐步累加斜率 $k$ 来计算下一个像素的坐标，并对结果取整。
- **步长计算与更新规则**：

  - 当斜率 $|k| \le 1$ 时，以 $x$ 为主步进方向，$\Delta x = 1$：

    $$
    \begin{cases}
    x_{i+1} = x_i + 1 \\
    y_{i+1} = y_i + k
    \end{cases}
    $$
  - 当斜率 $|k| > 1$ 时，以 $y$ 为主步进方向，$\Delta y = 1$：

    $$
    \begin{cases}
    y_{i+1} = y_i + 1 \\
    x_{i+1} = x_i + \frac{1}{k}
    \end{cases}
    $$
- **缺点**：每次迭代都包含浮点数加法与四舍五入取整操作，硬件实现效率低。

---

### 2. Bresenham 画线算法

- **基本思想**：将线段离散化问题转化为寻找距离理想直线最近的网格点。通过逐步递推误差判定值，最终消除浮点数与乘除法运算，仅用整数加减和移位即可完成渲染。
- **推导过程的三个演进阶段**（以第一象限内、斜率 $0 \le k \le 1$ 的直线为例，设起点为 $(x_0, y_0)$，终点为 $(x_1, y_1)$，$\Delta x = x_1 - x_0$，$\Delta y = y_1 - y_0$，斜率 $k = \frac{\Delta y}{\Delta x}$）：

#### (1) Bresenham 原始算法（包含小数与 0.5 比较）

- **核心逻辑**：
  设当前步已画点为 $P_i(x_i, y_i)$，下一步 $x_{i+1} = x_i + 1$ 时，理想直线上的精确纵坐标为 $y = k(x_i + 1 - x_0) + y_0$。
  我们需要在此处决策将像素点绘制在 $y_i$ 还是 $y_i + 1$。
  - 计算理想点与上下两个候选像素的垂直距离 $d_1$ 和 $d_2$：

    $$
    d_1 = y - y_i = k(x_i + 1 - x_0) + y_0 - y_i
    $$

    $$
    d_2 = (y_i + 1) - y = y_i + 1 - \left[ k(x_i + 1 - x_0) + y_0 \right]
    $$
  - 构造两者之差：

    $$
    d_1 - d_2 = 2y - 2y_i - 1 = 2(y - y_i) - 1
    $$
  - **决策判定**：

    - 若 $d_1 - d_2 < 0 \implies y - y_i < 0.5$，即理想点更靠近下方的 $y_i$，选择 $y_{i+1} = y_i$；
    - 若 $d_1 - d_2 \ge 0 \implies y - y_i \ge 0.5$，即理想点更靠近上方的 $y_i+1$，选择 $y_{i+1} = y_i + 1$。
- **局限性**：在每一步计算中，需要对每一个像素点计算理想的浮点坐标 $y$，并与 $0.5$ 比较，这包含了浮点数加法与乘法，性能开销较大。

#### (2) 改进算法 1：消除与 0.5 的比较（引入误差 e）

- **核心逻辑**：
  与其每次计算绝对的 $y$，不如使用递推的误差项 $e$。
  设误差 $e$ 表示理想直线 $y$ 坐标与当前选定像素 $y_i$ 之间的相对偏差。从起点出发时，$e_0 = 0$。
  每次 $x$ 步进 $1$，误差累加斜率 $k$（即 $e_{\text{temp}} = e_i + k$）：

  - 若 $e_i + k < 0.5$，选择 $y_{i+1} = y_i$，下一轮累积误差更新为：

    $$
    e_{i+1} = e_i + k
    $$
  - 若 $e_i + k \ge 0.5$，说明相对偏差超过了一半像素，选择 $y_{i+1} = y_i + 1$。由于像素坐标向上移动了 $1$，在此处需要做误差修正，使得误差项继续相对于新的像素线保持正确关系：

    $$
    e_{i+1} = e_i + k - 1
    $$
- **消除 0.5**：
  为避免与常数 $0.5$ 比较，令 $e'_i = e_i - 0.5$，将比较基准转换到 $0$：

  - 初始值：

    $$
    e'_0 = -0.5
    $$
  - 每次更新 $e'_{\text{temp}} = e'_i + k$ 并与 $0$ 进行大小判断：

    - 若 $e'_i + k < 0$，选 $y_{i+1} = y_i$，更新 $e'_{i+1} = e'_i + k$。
    - 若 $e'_i + k \ge 0$，选 $y_{i+1} = y_i + 1$，更新 $e'_{i+1} = e'_i + k - 1$。
- **局限性**：虽然通过转换使得判断条件变成了与 $0$ 比较，但由于斜率 $k = \frac{\Delta y}{\Delta x}$ 仍然是浮点数，且初始值 $e'_0 = -0.5$ 也是浮点数，系统仍然需要依赖浮点运算。

#### (3) 改进算法 2：彻底摆脱浮点数（引入整型判别式 E）

- **核心逻辑**：
  为了完全消除除法和浮点数，将改进算法 1 中的不等式和更新公式两边同乘以常数 $2\Delta x$（因为 $\Delta x > 0$，这不会改变判定不等式的符号方向）。
  定义全新的整型误差决策变量 $E_i = 2\Delta x \cdot e'_i$。

  - **初始值**：

    $$
    E_0 = 2\Delta x \cdot e'_0 = 2\Delta x \cdot (-0.5) = -\Delta x
    $$
  - **每次步进的增量变化**：

    - 原本递增的斜率项 $k$ 变为：

      $$
      2\Delta x \cdot k = 2\Delta x \cdot \frac{\Delta y}{\Delta x} = 2\Delta y
      $$
    - 原本溢出时的减 $1$ 修正项变为：

      $$
      -2\Delta x
      $$
  - **最终纯整型递推公式 (Bresenham 标准形式)**：
    令误差递增中间值 $E_{\text{temp}} = E_i + 2\Delta y$。

    - 若 $E_i + 2\Delta y < 0$，下一个像素为 $(x_i + 1, y_i)$，更新：

      $$
      E_{i+1} = E_i + 2\Delta y
      $$
    - 若 $E_i + 2\Delta y \ge 0$，下一个像素为 $(x_i + 1, y_i + 1)$，更新：

      $$
      E_{i+1} = E_i + 2\Delta y - 2\Delta x
      $$
- **优势**：在这个最终算法中，初始值和增量全部被转换为整数（$\Delta x$ 和 $\Delta y$ 均为整数像素差值）。算法在主循环中**仅执行整数加减法与乘 2 运算（乘 2 在硬件层面通过左移 1 位 `<< 1` 极速完成）**，彻底排除了浮点数，执行效率极高。

#### (4) Bresenham 算法三大演进阶段核心要素独立总结

为了方便对比与快速查阅，以下将三个演进阶段的核心公式、基本思想、判定决策规则以及参数含义进行完全独立的汇总。每个阶段的计算体系均彼此独立，所有变量与公式均已展开，无需向前追溯或参考其他版本。

##### ① Bresenham 原始算法（包含小数与 0.5 比较）
*   **基本思想**：在每一步 $x$ 步进 $1$ 时，跟踪理想直线与当前像素中心的高度偏差 $d$。如果下一个临时偏差 $d + k$ 小于 $0.5$，说明理想点更靠近下方像素 $y_i$，纵坐标保持不变；若大于等于 $0.5$，说明理想点更靠近上方像素 $y_i + 1$，纵坐标加 1，并对偏差做减 1 修正。
*   **决策判别式与递推公式**：
    *   **初始误差值**：
        $$d_0 = 0$$
    *   **递推决策规则**（若当前处于步骤 $i$，已知像素点 $(x_i, y_i)$ 与偏差 $d_i$，在 $x_{i+1} = x_i + 1$ 时）：
        *   若 $d_i + k < 0.5$：
            $$y_{i+1} = y_i$$
            $$d_{i+1} = d_i + k$$
        *   若 $d_i + k \ge 0.5$：
            $$y_{i+1} = y_i + 1$$
            $$d_{i+1} = d_i + k - 1$$
*   **下一像素点位置**：
    *   若 $d_i + k < 0.5$：绘制像素点 $(x_i + 1, y_i)$。
    *   若 $d_i + k \ge 0.5$：绘制像素点 $(x_i + 1, y_i + 1)$。
*   **各参数含义**：
    *   $x_i, y_i$：当前步已画的像素点坐标。
    *   $d_i$：第 $i$ 步时理想直线纵坐标与当前绘制像素 $y_i$ 的相对偏差值（浮点数）。
    *   $k = \frac{\Delta y}{\Delta x}$：直线的斜率（浮点数，在 $0 \le k \le 1$ 范围内）。

##### ② 改进算法 1：消除与 0.5 的比较（引入相对误差 $e'$）
*   **基本思想**：为了省去每步与 $0.5$ 比较的浮点开销，将误差变量整体平移 $0.5$，定义 $e' = d - 0.5$。这样误差判定基准由“与 $0.5$ 比较”转为“与 $0$ 比较”，仅需判断代数式符号（正负）即可做出位置决策。
*   **决策判别式与递推公式**：
    *   **初始误差值**：
        $$e'_0 = -0.5$$
    *   **递推决策规则**（在 $x_{i+1} = x_i + 1$ 时）：
        *   若 $e'_i + k < 0$：
            $$y_{i+1} = y_i$$
            $$e'_{i+1} = e'_i + k$$
        *   若 $e'_i + k \ge 0$：
            $$y_{i+1} = y_i + 1$$
            $$e'_{i+1} = e'_i + k - 1$$
*   **下一像素点位置**：
    *   若 $e'_i + k < 0$：绘制像素点 $(x_i + 1, y_i)$。
    *   若 $e'_i + k \ge 0$：绘制像素点 $(x_i + 1, y_i + 1)$。
*   **各参数含义**：
    *   $x_i, y_i$：当前步已画的像素点坐标。
    *   $e'_i$：第 $i$ 步平移后的相对偏差误差项（浮点数，初始值为 $-0.5$）。
    *   $k = \frac{\Delta y}{\Delta x}$：直线的斜率（浮点数）。

##### ③ 改进算法 2：彻底摆脱浮点数（引入整型判别式 $E$）
*   **基本思想**：为了完全消除浮点数（包括斜率 $k$ 和初值 $-0.5$），将改进算法 1 中的判别式两边同时乘以常数 $2\Delta x$。定义整型决策误差变量 $E_i = 2\Delta x \cdot e'_i$。转换后，所有变量和步进增量均变为整数，算法主循环内仅需整数加减和移位运算，无任何浮点计算。
*   **决策判别式与递推公式**：
    *   **初始误差值**：
        $$E_0 = -\Delta x$$
    *   **递推决策规则**（在 $x_{i+1} = x_i + 1$ 时）：
        *   若 $E_i + 2\Delta y < 0$：
            $$y_{i+1} = y_i$$
            $$E_{i+1} = E_i + 2\Delta y$$
        *   若 $E_i + 2\Delta y \ge 0$：
            $$y_{i+1} = y_i + 1$$
            $$E_{i+1} = E_i + 2\Delta y - 2\Delta x$$
*   **下一像素点位置**：
    *   若 $E_i + 2\Delta y < 0$：绘制像素点 $(x_i + 1, y_i)$。
    *   若 $E_i + 2\Delta y \ge 0$：绘制像素点 $(x_i + 1, y_i + 1)$。
*   **各参数含义**：
    *   $x_i, y_i$：当前步已画的像素点坐标。
    *   $E_i$：第 $i$ 步的整型误差决策判定变量（整数，初始值为 $-\Delta x$）。
    *   $\Delta x = x_1 - x_0$：线段终点与起点之间的水平跨度（正整数，且 $\Delta x > 0$）。
    *   $\Delta y = y_1 - y_0$：线段终点与起点之间的垂直跨度（正整数）。
    *   $2\Delta y$：在 $x$ 步进 1 时，整型误差变量的默认增加量（整数）。
    *   $2\Delta y - 2\Delta x$：像素点向上移动时，整型误差变量的修正增加量（整数）。

---

> [!TIP]
> **经典实例演练：绘制从 $P_0(0,0)$ 到 $P_1(5,2)$ 的直线段**
>
> 已知起点为 $(0,0)$，终点为 $(5,2)$，则：
>
> - $\Delta x = 5$ 且 $\Delta y = 2$
> - 斜率 $k = \frac{2}{5} = 0.4$
> - 终点像素为 $(5,2)$，需要在每一方向步进中决定下一个像素坐标。
>
> 以下使用上述三种演进阶段的算法依次进行完整的计算递推过程展示：
>
> #### 1. Bresenham 原始算法（包含小数与 0.5 比较）
>
> <div align="center">
> <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 600" width="100%" height="100%" style="background-color: #ffffff; max-width: 600px; display: block; margin: auto;">
>   <defs>
>     <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
>       <path d="M 0 0 L 10 5 L 0 10 z" fill="#333333" />
>     </marker>
>   </defs>
>   <text x="400" y="40" style="font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; font-size: 20px; font-weight: bold; fill: #111111; text-anchor: middle;">Bresenham 原始算法演示: P₀(0,0) 到 P₁(5,2) [d 与 0.5 比较]</text>
>   <line x1="230" y1="160" x2="230" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="310" y1="160" x2="310" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="390" y1="160" x2="390" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="470" y1="160" x2="470" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="550" y1="160" x2="550" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="630" y1="160" x2="630" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="400" x2="630" y2="400" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="320" x2="630" y2="320" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="240" x2="630" y2="240" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="160" x2="630" y2="160" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="440" x2="630" y2="440" style="stroke: #bc13fe; stroke-width: 1.5; stroke-dasharray: 8,4,2,4;" />
>   <line x1="150" y1="360" x2="630" y2="360" style="stroke: #bc13fe; stroke-width: 1.5; stroke-dasharray: 8,4,2,4;" />
>   <text x="640" y="444" style="font-family: Arial; font-size: 12px; fill: #bc13fe; font-weight: bold;">y = 0.5 临界线</text>
>   <text x="640" y="364" style="font-family: Arial; font-size: 12px; fill: #bc13fe; font-weight: bold;">y = 1.5 临界线</text>
>   <line x1="150" y1="480" x2="550" y2="320" style="stroke: #ff9900; stroke-width: 3.5; stroke-dasharray: 6,4;" />
>   <rect x="110" y="440" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
>   <rect x="190" y="440" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
>   <rect x="270" y="360" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
>   <rect x="350" y="360" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
>   <rect x="430" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
>   <rect x="510" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
>   <circle cx="150" cy="480" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="230" cy="480" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="310" cy="400" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="390" cy="400" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="470" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="550" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>   <text x="150" y="505" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(0,0)</text>
>   <text x="230" y="505" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(1,0)</text>
>   <text x="310" y="425" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(2,1)</text>
>   <text x="390" y="425" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(3,1)</text>
>   <text x="470" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(4,2)</text>
>   <text x="550" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(5,2)</text>
>   <line x1="100" y1="480" x2="680" y2="480" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
>   <line x1="150" y1="520" x2="150" y2="120" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
>   <text x="675" y="505" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">X</text>
>   <text x="130" y="130" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">Y</text>
>   <text x="150" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">0</text>
>   <text x="230" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
>   <text x="310" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
>   <text x="390" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
>   <text x="470" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">4</text>
>   <text x="550" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">5</text>
>   <text x="630" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">6</text>
>   <text x="125" y="405" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
>   <text x="125" y="325" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
>   <text x="125" y="245" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
>   <g transform="translate(140, 75)">
>     <rect x="0" y="0" width="520" height="40" style="fill: #f9f9f9; stroke: #dddddd; stroke-width: 1; rx: 4;" />
>     <line x1="15" y1="20" x2="45" y2="20" style="stroke: #ff9900; stroke-width: 3; stroke-dasharray: 4,3;" />
>     <text x="55" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">理想直线段</text>
>     <line x1="140" y1="20" x2="170" y2="20" style="stroke: #bc13fe; stroke-width: 1.5; stroke-dasharray: 5,2,1,2;" />
>     <text x="180" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">0.5 误差阈值边界线</text>
>     <rect x="315" y="12" width="16" height="16" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
>     <circle cx="323" cy="20" r="4" style="fill: #2e7d32;" />
>     <text x="340" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">Bresenham选中的离散像素</text>
>   </g>
> </svg>
> </div>
>
> - **初始化**：当前点 $(x_0, y_0) = (0, 0)$，误差偏移量初始值 $d = 0$。
> - **状态更新规则**：
>   - 每次步进计算临时值 $d_{\text{temp}} = d_i + k$。
>   - 若 $d_{\text{temp}} \ge 0.5 \implies y$ 递增 $1$，且做修正 $d_{i+1} = d_{\text{temp}} - 1$。
>   - 若 $d_{\text{temp}} < 0.5 \implies y$ 保持不变，且 $d_{i+1} = d_{\text{temp}}$。
>
> | 步数 ($x$) | 当前绘制点           | 误差项更新 ($d = d + 0.4$) |                判断$d \ge 0.5$？                | 下一步纵坐标$y$ |
> | :----------- | :------------------- | :--------------------------- | :-----------------------------------------------: | :---------------- |
> | $0$        | **$(0, 0)$** | $d = 0 + 0.4 = 0.4$        |                否 ($0.4 < 0.5$)                | $y = 0$         |
> | $1$        | **$(1, 0)$** | $d = 0.4 + 0.4 = 0.8$      | 是 ($0.8 \ge 0.5$)，更新 $d = 0.8 - 1 = -0.2$ | $y = 1$         |
> | $2$        | **$(2, 1)$** | $d = -0.2 + 0.4 = 0.2$     |                否 ($0.2 < 0.5$)                | $y = 1$         |
> | $3$        | **$(3, 1)$** | $d = 0.2 + 0.4 = 0.6$      | 是 ($0.6 \ge 0.5$)，更新 $d = 0.6 - 1 = -0.4$ | $y = 2$         |
> | $4$        | **$(4, 2)$** | $d = -0.4 + 0.4 = 0$       |                 否 ($0 < 0.5$)                 | $y = 2$         |
> | $5$        | **$(5, 2)$** | （已到达终点）               |                         -                         | -                 |
>
> ---
>
> #### 2. 改进算法 1：消除与 0.5 的比较（引入误差变量代换 $e$）
>
> <div align="center">
> <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 600" width="100%" height="100%" style="background-color: #ffffff; max-width: 600px; display: block; margin: auto;">
>   <defs>
>     <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
>       <path d="M 0 0 L 10 5 L 0 10 z" fill="#333333" />
>     </marker>
>   </defs>
>   <text x="400" y="40" style="font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; font-size: 18px; font-weight: bold; fill: #111111; text-anchor: middle;">Bresenham 改进算法1演示: 消除0.5比较 [误差变量代换 e]</text>
>   <line x1="230" y1="160" x2="230" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="310" y1="160" x2="310" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="390" y1="160" x2="390" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="470" y1="160" x2="470" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="550" y1="160" x2="550" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="630" y1="160" x2="630" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="400" x2="630" y2="400" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="320" x2="630" y2="320" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="240" x2="630" y2="240" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="160" x2="630" y2="160" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="440" x2="630" y2="440" style="stroke: #009688; stroke-width: 1.5; stroke-dasharray: 8,4;" />
>   <line x1="150" y1="360" x2="630" y2="360" style="stroke: #009688; stroke-width: 1.5; stroke-dasharray: 8,4;" />
>   <text x="640" y="444" style="font-family: Arial; font-size: 12px; fill: #009688; font-weight: bold;">e = 0 决策临界线</text>
>   <text x="640" y="364" style="font-family: Arial; font-size: 12px; fill: #009688; font-weight: bold;">e = 0 决策临界线</text>
>   <line x1="150" y1="480" x2="550" y2="320" style="stroke: #ff9900; stroke-width: 3.5; stroke-dasharray: 6,4;" />
>   <rect x="110" y="440" width="80" height="80" style="fill: #e1f5fe; fill-opacity: 0.4; stroke: #0288d1; stroke-width: 1;" />
>   <rect x="190" y="440" width="80" height="80" style="fill: #e1f5fe; fill-opacity: 0.4; stroke: #0288d1; stroke-width: 1;" />
>   <rect x="270" y="360" width="80" height="80" style="fill: #e1f5fe; fill-opacity: 0.4; stroke: #0288d1; stroke-width: 1;" />
>   <rect x="350" y="360" width="80" height="80" style="fill: #e1f5fe; fill-opacity: 0.4; stroke: #0288d1; stroke-width: 1;" />
>   <rect x="430" y="280" width="80" height="80" style="fill: #e1f5fe; fill-opacity: 0.4; stroke: #0288d1; stroke-width: 1;" />
>   <rect x="510" y="280" width="80" height="80" style="fill: #e1f5fe; fill-opacity: 0.4; stroke: #0288d1; stroke-width: 1;" />
>   <circle cx="150" cy="480" r="6" style="fill: #0288d1; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="230" cy="480" r="6" style="fill: #0288d1; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="310" cy="400" r="6" style="fill: #0288d1; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="390" cy="400" r="6" style="fill: #0288d1; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="470" cy="320" r="6" style="fill: #0288d1; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="550" cy="320" r="6" style="fill: #0288d1; stroke: #ffffff; stroke-width: 2;" />
>   <line x1="100" y1="480" x2="680" y2="480" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
>   <line x1="150" y1="520" x2="150" y2="120" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
>   <text x="675" y="505" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">X</text>
>   <text x="130" y="130" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">Y</text>
>   <text x="150" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">0</text>
>   <text x="230" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
>   <text x="310" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
>   <text x="390" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
>   <text x="470" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">4</text>
>   <text x="550" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">5</text>
>   <text x="125" y="405" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
>   <text x="125" y="325" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
>   <g transform="translate(140, 75)">
>     <rect x="0" y="0" width="520" height="40" style="fill: #f9f9f9; stroke: #dddddd; stroke-width: 1; rx: 4;" />
>     <line x1="15" y1="20" x2="45" y2="20" style="stroke: #ff9900; stroke-width: 3; stroke-dasharray: 4,3;" />
>     <text x="55" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">理想直线</text>
>     <line x1="140" y1="20" x2="170" y2="20" style="stroke: #009688; stroke-width: 1.5; stroke-dasharray: 6,4;" />
>     <text x="180" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">e = 0 零点分界线</text>
>     <rect x="315" y="12" width="16" height="16" style="fill: #e1f5fe; stroke: #0288d1; stroke-width: 1;" />
>     <text x="340" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">选中的像素点(基于 e 符号判断)</text>
>   </g>
> </svg>
> </div>
>
> - **初始化**：通过 $e = d - 0.5$，误差偏置量初始值 $e_0 = -0.5$。
> - **状态更新规则**：
>   - 每次步进计算临时值 $e_{\text{temp}} = e_i + k$。
>   - 若 $e_{\text{temp}} \ge 0 \implies y$ 递增 $1$，且做修正 $e_{i+1} = e_{\text{temp}} - 1$。
>   - 若 $e_{\text{temp}} < 0 \implies y$ 保持不变，且 $e_{i+1} = e_{\text{temp}}$。
>
> | 步数 ($x$) | 当前绘制点           | 误差项更新 ($e = e + 0.4$) |                判断$e \ge 0$？                | 下一步纵坐标$y$ |
> | :----------- | :------------------- | :--------------------------- | :---------------------------------------------: | :---------------- |
> | $0$        | **$(0, 0)$** | $e = -0.5 + 0.4 = -0.1$    |                否 ($-0.1 < 0$)                | $y = 0$         |
> | $1$        | **$(1, 0)$** | $e = -0.1 + 0.4 = 0.3$     | 是 ($0.3 \ge 0$)，更新 $e = 0.3 - 1 = -0.7$ | $y = 1$         |
> | $2$        | **$(2, 1)$** | $e = -0.7 + 0.4 = -0.3$    |                否 ($-0.3 < 0$)                | $y = 1$         |
> | $3$        | **$(3, 1)$** | $e = -0.3 + 0.4 = 0.1$     | 是 ($0.1 \ge 0$)，更新 $e = 0.1 - 1 = -0.9$ | $y = 2$         |
> | $4$        | **$(4, 2)$** | $e = -0.9 + 0.4 = -0.5$    |                否 ($-0.5 < 0$)                | $y = 2$         |
> | $5$        | **$(5, 2)$** | （已到达终点）               |                        -                        | -                 |
>
> ---
>
> #### 3. 改进算法 2：彻底摆脱浮点数（引入整型判别式 $E$）
>
> <div align="center">
> <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 600" width="100%" height="100%" style="background-color: #ffffff; max-width: 600px; display: block; margin: auto;">
>   <defs>
>     <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
>       <path d="M 0 0 L 10 5 L 0 10 z" fill="#333333" />
>     </marker>
>   </defs>
>   <text x="400" y="40" style="font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; font-size: 18px; font-weight: bold; fill: #111111; text-anchor: middle;">Bresenham 改进算法2演示: 纯整数标量运算 [整型判别式 E]</text>
>   <line x1="230" y1="160" x2="230" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="310" y1="160" x2="310" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="390" y1="160" x2="390" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="470" y1="160" x2="470" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="550" y1="160" x2="550" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="630" y1="160" x2="630" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="400" x2="630" y2="400" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="320" x2="630" y2="320" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="240" x2="630" y2="240" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="160" x2="630" y2="160" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="440" x2="630" y2="440" style="stroke: #e91e63; stroke-width: 2;" />
>   <line x1="150" y1="360" x2="630" y2="360" style="stroke: #e91e63; stroke-width: 2;" />
>   <text x="640" y="444" style="font-family: Arial; font-size: 12px; fill: #e91e63; font-weight: bold;">E = 0 整数分界轴</text>
>   <text x="640" y="364" style="font-family: Arial; font-size: 12px; fill: #e91e63; font-weight: bold;">E = 0 整数分界轴</text>
>   <line x1="150" y1="480" x2="550" y2="320" style="stroke: #ff9900; stroke-width: 3.5; stroke-dasharray: 6,4;" />
>   <rect x="110" y="440" width="80" height="80" style="fill: #fce4ec; fill-opacity: 0.5; stroke: #e91e63; stroke-width: 1;" />
>   <rect x="190" y="440" width="80" height="80" style="fill: #fce4ec; fill-opacity: 0.5; stroke: #e91e63; stroke-width: 1;" />
>   <rect x="270" y="360" width="80" height="80" style="fill: #fce4ec; fill-opacity: 0.5; stroke: #e91e63; stroke-width: 1;" />
>   <rect x="350" y="360" width="80" height="80" style="fill: #fce4ec; fill-opacity: 0.5; stroke: #e91e63; stroke-width: 1;" />
>   <rect x="430" y="280" width="80" height="80" style="fill: #fce4ec; fill-opacity: 0.5; stroke: #e91e63; stroke-width: 1;" />
>   <rect x="510" y="280" width="80" height="80" style="fill: #fce4ec; fill-opacity: 0.5; stroke: #e91e63; stroke-width: 1;" />
>   <circle cx="150" cy="480" r="6" style="fill: #e91e63; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="230" cy="480" r="6" style="fill: #e91e63; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="310" cy="400" r="6" style="fill: #e91e63; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="390" cy="400" r="6" style="fill: #e91e63; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="470" cy="320" r="6" style="fill: #e91e63; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="550" cy="320" r="6" style="fill: #e91e63; stroke: #ffffff; stroke-width: 2;" />
>   <text x="150" y="505" style="font-family: Arial; font-size: 11px; font-weight: bold; fill: #444444; text-anchor: middle;">(0,0) E0=-5</text>
>   <text x="230" y="505" style="font-family: Arial; font-size: 11px; font-weight: bold; fill: #444444; text-anchor: middle;">(1,0) E1=-1</text>
>   <text x="310" y="425" style="font-family: Arial; font-size: 11px; font-weight: bold; fill: #444444; text-anchor: middle;">(2,1) E2=3</text>
>   <text x="390" y="425" style="font-family: Arial; font-size: 11px; font-weight: bold; fill: #444444; text-anchor: middle;">(3,1) E3=-3</text>
>   <text x="470" y="345" style="font-family: Arial; font-size: 11px; font-weight: bold; fill: #444444; text-anchor: middle;">(4,2) E4=1</text>
>   <text x="550" y="345" style="font-family: Arial; font-size: 11px; font-weight: bold; fill: #444444; text-anchor: middle;">(5,2) E5=-5</text>
>   <line x1="100" y1="480" x2="680" y2="480" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
>   <line x1="150" y1="520" x2="150" y2="120" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
>   <text x="675" y="505" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">X</text>
>   <text x="130" y="130" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">Y</text>
>   <text x="150" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">0</text>
>   <text x="230" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
>   <text x="310" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
>   <text x="390" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
>   <text x="470" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">4</text>
>   <text x="550" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">5</text>
>   <text x="125" y="405" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
>   <text x="125" y="325" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
>   <g transform="translate(140, 75)">
>     <rect x="0" y="0" width="520" height="40" style="fill: #f9f9f9; stroke: #dddddd; stroke-width: 1; rx: 4;" />
>     <line x1="15" y1="20" x2="45" y2="20" style="stroke: #ff9900; stroke-width: 3; stroke-dasharray: 4,3;" />
>     <text x="55" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">理想直线</text>
>     <line x1="140" y1="20" x2="170" y2="20" style="stroke: #e91e63; stroke-width: 2;" />
>     <text x="180" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">E = 0 整数分界轴</text>
>     <rect x="315" y="12" width="16" height="16" style="fill: #fce4ec; stroke: #e91e63; stroke-width: 1;" />
>     <text x="340" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">纯整型硬件渲染点</text>
>   </g>
> </svg>
> </div>
>
> - **初始化**：通过 $E = e \cdot 2\Delta x$ 进行整体放大，已知 $2\Delta x = 10$ 且 $2\Delta y = 4$。
> - **状态更新规则**：
>   - 每次步进累加 $2\Delta y$ 即计算临时值 $E_{\text{temp}} = E_i + 4$。
>   - 若 $E_{\text{temp}} \ge 0 \implies y$ 递增 $1$，且做整型修正 $E_{i+1} = E_{\text{temp}} - 2\Delta x$（即减去 $10$）。
>   - 若 $E_{\text{temp}} < 0 \implies y$ 保持不变，且 $E_{i+1} = E_{\text{temp}}$。
>
> | 步数 ($x$) | 当前绘制点           | 误差项更新 ($E = E + 4$) |             判断$E \ge 0$？             | 下一步纵坐标$y$ |
> | :----------- | :------------------- | :------------------------- | :----------------------------------------: | :---------------- |
> | $0$        | **$(0, 0)$** | $E = -5 + 4 = -1$        |              否 ($-1 < 0$)              | $y = 0$         |
> | $1$        | **$(1, 0)$** | $E = -1 + 4 = 3$         | 是 ($3 \ge 0$)，更新 $E = 3 - 10 = -7$ | $y = 1$         |
> | $2$        | **$(2, 1)$** | $E = -7 + 4 = -3$        |              否 ($-3 < 0$)              | $y = 1$         |
> | $3$        | **$(3, 1)$** | $E = -3 + 4 = 1$         | 是 ($1 \ge 0$)，更新 $E = 1 - 10 = -9$ | $y = 2$         |
> | $4$        | **$(4, 2)$** | $E = -9 + 4 = -5$        |              否 ($-5 < 0$)              | $y = 2$         |
> | $5$        | **$(5, 2)$** | （已到达终点）             |                     -                     | -                 |
>
> **归纳总结**：
> 无论采用何种形式，其内部判定基准的数学逻辑完全等价，最终渲染产生的离散像素点序列也完全相同：
>
> $$
> (0,0) \to (1,0) \to (2,1) \to (3,1) \to (4,2) \to (5,2)
> $$


---

### 3. 中点画线法

- **基本思想**：构造直线的隐式方程 $F(x, y) = Ax + By + C = 0$（其中 $A = - \Delta y$, $B = \Delta x$, $C = \Delta x \cdot b$）。
- 每次步进 $x_{i+1} = x_i + 1$，计算中点 $M(x_i + 1, y_i + 0.5)$ 代入方程的值：

  $$
  d_i = F(x_i + 1, y_i + 0.5) = A(x_i + 1) + B(y_i + 0.5) + C
  $$

  - 若 $d_i < 0$，中点在直线下方，说明直线上方距离像素点更近，选右上方的像素点 $(x_i + 1, y_i + 1)$。
  - 若 $d_i \ge 0$，中点在直线上方，选右下方的像素点 $(x_i + 1, y_i)$。
- **递推公式 (整数优化形式)**：

  - 初始值：$d_0 = 2A + B$（即 $\Delta x - 2\Delta y$）。
  - 若 $d_i < 0$，选右上点 $(x_i+1, y_i+1)$，则下一轮判别式 $d_{i+1} = d_i + 2A + 2B$（即 $d_i + 2\Delta x - 2\Delta y$）。
  - 若 $d_i \ge 0$，选右下点 $(x_i+1, y_i)$，则下一轮判别式 $d_{i+1} = d_i + 2A$（即 $d_i - 2\Delta y$）。

> [!TIP]
> **经典实例演练：使用中点画线法绘制从 $P_0(0,0)$ 到 $P_1(5,2)$ 的直线段**
>
> 已知起点为 $(0,0)$，终点为 $(5,2)$，则：
>
> <div align="center">
> <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 600" width="100%" height="100%" style="background-color: #ffffff; max-width: 600px; display: block; margin: auto;">
>   <defs>
>     <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
>       <path d="M 0 0 L 10 5 L 0 10 z" fill="#333333" />
>     </marker>
>   </defs>
>   <text x="400" y="40" style="font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; font-size: 20px; font-weight: bold; fill: #111111; text-anchor: middle;">中点画线法绘制实例演示: P₀(0,0) 到 P₁(5,2)</text>
>   <line x1="230" y1="160" x2="230" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="310" y1="160" x2="310" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="390" y1="160" x2="390" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="470" y1="160" x2="470" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="550" y1="160" x2="550" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="630" y1="160" x2="630" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="400" x2="630" y2="400" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="320" x2="630" y2="320" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="240" x2="630" y2="240" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="160" x2="630" y2="160" style="stroke: #e0e0e0; stroke-width: 1;" />
>   <line x1="150" y1="480" x2="550" y2="320" style="stroke: #ff9900; stroke-width: 3; stroke-dasharray: 6,4;" />
>   <circle cx="190" cy="440" r="4" style="fill: #990099;" />
>   <circle cx="270" cy="440" r="4" style="fill: #990099;" />
>   <circle cx="350" cy="360" r="4" style="fill: #990099;" />
>   <circle cx="430" cy="360" r="4" style="fill: #990099;" />
>   <text x="190" y="430" style="font-family: Arial; font-size: 11px; fill: #990099; text-anchor: middle;">M₁</text>
>   <text x="270" y="430" style="font-family: Arial; font-size: 11px; fill: #990099; text-anchor: middle;">M₂</text>
>   <text x="350" y="350" style="font-family: Arial; font-size: 11px; fill: #990099; text-anchor: middle;">M₃</text>
>   <text x="430" y="350" style="font-family: Arial; font-size: 11px; fill: #990099; text-anchor: middle;">M₄</text>
>   <rect x="110" y="440" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
>   <rect x="190" y="440" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
>   <rect x="270" y="360" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
>   <rect x="350" y="360" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
>   <rect x="430" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
>   <rect x="510" y="280" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
>   <circle cx="150" cy="480" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="230" cy="480" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="310" cy="400" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="390" cy="400" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="470" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>   <circle cx="550" cy="320" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>   <text x="150" y="505" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(0,0)</text>
>   <text x="230" y="505" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(1,0)</text>
>   <text x="310" y="425" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(2,1)</text>
>   <text x="390" y="425" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(3,1)</text>
>   <text x="470" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(4,2)</text>
>   <text x="550" y="345" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(5,2)</text>
>   <line x1="100" y1="480" x2="680" y2="480" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
>   <line x1="150" y1="520" x2="150" y2="120" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
>   <text x="675" y="505" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">X</text>
>   <text x="130" y="130" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">Y</text>
>   <text x="150" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">0</text>
>   <text x="230" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
>   <text x="310" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
>   <text x="390" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
>   <text x="470" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">4</text>
>   <text x="550" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">5</text>
>   <text x="630" y="530" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">6</text>
>   <text x="125" y="405" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
>   <text x="125" y="325" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
>   <text x="125" y="245" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
>   <g transform="translate(180, 80)">
>     <rect x="0" y="0" width="440" height="40" style="fill: #f9f9f9; stroke: #dddddd; stroke-width: 1; rx: 4;" />
>     <line x1="15" y1="20" x2="45" y2="20" style="stroke: #ff9900; stroke-width: 3; stroke-dasharray: 4,3;" />
>     <text x="55" y="25" style="font-family: Arial; font-size: 12px; fill: #333333;">理想直线 (y = 0.4x)</text>
>     <rect x="175" y="12" width="16" height="16" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
>     <circle cx="183" cy="20" r="4" style="fill: #2e7d32;" />
>     <text x="200" y="25" style="font-family: Arial; font-size: 12px; fill: #333333;">光栅化选择的像素点</text>
>     <circle cx="335" cy="20" r="4" style="fill: #990099;" />
>     <text x="345" y="25" style="font-family: Arial; font-size: 12px; fill: #333333;">中点判别位置 (M)</text>
>   </g>
> </svg>
> </div>
>
> - $\Delta x = 5$ 且 $\Delta y = 2$
> - 斜率 $k = \frac{2}{5} = 0.4$
>
> 以下分别使用改进前（含小数）和改进后（纯整型）两种中点判别式递推展示计算过程：
>
> #### 1. 改进前（基于斜率 $k$ 的小数运算）
>
> - **初始化**：初始判别式 $d_0 = 0.5 - k = 0.5 - 0.4 = 0.1$。
> - **状态更新规则**：
>   - 若 $d_i \ge 0$（中点在直线上方），选择右下方的点，即 $y$ 保持不变，并更新：
>
>     $$
>     d_{i+1} = d_i - k = d_i - 0.4
>     $$
>   - 若 $d_i < 0$（中点在直线下方），选择右上方的点，即 $y$ 递增 $1$，并更新：
>
>     $$
>     d_{i+1} = d_i + 1 - k = d_i + 0.6
>     $$
>
> | 步数 ($x$) | 当前绘制点           | 当前判别式$d_i$ | 判断$d_i \ge 0$？ | 下一步纵坐标$y$ | 下一步判别式$d_{i+1}$ 更新 |
> | :----------- | :------------------- | :---------------- | :-----------------: | :---------------- | :--------------------------- |
> | $0$        | **$(0, 0)$** | $0.1$           |   是 ($\ge 0$)   | $y = 0$         | $d = 0.1 - 0.4 = -0.3$     |
> | $1$        | **$(1, 0)$** | $-0.3$          |    否 ($< 0$)    | $y = 1$         | $d = -0.3 + 0.6 = 0.3$     |
> | $2$        | **$(2, 1)$** | $0.3$           |   是 ($\ge 0$)   | $y = 1$         | $d = 0.3 - 0.4 = -0.1$     |
> | $3$        | **$(3, 1)$** | $-0.1$          |    否 ($< 0$)    | $y = 2$         | $d = -0.1 + 0.6 = 0.5$     |
> | $4$        | **$(4, 2)$** | $0.5$           |   是 ($\ge 0$)   | $y = 2$         | $d = 0.5 - 0.4 = 0.1$      |
> | $5$        | **$(5, 2)$** | -                 |   （已到达终点）   | -                 | -                            |
>
> ---
>
> #### 2. 改进后（纯整数运算，令 $D = 2d \cdot \Delta x$）
>
> - **参数计算**：已知 $2\Delta x = 10, 2\Delta y = 4$。
>   初始判别式为：
>
>   $$
>   D_0 = 2d_0 \cdot \Delta x = 2(0.5 - k)\Delta x = \Delta x - 2\Delta y = 5 - 4 = 1
>   $$
> - **状态更新规则**：
>
>   - 若 $D_i \ge 0$（中点在直线上方），选择右下方的点，即 $y$ 保持不变，并更新：
>
>     $$
>     D_{i+1} = D_i - 2\Delta y = D_i - 4
>     $$
>   - 若 $D_i < 0$（中点在直线下方），选择右上方的点，即 $y$ 递增 $1$，并更新：
>
>     $$
>     D_{i+1} = D_i + 2\Delta x - 2\Delta y = D_i + 6
>     $$
>
> | 步数 ($x$) | 当前绘制点           | 当前判别式$D_i$ | 判断$D_i \ge 0$？ | 下一步纵坐标$y$ | 下一步判别式$D_{i+1}$ 更新 |
> | :----------- | :------------------- | :---------------- | :-----------------: | :---------------- | :--------------------------- |
> | $0$        | **$(0, 0)$** | $1$             |   是 ($\ge 0$)   | $y = 0$         | $D = 1 - 4 = -3$           |
> | $1$        | **$(1, 0)$** | $-3$            |    否 ($< 0$)    | $y = 1$         | $D = -3 + 6 = 3$           |
> | $2$        | **$(2, 1)$** | $3$             |   是 ($\ge 0$)   | $y = 1$         | $D = 3 - 4 = -1$           |
> | $3$        | **$(3, 1)$** | $-1$            |    否 ($< 0$)    | $y = 2$         | $D = -1 + 6 = 5$           |
> | $4$        | **$(4, 2)$** | $5$             |   是 ($\ge 0$)   | $y = 2$         | $D = 5 - 4 = 1$            |
> | $5$        | **$(5, 2)$** | -                 |   （已到达终点）   | -                 | -                            |
>
> **归纳总结**：
> 对比可以清楚地看到，改进后的判别式 $D$ 的符号变化轨迹（$1 \to -3 \to 3 \to -1 \to 5$）与改进前的 $d$ （$0.1 \to -0.3 \to 0.3 \to -0.1 \to 0.5$）完全对应一致，最终绘制出的点列序列也完全相同，但整个主循环中没有出现任何浮点数。

---

### 4. 中点画圆法

- **基本思想**：利用圆的 8 对称性，只需计算八分之一圆弧（$0 \le x \le y$）。构造圆的隐式方程 $F(x, y) = x^2 + y^2 - R^2 = 0$。
- **判别式与递推公式**：
  - 从起点 $(0, R)$ 开始，步进 $x_{i+1} = x_i + 1$，评估中点 $M(x_i + 1, y_i - 0.5)$。
  - 初始值：

    $$
    d_0 = 1.25 - R \quad (\text{整数优化中常记为 } d_0 = 1 - R)
    $$
  - 递推规则：

    - 若 $d_i < 0$，选正右方点 $(x_i + 1, y_i)$，更新：

      $$
      d_{i+1} = d_i + 2x_i + 3
      $$
    - 若 $d_i \ge 0$，选斜下方点 $(x_i + 1, y_i - 1)$，更新：

      $$
      d_{i+1} = d_i + 2(x_i - y_i) + 5
      $$

> [!TIP]
> **经典实例演练：使用中点画圆法计算半径 $R=5$ 的 1/8 圆弧**
>
> 已知半径 $R=5$，初始起点为 $(0, 5)$。我们只计算 $x \le y$ 范围内的 1/8 圆弧像素序列。
>
> 以下分别对比优化前（含小数）和优化后（整型）两种中点判别式递推的详细计算过程：
>
> #### 1. 优化前（含小数运算）
>
> - **初始化**：初始判别式 $d_0 = 1.25 - R = 1.25 - 5 = -3.75$。
> - **状态更新规则**：
>   - 若 $d_i < 0$（中点在圆内），选择正右方点 $(x_i + 1, y_i)$，更新：
>
>     $$
>     d_{i+1} = d_i + 2x_i + 3
>     $$
>   - 若 $d_i \ge 0$（中点在圆外），选择斜下方点 $(x_i + 1, y_i - 1)$，更新：
>
>     $$
>     d_{i+1} = d_i + 2(x_i - y_i) + 5
>     $$
>
> | 步数  | 当前绘制点$(x, y)$ | 当前判别式$d_i$ | 判断$d_i \ge 0$？ | 下一步$d_{i+1}$ 更新计算         | 下一步绘制点 |
> | :---- | :------------------- | :---------------- | :-----------------: | :--------------------------------- | :----------- |
> | $0$ | **$(0, 5)$** | $-3.75$         |     否 ($<0$)     | $d = -3.75 + 2(0) + 3 = -0.75$   | $(1, 5)$   |
> | $1$ | **$(1, 5)$** | $-0.75$         |     否 ($<0$)     | $d = -0.75 + 2(1) + 3 = 4.25$    | $(2, 5)$   |
> | $2$ | **$(2, 5)$** | $4.25$          |   是 ($\ge 0$)   | $d = 4.25 + 2(2 - 5) + 5 = 3.25$ | $(3, 4)$   |
> | $3$ | **$(3, 4)$** | $3.25$          |   是 ($\ge 0$)   | $d = 3.25 + 2(3 - 4) + 5 = 6.25$ | $(4, 3)$   |
>
> ---
>
> #### 2. 优化后（纯整数运算）
>
> *优化原理*：在圆的光栅化中，由于每次的步进增量 $2x_i+3$ 或 $2(x_i-y_i)+5$ 均为整数，初始值中的 $0.25$ 在与 $0$ 判定大小的循环链中，不会改变判别式正负号的方向。因此可令新判别式 $d = d_{\text{old}} - 0.25$，得到纯整数初始值，完全摆脱浮点数运算。
>
> - **初始化**：初始判别式 $d_0 = 1 - R = 1 - 5 = -4$。
> - **状态更新规则**：与优化前一致，仅初始值不同。
>
> | 步数  | 当前绘制点$(x, y)$ | 当前判别式$d_i$ | 判断$d_i \ge 0$？ | 下一步$d_{i+1}$ 更新计算   | 下一步绘制点 |
> | :---- | :------------------- | :---------------- | :-----------------: | :--------------------------- | :----------- |
> | $0$ | **$(0, 5)$** | $-4$            |     否 ($<0$)     | $d = -4 + 2(0) + 3 = -1$   | $(1, 5)$   |
> | $1$ | **$(1, 5)$** | $-1$            |     否 ($<0$)     | $d = -1 + 2(1) + 3 = 4$    | $(2, 5)$   |
> | $2$ | **$(2, 5)$** | $4$             |   是 ($\ge 0$)   | $d = 4 + 2(2 - 5) + 5 = 3$ | $(3, 4)$   |
> | $3$ | **$(3, 4)$** | $3$             |   是 ($\ge 0$)   | $d = 3 + 2(3 - 4) + 5 = 6$ | $(4, 3)$   |
>
> **对比结论**：
>
> - 算完第 3 步后，下一步的待绘制坐标变成了 $(4, 3)$。此时由于 $x > y$（$4 > 3$），超出了 $x \le y$ 的循环控制条件，这 1/8 圆弧的计算至此宣告结束。
> - 优化前后判别式的正负号变化轨迹完全一致（负 $\to$ 负 $\to$ 正 $\to$ 正），计算出的点列也完全相同：
>
>   $$
>   (0,5) \to (1,5) \to (2,5) \to (3,4)
>   $$
>
>   <div align="center">
>   <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 600" width="100%" height="100%" style="background-color: #ffffff; max-width: 600px; display: block; margin: auto;">
>     <defs>
>       <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
>         <path d="M 0 0 L 10 5 L 0 10 z" fill="#333333" />
>       </marker>
>     </defs>
>     <text x="400" y="40" style="font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; font-size: 20px; font-weight: bold; fill: #111111; text-anchor: middle;">中点画圆法 1/8圆弧绘制实例 (R = 5)</text>
>     <line x1="230" y1="80" x2="230" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>     <line x1="310" y1="80" x2="310" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>     <line x1="390" y1="80" x2="390" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>     <line x1="470" y1="80" x2="470" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>     <line x1="550" y1="80" x2="550" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>     <line x1="630" y1="80" x2="630" y2="480" style="stroke: #e0e0e0; stroke-width: 1;" />
>     <line x1="150" y1="400" x2="630" y2="400" style="stroke: #e0e0e0; stroke-width: 1;" />
>     <line x1="150" y1="320" x2="630" y2="320" style="stroke: #e0e0e0; stroke-width: 1;" />
>     <line x1="150" y1="240" x2="630" y2="240" style="stroke: #e0e0e0; stroke-width: 1;" />
>     <line x1="150" y1="160" x2="630" y2="160" style="stroke: #e0e0e0; stroke-width: 1;" />
>     <line x1="150" y1="80" x2="630" y2="80" style="stroke: #e0e0e0; stroke-width: 1;" />
>     <path d="M 150 80 A 400 400 0 0 1 470 240" style="stroke: #ff9900; stroke-width: 3.5; stroke-dasharray: 6,4; fill: none;" />
>     <rect x="110" y="40" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
>     <rect x="190" y="40" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
>     <rect x="270" y="40" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
>     <rect x="350" y="120" width="80" height="80" style="fill: #4caf50; fill-opacity: 0.22; stroke: #4caf50; stroke-width: 1;" />
>     <rect x="430" y="200" width="80" height="80" style="fill: none; stroke: #888888; stroke-width: 1; stroke-dasharray: 4,4;" />
>     <circle cx="150" cy="80" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>     <circle cx="230" cy="80" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>     <circle cx="310" cy="80" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>     <circle cx="390" cy="160" r="6" style="fill: #2e7d32; stroke: #ffffff; stroke-width: 2;" />
>     <circle cx="470" cy="240" r="4" style="fill: #888888; stroke: #ffffff; stroke-width: 1.5;" />
>     <text x="150" y="105" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(0,5)</text>
>     <text x="230" y="105" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(1,5)</text>
>     <text x="310" y="105" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(2,5)</text>
>     <text x="390" y="185" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #2e7d32; text-anchor: middle;">(3,4)</text>
>     <text x="475" y="262" style="font-family: Arial; font-size: 11px; fill: #888888; text-anchor: middle;">(4,3) 终止</text>
>     <line x1="150" y1="480" x2="480" y2="150" style="stroke: #888888; stroke-width: 1.5; stroke-dasharray: 4,4;" />
>     <text x="485" y="145" style="font-family: Arial; font-size: 12px; fill: #888888; font-weight: bold;">y = x 边界线</text>
>     <circle cx="230" cy="120" r="4" style="fill: #990099;" />
>     <circle cx="310" cy="120" r="4" style="fill: #990099;" />
>     <circle cx="390" cy="120" r="4" style="fill: #990099;" />
>     <circle cx="470" cy="200" r="4" style="fill: #990099;" />
>     <text x="230" y="112" style="font-family: Arial; font-size: 11px; fill: #990099; text-anchor: middle;">M₁</text>
>     <text x="310" y="112" style="font-family: Arial; font-size: 11px; fill: #990099; text-anchor: middle;">M₂</text>
>     <text x="390" y="112" style="font-family: Arial; font-size: 11px; fill: #990099; text-anchor: middle;">M₃</text>
>     <text x="470" y="192" style="font-family: Arial; font-size: 11px; fill: #990099; text-anchor: middle;">M₄</text>
>     <line x1="100" y1="480" x2="680" y2="480" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
>     <line x1="150" y1="520" x2="150" y2="50" style="stroke: #333333; stroke-width: 2;" marker-end="url(#arrow)" />
>     <text x="675" y="505" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">X</text>
>     <text x="130" y="60" style="font-family: Arial; font-size: 16px; font-weight: bold; font-style: italic; fill: #333333;">Y</text>
>     <text x="150" y="505" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">0</text>
>     <text x="230" y="505" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
>     <text x="310" y="505" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
>     <text x="390" y="505" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
>     <text x="470" y="505" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">4</text>
>     <text x="550" y="505" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">5</text>
>     <text x="630" y="505" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">6</text>
>     <text x="125" y="405" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">1</text>
>     <text x="125" y="325" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">2</text>
>     <text x="125" y="245" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">3</text>
>     <text x="125" y="165" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">4</text>
>     <text x="125" y="85" style="font-family: Arial; font-size: 14px; fill: #333333; text-anchor: middle;">5</text>
>     <g transform="translate(440, 80)">
>       <rect x="0" y="0" width="220" height="120" style="fill: #f9f9f9; stroke: #dddddd; stroke-width: 1; rx: 4;" />
>       <line x1="15" y1="20" x2="45" y2="20" style="stroke: #ff9900; stroke-width: 3; stroke-dasharray: 4,3;" />
>       <text x="55" y="24" style="font-family: Arial; font-size: 12px; fill: #333333;">理想圆弧 (R=5)</text>
>       <rect x="15" y="42" width="16" height="16" style="fill: #4caf50; fill-opacity: 0.25; stroke: #4caf50; stroke-width: 1;" />
>       <circle cx="23" cy="50" r="4" style="fill: #2e7d32;" />
>       <text x="40" y="54" style="font-family: Arial; font-size: 12px; fill: #333333;">选中的像素点</text>
>       <circle cx="23" cy="80" r="4" style="fill: #990099;" />
>       <text x="40" y="84" style="font-family: Arial; font-size: 12px; fill: #333333;">中点判别位置 (M)</text>
>       <line x1="15" y1="105" x2="45" y2="105" style="stroke: #888888; stroke-width: 1.5; stroke-dasharray: 4,4;" />
>       <text x="55" y="109" style="font-family: Arial; font-size: 12px; fill: #888888;">y = x 对角边界</text>
>     </g>
>   </svg>
>   </div>
>
>   算法在实际运行中，只需计算出这 4 个坐标点，再利用圆的八分对称性即可直接绘制出整个完整的圆。

---

## 二、 区域填充算法

### 1. 包含性测试 (In-Out Test)

* **射线法 (Ray-Casting Method)**：
  - 从测试点 $P$ 向任意方向发射一条射线，计算该射线与多边形边界的交点个数。
  - 若交点个数为**奇数**，则点 $P$ 位于多边形内部；若为**偶数**，则位于外部。
  - *特例处理*：当射线恰好穿过顶点或切于边时，需进行退化判定（通常规定“左开右闭”或仅计算单向相交）。
    *   **X-扫描线算法——顶点配对**：
        当扫描线与多边形的顶点相交时：
        - 若共享顶点的两条边分别落在扫描线的两边，交点只算一个；
        - 若共享顶点的两条边在扫描线的同一边，这时交点作为两个；
        - 对于多边形的水平边，不计它与扫描线的交点。
        > **直观记忆口诀：**
        > *   路过拐角（一上一下）： 算作 1 个交点。
        > *   切到尖峰/谷底（同上同下）： 算作 2 个交点。
        > *   切到水平躺平 the 边： 直接无视，算 0 个。
        <div align="center">
        <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 600 600" width="100%" height="100%" style="background-color: #ffffff;">
          <defs>
            <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
              <path d="M 0 0 L 10 5 L 0 10 z" fill="#000000" />
            </marker>
          </defs>
          <line x1="120" y1="40" x2="120" y2="520" stroke="#888888" stroke-width="0.5" />
          <line x1="160" y1="40" x2="160" y2="520" stroke="#888888" stroke-width="0.5" />
          <line x1="200" y1="40" x2="200" y2="520" stroke="#888888" stroke-width="0.5" />
          <line x1="240" y1="40" x2="240" y2="520" stroke="#888888" stroke-width="0.5" />
          <line x1="280" y1="40" x2="280" y2="520" stroke="#888888" stroke-width="0.5" />
          <line x1="320" y1="40" x2="320" y2="520" stroke="#888888" stroke-width="0.5" />
          <line x1="360" y1="40" x2="360" y2="520" stroke="#888888" stroke-width="0.5" />
          <line x1="400" y1="40" x2="400" y2="520" stroke="#888888" stroke-width="0.5" />
          <line x1="440" y1="40" x2="440" y2="520" stroke="#888888" stroke-width="0.5" />
          <line x1="480" y1="40" x2="480" y2="520" stroke="#888888" stroke-width="0.5" />
          <line x1="520" y1="40" x2="520" y2="520" stroke="#888888" stroke-width="0.5" />
          <line x1="560" y1="40" x2="560" y2="520" stroke="#888888" stroke-width="0.5" />
          <line x1="80" y1="480" x2="560" y2="480" stroke="#888888" stroke-width="0.5" />
          <line x1="80" y1="440" x2="560" y2="440" stroke="#888888" stroke-width="0.5" />
          <line x1="80" y1="400" x2="560" y2="400" stroke="#888888" stroke-width="0.5" />
          <line x1="80" y1="360" x2="560" y2="360" stroke="#888888" stroke-width="0.5" />
          <line x1="80" y1="320" x2="560" y2="320" stroke="#888888" stroke-width="0.5" />
          <line x1="80" y1="280" x2="560" y2="280" stroke="#888888" stroke-width="0.5" />
          <line x1="80" y1="240" x2="560" y2="240" stroke="#888888" stroke-width="0.5" />
          <line x1="80" y1="200" x2="560" y2="200" stroke="#888888" stroke-width="0.5" />
          <line x1="80" y1="160" x2="560" y2="160" stroke="#888888" stroke-width="0.5" />
          <line x1="80" y1="120" x2="560" y2="120" stroke="#888888" stroke-width="0.5" />
          <line x1="80" y1="80"  x2="560" y2="80"  stroke="#888888" stroke-width="0.5" />
          <line x1="80" y1="40"  x2="560" y2="40"  stroke="#888888" stroke-width="0.5" />
          <line x1="50" y1="480" x2="590" y2="480" stroke="#0000ff" stroke-width="3" />
          <line x1="50" y1="320" x2="590" y2="320" stroke="#0000ff" stroke-width="3" />
          <line x1="50" y1="240" x2="590" y2="240" stroke="#0000ff" stroke-width="3" />
          <line x1="200" y1="480" x2="400" y2="480" stroke="#ff0000" stroke-width="5" stroke-linecap="round" />
          <polygon points="120,240 200,40 360,200 560,160 400,480 320,320 200,480" stroke="#000000" stroke-width="3" fill="none" stroke-linejoin="round" stroke-linecap="round" />
          <circle cx="120" cy="240" r="6" fill="#ff0000" stroke="#000000" stroke-width="2" />
          <circle cx="320" cy="320" r="6" fill="#ff0000" stroke="#000000" stroke-width="2" />
          <circle cx="200" cy="480" r="6" fill="#ff0000" stroke="#000000" stroke-width="2" />
          <circle cx="400" cy="480" r="6" fill="#ff0000" stroke="#000000" stroke-width="2" />
          <line x1="80" y1="520" x2="580" y2="520" stroke="#000000" stroke-width="2" marker-end="url(#arrow)" />
          <line x1="80" y1="520" x2="80" y2="20" stroke="#000000" stroke-width="2" marker-end="url(#arrow)" />
          <text x="575" y="545" font-family="sans-serif" font-size="18" font-weight="bold" font-style="italic" fill="#000000">x</text>
          <text x="55" y="30" font-family="sans-serif" font-size="18" font-weight="bold" font-style="italic" fill="#000000">y</text>
          <text x="120" y="545" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">1</text>
          <text x="160" y="545" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">2</text>
          <text x="200" y="545" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">3</text>
          <text x="240" y="545" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">4</text>
          <text x="280" y="545" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">5</text>
          <text x="320" y="545" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">6</text>
          <text x="360" y="545" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">7</text>
          <text x="400" y="545" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">8</text>
          <text x="440" y="545" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">9</text>
          <text x="480" y="545" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">10</text>
          <text x="520" y="545" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">11</text>
          <text x="560" y="545" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">12</text>
          <text x="60" y="485" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">1</text>
          <text x="60" y="445" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">2</text>
          <text x="60" y="405" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">3</text>
          <text x="60" y="365" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">4</text>
          <text x="60" y="325" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">5</text>
          <text x="60" y="285" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">6</text>
          <text x="60" y="245" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">7</text>
          <text x="60" y="205" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">8</text>
          <text x="60" y="165" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">9</text>
          <text x="60" y="125" font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">10</text>
          <text x="60" y="85"  font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">11</text>
          <text x="60" y="45"  font-family="sans-serif" font-size="16" fill="#000000" text-anchor="middle">12</text>
        </svg>
        </div>
* **环绕数/弧长法 (Winding Number Method)**：
  - 计算测试点 $P$ 沿多边形边界绕行一周时，边界边绕点 $P$ 的净旋转角之和。若旋转角之和非零，则点在内部。
  > **环绕数/弧长法是怎么运作的？**
  >
  > 这个方法非常直观。想象你站在要测试的 P 点上，目光盯着多边形的边界，看着一个人沿着多边形边缘走完整整一圈。
  >
  > *   如果 P 点在外部：你的目光会跟着这个人来回摆动（比如先往左看30度，最后又往右看30度）。当他走回起点时，你目光转动的“净角度”（正负相互抵消后的代数和）将是 0度。
  > *   如果 P 点在内部：因为你被边界包围了，为了看着他走完一圈，你自己必须原地转整整一个圈。也就是说，你目光旋转的代数和将是 2π（也就是360度）。
  >
  > 通过计算这个角度的总和是 0 还是 2π，就能精准判断点到底在外面还是里面。

---

### 2. 多边形扫描转换算法 (扫描线算法)

* **核心目标**：逐行扫描像素，利用多边形内部的连贯性进行区间快速面填充。
* **边表 (Edge Table, ET) 的构建**：
  - 按照边的最小 $Y$ 值进行分类归档（桶排序）。
  - ET 表节点结构：

    $$
    \begin{array}{|c|c|c|c|}
    \hline
    y_{\max} & x_{\text{ymin}} & \Delta x & \text{next} \\
    \hline
    \end{array}
    $$

    其中，$y_{\max}$ 是边的最大 $Y$ 坐标，$x_{\text{ymin}}$ 是边在最小 $Y$ 坐标处对应的 $X$ 值，$\Delta x$ 是边的斜率倒数（即 $\frac{1}{k}$）。
  > [!TIP]
  > 参数可能会出简答题
  - *注意*：若边水平（$\Delta y = 0$），则无需加入 ET 表。为了防止顶点处重复相交，若某边与邻边在顶点处单调递增或递减，需将上端点的高度算作 $y_{\max}-1$ 进行区间缩短。
* **活动边表 (Active Edge Table, AET) 的创建与维护步骤**：
  - AET 表存储与当前扫描线相交的所有边，并按 $X$ 坐标从小到大排序。
  - **算法执行步骤**：
    1. 初始化扫描线 $y = y_{\min}$。
    2. 将 ET 表中对应当前 $y$ 的边链表移入 AET。
    3. 对 AET 中的边按照当前 $X$ 进行升序排序。
    4. 对排好序的 AET 链表，奇偶配对填充像素（即 $x_0$ 到 $x_1$, $x_2$ 到 $x_3$ 之间的像素）。
    5. 从 AET 中剔除当前扫描线已达到最大值的边（即 $y = y_{\max}$ 的节点）。
    6. 将 AET 中剩余边节点的 $X$ 递增更新：$x_{\text{new}} = x_{\text{old}} + \Delta x$。
    7. 递增扫描线 $y = y + 1$，循环第 2 步直至 AET 和 ET 均为空。

> [!TIP]
> **期末大题演练：多边形扫描转换与有效边表（ET/AET）计算**
>
> **【题目描述】**
> 已知多边形有 6 个顶点，其局部网格坐标为：$A(2, 1)$、$B(6, 1)$、$C(6, 5)$、$D(4, 3)$、$E(2, 5)$、$F(1, 4)$。
> 规定有效边节点的物理存储结构为：`[ y_max | x_ymin | 1/k | next ]`。
> 请构建该多边形的边表（ET），并写出扫描线在 $y=1$、$y=2$、$y=3$ 时的活动边表（AET）及其填充区间。
>
> **【多边形网格示意图】**
>
> <div align="center">
> <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 400 350" width="100%" style="background-color: #ffffff; max-width: 500px; display: block; margin: auto;">
>   <defs>
>     <pattern id="grid" width="40" height="40" patternUnits="userSpaceOnUse">
>       <path d="M 40 0 L 0 0 0 40" fill="none" stroke="#f0f0f0" stroke-width="1"/>
>     </pattern>
>     <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
>       <path d="M 0 0 L 10 5 L 0 10 z" fill="#333" />
>     </marker>
>   </defs>
>   <rect width="100%" height="100%" fill="url(#grid)" />
>   <line x1="30" y1="300" x2="360" y2="300" stroke="#333" stroke-width="2" marker-end="url(#arrow)" />
>   <line x1="50" y1="320" x2="50" y2="30" stroke="#333" stroke-width="2" marker-end="url(#arrow)" />
>   <text x="355" y="315" font-family="sans-serif" font-size="14" fill="#333">x</text>
>   <text x="35" y="35" font-family="sans-serif" font-size="14" fill="#333">y</text>
>   <text x="35" y="315" font-family="sans-serif" font-size="12" fill="#666">0</text>
>   <line x1="90" y1="300" x2="90" y2="305" stroke="#333" /><text x="86" y="320" font-family="sans-serif" font-size="12" fill="#666">1</text>
>   <line x1="130" y1="300" x2="130" y2="305" stroke="#333" /><text x="126" y="320" font-family="sans-serif" font-size="12" fill="#666">2</text>
>   <line x1="170" y1="300" x2="170" y2="305" stroke="#333" /><text x="166" y="320" font-family="sans-serif" font-size="12" fill="#666">3</text>
>   <line x1="210" y1="300" x2="210" y2="305" stroke="#333" /><text x="206" y="320" font-family="sans-serif" font-size="12" fill="#666">4</text>
>   <line x1="250" y1="300" x2="250" y2="305" stroke="#333" /><text x="246" y="320" font-family="sans-serif" font-size="12" fill="#666">5</text>
>   <line x1="290" y1="300" x2="290" y2="305" stroke="#333" /><text x="286" y="320" font-family="sans-serif" font-size="12" fill="#666">6</text>
>   <line x1="45" y1="260" x2="50" y2="260" stroke="#333" /><text x="30" y="264" font-family="sans-serif" font-size="12" fill="#666">1</text>
>   <line x1="45" y1="220" x2="50" y2="220" stroke="#333" /><text x="30" y="224" font-family="sans-serif" font-size="12" fill="#666">2</text>
>   <line x1="45" y1="180" x2="50" y2="180" stroke="#333" /><text x="30" y="184" font-family="sans-serif" font-size="12" fill="#666">3</text>
>   <line x1="45" y1="140" x2="50" y2="140" stroke="#333" /><text x="30" y="144" font-family="sans-serif" font-size="12" fill="#666">4</text>
>   <line x1="45" y1="100" x2="50" y2="100" stroke="#333" /><text x="30" y="104" font-family="sans-serif" font-size="12" fill="#666">5</text>
>   <polygon points="130,260 290,260 290,100 210,180 130,100 90,140" fill="rgba(64, 158, 255, 0.2)" stroke="#409EFF" stroke-width="3" stroke-linejoin="round" />
>   <circle cx="130" cy="260" r="4" fill="#F56C6C" />
>   <circle cx="290" cy="260" r="4" fill="#F56C6C" />
>   <circle cx="290" cy="100" r="4" fill="#F56C6C" />
>   <circle cx="210" cy="180" r="4" fill="#F56C6C" />
>   <circle cx="130" cy="100" r="4" fill="#F56C6C" />
>   <circle cx="90" cy="140" r="4" fill="#F56C6C" />
>   <text x="120" y="280" font-family="sans-serif" font-size="12" font-weight="bold" fill="#333">A(2,1)</text>
>   <text x="295" y="280" font-family="sans-serif" font-size="12" font-weight="bold" fill="#333">B(6,1)</text>
>   <text x="295" y="95" font-family="sans-serif" font-size="12" font-weight="bold" fill="#333">C(6,5)</text>
>   <text x="210" y="200" font-family="sans-serif" font-size="12" font-weight="bold" fill="#333" text-anchor="middle">D(4,3)</text>
>   <text x="110" y="95" font-family="sans-serif" font-size="12" font-weight="bold" fill="#333">E(2,5)</text>
>   <text x="50" y="140" font-family="sans-serif" font-size="12" font-weight="bold" fill="#333">F(1,4)</text>
> </svg>
> </div>
>
> ---
>
> #### 1. 计算所有有效非水平边的参数
>
> 水平边 $AB$ （$y=1$ 时两端点高度一致）对扫描线无穿插变化贡献，直接舍弃。对其余 5 条有效边计算其边界特征值：
>
> - **$BC$ 边**：下端点 $y_{\min}=1$，上端点 $y_{\max}=5$，下端点对应 $x=6$。
>   斜率倒数：
>
>   $$
>   \frac{1}{k} = \frac{x_C - x_B}{y_C - y_B} = \frac{6 - 6}{5 - 1} = 0
>   $$
> - **$FA$ 边**：下端点 $y_{\min}=1$，上端点 $y_{\max}=4$，下端点对应 $x=2$。
>   斜率倒数：
>
>   $$
>   \frac{1}{k} = \frac{x_F - x_A}{y_F - y_A} = \frac{1 - 2}{4 - 1} = -\frac{1}{3}
>   $$
> - **$CD$ 边**：下端点 $y_{\min}=3$，上端点 $y_{\max}=5$，下端点对应 $x=4$。
>   斜率倒数：
>
>   $$
>   \frac{1}{k} = \frac{x_C - x_D}{y_C - y_D} = \frac{6 - 4}{5 - 3} = 1
>   $$
> - **$DE$ 边**：下端点 $y_{\min}=3$，上端点 $y_{\max}=5$，下端点对应 $x=4$。
>   斜率倒数：
>
>   $$
>   \frac{1}{k} = \frac{x_E - x_D}{y_E - y_D} = \frac{2 - 4}{5 - 3} = -1
>   $$
> - **$EF$ 边**：下端点 $y_{\min}=4$，上端点 $y_{\max}=5$，下端点对应 $x=1$。
>   斜率倒数：
>
>   $$
>   \frac{1}{k} = \frac{x_E - x_F}{y_E - y_F} = \frac{2 - 1}{5 - 4} = 1
>   $$
>
> ---
>
> #### 2. 构建边表 (Edge Table, ET)
>
> 将各条边按照其下端点的纵坐标 $y_{\min}$ 归档入对应的扫描桶中。在同一个桶链表中，按照端点 $x$ 坐标递增排序，若 $x$ 相同，则按 $\frac{1}{k}$ 递增排序：
>
> - **$y=1$ 桶**：挂入 $FA$ 边与 $BC$ 边。因为 $FA$ 的 $x=2$ 小于 $BC$ 的 $x=6$，因此链表顺序为：$FA \to BC$。
> - **$y=2$ 桶**：无新起点边，桶为空（`NULL`）。
> - **$y=3$ 桶**：挂入 $DE$ 边与 $CD$ 边。两者的 $x=4$ 相同，但 $DE$ 的 $\frac{1}{k}=-1$ 小于 $CD$ 的 $\frac{1}{k}=1$，因此链表顺序为：$DE \to CD$。
> - **$y=4$ 桶**：挂入 $EF$ 边。
>
> **构建完的静态 ET 表结果如下**：
>
> - **$y=1$ 桶**：$\to \text{`[4 | 2 | -1/3]`(FA)} \to \text{`[5 | 6 | 0]`(BC)}$
> - **$y=2$ 桶**：$\to \text{NULL}$
> - **$y=3$ 桶**：$\to \text{`[5 | 4 | -1]`(DE)} \to \text{`[5 | 4 | 1]`(CD)}$
> - **$y=4$ 桶**：$\to \text{`[5 | 1 | 1]`(EF)}$
>
> ---
>
> #### 3. 活动边表 (Active Edge Table, AET) 的递推更新
>
> 演示扫描线 $y = 1, 2, 3$ 时的活动边表动态更新与像素区间配对：
>
> **(1) 当扫描线 $y = 1$ 时**：
>
> - 将 $y=1$ 桶中的新边并入当前为空的 AET并排序。
> - **当前 AET 状态**：
>
>   $$
>   \text{AET} \to \text{`[4 | 2 | -1/3]`(FA)} \to \text{`[5 | 6 | 0]`(BC)}
>   $$
> - **交点配对与填充区间**：
>   两交点为 $x=2$ 与 $x=6$。对两交点之间的像素区间 **$[2, 6]$** 实施色彩填充。
>
> **(2) 当扫描线 $y = 2$ 时**：
>
> - 剔除失效边：当前 AET 中无最大高度 $y_{\max}=2$ 的边，不执行剔除。
> - 递增更新 $X$ 坐标（$x_{\text{new}} = x_{\text{old}} + \frac{1}{k}$）：
>
>   - $FA$ 边：$x = 2 + (-\frac{1}{3}) = \frac{5}{3} \approx 1.67$
>   - $BC$ 边：$x = 6 + 0 = 6$
> - 并入新边：$y=2$ 桶的 ET 为空，无新边并入。对 AET 重新排序。
> - **当前 AET 状态**：
>
>   $$
>   \text{AET} \to \text{`[4 | 5/3 | -1/3]`(FA)} \to \text{`[5 | 6 | 0]`(BC)}
>   $$
> - **交点配对与填充区间**：
>   两交点为 $x \approx 1.67$ 与 $x=6$。由于填充像素网格通常取整，该处奇偶配对区间为 $[1.67, 6]$，实际着色区间仍为 **$[2, 6]$**。
>
> **(3) 当扫描线 $y = 3$ 时**：
>
> - 剔除失效边：当前 AET 中无最大高度 $y_{\max}=3$ 的边，不执行剔除。
> - 递增更新 $X$ 坐标：
>
>   - $FA$ 边：$x = \frac{5}{3} + (-\frac{1}{3}) = \frac{4}{3} \approx 1.33$
>   - $BC$ 边：$x = 6 + 0 = 6$
> - 并入新边：有 $y=3$ 桶中的新边 $DE$ 和 $CD$ 并入，并对 AET 链表中所有边按最新 $x$ 重排（四个交点 $x$ 坐标值分别为：$\frac{4}{3}$、 $4$、 $4$、 $6$）：
> - **当前 AET 状态**：
>
>   $$
>   \text{AET} \to \text{`[4 | 4/3 | -1/3]`(FA)} \to \text{`[5 | 4 | -1]`(DE)} \to \text{`[5 | 4 | 1]`(CD)} \to \text{`[5 | 6 | 0]`(BC)}
>   $$
> - **交点配对与填充区间**：
>   两两奇偶配对可得到两个独立区间：$[\frac{4}{3}, 4]$ 与 $[4, 6]$。
>   像素化填充时，区间 1 填充 $[2, 4]$，区间 2 填充 $[4, 6]$，最终合并填充区间为 **$[2, 6]$**。

---

### 3. 种子填充算法

* **简单种子填充法 (递归法)**：
  - **基本思想**：从给定的种子像素 $(x, y)$ 开始，判断其颜色。若既非边界色（边界表示法）也未被着色成填充色，则将其涂为新色，并以此为基础向四个方向（4-邻接）或八个方向（8-邻接）递归调用自身。
  - **缺点**：由于采用逐像素递归的深度优先搜索，递归调用栈深度巨大，在填充大面积区域时**极易引发系统调用栈溢出**，性能低下。
* **扫描线种子填充法**：
  - **优化原理**：通过以“水平像素线段”为基础填充单元，大大减少压栈和出栈次数，**效率极高，适用于大面积区域填充**。
  - **核心步骤**：
    1. 给定初始种子点，向左右两个方向水平扩展，填充当前扫描线上所有未填充的连续像素，记录此区间的左右端点 $[x_{\text{left}}, x_{\text{right}}]$。
    2. 在相邻的上下两条扫描线（$y+1$ 和 $y-1$）的 $[x_{\text{left}}, x_{\text{right}}]$ 区间内，从左到右搜索未填充的像素。
    3. 找到该区间的每个子连通区段最右侧的像素，作为新种子点压入栈中。
    4. 弹出栈顶种子点，重复上述步骤，直到栈为空。

---

## 三、 字符表示与处理

* **点阵字符 (Bitmap Font)**：
  - 字符形状通过二进制位图表示（`1` 表示有墨色，`0` 表示背景）。
  - *特点*：显示速度极快，但缩放或旋转时会出现严重的锯齿与失真。
* **矢量字符 (Vector Font)**：
  - 字符轮廓用一组数学曲线（如 Bézier 曲线）或折线段描述。
  - *特点*：能够无损缩放、旋转，字体美观清晰，但渲染时需要实时进行多边形转换与像素填充，开销较大。

---

## 四、 走样与反走样 (Aliasing & Anti-aliasing)

* **走样现象**：在对连续的几何图形进行离散采样时，由于采样频率不满足奈奎斯特-香农（Shannon）采样定理而引发的信号畸变与高频分量混叠。
  - **具体表现**：
    1. **阶梯状/锯齿状边界 (Jaggies)**：直线或圆弧边缘呈现不平滑的锯齿。
    2. **细节失真 (Moiré Patterns)**：在细密网格或复杂纹理区域出现条纹状杂光混叠干扰。
    3. **细小物体在扫描线间闪烁丢失 (Temporal Aliasing)**：当物体移动时，微小图元交替落入或漏出采样点，导致画面闪烁不稳。
* **常见反走样技术**：
  - **提高分辨率 / 超采样 (Super-sampling, SSAA)**：在更高的虚拟分辨率下进行像素渲染，然后经过平滑滤波器下采样回显示设备的原分辨率。*局限*：显存开销与光栅化计算开销成倍暴增，硬件代价极高。
  - **简单区域采样 (Unweighted Area Sampling / Box Filter)**：像素颜色仅由覆盖该像素的多边形**相交面积比例**决定，不考虑覆盖区域距离像素中心的具体位置。
  - **加权区域采样 (Weighted Area Sampling)**：除了考虑覆盖面积比例，还根据覆盖区域到像素中心的距离进行加权计算。**通常采用圆锥形/高斯形等加权滤波器**，越靠近中心点的相交部分对像素亮度的贡献权重越大。

---

## 五、 裁剪算法

### 1. Cohen-Sutherland 编码裁剪算法 (直线的线段裁剪)

* **区域编码设计**：
  将裁剪窗口的四条边延长，将整个平面划分为 9 个区域。每个区域用一个 4 位二进制码（$C_T C_B C_R C_L$）表示：

  ```text
  1001 | 1000 | 1010
  -----|------|-----
  0001 | 0000 | 0010  (0000 为窗口内部)
  -----|------|-----
  0101 | 0100 | 0110
  ```

  <div align="center">
  <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 350 250" width="100%" style="background-color: #ffffff; max-width: 400px; display: block; margin: auto;">
    <!-- Grid extension lines -->
    <line x1="125" y1="10" x2="125" y2="240" stroke="#ddd" stroke-width="1.5" stroke-dasharray="3 3" />
    <line x1="225" y1="10" x2="225" y2="240" stroke="#ddd" stroke-width="1.5" stroke-dasharray="3 3" />
    <line x1="10" y1="75" x2="340" y2="75" stroke="#ddd" stroke-width="1.5" stroke-dasharray="3 3" />
    <line x1="10" y1="175" x2="340" y2="175" stroke="#ddd" stroke-width="1.5" stroke-dasharray="3 3" />
    <!-- Clipping Window -->
    <rect x="125" y="75" width="100" height="100" fill="rgba(103, 194, 58, 0.1)" stroke="#67C23A" stroke-width="2.5" />
    <text x="175" y="128" font-family="sans-serif" font-size="11" font-weight="bold" fill="#67C23A" text-anchor="middle">窗口 (0000)</text>
    <!-- 9-Region Codes -->
    <text x="75" y="50" font-family="sans-serif" font-size="14" font-weight="bold" fill="#409EFF" text-anchor="middle">1001</text>
    <text x="175" y="50" font-family="sans-serif" font-size="14" font-weight="bold" fill="#333" text-anchor="middle">1000</text>
    <text x="275" y="50" font-family="sans-serif" font-size="14" font-weight="bold" fill="#409EFF" text-anchor="middle">1010</text>
    <text x="75" y="130" font-family="sans-serif" font-size="14" font-weight="bold" fill="#333" text-anchor="middle">0001</text>
    <text x="275" y="130" font-family="sans-serif" font-size="14" font-weight="bold" fill="#333" text-anchor="middle">0010</text>
    <text x="75" y="210" font-family="sans-serif" font-size="14" font-weight="bold" fill="#409EFF" text-anchor="middle">0101</text>
    <text x="175" y="210" font-family="sans-serif" font-size="14" font-weight="bold" fill="#333" text-anchor="middle">0100</text>
    <text x="275" y="210" font-family="sans-serif" font-size="14" font-weight="bold" fill="#409EFF" text-anchor="middle">0110</text>
    <text x="10" y="245" font-family="sans-serif" font-size="9" fill="#999">编码规则: [上(T) 下(B) 右(R) 左(L)]</text>
  </svg>
  </div>

* **算法执行过程**：

  1. 计算直线段两端点 $P_1, P_2$ 的编码 $code_1, code_2$。
  2. **完全保留判定**：若 $code_1 = 0 \text{ 且 } code_2 = 0$，则线段完全在窗口内，接收。
  3. **完全舍弃判定**：若 $code_1 \;\&amp;\; code_2 \neq 0$（按位与非零），说明两点同在某条边界外侧，直接拒绝。
  4. **求交裁剪判定**：若上述两项均不满足，则选择一个位于窗口外的端点（编码非零），将其与窗口的边界（按 Top, Bottom, Right, Left 顺序）求交，原端点替换为交点，重新计算编码，返回第一步循环。

---

### 2. Liang-Barsky 裁剪算法 (参数化线段裁剪)

* **基本思想**：将线段写为参数方程形式 $x = x_1 + u\Delta x$, $y = y_1 + u\Delta y$（其中 $0 \le u \le 1$）。将复杂的几何裁剪问题，转化为求解一元一次不等式组的代数问题。

* **参数的物理与几何含义详解**：
  * **参数 $u$**：
    * 几何上，它表示线段上的点到起点 $P_1$ 的**相对距离比例**。
    * $u=0$ 对应起点 $P_1$，$u=1$ 对应终点 $P_2$。$0 < u < 1$ 对应线段内部的点。
  * **参数 $p_i$ （投影位移量/方向判定因子）**：
    * 物理上，它代表线段在相应坐标轴上的投影位移量（即运动方向在边界垂直法线上的投影）。
    * **左边界 ($i=1$)**：$p_1 = -\Delta x$（即线段向左运动的位移大小）
    * **右边界 ($i=2$)**：$p_2 = \Delta x$（即线段向右运动的位移大小）
    * **下边界 ($i=3$)**：$p_3 = -\Delta y$（即线段向下运动的位移大小）
    * **上边界 ($i=4$)**：$p_4 = \Delta y$（即线段向上运动的位移大小）
    * **$p_i$ 的符号意义**：
      * $p_i < 0$：线段从边界**外侧**向**内侧**移动（**穿入**过程）。
      * $p_i > 0$：线段从边界**内侧**向**外侧**移动（**穿出**过程）。
      * $p_i = 0$：线段**平行于**该边界。
  * **参数 $q_i$ （初始边界距离/容差因子）**：
    * 物理上，它代表线段起点 $P_1$ 到对应裁剪边界的**有向距离**。如果 $q_i \ge 0$，表示起点在边界内侧（或边界上）；如果 $q_i < 0$，表示起点在边界外侧。
    * **左边界 ($i=1$)**：$q_1 = x_1 - x_{\text{wmin}}$（起点偏离左边界的距离）
    * **右边界 ($i=2$)**：$q_2 = x_{\text{wmax}} - x_1$（右边界到起点的距离）
    * **下边界 ($i=3$)**：$q_3 = y_1 - y_{\text{wmin}}$（起点偏离下边界的距离）
    * **上边界 ($i=4$)**：$q_4 = y_{\text{wmax}} - y_1$（上边界到起点的距离）
  * **比值 $r_i = \frac{q_i}{p_i}$ （交点参数值）**：
    * 几何上，它是线段无限延长后，与第 $i$ 条边界所在直线**相交时的参数 $u$ 值**。
    * 当 $p_i < 0$ 时，它是线段**穿入**第 $i$ 条边界的时刻；
    * 当 $p_i > 0$ 时，它是线段**穿出**第 $i$ 条边界的时刻。
  * **区间的更新策略 ($u_1$ 和 $u_2$)**：
    * **$u_1$（起点参数）**：记录线段**最晚进入**所有边界的时刻。因为线段必须进入所有边界内侧才可见，所以 $u_1 = \max\left(\{0\} \cup \{r_i \mid p_i < 0\}\right)$。
    * **$u_2$（终点参数）**：记录线段**最早离开**任意边界的时刻。因为线段只要离开其中任意一个边界就不可见了，所以 $u_2 = \min\left(\{1\} \cup \{r_i \mid p_i > 0\}\right)$。
    * 若 $u_1 > u_2$，表示线段在“进入所有边界”之前就已经“离开了某个边界”，即线段完全在窗口外，应予以拒绝。

* **将窗口范围 $x_{\text{wmin}} \le x_1 + u\Delta x \le x_{\text{wmax}}$ 转化为通用不等式：**
  $$
  u \cdot p_k \le q_k, \quad k = 1, 2, 3, 4
  $$

* **裁剪求解流程**：

  - 若 $p_k = 0$ 且 $q_k < 0$，线段平行于边界且在外侧，直接拒绝。
  - 对于 $p_k \neq 0$：
    - 若 $p_k < 0$，计算交点参数 $r_k = \frac{q_k}{p_k}$，更新起点参数：
      $$
      u_1 = \max(0, r_k)
      $$
    - 若 $p_k > 0$，计算交点参数 $r_k = \frac{q_k}{p_k}$，更新终点参数：
      $$
      u_2 = \min(1, r_k)
      $$
  - 若最终得到 $u_1 > u_2$，说明线段完全在窗口外，舍弃；否则，裁剪后的线段对应参数区间为 $[u_1, u_2]$。

> [!TIP]
> **期末大题演练：使用 Liang-Barsky 算法裁剪直线段**
>
> **【题目描述】**
> 已知裁剪窗口边界为：$x_{\text{wmin}} = 0$，$x_{\text{wmax}} = 2$，$y_{\text{wmin}} = 0$，$y_{\text{wmax}} = 2$。直线段的起点坐标为 $P_0(1, -1)$，终点坐标为 $P_1(2, 3)$。请用 Liang-Barsky 算法求出该线段在窗口内部的裁剪后端点坐标值。
>
> **【裁剪几何示意图】**
>
> <div align="center">
> <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 350 350" width="100%" style="background-color: #ffffff; max-width: 450px; display: block; margin: auto;">
>   <defs>
>     <pattern id="grid" width="60" height="60" patternUnits="userSpaceOnUse">
>       <path d="M 60 0 L 0 0 0 60" fill="none" stroke="#f0f0f0" stroke-width="1"/>
>     </pattern>
>     <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
>       <path d="M 0 0 L 10 5 L 0 10 z" fill="#333" />
>     </marker>
>   </defs>
>   <rect width="100%" height="100%" fill="url(#grid)" />
>   <line x1="20" y1="250" x2="320" y2="250" stroke="#333" stroke-width="1.5" marker-end="url(#arrow)" />
>   <line x1="100" y1="330" x2="100" y2="30" stroke="#333" stroke-width="1.5" marker-end="url(#arrow)" />
>   <text x="315" y="265" font-family="sans-serif" font-size="12" fill="#333">X</text>
>   <text x="85" y="35" font-family="sans-serif" font-size="12" fill="#333">Y</text>
>   <text x="85" y="265" font-family="sans-serif" font-size="11" fill="#666">0</text>
>   <line x1="160" y1="250" x2="160" y2="255" stroke="#333" /><text x="156" y="268" font-family="sans-serif" font-size="10" fill="#666">1</text>
>   <line x1="220" y1="250" x2="220" y2="255" stroke="#333" /><text x="216" y="268" font-family="sans-serif" font-size="10" fill="#666">2</text>
>   <line x1="280" y1="250" x2="280" y2="255" stroke="#333" /><text x="276" y="268" font-family="sans-serif" font-size="10" fill="#666">3</text>
>   <line x1="40" y1="250" x2="40" y2="255" stroke="#333" /><text x="32" y="268" font-family="sans-serif" font-size="10" fill="#666">-1</text>
>   <line x1="95" y1="310" x2="100" y2="310" stroke="#333" /><text x="80" y="314" font-family="sans-serif" font-size="10" fill="#666">-1</text>
>   <line x1="95" y1="190" x2="100" y2="190" stroke="#333" /><text x="84" y="194" font-family="sans-serif" font-size="10" fill="#666">1</text>
>   <line x1="95" y1="130" x2="100" y2="130" stroke="#333" /><text x="84" y="134" font-family="sans-serif" font-size="10" fill="#666">2</text>
>   <line x1="95" y1="70" x2="100" y2="70" stroke="#333" /><text x="84" y="74" font-family="sans-serif" font-size="10" fill="#666">3</text>
>   <rect x="100" y="130" width="120" height="120" fill="none" stroke="#67C23A" stroke-width="2.5" stroke-dasharray="4 2" />
>   <text x="105" y="145" font-family="sans-serif" font-size="10" fill="#67C23A" font-weight="bold">Window</text>
>   <line x1="160" y1="310" x2="220" y2="70" stroke="#E6A23C" stroke-width="1.5" stroke-dasharray="3 3" />
>   <line x1="175" y1="250" x2="205" y2="130" stroke="#409EFF" stroke-width="3.5" stroke-linecap="round" />
>   <circle cx="160" cy="310" r="4" fill="#F56C6C" />
>   <text x="170" y="315" font-family="sans-serif" font-size="11" fill="#333" font-weight="bold">P0(1,-1)</text>
>   <circle cx="220" cy="70" r="4" fill="#F56C6C" />
>   <text x="230" y="75" font-family="sans-serif" font-size="11" fill="#333" font-weight="bold">P1(2,3)</text>
>   <circle cx="175" cy="250" r="3" fill="#409EFF" />
>   <text x="180" y="243" font-family="sans-serif" font-size="9" fill="#000">I0(1.25,0)</text>
>   <circle cx="205" cy="130" r="3" fill="#409EFF" />
>   <text x="210" y="125" font-family="sans-serif" font-size="9" fill="#000">I1(1.75,2)</text>
> </svg>
> </div>
>
> ---
>
> #### 1. 参数分析与计算准备
>
> - 线段起点 $P_0(x_1, y_1) = (1, -1)$，终点 $P_1(x_2, y_2) = (2, 3)$。
> - 计算线段的变化率：
>
>   $$
>   \Delta x = x_2 - x_1 = 2 - 1 = 1, \quad \Delta y = y_2 - y_1 = 3 - (-1) = 4
>   $$
> - 直线的参数方程形式为：
>
>   $$
>   \begin{cases}
>   x = 1 + u \cdot (1) \\
>   y = -1 + u \cdot (4)
>   \end{cases} \quad (0 \le u \le 1)
>   $$
> - 窗口边界参数：$x_{\text{wmin}} = 0$，$x_{\text{wmax}} = 2$，$y_{\text{wmin}} = 0$，$y_{\text{wmax}} = 2$。
>
> #### 2. 计算各边界对应的不等式参数 $p_k, q_k, r_k$
>
> 利用公式 $u \cdot p_k \le q_k$，依次计算四个边界的参数特征：
>
> - **左边界 ($k=1$)**：
>
>   $$
>   p_1 = -\Delta x = -1 \quad (<0)
>   $$
>
>   $$
>   q_1 = x_1 - x_{\text{wmin}} = 1 - 0 = 1 \implies r_1 = \frac{q_1}{p_1} = -1
>   $$
> - **右边界 ($k=2$)**：
>
>   $$
>   p_2 = \Delta x = 1 \quad (>0)
>   $$
>
>   $$
>   q_2 = x_{\text{wmax}} - x_1 = 2 - 1 = 1 \implies r_2 = \frac{q_2}{p_2} = 1
>   $$
> - **下边界 ($k=3$)**：
>
>   $$
>   p_3 = -\Delta y = -4 \quad (<0)
>   $$
>
>   $$
>   q_3 = y_1 - y_{\text{wmin}} = -1 - 0 = -1 \implies r_3 = \frac{q_3}{p_3} = 0.25
>   $$
> - **上边界 ($k=4$)**：
>
>   $$
>   p_4 = \Delta y = 4 \quad (>0)
>   $$
>
>   $$
>   q_4 = y_{\text{wmax}} - y_1 = 2 - (-1) = 3 \implies r_4 = \frac{q_4}{p_4} = 0.75
>   $$
>
> #### 3. 确定最终参数区间 $[u_1, u_2]$
>
> 根据方向穿入（$p_k < 0$）与穿出（$p_k > 0$）的原则，分别筛选取最大和最小值：
>
> - **由外向内穿入点参数最大值 $u_1$**：
>
>   $$
>   u_1 = \max\left(\{0\} \cup \{r_k \mid p_k < 0\}\right) = \max(0, r_1, r_3) = \max(0, -1, 0.25) = 0.25
>   $$
> - **由内向外穿出点参数最小值 $u_2$**：
>
>   $$
>   u_2 = \min\left(\{1\} \cup \{r_k \mid p_k > 0\}\right) = \min(1, r_2, r_4) = \min(1, 1, 0.75) = 0.75
>   $$
>
> 因为 $u_1 = 0.25 < u_2 = 0.75$，说明线段与裁剪窗口有相交部分，裁剪有效区间对应参数范围为 $[0.25, 0.75]$。
>
> #### 4. 代入参数方程求解裁剪后的物理端点坐标
>
> - **起点交点（$u = 0.25$）**：
>
>   $$
>   \begin{cases}
>   X_{\text{start}} = 1 + 0.25 \times 1 = 1.25 \\
>   Y_{\text{start}} = -1 + 0.25 \times 4 = 0
>   \end{cases}
>   $$
>
>   交点 1 坐标为 **$(1.25, 0)$**。
> - **终点交点（$u = 0.75$）**：
>
>   $$
>   \begin{cases}
>   X_{\text{end}} = 1 + 0.75 \times 1 = 1.75 \\
>   Y_{\text{end}} = -1 + 0.75 \times 4 = 2
>   \end{cases}
>   $$
>
>   交点 2 坐标为 **$(1.75, 2)$**。
>
> **结论**：
> 裁剪后的线段有效部分处于窗口内部，其两个端点坐标分别为 **$(1.25, 0)$** 与 **$(1.75, 2)$**。

---

### 3. Sutherland-Hodgeman 算法 (多边形裁剪)

* **基本思想**：采用**分治法**和**逐边裁剪**思想。把多边形裁剪问题分解为用裁剪窗口的单条边界依次对输入的多边形顶点序列进行裁剪，每一次处理完的输出顶点序列，将作为下一次裁剪的输入顶点序列，具有流式流水线处理的特征。
* **边界求交的输入与输出判定 (顶点 $S \to P$)**：

  | 边与顶点的相对位置关系 | 是否输出交点 $I$ | 是否输出终点 $P$ |
  | :--- | :---: | :---: |
  | **S 内 $\to$ P 内** | 否 | 是 (输出 $P$) |
  | **S 内 $\to$ P 外** | 是 (输出 $I$) | 否 |
  | **S 外 $\to$ P 外** | 否 | 否 (不输出) |
  | **S 外 $\to$ P 内** | 是 (输出 $I$) | 是 (输出 $P$) |

* **缺点**：只适用于凸多边形裁剪。如果裁剪凹多边形，可能会产生多余的退化连接线。

---

### 4. Weiler-Atherton 多边形裁剪算法

* **基本思想**：可用于任意多边形（包括凹多边形、带孔多边形）的裁剪。
* 顺时针排列主多边形和裁剪多边形的顶点，建立双向循环链表，求出所有交点，标记为“入点”（由外进入窗口）或“出点”（由窗口内出来）。
* **遍历规则**：
  - 遇到入点，沿主多边形顶点顺时针遍历；
  - 遇到出点，跳转至裁剪多边形，沿裁剪多边形边界顺时针遍历，直至回到起点形成闭合裁剪区域。

---

### 5. 裁剪算法特性横向对比

| 裁剪算法                      | 裁剪对象 | 核心优势                                                   | 局限性/缺点                        |
| :---------------------------- | :------- | :--------------------------------------------------------- | :--------------------------------- |
| **Cohen-Sutherland**    | 线段     | 编码快速，特别适合绝大部分线段处于完全保留或完全舍弃的场景 | 频繁迭代求交时效率降低             |
| **Liang-Barsky**        | 线段     | 参数化计算，减少了乘除法的次数                             | 仅限矩形窗口                       |
| **Sutherland-Hodgeman** | 多边形   | 流水线结构简单，易于硬件流水线实现                         | 凹多边形裁剪可能会产生冗余连接线   |
| **Weiler-Atherton**     | 多边形   | 支持任意复杂的凹多边形和内孔裁剪                           | 数据结构十分复杂，涉及较多链表跳转 |

---

# 第 4 章 图形几何变换

## 一、 齐次坐标 (Homogeneous Coordinates)

* **概念**：用 $n+1$ 维向量来表示 $n$ 维空间中的点。对于二维平面上的点 $(x, y)$，其齐次坐标表示为 $(hx, hy, h)$，其中 $h \neq 0$ 是缩放因子。通常令 $h = 1$，即标准齐次坐标为 $(x, y, 1)$。
* **引入齐次坐标的目的**：

  - 将图形学中原本属于非线性的平移操作（向量加法），统一化为矩阵乘法。
  - 将平移、旋转、缩放等多种操作统一写成相同的矩阵乘法形式，从而支持多级复合矩阵的连续连乘乘积，大幅提升图形硬件管线的执行效率。
* **齐次坐标向普通坐标的转换**：

  $$
  (x_h, y_h, w) \implies \left( \frac{x_h}{w}, \frac{y_h}{w} \right)
  $$

---

## 二、 几何变换通式及其分块含义

引入齐次坐标后，图形的几何变换可以表示为矩阵乘法。下面分别给出二维与三维几何变换矩阵的通式及其物理含义：

### 1. 二维齐次变换通式 ($3 \times 3$ 矩阵)

$$
T_{3 \times 3} = \begin{bmatrix}
a & b & p_x \\
c & d & p_y \\
l & m & s
\end{bmatrix} = \left[ \begin{array}{cc|c}
a & b & p_x \\
c & d & p_y \\
\hline
l & m & s
\end{array} \right]
$$

* **左上角 $2 \times 2$ 矩阵 $\begin{bmatrix} a & b \\ c & d \end{bmatrix}$（线性变换项）**：
  * 控制二维空间中的**旋转、缩放、反射对称和错切**。
  * **比例缩放 (Scaling)**：由对角线上的元素 $a, d$ 控制。
    * **拉伸/放大**：若 $a > 1$（或 $d > 1$），则沿 $X$ 轴（或 $Y$ 轴）方向放大。
    * **压缩/缩小**：若 $0 < a < 1$（或 $0 < d < 1$），则在对应轴方向上缩小。
    * **无缩放**：当 $a = 1, d = 1$ 时。
    * **反射/对称镜像 (Mirror Reflection)**：若对角线元素为负数。例如，若 $a = -1, d = 1$，则图形关于 $Y$ 轴反射对称；若 $a = 1, d = -1$，关于 $X$ 轴对称；若 $a = -1, d = -1$，关于原点对称。
  * **旋转 (Rotation)**：当矩阵表现为 $\begin{bmatrix} \cos\theta & -\sin\theta \\ \sin\theta & \cos\theta \end{bmatrix}$ 时，代表绕原点逆时针旋转角度 $\theta$。它改变 $x, y$ 的坐标值使其绕原点圆周运动，但保持点到原点的距离不变。
  * **错切 (Shear)**：由非对角线上的 $b, c$ 控制。其中 $b$ 产生沿 $X$ 方向的错切，$c$ 产生沿 $Y$ 方向的错切。
* **右上角 $2 \times 1$ 向量 $\begin{bmatrix} p_x \\ p_y \end{bmatrix}$（平移变换项）**：
  * 控制图形沿 $X, Y$ 方向的**平移位移量**。
  * 在齐次坐标最后一位 $w = 1$ 的情况下，平移项 $p_x, p_y$ 相当于直接累加到原坐标上（$x' = ax + by + p_x \cdot 1$）。若 $w \neq 1$，平移产生的实际位移为 $p_x/w$ 和 $p_y/w$。
* **左下角 $1 \times 2$ 向量 $\begin{bmatrix} l & m \end{bmatrix}$（透视投影项）**：
  * 用于二维空间中的**透视投影变换**，控制视线并非平行投射时的汇聚形变（即产生灭点）。
* **右下角 $1 \times 1$ 标量 $[s]$（全局比例因子）**：
  * 控制图形的**全局等比例统一缩放**。
  * 在将齐次坐标转换为普通笛卡尔坐标时，所有分量都需要除以齐次项（此时 $w' = s$），这会导致普通坐标变为原先的 $\frac{1}{s}$：
    * 若 $0 < s < 1$：图形整体**等比放大**。
    * 若 $s > 1$：图形整体**等比缩小**。
    * 若 $s = 1$：图形保持原大小。

---

### 2. 三维齐次变换通式 ($4 \times 4$ 矩阵)

$$
T_{4 \times 4} = \begin{bmatrix}
a & b & c & p_x \\
d & e & f & p_y \\
g & h & i & p_z \\
l & m & n & s
\end{bmatrix} = \left[ \begin{array}{ccc|c}
a & b & c & p_x \\
d & e & f & p_y \\
g & h & i & p_z \\
\hline
l & m & n & s
\end{array} \right]
$$

* **左上角 $3 \times 3$ 矩阵（线性变换项）**：
  * 控制三维空间中的**旋转、缩放、反射对称和错切**。
  * **比例缩放 (Scaling)**：由主对角线上的 $a, e, i$ 控制（分别对应 $s_x, s_y, s_z$）。
    * 因子 $> 1$ 代表沿对应轴**拉伸**，处于 $0$ 到 $1$ 之间代表**压缩**。
    * **镜像反射**：若有对角线项为负值，则沿相应的平面镜像。例如 $i = -1$ 时，物体的 $z$ 坐标反转，发生关于 $XY$ 平面的镜像反射。
  * **旋转 (Rotation)**：旋转通过整个 $3 \times 3$ 矩阵的联合变化实现。对于纯旋转，该子矩阵必须是**正交矩阵**（各行、各列向量正交且模为1），且行列式值为 1。
    * 绕三个不同的坐标轴旋转时，改变的矩阵元素各有不同，但旋转轴对应的坐标分量保持不变：
      * **绕 Z 轴旋转**：改变左上角 $2 \times 2$ 的 $a, b, d, e$ 元素（即 $X, Y$ 坐标发生变化，而 $Z$ 坐标不变，此时对角线上的 $i = 1$）。
      * **绕 X 轴旋转**：改变右下角 $2 \times 2$ 的 $e, f, h, i$ 元素（即 $Y, Z$ 坐标发生变化，而 $X$ 坐标不变，此时对角线上的 $a = 1$）。
      * **绕 Y 轴旋转**：改变四个角上的 $a, c, g, i$ 元素（即 $X, Z$ 坐标发生变化，而 $Y$ 坐标不变，此时对角线上的 $e = 1$）。
  * **错切 (Shear)**：由非对角线上的 6 个元素控制。
* **右上角 $3 \times 1$ 向量 $\begin{bmatrix} p_x \\ p_y \\ p_z \end{bmatrix}$（平移变换项）**：
  * 控制三维物体沿 $X, Y, Z$ 三个方向的**空间平移距离**。在 $w=1$ 下，平移分量直接作为常数相加。
* **左下角 $1 \times 3$ 向量 $\begin{bmatrix} l & m & n \end{bmatrix}$（透视投影项）**：
  * 控制空间几何物体在进行**透视投影**时产生的近大远小的投影形变。
* **右下角 $1 \times 1$ 标量 $[s]$（全局比例因子）**：
  * 控制三维物体的**整体全局等比放缩**。由于三维空间坐标在齐次归一化时都要除以 $s$，因此当 $s > 1$ 时，物体的尺寸变为原来的 $\frac{1}{s}$，而物体的物理体积则缩小为原来的 $\frac{1}{s^3}$。

---

## 三、 基本变换矩阵 (2D 与 3D 矩阵全集)

### 1. 二维基本齐次变换矩阵 ($3 \times 3$)

* **平移变换 (Translation)**：

  $$
  T(t_x, t_y) = \begin{bmatrix}
  1 & 0 & t_x \\
  0 & 1 & t_y \\
  0 & 0 & 1
  \end{bmatrix}
  $$

* **比例缩放 (Scaling)**：

  $$
  S(s_x, s_y) = \begin{bmatrix}
  s_x & 0 & 0 \\
  0 & s_y & 0 \\
  0 & 0 & 1
  \end{bmatrix}
  $$

* **旋转变换 (Rotation，绕原点逆时针旋转角度 $\theta$)**：

  $$
  R(\theta) = \begin{bmatrix}
  \cos\theta & -\sin\theta & 0 \\
  \sin\theta & \cos\theta & 0 \\
  0 & 0 & 1
  \end{bmatrix}
  $$

* **对称反射变换 (Reflection)**：
  - **关于 $X$ 轴反射**：

    $$
    M_x = \begin{bmatrix}
    1 & 0 & 0 \\
    0 & -1 & 0 \\
    0 & 0 & 1
    \end{bmatrix}
    $$

  - **关于 $Y$ 轴反射**：

    $$
    M_y = \begin{bmatrix}
    -1 & 0 & 0 \\
    0 & 1 & 0 \\
    0 & 0 & 1
    \end{bmatrix}
    $$

  - **关于原点对称反射**：

    $$
    M_{\text{origin}} = \begin{bmatrix}
    -1 & 0 & 0 \\
    0 & -1 & 0 \\
    0 & 0 & 1
    \end{bmatrix}
    $$

  - **关于直线 $y=x$ 反射**：

    $$
    M_{y=x} = \begin{bmatrix}
    0 & 1 & 0 \\
    1 & 0 & 0 \\
    0 & 0 & 1
    \end{bmatrix}
    $$

  - **关于直线 $y=-x$ 反射**：

    $$
    M_{y=-x} = \begin{bmatrix}
    0 & -1 & 0 \\
    -1 & 0 & 0 \\
    0 & 0 & 1
    \end{bmatrix}
    $$

* **错切变换 (Shear)**：
  - **沿 $X$ 方向错切**：

    $$
    SH_x(sh_x) = \begin{bmatrix}
    1 & sh_x & 0 \\
    0 & 1 & 0 \\
    0 & 0 & 1
    \end{bmatrix}
    $$

  - **沿 $Y$ 方向错切**：

    $$
    SH_y(sh_y) = \begin{bmatrix}
    1 & 0 & 0 \\
    sh_y & 1 & 0 \\
    0 & 0 & 1
    \end{bmatrix}
    $$


---

### 2. 三维基本齐次变换矩阵 ($4 \times 4$)

* **平移变换**：

  $$
  T(t_x, t_y, t_z) = \begin{bmatrix}
  1 & 0 & 0 & t_x \\
  0 & 1 & 0 & t_y \\
  0 & 0 & 1 & t_z \\
  0 & 0 & 0 & 1
  \end{bmatrix}
  $$

* **比例缩放**：

  $$
  S(s_x, s_y, s_z) = \begin{bmatrix}
  s_x & 0 & 0 & 0 \\
  0 & s_y & 0 & 0 \\
  0 & 0 & s_z & 0 \\
  0 & 0 & 0 & 1
  \end{bmatrix}
  $$

* **绕三个主坐标轴的旋转矩阵**：
  - **绕 Z 轴旋转 $\theta$**：

    $$
    R_z(\theta) = \begin{bmatrix}
    \cos\theta & -\sin\theta & 0 & 0 \\
    \sin\theta & \cos\theta & 0 & 0 \\
    0 & 0 & 1 & 0 \\
    0 & 0 & 0 & 1
    \end{bmatrix}
    $$

  - **绕 X 轴旋转 $\theta$**：

    $$
    R_x(\theta) = \begin{bmatrix}
    1 & 0 & 0 & 0 \\
    0 & \cos\theta & -\sin\theta & 0 \\
    0 & \sin\theta & \cos\theta & 0 \\
    0 & 0 & 0 & 1
    \end{bmatrix}
    $$

  - **绕 Y 轴旋转 $\theta$**：

    $$
    R_y(\theta) = \begin{bmatrix}
    \cos\theta & 0 & \sin\theta & 0 \\
    0 & 1 & 0 & 0 \\
    -\sin\theta & 0 & \cos\theta & 0 \\
    0 & 0 & 0 & 1
    \end{bmatrix}
    $$

* **对称反射变换 (Reflection)**：
  - **关于 $XY$ 平面反射 ($z \to -z$)**：

    $$
    M_{xy} = \begin{bmatrix}
    1 & 0 & 0 & 0 \\
    0 & 1 & 0 & 0 \\
    0 & 0 & -1 & 0 \\
    0 & 0 & 0 & 1
    \end{bmatrix}
    $$

  - **关于 $YZ$ 平面反射 ($x \to -x$)**：

    $$
    M_{yz} = \begin{bmatrix}
    -1 & 0 & 0 & 0 \\
    0 & 1 & 0 & 0 \\
    0 & 0 & 1 & 0 \\
    0 & 0 & 0 & 1
    \end{bmatrix}
    $$

  - **关于 $ZX$ 平面反射 ($y \to -y$)**：

    $$
    M_{zx} = \begin{bmatrix}
    1 & 0 & 0 & 0 \\
    0 & -1 & 0 & 0 \\
    0 & 0 & 1 & 0 \\
    0 & 0 & 0 & 1
    \end{bmatrix}
    $$

* **错切变换 (Shear，以沿 Z 轴错切为例)**：
  - 错切量由 $Z$ 坐标的大小决定，使 $X, Y$ 坐标发生线性错切偏移：

    $$
    SH_z(sh_x, sh_y) = \begin{bmatrix}
    1 & 0 & sh_x & 0 \\
    0 & 1 & sh_y & 0 \\
    0 & 0 & 1 & 0 \\
    0 & 0 & 0 & 1
    \end{bmatrix}
    $$

---

## 四、 复合变换 (Composite Transformations)

* **乘法顺序非交换性**：由于矩阵乘法不满足交换律（即 $A \cdot B \neq B \cdot A$），多个变换连续作用时，矩阵连乘的顺序至关重要。
* **典型推导：关于任意点 $(x_f, y_f)$ 的旋转**：
  为了让物体绕任意指定点 $F(x_f, y_f)$ 旋转 $\theta$，可拆解为三步操作：

  1. **平移**物体，使点 $F$ 与坐标原点重合：$T(-x_f, -y_f)$。
  2. 绕原点进行**标准旋转**：$R(\theta)$。
  3. **反向平移**物体，使原点回到点 $F$ 的原始位置：$T(x_f, y_f)$。

  复合变换矩阵表达为（右乘列向量的顺序）：

<div align="center">
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 900 280" width="100%" height="100%" style="background-color: #ffffff; max-width: 700px; display: block; margin: auto;">
  <defs>
    <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M 0 0 L 10 5 L 0 10 z" fill="#333333" />
    </marker>
    <marker id="arrow-blue" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="5" markerHeight="5" orient="auto-start-reverse">
      <path d="M 0 0 L 10 5 L 0 10 z" fill="#0288d1" />
    </marker>
  </defs>
  <g transform="translate(10, 20)">
    <text x="130" y="20" style="font-family: Arial; font-size: 13px; font-weight: bold; fill: #333333; text-anchor: middle;">步骤1: 平移使其与原点重合</text>
    <line x1="30" y1="200" x2="230" y2="200" style="stroke: #cccccc; stroke-width: 1.5;" marker-end="url(#arrow)" />
    <line x1="50" y1="220" x2="50" y2="40" style="stroke: #cccccc; stroke-width: 1.5;" marker-end="url(#arrow)" />
    <text x="225" y="215" style="font-family: Arial; font-size: 11px; fill: #666;">X</text>
    <text x="35" y="45" style="font-family: Arial; font-size: 11px; fill: #666;">Y</text>
    <circle cx="150" cy="100" r="5" style="fill: #e91e63;" />
    <text x="160" y="95" style="font-family: Arial; font-size: 11px; fill: #e91e63; font-weight: bold;">F(xf, yf)</text>
    <polygon points="130,110 170,110 150,70" style="fill: #ffb74d; stroke: #ff9800; stroke-width: 1.5; fill-opacity: 0.6;" />
    <path d="M 150 100 Q 100 130 55 200" style="fill: none; stroke: #0288d1; stroke-width: 2; stroke-dasharray: 4,4;" marker-end="url(#arrow-blue)" />
    <text x="95" y="130" style="font-family: Arial; font-size: 11px; fill: #0288d1; font-weight: bold;">T(-xf, -yf)</text>
  </g>
  <g transform="translate(310, 20)">
    <text x="130" y="20" style="font-family: Arial; font-size: 13px; font-weight: bold; fill: #333333; text-anchor: middle;">步骤2: 绕原点旋转 θ</text>
    <line x1="30" y1="200" x2="230" y2="200" style="stroke: #cccccc; stroke-width: 1.5;" marker-end="url(#arrow)" />
    <line x1="50" y1="220" x2="50" y2="40" style="stroke: #cccccc; stroke-width: 1.5;" marker-end="url(#arrow)" />
    <text x="225" y="215" style="font-family: Arial; font-size: 11px; fill: #666;">X</text>
    <text x="35" y="45" style="font-family: Arial; font-size: 11px; fill: #666;">Y</text>
    <circle cx="50" cy="200" r="5" style="fill: #e91e63;" />
    <polygon points="30,210 70,210 50,170" style="fill: #ffb74d; stroke: #ff9800; stroke-width: 1.5; fill-opacity: 0.3; stroke-dasharray: 2,2;" />
    <g transform="translate(50,200) rotate(45) translate(-50,-200)">
      <polygon points="30,210 70,210 50,170" style="fill: #ffb74d; stroke: #ff9800; stroke-width: 1.5; fill-opacity: 0.8;" />
    </g>
    <path d="M 50 160 A 40 40 0 0 1 78 172" style="fill: none; stroke: #0288d1; stroke-width: 2;" marker-end="url(#arrow-blue)" />
    <text x="80" y="160" style="font-family: Arial; font-size: 11px; fill: #0288d1; font-weight: bold;">R(θ)</text>
  </g>
  <g transform="translate(610, 20)">
    <text x="130" y="20" style="font-family: Arial; font-size: 13px; font-weight: bold; fill: #333333; text-anchor: middle;">步骤3: 反向平移回原位置</text>
    <line x1="30" y1="200" x2="230" y2="200" style="stroke: #cccccc; stroke-width: 1.5;" marker-end="url(#arrow)" />
    <line x1="50" y1="220" x2="50" y2="40" style="stroke: #cccccc; stroke-width: 1.5;" marker-end="url(#arrow)" />
    <text x="225" y="215" style="font-family: Arial; font-size: 11px; fill: #666;">X</text>
    <text x="35" y="45" style="font-family: Arial; font-size: 11px; fill: #666;">Y</text>
    <circle cx="150" cy="100" r="5" style="fill: #e91e63;" />
    <text x="160" y="95" style="font-family: Arial; font-size: 11px; fill: #e91e63; font-weight: bold;">F(xf, yf)</text>
    <path d="M 50 200 Q 100 130 150 100" style="fill: none; stroke: #0288d1; stroke-width: 2; stroke-dasharray: 4,4;" marker-end="url(#arrow-blue)" />
    <text x="110" y="160" style="font-family: Arial; font-size: 11px; fill: #0288d1; font-weight: bold;">T(xf, yf)</text>
    <g transform="translate(100,-100) translate(50,200) rotate(45) translate(-50,-200)">
      <polygon points="30,210 70,210 50,170" style="fill: #ffb74d; stroke: #ff9800; stroke-width: 1.5; fill-opacity: 0.8;" />
    </g>
  </g>
</svg>
</div>

  复合变换矩阵表达为（右乘列向量的顺序）：

$$
  M = T(x_f, y_f) \cdot R(\theta) \cdot T(-x_f, -y_f)
$$

  **矩阵各部分的具体定义与参数分析**：
  * **平移到原点矩阵 $T(-x_f, -y_f)$**：
    $$
    T(-x_f, -y_f) = \begin{bmatrix}
    1 & 0 & -x_f \\
    0 & 1 & -y_f \\
    0 & 0 & 1
    \end{bmatrix}
    $$
    * **作用**：将旋转中心点 $F(x_f, y_f)$ 平移到坐标原点。参数中的平移增量 $t_x = -x_f$，$t_y = -y_f$，使得后续的旋转可以利用“绕原点旋转”的标准公式来执行。
  * **绕原点标准旋转矩阵 $R(\theta)$**：
    $$
    R(\theta) = \begin{bmatrix}
    \cos\theta & -\sin\theta & 0 \\
    \sin\theta & \cos\theta & 0 \\
    0 & 0 & 1
    \end{bmatrix}
    $$
    * **作用**：控制物体绕当前的坐标原点逆时针旋转 $\theta$ 角（弧度制）。
  * **反向平移回原处矩阵 $T(x_f, y_f)$**：
    $$
    T(x_f, y_f) = \begin{bmatrix}
    1 & 0 & x_f \\
    0 & 1 & y_f \\
    0 & 0 & 1
    \end{bmatrix}
    $$
    * **作用**：这是第一个平移矩阵的逆矩阵。负责在完成原点旋转后，将整个物体连同旋转中心一起还原，向正方向平移 $t_x = x_f$ 和 $t_y = y_f$ 返回最初的位置。

  **逐步乘积展开计算过程**：
  1. 计算右侧两个矩阵相乘 $R(\theta) \cdot T(-x_f, -y_f)$：
     $$
     R(\theta) \cdot T(-x_f, -y_f) = \begin{bmatrix}
     \cos\theta & -\sin\theta & 0 \\
     \sin\theta & \cos\theta & 0 \\
     0 & 0 & 1
     \end{bmatrix} \begin{bmatrix}
     1 & 0 & -x_f \\
     0 & 1 & -y_f \\
     0 & 0 & 1
     \end{bmatrix} = \begin{bmatrix}
     \cos\theta & -\sin\theta & -x_f\cos\theta + y_f\sin\theta \\
     \sin\theta & \cos\theta & -x_f\sin\theta - y_f\cos\theta \\
     0 & 0 & 1
     \end{bmatrix}
     $$
  2. 左乘最左侧的平移矩阵 $T(x_f, y_f)$：
     $$
     M = T(x_f, y_f) \cdot \left[ R(\theta) \cdot T(-x_f, -y_f) \right] = \begin{bmatrix}
     1 & 0 & x_f \\
     0 & 1 & y_f \\
     0 & 0 & 1
     \end{bmatrix} \begin{bmatrix}
     \cos\theta & -\sin\theta & -x_f\cos\theta + y_f\sin\theta \\
     \sin\theta & \cos\theta & -x_f\sin\theta - y_f\cos\theta \\
     0 & 0 & 1
     \end{bmatrix}
     $$
     $$
     = \begin{bmatrix}
     \cos\theta & -\sin\theta & -x_f\cos\theta + y_f\sin\theta + x_f \\
     \sin\theta & \cos\theta & -x_f\sin\theta - y_f\cos\theta + y_f \\
     0 & 0 & 1
     \end{bmatrix}
     $$
  3. 整理矩阵第三列的代数常数项，最终得到任意点旋转复合矩阵通式：
     $$
     M = \begin{bmatrix}
     \cos\theta & -\sin\theta & x_f(1-\cos\theta) + y_f\sin\theta \\
     \sin\theta & \cos\theta & y_f(1-\cos\theta) - x_f\sin\theta \\
     0 & 0 & 1
     \end{bmatrix}
     $$

---

## 五、 全局固定坐标模式与活动局部坐标模式 (必考综合计算理论)

* **全局固定坐标模式 (Global Coordinate Mode / Left Multi-multiplication)**：
  - **视点**：所有的空间变换（平移、旋转、缩放）都是相对于绝对的、静止的“世界坐标系”进行。
  - **数学运算顺序**：采用矩阵**左乘模式**。若变换步骤为：先进行 $A$，再进行 $B$，则最终的变换矩阵连乘积为：

    $$
    M = B \cdot A
    $$

    即新矩阵左乘到累积矩阵链上，最先执行的变换 $A$ 紧贴在被乘的顶点向量 $v$ 左侧：$M \cdot v = B \cdot (A \cdot v)$。
* **活动局部坐标模式 (Local Coordinate Mode / Right Multi-multiplication)**：
  - **视点**：每一次空间变换都是相对于上一次变换后产生的新物体的“活动局部坐标系”进行（即坐标轴会随着变换一起运动）。
  - **数学运算顺序**：采用矩阵**右乘模式**。若变换步骤为：先进行 $A$，再进行 $B$，则最终的变换矩阵连乘积为：

    $$
    M = A \cdot B
    $$

    即新矩阵右乘到累积矩阵链上，先写的变换矩阵反而被置于左侧，顶点的最终计算形式依然是：$M \cdot v = A \cdot (B \cdot v)$，这在数学上等价于在世界坐标系下先执行 $B$，再执行 $A$。

  > [!NOTE]
  > **重要考点：OpenGL 中的变换顺序与代码书写顺序**
  > - OpenGL 采用的是**活动局部坐标系模式（右乘）**。
  > - 在 OpenGL 代码中，**先调用（写在上面）的变换函数矩阵位于乘积链的左侧，后调用（写在下面）的变换函数矩阵位于乘积链的右侧**。
  > - 因此，变换对几何物体的实际生效顺序为：**从下到上（即从右向左）执行**。先写的变换后执行，后写的变换先执行。
  >

---

## 六、 OpenGL 中的三类变换应用函数

* `glTranslatef(tx, ty, tz)`：平移当前矩阵。
* `glRotatef(angle, x, y, z)`：让物体绕指定方向向量 $(x, y, z)$ 旋转给定的角度 `angle`。
* `glScalef(sx, sy, sz)`：沿三轴缩放当前矩阵。

---

# 第 5 章 三维观察

## 一、 三维观察的流程

三维物体在最终呈现在显示屏上之前，需要经历如下一系列空间坐标系的映射与变换流程：

```mermaid
graph TD
    MC["模型坐标系 (MC)<br>Model Coordinates"] -->|模型变换| WC["世界坐标系 (WC)<br>World Coordinates"]
    WC -->|观察变换 gluLookAt| VC["观察坐标系 (VC)<br>Viewing Coordinates"]
    VC -->|投影变换 glOrtho/glFrustum| CC["裁剪坐标系 (CC)<br>Clipping Coordinates"]
    CC -->|透视除法 /w| NDC["归一化设备坐标系 (NDC)<br>Normalized Device"]
    NDC -->|视口映射| DC["屏幕设备坐标系 (DC)<br>Device Coordinates"]
```

---

## 二、 投影分类

投影将高维几何体降维投射至低维平面，主要分为**平行投影**与**透视投影**两大类：

```mermaid
graph TD
    Projection["投影分类"]
    Projection --> Parallel["平行投影 (Parallel)"]
    Projection --> Perspective["透视投影 (Perspective)"]

    Parallel --> Ortho["正投影 (Orthographic)"]
    Parallel --> Oblique["斜投影 (Oblique)"]

    Ortho --> ThreeView["三视图 (Front, Top, Side)"]
    Ortho --> Axonometric["正轴测 (正等测、正二测、正三测)"]

    Oblique --> ObliqueEtc["斜投影 (斜等测/Cavalier、斜二测/Cabinet)"]

    Perspective --> OnePoint["一点透视 (1-Point)"]
    Perspective --> TwoPoint["两点透视 (2-Point)"]
    Perspective --> ThreePoint["三点透视 (3-Point)"]
```

---

## 三、 平行投影

* **基本特点**：投影线互相平行。物体的投影大小不随物体的距离改变而改变，能够保持物体各部分的真实几何比例与平行性。
* **正投影 (Orthographic Projection)**：投影线与投影面相互垂直。
  - **三视图**：投影面与某个坐标轴垂直（主视图、俯视图、侧视图）。
  - **正轴测**：投影面与三个坐标轴倾斜，根据倾斜角不同，坐标轴收缩率不同：
    - *正等测*：三个轴的缩放比例完全相等。
    - *正二测*：两个轴的缩放比例相等，第三个不等。
    - *正三测*：三个轴的缩放比例互不相等。
* **斜投影 (Oblique Projection)**：投影线与投影面成倾斜角。
  - **斜等测 (Cavalier)**：投影线与投影面成 $45^\circ$，投影面上的倾斜边长度保持原长不变。
  - **斜二测 (Cabinet)**：投影线与投影面成约 $63.4^\circ$，投影面上倾斜轴的长度缩减为原长的一半。

---

## 四、 透视投影

* **基本特点**：投影线汇聚于单点（视点/投影中心），产生“近大远小”的逼真视觉效果，但无法维持平行的比例。
* **透视投影矩阵 (以投影平面位于 $z=d$, 视点在原点为例)**：

  $$
  M_{\text{pers}} = \begin{bmatrix}
  1 & 0 & 0 & 0 \\
  0 & 1 & 0 & 0 \\
  0 & 0 & 1 & 0 \\
  0 & 0 & \frac{1}{d} & 0
  \end{bmatrix}
  $$

  作用于齐次坐标 $[x, y, z, 1]^T$ 后得到 $[x, y, z, \frac{z}{d}]^T$，进行透视除法（归一化）后：

  $$
  x' = \frac{x \cdot d}{z}, \quad y' = \frac{y \cdot d}{z}
  $$
* **灭点 (Vanishing Point) 与主灭点 (Principal Vanishing Point)**：

  - **灭点**：空间中不平行于投影平面的平行直线系在透视投影后相交的汇聚点。
  - **主灭点**：空间中平行于世界坐标轴（$X$ 轴、$Y$ 轴或 $Z$ 轴）的直线系产生的灭点。
* **透视的维数分类与识别判定**：

  - **一点透视 (One-Point Perspective)**：
    * **几何特征**：投影面（视面）平行于物体的两个主坐标平面（即仅与某一个主轴垂直，例如仅垂直于 $Z$ 轴）。
    * **主灭点数量**：产生 **1 个**主灭点。
    * **如何辨别**：
      * 在投影图上，物体的两组主方向平行棱边（如水平边和垂直边）仍然保持互相平行，不产生交点；
      * 仅有第三个主轴方向（垂直于投影面的深度方向，如 $Z$ 轴方向）的平行棱线向远方延伸并汇聚于屏幕上的单一点（即主灭点）。
  - **两点透视 (Two-Point Perspective / 成角透视)**：
    * **几何特征**：投影面平行于物体的某一个主坐标轴（通常平行于铅垂轴 $Y$ 轴），但与另外两个主轴（如 $X$ 轴和 $Z$ 轴）倾斜相交。
    * **主灭点数量**：产生 **2 个**主灭点。
    * **如何辨别**：
      * 物体的垂直方向棱线仍然保持相互平行且直立，在画面上没有灭点；
      * 物体水平方向的两组平行棱线（如长、宽方向的边）在投影图上分别向左、右下方延伸，汇聚于视平线上的左右两个不同的主灭点。
  - **三点透视 (Three-Point Perspective / 斜透视)**：
    * **几何特征**：投影面与物体的三个主轴都倾斜相交（即不平行于任何一个坐标轴和主平面）。
    * **主灭点数量**：产生 **3 个**主灭点。
    * **如何辨别**：
      * 物体的长、宽、高三个主轴方向的平行线在投影面上均发生汇聚，没有任何一组主轴棱线在画面上保持平行；
      * 三组平行棱线分别汇聚于三个主灭点，其中两个灭点通常在视平线上（左右分布），第三个灭点则位于视平线之上（仰视）或之下（俯视），常用于表现宏大高耸物体的视觉张力。

<div align="center">
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 900 300" width="100%" height="100%" style="background-color: #ffffff; max-width: 800px; display: block; margin: auto;">
  <g transform="translate(10, 10)">
    <rect x="0" y="0" width="270" height="260" rx="5" fill="#fcfcfc" stroke="#dddddd" stroke-width="1.5" />
    <text x="135" y="30" font-family="sans-serif" font-size="14" font-weight="bold" fill="#333" text-anchor="middle">一点透视 (1个灭点)</text>
    <line x1="10" y1="130" x2="260" y2="130" stroke="#cccccc" stroke-dasharray="3,3" stroke-width="1" />
    <circle cx="135" cy="130" r="4" fill="#ff4d4f" />
    <text x="135" y="122" font-family="sans-serif" font-size="10" fill="#ff4d4f" font-weight="bold" text-anchor="middle">灭点 VP1</text>
    <polygon points="95,160 175,160 175,220 95,220" fill="none" stroke="#333333" stroke-width="1.5" />
    <polygon points="115,145 155,145 155,175 115,175" fill="none" stroke="#999999" stroke-width="1" />
    <line x1="95" y1="160" x2="115" y2="145" stroke="#409eff" stroke-width="1.5" />
    <line x1="175" y1="160" x2="155" y2="145" stroke="#409eff" stroke-width="1.5" />
    <line x1="95" y1="220" x2="115" y2="175" stroke="#409eff" stroke-width="1.5" />
    <line x1="175" y1="220" x2="155" y2="175" stroke="#409eff" stroke-width="1.5" />
    <line x1="115" y1="145" x2="135" y2="130" stroke="#ff4d4f" stroke-dasharray="2,2" stroke-width="1" />
    <line x1="155" y1="145" x2="135" y2="130" stroke="#ff4d4f" stroke-dasharray="2,2" stroke-width="1" />
    <text x="135" y="245" font-family="sans-serif" font-size="11" fill="#666" text-anchor="middle">X轴和Y轴平行，仅Z轴(深度)汇聚</text>
  </g>
  <g transform="translate(305, 10)">
    <rect x="0" y="0" width="270" height="260" rx="5" fill="#fcfcfc" stroke="#dddddd" stroke-width="1.5" />
    <text x="135" y="30" font-family="sans-serif" font-size="14" font-weight="bold" fill="#333" text-anchor="middle">两点透视 (2个灭点)</text>
    <line x1="10" y1="130" x2="260" y2="130" stroke="#cccccc" stroke-dasharray="3,3" stroke-width="1" />
    <circle cx="20" cy="130" r="4" fill="#ff4d4f" />
    <circle cx="250" cy="130" r="4" fill="#ff4d4f" />
    <text x="25" y="122" font-family="sans-serif" font-size="10" fill="#ff4d4f" font-weight="bold">VP1</text>
    <text x="245" y="122" font-family="sans-serif" font-size="10" fill="#ff4d4f" font-weight="bold" text-anchor="end">VP2</text>
    <line x1="135" y1="150" x2="135" y2="220" stroke="#333" stroke-width="2" />
    <line x1="90" y1="160" x2="90" y2="200" stroke="#999" stroke-width="1" />
    <line x1="180" y1="165" x2="180" y2="205" stroke="#999" stroke-width="1" />
    <line x1="135" y1="150" x2="90" y2="160" stroke="#333" stroke-width="1.5" />
    <line x1="135" y1="220" x2="90" y2="200" stroke="#333" stroke-width="1.5" />
    <line x1="135" y1="150" x2="180" y2="165" stroke="#333" stroke-width="1.5" />
    <line x1="135" y1="220" x2="180" y2="205" stroke="#333" stroke-width="1.5" />
    <line x1="90" y1="160" x2="20" y2="130" stroke="#ff4d4f" stroke-dasharray="2,2" stroke-width="1" />
    <line x1="90" y1="200" x2="20" y2="130" stroke="#ff4d4f" stroke-dasharray="2,2" stroke-width="1" />
    <line x1="180" y1="165" x2="250" y2="130" stroke="#ff4d4f" stroke-dasharray="2,2" stroke-width="1" />
    <line x1="180" y1="205" x2="250" y2="130" stroke="#ff4d4f" stroke-dasharray="2,2" stroke-width="1" />
    <line x1="135" y1="150" x2="250" y2="130" stroke="#ff4d4f" stroke-dasharray="2,2" stroke-width="1" />
    <line x1="135" y1="150" x2="20" y2="130" stroke="#ff4d4f" stroke-dasharray="2,2" stroke-width="1" />
    <text x="135" y="245" font-family="sans-serif" font-size="11" fill="#666" text-anchor="middle">Y轴(高度)平行垂直，X和Z轴汇聚</text>
  </g>
  <g transform="translate(600, 10)">
    <rect x="0" y="0" width="270" height="260" rx="5" fill="#fcfcfc" stroke="#dddddd" stroke-width="1.5" />
    <text x="135" y="30" font-family="sans-serif" font-size="14" font-weight="bold" fill="#333" text-anchor="middle">三点透视 (3个灭点)</text>
    <line x1="10" y1="160" x2="260" y2="160" stroke="#cccccc" stroke-dasharray="3,3" stroke-width="1" />
    <circle cx="20" cy="160" r="4" fill="#ff4d4f" />
    <circle cx="250" cy="160" r="4" fill="#ff4d4f" />
    <circle cx="135" cy="45" r="4" fill="#ff4d4f" />
    <text x="25" y="152" font-family="sans-serif" font-size="10" fill="#ff4d4f" font-weight="bold">VP1</text>
    <text x="245" y="152" font-family="sans-serif" font-size="10" fill="#ff4d4f" font-weight="bold" text-anchor="end">VP2</text>
    <text x="135" y="38" font-family="sans-serif" font-size="10" fill="#ff4d4f" font-weight="bold" text-anchor="middle">VP3</text>
    <line x1="135" y1="110" x2="115" y2="200" stroke="#333" stroke-width="2" />
    <line x1="135" y1="110" x2="155" y2="200" stroke="#333" stroke-width="2" />
    <line x1="115" y1="200" x2="155" y2="200" stroke="#333" stroke-width="1.5" />
    <line x1="90" y1="130" x2="80" y2="190" stroke="#999" stroke-width="1" />
    <line x1="180" y1="130" x2="190" y2="190" stroke="#999" stroke-width="1" />
    <line x1="135" y1="110" x2="90" y2="130" stroke="#333" stroke-width="1.5" />
    <line x1="135" y1="110" x2="180" y2="130" stroke="#333" stroke-width="1.5" />
    <line x1="115" y1="200" x2="80" y2="190" stroke="#333" stroke-width="1.5" />
    <line x1="155" y1="200" x2="190" y2="190" stroke="#333" stroke-width="1.5" />
    <line x1="115" y1="200" x2="135" y2="45" stroke="#ff4d4f" stroke-dasharray="2,2" stroke-width="1" />
    <line x1="155" y1="200" x2="135" y2="45" stroke="#ff4d4f" stroke-dasharray="2,2" stroke-width="1" />
    <line x1="90" y1="130" x2="20" y2="160" stroke="#ff4d4f" stroke-dasharray="2,2" stroke-width="1" />
    <line x1="180" y1="130" x2="250" y2="160" stroke="#ff4d4f" stroke-dasharray="2,2" stroke-width="1" />
    <text x="135" y="245" font-family="sans-serif" font-size="11" fill="#666" text-anchor="middle">X、Y、Z轴均不平行，分别汇聚</text>
  </g>
</svg>
</div>

---

## 五、 OpenGL 中的观察与投影函数

* `gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz)`：设置观察坐标系（相机位置、朝向和头顶方向向量）。
* `glOrtho(left, right, bottom, top, near, far)`：定义一个对称平行的立方体视锥体裁剪区。
* `glFrustum(left, right, bottom, top, near, far)`：定义一个透视投影的梯形截头体。
* `gluPerspective(fovy, aspect, zNear, zFar)`：通过垂直张角 `fovy`、宽高比 `aspect` 快速设置对称透视投影。

---

# 第 6 章 三维造型

* **三维造型表示方法对比**：

  - **线框模型 (Wireframe Model)**：仅通过顶点和棱边表达物体轮廓。数据简单，但无法表达表面及内部属性，存在二义性漏洞。
  - **表面模型 (Surface Model)**：利用边线组成的网格面（如多边形面片）来模拟物体的外部边界。支持消隐和着色，但内部不含实体信息。
  - **实体模型 (Solid Model)**：不仅表达物体的三维空间轮廓，还能识别物体内部和外部空间，可计算体积、重心等物理量。
* **实体表示的常用造型方法**：

  - **多边形网格 (Polygon Mesh)**：最常用的离散边界表示法，便于 GPU 并行硬件加速。
  - **参数曲线/曲面**：使用 Bézier 曲面、B 样条（B-Spline）、NURBS 曲面实现极高精度的非均匀几何曲面建模。
  - **空间细分法——八叉树 (Octree)**：
    - *原理*：将一个三维空间立方体不断递归均分为 8 个子块。
    - *属性标志*：子块节点状态分为“空 (Empty)”、“满 (Full)”和“混合 (Mixed)”。若为混合节点则继续递归剖分，直至达到精度限制。
    - *应用*：适合体素渲染与快速的碰撞检测。
* **构造方法 (CSG & Sweep)**：

  - **构造实体几何法 (Constructive Solid Geometry, CSG)**：
    - *原理*：通过基础实体基元（如立方体、球体、圆柱体）经过逻辑布尔集合运算（并 $\cup$、交 $\cap$、差 $-$）来生成复杂模型。
    - *数据结构*：表示为一棵二叉树，叶子节点为基本体素，非叶子节点为布尔算子。
  - **扫描表示法 (Sweep Representation)**：
    - 将一个二维封闭平面图形沿空间的一条轨迹移动而生成三维实体的几何表示法。
    - 包括拉伸扫描（Translational Sweep）和旋转扫描（Rotational Sweep）。
* **非规则对象的表示方法**：

  - **分形几何 (Fractal Geometry)**：用于模拟自然界中具有自相似特征的粗糙几何体，如海岸线、云朵、山脉。
  - **形状语法 (Shape Grammar)**：利用规则递推的生成文法建立几何模型。
  - **粒子系统 (Particle System)**：通过管理成千上万个生命周期有限的微小运动点（粒子）来模拟流体、火焰、烟雾、爆炸等无法用规则边界表示的模糊对象。

---

# 第 7 章 真实感图形技术

## 一、 消隐技术 (Hidden Surface Removal, 隐藏面消除)

* **概念**：判定并剔除在当前视点下被其他遮挡物遮挡的不可见线段或面片。
* **消隐算法分类与对比**：
  * **按空间操作域分类**：
    * **对象空间算法 (Object-space algorithms)**：在三维世界坐标系下比较物体之间的相对几何关系。其算法复杂度与场景中多边形数量的平方相关 $O(n^2)$。适用于精度要求极高的线框消隐。
    * **图像空间算法 (Image-space algorithms)**：在二维投影平面的像素级别上逐像素判断并比较各个物体的深度值。其算法复杂度通常为 $O(n \cdot p)$，其中 $n$ 是多边形数量，$p$ 为屏幕总像素数。这是现代实时图形学（如 GPU 渲染）中最主流的消隐策略。

  * **常用消隐算法对比表 (考点指导：哪种场景用哪个更好)**：

    | 消隐算法 | 空间域 | 最优适用场景 | 主要局限性 / 缺点 |
    | :--- | :--- | :--- | :--- |
    | **深度缓存 (Z-Buffer)** | 图像空间 | 动态场景、极其复杂的 3D 场景，硬件 GPU 加速的实时渲染。 | 内存开销大（与屏幕分辨率成正比）；可能产生深度冲突 (Z-Fighting)；无法直接处理半透明混合。 |
    | **画家算法 (Painter)** | 图像空间 | 静态场景、多边形数量少且无穿插的场景；软件渲染器中对半透明物体进行从后往前渲染。 | 排序开销大 $O(n \log n)$；当多边形发生循环重叠或相互穿插时，必须进行昂贵的多边形分割。 |
    | **扫描线消隐 (Scan-Line)** | 图像空间 | 将消隐与多边形光栅化紧密结合的场景。能极大减少每像素的深度计算。 | 数据结构设计极度复杂（需要维护活动边表和活动多边形表）；难以用现代硬件高并行处理。 |
    | **光线投射 (Ray-Casting)** | 图像空间 | 静态、非实时的高质量离线渲染；小体积渲染。 | 对屏幕上每个像素都需要做光线与几何体的求交，计算开销极其庞大。 |
    | **背面剔除 (Back-Face)** | 对象空间 | 闭合凸体模型的消隐预处理（可以直接作为第一步初筛剔除约 50% 的多边形）。 | 仅能剔除朝向背对相机的表面，对相互遮挡的凹体或多体场景无效，必须配合其他消隐算法。 |

---

### 1. 深度缓存器 (Z-Buffer) 算法 (图像空间消隐)

* **核心组成**：需要两个与屏幕分辨率大小完全相同的二维数据缓存：
  - **帧缓存 (Frame Buffer / Color Buffer)**：记录当前像素点的 RGB 颜色。
  - **深度缓存 (Depth Buffer / Z-Buffer)**：记录当前像素点所关联的最靠近视点的物体深度 $Z$ 值。

<div align="center">
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 400" width="100%" height="100%" style="background-color: #ffffff; max-width: 700px; display: block; margin: auto;">
  <defs>
    <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M 0 0 L 10 5 L 0 10 z" fill="#333333" />
    </marker>
  </defs>
  <text x="200" y="30" style="font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; font-size: 16px; font-weight: bold; fill: #111111; text-anchor: middle;">3D 场景空间 (视点看向物体)</text>
  <circle cx="50" cy="200" r="10" style="fill: #333333;" />
  <path d="M 50 190 L 30 200 L 50 210 Z" style="fill: #333333;" />
  <text x="50" y="175" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #333333; text-anchor: middle;">Camera (视点)</text>
  <line x1="50" y1="200" x2="350" y2="100" style="stroke: #cccccc; stroke-width: 1; stroke-dasharray: 4,4;" />
  <line x1="50" y1="200" x2="350" y2="300" style="stroke: #cccccc; stroke-width: 1; stroke-dasharray: 4,4;" />
  <polygon points="180,120 250,220 160,250" style="fill: #f44336; fill-opacity: 0.8; stroke: #d32f2f; stroke-width: 1.5;" />
  <text x="195" y="195" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #ffffff;">红三角形 (z=0.3)</text>
  <polygon points="230,100 320,180 240,260" style="fill: #2196f3; fill-opacity: 0.6; stroke: #1976d2; stroke-width: 1.5;" />
  <text x="270" y="165" style="font-family: Arial; font-size: 12px; font-weight: bold; fill: #ffffff;">蓝三角形 (z=0.6)</text>
  <path d="M 230,175 L 200,80" style="stroke: #333333; stroke-width: 1; marker-end: url(#arrow);" />
  <text x="200" y="70" style="font-family: Arial; font-size: 11px; fill: #333333; text-anchor: middle;">遮挡发生处 (红遮挡蓝)</text>
  <line x1="400" y1="20" x2="400" y2="380" style="stroke: #dddddd; stroke-width: 2;" />
  <text x="600" y="30" style="font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; font-size: 16px; font-weight: bold; fill: #111111; text-anchor: middle;">帧缓存与深度缓存渲染结果</text>
  <g transform="translate(480, 80)">
    <rect x="0" y="0" width="40" height="40" style="fill: #ffffff; stroke: #e0e0e0;" /><text x="20" y="25" style="font-family: Arial; font-size: 10px; fill: #888; text-anchor: middle;">1.0</text>
    <rect x="40" y="0" width="40" height="40" style="fill: #ffffff; stroke: #e0e0e0;" /><text x="60" y="25" style="font-family: Arial; font-size: 10px; fill: #888; text-anchor: middle;">1.0</text>
    <rect x="80" y="0" width="40" height="40" style="fill: #2196f3; fill-opacity: 0.6; stroke: #1976d2;" /><text x="100" y="25" style="font-family: Arial; font-size: 10px; fill: #fff; text-anchor: middle;">0.6</text>
    <rect x="120" y="0" width="40" height="40" style="fill: #ffffff; stroke: #e0e0e0;" /><text x="140" y="25" style="font-family: Arial; font-size: 10px; fill: #888; text-anchor: middle;">1.0</text>
    <rect x="0" y="40" width="40" height="40" style="fill: #f44336; fill-opacity: 0.8; stroke: #d32f2f;" /><text x="20" y="65" style="font-family: Arial; font-size: 10px; fill: #fff; text-anchor: middle;">0.3</text>
    <rect x="40" y="40" width="40" height="40" style="fill: #f44336; fill-opacity: 0.8; stroke: #d32f2f;" /><text x="60" y="65" style="font-family: Arial; font-size: 10px; fill: #fff; text-anchor: middle;">0.3</text>
    <rect x="80" y="40" width="40" height="40" style="fill: #f44336; fill-opacity: 0.8; stroke: #d32f2f;" /><text x="100" y="65" style="font-family: Arial; font-size: 10px; fill: #fff; text-anchor: middle;">0.3</text>
    <rect x="120" y="40" width="40" height="40" style="fill: #2196f3; fill-opacity: 0.6; stroke: #1976d2;" /><text x="140" y="65" style="font-family: Arial; font-size: 10px; fill: #fff; text-anchor: middle;">0.6</text>
    <rect x="0" y="80" width="40" height="40" style="fill: #f44336; fill-opacity: 0.8; stroke: #d32f2f;" /><text x="20" y="105" style="font-family: Arial; font-size: 10px; fill: #fff; text-anchor: middle;">0.3</text>
    <rect x="40" y="80" width="40" height="40" style="fill: #f44336; fill-opacity: 0.8; stroke: #d32f2f;" /><text x="60" y="105" style="font-family: Arial; font-size: 10px; fill: #fff; text-anchor: middle;">0.3</text>
    <rect x="80" y="80" width="40" height="40" style="fill: #f44336; fill-opacity: 0.8; stroke: #d32f2f;" /><text x="100" y="105" style="font-family: Arial; font-size: 10px; fill: #fff; text-anchor: middle;">0.3</text>
    <rect x="120" y="80" width="40" height="40" style="fill: #2196f3; fill-opacity: 0.6; stroke: #1976d2;" /><text x="140" y="105" style="font-family: Arial; font-size: 10px; fill: #fff; text-anchor: middle;">0.6</text>
    <rect x="0" y="120" width="40" height="40" style="fill: #ffffff; stroke: #e0e0e0;" /><text x="20" y="145" style="font-family: Arial; font-size: 10px; fill: #888; text-anchor: middle;">1.0</text>
    <rect x="40" y="120" width="40" height="40" style="fill: #f44336; fill-opacity: 0.8; stroke: #d32f2f;" /><text x="60" y="145" style="font-family: Arial; font-size: 10px; fill: #fff; text-anchor: middle;">0.3</text>
    <rect x="80" y="120" width="40" height="40" style="fill: #ffffff; stroke: #e0e0e0;" /><text x="100" y="145" style="font-family: Arial; font-size: 10px; fill: #888; text-anchor: middle;">1.0</text>
    <rect x="120" y="120" width="40" height="40" style="fill: #ffffff; stroke: #e0e0e0;" /><text x="140" y="145" style="font-family: Arial; font-size: 10px; fill: #888; text-anchor: middle;">1.0</text>
    <g transform="translate(-40, 185)">
      <rect x="0" y="0" width="12" height="12" style="fill: #f44336; fill-opacity: 0.8; stroke: #d32f2f;" />
      <text x="18" y="10" style="font-family: Arial; font-size: 11px; fill: #333;">Frame:红 / Depth:0.3</text>
      <rect x="130" y="0" width="12" height="12" style="fill: #2196f3; fill-opacity: 0.6; stroke: #1976d2;" />
      <text x="148" y="10" style="font-family: Arial; font-size: 11px; fill: #333;">Frame:蓝 / Depth:0.6</text>
    </g>
  </g>
  <text x="600" y="320" style="font-family: Arial; font-size: 12px; fill: #e53935; font-weight: bold; text-anchor: middle;">重叠区域 Z-Buffer 更新判定: 0.3 &lt; 0.6 (红覆盖蓝)</text>
</svg>
</div>

* **深度计算的数学原理与公式**：
    假设空间中多边形所在的平面方程为：
    $$Ax + By + Cz + D = 0$$
    由于深度 $z$ 是屏幕坐标 $(x, y)$ 的函数，则在点 $(x, y)$ 处的深度值计算公式为：
    $$z(x, y) = -\frac{Ax + By + D}{C} \quad (C \neq 0)$$
  * **深度递推/增量计算公式 (扫描线算法核心，计算大题必考)**：
    为了避免在每个像素位置都进行高开销的乘除法，可以利用空间的连续性进行增量计算：
    * **沿着水平扫描线向右移动一个像素（$x \to x + 1$）**：
      $$z(x+1, y) = -\frac{A(x+1) + By + D}{C} = z(x, y) - \frac{A}{C}$$
      因此，水平相邻像素的深度递推公式为：
      $$z(x+1, y) = z(x, y) + \Delta z_x, \quad \text{其中 } \Delta z_x = -\frac{A}{C}$$
    * **沿着垂直方向向下移动一行扫描线（$y \to y - 1$）**：
      若在行首的起点 $x$ 的偏移变化量为 $\Delta x$（即在活动边表 AET 中跟随边斜率倒数发生的变化），则：
      $$z(x+\Delta x, y-1) = z(x, y) + \Delta z_y, \quad \text{其中 } \Delta z_y = \frac{-A \cdot \Delta x + B}{C}$$
      特别地，若 $x$ 方向无偏移（$\Delta x = 0$，单纯垂直向下移动），则：
      $$z(x, y-1) = z(x, y) + \frac{B}{C}$$

* **算法计算执行过程**：
  1. 初始化 Z-Buffer 中所有像素的深度值为最大可能值（如 $1.0$），Frame Buffer 初始化为背景色。
  2. 遍历场景中的每一个多边形。
  3. 计算该多边形覆盖的每一个像素点 $(x, y)$ 处的深度值 $z(x, y)$。
  4. 如果该点深度值满足：

     $$
     z(x, y) < \text{DepthBuffer}(x, y)
     $$

     （假设视点在原点，越小越靠近相机），则更新数据：

     $$
     \begin{cases}
     \text{DepthBuffer}(x, y) = z(x, y) \\
     \text{FrameBuffer}(x, y) = \text{Color}_{\text{polygon}}(x, y)
     \end{cases}
     $$
  5. 重复处理，直到全部多边形光栅化完毕。
* **优点**：算法逻辑极简，容易由硬件电路高速实现，不需要对场景内的多边形进行全局深度预排序。

---

### 2. 画家算法 (Painter's Algorithm / 深度排序)

* **核心步骤**：
  1. 将场景中所有的多边形按其最远深度（$z_{\max}$）进行降序排序。
  2. 按照由远及近（Back-to-Front）的顺序依次在帧缓存中绘制每个多边形，较近的图形自动覆盖先前画好的较远的物体。
* **重叠判决冲突与分割**：
  - 当两个多边形的深度范围存在重叠、相交、或循环环绕时，画家算法必须对待绘制的表面进行切割分割，使其转化为互不穿插的独立面片，否则将产生错误的遮挡效果。

---

## 二、 常用颜色模型

* **RGB 颜色模型 (三基色模型)**：
  - 红 (Red)、绿 (Green)、蓝 (Blue) 三色叠加。
  - 属于**相加/加色混合模型**，主要应用在显示器、电视等发光呈像设备上。
* **CMY 颜色模型 (相减模型)**：
  - 青 (Cyan)、品红 (Magenta)、黄 (Yellow) 三色相减。
  - 属于**相减/减色混合模型**，主要应用在彩色印刷、绘图仪等反射光呈像的行业。
  - 与 RGB 之间的基础数学转换关系为：

    $$
    \begin{bmatrix}
    C \\
    M \\
    Y
    \end{bmatrix} =
    \begin{bmatrix}
    1 \\
    1 \\
    1
    \end{bmatrix} -
    \begin{bmatrix}
    R \\
    G \\
    B
    \end{bmatrix}
    $$

---

## 三、 光照模型

### 1. 局部光照模型 (Phong 反射模型)

局部光照模型只考虑光源与物体表面本身的作用，忽略物体与物体之间的间接反射光（即把间接光照强行简化为一个均匀的环境光分量）。

* **标准 Phong 反射模型完整公式**：
  $$I = I_e + I_a + I_d + I_s = E + I_{ambient} K_a + \sum_{j} I_{pj} \left[ K_d (L_j \cdot N) + K_s (R_j \cdot V)^n \right]$$

* **Blinn-Phong 改进反射模型完整公式 (使用半角向量代替反射向量)**：
  $$I = I_e + I_a + I_d + I_s = E + I_{ambient} K_a + \sum_{j} I_{pj} \left[ K_d (L_j \cdot N) + K_s (H_j \cdot N)^n \right]$$

*(注：上述公式中的 $\sum_j$ 代表对场景中所有发射光的点光源进行光强累加，其中每个分量的详细定义如下)*

* **公式中各分量及物理量含义详解**：
  * **$I_e$（自发光分量 / Emissive Component）**：
    * **英文全称**: Emissive Light / Self-Emission
    * **子公式**: $I_e = E$ （通常为一个表征自发光强度的常数）
    * **物理意义**: 描述物体自身发光的光照表现。它完全不依赖于外部光源和材质的反射属性。如果物体本身并非光源，则此项为 0。
  * **$I_a$（环境光分量 / Ambient Component）**：
    * **英文全称**: Ambient Light
    * **子公式**: $I_a = I_{ambient} \cdot K_a$
    * **物理意义**: 模拟光线在环境中经过无数次漫反射后，达到完全均匀散射状态的无方向性背景光照。它用于均匀照亮场景中的所有物体（包括背光面），防止背光处出现绝对的纯黑。其中 $I_{ambient}$ 为环境光强，$K_a$ 为材质的环境光反射系数。
  * **$I_d$（漫反射分量 / Diffuse Component）**：
    * **英文全称**: Diffuse Reflection
    * **子公式**: $I_d = I_{light} \cdot K_d \cdot (L \cdot N) = I_{light} \cdot K_d \cdot \cos\theta$
    * **物理意义**: 描述粗糙表面向空间各个方向均匀散射的光照表现，遵循**朗伯余弦定律 (Lambert's Cosine Law)**。漫反射的光强与观察者的视线方向无关，仅取决于光源入射角（即光源方向 $L$ 与表面法线 $N$ 的夹角 $\theta$ 的余弦值）。当夹角 $\theta > 90^\circ$（即 $L \cdot N < 0$）时，漫反射分量计算结果为 0。其中 $I_{light}$ 为光源光强，$K_d$ 为材质的漫反射系数。
  * **$I_s$（镜面反射分量 / Specular Component）**：
    * **英文全称**: Specular Reflection
    * **子公式**:
      * **标准 Phong 模型**: $I_s = I_{light} \cdot K_s \cdot (R \cdot V)^n = I_{light} \cdot K_s \cdot \cos^n\alpha$ （$\alpha$ 为反射光向量 $R$ 与视线向量 $V$ 的夹角）
      * **Blinn-Phong 模型**: $I_s = I_{light} \cdot K_s \cdot (H \cdot N)^n = I_{light} \cdot K_s \cdot \cos^n\beta$ （$\beta$ 为半角向量 $H$ 与法向量 $N$ 的夹角）
    * **物理意义**: 描述光滑表面对光线的方向性反射，从而在特定观察视角下产生高亮光斑（高光，Specular Highlight）。其中 $K_s$ 为镜面反射系数，$n$ 为高光反射指数（Shininess，控制高光的集中度和粗糙度。$n$ 越大，表面越光滑，高光光斑越小而越亮）。
  * **关键向量定义**（参见下方示意图）：
    * $N$：物体表面交点处的**单位法向量 (Unit Normal Vector)**。
    * $L$：从物体表面交点指向点光源的**单位入射光向量 (Unit Light Vector)**。
    * $V$：从物体表面交点指向相机/眼睛的**单位视线向量 (Unit View Vector)**。
    * $R$：入射光线 $L$ 关于法线 $N$ 的**单位反射向量 (Unit Reflection Vector)**，计算公式为 $R = 2(L \cdot N)N - L$。
    * $H$：入射光向量 $L$ 和视线向量 $V$ 的**单位半角向量 (Unit Halfway Vector)**，计算公式为：
      $$H = \frac{L + V}{\|L + V\|}$$

<div align="center">
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 320 180" width="100%" style="background-color: #ffffff; max-width: 350px; display: block; margin: auto;">
  <defs>
    <marker id="arrow-vector" viewBox="0 0 10 10" refX="8" refY="5" markerWidth="5" markerHeight="5" orient="auto-start-reverse">
      <path d="M 0 1.5 L 8 5 L 0 8.5 z" fill="#333" />
    </marker>
    <marker id="arrow-vector-h" viewBox="0 0 10 10" refX="8" refY="5" markerWidth="5" markerHeight="5" orient="auto-start-reverse">
      <path d="M 0 1.5 L 8 5 L 0 8.5 z" fill="#409EFF" />
    </marker>
  </defs>
  <!-- Surface line -->
  <line x1="20" y1="150" x2="300" y2="150" stroke="#666" stroke-width="2" />
  <rect x="20" y="150" width="280" height="20" fill="rgba(240,240,240,0.5)" />
  <!-- Surface point P -->
  <circle cx="150" cy="150" r="3" fill="#333" />
  <text x="145" y="165" font-family="sans-serif" font-size="11" fill="#333">P</text>
  <!-- Normal Vector N -->
  <line x1="150" y1="150" x2="150" y2="40" stroke="#333" stroke-width="2" marker-end="url(#arrow-vector)" />
  <text x="145" y="28" font-family="sans-serif" font-size="12" font-weight="bold" fill="#333">N</text>
  <!-- Light Vector L -->
  <line x1="150" y1="150" x2="70" y2="70" stroke="#333" stroke-width="2" marker-end="url(#arrow-vector)" />
  <text x="55" y="68" font-family="sans-serif" font-size="12" font-weight="bold" fill="#333">L</text>
  <!-- Reflection Vector R -->
  <line x1="150" y1="150" x2="230" y2="70" stroke="#999" stroke-width="1.5" stroke-dasharray="3 2" marker-end="url(#arrow-vector)" />
  <text x="235" y="68" font-family="sans-serif" font-size="12" fill="#999">R</text>
  <!-- View Vector V -->
  <line x1="150" y1="150" x2="200" y2="55" stroke="#333" stroke-width="2" marker-end="url(#arrow-vector)" />
  <text x="205" y="50" font-family="sans-serif" font-size="12" font-weight="bold" fill="#333">V</text>
  <!-- Halfway Vector H -->
  <line x1="150" y1="150" x2="172" y2="48" stroke="#409EFF" stroke-width="2" marker-end="url(#arrow-vector-h)" />
  <text x="178" y="42" font-family="sans-serif" font-size="12" font-weight="bold" fill="#409EFF">H</text>
  <!-- Surface Normal Arc -->
  <path d="M 130 150 A 20 20 0 0 1 150 130" fill="none" stroke="#ddd" stroke-width="1" />
</svg>
</div>

* **公式中各分量及物理量含义**：
  - $I$：计算出的表面最终合成反射光强度。
  - $I_a$：环境光（Ambient Light）分量。
  - $K_a$：物体表面的环境光反射系数（$0 \le K_a \le 1$）。
  - $I_p$（即 $I_{pj}$）：点光源入射光强。
  - $K_d$：漫反射（Diffuse Reflection）系数。
  - $L$：从物体表面交点指向点光源的**单位方向向量**。
  - $N$：物体表面的**单位法向量**。
  - $K_s$：镜面反射（Specular Reflection）系数。
  - $H$：半角向量（Half-way Vector），是入射光向量 $L$ 和视线向量 $V$ 的中间平分单位向量，计算方式为：

    $$
    H = \frac{L + V}{\|L + V\|}
    $$
  - $n$：高光反射指数（Shininess），控制镜面反射光束的集中程度。$n$ 越大，表面越光滑，高光区域越小。

---

### 2. Whitted 整体光照模型

整体光照模型在此基础上引入了光线在场景中不断折射、镜面反射产生的间接光强。

$$
I = I_a K_a + I_p K_d (L \cdot N) + I_p K_s (H \cdot N)^n + I_t K_t' + I_s K_s'
$$

* **参数含义**：
  - $I_t$：经由其他透明介质折射/透射（Transmission）传入本表面的间接光强；$K_t'$ 为对应的折射贡献参数。
  - $I_s$：经由其他镜面反射（Reflection）照进本表面的间接光强；$K_s'$ 为对应的镜面间接反射贡献参数。

---

## 四、 三种多边形着色 (Shading) 算法

在计算多边形表面各处色彩时，有如下三种插值方案：

<div align="center">
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 250" width="100%" height="100%" style="background-color: #ffffff; max-width: 650px; display: block; margin: auto;">
  <defs>
    <radialGradient id="gouraud-grad" cx="40%" cy="40%" r="60%" fx="30%" fy="30%">
      <stop offset="0%" stop-color="#a0c0f0" />
      <stop offset="50%" stop-color="#4a70a0" />
      <stop offset="100%" stop-color="#1a2540" />
    </radialGradient>
    <radialGradient id="phong-diffuse" cx="40%" cy="40%" r="60%" fx="30%" fy="30%">
      <stop offset="0%" stop-color="#70a0e0" />
      <stop offset="70%" stop-color="#2c5080" />
      <stop offset="100%" stop-color="#0f1830" />
    </radialGradient>
    <radialGradient id="phong-specular" cx="50%" cy="50%" r="50%">
      <stop offset="0%" stop-color="#ffffff" stop-opacity="1" />
      <stop offset="30%" stop-color="#ffffff" stop-opacity="0.8" />
      <stop offset="100%" stop-color="#ffffff" stop-opacity="0" />
    </radialGradient>
  </defs>
  <g transform="translate(100, 110)">
    <polygon points="0,-70 45,-50 0,0" style="fill: #7aa0d0; stroke: #3f5d80; stroke-width: 0.5;" />
    <polygon points="45,-50 70,0 0,0" style="fill: #5a80b0; stroke: #3f5d80; stroke-width: 0.5;" />
    <polygon points="70,0 45,50 0,0" style="fill: #3a5f8f; stroke: #3f5d80; stroke-width: 0.5;" />
    <polygon points="45,50 0,70 0,0" style="fill: #254066; stroke: #3f5d80; stroke-width: 0.5;" />
    <polygon points="0,70 -45,50 0,0" style="fill: #152540; stroke: #3f5d80; stroke-width: 0.5;" />
    <polygon points="-45,50 -70,0 0,0" style="fill: #1c3050; stroke: #3f5d80; stroke-width: 0.5;" />
    <polygon points="-70,0 -45,-50 0,0" style="fill: #3c5880; stroke: #3f5d80; stroke-width: 0.5;" />
    <polygon points="-45,-50 0,-70 0,0" style="fill: #5c7ca8; stroke: #3f5d80; stroke-width: 0.5;" />
    <circle cx="0" cy="0" r="70" style="fill: none; stroke: #333333; stroke-width: 1.5;" />
    <text x="0" y="95" style="font-family: Arial; font-size: 13px; font-weight: bold; fill: #333; text-anchor: middle;">Flat Shading (恒定着色)</text>
    <text x="0" y="112" style="font-family: Arial; font-size: 11px; fill: #666; text-anchor: middle;">逐多边形计算颜色，呈块状</text>
  </g>
  <g transform="translate(350, 110)">
    <circle cx="0" cy="0" r="70" fill="url(#gouraud-grad)" stroke="#333333" stroke-width="1.5" />
    <text x="0" y="95" style="font-family: Arial; font-size: 13px; font-weight: bold; fill: #333; text-anchor: middle;">Gouraud Shading (顶点插值)</text>
    <text x="0" y="112" style="font-family: Arial; font-size: 11px; fill: #666; text-anchor: middle;">逐顶点计算光照，颜色线性插值</text>
  </g>
  <g transform="translate(600, 110)">
    <circle cx="0" cy="0" r="70" fill="url(#phong-diffuse)" stroke="#333333" stroke-width="1.5" />
    <ellipse cx="-15" cy="-15" rx="20" ry="20" fill="url(#phong-specular)" transform="rotate(-15 -15 -15)" />
    <text x="0" y="95" style="font-family: Arial; font-size: 13px; font-weight: bold; fill: #333; text-anchor: middle;">Phong Shading (法向插值)</text>
    <text x="0" y="112" style="font-family: Arial; font-size: 11px; fill: #666; text-anchor: middle;">逐像素插值法向并计算光照</text>
  </g>
</svg>
</div>

<div align="center">
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 320" width="100%" height="100%" style="background-color: #ffffff; max-width: 700px; display: block; margin: auto;">
  <g transform="translate(10, 10)">
    <rect x="0" y="0" width="370" height="295" rx="5" fill="#fcfcfc" stroke="#dddddd" stroke-width="1.5" />
    <text x="185" y="25" font-family="sans-serif" font-size="14" font-weight="bold" fill="#333" text-anchor="middle">Gouraud Shading (双线性光强插值)</text>
    <polygon points="185,50 85,210 285,210" fill="none" stroke="#444444" stroke-width="1.5" />
    <circle cx="185" cy="50" r="5" fill="#ff4d4f" />
    <text x="185" y="42" font-family="sans-serif" font-size="11" font-weight="bold" fill="#ff4d4f" text-anchor="middle">V1 (颜色 I1)</text>
    <circle cx="85" cy="210" r="5" fill="#52c41a" />
    <text x="65" y="225" font-family="sans-serif" font-size="11" font-weight="bold" fill="#52c41a">V2 (颜色 I2)</text>
    <circle cx="285" cy="210" r="5" fill="#1890ff" />
    <text x="305" y="225" font-family="sans-serif" font-size="11" font-weight="bold" fill="#1890ff" text-anchor="end">V3 (颜色 I3)</text>
    <line x1="50" y1="130" x2="320" y2="130" stroke="#999999" stroke-dasharray="4,4" stroke-width="1" />
    <text x="325" y="133" font-family="sans-serif" font-size="10" fill="#666">扫描线</text>
    <circle cx="135" cy="130" r="4" fill="#75c236" />
    <text x="110" y="125" font-family="sans-serif" font-size="10" fill="#555">A (插值颜色 Ia)</text>
    <circle cx="235" cy="130" r="4" fill="#8cb2a6" />
    <text x="260" y="125" font-family="sans-serif" font-size="10" fill="#555">B (插值颜色 Ib)</text>
    <rect x="180" y="127" width="8" height="6" fill="#fadb14" />
    <circle cx="184" cy="130" r="2" fill="#d48806" />
    <text x="184" y="120" font-family="sans-serif" font-size="9" fill="#d48806" font-weight="bold" text-anchor="middle">像素 P (插值颜色 Ip)</text>
    <text x="185" y="255" font-family="sans-serif" font-size="11" fill="#666" text-anchor="middle">插值顺序：顶点颜色 → 边界交点颜色 → 内部像素颜色</text>
    <text x="185" y="275" font-family="sans-serif" font-size="10" fill="#ff4d4f" font-weight="bold" text-anchor="middle">缺点：无法产生正确镜面高光 (产生“高光失真”)</text>
  </g>
  <g transform="translate(410, 10)">
    <rect x="0" y="0" width="370" height="295" rx="5" fill="#fcfcfc" stroke="#dddddd" stroke-width="1.5" />
    <text x="185" y="25" font-family="sans-serif" font-size="14" font-weight="bold" fill="#333" text-anchor="middle">Phong Shading (双线性法向插值)</text>
    <polygon points="185,50 85,210 285,210" fill="none" stroke="#444444" stroke-width="1.5" />
    <line x1="185" y1="50" x2="185" y2="15" stroke="#333333" stroke-width="1.5" />
    <polygon points="185,15 182,22 188,22" fill="#333333" />
    <text x="185" y="10" font-family="sans-serif" font-size="10" fill="#333" text-anchor="middle">N1</text>
    <line x1="85" y1="210" x2="60" y2="190" stroke="#333333" stroke-width="1.5" />
    <polygon points="60,190 67,192 63,197" fill="#333333" />
    <text x="50" y="185" font-family="sans-serif" font-size="10" fill="#333">N2</text>
    <line x1="285" y1="210" x2="310" y2="190" stroke="#333333" stroke-width="1.5" />
    <polygon points="310,190 307,197 303,192" fill="#333333" />
    <text x="315" y="185" font-family="sans-serif" font-size="10" fill="#333">N3</text>
    <line x1="50" y1="130" x2="320" y2="130" stroke="#999999" stroke-dasharray="4,4" stroke-width="1" />
    <text x="325" y="133" font-family="sans-serif" font-size="10" fill="#666">扫描线</text>
    <line x1="135" y1="130" x2="115" y2="110" stroke="#333333" stroke-width="1" />
    <polygon points="115,110 121,112 118,116" fill="#333333" />
    <text x="110" y="105" font-family="sans-serif" font-size="9" fill="#555">Na</text>
    <line x1="235" y1="130" x2="245" y2="105" stroke="#333333" stroke-width="1" />
    <polygon points="245,105 240,111 246,113" fill="#333333" />
    <text x="248" y="100" font-family="sans-serif" font-size="9" fill="#555">Nb</text>
    <rect x="180" y="127" width="8" height="6" fill="#ff9900" />
    <line x1="184" y1="130" x2="184" y2="100" stroke="#ff4d4f" stroke-width="1.5" />
    <polygon points="184,100 181,107 187,107" fill="#ff4d4f" />
    <text x="184" y="94" font-family="sans-serif" font-size="9" fill="#ff4d4f" font-weight="bold" text-anchor="middle">Np (插值法线)</text>
    <text x="185" y="255" font-family="sans-serif" font-size="11" fill="#666" text-anchor="middle">插值顺序：顶点法线 → 边界交点法线 → 像素法线 Np</text>
    <text x="185" y="275" font-family="sans-serif" font-size="10" fill="#1890ff" font-weight="bold" text-anchor="middle">优点：在像素 P 处用 Np 计算光照，完美呈现高光</text>
  </g>
</svg>
</div>


### 1. Flat Shading (恒定着色)

* **执行步骤**：
  - 对于给定的多边形，只取其中一个顶点（或多边形中心点）的法向量，结合光照模型算出一个统一的颜色。整个多边形内所有像素均填充此颜色。
* **优缺点**：
  - *优点*：计算速度极快，计算开销极低。
  - *缺点*：物体表面呈块状拼接，会产生由于生理视觉限制引起的“马赫带 (Mach Band)”边界效应，过渡极不自然。

---

### 2. Gouraud Shading (双线性光强插值)

* **执行步骤**：

  1. 计算多边形各个顶点的平均法向量。
  2. 根据光照模型，利用顶点的法向量算出各个**顶点处的颜色光强值**。
  3. 在多边形扫描转换光栅化时，利用顶点光强沿扫描线进行**双线性插值**，算出多边形内部任意像素的颜色。
* **插值计算公式**：
  如图，对于扫描线与多边形边相交得到的端点 $P$，若多边形两顶点为 $A, B$，其 $y$ 坐标分别为 $y_A, y_B$，对应的颜色光强为 $I_A, I_B$：

  $$
  I_P = \frac{y_B - y_P}{y_B - y_A} I_A + \frac{y_P - y_A}{y_B - y_A} I_B
  $$
* **优缺点**：

  - *优点*：消除了多边形拼接处的颜色突变，物体外观平滑连续。
  - *缺点*：无法完美呈现细小的高光区域（镜面反射）。若高光区域处于多边形内部而非顶点上，插值后会被完全抹平。同时在光强导数变化剧烈处仍会有较淡的马赫带。

---

### 3. Phong Shading (双线性法向插值)

* **执行步骤**：

  1. 计算多边形各个顶点的法向量。
  2. 在扫描转换过程中，不是插值颜色，而是利用顶点的法向量进行**双线性插值**，求出每个像素网格点对应的**法向量**。
  3. 对每个像素插值出的法向量进行**归一化处理**。
  4. 利用该像素的法向量和光照模型，**逐像素**重新计算其颜色值。
* **插值计算公式**：
  若已知多边形顶点 $A, B$ 的法向量为 $N_A, N_B$，相交处像素点 $P$ 的法向量 $N_P$ 计算为：

  $$
  N_P = \text{normalize}\left( \frac{y_B - y_P}{y_B - y_A} N_A + \frac{y_P - y_A}{y_B - y_A} N_B \right)
  $$
* **优缺点**：

  - *优点*：能够极其准确地计算并绘制镜面高光反射，高光区边缘清晰细腻，画面最为逼真。
  - *缺点*：因为需要对每一个像素单独计算光照方程，包含大量的求交和法向量归一化开销，计算负荷远大于 Gouraud 着色。

---

## 五、 简单透明与阴影的处理方式

* **简单透明处理**：

  - 采用插值混色公式。设透明物体的光强为 $I_{\text{obj}}$，其后方背景的折射光强为 $I_{\text{bg}}$，定义透光率系数为 $K_t$（$0 \le K_t \le 1$），则该像素点的最终合成光强为：

    $$
    I = (1 - K_t) I_{\text{obj}} + K_t I_{\text{bg}}
    $$
* **阴影的处理方式**：

  - **阴影图法 (Shadow Mapping)**：
    - 第一遍渲染：将视点移至光源处，渲染场景深度图，生成 Z-Buffer（记录哪些点对光源可见）。
    - 第二遍渲染：以正常相机视角渲染，将待绘制点的坐标转换回光源视角，对比其深度。若深度值大于第一遍记录的值，说明被挡住，处于阴影中。
  - **阴影椎体法 (Shadow Volume)**：根据光源与遮挡物几何体生成伸展的退化几何体（锥体），对射线穿过的次数进行统计（利用模板缓存计数），奇偶法确定是否在阴影内。

---

## 六、 光线跟踪算法 (Ray Tracing)

* **基本思想**：
  - 从相机（视点）出发，向屏幕上的每一个像素发射一条初始射线（视线/Primary Ray）。
  - 计算射线与场景中物体的最近交点。
  - 在交点处发射**次级光线**（Secondary Rays）：
    - *反射光线*：顺着镜面反射方向追踪，计算周围物体的反射贡献。
    - *折射光线*：若物体为半透明，顺着折射方向穿过物体继续追踪。
    - *阴影测试光线 (Shadow Ray)*：从交点连线指向各点光源。若途中被遮挡，则该光源对该点无直接贡献（该点处于阴影中）。
* **跟踪的终止条件**：
  1. 射线没有碰撞到场景中的任何物体（逃逸出场景边界，射入背景）。
  2. 射线的反射/折射次数达到了预设的最大递归追踪深度（Depth Limit）。
  3. 射线累积的能量/强度贡献值已经衰减到了指定的阈值下限（衰减极小，可忽略不计）。

---

## 七、 纹理映射 (Texture Mapping)

* **概念**：将二维的图样（图像）粘贴到三维物体的几何表面上，以在不增加物体网格面数（几何复杂度）的前提下，实现极高细节的复杂图样外观效果。
* **纹理映射的分类**：
  1. **颜色纹理映射 (Color Texture Mapping)**：最基本的方式。将二维图片的 RGB 像素值映射为物体的漫反射系数，改变表面外观颜色。
  2. **凹凸映射 (Bump Mapping / Normal Mapping)**：不改变几何体表面高度，而是利用纹理扰动多边形表面的**法向量方向**，从而改变局部光照明暗，创造假的小凹凸、划痕等立体质感。
  3. **环境映射 (Environment Mapping / Reflection Mapping)**：将周围环境绘制在一张立方体或球形贴图上。计算物体的反射光线去采样贴图，用以模拟高反射率物体（如镜子、光滑金属）的镜面反射场景。
  4. **三维/空间纹理 (Solid Texture)**：将纹理定义为三维空间坐标 $(x, y, z)$ 的函数（如木纹、大理石纹），物体任意位置的颜色直接由其空间三维坐标决定，适合雕刻实体模型。

---

# OpenGL 专项高频考点辨析 (选择/程序设计题必考)

在期末考试中，通常包含 5 道关于 OpenGL 核心 API 与矩阵变换的代码分析选择题（占 10 分）。以下为核心高频考点解析：

## 一、 复合变换的代码书写顺序与顶点实际作用顺序

* **核心理论：活动局部坐标系模式**
  - OpenGL 固定管线在内部采用的是**活动局部坐标系模式**，矩阵运算采用**右乘模式**。
  - 每一个矩阵变换函数都会将其相应的矩阵右乘到当前的矩阵堆栈顶部。
* **书写与生效规律**：
  - **代码书写顺序**（从上到下）：
    ```cpp
    glLoadIdentity();
    glRotatef(30.0f, 0.0f, 0.0f, 1.0f);   // 旋转 A
    glTranslatef(2.0f, 0.0f, 0.0f);      // 平移 B
    glScalef(1.5f, 1.5f, 1.0f);          // 缩放 C
    drawPolygon();                       // 绘制几何体
    ```
  - **矩阵相乘顺序**（从左到右）：

    $$
    M = I \cdot R_A \cdot T_B \cdot S_C
    $$

  - **几何物体顶点的实际生效顺序**：**从下到上（从右向左）**。
    也就是：**先进行缩放 C $\to$ 再进行平移 B $\to$ 最后进行旋转 A**。

  > [!WARNING]
  > **避坑警示**：考试选择题往往会给出一段 OpenGL 几何变换的顺序代码，问其等价的几何操作流程。请记住核心规则：**代码里写在下方的变换最先作用于物体顶点，写在最上方的变换最后作用。**

---

## 二、 三维观察与投影核心函数解析

在 OpenGL 渲染流程中，视图与投影变换是通过以下几个关键函数来定义视景体（Viewing Volume）的：

### 1. `gluLookAt()` —— 设置相机视点变换
* **函数原型**：
  ```cpp
  void gluLookAt(
      GLdouble eyex, GLdouble eyey, GLdouble eyez,        // 视点/相机位置 (Eye)
      GLdouble centerx, GLdouble centery, GLdouble centerz, // 观察参考点/焦点 (Center)
      GLdouble upx, GLdouble upy, GLdouble upz             // 相机向上向量 (Up)
  );
  ```
* **核心作用**：
  - 定义相机（视点）在三维世界空间的位置和指向方向，把世界坐标系 (WC) 中的物体坐标转换到观察参考坐标系 (VC)。
  - `up` 向量决定了相机的倾斜角度（如 $(0,1,0)$ 表示相机头顶朝向正 $Y$ 轴）。

---

### 2. `glOrtho()` —— 设置正交（平行）投影
* **函数原型**：
  ```cpp
  void glOrtho(
      GLdouble left, GLdouble right,    // 左右截面 X 坐标限制
      GLdouble bottom, GLdouble top,    // 下上截面 Y 坐标限制
      GLdouble nearVal, GLdouble farVal // 近远截面 Z 距离限制
  );
  ```
* **核心作用**：
  - 定义一个正交（平行）投影的六面体视景体。
  - **特点**：投影线平行，不产生近大远小的透视收缩效果。常用于二维地图、CAD 制图或 UI 界面的绘制。

---

### 3. `gluPerspective()` 与 `glFrustum()` —— 设置透视投影
* **`gluPerspective()`**（通过张角与比例定义）：
  - **函数原型**：
    ```cpp
    void gluPerspective(
        GLdouble fovy,   // 垂直视角（Y方向张角，单位：度）
        GLdouble aspect, // 宽高比（视口的宽除以高）
        GLdouble zNear,  // 近裁剪面到相机的距离（必须为正数，且 > 0）
        GLdouble zFar    // 远裁剪面到相机的距离（必须为正数，且 > 0）
    );
    ```
  - **应用特点**：符合人类日常视觉习惯（近大远小），定义了一个对称的四棱台截头体视景体，最易于设置。
* **`glFrustum()`**（通过截面坐标定义）：
  - **函数原型**：
    ```cpp
    void glFrustum(
        GLdouble left, GLdouble right,
        GLdouble bottom, GLdouble top,
        GLdouble nearVal, GLdouble farVal
    );
    ```
  - **应用特点**：通过直接指定近裁剪面上各边界的坐标来定义视景体，支持设置非对称的斜视透视投影截头体。

---

### 4. `glViewport()` —— 设置视口映射
* **函数原型**：
  ```cpp
  void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
  ```
* **核心作用**：
  - 决定了归一化设备坐标 (NDC) 的 $[-1, 1]$ 范围最终如何映射到屏幕窗口上的物理像素区域（以窗口左下角为原点 $(x, y)$，定义渲染区域的宽和高）。
