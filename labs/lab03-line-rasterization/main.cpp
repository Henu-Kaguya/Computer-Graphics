#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>

namespace {

struct Point {
  int x;
  int y;
};

struct ClipRect {
  int left;
  int right;
  int bottom;
  int top;
};

enum class DemoMode {
  Line,
  Circle,
  Clipping,
};

constexpr int kWindowHalfWidth = 120;
constexpr int kWindowHalfHeight = 90;
constexpr int kTimerIntervalMs = 30;
constexpr ClipRect kClipWindow{-50, 50, -30, 30};

DemoMode g_mode = DemoMode::Clipping;
int g_animationStep = 1;

std::vector<Point> rasterizeLine(Point start, Point end) {
  std::vector<Point> points;

  int x0 = start.x;
  int y0 = start.y;
  const int x1 = end.x;
  const int y1 = end.y;

  const int dx = std::abs(x1 - x0);
  const int sx = (x0 < x1) ? 1 : -1;
  const int dy = -std::abs(y1 - y0);
  const int sy = (y0 < y1) ? 1 : -1;
  int error = dx + dy;

  while (true) {
    points.push_back({x0, y0});
    if ((x0 == x1) && (y0 == y1)) {
      break;
    }
    const int doubled = 2 * error;
    if (doubled >= dy) {
      error += dy;
      x0 += sx;
    }
    if (doubled <= dx) {
      error += dx;
      y0 += sy;
    }
  }

  return points;
}

void appendCircleSymmetry(std::vector<Point>& points, Point center, int x, int y) {
  points.push_back({center.x + x, center.y + y});
  points.push_back({center.x - x, center.y + y});
  points.push_back({center.x + x, center.y - y});
  points.push_back({center.x - x, center.y - y});
  points.push_back({center.x + y, center.y + x});
  points.push_back({center.x - y, center.y + x});
  points.push_back({center.x + y, center.y - x});
  points.push_back({center.x - y, center.y - x});
}

std::vector<Point> rasterizeCircle(Point center, int radius) {
  std::vector<Point> points;

  int x = 0;
  int y = radius;
  int decision = 1 - radius;

  while (x <= y) {
    appendCircleSymmetry(points, center, x, y);
    ++x;
    if (decision < 0) {
      decision += 2 * x + 1;
    } else {
      --y;
      decision += 2 * (x - y) + 1;
    }
  }

  return points;
}

int computeRegionCode(const ClipRect& rect, Point point) {
  int code = 0;
  if (point.x < rect.left) {
    code |= 1;
  } else if (point.x > rect.right) {
    code |= 2;
  }
  if (point.y < rect.bottom) {
    code |= 4;
  } else if (point.y > rect.top) {
    code |= 8;
  }
  return code;
}

bool clipLine(const ClipRect& rect, Point start, Point end, Point& clipped_start, Point& clipped_end) {
  double x0 = static_cast<double>(start.x);
  double y0 = static_cast<double>(start.y);
  double x1 = static_cast<double>(end.x);
  double y1 = static_cast<double>(end.y);

  while (true) {
    const int code0 = computeRegionCode(rect, {static_cast<int>(std::lround(x0)), static_cast<int>(std::lround(y0))});
    const int code1 = computeRegionCode(rect, {static_cast<int>(std::lround(x1)), static_cast<int>(std::lround(y1))});

    if ((code0 | code1) == 0) {
      clipped_start = {static_cast<int>(std::lround(x0)), static_cast<int>(std::lround(y0))};
      clipped_end = {static_cast<int>(std::lround(x1)), static_cast<int>(std::lround(y1))};
      return true;
    }
    if ((code0 & code1) != 0) {
      return false;
    }

    const int code_out = (code0 != 0) ? code0 : code1;
    double x = 0.0;
    double y = 0.0;

    if ((code_out & 8) != 0) {
      x = x0 + (x1 - x0) * (rect.top - y0) / (y1 - y0);
      y = static_cast<double>(rect.top);
    } else if ((code_out & 4) != 0) {
      x = x0 + (x1 - x0) * (rect.bottom - y0) / (y1 - y0);
      y = static_cast<double>(rect.bottom);
    } else if ((code_out & 2) != 0) {
      y = y0 + (y1 - y0) * (rect.right - x0) / (x1 - x0);
      x = static_cast<double>(rect.right);
    } else {
      y = y0 + (y1 - y0) * (rect.left - x0) / (x1 - x0);
      x = static_cast<double>(rect.left);
    }

    if (code_out == code0) {
      x0 = x;
      y0 = y;
    } else {
      x1 = x;
      y1 = y;
    }
  }
}

void drawBitmapText(float x, float y, const std::string& text) {
  glRasterPos2f(x, y);
  for (unsigned char character : text) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, character);
  }
}

void drawAxes() {
  glColor3f(0.2f, 0.25f, 0.35f);
  glBegin(GL_LINES);
  glVertex2f(-kWindowHalfWidth, 0.0f);
  glVertex2f(kWindowHalfWidth, 0.0f);
  glVertex2f(0.0f, -kWindowHalfHeight);
  glVertex2f(0.0f, kWindowHalfHeight);
  glEnd();
}

