#include <windows.h>
#include <GL/glut.h>

#define GL_SILENCE_DEPRECATION
#include <cmath>       // For M_PI (or define it) and sin/cos functions

// Define PI if not available (e.g., on some Windows compilers)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Window dimensions
int windowWidth = 800;
int windowHeight = 600;

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    glMatrixMode(GL_PROJECTION);          // Switch to the projection matrix
    glLoadIdentity();                     // Reset the projection matrix
    // Set up a 2D orthographic projection matching window dimensions
    glOrtho(0.0, (double)windowWidth, 0.0, (double)windowHeight, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);           // Switch back to the modelview matrix
    glLoadIdentity();                     // Reset the modelview matrix
}

// Function to draw a circle using line segments
void drawCircle(float centerX, float centerY, float radius, int numSegments) {
    glBegin(GL_LINE_LOOP); // Use GL_LINE_LOOP to connect the last segment to the first
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * M_PI * (float)i / (float)numSegments; // Get angle for current segment
        float x = centerX + radius * cos(theta);                   // Calculate x coordinate
        float y = centerY + radius * sin(theta);                   // Calculate y coordinate
        glVertex2f(x, y);                                          // Specify vertex
    }
    glEnd();
}

// Function to draw a sine wave using line segments
void drawSineWave(float startX, float startY, float endX, float amplitude, float frequency, int numPoints) {
    glBegin(GL_LINE_STRIP); // Use GL_LINE_STRIP for a continuous line
    float rangeX = endX - startX;
    for (int i = 0; i < numPoints; ++i) {
        float x = startX + (float)i / (float)(numPoints - 1) * rangeX;
        // Calculate y using sine function: amplitude * sin(frequency * x_scaled)
        // Adjust frequency to control how many waves are drawn over the given X range
        float y = startY + amplitude * sin(frequency * x * (M_PI / (endX - startX)));
        glVertex2f(x, y);
    }
    glEnd();
}


// The display callback function: This is where all drawing happens
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    // --- Draw a Green Circle ---
    glColor3f(0.0f, 1.0f, 0.0f);   // Green color
    glLineWidth(2.0f);            // 2 pixels wide
    drawCircle(200.0f, 300.0f, 100.0f, 10); // Center (200,300), radius 100, 100 segments

    // --- Draw a Blue Sine Wave ---
    glColor3f(0.0f, 0.0f, 1.0f);   // Blue color
    glLineWidth(3.0f);            // 3 pixels wide
    drawSineWave(100.0f, 100.0f, 700.0f, 50.0f, 3.0f, 200);
    // Starts at X=100, Base Y=100, Ends X=700, Amplitude 50, 3 cycles, 200 points

    // --- Draw an Orange Ellipse (as a stretched circle) ---
    glColor3f(1.0f, 0.5f, 0.0f);   // Orange color
    glLineWidth(1.5f);            // 1.5 pixels wide
    glPushMatrix();                // Save current modelview matrix
    glTranslatef(600.0f, 300.0f, 0.0f); // Translate to desired center
    glScalef(1.5f, 0.8f, 1.0f);     // Scale to make it an ellipse (stretch X, squish Y)
    drawCircle(0.0f, 0.0f, 80.0f, 1000); // Draw a circle at local origin (0,0) which is now (600,300)
    glPopMatrix();                 // Restore previous modelview matrix

    glFlush(); // Force all OpenGL commands to be executed
}

// The reshape callback function: Called when the window is resized
void reshape(int width, int height) {
    if (height == 0) height = 1; // Prevent division by zero

    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, width, height); // Set the viewport to cover the new window dimensions

    glMatrixMode(GL_PROJECTION); // Switch to projection matrix
    glLoadIdentity();            // Reset it
    // Re-adjust the orthographic projection to match the new window size
    glOrtho(0.0, (double)windowWidth, 0.0, (double)windowHeight, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix
    glLoadIdentity();           // Reset it
}

// The main function where the program execution begins
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Curve Lines Demo");

    init(); // Call our custom initialization function

    glutDisplayFunc(display); // Register the 'display' function
    glutReshapeFunc(reshape); // Register the 'reshape' function

    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}
