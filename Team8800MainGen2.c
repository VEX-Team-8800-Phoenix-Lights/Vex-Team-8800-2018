#pragma config(Sensor, in1,    mobilePot,      sensorPotentiometer)
#pragma config(Sensor, in2,    liftLeftPot,    sensorPotentiometer)
#pragma config(Sensor, in3,    armPot,         sensorPotentiometer)
#pragma config(Sensor, in4,    liftRightPot,   sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rightDriveEnc,  sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftDriveEnc,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rollerEnc,      sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  liftRightEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  liftLeftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, MOSI,           sensorDigitalOut)
#pragma config(Sensor, dgtl12, SCLK,           sensorDigitalOut)
#pragma config(Motor,  port1,           mobileGoal,    tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           driveBL,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           driveBR,       tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, None)
#pragma config(Motor,  port4,           driveFL,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           driveFR,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           swingingArm,   tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           roller,        tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           liftL,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           liftR,         tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Declare VEX as the robot platform

#pragma platform(VEX)

// Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

// **** Important programmer notes ****
//
// When upgrading ROBOTC the Robot Platform Settings are lost and must be reset
// otherwise compiler error will result. Ensure the following are set:
// 		Robot -> Platform Type -> VEX 2.0 Cortex
// 		Robot -> Platform Type -> VEX Robotics -> VEX 2.0 Cortex
// 		Robot -> Platform Type -> Natural Language (PLTW)
//
//
// Note: Sometime when upgrading FW on the controller and/or joystick, the FW for the
//       VEXNet Keys must also be upgraded. The symptom of needing this upgrade is a
//       failure of the controller and joystick to communicate with each other.
//
//
// Note: When RobotC refuses to download code to the robot, first try manually selecting the
//       COM port. If that doesn't work then it may be necessary reload the firmware. First
//       update the main FW and then the RobotC FW. Don't forget to rename robot afterwards.
//
//
// Variable info:
//
//		int, short, word - 2 bytes
//		long - 4 bytes
//		SensorValue() returns 2 byte value

// Control debugger windows by defining these pragmas
#pragma DebuggerWindows("debugStream")

#include "Team8800Lib.c"		// Utility routines to simplify programming
#include "Team8800Led.c"		// Routines to control the LED strip
#include "MultiTask.c"  // Motor slew control

// Delcarations

// Initialize
void initialize();
void selectTeamAlliance();

// Controller Input
//void processController();

// Autonomous
//void autonomousRoutines();

// Robot Action

//Functions
void moveLiftDown(int speed, int distance);
void moveArmOut();
void moveArmIn();
void moveArmOutAuto();
void moveArm(bool forward);
void moveLiftUp(int speed, int distance);
void moveLiftUpAuto(int speed, int distance);
void rollerIntake(int speed);
void rollerOutake(int speed, int distance);

void liftPIDControl (float position);

//Auto Functions
void moveMobileGoalOutAndDrive(int speed, int distance);
void moveMobileGoalInAndDrive(int speed, int distance);
void autoLiftControl (int height);
void drive(int left, int right);
void driveForward(int speed, int distance);
void driveBackward(int speed, int distance);
void turnLeft(int speed, int distance);
void turnRight(int speed, int distance);
void clearDriveEnc();
void moveMobileGoalOutAuto();
void moveMobileGoalInAuto();
void moveMobileGoalOut();
void moveMobileGoalIn();
void moveMobileGoalInDistance(int distance);

// Constants and global vars
const byte MIN_JOYSTICK_THRESHOLD = 30;

const byte RED_ALLIANCE = 1;
const byte BLUE_ALLIANCE = 2;
byte allianceColor = BLUE_ALLIANCE;

const byte LEFT = 1;
const byte RIGHT = 2;
byte allianceSide = RIGHT;

const byte AUTONOMOUS_MODE_MOBILE_GOAL_20 = 1;
const byte AUTONOMOUS_MODE_CUBE_BACK_STAR = 2;
const byte AUTONOMOUS_MODE_FENCE = 3;
const byte AUTONOMOUS_MODE_SKILLS = 4;
const byte AUTONOMOUS_MODE_STACK_DRIVE = 5;
const byte AUTONOMOUS_MODE_STACK_PIPE = 6;
const byte AUTONOMOUS_MODE_STACK_BACK = 7;
const byte AUTONOMOUS_MODE_DRIVE_BLOCK = 8;
byte autonomousMode = AUTONOMOUS_MODE_MOBILE_GOAL_20;