void drawRasterPoints(const std::vector<Point>& points, int visible_count, float red, float green, float blue, float point_size) {
  glPointSize(point_size);
  glColor3f(red, green, blue);
  glBegin(GL_POINTS);
  const int count = std::min<int>(visible_count, static_cast<int>(points.size()));
  for (int index = 0; index < count; ++index) {
    glVertex2i(points[index].x, points[index].y);
  }
  glEnd();
}

void drawLineScene() {
  const Point start{-90, -45};
  const Point end{75, 40};
  const auto line_points = rasterizeLine(start, end);

  drawAxes();
  drawBitmapText(-112.0f, 78.0f, "1: Bresenham line rasterization");
  drawBitmapText(-112.0f, 68.0f, "Discrete pixels are revealed step by step.");

  drawRasterPoints(line_points, g_animationStep, 1.0f, 0.78f, 0.2f, 5.0f);
}

void drawCircleScene() {
  const auto circle_points = rasterizeCircle({0, 0}, 42);

  drawAxes();
  drawBitmapText(-112.0f, 78.0f, "2: Midpoint circle rasterization");
  drawBitmapText(-112.0f, 68.0f, "Eight-way symmetry is plotted over time.");

  drawRasterPoints(circle_points, g_animationStep, 0.35f, 0.95f, 0.85f, 4.5f);
}

void drawClippingScene() {
  const Point original_start{-95, -52};
  const Point original_end{88, 57};
  Point clipped_start{};
  Point clipped_end{};

  drawAxes();
  drawBitmapText(-112.0f, 78.0f, "3: Cohen-Sutherland clipping");
  drawBitmapText(-112.0f, 68.0f, "Original line, clip window, and clipped result.");

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_LINE_SMOOTH);

  glColor3f(0.9f, 0.25f, 0.35f);
  glBegin(GL_LINES);
  glVertex2i(original_start.x, original_start.y);
  glVertex2i(original_end.x, original_end.y);
  glEnd();

  glColor3f(0.7f, 0.7f, 0.9f);
  glLineWidth(2.0f);
  glBegin(GL_LINE_LOOP);
  glVertex2i(kClipWindow.left, kClipWindow.bottom);
  glVertex2i(kClipWindow.right, kClipWindow.bottom);
  glVertex2i(kClipWindow.right, kClipWindow.top);
  glVertex2i(kClipWindow.left, kClipWindow.top);
  glEnd();
  glLineWidth(1.0f);

  glDisable(GL_LINE_SMOOTH);
  glDisable(GL_BLEND);

  if (clipLine(kClipWindow, original_start, original_end, clipped_start, clipped_end)) {
    const auto clipped_points = rasterizeLine(clipped_start, clipped_end);
    drawRasterPoints(clipped_points, g_animationStep, 0.25f, 0.95f, 0.3f, 5.5f);
  }
}

int currentStepLimit() {
  switch (g_mode) {
    case DemoMode::Line:
      return static_cast<int>(rasterizeLine({-90, -45}, {75, 40}).size());
    case DemoMode::Circle:
      return static_cast<int>(rasterizeCircle({0, 0}, 42).size());
    case DemoMode::Clipping: {
      Point clipped_start{};
      Point clipped_end{};
      if (clipLine(kClipWindow, {-95, -52}, {88, 57}, clipped_start, clipped_end)) {
        return static_cast<int>(rasterizeLine(clipped_start, clipped_end).size());
      }
      return 1;
    }
  }
  return 1;
}

void restartAnimation() {
  g_animationStep = 1;
}

void timer(int) {
  g_animationStep = std::min(g_animationStep + 3, currentStepLimit());
  glutPostRedisplay();
  glutTimerFunc(kTimerIntervalMs, timer, 0);
}

}  // namespace

void init() {
  glClearColor(0.04f, 0.06f, 0.1f, 1.0f);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  switch (g_mode) {
    case DemoMode::Line:
      drawLineScene();
      break;
    case DemoMode::Circle:
      drawCircleScene();
      break;
    case DemoMode::Clipping:
      drawClippingScene();
      break;
  }

  glColor3f(0.85f, 0.88f, 0.95f);
  drawBitmapText(-112.0f, -80.0f, "Keys: 1 line, 2 circle, 3 clipping, R replay, ESC exit");

  glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  const GLfloat aspect = (h == 0) ? 1.0f : static_cast<GLfloat>(w) / static_cast<GLfloat>(h);
  if (aspect >= 1.0f) {
    glOrtho(-kWindowHalfWidth * aspect, kWindowHalfWidth * aspect, -kWindowHalfHeight, kWindowHalfHeight, -1.0, 1.0);
  } else {
    glOrtho(-kWindowHalfWidth, kWindowHalfWidth, -kWindowHalfHeight / aspect, kWindowHalfHeight / aspect, -1.0, 1.0);
  }
}

void keyboard(unsigned char key, int, int) {
  switch (key) {
    case '1':
      g_mode = DemoMode::Line;
      restartAnimation();
      break;
    case '2':
      g_mode = DemoMode::Circle;
      restartAnimation();
      break;
    case '3':
      g_mode = DemoMode::Clipping;
      restartAnimation();
      break;
    case 'r':
    case 'R':
      restartAnimation();
      break;
    case 27:
      std::exit(0);
      break;
    default:
      break;
  }

  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(120, 120);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Computer Graphics - Lab 3");



  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(kTimerIntervalMs, timer, 0);
  glutMainLoop();
  return 0;
}
