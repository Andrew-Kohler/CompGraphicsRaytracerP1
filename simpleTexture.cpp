// Based on templates from learnopengl.com

#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#include <iostream> 
#include <sstream>
//#include <vector>
//#include<glm/glm.hpp>
//#include<glm/gtc/matrix_transform.hpp>
//#include<glm/gtc/type_ptr.hpp>
//#include <glm/ext/vector_float3.hpp>

#include "OrthoCamera.h"
#include "PerspectiveCamera.h";
#include "Sphere.h"
#include "Scene.h"
#include "HitReport.h"
#include "PointLight.h"
#include "AmbientLight.h"
#include "Triangle.h"
#include "Tetrahedron.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;\n"
"TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D texture1;\n"
"void main()\n"
"{\n"
"   FragColor = texture(texture1, TexCoord);\n"
"}\n\0";

bool perspBool;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Raytracing Begins", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // // GLEW: load all OpenGL function pointers
    glewInit();

    // build and compile the shaders
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // WORK IN HERE ------------------------------------------------------------------
    // Create the image (RGB Array) to be displayed
    const int width = 512; // keep it in powers of 2!
    const int height = 512; // keep it in powers of 2!
    unsigned char image[width * height * 3];

    // Relevant data
    glm::vec3 camPos(2.5f, 1.0f, -1.0f);   // Camera position -.5, .5
    glm::vec3 camPos2(3.0f, -3.0f, -6.0f);   // Camera position -.5, .5
    glm::vec3 camDir(-1.0f, 0.0f, .2f);     // Camera lookAt dir - normal (currently looking in x dir)
    glm::vec3 camUp(0.0f, -1.0f, 0.0f);      // Vector that defines which way is up for the camera


    // Materials
    ObjMaterial basicMaterial = ObjMaterial(0.3f, 0.3f, 0.4f, glm::vec3(255, 255, 0), glm::vec3(.2, .2, .2), glm::vec3(255, 255, 0),false, glm::vec3(.2, .2, .2), 10);
    ObjMaterial basicMaterial2 = ObjMaterial(0.3f, 0.3f, 0.4f, glm::vec3(255, 0, 0), glm::vec3(255, 255, 255), glm::vec3(255, 0, 0), false, glm::vec3(.2, .2, .2), 10);
    ObjMaterial basicMaterial3 = ObjMaterial(0.1f, 0.1f, 0.8f, glm::vec3(180, 180, 255), glm::vec3(1, 1, 1), glm::vec3(180, 180, 255), true, glm::vec3(.3, .3, .3), 2500);

    ObjMaterial ice = ObjMaterial(0.1f, 0.1f, 0.8f, glm::vec3(180, 180, 255), glm::vec3(5, 5, 5), glm::vec3(180, 180, 255), true, glm::vec3(.3, .3, .3), 500);
    ObjMaterial snow = ObjMaterial(0.1f, 0.1f, 0.8f, glm::vec3(230, 230, 230), glm::vec3(.1, .1, .3), glm::vec3(230, 230, 230), false, glm::vec3(.3, .3, .3), 10);
    ObjMaterial coal = ObjMaterial(0.1f, 0.1f, 0.8f, glm::vec3(30, 30, 30), glm::vec3(5, 5, 5), glm::vec3(30, 30, 30), false, glm::vec3(.3, .3, .3), 250);
    ObjMaterial ice2 = ObjMaterial(0.1f, 0.1f, 0.8f, glm::vec3(160, 160, 255), glm::vec3(5, 5, 5), glm::vec3(160, 160, 255), false, glm::vec3(.6, .6, .6), 500);
    ObjMaterial ball = ObjMaterial(0.1f, 0.1f, 0.8f, glm::vec3(255, 0, 0), glm::vec3(5, 5, 5), glm::vec3(255, 0, 0), false, glm::vec3(.3, .3, .3), 2000);

    // Cameras
    OrthoCamera ortho = OrthoCamera(camPos2, camDir, camUp, 64, 64, width, height); // Create a camera which will render our Scene

    PerspectiveCamera persp = PerspectiveCamera(camPos, camDir, camUp, width, height, width, height, .5f); // Create a camera which will render our Scene

    // Objects
    float corner = 7;
    glm::vec3 planeC1 = glm::vec3(corner, 0, corner);
    glm::vec3 planeC2 = glm::vec3(corner, 0, -corner);
    glm::vec3 planeC3 = glm::vec3(-corner, 0, corner);
    glm::vec3 planeC4 = glm::vec3(-corner, 0, -corner);

    glm::vec3 tetraC1 = glm::vec3(1, 0, 0);
    glm::vec3 tetraC2 = glm::vec3(0, 0, 0);
    glm::vec3 tetraC3 = glm::vec3(0, 0, 1);
    glm::vec3 tetraC4 = glm::vec3(1, 0, 0);

    //Sphere ball = Sphere(basicMaterial, .5, glm::vec3(0, 1, -.3f));   // Create a Sphere to go in the scene
    //Sphere ball2 = Sphere(basicMaterial, .3, glm::vec3(2, 1, -0.5f));   // Create a Sphere to go in the scene
    //Sphere ball3 = Sphere(basicMaterial, .5, glm::vec3(0, 1, -2));   
    //Triangle tri = Triangle(basicMaterial, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(1, 1, 0), true);
    //Triangle pl1 = Triangle(basicMaterial3, planeC1, planeC2, planeC4, true);
    //Triangle pl2 = Triangle(basicMaterial3, planeC3, planeC1, planeC4, true);

    //Sphere ball4 = Sphere(basicMaterial2, .2, glm::vec3(0, 0, 1));
    //Sphere ball5 = Sphere(basicMaterial2, .2, glm::vec3(1, 0, 0));
    //Sphere ball6 = Sphere(basicMaterial2, .2, glm::vec3(0, 0, -1));
    //Sphere ball7 = Sphere(basicMaterial2, .2, glm::vec3(.5, 1, 0));

    //Triangle tri2 = Triangle(basicMaterial, glm::vec3(.5, 1, 0), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), false);

    Tetrahedron d4 = Tetrahedron();
    //Tetrahedron d42 = Tetrahedron(basicMaterial, tetraC1, tetraC2, tetraC3, tetraC4);

    Triangle pl1 = Triangle(ice, planeC1, planeC2, planeC4, true);
    Triangle pl2 = Triangle(snow, planeC3, planeC1, planeC4, true);
    Sphere base = Sphere(snow, .5, glm::vec3(0.25, .5, .25));
    Sphere top = Sphere(snow, .4, glm::vec3(0.25, 1.35, .25));
    Sphere eye1 = Sphere(coal, .1, glm::vec3(.65, 1.4, 0));
    Sphere eye2 = Sphere(coal, .1, glm::vec3(0, 1.4, -.15));

    glm::vec3 iC1 = glm::vec3(-2, 0, -4);
    glm::vec3 iC2 = glm::vec3(-4, 0, -1); // - 4.5
    glm::vec3 iC3 = glm::vec3(-1, 0, -2);
    glm::vec3 iC4 = glm::vec3(-3, 2, -2);

    glm::vec3 b1 = glm::vec3(0, 0, 1);
    glm::vec3 b2 = glm::vec3(1, 0, 0);
    glm::vec3 b3 = glm::vec3(0, 0, -1);
    glm::vec3 tCoord = glm::vec3(.5, 1, 0);

    Tetrahedron iceSpire = Tetrahedron(ice2, iC1, iC2, iC3, iC4);
    Triangle test = Triangle(ice2, iC4, iC2, iC1, false);
    Triangle test2 = Triangle(ice2, iC2, iC4, iC3, false);
    Triangle test3 = Triangle(ice2, iC3, iC1, iC4, false);

    Sphere redBall = Sphere(ball, .2, glm::vec3(3, .2, -3));

    // Lights
    PointLight light = PointLight(glm::vec3(1.0f, 1.2f, -1.0f), 8.0f);
    PointLight light2 = PointLight(glm::vec3(-1.0, 1.5f, 1.0f), 6.0f);
    PointLight light3 = PointLight(glm::vec3(1.0, 1.5f, 1.0f), 3.0f);
    AmbientLight light4 = AmbientLight(1.0f);
    PointLight light5 = PointLight(glm::vec3(-1.0, 1.5f, -3.0f),10.0f);

    std::vector<Object*> objList;   // Create a vector of Objects to pass into the Scene constructor
    //objList.push_back(&ball);
   // objList.push_back(&ball2);
    //objList.push_back(&ball3);
    //objList.push_back(&tri2);
    //objList.push_back(&pl1);
    //objList.push_back(&pl2);


    //objList.push_back(&ball4);
    //objList.push_back(&ball5);
    //objList.push_back(&ball6);
    //objList.push_back(&ball7);
    //objList.push_back(&d4);

    objList.push_back(&pl1);
    objList.push_back(&pl2);
    objList.push_back(&base);
    objList.push_back(&top);
    objList.push_back(&eye1);
    objList.push_back(&eye2);
    objList.push_back(&iceSpire);
    //objList.push_back(&test);
    //objList.push_back(&test2);
    //objList.push_back(&test3);
    //objList.push_back(&redBall);

    std::vector<Light*> lightList;
    lightList.push_back(&light);
    //lightList.push_back(&light2);
    //lightList.push_back(&light3);
    lightList.push_back(&light4);
    lightList.push_back(&light5);

    Scene currentScene = Scene(objList, lightList);                                 // Create a Scene
     
    for (int i = 0; i < height; i++) // We iterate over each pixel
    {
        for (int j = 0; j < width; j++)
        {
            Ray currentRay = (&persp)->generateRay(i, j);   // Compute a viewing ray for this pixel
            //HitReport report = currentScene.objHit(currentRay, 0, std::numeric_limits<float>::infinity());
            // TODO: If there is an intersection, use the data we got to set the color of this pixel; otherwise, the pixel is a default color
            glm::vec3 color = currentScene.lightColor(currentRay, 0, std::numeric_limits<float>::infinity(), 3);
            int idx = (j * height + i) * 3;
            //image[idx] = report.material.baseColor.x; //((i+j) % 2) * 255;
            //image[idx + 1] = report.material.baseColor.y;
            //image[idx + 2] = report.material.baseColor.z;
            image[idx] = (255 <= color.x) ? 255 : color.x; //((i+j) % 2) * 255;
            image[idx + 1] = (255 <= color.y) ? 255 : color.y;
            image[idx + 2] = (255 <= color.z) ? 255 : color.z;
        }
    }
    //// WORK ABOVE HERE--------------------------------------------------------

    unsigned char* data = &image[0];
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    int frameCount = 0; // The number of times I will be re-rendering
    int frameCap = 48;
    perspBool = true;
    bool prevPerspBool = perspBool;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        
        // input
        // -----
        if (prevPerspBool != perspBool) {
            for (int i = 0; i < height; i++) // We iterate over each pixel
            {
                for (int j = 0; j < width; j++)
                {
                    Ray currentRay = Ray(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
                    if (perspBool)
                        currentRay = (&persp)->generateRay(i, j);   // Compute a viewing ray for this pixel
                    else
                        currentRay = (&ortho)->generateRay(i, j);
                    glm::vec3 color = currentScene.lightColor(currentRay, 0, std::numeric_limits<float>::infinity(), 3);
                    int idx = (j * height + i) * 3;
                    image[idx] = (255 <= color.x) ? 255 : color.x; //((i+j) % 2) * 255;
                    image[idx + 1] = (255 <= color.y) ? 255 : color.y;
                    image[idx + 2] = (255 <= color.z) ? 255 : color.z;
                }
            }


            data = &image[0];
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
        }

        prevPerspBool = perspBool;

        

        /*if (frameCount < frameCap) {
            persp.setPos(glm::vec3(persp.getPos().x - (2.5/24.0), persp.getPos().y, persp.getPos().z));
            if (persp.getPos().x > 0) {
                persp.setDir(glm::vec3(persp.getDir().x + (1.0 / 24.0), persp.getDir().y, persp.getDir().z - (1.0/24.0)), camUp);
            }
            else {
                persp.setDir(glm::vec3(persp.getDir().x + (1.0 / 24.0), persp.getDir().y, persp.getDir().z + (1.0 / 24.0)), camUp);
            }
            eye1.setCenter(glm::vec3(eye1.getCenter().x - (.65 / 48.0), eye1.getCenter().y, eye1.getCenter().z - (.15 / 48.0)));
            eye2.setCenter(glm::vec3(eye2.getCenter().x - (.65 / 48.0), eye2.getCenter().y, eye2.getCenter().z + (.15 / 48.0)));
            std::cout << "loop" << "\n";
            std::ostringstream fileName;
            fileName  << "render/render" << frameCount << ".jpg";
            std::string fileString = fileName.str();
            stbi_write_jpg(fileString.c_str(), width, height, 3, data, width * height * 3);
            frameCount++;
        }*/
        
        //objList.clear();
        processInput(window);

        // render
        // ------
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        //stbi_image_free(data);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        perspBool = !perspBool;
        std::cout << "New render now loading. Thank you for your patience.\n";
    }
        

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}