const byte PRESET_LEVEL_ONE = 1;
const byte PRESET_LEVEL_TWO = 2;
const byte PRESET_LEVEL_THREE = 3;
const byte PRESET_LEVEL_FOUR = 4;
const byte PRESET_LEVEL_FIVE = 5;
const byte PRESET_LEVEL_SIX = 6;
const byte PRESET_LEVEL_SEVEN = 7;
const byte PRESET_LEVEL_EIGHT = 8;
const byte PRESET_LEVEL_NINE = 9;
const byte PRESET_LEVEL_TEN = 10;
const byte PRESET_LEVEL_ELEVEN = 11;
const byte PRESET_LEVEL_TWELVE = 12;
const byte PRESET_LEVEL_THIRTEEN = 13;
const byte PRESET_LEVEL_FOURTEEN = 14;
const byte PRESET_LEVEL_FIFTEEN = 15;
byte presetLevel = PRESET_LEVEL_ONE;

unsigned long autonomousStartTime;

const byte AUTONOMOUS = 1;
const byte USER_CONTROL = 2;
byte robotMode = 1;

bool presetLevelActive = false;
bool presetLevelJustActive = false;

bool boingyPointOn = true;
bool armBack = false;
bool armFront = true;

bool armIsBack = false;
bool armIsBackLvl1and2;
bool armIsForward;
bool liftLeftIsPosition4;
bool liftRightIsPosition4 = false;
bool liftIsPosition4Again = false;
bool liftIsPosition5;
bool liftIsPosition6;
bool liftIsDown = false;

bool mobileGoalOut;

bool rollerIntaking = false;
bool rollerOutaking = false;

bool btnSixUPressed = false;
bool btnSixDPressed = false;

bool presetLevelScrollUp = false;
bool presetLevelScrollDown = false;

int level4Height = 85;
int level5Height = 115;
int level6Height = 260;
int level7Height = 370;
int level8Height = 470;
int level9Height = 570;
int level10Height = 800;
int level11Height = 100;
int level12Height = 120;
int level13Height = 120;
int level14Height = 120;
int level15Height = 120;

int leftPositionError = 10;
int rightPositionError = 0;
int armError = 2;

float liftLeftError;
float liftRightError;
float leftErrorT;
float rightErrorT;
float liftLeftLastError;
float liftRightLastError;

float leftkp = 1.2;
float leftki = 0.007;
float leftkd = 0.04;

float rightkp = 1.2;
float rightki = 0.007;
float rightkd = 0.04;

float leftCurrent;
float rightCurrent;

float integralAcitveZone = 200;

float leftProportion;
float leftIntegral;
float leftDerivative;
float rightProportion;
float rightIntegral;
float rightDerivative;

int rollerSpeed;

void pre_auton()
{
	bStopTasksBetweenModes = true;

	clearDebugStream();
	writeDebugStreamLine("Pre-Autonomous...");

	// Select alliance using LCD and indicate selection with LEDs
	selectTeamAlliance();
}

