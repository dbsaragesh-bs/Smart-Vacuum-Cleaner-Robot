# Smart Vacuum Cleaner Robot

## Overview

The Smart Vacuum Cleaner Robot is an floor-cleaning robot designed and built as part of the course *Computational Physics* at Amrita Vishwa Vidyapeetham. It is capable of navigating environments, avoiding obstacles, and cleaning surfaces using a motor-driven vacuum mechanism.

This project combines embedded systems, sensor integration, and basic robotics to provide a cost-efficient and functional home cleaning assistant. The robot uses ultrasonic sensing for obstacle avoidance, motor drivers for motion control, and Arduino Uno as the central controller.

---

## Features

- Obstacle detection and avoidance using an ultrasonic sensor
- Autonomous forward movement with turning logic
- Real-time environmental sensing via servo-mounted sensor head
- DC motor-based vacuum mechanism for dust collection
- Smooth acceleration and deceleration
- Manual circuit diagram integration
- Modular and upgradable design

---

## Project Demo

> **Demo Video:**  
> *[Add link here]*

---

## Circuit Diagram

> **Circuit Diagram Image:**  
> *[Insert circuit diagram here]*

---

## Components Used

- Arduino Uno
- L293D Motor Driver Shield
- Ultrasonic Sensor (HC-SR04)
- Servo Motor
- 4 × DC Geared Motors (High Torque)
- Vacuum motor with fan
- Two acrylic sheets (chassis)
- Wheels and rubber tires
- 9V Batteries (x2)

---

## Working Principle

1. **Initialization**: Robot checks for obstacles ahead using an ultrasonic sensor.
2. **Movement**: If no obstacle is detected within the stop distance, it moves forward.
3. **Obstacle Avoidance**: On detection, the robot decelerates, analyzes surroundings using a servo-mounted sensor, and turns in the direction with more free space.
4. **Vacuuming**: A separate vacuum fan continuously collects dust from the floor during motion.
5. **Loop**: The process repeats, making it an efficient cleaning cycle.

---

## Arduino Code

The robot is programmed using the Arduino IDE. You can find the complete source code in the [source_code.ino](source_code.ino) file of this repository.

---

## Future Scope

- Integration with smart home ecosystems
- Advanced path planning and room mapping using AI/ML
- Multi-room and multi-floor navigation
- Self-cleaning mechanisms and automatic dirt disposal
- Voice control and mobile app interface
- Improved suction mechanism and adaptive cleaning

---

## Team Members
- [Raghav N](https://github.com/Rag-795)
- [Hari Heman V K](https://github.com/HXMAN76)
- [Dev Bala Saragesh](https://github.com/dbsaragesh-bs)
- [Ghanasree](https://github.com/Ghanasree-S)
---
