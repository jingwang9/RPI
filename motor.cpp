
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

static int pin_A, pin_B, pin_E;

void set_L293D(int value)
{
        if(value == 0) {
                digitalWrite(pin_A, HIGH);
                digitalWrite(pin_B, LOW);
                digitalWrite(pin_E, LOW);
        } else {
                digitalWrite(pin_A, HIGH);
                digitalWrite(pin_B, LOW);
                digitalWrite(pin_E, HIGH);
        }
}

void init_L293D(int pinA, int pinB, int pinE)
{
        pin_A = pinA;
        pin_B = pinB;
        pin_E = pinE;
        wiringPiSetup();
        pinMode(pin_E, OUTPUT);
        pinMode(pin_A, OUTPUT);
        pinMode(pin_B, OUTPUT);
}

int main(int argc, char**argv)
{
        pin_A = 16;
        pin_B = 18;
        pin_E = 22;
        wiringPiSetup();
        pinMode(pin_A, OUTPUT);
        pinMode(pin_B, OUTPUT);
        pinMode(pin_E, OUTPUT);
        digitalWrite(pin_A, HIGH);
        digitalWrite(pin_B, LOW);
        digitalWrite(pin_E, HIGH);
        while(1) {
                sleep(2);
                digitalWrite(pin_E, LOW);
                sleep(2);
                digitalWrite(pin_E, HIGH);
        }
        /*
        int value;
        init_L293D(16,18,22);
        while(1) {
                set_L293D(0);
                sleep(2);
                set_L293D(1);
                sleep(2);
        }
        */
        return 0;
}
