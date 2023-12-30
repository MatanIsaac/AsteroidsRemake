#pragma once
#include <glm/glm.hpp>

struct SpaceObject
{
    glm::vec2 mPosition;
    glm::vec2 mVelocity;
    float mRotation;
    int mSize;

    SpaceObject(const glm::vec2& pos, const glm::vec2& vel, float rot, int size)
        :   mPosition(pos), mVelocity(vel),mRotation(rot),mSize(size) { }

    SpaceObject() = default;
};