task autonomousRoutines()
{
	switch (autonomousMode) {
	case AUTONOMOUS_MODE_MOBILE_GOAL_20:
		if (allianceSide == LEFT && allianceColor == BLUE_ALLIANCE) {
			motor [roller] = 40;

			//move lift up
			moveLiftUpAuto(100, 1900);

			waitInMilliseconds(200);

			clearDriveEnc();

			//mobile goal out
			moveMobileGoalOutAndDrive(50, 1200);

			//drive forward
			//driveForward (90, 1100);

			waitInMilliseconds(200);

			//intake the mobile goal
			//moveMobileGoalIn();
			moveMobileGoalInDistance(1000);
			moveMobileGoalInAndDrive(-110, -380);
			driveBackward(-110, -380);

			motor[mobileGoal] = 5;
			waitInMilliseconds(150);

			//move lift down
			moveLiftDown(50, 2400);

			waitInMilliseconds(200);

			SensorValue[rollerEnc] = 0;

			rollerOutake(-100, 250);

			waitInMilliseconds(200);

			//clearDriveEnc();

			//drive backward
			//driveBackward(-110, -500);

			waitInMilliseconds(300);

			clearDriveEnc();

			turnLeft(127, 95);

			waitInMilliseconds(200);

			clearDriveEnc();

			driveBackward(-100, -330);

			waitInMilliseconds(200);

			clearDriveEnc();

			turnLeft(100, 275);

			waitInMilliseconds(300);

			clearDriveEnc();

			driveBackward(-120, -40);

			waitInMilliseconds(200);

			moveLiftUpAuto(100, 2300);

			clearDriveEnc();

			driveForward(127, 500);

			waitInMilliseconds(200);

			drive(70, 70);
			waitInMilliseconds(500);
			drive(15, 15);

			waitInMilliseconds(400);

			moveMobileGoalOutAuto();

			waitInMilliseconds(200);

			drive(-50, -50);
			waitInMilliseconds(700);
			drive(0, 0);

			waitInMilliseconds(200);

			moveMobileGoalInAuto();

			} else if (allianceSide == RIGHT && allianceColor == BLUE_ALLIANCE) {
			motor [roller] = 40;

			//move lift up
			moveLiftUpAuto(100, 1900);

			waitInMilliseconds(200);

			clearDriveEnc();

			//mobile goal out
			moveMobileGoalOutAndDrive(55, 1100);

			//drive forward
			//driveForward (90, 1100);

			waitInMilliseconds(200);

			//intake the mobile goal
			//moveMobileGoalIn();
			moveMobileGoalInDistance(1000);
			moveMobileGoalInAndDrive(-110, -380);
			driveBackward(-110, -380);

			motor[mobileGoal] = 5;
			waitInMilliseconds(150);

			//move lift down
			moveLiftDown(50, 2400);

			waitInMilliseconds(200);

			SensorValue[rollerEnc] = 0;

			rollerOutake(-100, 250);

			waitInMilliseconds(200);

			//clearDriveEnc();

			//drive backward
			//driveBackward(-110, -500);

			waitInMilliseconds(300);

			clearDriveEnc();

			turnRight(115, 95);

			waitInMilliseconds(200);

			clearDriveEnc();

			driveBackward(-100, -300);

			waitInMilliseconds(200);

			clearDriveEnc();

			turnRight(100, 275);

			waitInMilliseconds(300);

			clearDriveEnc();

			driveBackward(-120, -40);

			waitInMilliseconds(200);

			moveLiftUpAuto(100, 2300);

			clearDriveEnc();

			driveForward(127, 500);

			waitInMilliseconds(200);

			drive(70, 70);
			waitInMilliseconds(500);
			drive(15, 15);

			waitInMilliseconds(400);

			moveMobileGoalOutAuto();

			waitInMilliseconds(200);

			drive(-50, -50);
			waitInMilliseconds(700);
			drive(0, 0);

			waitInMilliseconds(200);

			moveMobileGoalInAuto();

			driveBackward(-70, -400);
			} else if (allianceSide == LEFT && allianceColor == RED_ALLIANCE) {
			motor [roller] = 40;

			//move lift up
			moveLiftUpAuto(100, 1900);

			waitInMilliseconds(200);

			clearDriveEnc();

			//mobile goal out
			moveMobileGoalOutAndDrive(50, 1200);

			//drive forward
			//driveForward (90, 1100);

			waitInMilliseconds(200);

			//intake the mobile goal
			//moveMobileGoalIn();
			moveMobileGoalInDistance(1000);
			moveMobileGoalInAndDrive(-110, -380);
			driveBackward(-110, -380);

			motor[mobileGoal] = 5;
			waitInMilliseconds(150);

			//move lift down
			moveLiftDown(50, 2400);

			waitInMilliseconds(200);

			SensorValue[rollerEnc] = 0;

			rollerOutake(-100, 250);

			waitInMilliseconds(200);

			//clearDriveEnc();

			//drive backward
			//driveBackward(-110, -500);

			waitInMilliseconds(300);

			clearDriveEnc();

			turnLeft(127, 95);

			waitInMilliseconds(200);

			clearDriveEnc();

			driveBackward(-100, -330);

			waitInMilliseconds(200);

			clearDriveEnc();

			turnLeft(100, 275);

			waitInMilliseconds(300);

			clearDriveEnc();

			driveBackward(-120, -40);

			waitInMilliseconds(200);

			moveLiftUpAuto(100, 2300);

			clearDriveEnc();

			driveForward(127, 500);

			waitInMilliseconds(200);

			drive(70, 70);
			waitInMilliseconds(500);
			drive(15, 15);

			waitInMilliseconds(400);

			moveMobileGoalOutAuto();

			waitInMilliseconds(200);

			drive(-50, -50);
			waitInMilliseconds(700);
			drive(0, 0);

			waitInMilliseconds(200);

			moveMobileGoalInAuto();

			driveBackward(-70, -400);
			} else if (allianceSide == RIGHT && allianceColor == RED_ALLIANCE) {
			motor [roller] = 40;

			//move lift up
			moveLiftUpAuto(100, 1900);

			waitInMilliseconds(200);

			clearDriveEnc();

			//mobile goal out
			moveMobileGoalOutAndDrive(55, 1100);

			//drive forward
			//driveForward (90, 1100);

			waitInMilliseconds(200);

			//intake the mobile goal
			//moveMobileGoalIn();
			moveMobileGoalInDistance(1000);
			moveMobileGoalInAndDrive(-110, -380);
			driveBackward(-110, -380);

			motor[mobileGoal] = 5;
			waitInMilliseconds(150);

			//move lift down
			moveLiftDown(50, 2400);

			waitInMilliseconds(200);

			SensorValue[rollerEnc] = 0;

			rollerOutake(-100, 250);

			waitInMilliseconds(200);

			//clearDriveEnc();

			//drive backward
			//driveBackward(-110, -500);

			waitInMilliseconds(300);

			clearDriveEnc();

			turnRight(115, 95);

			waitInMilliseconds(200);

			clearDriveEnc();

			driveBackward(-100, -300);

			waitInMilliseconds(200);

			clearDriveEnc();

			turnRight(100, 275);

			waitInMilliseconds(300);

			clearDriveEnc();

			driveBackward(-120, -40);

			waitInMilliseconds(200);

			moveLiftUpAuto(100, 2300);

			clearDriveEnc();

			driveForward(127, 500);

			waitInMilliseconds(200);

			drive(70, 70);
			waitInMilliseconds(500);
			drive(15, 15);

			waitInMilliseconds(400);

			moveMobileGoalOutAuto();

			waitInMilliseconds(200);

			drive(-50, -50);
			waitInMilliseconds(700);
			drive(0, 0);

			waitInMilliseconds(200);

			moveMobileGoalInAuto();

			driveBackward(-70, -400);
		}

		if (allianceColor == BLUE_ALLIANCE) {
			theaterChaseTask(0, 0, 127, 50, 15000);
			} else {
			theaterChaseTask(127, 0, 0, 50, 15000);
		}
		break;

	case AUTONOMOUS_MODE_CUBE_BACK_STAR:

		//Apply passive power to roller
		motor [roller] = 40;

		//move lift up
		moveLiftUpAuto(100, 1800);

		//drive forward
		driveForward(80, 220);

		waitInMilliseconds(100);

		//move swinging arm out
		moveArmOutAuto();

		waitInMilliseconds(200);

		//move lift down
		moveLiftDown(50, 1950);

		waitInMilliseconds(500);

		//move lift up and release cone
		motor[roller] = -100;
		moveLiftUpAuto(100, 1800);

		waitInMilliseconds(100);

		//back up
		driveBackward(-100, 200);

		//turn and drive out of the way
		turnLeft(100, 300);
		driveBackward(-100, -400);

		if (allianceColor == BLUE_ALLIANCE) {
			theaterChaseTask(0, 0, 127, 50, 15000);
			} else {
			theaterChaseTask(127, 0, 0, 50, 15000);
		}
		break;

	case AUTONOMOUS_MODE_FENCE:

		if (allianceColor == BLUE_ALLIANCE) {
			theaterChaseTask(0, 0, 127, 50, 15000);
			} else {
			theaterChaseTask(127, 0, 0, 50, 15000);
		}

		break;

	case AUTONOMOUS_MODE_SKILLS:


		break;

	case AUTONOMOUS_MODE_STACK_DRIVE:

		break;

	case AUTONOMOUS_MODE_STACK_PIPE:

		break;

	case AUTONOMOUS_MODE_STACK_BACK:

		break;

	case AUTONOMOUS_MODE_DRIVE_BLOCK:

		break;
	}
}

