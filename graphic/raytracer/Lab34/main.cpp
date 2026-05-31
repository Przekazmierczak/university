
#include <iostream>

#include "rt.h"

extern void draw_robot();
extern void ray_matrix();

struct Head {
    glm::vec3 pp{0.0,0.0,1.0};
    float radius = 0.1f;

    void transScale(float tX, float tY, float sX, float sY) {
        glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix
        glm::mat3x3 mScale {{sX,0,0}, {0,sY,0}, {0,0,1}}; // translation matrix

        //PRINT_MAT3(mTrans);
        //PRINT_MAT3(mScale);

        pp = mTrans * mScale * pp;
    }

    void draw(CImage img, glm::vec3 color) {
        img.drawCircle(pp, radius, color);
    }
};

struct BodyPart {
    glm::vec3 pp0{0.5, 0.5, 1};
    glm::vec3 pp1{-0.5, 0.5, 1};
    glm::vec3 pp2{-0.5, -0.5, 1};
    glm::vec3 pp3{0.5, -0.5, 1};

    void transScaleRotate(float tX, float tY, float sX, float sY, float theta) {
        glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix
        glm::mat3x3 mScale {{sX,0,0}, {0,sY,0}, {0,0,1}}; // translation matrix
        glm::mat3x3 mRotate {{cos(theta),sin(theta),0}, {-sin(theta),cos(theta),0}, {0,0,1}}; // translation matrix

        //PRINT_MAT3(mTrans);
        //PRINT_MAT3(mScale);
        //PRINT_MAT3(mRotate);

        // translation of vertices
        pp0 = mTrans * mRotate * mScale * pp0;
        pp1 = mTrans * mRotate * mScale * pp1;
        pp2 = mTrans * mRotate * mScale * pp2;
        pp3 = mTrans * mRotate * mScale * pp3;
    }

    void draw(CImage& img, glm::vec3 color) {
        img.drawLine(pp0, pp1, color);
        img.drawLine(pp1, pp2, color);
        img.drawLine(pp2, pp3, color);
        img.drawLine(pp3, pp0, color);
    }
};

///
int main (int argc, char * const argv[]) {

    // draw_robot();
    ray_matrix();

    return 0;
}

/// Draws robot.
void draw_robot() {
    CImage img(1000, 1000);
    glm::vec3 color(0.7, 0.5, 0.3);

    // Body
    BodyPart body;
    body.transScaleRotate(0.0f, 0.0f, 0.2f, 0.4f,0.0f);
    body.draw(img, color);

    // Left arm
    BodyPart leftArm;
    leftArm.transScaleRotate(0.3f, 0.15f, 0.3f, 0.1f,0.0f);
    leftArm.draw(img, color);

    // Right arm
    BodyPart rightArm;
    rightArm.transScaleRotate(-0.3f, 0.15f, 0.3f, 0.1f,0.0f);
    rightArm.draw(img, color);

    // Left leg
    BodyPart leftLeg;
    leftLeg.transScaleRotate(0.2f, -0.35f, 0.3f, 0.1f,-M_PI / 3);
    leftLeg.draw(img, color);

    // Right leg
    BodyPart rightLeg;
    rightLeg.transScaleRotate(-0.2f, -0.35f, 0.3f, 0.1f,M_PI / 3);
    rightLeg.draw(img, color);

    // Head
    Head head;
    head.transScale(0.0f, 0.35f, 1.0f, 1.0f);
    head.draw(img, color);

    img.save("robot.png");
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();
}

void ray_matrix() {
    for (int i = 0; i < 2; i++) {
        CScene scene;
        scene.create(i);

        glm::mat3 mat;

        CRayTrace::compPrimaryRayMatrix(scene.cam, mat);

        std::cout << "Camera: " << i << std::endl;
        std::cout << "[" << mat[0][0] << " " << mat[1][0] << " " << mat[2][0] << "]" << std::endl;
        std::cout << "[" << mat[0][1] << " " << mat[1][1] << " " << mat[2][1] << "]" << std::endl;
        std::cout << "[" << mat[0][2] << " " << mat[1][2] << " " << mat[2][2] << "]" << std::endl;
    }
}