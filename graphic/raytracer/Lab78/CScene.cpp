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

    CSphere* sphere = new CSphere({-2.5, 1.3, -3}, 1.0);
    objectList.push_back(sphere);
    sphere = new CSphere({0, 0, 0}, 1.6);
    objectList.push_back(sphere);
    sphere = new CSphere({0, 0, 0}, 5);
    objectList.push_back(sphere);
    
    // add camera, light sources, and objects
    if (camera == 0) {
        cam.eyep = {0.0f, 0.0f, 10.0f};
        cam.lookp = {0.0f, 0.0f, 0.0f};
        cam.up = {0.0f, 1.0f, 0.0f};
        cam.fov = 50.0f;
        cam.width = 500;
        cam.height = 400;
    } else if (camera == 1) {
        cam.eyep = glm::vec3(2.0f, 5.0f, 10.0f);
        cam.lookp = glm::vec3(-2.0f, 1.0f, 0.0f);
        cam.up = glm::vec3(0.0f, 1.0f, 0.0f);
        cam.fov = 50.0f;
        cam.width = 500;
        cam.height = 400;
    }
}

