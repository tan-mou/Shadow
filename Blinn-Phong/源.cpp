#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp> 
#include<glm/gtc/type_ptr.hpp>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include"class/VertexBuffer.h"
#include"class/Shader.h"
#include"class/Camera.h"
#include"class/Texture.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


float fov = 45.0f;
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
float lastX = 320.0f;
float lastY = 240.0f;

int esc_counts = 0;
bool esc_status = false;
bool firstmouse = true;

Camera camera1(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwWindowHint(GLFW_REFRESH_RATE, 30);
    glfwSetScrollCallback(window, scroll_callback);


    glewInit();
    GLenum err = glewInit();

    if (err != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    //vertex in here
    float attribute[] = {
        // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
       0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
      -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
       0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
       0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
       0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
       0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
       0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    //floor attribute
    float planeVertices[] = {
        // positions            // normals         // texcoords
         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
        -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
         25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
    };
    float screen[]{
     -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
    };
    unsigned int screenvao;
    glGenVertexArrays(1, &screenvao);
    glBindVertexArray(screenvao);
    VertexBuffer screenvbo(screen, 24 * sizeof(float));
    //bind data to layout
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    unsigned int planevao;
    glGenVertexArrays(1, &planevao);
    glBindVertexArray(planevao);
    VertexBuffer planevbo(planeVertices, 48 * sizeof(float));
    //bind data to layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    unsigned int cubevao;
    glGenVertexArrays(1, &cubevao);
    glBindVertexArray(cubevao);
    VertexBuffer vbo(attribute,  288* sizeof(float));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    unsigned int lightvao;
    glGenVertexArrays(1, &lightvao);
    glBindVertexArray(lightvao);
    vbo.Bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    Texture texture0(GL_TEXTURE0, "texture/wood.jpg", JPG);
    Texture texture1(GL_TEXTURE1, "texture/wood.jpg", JPG);

    Shader cubeshader( "shader/v_vertex.shader","shader/f_cube.shader" );
    Shader lightshader( "shader/v_vertex.shader", "shader/f_light.shader");
    Shader depthshader("shader/v_depth.shader", "shader/f_depth.shader");
    Shader shadowmapshader("shader/v_shadowmap.shader", "shader/f_shadowmap.shader");
    //framebuffer
    unsigned int depth_fbo;
    glGenFramebuffers(1, &depth_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);
    //bind depth texutre to framebuffer
    glActiveTexture(GL_TEXTURE2);
    unsigned int depth_texture;
    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, depth_texture, 0);
    //bind rbo
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 640, 480);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    //bind depth and stencil to rbo
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //light attribute
    float k = 1;
    float n = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //bind depth texture framebuffer
        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, 640, 480);
        glBindFramebuffer(GL_FRAMEBUFFER,depth_fbo);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput(window);
        //light model transformation   
        glm::vec3 light_position(1.0f, 1.0f, 1.0f);
        glm::mat4 trans(1.0f);
        /*trans = glm::translate(trans, glm::vec3(2.0f * sin((float)glfwGetTime()), 0.0f, 2.0f * cos((float)glfwGetTime())));*/
        light_position = glm::vec3(trans * glm::vec4(light_position,1.0f));
        glm::mat4 light_model(1.0f);

        light_model = glm::translate(light_model, light_position);
        light_model = glm::scale(light_model, glm::vec3(0.2f));
        
        glm::mat4 view(1.0f);
        view = camera1.GetView();
        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 1.3f, 0.1f, 100.0f);
        glm::mat4 depth_view(1.0f);
        depth_view = glm::lookAt(light_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 depth_projection(1.0f);
        depth_projection= glm::perspective(glm::radians(45.0f), 1.3f, 0.1f, 100.0f);
        //transformation
        
        //cube model transformation
        glm::mat4 cube_model(1.0f);
        cube_model = glm::rotate(cube_model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //pass1 shadow_map
        
        //cube shader
        glBindVertexArray(cubevao);
        glEnable(GL_POLYGON_OFFSET_FILL);
        shadowmapshader.Use();
        shadowmapshader.setMat4("u_model", cube_model);
        shadowmapshader.setMat4("u_view", depth_view);
        shadowmapshader.setMat4("u_projection", depth_projection);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //draw plane
        glBindVertexArray(planevao);
        shadowmapshader.Use();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        //pass2 
        
        
        
       //draw depth texture
        glViewport(0, 0, 640, 480);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //cube shader
        glBindVertexArray(cubevao);
        cubeshader.Use();
        cubeshader.setMat4("u_model", cube_model);
        cubeshader.setMat4("u_view", view);
        cubeshader.setMat4("u_projection", projection);
        cubeshader.setMat4("shadow_view", depth_view);
        cubeshader.setMat4("shadow_projection", depth_projection);
        cubeshader.setInt("u_texture", 0);
        cubeshader.setInt("u_texture_specular", 1);
        cubeshader.setInt("u_shadowmap",2);
        cubeshader.setVec3("u_camerapos", camera1.GetPos());
        //u_point
        cubeshader.setVec3("u_pointlight.color", glm::vec3(1.0f, 1.0f, 1.0f));
        cubeshader.setVec3("u_pointlight.position", light_position);
        cubeshader.setFloat("u_pointlight.p", 256);
        cubeshader.setFloat("u_pointlight.constant", 1.0f);
        cubeshader.setFloat("u_pointlight.linear", 0.22f);
        cubeshader.setFloat("u_pointlight.quadratic", 0.20f);
        //u_spot
        cubeshader.setVec3("u_spotlight.color", glm::vec3(1.0f, 1.0f, 1.0f));
        cubeshader.setVec3("u_spotlight.position", camera1.GetPos());
        cubeshader.setVec3("u_spotlight.direction", camera1.GetDir());
        cubeshader.setFloat("u_spotlight.cutoff", glm::cos(glm::radians(12.5f)));
        cubeshader.setFloat("u_spotlight.outer_cutoff", glm::cos(glm::radians(17.5f)));
        cubeshader.setFloat("u_spotlight.p", 256);
        cubeshader.setFloat("u_spotlight.constant", 1.0f);
        cubeshader.setFloat("u_spotlight.linear", 0.22f);
        cubeshader.setFloat("u_spotlight.quadratic", 0.20f);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //draw plane
        glBindVertexArray(planevao);
        cubeshader.Use();
        glDrawArrays(GL_TRIANGLES, 0, 6);


         //light shader
        glBindVertexArray(lightvao);
        lightshader.Use();
        lightshader.setMat4("u_model", light_model);
        lightshader.setMat4("u_view", view);
        lightshader.setMat4("u_projection", projection);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);




        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
// camera controll
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 60.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 60.0f)
        fov = 60.0f;
}


void processInput(GLFWwindow* window)
{

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera1.Set_Keyborad_MOVE(deltaTime, GLFW_KEY_W);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera1.Set_Keyborad_MOVE(deltaTime, GLFW_KEY_S);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera1.Set_Keyborad_MOVE(deltaTime, GLFW_KEY_A);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera1.Set_Keyborad_MOVE(deltaTime, GLFW_KEY_D);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera1.Set_Keyborad_MOVE(deltaTime, GLFW_KEY_SPACE);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera1.Set_Keyborad_MOVE(deltaTime, GLFW_KEY_LEFT_CONTROL);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        if (!esc_counts) {
            if (esc_status) {
                esc_status = false;

                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            else {
                esc_status = true;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            esc_counts = 1;
        }


    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
        esc_counts = 0;

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    //intialize

    float sensitivity = 0.05f;
    float xoffset = sensitivity * (xpos - lastX);
    float yoffset = sensitivity * (lastY - ypos);
    lastX = xpos;
    lastY = ypos;
    camera1.Set_Mouse_MOVE(xoffset, yoffset);


}