task autonomous()
{
	robotMode = AUTONOMOUS;

	autonomousStartTime = nSysTime;
	writeDebugStreamLine("Starting Autonomous...");

	if (false) AutonomousCodePlaceholderForTesting();  // complains if I remove this

	initialize();
	startTask(autonomousRoutines);
}

task ProcessController() {
	while(true) {

		/*
		Main Controller:
		joysticks = drive

		Partner Contorller:
		right joystick = catapult
		*/

		// --- Joysticks to control robot driving (main controller only)

		static byte rightJoystickY, leftJoystickY, prevRightJoystickY = 0, prevLeftJoystickY = 0;

		rightJoystickY = readRightJoystickYAxis();
		leftJoystickY = readLeftJoystickYAxis();

		static bool rightDriveMoving = false;
		if (abs(rightJoystickY) > MIN_JOYSTICK_THRESHOLD) {
			rightDriveMoving = true;
			motorReq2[driveFR] = rightJoystickY;
			motorReq2[driveBR] = rightJoystickY;
			writeDebugStreamLine("Right: %d%%", rightJoystickY);
			} else {
			rightDriveMoving = false;
			motorReq2[driveFR] = 0;
			motorReq2[driveBR] = 0;
		}

		static bool leftDriveMoving = false;
		if (abs(leftJoystickY) > MIN_JOYSTICK_THRESHOLD) {
			leftDriveMoving = true;
			motorReq2[driveFL] = leftJoystickY;
			motorReq2[driveBL] = leftJoystickY;
			writeDebugStreamLine("Left: %d%%", leftJoystickY);
			} else {
			leftDriveMoving = false;
			motorReq2[driveFL] = 0;
			motorReq2[driveBL] = 0;
		}

		if (isButtonPressed(Btn8RXmtr2)) {
			armIsBack = true;
			} else if (isButtonPressed(Btn8LXmtr2)) {
			armIsBack = false;
		}

		if (armIsBack) {
			moveArmOut();
			} else if (!armIsBack) {
			moveArmIn();
		}

		//Mobile Goal control on joystick
		if (isButtonPressed(Btn8U)) {
			mobileGoalOut = true;
			} else if (isButtonPressed(Btn8D)) {
			mobileGoalOut = false;
		}

		if (isButtonPressed(Btn8R)) {
			moveMobileGoalOut();
			} else if (isButtonPressed(Btn8L)) {
			moveMobileGoalIn();
			} else if (mobileGoalOut) {
			moveMobileGoalOut();
			} else if (!mobileGoalOut) {
			moveMobileGoalIn();
		}

		//Roller control
		if (isButtonPressed(Btn6DXmtr2)) {
			motor[roller] = -127;
			} else if (isButtonPressed(Btn6UXmtr2)) {
			motor[roller] = 127;
			} else {
			//motor[roller] = 30;
			motor[roller] = 0;
		}

		bool PID;
		//Move lift
		if (isButtonPressed(Btn5UXmtr2)) {
			PID = true;
			//motor[liftL] = 127;
			//motor[liftR] = 127;
		} else if (isButtonPressed(Btn5DXmtr2)) {
			motor[liftL] = -50;
			motor[liftR] = -50;
			PID = false;
		} else {
			motor[liftL] = 0;
			motor[liftR] = 0;
		}

		if (PID) {
			liftPIDControl(900);
		}

		writeDebugStreamLine("lift Left, %d", SensorValue[liftLeftEncoder]/*SensorValue[liftLeftPot]/2*/);
		writeDebugStreamLine("lift Right                               , %d", SensorValue[liftRightEncoder]/*SensorValue[liftRightPot]/2*/);
		//writeDebugStreamLine("Left Enc, %d", SensorValue[leftDriveEnc]);
		//writeDebugStreamLine("mobile, %d", SensorValue[mobilePot]);
		//writeDebugStreamLine("roller Enc, %d", SensorValue[rollerEnc]);
		//writeDebugStreamLine("arm pot, %d", SensorValue[armPot]);

		//datalogAddValueWithTimeStamp(0, SensorValue[liftLeftPot]);
		//datalogAddValueWithTimeStamp(1, SensorValue[liftRightPot]);

		if (isButtonClick(Btn8UXmtr2)) {
			theaterChaseTask(127, 0, 127, 127, 15000);
		}

		if (isButtonClick(Btn8RXmtr2)) {
			theaterChaseTask(0, 0, 127, 127, 15000);
		}

		if (isButtonClick(Btn8LXmtr2)) {
			theaterChaseTask(127, 0, 0, 127, 15000);
		}


		// --- Choose alliance if both Left & Right LCD Buttons are pressed

		if ((nLCDButtons & (kButtonLeft | kButtonRight)) == (kButtonLeft | kButtonRight)) {
			selectTeamAlliance();
		}

		//writeDebugStreamLine("value Arm pot %d", SensorValue[armPot]);

		wait1Msec(15);
	}
}

