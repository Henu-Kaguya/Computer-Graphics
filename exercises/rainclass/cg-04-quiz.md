# 《计算机图形学》雨课堂随堂测试 - CG-4 二维与三维几何变换

---

## 一、 单项选择题

**1. 点 $P$ 的齐次坐标为 $(6, -2, 2)$，其对应的普通坐标是：** `[   ]`

* A. $(6,-2,1)$
* B. $(3,-1,1)$
* C. $(6,-2)$
* D. $(3,-1)$

**2. 将下图所示四边形 $ABCD$ 绕点 $P(5,4)$ 逆时针旋转 $45^\circ$，涉及到三个变换矩阵，则三个矩阵复合的顺序是？** `[   ]`

<div align="center">
  <img src="images/cg_4_q2_body_1.png" width="350" alt="四边形旋转示意图 1"/>
  <img src="images/cg_4_q2_body_2.png" width="350" alt="四边形旋转示意图 2"/>
</div>

* A. $T(-5, -4)R(45^\circ)T(5, 4)$
* B. $R(45^\circ)T(-5, -4)T(5, 4)$
* C. $T(5, 4)R(45^\circ)T(-5, -4)$
* D. $T(5, 4)T(-5, -4)R(45^\circ)$

**3. 将下图所示四边形 $ABCD$ 绕点 $P(5,4)$ 逆时针旋转 $45^\circ$ 的代码是：** `[   ]`

<div align="center">
  <img src="images/cg_4_q3_body.png" width="350" alt="旋转代码对应图"/>
</div>

* A. 
  ```cpp
  glLoadIdentity();
  glTranslatef(5, 4, 0);
  glRotatef(45, 0.0f, 0.0f, 1.0f);
  glTranslatef(-5, -4, 0);
  DrawQuadrangle();
  ```
* B. 
  ```cpp
  glLoadIdentity();
  glTranslatef(-5, -4, 0);
  glRotatef(45, 0.0f, 0.0f, 1.0f);
  glTranslatef(5, 4, 0);
  DrawQuadrangle();
  ```

**4. 如下图所示，欲使 $OB$ 绕 $X$ 轴旋转至 $XOZ$ 坐标平面内，旋转角度应为多少？** `[   ]`

<div align="center">
  <img src="images/cg_4_q4_body.png" width="350" alt="三维旋转示意图"/>
</div>

* A. $\angle AOB$
* B. $\angle EOB$
* C. $\angle EOB'$
* D. $\angle AOB'$

**5. 在三维旋转变换中，关于 $X$ 轴旋转 $90^\circ$ 时变换特点描述正确的是什么？** `[   ]`

* A. $y' = -z$
* B. $y' = z$
* C. $y$ 坐标不变
* D. $x, y, z$ 坐标都不变

---

**6. 空间四面体 $ABCD$ 几何变换关于点 $S(-2, 2, 2)$ 整体放大 2 倍的变换矩阵为：** `[   ]`

* A. $$\begin{bmatrix} 1 & 0 & 0 & -2 \\ 0 & 1 & 0 & 2 \\ 0 & 0 & 1 & 2 \\ 0 & 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 2 \end{bmatrix} \begin{bmatrix} 1 & 0 & 0 & 2 \\ 0 & 1 & 0 & -2 \\ 0 & 0 & 1 & -2 \\ 0 & 0 & 0 & 1 \end{bmatrix}$$
* B. $$\begin{bmatrix} 1 & 0 & 0 & -2 \\ 0 & 1 & 0 & 2 \\ 0 & 0 & 1 & 2 \\ 0 & 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1/2 \end{bmatrix} \begin{bmatrix} 1 & 0 & 0 & 2 \\ 0 & 1 & 0 & -2 \\ 0 & 0 & 1 & -2 \\ 0 & 0 & 0 & 1 \end{bmatrix}$$
* C. $$\begin{bmatrix} 1 & 0 & 0 & 2 \\ 0 & 1 & 0 & -2 \\ 0 & 0 & 1 & -2 \\ 0 & 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 2 \end{bmatrix} \begin{bmatrix} 1 & 0 & 0 & -2 \\ 0 & 1 & 0 & 2 \\ 0 & 0 & 1 & 2 \\ 0 & 0 & 0 & 1 \end{bmatrix}$$
* D. $$\begin{bmatrix} 1 & 0 & 0 & 2 \\ 0 & 1 & 0 & -2 \\ 0 & 0 & 1 & -2 \\ 0 & 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} 2 & 0 & 0 & 0 \\ 0 & 2 & 0 & 0 \\ 0 & 0 & 2 & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} 1 & 0 & 0 & -2 \\ 0 & 1 & 0 & 2 \\ 0 & 0 & 1 & 2 \\ 0 & 0 & 0 & 1 \end{bmatrix}$$

**7. 下面哪项不是齐次坐标的特点？** `[   ]`

* A. 用 $n+1$ 维向量表示一个 $n$ 维向量
* B. 将图形的变换统一为图形的坐标矩阵与某一变换矩阵相乘的形式
* C. 易于表示无穷远点
* D. 一个 $n$ 维向量的齐次坐标表示是唯一的

**8. 经过三维几何变换，使得图 1 中的图形成为如图 2 所示的图形，其几何变换是什么？** `[   ]`

<div align="center">
  <img src="images/cg_4_q9_body.png" width="350" alt="三维立方体几何变换图"/>
</div>

* A. 先沿 $X$ 轴方向平移 1 个单位，再绕 $Y$ 轴逆时针旋转 $45^\circ$
* B. 先绕 $Y$ 轴逆时针旋转 $45^\circ$，再沿 $X$ 轴方向平移 1 个单位
* C. 先沿 $X$ 轴方向平移 1 个单位，再绕 $Y$ 轴顺时针旋转 $45^\circ$
* D. 先绕 $Y$ 轴顺时针旋转 $45^\circ$，再沿 $X$ 轴方向平移 1 个单位

**9. 空间四面体 $ABCD$ 关于 $X$ 轴进行对称变换的变换矩阵为：** `[   ]`

* A. $$\begin{bmatrix} -1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}$$
* B. $$\begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & -1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}$$
* C. $$\begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & -1 & 0 & 0 \\ 0 & 0 & -1 & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}$$
* D. $$\begin{bmatrix} -1 & 0 & 0 & 0 \\ 0 & -1 & 0 & 0 \\ 0 & 0 & -1 & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}$$

---

## 二、 填空题

**10. 基本几何变换都是相对于______ 坐标原点 ______和坐标轴进行的几何变换。**
*(注：填 **坐标原点** 或 **原点**)*
