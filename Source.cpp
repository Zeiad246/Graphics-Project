#include "Angel.h"
#include "Sphere.h"
#include "glm/glm.hpp"
#include <glm/ext.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Sphere sphere1(0.5f); 
Sphere sphere2(0.5f);
Sphere sphere3(0.5f);
Sphere sphere4(0.5f);
Sphere sphere5(0.5f);
Sphere sphere6(0.5f);
Sphere sphere7(0.5f);
Sphere sphere8(0.5f);
Sphere sphere9(0.5f);

typedef Angel::vec4 color4;
typedef Angel::vec4 point4;

GLuint vao, vbo1, vbo2, vbo3, vbo4, vbo5, vbo6, vbo7, vbo8, vbo9,
ibo1, ibo2, ibo3, ibo4, ibo5, ibo6, ibo7, ibo8, ibo9,
vPosition, vNormal, vTexture, modelUnifrom, modelAttrib, viewAttrib, projectionAttrib, colorAttribute, cameraUniform
, texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9, texture10;
GLuint program;
glm::mat4 model;

glm::vec3 cameraPos, cameraTarget, cameraDirection, cameraRight, cameraUp, cameraFront;
glm::mat4 view, projection;

float speed = 0.1f, yaw = -90.0f;
float translate = 0.f, scale = 0.f,  rotate =  0.f;
float factor = 0.00025;

void initLight()
{

    point4 light_direction(0.0, 0.0, -1.0, 0.0);

    color4 light_ambient(1.0, 1.0, 1.0, 1.0);
    color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
    color4 light_specular(1.0, 1.0, 1.0, 1.0);

    float material_shininess = 100.f;
    color4 material_ambient(0.5, 0.5, 0.5, 1.0);
    color4 material_diffuse(0.5, 0.5, 0.5, 1.0);
    color4 material_specular(0.5, 0.5, 0.5, 1.0);

    glUniform4fv(glGetUniformLocation(program, "directionalLight.ambient"), 1, light_ambient);
    glUniform4fv(glGetUniformLocation(program, "directionalLight.diffuse"), 1, light_diffuse);
    glUniform4fv(glGetUniformLocation(program, "directionalLight.specular"), 1, light_specular);
    glUniform4fv(glGetUniformLocation(program, "directionalLight.direction"), 1, light_direction);

    glUniform4fv(glGetUniformLocation(program, "material.ambient"), 1, material_ambient);
    glUniform4fv(glGetUniformLocation(program, "material.diffuse"), 1, material_diffuse);
    glUniform4fv(glGetUniformLocation(program, "material.specular"), 1, material_specular);
    glUniform1f(glGetUniformLocation(program, "material.shininess"), material_shininess);

    //point4 light_direction(0.0, 0.0, -1.0, 0.0);
    //point4 light_poisiton1(0.5f, 0.f, 0.f, 0.f);
    //point4 light_poisiton2(-0.5f, 0.f, 0.f, 0.f);

    //color4 light_ambient(0.5, 0.5, 0.5, 1.0);
    //color4 light_diffuse(1.0, 1.0, 0.0, 1.0);
    //color4 light_specular(1.0, 1.0, 1.0, 1.0);

    //float light_constant = 1.f;
    //float light_linear = 0.07f;
    //float light_quadratic = 0.017f;

    //float material_shininess = 100.f;
    //color4 material_ambient(0.0, 0.5, 0.5, 1.0);
    //color4 material_diffuse(0.0, 1.0, 1.0, 1.0);
    //color4 material_specular(0.0, 1.0, 1.0, 1.0);

    //glUniform4fv(glGetUniformLocation(program, "directionalLight.ambient"), 1, light_ambient);
    //glUniform4fv(glGetUniformLocation(program, "directionalLight.diffuse"), 1, light_diffuse);
    //glUniform4fv(glGetUniformLocation(program, "directionalLight.specular"), 1, light_specular);
    //glUniform4fv(glGetUniformLocation(program, "directionalLight.direction"), 1, light_direction);

    //glUniform1f(glGetUniformLocation(program, "pointLights[0].constant"), light_constant);
    //glUniform1f(glGetUniformLocation(program, "pointLights[0].linear"), light_linear);
    //glUniform1f(glGetUniformLocation(program, "pointLights[0].quadratic"), light_quadratic);
    //glUniform4fv(glGetUniformLocation(program, "pointLights[0].ambient"), 1, light_ambient);
    //glUniform4fv(glGetUniformLocation(program, "pointLights[0].diffuse"), 1, light_diffuse);
    //glUniform4fv(glGetUniformLocation(program, "pointLights[0].specular"), 1, light_specular);
    //glUniform4fv(glGetUniformLocation(program, "pointLights[0].position"), 1, light_poisiton1);

    //glUniform1f(glGetUniformLocation(program, "pointLights[1].constant"), light_constant);
    //glUniform1f(glGetUniformLocation(program, "pointLights[1].linear"), light_linear);
    //glUniform1f(glGetUniformLocation(program, "pointLights[1].quadratic"), light_quadratic);
    //glUniform4fv(glGetUniformLocation(program, "pointLights[1].ambient"), 1, light_ambient);
    //glUniform4fv(glGetUniformLocation(program, "pointLights[1].diffuse"), 1, light_diffuse);
    //glUniform4fv(glGetUniformLocation(program, "pointLights[1].specular"), 1, light_specular);
    //glUniform4fv(glGetUniformLocation(program, "pointLights[1].position"), 1, light_poisiton2);

    //glUniform4fv(glGetUniformLocation(program, "material.ambient"), 1, material_ambient);
    //glUniform4fv(glGetUniformLocation(program, "material.diffuse"), 1, material_diffuse);
    //glUniform4fv(glGetUniformLocation(program, "material.specular"), 1, material_specular);
    //glUniform1f(glGetUniformLocation(program, "material.shininess"), material_shininess);
}