task usercontrol()
{
	robotMode = USER_CONTROL;

	if (false) UserControlCodePlaceholderForTesting();	// complains if I remove this

	writeDebugStreamLine("Starting User Control...");
	writeDebugStreamLine("Main battery level: %3.2f", nAvgBatteryLevel * 0.001);
	writeDebugStreamLine("Backup battery level: %3.2f", BackupBatteryLevel * 0.001);

	initialize();

	startTask(MotorSlewRateTask);
	startTask(ProcessController);
}

void initialize()
{
	// Library routines thread
	startTask(activateLib);

	// LED strip routines thread
	setupLedStrip();

	SensorValue[rightDriveEnc] = 0;
	SensorValue[leftDriveEnc] = 0;
	SensorValue[rollerEnc] = 0;
	SensorValue[liftLeftEncoder] = 0;
	SensorValue[liftRightEncoder] = 0;

	datalogClear();

	presetLevel = PRESET_LEVEL_ONE;
}

void timerCallback(unsigned int timerId)
{

}

void selectTeamAlliance()
{
	// Defaults
	allianceColor = BLUE_ALLIANCE;
	allianceSide = RIGHT;
	autonomousMode = AUTONOMOUS_MODE_MOBILE_GOAL_20;
	//return;

	//SensorValue[ledGreen] = 0;
	//SensorValue[ledRed] = 0;

	// Zero out encoder positions

	// Clear LCD and turn on backlight
	clearLCDLine(0);
	clearLCDLine(1);
	bLCDBacklight = true;

	// Display alliance selection
	displayLCDString(0, 0, " Team Color  ");
	displayLCDString(1, 0, " Blue       Red ");

	bool allianceSelected = false;
	while (!allianceSelected) {	//bIfiRobotDisabled
		// Wait for button press
		switch (getLcdButtons()) {
		case kButtonLeft:
			allianceColor = BLUE_ALLIANCE;
			displayLCDString(1, 0, "[Blue]      Red ");
			allianceSelected = true;
			break;

		case kButtonRight:
			allianceColor = RED_ALLIANCE;
			displayLCDString(1, 0, "Blue       [Red]");
			allianceSelected = true;
			break;
		}

		wait1Msec(10);
	}

	// Display autonomous selection
	wait1Msec(500);

	// Display alliance selection
	displayLCDString(0, 0, " Team Side  ");
	displayLCDString(1, 0, " Left     Right ");

	bool sideSelected = false;
	while (!sideSelected) {	//bIfiRobotDisabled
		// Wait for button press
		switch (getLcdButtons()) {
		case kButtonLeft:
			allianceSide = LEFT;
			displayLCDString(1, 0, "[Left]    Right ");
			sideSelected = true;
			break;

		case kButtonRight:
			allianceSide = RIGHT;
			displayLCDString(1, 0, "Left     [Right]");
			sideSelected = true;
			break;
		}
		wait1Msec(10);
	}



	// Display autonomous selection
	wait1Msec(500);

	displayLCDString(0, 0, "Autonomous Mode ");
	displayLCDString(1, 0, "Full  Min  None ");

	bool autonomousSelected = false;
	int scrollCount = 1;
	byte scrolledAuto = AUTONOMOUS_MODE_MOBILE_GOAL_20;
	while (!autonomousSelected) {
		// Wait for button press
		if(nLCDButtons == 1) {
			scrollCount -= 1;
		}
		if(nLCDButtons == 4) {
			scrollCount += 1;
		}
		if(nLCDButtons == 2) {
			autonomousMode = scrolledAuto;
			autonomousSelected = true;
		}

		switch (scrollCount) {
		case 1:
			scrolledAuto = AUTONOMOUS_MODE_MOBILE_GOAL_20;
			displayLCDString(1, 0, "[1]2 3 4 5 6 7 8 ");
			wait1Msec(200);
			break;

		case 2:
			scrolledAuto = AUTONOMOUS_MODE_CUBE_BACK_STAR;
			displayLCDString(1, 0, " 1[2]3 4 5 6 7 8 ");
			wait1Msec(200);
			break;

		case 3:
			scrolledAuto = AUTONOMOUS_MODE_FENCE;
			displayLCDString(1, 0, " 1 2[3]4 5 6 7 8 ");
			wait1Msec(200);
			break;

		case 4:
			scrolledAuto = AUTONOMOUS_MODE_SKILLS;
			displayLCDString(1, 0, " 1 2 3[4]5 6 7 8 ");
			wait1Msec(200);
			break;

		case 5:
			scrolledAuto = AUTONOMOUS_MODE_STACK_DRIVE;
			displayLCDString(1, 0, " 1 2 3 4[5]6 7 8 ");
			wait1Msec(200);
			break;

		case 6:
			scrolledAuto = AUTONOMOUS_MODE_STACK_PIPE;
			displayLCDString(1, 0, " 1 2 3 4 5[6]7 8 ");
			wait1Msec(200);
			break;

		case 7:
			scrolledAuto = AUTONOMOUS_MODE_STACK_BACK;
			displayLCDString(1, 0, " 1 2 3 4 5 6[7]8 ");
			wait1Msec(200);
			break;

		case 8:
			scrolledAuto = AUTONOMOUS_MODE_DRIVE_BLOCK;
			displayLCDString(1, 0, " 1 2 3 4 5 6 7[8]");
			wait1Msec(200);
			break;
		}

		wait1Msec(10);
	}

	wait1Msec(500);

	// Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
}

