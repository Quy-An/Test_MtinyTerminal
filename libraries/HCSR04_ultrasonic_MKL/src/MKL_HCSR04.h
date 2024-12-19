#pragma once
#include <Arduino.h>

class MKL_HCSR04
{
public:
	MKL_HCSR04(int out, int echo);			//initialisation class MKL_HCSR04 (trig pin , echo pin)
	MKL_HCSR04(int out, int echo[], int n); //initialisation class MKL_HCSR04 (trig pin , echo pin)
	~MKL_HCSR04();							//destructor
	float dist() const;					//return curent distance of element 0
	float dist(int n) const;			//return curent distance of element n

private:
	void init(int out, int echo[], int n); //for constructor
	int out;							   //out pin
	int *echo;							   //echo pin list
	int n;								   //number of el
};
