#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif

#include "Rover.h"

// Initialize data structures in a Rover_data object
void Rover_data::dataInit() {
	// Accelerometer
	eventData.acceleration.x = 0.0;
	eventData.acceleration.y = 0.0;
	eventData.acceleration.z = 0.0;

	// Magnetometer
	eventData.magnetic.x = 0.0;
	eventData.magnetic.y = 0.0;
	eventData.magnetic.z = 0.0;

	// Orientation
	eventData.orientation.roll = 0.0;
	eventData.orientation.pitch = 0.0;
	eventData.orientation.heading = 0.0;

	// Gyroscope
	eventData.gyro.x = 0.0;
	eventData.gyro.y = 0.0;
	eventData.gyro.z = 0.0;

	// Atomic sensor values
        eventData.temperature = 0.0;
        eventData.temperature01 = 0.0;
        eventData.temperature02 = 0.0;
        eventData.distance = 0.0;
        eventData.light = 0.0;
	eventData.lightVisible = 0.0;
	eventData.lightIR = 0.0;
	eventData.lightUV = 0.0;
	eventData.lightUVindex = 0.0;
        eventData.pressure = 0.0;
        eventData.relative_humidity = 0.0;
        eventData.current = 0.0;
        eventData.voltage = 0.0;

	// Global Positioning System
	eventData.gps.latitude = 0.0;
	eventData.gps.longitude = 0.0;
	eventData.gps.altitude = 0.0;
	eventData.gps.hours = 0;
	eventData.gps.minutes = 0;
	eventData.gps.seconds = 0.0;
	eventData.gps.day = 0;
	eventData.gps.month = 0;
	eventData.gps.year = 2015;
	eventData.gps.fix = false;
	eventData.gps.sats = 0;
}