void moveArmOut () {
	if (SensorValue[armPot] > 1800) {
		motor[swingingArm] = 120;
		} else if (SensorValue[armPot] <= 1800) {
		motor[swingingArm] = 0;
	}
}

void moveArmIn () {
	if (SensorValue[armPot] < 3850) {
		motor[swingingArm] = -120;
		} else if (SensorValue[armPot] >= 3850) {
		motor[swingingArm] = 0;
	}
}

void moveArmOutAuto() {
	while(SensorValue[armPot] > 45) {
		motor[swingingArm] = 100;
	}
	motor[swingingArm] = 0;
}

void moveArm (bool forward) {
	if (forward) {
		moveArmOut();
		} else {
		moveArmIn();
	}
}

void rollerIntake(int speed) {
	motor[roller] = speed;
	rollerSpeed = speed;
	//	writeDebugStreamLine("Set speed %d", rollerSpeed);
}

void rollerOutake(int speed, int distance) {
	while (distance > SensorValue[rollerEnc]) {
		motor[roller] = speed;
		writeDebugStreamLine("Roller Enc %d", SensorValue[rollerEnc]);
	}
	motor [roller] = 0;
}

//Drive function for auto
void drive(int left, int right) {
	turnMotor(driveFL, left);
	turnMotor(driveFR, right);
	turnMotor(driveBL, left);
	turnMotor(driveBR, right);
}
//Drive function with encoders for auto
void driveForward(int speed, int distance) {
	while (SensorValue[rightDriveEnc] < distance && SensorValue[leftDriveEnc] < distance) {
		writeDebugStreamLine(" Left Encoder: %d", SensorValue[leftDriveEnc]);
		writeDebugStreamLine(" Right Encoder: %d", SensorValue[rightDriveEnc]);
		writeDebugStreamLine("Moving forward");
		drive(speed, speed);
	}
	drive(0, 0);

	SensorValue[rightDriveEnc] = 0;
	SensorValue[leftDriveEnc] = 0;
	writeDebugStreamLine("Front Left Encoder: %d", SensorValue[leftDriveEnc]);
	writeDebugStreamLine("Front Right Encoder: %d", SensorValue[rightDriveEnc]);
}

