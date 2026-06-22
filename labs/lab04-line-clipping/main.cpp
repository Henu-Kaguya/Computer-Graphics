#include <cstdlib>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>

namespace {

bool g_usePerspective = false;
float g_cameraX = 0.0f;
float g_cameraZ = 6.5f;
float g_teapotX = 0.0f;
float g_teapotZ = 0.0f;
float g_teapotRotation = 0.0f;
int g_windowWidth = 800;
int g_windowHeight = 600;

void setMaterial(const GLfloat ambient[4], const GLfloat diffuse[4], const GLfloat specular[4], GLfloat shininess) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void drawBitmapText(float x, float y, const std::string& text) {
  glRasterPos2f(x, y);
  for (unsigned char character : text) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, character);
  }
}

void drawOverlay() {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, static_cast<GLdouble>(g_windowWidth), 0.0, static_cast<GLdouble>(g_windowHeight));

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glColor3f(0.08f, 0.08f, 0.08f);
  drawBitmapText(18.0f, g_windowHeight - 24.0f, g_usePerspective ? "Projection: Perspective (press P to toggle)" : "Projection: Orthographic (press P to toggle)");
  drawBitmapText(18.0f, g_windowHeight - 42.0f, "Arrow keys move the camera. J/L and I/K slide the teapot. E spins the teapot.");

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void drawTable() {
  const GLfloat ambient[] = {0.16f, 0.12f, 0.08f, 1.0f};
  const GLfloat diffuse[] = {0.58f, 0.38f, 0.2f, 1.0f};
  const GLfloat specular[] = {0.2f, 0.2f, 0.18f, 1.0f};
  setMaterial(ambient, diffuse, specular, 18.0f);

  glPushMatrix();
  glTranslatef(0.0f, -0.65f, 0.0f);
  glScalef(3.2f, 0.2f, 2.2f);
  glutSolidCube(1.0);
  glPopMatrix();

  for (int xSign : {-1, 1}) {
    for (int zSign : {-1, 1}) {
      glPushMatrix();
      glTranslatef(1.3f * static_cast<float>(xSign), -1.25f, 0.9f * static_cast<float>(zSign));
      glScalef(0.16f, 1.0f, 0.16f);
      glutSolidCube(1.0);
      glPopMatrix();
    }
  }
}

void drawAxes() {
  glDisable(GL_LIGHTING);
  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glColor3f(0.95f, 0.15f, 0.15f);
  glVertex3f(0.0f, -0.5f, 0.0f);
  glVertex3f(1.6f, -0.5f, 0.0f);
  glColor3f(0.15f, 0.85f, 0.2f);
  glVertex3f(0.0f, -0.5f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glColor3f(0.2f, 0.45f, 1.0f);
  glVertex3f(0.0f, -0.5f, 0.0f);
  glVertex3f(0.0f, -0.5f, 1.6f);
  glEnd();
  glLineWidth(1.0f);
  glEnable(GL_LIGHTING);
}

void drawTeapot() {
  const GLfloat ambient[] = {0.1f, 0.08f, 0.16f, 1.0f};
  const GLfloat diffuse[] = {0.38f, 0.3f, 0.95f, 1.0f};
  const GLfloat specular[] = {0.95f, 0.92f, 1.0f, 1.0f};
  setMaterial(ambient, diffuse, specular, 72.0f);

  glPushMatrix();
  glTranslatef(g_teapotX, -0.28f, g_teapotZ);
  glRotatef(g_teapotRotation, 0.0f, 1.0f, 0.0f);
  glutSolidTeapot(0.42);
  glPopMatrix();
}

}  // namespace

void init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  const GLfloat light_position[] = {3.0f, 4.0f, 5.0f, 1.0f};
  const GLfloat light_diffuse[] = {0.95f, 0.95f, 0.95f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void display() {
  glClearColor(0.9f, 0.94f, 0.98f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(g_cameraX, 2.1, g_cameraZ, g_cameraX, -0.2, 0.0, 0.0, 1.0, 0.0);

  drawAxes();
  drawTable();
  drawTeapot();
  drawOverlay();

  glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
  g_windowWidth = (w == 0) ? 1 : w;
  g_windowHeight = (h == 0) ? 1 : h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  const GLfloat aspect = (h == 0) ? 1.0f : static_cast<GLfloat>(w) / static_cast<GLfloat>(h);
  if (g_usePerspective) {
    gluPerspective(45.0, aspect, 1.0, 30.0);
  } else if (aspect >= 1.0f) {
    glOrtho(-3.2 * aspect, 3.2 * aspect, -2.4, 2.4, 1.0, 30.0);
  } else {
    glOrtho(-3.2, 3.2, -2.4 / aspect, 2.4 / aspect, 1.0, 30.0);
  }
}

void keyboard(unsigned char key, int, int) {
  switch (key) {
    case 'p':
    case 'P':
      g_usePerspective = !g_usePerspective;
      reshape(g_windowWidth, g_windowHeight);
      break;
    case 'j':
    case 'J':
      g_teapotX -= 0.12f;
      break;
    case 'l':
    case 'L':
      g_teapotX += 0.12f;
      break;
    case 'i':
    case 'I':
      g_teapotZ -= 0.12f;
      break;
    case 'k':
    case 'K':
      g_teapotZ += 0.12f;
      break;
    case 'e':
    case 'E':
      g_teapotRotation += 12.0f;
      break;
    case 27:
      std::exit(0);
      break;
    default:
      break;
  }

  glutPostRedisplay();
}

void special(int key, int, int) {
  switch (key) {
    case GLUT_KEY_LEFT:
      g_cameraX -= 0.18f;
      break;
    case GLUT_KEY_RIGHT:
      g_cameraX += 0.18f;
      break;
    case GLUT_KEY_UP:
      g_cameraZ = (g_cameraZ > 3.2f) ? (g_cameraZ - 0.2f) : g_cameraZ;
      break;
    case GLUT_KEY_DOWN:
      g_cameraZ = (g_cameraZ < 10.0f) ? (g_cameraZ + 0.2f) : g_cameraZ;
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
  glutCreateWindow("Computer Graphics - Lab 4");



  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMainLoop();
  return 0;
}