// Parse master data from science platform and store it in data structure
void Rover_data::parseMasterData(char * dInput) {
	// -0.59,0.00,10.55,-5.18,6.00,-59.29,0.10,0.04,-0.00,997.41,21.50,41.00,261,258,2.00,0.02,21.35,52.64
	// accel(zyz),mag(xyz),gyro(xyz),pressure,temp,lux,visible,IR,UV,UVindex,temp01,humidity

	int curInd = 0;				// Current string
	int endInd = 0;				// end of string
	char tBuf[255];				// temporary buffer

	strncpy(tBuf, dInput, strlen(dInput));
	
	// First, get the Accelerometer data

	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setAccelX(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setAccelY(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setAccelZ(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	// Get the magnetometer data
	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setMagX(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setMagY(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setMagZ(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	// Get the gyroscope data
	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setGyroX(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setGyroY(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setGyroZ(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	// Get the atmospheric pressure
	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setPressure(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	// Get the first temperature reading
	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setTempA(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;


	// Get the light reading in Lux
	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setLight(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;


	// Get the visible light reading
	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setLightVisible(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	// Get the IR light reading
	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setLightIR(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	// Get the UV light reading
	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setLightUV(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	// Get the UV index
	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setLightUVindex(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	// Get the second temperature reading
	while (',' != tBuf[endInd])
	{
		endInd++;
	}
	tBuf[endInd] = '\0';
	setTempB(atof(&tBuf[curInd]));
	curInd = endInd + 1;
	endInd = curInd;

	// Get the relative humidity
	setRH(atof(&tBuf[curInd]));
}

// setXXX and getXXX methods for each data element

// Accelerometer
void Rover_data::setAccelX(double xval) {
	eventData.acceleration.x = xval;
}
double Rover_data::getAccelX() {
	return(eventData.acceleration.x);
}

void Rover_data::setAccelY(double yval) {
	eventData.acceleration.y = yval;
}
double Rover_data::getAccelY() {
	return(eventData.acceleration.y);
}

void Rover_data::setAccelZ(double zval) {
	eventData.acceleration.z = zval;
}
double Rover_data::getAccelZ() {
	return(eventData.acceleration.z);
}

// Magnetometer
void Rover_data::setMagX(double xval) {
	eventData.magnetic.x = xval;
}
double Rover_data::getMagX() {
	return(eventData.magnetic.x);
}

void Rover_data::setMagY(double yval) {
	eventData.magnetic.y = yval;
}
double Rover_data::getMagY() {
	return(eventData.magnetic.y);
}

void Rover_data::setMagZ(double zval) {
	eventData.magnetic.z = zval;
}
double Rover_data::getMagZ() {
	return(eventData.magnetic.z);
}

// Orientation
void Rover_data::setOrientRoll(double xval) {
	eventData.orientation.roll = xval;
}
double Rover_data::getOrientRoll() {
	return(eventData.orientation.roll);
}

void Rover_data::setOrientPitch(double yval) {
	eventData.orientation.pitch = yval;
}
double Rover_data::getOrientPitch() {
	return(eventData.orientation.pitch);
}

void Rover_data::setOrientHeading(double zval) {
	eventData.orientation.heading = zval;
}
double Rover_data::getOrientHeading() {
	return(eventData.orientation.heading);
}


// Gyroscope
void Rover_data::setGyroX(double xval) {
	eventData.gyro.x = xval;
}
double Rover_data::getGyroX() {
	return(eventData.gyro.x);
}

void Rover_data::setGyroY(double yval) {
	eventData.gyro.y = yval;
}
double Rover_data::getGyroY() {
	return(eventData.gyro.y);
}

void Rover_data::setGyroZ(double zval) {
	eventData.gyro.z = zval;
}
double Rover_data::getGyroZ() {
	return(eventData.gyro.z);
}

// Atomic sensor values - Temperatures
void Rover_data::setTempA(double inVal) {
	eventData.temperature = inVal;
}
double Rover_data::getTempA() {
	return(eventData.temperature);
}

void Rover_data::setTempB(double inVal) {
	eventData.temperature01 = inVal;
}
double Rover_data::getTempB() {
	return(eventData.temperature01);
}

void Rover_data::setTempC(double inVal) {
	eventData.temperature02 = inVal;
}
double Rover_data::getTempC() {
	return(eventData.temperature02);
}

// Atomic sensor values - distance (in centimeters)
void Rover_data::setDisitance(double inVal) {
	eventData.distance = inVal;
}
double Rover_data::getDisitance() {
	return(eventData.distance);
}

// Atomic sensor values - light (in lux)
void Rover_data::setLight(double inVal) {
	eventData.light = inVal;
}
double Rover_data::getLight() {
	return(eventData.light);
}

// Atomic sensor values - light levels by type
void Rover_data::setLightVisible(double inVal) {
	eventData.lightVisible = inVal;
}
double Rover_data::getLightVisible() {
	return(eventData.lightVisible);
}

void Rover_data::setLightIR(double inVal) {
	eventData.lightIR = inVal;
}
double Rover_data::getLightIR() {
	return(eventData.lightIR);
}

void Rover_data::setLightUV(double inVal) {
	eventData.lightUV = inVal;
}
double Rover_data::getLightUV() {
	return(eventData.lightUV);
}

void Rover_data::setLightUVindex(double inVal) {
	eventData.lightUVindex = inVal;
}
double Rover_data::getLightUVindex() {
	return(eventData.lightUVindex);
}

// Atomic sensor values - pressure
void Rover_data::setPressure(double inVal) {
	eventData.pressure = inVal;
}
double Rover_data::getPressure() {
	return(eventData.pressure);
}

// Atomic sensor values - relative humidity
void Rover_data::setRH(double inVal) {
	eventData.relative_humidity = inVal;
}
double Rover_data::getRH() {
	return(eventData.relative_humidity);
}

// Atomic sensor values - current
void Rover_data::setCurrent(double inVal) {
	eventData.current = inVal;
}
double Rover_data::getCurrent() {
	return(eventData.current);
}

// Atomic sensor values - voltage
void Rover_data::setVoltage(double inVal) {
	eventData.voltage = inVal;
}
double Rover_data::getVoltage() {
	return(eventData.voltage);
}

// Global Positioning System
void Rover_data::setGPSlat(double inVal) {
	eventData.gps.latitude = inVal;
}
double Rover_data::getGPSlat() {
	return(eventData.gps.latitude);
}

void Rover_data::setGPSlong(double inVal) {
	eventData.gps.longitude = inVal;
}
double Rover_data::getGPSlong() {
	return(eventData.gps.longitude);
}

void Rover_data::setGPSalt(double inVal) {
	eventData.gps.altitude = inVal;
}
double Rover_data::getGPSalt() {
	return(eventData.gps.altitude);
}

void Rover_data::setGPShours(int inVal) {
	eventData.gps.hours = inVal;
}
int Rover_data::getGPShours() {
	return(eventData.gps.hours);
}

void Rover_data::setGPSminutes(int inVal) {
	eventData.gps.minutes = inVal;
}
int Rover_data::getGPSminutes() {
	return(eventData.gps.minutes);
}

void Rover_data::setGPSseconds(double inVal) {
	eventData.gps.seconds = inVal;
}
double Rover_data::getGPSseconds() {
	return(eventData.gps.seconds);
}

void Rover_data::setGPSday(int inVal) {
	eventData.gps.day = inVal;
}
int Rover_data::getGPSday() {
	return(eventData.gps.day);
}

void Rover_data::setGPSmonth(int inVal) {
	eventData.gps.month = inVal;
}
int Rover_data::getGPSmonth() {
	return(eventData.gps.month);
}

void Rover_data::setGPSyear(int inVal) {
	eventData.gps.year = inVal;
}
int Rover_data::getGPSyear() {
	return(eventData.gps.year);
}

void Rover_data::setGPSfix(bool inVal) {
	eventData.gps.fix = inVal;
}
bool Rover_data::getGPSfix() {
	return(eventData.gps.fix);
}
void Rover_data::toggleGPSfix() {
	eventData.gps.fix = !eventData.gps.fix;
}

void Rover_data::setGPSsats(int inVal) {
	eventData.gps.sats = inVal;
}
int Rover_data::getGPSsats()
{
	return(eventData.gps.sats);
}

void Rover_data::setGPSspeed(double inSpeed)
{
	eventData.gps.speed = inSpeed;
}
double Rover_data::getGPSspeed()
{
	return(eventData.gps.speed);
}

void Rover_data::setGPSheading(double inHead)
{
	eventData.gps.heading = inHead;
}
double Rover_data::getGPSheading()
{
	return(eventData.gps.heading);
}

