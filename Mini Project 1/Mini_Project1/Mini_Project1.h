/*
 * Mini_Project1.h
 *
 *  Created on: Aug 13, 2023
 *      Author: Esraa Khaled Mostafa
 */

#ifndef MINI_PROJECT1_H_
#define MINI_PROJECT1_H_

//preprocessor directive to include the engine temperature controller
//comment the following line if you do not want the engine temperature controller module
#define WITH_ENGINE_TEMP_CONTROLLER

//required values of speed based on traffic light sensor
#define G_Speed 100;
#define O_Speed 30
#define R_Speed 0

//required room temperature based on room temp sensor
#define R_Temperature 20

//required engine temperature based on engine temp sensor
#define E_Temperature 125

//enumerations for the controllers states
enum Bool
{
	OFF, ON
}AC_State, Engine_State, Engine_Temp_Controller_State;

//Functions prototypes
void Start_Menu(short* Speed, float* RoomTemperature, float*  EngineTemperature);
void Sensors_Set_Menu(short* Speed, float* RoomTemperature, float*  EngineTemperature);
void Traffic_Light_Controller(short* Speed, float* RoomTemperature, float*  EngineTemperature);
void AC_Controller(short* Speed, float* RoomTemperature, float*  EngineTemperature);
void Engine_Temperature_Controller(short* Speed, float* RoomTemperature, float*  EngineTemperature);
void DisplayVehicleState(short* Speed, float* RoomTemperature, float*  EngineTemperature);


#endif /* MINI_PROJECT1_H_ */