void initTexture()
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    
    unsigned char* data1 = stbi_load("8k_mercury.jpg", &width, &height, &channels, 0);

    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    stbi_image_free(data1);


    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data2 = stbi_load("8k_venus_surface.jpg", &width, &height, &channels, 0);

    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data2);

    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    unsigned char* data3 = stbi_load("8k_earth_daymap.jpg", &width, &height, &channels, 0);

    if (data3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    stbi_image_free(data3);

    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    unsigned char* data4 = stbi_load("8k_mars.jpg", &width, &height, &channels, 0);

    if (data4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    stbi_image_free(data4);

    glGenTextures(1, &texture5);
    glBindTexture(GL_TEXTURE_2D, texture5);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    unsigned char* data5 = stbi_load("8k_jupiter.jpg", &width, &height, &channels, 0);

    if (data5)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data5);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    stbi_image_free(data5);

    glGenTextures(1, &texture6);
    glBindTexture(GL_TEXTURE_2D, texture6);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    unsigned char* data6 = stbi_load("8k_saturn.jpg", &width, &height, &channels, 0);

    if (data6)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data6);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    stbi_image_free(data6);

    glGenTextures(1, &texture7);
    glBindTexture(GL_TEXTURE_2D, texture7);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    unsigned char* data7 = stbi_load("8k_saturn_ring_alpha.png", &width, &height, &channels, 0);

    if (data7)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data7);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    stbi_image_free(data7);

    glGenTextures(1, &texture8);
    glBindTexture(GL_TEXTURE_2D, texture8);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    unsigned char* data8 = stbi_load("2k_uranus.jpg", &width, &height, &channels, 0);

    if (data8)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data8);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    stbi_image_free(data8);

    glGenTextures(1, &texture9);
    glBindTexture(GL_TEXTURE_2D, texture9);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    unsigned char* data9 = stbi_load("2k_neptune.jpg", &width, &height, &channels, 0);

    if (data9)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data9);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    stbi_image_free(data9);

    glGenTextures(1, &texture10);
    glBindTexture(GL_TEXTURE_2D, texture10);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    unsigned char* data10 = stbi_load("8k_sun.jpg", &width, &height, &channels, 0);

    if (data10)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data10);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    stbi_image_free(data10);
}

