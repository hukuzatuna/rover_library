#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif

// struct rover_vec_s is used to return a vector in a common format.
typedef struct {
    union {
        double v[3];
        struct {
            double x;
            double y;
            double z;
        };
        /* Orientation sensors */
        struct {
            double roll;    // Rotation around the longitudinal axis (the plane body, 'X axis'). Roll is positive and increasing when moving downward. -90°<=roll<=90°
            double pitch;   // Rotation around the lateral axis (the wing span, 'Y axis'). Pitch is positive and increasing when moving upwards. -180°<=pitch<=180°)
            double heading; // Angle between the longitudinal axis (the plane body) and magnetic north, measured clockwise when viewing from the top of the device. 0-359°
        };
    };
    int8_t status;
    uint8_t reserved[3];
} rover_vec_t;


// struct rover_loc_t is used to store the rover's GPS data
typedef struct {
	double latitude;		// Latitude
	double longitude;		// longitude
	double altitude;		// altitude (meters)
	int8_t hours;			// time - hours
	int8_t minutes;			// time - minutes
	double seconds;			// time - seconds
	int8_t day;			// date - day
	int8_t month;			// date - month
	int year;			// date - year
	double speed;			// Speed in kph
	double heading;			// Heading in degrees
	boolean fix;			// Do we have a satellite fix?
	int8_t sats;			// Number of sats currently fixed
} rover_loc_t;

// rover_event_t is a data structure to hold science, IMU, and GPS data in one place
typedef struct
{
        rover_vec_t     acceleration;         // acceleration values are in meter per second per second (m/s^2)
        rover_vec_t     magnetic;             // magnetic vector values are in micro-Tesla (uT)
        rover_vec_t     orientation;          // orientation values are in degrees
        rover_vec_t     gyro;                 // gyroscope values are in rad/s
        double          temperature;          // temperature is in degrees centigrade (Celsius) - sensor A
        double          temperature01;        // temperature is in degrees centigrade (Celsius) - sensor B
        double          temperature02;        // temperature is in degrees centigrade (Celsius) - sensor C
        double          distance;             // distance in centimeters
        double          light;                // light in SI lux units
	double		lightVisible;         // Light intenstiy levels, visible spectrum 
	double		lightIR;              // Light intensity levels - infrared spectrum
	double		lightUV;              // Light intensity levels - ultraviolet spectrum
	double		lightUVindex;         // UV index (calculated) 
        double          pressure;             // pressure in hectopascal (hPa)
        double          relative_humidity;    // relative humidity in percent
        double          current;              // current in milliamps (mA)
        double          voltage;              // voltage in volts (V)
	rover_loc_t	gps;                  // GPS location structure
} rover_event_t;


class Rover_data {
 public:
  // Data structures
  rover_event_t eventData;
  // Constructor(s)
  Rover_data() {
    dataInit();
  }
  virtual ~Rover_data() {
    dataInit();
  }

  // Method definitions (below)
  void dataInit();
  void parseMasterData(char *);

  // setXXX and getXXX methods
  void setAccelX(double);
  double getAccelX();
  void setAccelY(double);
  double getAccelY();
  void setAccelZ(double);
  double getAccelZ();
  void setMagX(double);
  double getMagX();
  void setMagY(double);
  double getMagY();
  void setMagZ(double);
  double getMagZ();
  void setOrientRoll(double);
  double getOrientRoll();
  void setOrientPitch(double);
  double getOrientPitch();
  void setOrientHeading(double);
  double getOrientHeading();
  void setGyroX(double);
  double getGyroX();
  void setGyroY(double);
  double getGyroY();
  void setGyroZ(double);
  double getGyroZ();
  void setTempA(double);
  double getTempA();
  void setTempB(double);
  double getTempB();
  void setTempC(double);
  double getTempC();
  void setDisitance(double);
  double getDisitance();
  void setLight(double);
  double getLight();
  void setLightVisible(double);
  double getLightVisible();
  void setLightIR(double);
  double getLightIR();
  void setLightUV(double);
  double getLightUV();
  void setLightUVindex(double);
  double getLightUVindex();
  void setPressure(double);
  double getPressure();
  void setRH(double);
  double getRH();
  void setCurrent(double);
  double getCurrent();
  void setVoltage(double);
  double getVoltage();
  void setGPSlat(double);
  double getGPSlat();
  void setGPSlong(double);
  double getGPSlong();
  void setGPSalt(double);
  double getGPSalt();
  void setGPShours(int);
  int getGPShours();
  void setGPSminutes(int);
  int getGPSminutes();
  void setGPSseconds(double);
  double getGPSseconds();
  void setGPSday(int);
  int getGPSday();
  void setGPSmonth(int);
  int getGPSmonth();
  void setGPSyear(int);
  int getGPSyear();
  void setGPSfix(bool);
  bool getGPSfix();
  void toggleGPSfix();
  void setGPSsats(int);
  int getGPSsats();
  void setGPSspeed(double);
  double getGPSspeed();
  void setGPSheading(double);
  double getGPSheading();
  
 private:
  bool _autoRange;
};

