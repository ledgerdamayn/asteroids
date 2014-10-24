#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SCREEN_SIZE 200
#define TIMER_FREQUENCY 50 // 20 times/sec

#define ASTEROID_BASE_SIZE 20 // Percent
#define ASTEROID_SIZE_RANGE 5 // Percent
#define ASTEROID_BASE_SPIN 180
#define ASTEROID_SPIN_RANGE 90
#define ASTEROID_BASE_SPEED 25 // Percent of screen/sec
#define ASTEROID_SPEED_RANGE 10
#define ASTEROID_MEDIUM_RATIO 0.75f // Relative to large asteroid
#define ASTEROID_SMALL_RATIO 0.5f // Relative to large asteroid
#define ASTEROID_FRAGMENT_COUNT 2
#define ASTEROID_PERTURB 75

#define SHIP_SIZE 5
#define SHIP_ACCELERATION 15
#define SHIP_SPEED_DECAY 0.9
#define SHIP_SPEED_LAMBDA 0.0001
#define SHIP_ROTATION_SPEED 180 // Degrees per second

#define LASER_DURATION 3000
#define MAX_LASERS 4
#define LASER_BUFFER 10
#define LASER_SPEED 100

#define LARGE 0
#define MEDIUM 1
#define SMALL 2

#endif