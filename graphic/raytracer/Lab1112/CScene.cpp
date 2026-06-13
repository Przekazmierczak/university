//
//  CScene.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"

#include<fstream>

/// \fn create(void)
/// \brief Adds components to the scene.
///
void CScene::create(int camera) {
    
    lightList.clear(); // clears vector with the light data
    objectList.clear(); // clears vector of pointers to objects

    // CSphere* sphere = new CSphere({-2.5, 1.3, -3}, 1.0);
    // objectList.push_back(sphere);
    // sphere = new CSphere({0, 0, 0}, 1.6);
    // objectList.push_back(sphere);
    // sphere = new CSphere({0, 0, 0}, 5);
    // objectList.push_back(sphere);

    // CTriangle* triangle = new CTriangle({3.0f, 3.0f, -5.0f}, {-3.0f, 3.0f, -10.0f},{-3.0f, -3.0f, -8.0f});
    // triangle->matAmbient = glm::vec3(1.0f, 1.0f, 1.0f);
    // objectList.push_back(triangle);

    // // T1 (Red)
    // CTriangle* T1 = new CTriangle({-4.0f, 1.5f, 1.0f},{-2.0f, 2.5f, -1.0f},{-3.5f, 3.5f, 0.0f});
    // T1->matAmbient = glm::vec3(0.8f, 0.1f, 0.1f);
    // objectList.push_back(T1);
    //
    // // T2 (Green)
    // CTriangle* T2 = new CTriangle({-0.5f, 1.5f, -1.0f},{0.5f, 1.5f, -1.0f},{0.0f, 3.5f, -6.0f});
    // T2->matAmbient = glm::vec3(0.1f, 0.8f, 0.1f);
    // objectList.push_back(T2);
    //
    // // T3 (Blue)
    // CTriangle* T3 = new CTriangle({2.0f, 2.0f, 0.0f},{4.0f, 1.5f, -2.0f},{2.5f, 3.5f, 2.0f});
    // T3->matAmbient = glm::vec3(0.1f, 0.1f, 0.8f);
    // objectList.push_back(T3);
    //
    // // T4 (Yellow)
    // CTriangle* T4 = new CTriangle({-4.5f, -1.0f, -3.0f},{-3.5f, 0.5f, -4.0f},{-4.2f, 1.0f, -1.0f});
    // T4->matAmbient = glm::vec3(0.8f, 0.8f, 0.1f);
    // objectList.push_back(T4);
    //
    // // T5 (Magenta)
    // CTriangle* T5 = new CTriangle({-1.0f, -1.0f, 1.0f},{1.5f, -0.5f, -1.0f},{0.0f, 1.0f, 0.0f});
    // T5->matAmbient = glm::vec3(0.8f, 0.1f, 0.8f);
    // objectList.push_back(T5);
    //
    // // T6 (Cyan)
    // CTriangle* T6 = new CTriangle({3.0f, -1.0f, -2.0f},{4.5f, 1.0f, -4.0f},{4.5f, -1.0f, -2.0f});
    // T6->matAmbient = glm::vec3(0.1f, 0.8f, 0.8f);
    // objectList.push_back(T6);
    //
    // // T7 (Orange)
    // CTriangle* T7 = new CTriangle({-3.5f, -2.0f, 1.0f},{-2.0f, -3.5f, -1.0f},{-4.0f, -3.5f, -2.0f});
    // T7->matAmbient = glm::vec3(0.9f, 0.5f, 0.1f);
    // objectList.push_back(T7);
    //
    // // T8 (Dark grey)
    // CTriangle* T8 = new CTriangle({-1.5f, -2.5f, -2.0f},{1.5f, -2.0f, -3.0f},{0.0f, -3.5f, -1.0f});
    // T8->matAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
    // objectList.push_back(T8);
    //
    // // T9 (White)
    // CTriangle* T9 = new CTriangle({2.5f, -2.0f, 2.0f},{3.5f, -4.0f, -1.0f},{3.0f, -1.5f, -4.0f});
    // T9->matAmbient = glm::vec3(0.9f, 0.9f, 0.9f);
    // objectList.push_back(T9);
    //
    // // T10 (Grey)
    // CTriangle* T10 = new CTriangle({-7.0f, -2.0f, -15.0f},{2.0f, 5.0f, -10.0f},{-3.0f, 7.0f, -12.0f});
    // T10->matAmbient = glm::vec3(0.7f, 0.7f, 0.7f);
    // objectList.push_back(T10);

    CSphere* sphere = new CSphere({0, 0, 0}, 1.6);
    // 1.4
    // sphere->matAmbient = glm::vec3(0.5f, 0.0f, 0.0f);
    // sphere->matDiffuse = glm::vec3(0.0f, 0.0f, 0.0f);
    // sphere->matSpecular = glm::vec3(0.0f, 0.0f, 0.0f);
    // sphere->matShininess= 30.0f;

    // 1.5
    // sphere->matAmbient = glm::vec3(0.0f, 0.0f, 0.0f);
    // sphere->matDiffuse = glm::vec3(0.7f, 0.0f, 0.0f);
    // sphere->matSpecular = glm::vec3(0.0f, 0.0f, 0.0f);
    // sphere->matShininess= 0.0f;

    // 1.6
    // sphere->matAmbient = glm::vec3(0.0f, 0.0f, 0.0f);
    // sphere->matDiffuse = glm::vec3(0.0f, 0.0f, 0.0f);
    // sphere->matSpecular = glm::vec3(0.7f, 0.7f, 0.7f);
    // sphere->matShininess= 30.0f;

    // 1.7
    sphere->matAmbient = glm::vec3(0.1f, 0.0f, 0.0f);
    sphere->matDiffuse = glm::vec3(0.6f, 0.0f, 0.0f);
    sphere->matSpecular = glm::vec3(0.7f, 0.7f, 0.7f);
    //sphere->matShininess= 30.0f;
    //sphere->matShininess= 10.0f;
    sphere->matShininess= 50.0f;

    objectList.push_back(sphere);

    CLight light;
    light.pos = glm::vec3(-3.0f, -2.0f, 8.0f);
    light.color = glm::vec3(0.6f, 0.6f, 0.6f);
    lightList.push_back(light);

    // add camera, light sources, and objects
    if (camera == 0) {
        cam.eyep = {0.0f, 0.0f, 10.0f};
        cam.lookp = {0.0f, 0.0f, 0.0f};
        cam.up = {0.0f, 1.0f, 0.0f};
        cam.fov = 50.0f;
        cam.width = 500;
        cam.height = 400;
    } else if (camera == 1) {
        cam.eyep = glm::vec3(0.0f, 0.0f, 10.0f);
        cam.lookp = glm::vec3(0.0f, 0.0f, 0.0f);
        cam.up = glm::vec3(0.0f, 1.0f, 0.0f);
        cam.fov = 65.0f;
        cam.width = 800;
        cam.height = 600;
    }
}

