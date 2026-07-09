#include <iostream> 
#include <glad/glad.h> 
#include <GLFW/glfw3.h> 

// forward declarations of functions 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void versioncheck(); 

int main(){
    
    if (!glfwInit()) {                                            // initialises GLFW, 
        std::cout << "Failed to initialise GLFW" << std::endl;    // Returns error if initialisation fails 
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
        glfwTerminate; 
        return -1; 
    }

    versioncheck(); 

    glViewport(0,0,800,600); 
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    

    
    while (!glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.47f, 0.36f, 1.0f);         // dark green-blueish colour
        glClear(GL_COLOR_BUFFER_BIT); // clears back buffer

        glfwSwapBuffers(window); //swaps the back buffer with the front buffer  
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
 