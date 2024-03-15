#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <windows.h>
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1f, 1f, 1f, 1.0f);\n"
"}\n\0";



int main() {
	POINT cp;
	double a=0;
	int s = 0;
	double b = 0;
	int aa = 1920/2;
	double var_ver = 0.2f;
	int INTERVAL = 1;
	double speed = INTERVAL*0.001f;
	double c_time;



	double y_tranform = 0;
	double y_speed = 0;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "opengl application", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(INTERVAL);

	gladLoadGL();
	glViewport(0, 0, 1920, 1080);
	
	GLfloat vertices[] = {
		0.3f,0.0f, 0.0f,

		-0.3f,0.0f, 0.0f,//

		-0.3f,0.6f, 0.0f,


		0.3f,0.6f, 0.0f,//

		0.3f,0.0f, 0.0f,

		-0.3f,0.6f, 0.0f
	};


	int getArrayLength = sizeof(vertices) / sizeof(int);

	//initial vert transform
			//x transform
	for (int i = 0; i <= getArrayLength; i = i + 3) {
		vertices[i] = vertices[i] + 0.0f;
	}
	//y transform
	for (int i = 1; i <= getArrayLength + 1; i = i + 3) {

		vertices[i] = vertices[i] + 0.3f;
	}
	//z transform
	for (int i = 2; i <= getArrayLength+2; i = i + 3) {

		vertices[i] = vertices[i] + 0.00f;
	}

	int vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexshader);

	int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentshader);

	int shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vertexshader);
	glAttachShader(shaderprogram, fragmentshader);

	glLinkProgram(shaderprogram);

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);



	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		
		clock_t start = clock();
		
		

		
		//cursor poss
		GetCursorPos(&cp);
		a = cp.x;
		b = -(cp.y);

		

		//vert transform
		    //x transform
		for (int i = 0; i <= getArrayLength; i = i + 3) {
			vertices[i] = vertices[i] + 0.0f;
		}
		    //y transform
		for (int i = 1; i <= getArrayLength+1; i = i + 3) {
			

			

			if (-vertices[i] < 0.5f ) {

				y_speed = y_speed - 0.0001f;
				
			}

			vertices[i] = vertices[i] + y_speed;
		}
		    //z transform
		for (int i = 2; i <= getArrayLength+2; i = i + 3) {

			vertices[i] = vertices[i] + 0.00f;
		}


		
		

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
		glUseProgram(shaderprogram);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//std::cout << a/1920 << " , " << cp.y << std::endl;

		clock_t end = clock();

		c_time = (double)(end - start) / 1000;
		
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
