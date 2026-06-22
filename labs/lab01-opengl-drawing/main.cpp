#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>

namespace {

void setMaterial(const GLfloat ambient[4], const GLfloat diffuse[4], const GLfloat specular[4], GLfloat shininess) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

}  // namespace

void init() {
  glEnable(GL_DEPTH_TEST);

  const GLfloat light_position[] = {1.0f, 1.0f, 1.0f, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glShadeModel(GL_SMOOTH);
}

void display() {
  glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -0.2f);
  glRotatef(18.0f, 1.0f, 0.0f, 0.0f);

  const GLfloat ambient[] = {0.08f, 0.08f, 0.08f, 1.0f};
  const GLfloat highlight[] = {0.9f, 0.9f, 0.9f, 1.0f};

  glPushMatrix();
  glTranslatef(-1.1f, -0.15f, 0.0f);
  const GLfloat magenta[] = {0.90f, 0.20f, 0.75f, 1.0f};
  setMaterial(ambient, magenta, highlight, 48.0f);
  glutSolidTeapot(0.35);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0f, -0.05f, 0.0f);
  const GLfloat gold[] = {0.95f, 0.72f, 0.18f, 1.0f};
  setMaterial(ambient, gold, highlight, 64.0f);
  glutSolidSphere(0.52, 36, 36);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.15f, 0.05f, 0.0f);
  glScalef(1.0f, 1.2f, 1.0f);
  glDisable(GL_LIGHTING);
  glColor3f(0.15f, 0.55f, 0.95f);
  glutWireSphere(0.48, 20, 20);
  glEnable(GL_LIGHTING);
  glPopMatrix();

  glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  const GLfloat aspect = (h == 0) ? 1.0f : static_cast<GLfloat>(w) / static_cast<GLfloat>(h);
  if (aspect >= 1.0f) {
    glOrtho(-aspect, aspect, -1.0, 1.0, -2.0, 2.0);
  } else {
    glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, -2.0, 2.0);
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(500, 100);
  glutInitWindowSize(640, 640);
  glutCreateWindow("Computer Graphics - Lab 1");



  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}
