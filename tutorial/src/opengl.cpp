#include "matrix.hpp"
#include "vector.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <stdio.h>
 #include <stdbool.h>
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouseCallback(GLFWwindow *window, double xPos, double yPos);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

camera sceneCamera;

float mouseX = SCR_WIDTH / 2;
float mouseY = SCR_HEIGHT / 2;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Game", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------

    if(glewInit() != GLEW_OK) {
        printf("Failed to initialized GLEW\n");
        return -1;
    }

    glEnable(GL_DEPTH_TEST);


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    GLuint shaderProgram = loadShaderProgram("shaders/main.vert", "shaders/main.frag");
    GLuint texture = loadTextureBMP("textures/brick.bmp");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

    float positions[] = {
		 0.0f,  0.0f,  0.0f, 
		 2.0f,  5.0f, -15.0f, 
		-1.5f, -2.2f, -2.5f,  
		-3.8f, -2.0f, -12.3f,  
		 2.4f, -0.4f, -3.5f,  
		-1.7f,  3.0f, -7.5f,  
		 1.3f, -2.0f, -2.5f,  
		 1.5f,  2.0f, -2.5f, 
		 1.5f,  0.2f, -1.5f, 
		-1.3f,  1.0f, -1.5f,
	};

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexBuffer(0, VBO, 0, 5 * sizeof(float));

    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(0, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
    glVertexAttribBinding(2, 0);
    glEnableVertexAttribArray(2);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    
    int frames = 0;
    glfwSetTime(0);

	float angle = 0;
    vec3 rotation, translation, scaling;

    (void)scaling;


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);

        mat4 view = sceneCamera.getViewMatrix();
        
		view.setUniformMatrix(shaderProgram, "view");
		//std::cout << view << "\n";

        mat4 projection = mat4::perspectiveMatrix(45, (float)SCR_WIDTH / SCR_HEIGHT, 0.1, 100);
        //mat4 projection = mat4::orthoMatrix(-5, 5, -5, 5, 1, 1000);
        projection.setUniformMatrix(shaderProgram, "projection");
        
        ////////////////////////////////////////////////////////////////////

		for(int i = 0; i < 10; i++) {
            mat4 model(1);

			float *translationVals = &positions[3 * i];

			model = mat4::rotationMatrix(vec3(1, 1, 1), i) * model;
			model = mat4::translationMatrix(vec3(translationVals[0], translationVals[1], translationVals[2])) * model;

			model.setUniformMatrix(shaderProgram, "model");
			
			glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			glBindTexture(GL_TEXTURE_2D, texture);

            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0); // no need to unbind it every time 
		}

        ////////////////////////////////////////////////////////////////////
        
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

        frames++;
		angle += 0.0005;

        if(glfwGetTime() >= 1) {
            printf("[+] FPS: %d\n", frames);
            frames = 0;
            glfwSetTime(0);
        }
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
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
	}
	
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		sceneCamera.processKeyPress(FORWARD);	
	}

	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		sceneCamera.processKeyPress(BACKWARD);	
	}

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		sceneCamera.processKeyPress(LEFT);	
	}

	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		sceneCamera.processKeyPress(RIGHT);	
	}

}

void mouseCallback(GLFWwindow *window, double xPos, double yPos) {
	float xOffset = xPos - mouseX;
	float yOffset = mouseY - yPos; //reverse since y-coords are from bottom to top

	mouseX = xPos;
	mouseY = yPos;

	float sensitivity = 0.005f;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	sceneCamera.processMouseMovement(xOffset, yOffset);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
