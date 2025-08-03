#include <windows.h>
#include <GL/glut.h>

#define GL_SILENCE_DEPRECATION

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set the background color to black
    glMatrixMode(GL_PROJECTION);          // Switch to the projection matrix
    glLoadIdentity();                     // Reset the projection matrix
    // Set up a 2D orthographic projection.
    // This maps (0,0) to bottom-left and (width, height) to top-right of the window.
    glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);           // Switch back to the modelview matrix
    glLoadIdentity();                     // Reset the modelview matrix
}

// The display callback function: This is where all drawing happens
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (effectively clears the background)

    // Set the drawing color to red
    glColor3f(0.0f, 1.0f, 0.0f); // RGB: Red, Green, Blue (values from 0.0 to 1.0)

    // Set the size of the point to be drawn
    glPointSize(1.0f); // The point will be 10x10 pixels

    /*
    // Begin drawing points
    glBegin(GL_POINTS);
        // Define the coordinates of our point.
        // In our glOrtho setup (0,0,800,600), (400,300) is the center of an 800x600 window.
        glVertex2f(400.0f, 300.0f); // X = 400, Y = 300
    glEnd(); // End drawing points
    */

    for(int i = 0; i < 800; i = i + 5)
    {
        for(int j = 0; j < 600; j = j + 5)
        {
            glBegin(GL_POINTS);
                glVertex2f((float)i, (float)j);
            glEnd();
        }
    }

    glFlush(); // Force all OpenGL commands to be executed and rendered to the screen
}

// The reshape callback function: Called when the window is resized
void reshape(int width, int height) {
    if (height == 0) height = 1; // Prevent division by zero

    glViewport(0, 0, width, height); // Set the viewport to cover the new window dimensions

    glMatrixMode(GL_PROJECTION); // Switch to projection matrix
    glLoadIdentity();            // Reset it
    // Re-adjust the orthographic projection to match the new window size
    // This ensures that (400,300) still refers to the center,
    // and points scale correctly with window resize.
    glOrtho(0.0, (double)width, 0.0, (double)height, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix
    glLoadIdentity();           // Reset it
}

// The main function where the program execution begins
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT (OpenGL Utility Toolkit)

    // Set the display mode:
    // GLUT_SINGLE: Use a single buffer (drawing directly to the screen)
    // GLUT_RGB: Use RGB color mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 600);       // Set the initial window width and height
    glutInitWindowPosition(100, 100);   // Set the initial window position (top-left corner)
    glutCreateWindow("Simple OpenGL Points"); // Create the window with a title

    init(); // Call our custom initialization function

    glutDisplayFunc(display); // Register the 'display' function as the rendering callback
    glutReshapeFunc(reshape); // Register the 'reshape' function for window resizing

    glutMainLoop(); // Enter the GLUT event processing loop. This function never returns.

    return 0; // This line is technically unreachable due to glutMainLoop()
}
