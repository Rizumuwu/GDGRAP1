// SetupProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <Windows.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h";

#include <string>
#include <iostream>

//GLM HEADERS//
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

//float x_mod = 0;
//float y_mod = 0;

// GLM MATRIX VARIABLES //
float trans_x = 0, trans_y = 0, trans_z = -2;
float scale_x = 2, scale_y = 2, scale_z = 2;
float axis_x = 1, axis_y = 1, axis_z = 1;
float theta = 60;

// END OF GLM VARIABLES //

bool spacePressed = false;
bool flap = false;
float senOne = 0;
float senTwo = 0;

void Key_CallBack(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mod
)
{
    if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
        trans_x += 0.01f;
    }
    else if (key == GLFW_KEY_A && action == GLFW_REPEAT) {
        trans_x -= 0.01f;
    }
    else if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
        trans_y += 0.01f;
    }
    else if (key == GLFW_KEY_S && action == GLFW_REPEAT) {
        trans_y -= 0.01f;
    }
    else if (key == GLFW_KEY_Z && action == GLFW_REPEAT) {
        trans_z -= 0.01f;
    }
    else if (key == GLFW_KEY_X && action == GLFW_REPEAT) {
        trans_z += 0.01f;
    }
    else if (key == GLFW_KEY_E && action == GLFW_REPEAT) {
        scale_x += 0.1f;
        scale_y += 0.1f;
        scale_z += 0.1f;

    }
    else if (key == GLFW_KEY_Q && action == GLFW_REPEAT) {
        scale_x -= 0.1f;
        scale_y -= 0.1f;
        scale_z -= 0.1f;
    }
    else if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT) {
        axis_x = 0.0f;
        axis_y = 1.0f;
        axis_z = 0.0f;

        theta -= 2.0f;
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT) {
        axis_x = 0.0f;
        axis_y = 1.0f;
        axis_z = 0.0f;

        theta += 2.0f;
    }
    else if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {
        axis_x = 1.0f;
        axis_y = 0.0f;
        axis_z = 0.0f;

        theta -= 2.0f;
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT) {
        axis_x = 1.0f;
        axis_y = 0.0f;
        axis_z = 0.0f;

        theta += 2.0f;
    }
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        axis_x += 2.0f;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        axis_y += 2.0f;
    }
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        axis_z += 2.0f;
    }
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
        axis_x -= 2.0f;
    }
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
        axis_y -= 2.0f;
    }
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
        axis_z -= 2.0f;
    }
    
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        spacePressed = true;
    }

    if (key == GLFW_KEY_J && action == GLFW_PRESS) {
        flap = true;
    }
}


int main(void)
{
    float window_height = 600.0f;
    float window_width = 600.0f;

    GLFWwindow* window;
    float i = 0;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(600, 600, "Miguel Paglinawan", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();
    
    // SCREEN SPACE STUFF //
    /*
    glViewport(0,   // min x
        0,          // min y
        600,    // width
        600);   // height
    */
    // END OF SCREEN SPACE STUFF //

    glfwSetKeyCallback(window, Key_CallBack);

    std::fstream vertSrc("Shaders/sample.vert");
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    std::fstream fragSrc("Shaders/sample.frag");
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &v, NULL);
    glCompileShader(vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);

    glLinkProgram(shaderProgram);

    std::string path = "3D/bunny.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str()
    );

    std::vector<GLuint> mesh_indices;
    
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        mesh_indices.push_back(
            shapes[0].mesh.indices[i].vertex_index
        );
    }

    GLfloat vertices[]{
        //x    y    z
        0.f, 0.5f, 0.f,     // point 1
        -0.5f, -0.5f, 0.f,  // point 2
        0.5f, -0.5f, 0.f    // point 3
    };

    GLuint indices[]{
        0, 1, 2
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT) * attributes.vertices.size(),
        &attributes.vertices[0],
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,  // 0 == position
        3,  // xyz
        GL_FLOAT, // what array is type of
        GL_FALSE,
        3 * sizeof(GL_FLOAT),
        (void*)0
    );

    //enable index 0
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLuint) * mesh_indices.size(),
        mesh_indices.data(),
        GL_STATIC_DRAW
    );

    // tells opengl that you're done with VAO and VBO;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // GLM MATRICES //
    glm::mat4 identity_matrix = glm::mat4(1.0f);
    
    
    /*
    glm::mat4 projection_matrix = glm::ortho(-2.0f,    // left most point
                                        2.0f,    // right most point
                                        -2.0f,    // bottom most point
                                          2.0f,    // top most point
                                           -1.0f,   // nearest point
                                             1.0f);  // farthest point
    */

    glm::mat4 projection_matrix = glm::perspective(glm::radians(60.0f),  // FOV
        window_height / window_width,   // Aspect Ratio
        0.1f,   // Near
        100.0f);    // Far

    int check = 0;
    int sideways = 0;
    bool direction = true;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /*
        unsigned int xLoc = glGetUniformLocation(shaderProgram, "x");
        glUniform1f(xLoc, x_mod);

        unsigned int yLoc = glGetUniformLocation(shaderProgram, "y");
        glUniform1f(yLoc, y_mod);
        */

        // JUMP //
        if (spacePressed) {

            if (senOne <= 50) {
                trans_x -= 0.01f;
                trans_y += 0.05f;
                senOne++;
                Sleep(3);
            }

            if (senOne > 50) {
                if (senTwo <= 50) {
                    trans_x -= 0.01f;
                    trans_y -= 0.05f;
                    senTwo++;
                    Sleep(3);
                }
            }

            if (senOne > 50 && senTwo > 50) {
                spacePressed = false;
                senOne = 0;
                senTwo = 0;
            }
        }
        
        /*
        // FLAPPER //
        if (!flap) {
            if (check > 15) {
                check--;
                trans_y += 0.005f;
            }
            else if (check > 10) {
                check--;
                trans_y += 0.003f;
            }
            else if (check > 5) {
                check--;
                trans_y += 0.001f;
            }
            else if (check > 0) {
                check--;
                trans_y += 0.0007f;
            }
            else
                trans_y -= 0.01f;
        }
        else if (flap) {
            if (check < 3) {
                trans_y += 0.06f;
                check++;
            }
            else {
                flap = false;
                check = 20;
            }
        }

        if (direction) {
            trans_x += 0.01f;
            sideways++;

            if (sideways >= 50)
                direction = false;
        }
        else if (!direction) {
            trans_x -= 0.01f;
            sideways--;

            if (sideways <= -50)
                direction = true;
        }
        */

        // GLM STUFF //
        glm::mat4 transformation_matrix = glm::translate(identity_matrix, glm::vec3(trans_x, trans_y, trans_z));

        transformation_matrix = glm::scale(transformation_matrix, glm::vec3(scale_x, scale_y, scale_z));

        transformation_matrix = glm::rotate(transformation_matrix, glm::radians(theta), glm::vec3(axis_x, axis_y, axis_z));

        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, //Addess of transform variable
            1,                           // how many matrices to assign
            GL_FALSE,
            glm::value_ptr(transformation_matrix));

        unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, //Addess of transform variable
            1,                           // how many matrices to assign
            GL_FALSE,
            glm::value_ptr(projection_matrix));

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glDrawElements(
            GL_TRIANGLES,
            mesh_indices.size(),
            GL_UNSIGNED_INT,
            0
        );

        /*
        glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(0.3f, 0.2f);
        glVertex2f(0.2f, -0.1f);
        glVertex2f(-0.2f, -0.1);
        glVertex2f(-0.3f, 0.2f);
        glEnd();
        */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
