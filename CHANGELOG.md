# Changelog

## 3.1.0 (2026-10-26)

**Upgrading from 3.0.0.** The sketches now use SnappyXOShield 0.3.0, so update both libraries together. Sketches written for 3.0.0 need the changes in SnappyXOShield's "Upgrading from 0.2.x" table.

- Every sketch uses the SnappyXOShield 0.3.0 API: `SnappyXOShield shield(SnappyXOShield::V3);`, `shield.begin()`, `shield.spinLeft()`/`spinRight()` (were `turnLeft()`/`turnRight()`), `shield.stop()` (was `pause()`) and `shield.setMotors()` (was `_motorWrite()`).
- The wheeled robot sketches and `Robot_Dog` assume the motors are wired the right way round. Each has `shield.invertLeft()` and `shield.invertRight()` commented out under `shield.begin()`, to uncomment for a wheel or motor that turns backward when it should go forward. Ten of them used to reverse a motor in code: `Bluetooth_4_Bar_Steering_Car`, `Gesture_Driven_Bot`, `IR_Grabber_Car`, `Light_Following_Car`, `Punch_Buggy`, `Race_Car_with_Speed_Sensors`, `Ram_Mobile`, `Robot_Dog`, `Scorpion` and `Tractor_with_Speed_Sensors`.
- Bluetooth sketches, for MicroBlue 2.1: they read the app only while connected, stop the motors when the phone disconnects or the app's heartbeat stops, check that both numbers of `x,y` arrived and map them from 0-1023 to `drive()`'s -255 to 255.
- Fixed: `Race_Car_with_Speed_Sensors` and `Tractor_with_Speed_Sensors` didn't compile (`turnRight(360.0 / numOfSides)` was ambiguous with the library's `turnRight()`). Their turn function is now `turnRightDegrees()`, and `turnRight(90)` no longer runs the library's spin by mistake.
- Fixed: the speed-sensor sketches called `delay()` inside their interrupt functions and counted pulses in plain `float`s. The counters are now `volatile` whole numbers read with interrupts paused, and sensor flicker is filtered with `micros()` instead of `delay()`. Each move now counts from zero, and `triangle()` uses its `delayTime`.
- Fixed: `Wheeled_Robot_with_4_Bar_Lift` didn't compile (missing semicolons).
- Fixed: `Wheeled_Robot_with_4_Bar_Sweeper` and `Wheeled_Robot_with_4_Bar_Lift` used `delay()` after a button press, so the robot kept driving without reading the app. The sweep is timed with `millis()` and the lift no longer waits.
- Fixed: `IR_Grabber_Car` and `IR_Excavator_Robot` drove forward at power-on until the first button press.
- Fixed: `Bluetooth_Controlled_Wheeled_Robot` printed the throttle in the wrong number base; it now prints throttle and steering.
- `Bluetooth_Controlled_Light_Up_Wheeled_Robot` lights its LED, which it never did: green driving forward, red stopped or backward, blue spinning in place (the same colors as `Light_Up_Obstacle_Avoiding_Wheeled_Robot`), and blinking red while the phone is disconnected or the app's heartbeat has stopped.
- Fixed: `Ram_Mobile` printed "Left" when turning right and "Turn Right" when turning left.
- IR sketches include `IRremote.hpp` (two used the old `IRremote.h`, which prints "no longer supported" warnings) and call `IrReceiver.resume()` after each button (two called `start()`).
- `library.properties`: maintainer A+ Mobile Solutions Inc, and `depends` now lists minimum versions and Servo and IRremote, so the Library Manager installs everything the sketches need.
- README: what the sketches need, how to upgrade from 3.0.0, and the license.
- License: still MIT, now with A+ Mobile Solutions Inc as the copyright holder, like MicroBlue. Every sketch says so at the top.
- `keywords.txt`: replaced the empty template with a note that the keywords come from SnappyXOShield and MicroBlue.
- CI compiles every sketch for the UNO R4 WiFi.
