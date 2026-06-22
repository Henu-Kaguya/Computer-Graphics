#include <cstdlib>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>

namespace {

enum class ModelType {
  Cube,
  Sphere,
  Torus,
  Hierarchy,
};

constexpr GLuint kBodyList = 1;
constexpr GLuint kWheelList = 2;
constexpr GLuint kHeadList = 3;

ModelType g_currentModel = ModelType::Hierarchy;
float g_rotationX = 18.0f;
float g_rotationY = -24.0f;
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

  std::string modelName = "Cube";
  switch (g_currentModel) {
    case ModelType::Cube:
      modelName = "Cube";
      break;
    case ModelType::Sphere:
      modelName = "Sphere";
      break;
    case ModelType::Torus:
      modelName = "Torus";
      break;
    case ModelType::Hierarchy:
      modelName = "Hierarchy";
      break;
  }

  drawBitmapText(18.0f, g_windowHeight - 24.0f, "Right click: choose model. Arrow keys: rotate. Current: " + modelName);
  drawBitmapText(18.0f, g_windowHeight - 42.0f, "The hierarchy mode uses nested display lists for body, wheels, and head.");

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void buildDisplayLists() {
  glNewList(kBodyList, GL_COMPILE);
  const GLfloat bodyAmbient[] = {0.08f, 0.12f, 0.18f, 1.0f};
  const GLfloat bodyDiffuse[] = {0.2f, 0.5f, 0.95f, 1.0f};
  const GLfloat bodySpecular[] = {0.9f, 0.95f, 1.0f, 1.0f};
  setMaterial(bodyAmbient, bodyDiffuse, bodySpecular, 56.0f);
  glPushMatrix();
  glScalef(1.8f, 0.6f, 1.0f);
  glutSolidCube(1.0f);
  glPopMatrix();
  glEndList();

  glNewList(kWheelList, GL_COMPILE);
  const GLfloat wheelAmbient[] = {0.02f, 0.02f, 0.02f, 1.0f};
  const GLfloat wheelDiffuse[] = {0.12f, 0.12f, 0.12f, 1.0f};
  const GLfloat wheelSpecular[] = {0.4f, 0.4f, 0.4f, 1.0f};
  setMaterial(wheelAmbient, wheelDiffuse, wheelSpecular, 18.0f);
  glutSolidTorus(0.08, 0.22, 18, 24);
  glEndList();

  glNewList(kHeadList, GL_COMPILE);
  const GLfloat headAmbient[] = {0.08f, 0.08f, 0.04f, 1.0f};
  const GLfloat headDiffuse[] = {0.95f, 0.76f, 0.26f, 1.0f};
  const GLfloat headSpecular[] = {1.0f, 0.95f, 0.65f, 1.0f};
  setMaterial(headAmbient, headDiffuse, headSpecular, 42.0f);
  glutSolidSphere(0.28, 30, 30);
  glEndList();
}

void drawHierarchyModel() {
  glCallList(kBodyList);

  for (int xSign : {-1, 1}) {
    for (int zSign : {-1, 1}) {
      glPushMatrix();
      glTranslatef(0.55f * static_cast<float>(xSign), -0.28f, 0.38f * static_cast<float>(zSign));
      glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
      glCallList(kWheelList);
      glPopMatrix();
    }
  }

  glPushMatrix();
  glTranslatef(0.0f, 0.5f, 0.0f);
  glCallList(kHeadList);
  glPopMatrix();

  const GLfloat armAmbient[] = {0.08f, 0.1f, 0.06f, 1.0f};
  const GLfloat armDiffuse[] = {0.45f, 0.75f, 0.32f, 1.0f};
  const GLfloat armSpecular[] = {0.7f, 0.82f, 0.72f, 1.0f};
  setMaterial(armAmbient, armDiffuse, armSpecular, 24.0f);

  for (int side : {-1, 1}) {
    glPushMatrix();
    glTranslatef(0.95f * static_cast<float>(side), 0.15f, 0.0f);
    glScalef(0.2f, 0.75f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
  }
}

void drawCurrentModel() {
  switch (g_currentModel) {
    case ModelType::Cube: {
      const GLfloat ambient[] = {0.12f, 0.06f, 0.06f, 1.0f};
      const GLfloat diffuse[] = {0.95f, 0.32f, 0.28f, 1.0f};
      const GLfloat specular[] = {0.95f, 0.85f, 0.82f, 1.0f};
      setMaterial(ambient, diffuse, specular, 36.0f);
      glutSolidCube(1.35f);
      break;
    }
    case ModelType::Sphere: {
      const GLfloat ambient[] = {0.04f, 0.12f, 0.12f, 1.0f};
      const GLfloat diffuse[] = {0.22f, 0.85f, 0.82f, 1.0f};
      const GLfloat specular[] = {0.95f, 0.98f, 0.98f, 1.0f};
      setMaterial(ambient, diffuse, specular, 56.0f);
      glutSolidSphere(0.82f, 36, 36);
      break;
    }
    case ModelType::Torus: {
      const GLfloat ambient[] = {0.08f, 0.06f, 0.12f, 1.0f};
      const GLfloat diffuse[] = {0.55f, 0.42f, 0.96f, 1.0f};
      const GLfloat specular[] = {0.95f, 0.9f, 1.0f, 1.0f};
      setMaterial(ambient, diffuse, specular, 48.0f);
      glutSolidTorus(0.25, 0.7, 28, 36);
      break;
    }
    case ModelType::Hierarchy:
      drawHierarchyModel();
      break;
  }
}

void menu(int value) {
  g_currentModel = static_cast<ModelType>(value);
  glutPostRedisplay();
}

}  // namespace

void init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  const GLfloat light_position[] = {3.5f, 4.0f, 5.0f, 1.0f};
  const GLfloat light_diffuse[] = {0.95f, 0.95f, 0.95f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  buildDisplayLists();
}

void display() {
  glClearColor(0.92f, 0.94f, 0.98f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 1.5, 5.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glRotatef(g_rotationX, 1.0f, 0.0f, 0.0f);
  glRotatef(g_rotationY, 0.0f, 1.0f, 0.0f);

  drawCurrentModel();
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
  if (aspect >= 1.0f) {
    gluPerspective(45.0, aspect, 1.0, 30.0);
  } else {
    gluPerspective(45.0, aspect, 1.0, 30.0);
  }
}

void keyboard(unsigned char key, int, int) {
  if (key == 27) {
    std::exit(0);  // ESC to exit
  }
}

void special(int key, int, int) {
  switch (key) {
    case GLUT_KEY_LEFT:
      g_rotationY -= 6.0f;
      break;
    case GLUT_KEY_RIGHT:
      g_rotationY += 6.0f;
      break;
    case GLUT_KEY_UP:
      g_rotationX -= 6.0f;
      break;
    case GLUT_KEY_DOWN:
      g_rotationX += 6.0f;
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
  glutCreateWindow("Computer Graphics - Lab 5");



  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);

  glutCreateMenu(menu);
  glutAddMenuEntry("Cube", static_cast<int>(ModelType::Cube));
  glutAddMenuEntry("Sphere", static_cast<int>(ModelType::Sphere));
  glutAddMenuEntry("Torus", static_cast<int>(ModelType::Torus));
  glutAddMenuEntry("Hierarchy Model", static_cast<int>(ModelType::Hierarchy));
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}
