/*
 * Mini_Project1.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Esraa Khaled Mostafa
 */

#include <stdio.h>
#include "Mini_Project1.h"


//function to get the desired value from the user in the beginning of the program
void Start_Menu(short* Speed, float* RoomTemperature, float* EngineTemperature)
{
	char UserValue;
	//input validation
	do
	{
		printf("Start Menu: \n");
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n");
		scanf(" %c",&UserValue);
		while(getchar()!='\n'); //this lines just clears the unused characters from the input buffer if wrong data is entered
	}while(!((UserValue == 'a') || (UserValue == 'c')));

	switch(UserValue)
	{
	case('a'):
			{
		//go to the sensors set menu to choose required action from it
		printf("Turn on the vehicle engine\n\n");
		Engine_State = ON;
		Sensors_Set_Menu(Speed, RoomTemperature, EngineTemperature);
		break;
			}

	case('c'):
			{
		//ending the program
		printf("Quit the system\n\n");
		return;
			}
	}
}


//function to choose the desired action after starting the engine
void Sensors_Set_Menu(short* Speed, float* RoomTemperature, float* EngineTemperature)
{
	char UserValue;
	//input validation
	do
	{
		printf("Sensors set menu: \n");
		printf("a. Turn off the engine\n");
		printf("b. Set the traffic light color\n");
		printf("c. Set the room temperature(Temperature Sensor)\n");

		//preprocessor directive to choose whether to include the engine temperature control functionality or not
#ifdef WITH_ENGINE_TEMP_CONTROLLER
		printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
#endif

		scanf(" %c",&UserValue);
		while(getchar()!='\n');
	}while(!((UserValue == 'a') || (UserValue == 'b') || (UserValue == 'c') || (UserValue == 'd')));

	switch(UserValue)
	{
	case('a'):
			{
		//turning off the engine would lead to going back to the start menu
		printf("Turn off the engine\n\n");
		Engine_State = OFF;
		Start_Menu(Speed, RoomTemperature, EngineTemperature);
		break;
			}
	case('b'):
			{
		//calling the traffic light function to adjust the speed
		printf("Set the traffic light color\n\n");
		Traffic_Light_Controller(Speed, RoomTemperature, EngineTemperature);
		break;
			}
	case('c'):
			{
		//calling the AC function to adjust the room temperature
		printf("Set the room temperature(Temperature Sensor)\n\n");
		AC_Controller(Speed, RoomTemperature, EngineTemperature);
		break;
			}

	//if we used this preprocessor directive above it would not be useful to check for this case here
#ifdef WITH_ENGINE_TEMP_CONTROLLER
	case('d'):
			{
		printf("Set the engine temperature (Engine Temperature Sensor)\n\n");
		Engine_Temperature_Controller(Speed, RoomTemperature, EngineTemperature);
		break;
			}
#endif
	}

}

//function to adjust the vehicle speed according to the traffic light sensor
void Traffic_Light_Controller(short* Speed, float* RoomTemperature, float* EngineTemperature)
{
	char TrafficLightSensor;
	//input validation
	do
	{
		printf("Enter the Traffic Light Sensor Value (G/O/R): \n");
		scanf(" %c",&TrafficLightSensor);
		while(getchar()!='\n');
	}while(!((TrafficLightSensor == 'G') || (TrafficLightSensor == 'O') || (TrafficLightSensor == 'R')));

	switch(TrafficLightSensor)
	{
	case('G'):
			{
		*Speed = G_Speed;
		break;
			}
	case('O'):
			{
		*Speed = O_Speed;
		break;
			}
	case('R'):
			{
		*Speed = R_Speed;
		break;
			}
	}
	//after processing the values we need to display all the states of the vehicle
	DisplayVehicleState(Speed, RoomTemperature, EngineTemperature);
}


//function to adjust the AC state and the room temperature according to the room temperature sensor
void AC_Controller(short* Speed, float* RoomTemperature, float* EngineTemperature)
{
	printf("Enter the Room Temperature Sensor Value: \n");
	scanf("%f",RoomTemperature);

	if((*RoomTemperature < 10) || (*RoomTemperature > 30))
	{
		AC_State = ON;
		*RoomTemperature = R_Temperature;
	}
	else
	{
		AC_State = OFF;
	}
	//after processing the values we need to display all the states of the vehicle
	DisplayVehicleState(Speed, RoomTemperature, EngineTemperature);
}


//function to adjust the engine temperature controller depending on the engine temperature sensor
//it will be called only in case WITH_ENGINE_TEMP_CONTROLLER macro was defined
void Engine_Temperature_Controller(short* Speed, float* RoomTemperature, float* EngineTemperature)
{
	printf("Enter the Engine Temperature Sensor Value: \n");
	scanf("%f",EngineTemperature);

	if((*EngineTemperature < 100) || (*EngineTemperature > 150))
	{
		Engine_Temp_Controller_State = ON;
		*EngineTemperature = E_Temperature;
	}
	else
	{
		Engine_Temp_Controller_State = OFF;
	}
	//after processing the values we need to display all the states of the vehicle
	DisplayVehicleState(Speed, RoomTemperature, EngineTemperature);
}



void DisplayVehicleState(short* Speed, float* RoomTemperature, float* EngineTemperature)
{
	//need to check before displaying any values that the speed != 30
	//if speed == 30 we will need to process the data again before displaying
	if(*Speed == 30)
	{
		AC_State = ON;
		*RoomTemperature = *RoomTemperature *(5.0/4) + 1;
		//works only if WITH_ENGINE_TEMP_CONTROLLER macro was defined
#ifdef WITH_ENGINE_TEMP_CONTROLLER
		Engine_Temp_Controller_State = ON;
		*EngineTemperature = *EngineTemperature *(5.0/4) + 1;
#endif
	}
	//in case the speed != 30 will display all the vehicle state with the present and modified values
	//checking for the engine state to print the correct corresponding one
	if(Engine_State == ON)
	{
		printf("Engine State is ON \n");
	}
	else
	{
		printf("Engine State is OFF \n");
	}

	//checking for the AC state to print the correct corresponding one
	if(AC_State == ON)
	{
		printf("AC is ON \n");
	}
	else
	{
		printf("AC is OFF \n");
	}

	printf("Vehicle Speed: %d Km/hr\n", *Speed);
	printf("Room Temperature: %0.2f \n", *RoomTemperature);

	//no need to print the values of the engine temperature controller if the WITH_ENGINE_TEMP_CONTROLLER macro was not defined
#ifdef WITH_ENGINE_TEMP_CONTROLLER
	if(Engine_Temp_Controller_State == ON)
	{
		printf("Engine Temperature Controller is ON \n");
	}
	else
	{
		printf("Engine Temperature Controller is OFF \n");
	}
	printf("Engine Temperature: %0.2f \n", *EngineTemperature);
#endif

	printf("\n\n");
	//calling the set menu again after any display for further actions
	Sensors_Set_Menu(Speed, RoomTemperature, EngineTemperature);
}


int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	//initial values to be passed to the functions
	short Speed = 60;
	float RoomTemperature = 25;
	float EngineTemperature = 90;

	//starting the program
	Start_Menu(&Speed, &RoomTemperature, &EngineTemperature);



	return 0;
}