void driveBackward(int speed, int distance) {
	while (SensorValue[rightDriveEnc] > distance && SensorValue[leftDriveEnc] > distance) {
		drive(speed, speed);
	}
	drive(0, 0);

	SensorValue[rightDriveEnc] = 0;
	SensorValue[leftDriveEnc] = 0;
}

void turnLeft(int speed, int distance) {
	while (SensorValue[leftDriveEnc] < distance && SensorValue[rightDriveEnc] > (-distance)) {
		drive(-speed, speed);
	}
	drive(0, 0);

	SensorValue[rightDriveEnc] = 0;
	SensorValue[leftDriveEnc] = 0;
}

void turnRight(int speed, int distance) {
	while (SensorValue[leftDriveEnc] > (-distance) && SensorValue[rightDriveEnc] < distance) {
		drive(speed, -speed);
	}
	drive(0, 0);

	SensorValue[rightDriveEnc] = 0;
	SensorValue[leftDriveEnc] = 0;
}

void clearDriveEnc() {
	SensorValue[rightDriveEnc] = 0;
	SensorValue[leftDriveEnc] = 0;
}

void moveMobileGoalIn() {
	if (SensorValue[mobilePot] > 230) {
		motor[mobileGoal] = 127;
		} else {
		motor[mobileGoal] = 0;
	}
}

void moveMobileGoalInAuto() {
	while (SensorValue[mobilePot] > 230) {
		motor[mobileGoal] = 127;
	}
	motor[mobileGoal] = 0;
}

void moveMobileGoalInDistance(int distance) {
	while (SensorValue[mobilePot] > distance) {
		motor[mobileGoal] = 127;
	}
	motor[mobileGoal] = 0;
}

void moveMobileGoalOut() {
	if (SensorValue[mobilePot] < 2170) {
		motor[mobileGoal] = -127;
		} else {
		motor[mobileGoal] = 0;
	}
}

void moveMobileGoalOutAuto() {
	while (SensorValue[mobilePot] < 2170) {
		motor[mobileGoal] = -127;
	}
	motor[mobileGoal] = 0;
}

void moveMobileGoalOutAndDrive(int speed, int distance) {
	while (SensorValue[rightDriveEnc] < distance && SensorValue[leftDriveEnc] < distance) {
		drive(speed, speed);
		while (SensorValue[mobilePot] < 2170) {
			motor[mobileGoal] = -127;
		}
		motor[mobileGoal] = 0;
	}
	drive(0, 0);

	SensorValue[rightDriveEnc] = 0;
	SensorValue[leftDriveEnc] = 0;
}

