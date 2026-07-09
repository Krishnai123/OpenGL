#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h> 
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp> 
#include<glm/gtc/type_ptr.hpp> 

#include"texture.h" 
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h" 
#include"extraFunctions.h" 

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};

int main()
{
	int width = 800; 
	int height = 800;  
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of width by height pixels, naming it "WindowName"
	GLFWwindow* window = glfwCreateWindow(width, height, "WindowName", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialise GLAD. " << std::endl; 
        return -1; 
    }
	
	et::versioncheck();  

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = width, y = height
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, et::framebuffer_size_callback); 

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("C:/OGL/res/vertex/mat.vert.txt", "C:/OGL/res/fragment/tex.frag.txt");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); 
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); 
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); 

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind(); 

	Texture popcat("C:/OGL/res/texture/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); 
	popcat.texUnit(shaderProgram, "tex0", 0); 

	glEnable(GL_DEPTH_TEST);
	float rotation = 0.0f; 
	double prevTime = glfwGetTime(); 

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		popcat.Bind(); 
		// Bind the VAO so OpenGL knows to use it

		double currentTime = glfwGetTime(); 
		if (currentTime - prevTime >= 1.0f / 60.0f){
			rotation += 15.0f ; 
			prevTime = currentTime; 
		}

		glm::mat4 model = glm::mat4(1.0f); 
		glm::mat4 view  = glm::mat4(1.0f); 
		glm::mat4 proj  = glm::mat4(1.0f); 

		glfwGetWindowSize(window, &width, &height); 

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f)); 
		proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f); 

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model"); 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view"); 
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)); 
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj"); 
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj)); 

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/ sizeof(int) , GL_UNSIGNED_INT, 0);
		// lets you esc out of a window 
		et::processInput(window); 
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popcat.Delete(); 
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}
