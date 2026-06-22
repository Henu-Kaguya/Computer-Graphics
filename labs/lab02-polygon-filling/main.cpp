#include <cstdlib>
#include <array>
#include <cmath>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>

namespace {

constexpr float kPi = 3.14159265358979323846f;
constexpr int kVertexCount = 12;

struct Vertex2D {
  GLfloat x;
  GLfloat y;
};

std::array<Vertex2D, kVertexCount> makeStarVertices(float outer_radius, float inner_radius) {
  std::array<Vertex2D, kVertexCount> vertices{};
  for (int index = 0; index < kVertexCount; ++index) {
    const float radius = (index % 2 == 0) ? outer_radius : inner_radius;
    const float angle = kPi / 2.0f - static_cast<float>(index) * (kPi / 6.0f);
    vertices[index] = {radius * std::cos(angle), radius * std::sin(angle)};
  }
  return vertices;
}

void drawStar(const std::array<Vertex2D, kVertexCount>& vertices, bool use_gradient) {
  glBegin(GL_TRIANGLE_FAN);
  if (use_gradient) {
    glColor3f(1.0f, 1.0f, 1.0f);
  } else {
    glColor3f(1.0f, 1.0f, 1.0f);
  }
  glVertex2f(0.0f, 0.0f);

  constexpr std::array<std::array<GLfloat, 3>, 6> colors = {{
      {{1.0f, 0.15f, 0.15f}},
      {{1.0f, 0.9f, 0.15f}},
      {{0.2f, 0.95f, 0.25f}},
      {{0.15f, 0.85f, 1.0f}},
      {{0.3f, 0.3f, 1.0f}},
      {{1.0f, 0.2f, 0.9f}},
  }};

  for (int index = 0; index <= kVertexCount; ++index) {
    const auto& vertex = vertices[index % kVertexCount];
    if (use_gradient) {
      const auto& color = colors[(index / 2) % static_cast<int>(colors.size())];
      glColor3fv(color.data());
    } else {
      glColor3f(1.0f, 1.0f, 1.0f);
    }
    glVertex2f(vertex.x, vertex.y);
  }
  glEnd();
}

}  // namespace

void init() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  const auto vertices = makeStarVertices(0.78f, 0.38f);

  glPushMatrix();
  glTranslatef(-1.0f, 0.0f, 0.0f);
  drawStar(vertices, false);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.0f, 0.0f, 0.0f);
  drawStar(vertices, true);
  glPopMatrix();

  glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  const GLfloat aspect = (h == 0) ? 1.0f : static_cast<GLfloat>(w) / static_cast<GLfloat>(h);
  if (aspect >= 1.0f) {
    glOrtho(-2.4 * aspect, 2.4 * aspect, -1.6, 1.6, -1.0, 1.0);
  } else {
    glOrtho(-2.4, 2.4, -1.6 / aspect, 1.6 / aspect, -1.0, 1.0);
  }
}

void keyboard(unsigned char key, int, int) {
  if (key == 27) {
    std::exit(0);  // ESC to exit
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(120, 120);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Computer Graphics - Lab 2");



  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
