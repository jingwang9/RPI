#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>

static int pin_A, pin_B, pin_E;
void set_L293D(int);
void init_L293D()
{
    pin_A = 16;
    pin_B = 18;
    pin_E = 22;
    pinMode(pin_E, OUTPUT);
    pinMode(pin_A, OUTPUT);
    pinMode(pin_B, OUTPUT);
    set_L293D(0);
}

void set_L293D(int value)
{
    if(value == 0) {
        digitalWrite(pin_E, LOW);
    } else if(value > 0 && value <= 255) {
        digitalWrite(pin_E, LOW);
        digitalWrite(pin_A, HIGH);
        digitalWrite(pin_B, LOW);
        analogWrite(pin_E, value);
    } else if(value < 0 && value >= -255) {
        digitalWrite(pin_E, LOW);
        digitalWrite(pin_A, LOW);
        digitalWrite(pin_B, HIGH);
        analogWrite(pin_E, value);
    }
}

int main(int argc, char**argv)
{
    int pin_A, pinB, pinE;
    int value;
    init_L293D();
    while(1) {
        printf("Input the value\n");
        scanf("%d", &value);
        if(value>255||value<-255) {
            printf("Invalid value(Must -255~255)\n");
            continue;
        }
        set_L293D(value);
    }
    return 0;
}
