#include <Alfredo_NoU2.h>
#include <AlfredoConnect.h>
#include <BluetoothSerial.h>

////////////////////////////////////////////////////////////////////////////////////
NoU_Motor leftDrive(4);
NoU_Motor rightDrive(5);
NoU_Motor stable(6);
NoU_Motor octopusSpin(3);

NoU_Servo elbow(1);
NoU_Servo wrist(2);
NoU_Servo shoulder(3);
NoU_Drivetrain drivetrain(&leftDrive, &rightDrive);
bool autoRoutine = true; 
BluetoothSerial bluetooth;
////////////////////////////////////////////////////////////////////////////////////


void setup() {
  //Setup Code
  bluetooth.begin("ROBOT");
  AlfredoConnect.begin(bluetooth);
  bluetooth.println("Starting motor and servo test program.");
  RSL::initialize();
  RSL::setState(RSL_ENABLED);

}

bool autoFlag = false;

void loop() {
  int servoAngle = 0; //intake servo variable

  //Mid Cube
  if (autoRoutine && AlfredoConnect.keyHeld(Key::D) && autoFlag == false){
    autoFlag = true;
    leftDrive.setInverted(true);
    stable.set(-1);
    delay (150);
    stable.set(0);
    elbow.write (135);
    delay (300);
    shoulder.write(50);
    delay(500);
    wrist.write(0);
    delay(500);
    shoulder.write(0);
    delay(1000);
    elbow.write(15);
    drivetrain.arcadeDrive(1,0);
    shoulder.write(-10);
    octopusSpin.set(1);
    delay (750);
    drivetrain.arcadeDrive (0, 0);
    octopusSpin.set(0);
    leftDrive.setInverted(false);
  }
//Joystick Drive
  if (AlfredoConnect.getGamepadCount() >= 1) {
    float throttle = -AlfredoConnect.getAxis(0, 2);
    float rotation = -AlfredoConnect.getAxis(0, 1);
    drivetrain.arcadeDrive(throttle, rotation); //lets robot drive
    RSL::setState(RSL_ENABLED);
  } else {
    RSL::setState(RSL_DISABLED);
  }
////////////////////////////////////////////////////////////////////////////////////

//stable
  if (AlfredoConnect.buttonHeld(0,9)) {
    stable.set(1);
    delay (50);
    stable.set(0);
  }

  if (AlfredoConnect.buttonHeld(0,8)) {
    stable.set(-1);
    delay (50);
    stable.set(0);
  }

//Octopus spin
  if (AlfredoConnect.buttonHeld(0,14)) {
    octopusSpin.set(1);
    delay(100);
    octopusSpin.set(0);
  }
  
  if (AlfredoConnect.buttonHeld(0,15)) {
    octopusSpin.set(-1);
    delay(100);
    octopusSpin.set(0);
  }


//Stow
  if (AlfredoConnect.buttonHeld(0,0)) {
    stable.set(1);
    delay (150);
    stable.set(0);
    shoulder.write(-10);
    elbow.write(15); 
  }

//Ground Pickup
  if (AlfredoConnect.buttonHeld(0,6)) {
    shoulder.write(30);
    elbow.write(35); 
  }


  //substation pickup
  if (AlfredoConnect.buttonHeld(0,4)) {
    stable.set(-1);
    delay (150);
    stable.set(0);
    elbow.write(81);
    shoulder.write(30);
  }

  // Mid
  if (AlfredoConnect.buttonHeld(0,1)) {
    stable.set(-1);
    delay (150);
    stable.set(0);
    elbow.write(93);
    delay (300);
    shoulder.write(30);
  }

  // High
  if (AlfredoConnect.buttonHeld(0,3)) {
    stable.set(-1);
    delay (150);
    stable.set(0);
    elbow.write(135);
    delay (300);
    shoulder.write(50);
  }

  //Wrist up
    if (AlfredoConnect.buttonHeld(0,2)) {
    elbow.write(127);
  }

  //Wrist close
  if (AlfredoConnect.buttonHeld(0,7)) {
    wrist.write (100);
  }

  //Wrist open
  if (AlfredoConnect.buttonHeld(0,5)) {
    wrist.write (0);
  }

  AlfredoConnect.update();
  RSL::update();
}

