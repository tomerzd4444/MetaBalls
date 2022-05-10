#include <GLFW/glfw3.h>
#include <iostream>
#include "Blob.h"

using namespace MetaBalls;


const int width = 800;
const int height = 800;
const int blobsAmount = 10;
float* PixelBuffer;
void setPixel(int, int, float);

void display();

int size = width * height * 3;

float dist(float x1, float y1, float x2, float y2) {

    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

float calcInvSqRoot(float n) {

    const float threehalfs = 1.5F;
    float y = n;

    long i = *(long*)&y;

    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;

    y = y * (threehalfs - ((n * 0.5F) * y * y));

    return y;
}


int main(void)
{
    GLFWwindow* window;
    PixelBuffer = new float[size];
    Blob* blobs[blobsAmount];
    for (int i = 0; i < blobsAmount; i++) {
        blobs[i] = new Blob();
    }
    //for (int i = 0; i < width * height; i++) {
    //    pixels[i] = new int[3]{ 255, 255, 255 };
    //}
    

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    double previousTime = glfwGetTime();
    int frameCount = 0;
    /* Loop until the user closes the window */
    int scale = 125;
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        frameCount++;
        if (currentTime - previousTime >= 1.0)
        {
            // Display the frame count here any way you want.
            std::cout << frameCount << std::endl;

            frameCount = 0;
            previousTime = currentTime;
        }
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        // Updating Pixels

        for (float x = 0; x < width; x++) {
            for (float y = 0; y < height; y++) {
                // Loops over each pixels
                float sum = 0;
                for (Blob* b : blobs) {
                    // Sets color for each pixel
                    float adjx = width * (b->pos[0] + 1) / 2;
                    float adjy = height * (b->pos[1] + 1) / 2;
                    float d = calcInvSqRoot(dist(x, y, adjx, adjy));
                    
                    sum += scale * b->r * d;
                }
                //pixels[index][0] = sum;
                //pixels[index][1] = sum;
                //pixels[index][2] = sum;
                //glColor3f(pixels[index][0], pixels[index][1], pixels[index][2]);
                // Draws pixel
                //glVertex2f((x / (float)width - 0.5f) * 2.0f, (y / (float)height - 0.5f) * 2.0f);
                setPixel(x, y, sum);
            }
        }

        display();
        //b->show();
        for (Blob* b : blobs) {
            b->update();
        }
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glDrawPixels(width, height, GL_RGB, GL_FLOAT, PixelBuffer);
    glFlush();
}

void setPixel(int x, int y, float col)
{
    int pixelLocation;
    pixelLocation = (y * width * 3) + (x * 3);
    PixelBuffer[pixelLocation + 0] = col;
    PixelBuffer[pixelLocation + 1] = col;
    PixelBuffer[pixelLocation + 2] = col;
};