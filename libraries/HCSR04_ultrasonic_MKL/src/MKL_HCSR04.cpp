#include "MKL_HCSR04.h"
////////////////////////////////////consttruct/destruct
void MKL_HCSR04::init(int out, int echo[], int n)
{
	this->out = out;
	this->echo = echo;
	this->n = n;
	pinMode(this->out, OUTPUT);
	for (int i = 0; i < n; i++)
		pinMode(this->echo[i], INPUT);
}
MKL_HCSR04::MKL_HCSR04(int out, int echo) { this->init(out, new int[1]{echo}, 1); }
MKL_HCSR04::MKL_HCSR04(int out, int echo[], int n) { this->init(out, echo, n); }
MKL_HCSR04::~MKL_HCSR04()
{
	~this->out;
	delete[] this->echo;
	~this->n;
}

///////////////////////////////////////////////////dist
float MKL_HCSR04::dist(int n) const
{
	digitalWrite(this->out, LOW);
	delayMicroseconds(2);
	digitalWrite(this->out, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->out, LOW);
	// noInterrupts();	// bug for RC servo
	float d = pulseIn(this->echo[n], HIGH, 23529.4); // max sensor dist ~4m
	// interrupts();
	return d / 58.8235;
}
float MKL_HCSR04::dist() const { return this->dist(0); }
