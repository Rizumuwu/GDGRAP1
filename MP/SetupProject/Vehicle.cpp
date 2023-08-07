#include "Vehicle.h"

using namespace vehicle;

Vehicle::Vehicle() {
    this->shader = new Shader(vertPath, fragPath);
    this->model = new ThreeDimensionalModel(meshPath);
    this->InitVert();
    this->texture = new Texture(textPath);
    this->normals = new Normals(normPath);
    this->transform = new Transform();
}

void Vehicle::InitVert() {
    glBindVertexArray(this->model->VAOReference());
    glUseProgram(this->shader->GetShaderProgram());

    glBindBuffer(GL_ARRAY_BUFFER, this->model->VBOReference());
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * this->model->VertexData().size(), this->model->VertexData().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (void*)0);

    GLuint normalsPtr = 3 * sizeof(GLfloat);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (void*)normalsPtr);

    GLuint uvPtr = 6 * sizeof(GLfloat);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (void*)uvPtr);

    GLuint tangentPtr = 8 * sizeof(GLfloat);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (void*)tangentPtr);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Vehicle::Draw(CameraData cameraData, LightData pointLight, LightData directionalLight) {
    glUseProgram(this->shader->GetShaderProgram());

    unsigned int transformLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform->RetrieveModelMatrix()));

    unsigned int viewLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cameraData.view_matrix));

    unsigned int projectionLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraData.projection_matrix));

    GLuint cameraPosLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "cameraPos");
    glUniform3fv(cameraPosLoc, 1, glm::value_ptr(cameraData.camera_pos));

    glActiveTexture(GL_TEXTURE0);
    GLuint tex0Loc = glGetUniformLocation(this->shader->GetShaderProgram(), "tex0");
    glBindTexture(GL_TEXTURE_2D, this->texture->GetTexture());
    glUniform1i(tex0Loc, 0);

    glActiveTexture(GL_TEXTURE1);
    GLuint tex1Loc = glGetUniformLocation(this->shader->GetShaderProgram(), "norm_tex");
    glBindTexture(GL_TEXTURE_2D, this->normals->RetrieveNormals());
    glUniform1i(tex1Loc, 1);

    //point light data
    GLuint pointPosLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "pointLightPos");
    glUniform3fv(pointPosLoc, 1, glm::value_ptr(pointLight.light_position));

    GLuint pointColorLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "pointLightColor");
    glUniform3fv(pointColorLoc, 1, glm::value_ptr(pointLight.light_color));

    GLuint pointAmbientStrLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "pointLightAmbientStr");
    glUniform1f(pointAmbientStrLoc, pointLight.ambient_str);

    GLuint pointAmbientColorLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "pointLightAmbientColor");
    glUniform3fv(pointAmbientColorLoc, 1, glm::value_ptr(pointLight.ambient_color));

    GLuint pointSpecStrLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "pointLightSpecStr");
    glUniform1f(pointSpecStrLoc, pointLight.spec_str);

    GLuint pointSpecPhongLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "pointLightSpecPhong");
    glUniform1f(pointSpecPhongLoc, pointLight.spec_phong);

    GLuint pointIntensityLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "pointLightIntensity");
    glUniform1f(pointIntensityLoc, pointLight.intensity);

    // directional light data
    GLuint dirDirLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "directionalLightDir");
    glUniform3fv(dirDirLoc, 1, glm::value_ptr(directionalLight.light_direction));

    GLuint dirColorLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "directionalLightColor");
    glUniform3fv(dirColorLoc, 1, glm::value_ptr(directionalLight.light_color));

    GLuint dirAmbientStrLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "directionalLightAmbientStr");
    glUniform1f(dirAmbientStrLoc, directionalLight.ambient_str);

    GLuint dirAmbientColorLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "directionalLightAmbientColor");
    glUniform3fv(dirAmbientColorLoc, 1, glm::value_ptr(directionalLight.ambient_color));

    GLuint dirSpecStrLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "directionalLightSpecStr");
    glUniform1f(dirSpecStrLoc, directionalLight.spec_str);

    GLuint dirSpecPhongLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "directionalLightSpecPhong");
    glUniform1f(dirSpecPhongLoc, directionalLight.spec_phong);

    GLuint dirIntensityLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "dirLightIntensity");
    glUniform1f(dirIntensityLoc, directionalLight.intensity);

    //checks for night vision
    GLuint dirNV = glGetUniformLocation(this->shader->GetShaderProgram(), "NV");
    glUniform1i(dirNV, cameraData.isFPS);

    //Draw
    glBindVertexArray(model->VAOReference());
    glDrawArrays(GL_TRIANGLES, 0, model->VertexData().size() / 11);
}

Transform* Vehicle::RetrieveTransform() {
    return this->transform;
}