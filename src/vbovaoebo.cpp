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
    if (!glfwInit()) {                                            // initialises GLFW, 
        std::cout << "Failed to initialize GLFW" << std::endl;    // Returns error if initialisation fails 
        return -1;
    } 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // tells GLFW which version of OpenGL we're using 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // same as major  
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Tells GLFW that we're using the core profile, 
    // This means we are only using the modern function 
    GLFWwindow* window = glfwCreateWindow(800, 600, "WindowName", NULL, NULL); 
    // makes the window with a width of 800, height of 600 and a name of WindowName 
    if(window == NULL){  // checks if window is created 
        std::cout << "Failed to create GLFW window. " << std::endl; 
        glfwTerminate();
        return -1; 
    }
    glfwMakeContextCurrent(window); // Introduces the window into the current context
    glfwSwapInterval(1); // Turns on V-Sync -> syncs to screen refresh rate 
    if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialise GLAD. " << std::endl; 
        glfwTerminate(); 
        return -1; 
    }
    versioncheck(); 
    glViewport(0,0,800,600); 
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    
    // Set up for GLFW is finished 
    // glad is initialised 

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

    // Fragment and Vertex shaders set up 
    // copied from triangle.cpp 

    GLfloat verticies[] = 
    {
        -0.5f, -0.5f, 0.0f, 
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
    };      

    GLuint VBO, VAO, EBO; 

    glGenBuffers(1, &VBO); // generates a single VBO handle 
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW); 

    glGenVertexArrays(1, &VAO); // generates a single VAO handle 
    glBindVertexArray(VAO); 
    
    // position attribute 
    glVertexAttribPointer(
        0,                             // attribute index (matches the vertex shader) 
        6,                             //  number of components (x, y, z) 
        GL_FLOAT,                      // data type 
        GL_FALSE,                      // should OGL normalise Values (integers )
        6 * sizeof(float),             // stride: total size of a single vertex (3 components so 3 * float)
        (void*)0                       // offser: where attribute starts 
    ); 
    
    glEnableVertexAttribArray(0); 


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);         // dark green-blueish colour
    glClear(GL_COLOR_BUFFER_BIT); // clears back buffer

    glfwSwapBuffers(window); //swaps the back buffer with the front buffer 
    
    while (!glfwWindowShouldClose(window)){
        // input 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT); 
        glUseProgram(shaderProgram); 
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 3); 
        processInput(window); 
        glfwPollEvents(); 
    }

    glfwDestroyWindow(window);	// Delete window before ending the program
    glfwTerminate();            // Terminate GLFW before ending the program

    return 0; 
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height); 
} // allows windows to be resized 
void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true); 
    }
} // terminates window if esc pressed
void versioncheck(){
    const GLubyte* vendor   = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version  = glGetString(GL_VERSION);

    std::cout << "GPU Vendor: " << vendor << std::endl;
    std::cout << "Device: " << renderer << std::endl;
    std::cout << "OpenGL Version: " << version << std::endl;
} // prints hardware and version in use 
 