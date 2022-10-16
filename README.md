# Jetson Reinforcement Learning Robot

This is a C++ project that runs on an Nvidia Jetson, and communicates with an Arduino via I2C. This code implements a first visit Monte Carlo Reinforcement Learning method. As such, this robot makes moves, takes measurements or observations, and after enough data has been gathered for an episode, its begins calculation of its value table. There is an initial guess for the policy.

The Arduino part of this project takes care of driving the PWM to the robot servos and wheel drive motors, it responds to commands from the Jetson robot over I2C and sends its latest sensor data back over as well.