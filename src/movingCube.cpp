#include<iostream> 
#include<glad/glad.h> 
#include<GLFW/glfw3.h> 
#include<glm/glm.hpp> 
#include<glm/gtc/matrix_transform.hpp> 
#include<glm/gtc/type_ptr.hpp> 

#include"texture.h" 
#include"shaderClass.h"
#include"VBO.h" 
#include"VAO.h" 
#include"EBO.h" 
#include"extraFunctions.h" 
#include"camera.h" 

const unsigned int width = 800; 
const unsigned int height = 800; 

int main(){ 

    glfwInit(); 

    GLfloat vertices[] {
        // x,      y,      z       r,    g,    b       u,    v

        // --- FRONT FACE (Z = -0.5f) ---
        -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Close bottom left  (0)
        0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, // Close bottom right (1)
        0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, // Close top right    (2)
        -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, // Close top left     (3)

        // --- BACK FACE (Z = 0.5f) ---
        0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Far bottom right   (4)
        -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, // Far bottom left    (5)
        -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, // Far top left       (6)
        0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, // Far top right      (7)

        // --- LEFT FACE (X = -0.5f) ---
        -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Far bottom left    (8)
        -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, // Close bottom left  (9)
        -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, // Close top left     (10)
        -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, // Far top left       (11)

        // --- RIGHT FACE (X = 0.5f) ---
        0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Close bottom right (12)
        0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, // Far bottom right   (13)
        0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, // Far top right      (14)
        0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, // Close top right    (15)

        // --- TOP FACE (Y = 0.5f) ---
        -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Close top left     (16)
        0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, // Close top right    (17)
        0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, // Far top right      (18)
        -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, // Far top left       (19)

        // --- BOTTOM FACE (Y = -0.5f) ---
        -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Far bottom left    (20)
        0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, // Far bottom right   (21)
        0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, // Close bottom right (22)
        -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f  // Close bottom left  (23)
    };
    GLuint indices[] {
        // Front Face
        0, 1, 2,     2, 3, 0,
        // Back Face
        4, 5, 6,     6, 7, 4,
        // Left Face
        8, 9, 10,    10, 11, 8,
        // Right Face
        12, 13, 14,  14, 15, 12,
        // Top Face
        16, 17, 18,  18, 19, 16,
        // Bottom Face
        20, 21, 22,  22, 23, 20
    };

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    GLFWwindow* window = glfwCreateWindow(width, height, "moving cube" , NULL, NULL); 

    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl; 
        glfwTerminate(); 
        return -1; 
    } 

    glfwMakeContextCurrent(window); 

    if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialise GLAD. " << std::endl; 
        return -1; 
    }

    glViewport(0, 0, width, height); 
    glfwSetFramebufferSizeCallback(window, et::framebuffer_size_callback); 
	glfwSwapInterval(1); 
    glEnable(GL_DEPTH_TEST); 
    et::versioncheck();  
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);        

    Shader shaderProgram("C:/OGL/res/vertex/mat.vert.txt", "C:/OGL/res/fragment/tex.frag.txt"); 

    VAO VAO1; 
    VAO1.Bind(); 
    
    VBO VBO1(vertices, sizeof(vertices)); 
    EBO EBO1(indices, sizeof(indices)); 

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); 
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); 
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); 

    VAO1.Unbind(); 
    VBO1.Unbind(); 
    EBO1.Unbind(); 

    Texture brick("C:/OGL/res/texture/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); 
    brick.texUnit(shaderProgram, "tex0", 0); 

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f)); 

    double prevTime = glfwGetTime(); 
    float xc = 0.0f; 
    float yc = 0.0f; 
    float zc = -1.0f; 

    while(!glfwWindowShouldClose(window)){


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        shaderProgram.Activate(); 

        double currentTime = glfwGetTime(); 

        if(currentTime - prevTime >= 1.0f / 60.0f){
            if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
                yc += 0.1f; 
            }if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
                yc -= 0.1f; 
            }if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
                xc += 0.1f; 
            }if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
                xc -= 0.1f; 
            } 
            prevTime = currentTime; 
            camera.Inputs(window); 
        }

        camera.Matrix(90.0f, 0.1f, 100.0f, shaderProgram, "camMatrix"); 
		glm::mat4 model = glm::mat4(1.0f); 
    
        model = glm::translate(model, glm::vec3(xc, yc, zc)); 

        model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));

        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model"); 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 

        brick.Bind(); 
        VAO1.Bind(); 

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window); 
        et::processInput(window); 
        glfwPollEvents();

    }

    VAO1.Delete(); 
    VBO1.Delete(); 
    EBO1.Delete(); 
    brick.Delete(); 
    shaderProgram.Delete(); 

    glfwDestroyWindow(window); 
    glfwTerminate(); 
}