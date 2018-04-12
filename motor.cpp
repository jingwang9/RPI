
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

static int pin_A, pin_B, pin_E;

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

void init_L293D(int pinA, int pinB, int pinE)
{
        pin_A = pinA;
        pin_B = pinB;
        pin_E = pinE;
        pinMode(pin_E, OUTPUT);
        pinMode(pin_A, OUTPUT);
        pinMode(pin_B, OUTPUT);
        wiringPisetup();
        set(0);
}

int main(int argc, char**argv)
{
        int value;
        init_L293D(16,18,22);
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
