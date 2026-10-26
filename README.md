# SnappyXOExamples

Example sketches for SnappyXO V3 robotics kits. The version follows the kit: 3.x is for the V3 kits.

## Installation

Install via the Arduino Library Manager (search for **SnappyXOExamples**) or download and place the folder in your Arduino `libraries/` directory.

The Library Manager also installs the libraries the sketches use: **SnappyXOShield** 1.0 or later, **MicroBlue** 2.1 or later, **Servo** and **IRremote**. If you install by hand, install those too.

## What you need

- **Board:** Arduino UNO R4 WiFi
- **Shield:** SnappyXO Motor Shield v3. Each sketch starts with `SnappyXOShield shield(SnappyXOShield::V3);`
- **Bluetooth sketches:** the MicroBlue app 2.0 or later, which sends a heartbeat (Settings > Send heartbeat, on by default). The robot stops when the phone disconnects or the heartbeat stops.

## Upgrading from 3.0.0

Version 3.1.0 uses SnappyXOShield 1.0, where the motor functions moved into the `SnappyXOShield` class (`shield.forward()` instead of `forward()`). The 3.0.0 sketches don't compile with SnappyXOShield 1.0. Update both libraries together. To keep using sketches you wrote for 3.0.0, follow SnappyXOShield's ["Upgrading from 0.x"](https://github.com/snappyxo/SnappyXOShield#upgrading-from-0x) table, or install SnappyXOShield 0.2.1 from the Library Manager.

## Examples

After installation, open examples from:

**File > Examples > SnappyXOExamples > V3 > \<sketch name\>**

Available V3 examples:

- [Advanced_Walking_Robot](examples/V3/Advanced_Walking_Robot/Advanced_Walking_Robot.ino)
- [Automatic_Catapult](examples/V3/Automatic_Catapult/Automatic_Catapult.ino)
- [Bluetooth_4_Bar_Steering_Car](examples/V3/Bluetooth_4_Bar_Steering_Car/Bluetooth_4_Bar_Steering_Car.ino)
- [Bluetooth_Controlled_Light_Up_Wheeled_Robot](examples/V3/Bluetooth_Controlled_Light_Up_Wheeled_Robot/Bluetooth_Controlled_Light_Up_Wheeled_Robot.ino)
- [Bluetooth_Controlled_Wheeled_Robot](examples/V3/Bluetooth_Controlled_Wheeled_Robot/Bluetooth_Controlled_Wheeled_Robot.ino)
- [Bluetooth_Excavator_Robot](examples/V3/Bluetooth_Excavator_Robot/Bluetooth_Excavator_Robot.ino)
- [Gesture_Driven_Bot](examples/V3/Gesture_Driven_Bot/Gesture_Driven_Bot.ino)
- [IR_4_Bar_Steering_Car](examples/V3/IR_4_Bar_Steering_Car/IR_4_Bar_Steering_Car.ino)
- [IR_Excavator_Robot](examples/V3/IR_Excavator_Robot/IR_Excavator_Robot.ino)
- [IR_Grabber_Car](examples/V3/IR_Grabber_Car/IR_Grabber_Car.ino)
- [Light_Following_Car](examples/V3/Light_Following_Car/Light_Following_Car.ino)
- [Light_Up_Obstacle_Avoiding_Wheeled_Robot](examples/V3/Light_Up_Obstacle_Avoiding_Wheeled_Robot/Light_Up_Obstacle_Avoiding_Wheeled_Robot.ino)
- [Light_Up_Wheeled_Robot](examples/V3/Light_Up_Wheeled_Robot/Light_Up_Wheeled_Robot.ino)
- [Obstacle_Avoiding_Wheeled_Robot](examples/V3/Obstacle_Avoiding_Wheeled_Robot/Obstacle_Avoiding_Wheeled_Robot.ino)
- [PIR_Door_Sensor](examples/V3/PIR_Door_Sensor/PIR_Door_Sensor.ino)
- [Punch_Buggy](examples/V3/Punch_Buggy/Punch_Buggy.ino)
- [Race_Car_with_Speed_Sensors](examples/V3/Race_Car_with_Speed_Sensors/Race_Car_with_Speed_Sensors.ino)
- [Ram_Mobile](examples/V3/Ram_Mobile/Ram_Mobile.ino)
- [Reflex_Challenge___SnappyXO_Games](examples/V3/Reflex_Challenge___SnappyXO_Games/Reflex_Challenge___SnappyXO_Games.ino)
- [Robot_Dog](examples/V3/Robot_Dog/Robot_Dog.ino)
- [Scorpion](examples/V3/Scorpion/Scorpion.ino)
- [Tractor_with_Speed_Sensors](examples/V3/Tractor_with_Speed_Sensors/Tractor_with_Speed_Sensors.ino)
- [Ultrasonic_Piano](examples/V3/Ultrasonic_Piano/Ultrasonic_Piano.ino)
- [Wheeled_Robot](examples/V3/Wheeled_Robot/Wheeled_Robot.ino)
- [Wheeled_Robot_with_4_Bar_Lift](examples/V3/Wheeled_Robot_with_4_Bar_Lift/Wheeled_Robot_with_4_Bar_Lift.ino)
- [Wheeled_Robot_with_4_Bar_Sweeper](examples/V3/Wheeled_Robot_with_4_Bar_Sweeper/Wheeled_Robot_with_4_Bar_Sweeper.ino)
- [Wheeled_Sweeper_Robot](examples/V3/Wheeled_Sweeper_Robot/Wheeled_Sweeper_Robot.ino)

## License

MIT License — Copyright (c) 2024-2026 A+ Mobile Solutions Inc. See [LICENSE](LICENSE) for details.
