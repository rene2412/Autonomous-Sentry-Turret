#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>
#include <softPwm.h>

#define Trig            0
#define Echo            1
#define ServoPin        2
#define BigServoPin     3

long Map(long value, long fromLow, long fromHigh, long toLow, long toHigh){
    return (toHigh-toLow)*(value-fromLow) / (fromHigh-fromLow) + toLow;
}

void setAngle(int pin, int angle) {    //Create a funtion to control the angle of the servo.
    if(angle < 0)
        angle = 0;
:    if(angle > 180)
        angle = 180;
    softPwmWrite(pin,Map(angle, 0, 180, 5, 25));
}

void ultraInit(void) {
    pinMode(Echo, INPUT);
    pinMode(Trig, OUTPUT);
}

float disMeasure(void) {
    struct timeval tv1;
    struct timeval tv2;
    long time1, time2;
    float dis;

    digitalWrite(Trig, LOW);
    delayMicroseconds(2);

    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
 digitalWrite(Trig, LOW);

    while(!(digitalRead(Echo) == 1));
    gettimeofday(&tv1, NULL);

    while(!(digitalRead(Echo) == 0));
    gettimeofday(&tv2, NULL);

    time1 = tv1.tv_sec * 1000000 + tv1.tv_usec;
    time2  = tv2.tv_sec * 1000000 + tv2.tv_usec;

    dis = (float)(time2 - time1) / 1000000 * 34000 / 2;

    return dis;
}

int main(void) {
    float dis;
    if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !");
        return 1;
    }

    ultraInit();
    softPwmCreate(ServoPin, 4, 200);
    softPwmCreate(ServoPin, 4, 200);
   int angle = 0;
   int turn = 1;
   while(1) {
        if (turn == 1) {
                if (angle = 180) {
                        turn = 0;
                }
                angle += 1;}
      } else {
 if (angle == 0) {
                        turn = 1;
                }
                angle -= 1;
        }

        dis = disMeasure();

        if (dis <= 25) {
                setAngle(BigServoPin, angle);
                printf("In Range: ");
        }
        printf("0.2f cm\n\n", dis);
        setAngle(ServoPin, angle);
        delay(10);
   }

return 0;
}

