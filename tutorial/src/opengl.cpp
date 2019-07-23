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

#define FPS 120

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Camera &sceneCamera, double &mouseX, double &mouseY);
void mouseCallback(GLFWwindow *window, double xPos, double yPos);

// settings
const unsigned int SCR_WIDTH = 2500;
const unsigned int SCR_HEIGHT = 1250;

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	Camera sceneCamera;

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
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2, 1, 2, 3,
		4, 5, 6, 5, 6, 7,
		8, 9, 10, 9, 10, 11,
		12, 13, 14, 13, 14, 15,
		16, 17, 18, 17, 18, 19,
		20, 21, 22, 21, 22, 23
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

	(void)positions;

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

    glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

    // render loop
    // -----------
    
    int frames = 0;
    glfwSetTime(0);

	float angle = 0;
    Vec3 rotation, translation, scaling;

    (void)scaling;

	double mouseX, mouseY;

	glfwGetCursorPos(window, &mouseX, &mouseY);

    while (!glfwWindowShouldClose(window)) {
        processInput(window, sceneCamera, mouseX, mouseY);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);

        Mat4 view = sceneCamera.getViewMatrix();
        
		view.setUniformMatrix(shaderProgram, "view");
		//std::cout << view << "\n";

        Mat4 projection = Mat4::perspectiveMatrix(45, (float)SCR_WIDTH / SCR_HEIGHT, 0.1, 100);
        //Mat4 projection = Mat4::orthoMatrix(-5, 5, -5, 5, 1, 1000);
        projection.setUniformMatrix(shaderProgram, "projection");
        
        ////////////////////////////////////////////////////////////////////

		for(int i = 0; i < 10; i++) {
            Mat4 model(1);

			float *translationVals = &positions[3 * i];

			model = Mat4::translationMatrix(Vec3(translationVals[0], translationVals[1], translationVals[2])) * model;

			model.setUniformMatrix(shaderProgram, "model");
			
			glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			glBindTexture(GL_TEXTURE_2D, texture);

            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0); // no need to unbind it every time 
		}

        ////////////////////////////////////////////////////////////////////
        
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

        frames++;
		angle += 0.0005;

		while(glfwGetTime() < ((float)frames) / FPS) { }; //spin lock to limit frame rate

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
void processInput(GLFWwindow *window, Camera &sceneCamera, double &lastMouseX, double &lastMouseY) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
	}

	float movementSpeed = 0.02;
	
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		sceneCamera.move(Camera::LOCAL_FORWARD, movementSpeed);	
	}

	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		sceneCamera.move(Camera::LOCAL_BACKWARD, movementSpeed);
	}

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		sceneCamera.move(Camera::LOCAL_LEFT, movementSpeed);	
	}

	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		sceneCamera.move(Camera::LOCAL_RIGHT, movementSpeed);	
	}

	float mouseSensitivity = 0.002;

	double thisMouseX, thisMouseY;	

	glfwGetCursorPos(window, &thisMouseX, &thisMouseY);

	double mouseDeltaX = thisMouseX - lastMouseX;
	double mouseDeltaY = lastMouseY - thisMouseY;

	sceneCamera.move(Camera::YAW, -mouseDeltaX * mouseSensitivity); //increasing mouse x decreases yaw
	sceneCamera.move(Camera::PITCH, mouseDeltaY * mouseSensitivity); //increasing mouse y increases pitch

	lastMouseX = thisMouseX;
	lastMouseY = thisMouseY;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
