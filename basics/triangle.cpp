#include <iostream> 
#include <glad/glad.h> 
#include <GLFW/glfw3.h> 

// forward declarations of functions 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void versioncheck(); 

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.0.0f, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0"; 

int main(){
    
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    } 

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // need context, tells which version to use maybe
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // same as major 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    GLFWwindow* window = glfwCreateWindow(800, 600, "WindowName", NULL, NULL); 

    if(window == NULL){
        std::cout << "Failed to create GLFW window. " << std::endl; 
        glfwTerminate();
        return -1; 
    }

    glfwMakeContextCurrent(window); 

    glfwSwapInterval(1); // Turns on V-Sync -> syncs to screen refresh rate 

    if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialise GLAD. " << std::endl; 
        return -1; 
    }
    versioncheck(); 

    glViewport(0,0,800,600); 

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); 
    glCompileShader(vertexShader); 

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); 
    glCompileShader(fragmentShader); 
    
    GLuint shaderProgram = glCreateProgram(); 
    
    glAttachShader(shaderProgram, vertexShader); 
    glAttachShader(shaderProgram, fragmentShader); 

    glLinkProgram(shaderProgram); 

    glDeleteShader(vertexShader); 
    glDeleteShader(fragmentShader);  

    GLfloat verticies[] = 
    {
        -0.5f, -0.5f, 0.0f, 
        0.5f, -0.5f, 0.0f, 
        0.5f, 0.5f, 0.0f,
    }; 

    GLuint VAO, VBO; 

    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1, &VBO); 

    glBindVertexArray(VAO); 

    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0); 

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);         // dark green-blueish colour
    glClear(GL_COLOR_BUFFER_BIT); // clears back buffer

    glfwSwapBuffers(window); //swaps the back buffer with the front buffer 
    
    while (!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram); 
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 3);  
        
        processInput(window); 
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }

    glDeleteVertexArrays(1, &VAO); 
    glDeleteBuffers(1, &VBO); 
    glDeleteProgram(shaderProgram); 

    glfwDestroyWindow(window);	// Delete window before ending the program
    glfwTerminate();            // Terminate GLFW before ending the program

    return 0; 
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height); 
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true); 
    }
}

void versioncheck(){
    const GLubyte* vendor   = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version  = glGetString(GL_VERSION);

    std::cout << "GPU Vendor: " << vendor << std::endl;
    std::cout << "Device: " << renderer << std::endl;
    std::cout << "OpenGL Version: " << version << std::endl;
}
