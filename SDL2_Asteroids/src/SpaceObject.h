#pragma once
#include <glm/glm.hpp>

// A simple struct to represent a space object
// space object is the commonality between the ship and the asteroids
// both need a position, velocity etc.. .

struct SpaceObject
{
    // The space object's position
    glm::vec2 mPosition;
    // The space object's velocity  
    glm::vec2 mVelocity;
    // The space object's rotation
    float mRotation;
    // The space object's size
    int mSize;

    // The space object constructor
    SpaceObject(const glm::vec2& pos, const glm::vec2& vel, float rot, int size)
        :   mPosition(pos), mVelocity(vel),mRotation(rot),mSize(size) { }

    // The space object default constructor
    SpaceObject() = default;
};