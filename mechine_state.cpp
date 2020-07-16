#include "ArduinoJson-v6.9.1.h"

//状态机
StaticJsonDocument<COMMAND_SIZE> doc;
char command[COMMAND_SIZE];
//当前使用IO情况
enum PinAssignments {
clearButton = 8,
encoderPinA = 2,
encoderPinB = 3,
driveLed = 10,
drivePin = 6,
loadLed = 12,
loadPin = 4,
brakingLed = 8
};
/**
 * Defines the valid states for the state machine
 * 
 */
typedef enum
{
  STATE_START_CALIBRATION,
  STATE_ZERO_ENCODER,
  STATE_AWAITING_STOP,
  STATE_DRIVING,
  STATE_START,
  STATE_STOPPED,
} StateType;

//state Machine function prototypes
void Sm_State_Start_Calibration(void);
void Sm_State_Zero_Encoder(void);
void Sm_State_Awaiting_Stop(void);
void Sm_State_Driving(void);
void Sm_State_Start(void);
void Sm_State_Stopped(void);


/**
 * Type definition used to define the state
 */
 
typedef struct
{
  StateType State; /**< Defines the command */
  void (*func)(void); /**< Defines the function to run */
} StateMachineType;
 
/**
 * A table that defines the valid states of the state machine and
 * the function that should be executed for each state
 */
StateMachineType StateMachine[] =
{
  {STATE_START_CALIBRATION, Sm_State_Start_Calibration},
  {STATE_ZERO_ENCODER, Sm_State_Zero_Encoder},
  {STATE_AWAITING_STOP, Sm_State_Awaiting_Stop},
  {STATE_DRIVING, Sm_State_Driving},
  {STATE_START, Sm_State_Start},
  {STATE_STOPPED, Sm_State_Stopped}
};
 
int NUM_STATES = 6;

/**
 * Stores the current state of the state machine
 */
 
StateType SmState = STATE_START_CALIBRATION;


/**
 *  Example commmands
 *  {"cmd":"interval","param":200}
 *  {"cmd":"drive","param":30}
 *  {"cmd":"stop","param":"loaded"}
 *  {"cmd":"stop","param":"unloaded"}
 *  {"cmd":"stop","param":"brake"}
 *  {"cmd":"brake","param":30}
 *  {"cmd":"stop"}
 *  {"cmd":"start","param":50}
 *  {"cmd":"calibrate"}
 */

StateType readSerialJSON(StateType SmState){
  

  
  if (Serial.available() > 0) 
  {

    char start[] = "start";
    char stop[] = "stop";
    char cal[] = "calibrate";
    char report_interval[] = "interval";
    char loaded[] = "loaded";
    char unloaded[] = "unloaded";
    char brake[] = "brake";
    char drive[] = "drive";
    
    Serial.readBytesUntil(10, command, COMMAND_SIZE);
                
    deserializeJson(doc, command);

    const char* cmd = doc["cmd"];
    
    if (strcmp(cmd,report_interval)==0)
    {
      int new_interval = doc["param"];
      if ((new_interval > 0) && (new_interval < 1000))
      {
        interval = new_interval;
        Serial.println("{\"result\":\"ok\"}");
      }
      else
      {
        Serial.println("{\"error\":\"interval must be between 0 - 1000\"}");
      }
    }

    if (strcmp(cmd,drive)==0)
    {
      int newDriveThresh = doc["param"];
      if ((newDriveThresh >= 0) && (newDriveThresh <= 100))
      {
        driveThresh = newDriveThresh;
        Serial.println("{\"result\":\"ok\"}");
      }
      else
      {
        Serial.println("{\"error\":\"drive must be between 0 - 100 (inclusive)\"}");
      }
    }

    
    if (strcmp(cmd,brake)==0)
    {
      int newBrakeThresh = doc["param"];
      if ((newBrakeThresh >= 0) && (newBrakeThresh <= 100))
      {
        brakeThresh = newBrakeThresh;
        Serial.println("{\"result\":\"ok\"}");
      }
      else
      {
        Serial.println("{\"error\":\"break must be between 0 - 100 (inclusive)\"}");
      }
    }
    
    if (strcmp(cmd,stop)==0)
    {
      if (((SmState == STATE_DRIVING) || (SmState == STATE_STOPPED)))
      { 
        Serial.print("{\"result\":\"stopped\"");
        const char * param = doc["param"];
      
        if (strcmp(param, loaded)==0){
          //load is on
          digitalWrite_supervised(loadLed,HIGH); 
          digitalWrite_supervised(loadPin,HIGH); 
          loadMessage(HIGH);
          brakeStop = false;

        }
        else if (strcmp(param, unloaded)==0){
          //load is off
          digitalWrite_supervised(loadLed,LOW); 
          digitalWrite_supervised(loadPin,LOW); 
          loadMessage(LOW);
          brakeStop = false;
        }
        else if (strcmp(param, brake)==0){
          //load is off - else short circuit!
          digitalWrite_supervised(loadLed,LOW); 
          digitalWrite_supervised(loadPin,LOW); 
          loadMessage(LOW);
          brakeStop = true;
        }        
        Serial.print(",\"loaded\":");
        Serial.print(digitalRead_supervised(loadPin));
        Serial.print(",\"brake\":");
        Serial.print(brakeStop);
        Serial.print("}");
        SmState = STATE_STOPPED;
      }
      else
      {
        Serial.print("{\"error\":\"In wrong state to stop\"}");
      } 
  
    }//if stop
    
    if (strcmp(cmd,cal)==0)
    {
    
      if ((SmState == STATE_DRIVING) || (SmState == STATE_STOPPED))
      { 
        Serial.println("{\"result\":\"calibrating\"}");
        SmState = STATE_START_CALIBRATION;
      }
      else{
      
      Serial.println("{\"error\":\"In wrong state to calibrate\"}");
      }
    } //if cal

    if (strcmp(cmd,start)==0)
    {
    
      if ((SmState == STATE_DRIVING) || (SmState == STATE_STOPPED))
      { 

        int newStartDelay = doc["param"];
        if ((newStartDelay >= 0) && (newStartDelay <= 500))
        {
          startDelay = newStartDelay;

          Serial.println("{\"result\":\"starting\"}");
          SmState = STATE_START;
          
        }
        else
        {
          Serial.println("{\"error\":\"start must be between 0 - 500 [ms](exclusive)\"}");
        }
        

      }
      else{
      
      Serial.println("{\"error\":\"In wrong state to start\"}");
      }
    } //if cal

  } //if bytes available
  return SmState;
}
void Sm_Run(void)
{
  if (SmState < NUM_STATES)
  {
    if (debug){
      Serial.print("{\"State\":");
      Serial.print(SmState);
      Serial.println("}");
    }
    SmState = readSerialJSON(SmState);
    (*StateMachine[SmState].func)();
    
  }
  else{
    Serial.println("Exception in State Machine");
  }
  
}