void moveMobileGoalInAndDrive(int speed, int distance) {
	while (SensorValue[rightDriveEnc] > distance && SensorValue[leftDriveEnc] > distance) {
		drive(speed, speed);
		while (SensorValue[mobilePot] > 180) {
			motor[mobileGoal] = 127;
		}
		motor[mobileGoal] = 0;
	}
	drive(0, 0);
}


void moveLiftUp(int speed, int distance) {
	if (((SensorValue[liftLeftPot] + SensorValue[liftRightPot])/2) > distance) {
		motor [liftL] = speed;
		motor [liftR] = speed;
	} else {
		motor [liftL] = 0;
		motor [liftR] = 0;
	}
}

void moveLiftUpAuto(int speed, int distance) {
	while (((SensorValue[liftLeftPot] + SensorValue[liftRightPot])/2) > distance) {
		motor [liftL] = speed;
		motor [liftR] = speed;
	}
	motor [liftL] = 0;
	motor [liftR] = 0;
}

void moveLiftDown(int speed, int distance) {
	while (((SensorValue[liftLeftPot] + SensorValue[liftRightPot])/2) < distance) {
		motor [liftL] = -speed;
		motor [liftR] = -speed;
	}
	motor [liftL] = 0;
	motor [liftR] = 0;
}

void liftPIDControl (float position) {
	float leftPot = (SensorValue[liftLeftPot]/2);
	float rightPot = (SensorValue[liftRightPot]/2);

	//Find lift error
	liftLeftError = position - leftPot;
	liftRightError = position - rightPot;

	leftProportion = liftLeftError * leftkp;
	rightProportion = liftRightError * rightkp;

	leftIntegral = leftErrorT * leftki;
	rightIntegral = rightErrorT * rightki;

	leftDerivative = (liftLeftError - liftLeftLastError) * leftkd;
	rightDerivative = (liftRightError - liftRightLastError) * rightkd;

	leftCurrent = leftProportion + leftIntegral + leftDerivative;
	rightCurrent = rightProportion + rightProportion + rightDerivative;

	//left
	if (liftLeftError < integralAcitveZone) {
	leftErrorT += liftLeftError;
	} else {
	leftErrorT = 0;
	}
	if (leftErrorT > 50/leftki) {
		leftErrorT = 50/leftki;
	}

	//right
	if (liftRightError < integralAcitveZone) {
	rightErrorT += liftRightError;
	} else {
	rightErrorT = 0;
	}
	if (rightErrorT > 50/rightki) {
		rightErrorT = 50/rightki;
	}

	if (liftLeftError == 0) {
		leftDerivative = 0;
	}
	if (liftRightError == 0) {
		rightDerivative = 0;
	}

	liftLeftLastError = liftLeftError;
	liftRightLastError = liftRightError;

	//left
	/*if (leftPot >= position + liftError && leftPot < position - liftError) {
		leftCurrent = 0;
	}

	//right
	if (rightPot >= position + liftError && rightPot < position - liftError) {
		rightCurrent = 0;
	}*/

	if (abs(liftLeftError) <= leftPositionError) {
		leftCurrent = 0;
	}
	if (abs(liftRightError) <= rightPositionError) {
		rightCurrent = 0;
	}

	if (leftCurrent > 127) {
		leftCurrent = 127;
	}
	if (rightCurrent > 127) {
		rightCurrent = 127;
	}
	if (leftCurrent < -127) {
		leftCurrent = -127;
	}
	if (rightCurrent < -127) {
		rightCurrent = -127;
	}

	motor[liftL] = -leftCurrent;
	motor[liftR] = -rightCurrent;

	writeDebugStreamLine("left encoder %d", leftPot);
	writeDebugStreamLine("                         right encoder %d", rightPot);
	writeDebugStreamLine("position %d", position);
	writeDebugStreamLine("          left error %d", liftLeftError);
	writeDebugStreamLine("                  right error %d", liftRightError);
	writeDebugStreamLine("                                            left curent %d", -leftCurrent);
	writeDebugStreamLine("                                                        right curent %d", -rightCurrent);

	datalogAddValueWithTimeStamp(0, leftPot);
	datalogAddValueWithTimeStamp(1, rightPot);
	datalogAddValueWithTimeStamp(2, liftLeftError);
	datalogAddValueWithTimeStamp(3, liftRightError);
	datalogAddValueWithTimeStamp(4, -leftCurrent);
	datalogAddValueWithTimeStamp(5, -rightCurrent);
	datalogAddValueWithTimeStamp(6, -leftIntegral);
	datalogAddValueWithTimeStamp(7, -rightIntegral);
}