// OpenGL initialization
void init()
{
    // Create a vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and initialize a vertex buffer object
    glGenBuffers(1, &vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sphere1.getInterleavedVertexSize(), sphere1.getInterleavedVertices(), GL_STATIC_DRAW);
 
    // Create and initialize an index buffer object
    glGenBuffers(1, &ibo1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere1.getIndexSize(), sphere1.getIndices(), GL_STATIC_DRAW);

    // Load shaders and use the resulting shader program
    program = InitShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    // set up vertex arrays
    vPosition = glGetAttribLocation(program, "vertexPosition");
    glEnableVertexAttribArray(vPosition);
    

    vNormal = glGetAttribLocation(program, "vertexNormal");
    glEnableVertexAttribArray(vNormal);

    vTexture = glGetAttribLocation(program, "vertexTexture");
    glEnableVertexAttribArray(vTexture);

    modelAttrib = glGetUniformLocation(program, "model");
    viewAttrib = glGetUniformLocation(program, "view");
    projectionAttrib = glGetUniformLocation(program, "projection");
    cameraUniform = glGetUniformLocation(program, "camera");

    /*glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sphere1.getInterleavedStride(), BUFFER_OFFSET(0));

    
    //glEnableVertexAttribArray(vPosition);
    //glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    //glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
    //glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sphere1.getInterleavedStride(), BUFFER_OFFSET(0));


    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sphere2.getInterleavedStride(), BUFFER_OFFSET(0));*/

  //  colorAttribute = glGetUniformLocation(program, "color");

    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraDirection = glm::normalize(cameraPos - cameraTarget);
    cameraRight = glm::normalize(glm::cross(glm::vec3(0.f, 1.0f, 0.0f), cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    projection = glm::perspective(glm::radians(45.f), 512.0f / 512.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionAttrib, 1, GL_FALSE, glm::value_ptr(projection));

    initLight();
    initTexture();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display(void)
{

    colorAttribute = glGetUniformLocation(program, "color");

    //
    glUniform3fv(cameraUniform, 1, glm::value_ptr(cameraPos));

    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sphere1.getInterleavedStride(),
        BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, sphere1.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, sphere1.getInterleavedStride(), (void*)(6 * sizeof(float)));


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture1);
    model = glm::mat4(1.0f);
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    model = glm::translate(model, glm::vec3(0.15f, 0.0f, -0.3f));
    model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));

    glUniform4fv(colorAttribute, 1, Angel::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, texture10);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));

    glUniform4fv(colorAttribute, 1, Angel::vec4(1.0f, 1.0f, 0.0f, 1.0f));

    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, texture2);
    model = glm::mat4(1.0f);
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));

    glUniform4fv(colorAttribute, 1, Angel::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, texture3);
    model = glm::mat4(1.0f);
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    model = glm::translate(model, glm::vec3(0.26f, 0.0f, 0.2f));
    model = glm::scale(model, glm::vec3(0.045f, 0.045f, 0.045f));
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));

    glUniform4fv(colorAttribute, 1, Angel::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, texture4);
    model = glm::mat4(1.0f);
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.2f));
    model = glm::scale(model, glm::vec3(0.035f, 0.035f, 0.035f));
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));

    glUniform4fv(colorAttribute, 1, Angel::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, texture5);
    model = glm::mat4(1.0f);
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    model = glm::translate(model, glm::vec3(0.5f, 0.0f, -0.4f));
    model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));

    glUniform4fv(colorAttribute, 1, Angel::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, texture6);
    model = glm::mat4(1.0f);
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    model = glm::translate(model, glm::vec3(-0.7f, 0.0f, 0.7f));
    model = glm::scale(model, glm::vec3(0.13f, 0.13f, 0.13f));
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));

    glUniform4fv(colorAttribute, 1, Angel::vec4(0.0f, 0.3f, 0.6f, 1.0f));

    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, texture7);
    model = glm::mat4(1.0f);
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    model = glm::translate(model, glm::vec3(-0.7f, 0.0f, 0.7f));
    model = glm::scale(model, glm::vec3(0.18f, 0.013f, 0.18f));
    model = glm::rotate(model, rotate, glm::vec3(1.0, 1.0, 0.0));
    glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));

    glUniform4fv(colorAttribute, 1, Angel::vec4(0.5f, 1.0f, 0.75f, 1.0f));

    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, texture8);
    model = glm::mat4(1.0f);
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    model = glm::translate(model, glm::vec3(0.85f, 0.0f, -0.85f));
    model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));

    glUniform4fv(colorAttribute, 1, Angel::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, texture9);
    model = glm::mat4(1.0f);
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.5f));
    model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
    model = glm::rotate(model, rotate, glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));

    glUniform4fv(colorAttribute, 1, Angel::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);


    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(viewAttrib, 1, GL_FALSE, glm::value_ptr(view));

    


    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 033:
        exit(EXIT_SUCCESS);
        break;
    case 'r':
        cameraPos += speed * cameraUp;
        break;
    case 'f':
        cameraPos -= speed * cameraUp;
        break;
    case 'w':
        cameraPos += speed * cameraFront;
        break;
    case 's':
        cameraPos -= speed * cameraFront;
        break;
    case 'a':
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
        break;
    case 'd':
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
        break;
    case 'q':
        yaw -= 1.0f;
        cameraDirection.x = glm::cos(glm::radians(yaw));
        cameraDirection.z = glm::sin(glm::radians(yaw));
        cameraFront = glm::normalize(cameraDirection);
        break;
    case 'e':
        yaw += 1.0f; //we move around the y, then we update the x and z positions
        cameraDirection.x = glm::cos(glm::radians(yaw));
        cameraDirection.z = glm::sin(glm::radians(yaw));
        cameraFront = glm::normalize(cameraDirection);
        break;
    }
}

void idle() {
    translate += factor;
    scale += factor;
    rotate += factor;

    /*if (translate > 5.0f) {
        factor = -0.0005;
    }
    else if (translate < -5.0f) {
        factor = 0.0005;
    }*/

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitContextVersion(3, 2);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Sphere");

    glewInit();

    init();

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutIdleFunc(idle);


    glutMainLoop();
    return 0;
}
