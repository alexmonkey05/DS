#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>  // sqrt() 사용을 위한 헤더

typedef struct
{
    double x;
    double y;
} Point;

typedef struct
{
    double x;
    double y;
} Vector2;

Vector2 cal_gravity(double sec, Vector2 person, Vector2 gravity);

int main()
{
    double frame = 0.1; //점의 위치를 찍는 시간의 텀
    Vector2 gravity = { 0, -9.8 };
    Point highest = { 0, 0 };
    Point present = { 0, 0 };
    Vector2 speed;
    printf("초기 속도를 설정[x y]로 입력: ");
    scanf("%lf %lf", &speed.x, &speed.y);
    while (present.y >= 0)
    {
        present.x += speed.x * frame;
        present.y += speed.y * frame;
        if (present.y > 0) {
            speed = cal_gravity(frame, speed, gravity);
        }
        if (present.y > highest.y)
        {
            highest.x = present.x;
            highest.y = present.y;
        }
    }
    present.x -= speed.x * frame;
    present.y -= speed.y * frame;
    present.x = present.x - speed.x * (present.y / speed.y);
    present.y = 0;
    printf("도착 지점: (%.2lf, %.2lf) ", present.x, present.y);
    printf("최고점: (%.2lf, %.2lf) \n", highest.x, highest.y);
}



Vector2 cal_gravity(double sec, Vector2 speed, Vector2 gravity)
{
    speed.y += gravity.y * sec;
    return speed;
}