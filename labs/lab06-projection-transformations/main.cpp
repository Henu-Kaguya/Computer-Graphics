#include <cstdlib>
#include <array>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>

namespace {

GLuint g_checkerTexture = 0;
std::array<GLfloat, 4> g_secondaryLightPosition = {1.8f, 1.8f, 1.2f, 1.0f};
int g_windowWidth = 800;
int g_windowHeight = 600;

void setMaterial(const GLfloat ambient[4], const GLfloat diffuse[4], const GLfloat specular[4], GLfloat shininess) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void generateCheckerTexture() {
  constexpr int kTextureSize = 64;
  GLubyte pixels[kTextureSize][kTextureSize][3];

  for (int y = 0; y < kTextureSize; ++y) {
    for (int x = 0; x < kTextureSize; ++x) {
      const bool darkCell = (((x / 8) + (y / 8)) % 2) == 0;
      const GLubyte value = darkCell ? 60 : 220;
      pixels[y][x][0] = value;
      pixels[y][x][1] = static_cast<GLubyte>(darkCell ? 95 : 210);
      pixels[y][x][2] = static_cast<GLubyte>(darkCell ? 160 : 255);
    }
  }

  glGenTextures(1, &g_checkerTexture);
  glBindTexture(GL_TEXTURE_2D, g_checkerTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, kTextureSize, kTextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
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
  glColor3f(0.07f, 0.07f, 0.07f);
  drawBitmapText(18.0f, g_windowHeight - 24.0f, "W/A/S/D move the secondary light. Depth testing, lighting, and texture are all enabled.");
  drawBitmapText(18.0f, g_windowHeight - 42.0f, "The checker floor uses a procedural texture; the teapot, cube, and sphere demonstrate occlusion.");

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void updateLights() {
  const GLfloat primaryPosition[] = {-2.2f, 3.4f, 2.8f, 1.0f};
  const GLfloat primaryDiffuse[] = {0.95f, 0.92f, 0.88f, 1.0f};
  const GLfloat secondaryDiffuse[] = {0.38f, 0.72f, 1.0f, 1.0f};
  const GLfloat secondarySpecular[] = {0.5f, 0.82f, 1.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, primaryPosition);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, primaryDiffuse);

  glLightfv(GL_LIGHT1, GL_POSITION, g_secondaryLightPosition.data());
  glLightfv(GL_LIGHT1, GL_DIFFUSE, secondaryDiffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, secondarySpecular);
}

void drawLightMarker() {
  glPushMatrix();
  glTranslatef(g_secondaryLightPosition[0], g_secondaryLightPosition[1], g_secondaryLightPosition[2]);

  const GLfloat emission[] = {0.2f, 0.5f, 0.9f, 1.0f};
  const GLfloat noEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};
  glMaterialfv(GL_FRONT, GL_EMISSION, emission);
  glutSolidSphere(0.12, 20, 20);
  glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
  glPopMatrix();
}

void drawTexturedFloor() {
  const GLfloat floorAmbient[] = {0.14f, 0.14f, 0.14f, 1.0f};
  const GLfloat floorDiffuse[] = {0.9f, 0.9f, 0.9f, 1.0f};
  const GLfloat floorSpecular[] = {0.2f, 0.2f, 0.2f, 1.0f};
  setMaterial(floorAmbient, floorDiffuse, floorSpecular, 10.0f);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, g_checkerTexture);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f, -1.0f, -4.0f);
  glTexCoord2f(6.0f, 0.0f); glVertex3f(4.0f, -1.0f, -4.0f);
  glTexCoord2f(6.0f, 6.0f); glVertex3f(4.0f, -1.0f, 4.0f);
  glTexCoord2f(0.0f, 6.0f); glVertex3f(-4.0f, -1.0f, 4.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void drawSceneObjects() {
  const GLfloat teapotAmbient[] = {0.1f, 0.08f, 0.04f, 1.0f};
  const GLfloat teapotDiffuse[] = {0.85f, 0.66f, 0.22f, 1.0f};
  const GLfloat teapotSpecular[] = {1.0f, 0.95f, 0.82f, 1.0f};
  setMaterial(teapotAmbient, teapotDiffuse, teapotSpecular, 68.0f);
  glPushMatrix();
  glTranslatef(0.0f, -0.1f, 0.2f);
  glutSolidTeapot(0.65);
  glPopMatrix();

  const GLfloat cubeAmbient[] = {0.08f, 0.02f, 0.02f, 1.0f};
  const GLfloat cubeDiffuse[] = {0.92f, 0.25f, 0.28f, 1.0f};
  const GLfloat cubeSpecular[] = {0.85f, 0.82f, 0.82f, 1.0f};
  setMaterial(cubeAmbient, cubeDiffuse, cubeSpecular, 30.0f);
  glPushMatrix();
  glTranslatef(-1.3f, -0.35f, 1.0f);
  glRotatef(22.0f, 1.0f, 1.0f, 0.0f);
  glutSolidCube(0.9f);
  glPopMatrix();

  const GLfloat sphereAmbient[] = {0.03f, 0.08f, 0.12f, 1.0f};
  const GLfloat sphereDiffuse[] = {0.2f, 0.78f, 0.96f, 1.0f};
  const GLfloat sphereSpecular[] = {0.92f, 0.98f, 1.0f, 1.0f};
  setMaterial(sphereAmbient, sphereDiffuse, sphereSpecular, 50.0f);
  glPushMatrix();
  glTranslatef(1.45f, -0.4f, -0.65f);
  glutSolidSphere(0.62, 32, 32);
  glPopMatrix();
}

}  // namespace

void init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_TEXTURE_2D);

  const GLfloat globalAmbient[] = {0.16f, 0.16f, 0.18f, 1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

  generateCheckerTexture();
}

void display() {
  glClearColor(0.82f, 0.88f, 0.96f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 2.4, 6.6, 0.0, -0.15, 0.0, 0.0, 1.0, 0.0);

  updateLights();

  drawTexturedFloor();
  drawSceneObjects();
  drawLightMarker();
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
  gluPerspective(45.0, aspect, 1.0, 30.0);
}

void keyboard(unsigned char key, int, int) {
  switch (key) {
    case 'w':
    case 'W':
      g_secondaryLightPosition[2] -= 0.2f;
      break;
    case 's':
    case 'S':
      g_secondaryLightPosition[2] += 0.2f;
      break;
    case 'a':
    case 'A':
      g_secondaryLightPosition[0] -= 0.2f;
      break;
    case 'd':
    case 'D':
      g_secondaryLightPosition[0] += 0.2f;
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
  glutCreateWindow("Computer Graphics - Lab 6");



  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
