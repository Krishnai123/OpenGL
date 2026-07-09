#include "extraFunctions.h"

void rd::randseed() { 
    std::srand(static_cast<unsigned int>(std::time(nullptr))); 
}

int rd::ransign(){
    int x = rand() % 2; 
    if (x == 0){
        return -1;
    } 
    return x; 
}

int rd::randIntSign(int ub){
    int x = rand() % (ub+1); 
    return (x * ransign()); 
}

float rd::randsignf(){ 
    float x = static_cast <float> (rand())/static_cast <float> (RAND_MAX) ; 
    return (x * ransign()); 
}

float rd::randf(){
    float x = static_cast<float>(rand())/ static_cast <float> (RAND_MAX); 
    return x; 
}
float rd::randfb(float upper_bound){
    float x = static_cast <float> (rand())/static_cast <float> (RAND_MAX/upper_bound) ; 
    return (x * ransign()); 
}

void et::framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height); 
} // allows windows to be resized 

void et::processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true); 
    }
} // terminates window if esc pressed

void et::versioncheck(){
    const GLubyte* vendor   = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version  = glGetString(GL_VERSION);

    std::cout << "GPU Vendor: " << vendor << std::endl;
    std::cout << "Device: " << renderer << std::endl;
    std::cout << "OpenGL Version: " << version << std::endl;
} // prints hardware and version in use 