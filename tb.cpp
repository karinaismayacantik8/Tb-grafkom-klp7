#include <GL/glut.h>
#include <math.h>

float rotationX = 0.0f;
float rotationY = 0.0f;
float sunPosition = 0.0f;
float translateX = 0.0f;
float translateY = 0.0f;
float translateZ = 0.0f;
float scaleX = 1.0f;
float scaleY = 1.0f;
float scaleZ = 1.0f;

// Tekstur ID
GLuint sandTexture;
GLuint stoneTexture;

// Fungsi untuk membuat tekstur prosedural pasir
void createSandTexture() {
    const int size = 128;
    unsigned char* data = new unsigned char[size * size * 3];
    
    for(int i = 0; i < size * size; i++) {
        unsigned char value = 200 + (rand() % 56); // Variasi warna pasir
        data[i*3] = value;        // R
        data[i*3+1] = value - 40; // G
        data[i*3+2] = value - 80; // B
    }

    glGenTextures(1, &sandTexture);
    glBindTexture(GL_TEXTURE_2D, sandTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    delete[] data;
}

// Fungsi untuk membuat tekstur prosedural batu
void createStoneTexture() {
    const int size = 128;
    unsigned char* data = new unsigned char[size * size * 3];
    
    for(int i = 0; i < size * size; i++) {
        unsigned char value = 180 + (rand() % 76); // Variasi warna batu
        data[i*3] = value;        // R
        data[i*3+1] = value - 20; // G
        data[i*3+2] = value - 40; // B
    }

    glGenTextures(1, &stoneTexture);
    glBindTexture(GL_TEXTURE_2D, stoneTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    delete[] data;
}

void init() {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f); // Warna langit biru cerah
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);

    // Material properties
    GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    createSandTexture();
    createStoneTexture();
}

void drawGround() {
    glBindTexture(GL_TEXTURE_2D, sandTexture);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    for(int x = -20; x < 20; x++) {
        for(int z = -20; z < 20; z++) {
            glTexCoord2f(0.0f, 0.0f); glVertex3f(x, -1.0f, z);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(x+1, -1.0f, z);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(x+1, -1.0f, z+1);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(x, -1.0f, z+1);
        }
    }
    glEnd();
}

void drawPyramid() {
    glBindTexture(GL_TEXTURE_2D, stoneTexture);
    
    // Base size of the pyramid
    float baseSize = 2.0f;
    float height = 3.0f;
    
    glBegin(GL_TRIANGLES);
    // Front face
    glNormal3f(0.0f, 0.5f, 0.5f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, height, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-baseSize, 0.0f, baseSize);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(baseSize, 0.0f, baseSize);

    // Right face
    glNormal3f(0.5f, 0.5f, 0.0f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, height, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(baseSize, 0.0f, baseSize);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(baseSize, 0.0f, -baseSize);

    // Back face
    glNormal3f(0.0f, 0.5f, -0.5f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, height, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(baseSize, 0.0f, -baseSize);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-baseSize, 0.0f, -baseSize);

    // Left face
    glNormal3f(-0.5f, 0.5f, 0.0f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, height, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-baseSize, 0.0f, -baseSize);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-baseSize, 0.0f, baseSize);
    glEnd();

    // Base
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-baseSize, 0.0f, baseSize);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(baseSize, 0.0f, baseSize);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(baseSize, 0.0f, -baseSize);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-baseSize, 0.0f, -baseSize);
    glEnd();
}

void updateSunPosition() {
    sunPosition += 0.5f;
    if(sunPosition > 360.0f) sunPosition = 0.0f;
    
    float sunX = 20.0f * cos(sunPosition * 3.14159f / 180.0f);
    float sunY = 20.0f * sin(sunPosition * 3.14159f / 180.0f);
    
    GLfloat light_position[] = { sunX, sunY, 20.0f, 1.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 0.9f, 1.0f };
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera position and orientation
    gluLookAt(8.0f, 5.0f, 8.0f,  // Eye position
              0.0f, 0.0f, 0.0f,  // Look at point
              0.0f, 1.0f, 0.0f); // Up vector

    // Update lighting
    updateSunPosition();

    // Terapkan transformasi pada piramida
    glPushMatrix();
    
    // Translasi
    glTranslatef(translateX, translateY, translateZ);
    
    // Rotasi
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    
    // Scaling
    glScalef(scaleX, scaleY, scaleZ);

    // Draw pyramid
    drawPyramid();
    glPopMatrix();

    // Draw ground (tidak dipengaruhi transformasi piramida)
    drawGround();

    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    const float moveSpeed = 0.1f;
    const float scaleSpeed = 0.1f;

    switch (key) {
        // Translasi
        case 'w': translateZ -= moveSpeed; break;  // Maju
        case 's': translateZ += moveSpeed; break;  // Mundur
        case 'a': translateX -= moveSpeed; break;  // Kiri
        case 'd': translateX += moveSpeed; break;  // Kanan
        case 'q': translateY += moveSpeed; break;  // Atas
        case 'e': translateY -= moveSpeed; break;  // Bawah

        // Scaling
        case 'z': // Scale up
            scaleX += scaleSpeed;
            scaleY += scaleSpeed;
            scaleZ += scaleSpeed;
            break;
        case 'x': // Scale down
            if (scaleX > scaleSpeed) {
                scaleX -= scaleSpeed;
                scaleY -= scaleSpeed;
                scaleZ -= scaleSpeed;
            }
            break;

        // Reset transformasi
        case 'r':
            translateX = translateY = translateZ = 0.0f;
            rotationX = rotationY = 0.0f;
            scaleX = scaleY = scaleZ = 1.0f;
            break;

        case 27: // ESC
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            rotationX += 5.0f;
            break;
        case GLUT_KEY_DOWN:
            rotationX -= 5.0f;
            break;
        case GLUT_KEY_LEFT:
            rotationY -= 5.0f;
            break;
        case GLUT_KEY_RIGHT:
            rotationY += 5.0f;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Piramida Mesir 3D Realistis - OpenGL");

    init();

    glutDisplayFunc(display);	
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}
