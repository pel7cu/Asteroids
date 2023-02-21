#pragma once
#include <GameDev2D.h>


const float ANGULAR_VELOCITY = 2.0944f; //In radians (~120 degrees)

const float MAX_SPEED_S = 350.0f;


const float RATE_OF_ACCELERATION = 200.0f;
const float RADIANS = 0.4014f;

const float MAX_RADIANS = 6.28319f;

const float OUTLINE = 4.0f;

//asteroids stuff
const float MAX_SPEED_A = 100.0f;
const float MIN_SPEED_A = 30.0f;
const float MAX_A_SPEED_A = 150.0f;
const float MIN_A_SPEED_A = 50.0f;
const int NUM_OF_ASTEROIDS = 20;//for the vector holding the objects
const int MIN_NUM_OF_SIDES = 7;//  for the number of sides each asteroid can have
const int MAX_NUM_OF_SIDES = 17;//^
const float MIN_RADIUS = 15.0f;//for how far away from center each point is
const float MAX_RADIUS = 27.0f;//^


const float LASER_SPEED = 600.0f;
const int LASER_POOL_SIZE = 20;
const int SHEILD_POOL_SIZE = 10;

const float DIAMOND_ACTIVE_TIME = 20.0f;
const float LASER_ACTIVE_TIME = 2.0f;