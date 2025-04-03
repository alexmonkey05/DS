#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define TIME_STEPS 10  // 비교할 시간 단계 수
#define MAX_DEGREE 1001

// 다항식 구조체 정의
typedef struct
{
    int degree;
    float coef[MAX_DEGREE];
} Polynomial;

// 다항식 평가 함수 (x에 대한 다항식 값 계산)
float evaluate(Polynomial p, float x)
{
    float result = p.coef[0]; // 상수항부터 시작
    float mul = 1;            // x^i 계산을 위한 변수
    for (int i = 1; i <= p.degree; i++)
    {
        mul *= x;
        result += p.coef[i] * mul;
    }
    return result;
}

int main()
{
    FILE* fin = fopen("input.txt", "r");
    if (fin == NULL)
    {
        printf("입력 파일을 여는 데 실패했습니다.\n");
        return 1;
    }

    FILE* fout = fopen("output.txt", "w");
    if (fout == NULL)
    {
        printf("출력 파일을 여는 데 실패했습니다.\n");
        fclose(fin);
        return 1;
    }

    // A, B, C, goal 포물선(다항식) 선언
    Polynomial A, B, C, goal;

    // 파일로부터 각 다항식 읽기
    // 각 줄: degree coef0 coef1 ... coef[degree]
    fscanf(fin, "%d", &A.degree);
    for (int i = 0; i <= A.degree; i++)
    {
        fscanf(fin, "%f", &A.coef[i]);
    }

    fscanf(fin, "%d", &B.degree);
    for (int i = 0; i <= B.degree; i++)
    {
        fscanf(fin, "%f", &B.coef[i]);
    }

    fscanf(fin, "%d", &C.degree);
    for (int i = 0; i <= C.degree; i++)
    {
        fscanf(fin, "%f", &C.coef[i]);
    }

    fscanf(fin, "%d", &goal.degree);
    for (int i = 0; i <= goal.degree; i++)
    {
        fscanf(fin, "%f", &goal.coef[i]);
    }

    fclose(fin);

    double total_diff_A = 0, total_diff_B = 0, total_diff_C = 0;

    // 시간 단계별로 goal 다항식과 A, B, C와의 차이(절대값)를 누적
    for (int t = 0; t < TIME_STEPS; t++)
    {
        double y_goal = evaluate(goal, t);
        double yA = evaluate(A, t);
        double yB = evaluate(B, t);
        double yC = evaluate(C, t);

        total_diff_A += fabs(y_goal - yA);
        total_diff_B += fabs(y_goal - yB);
        total_diff_C += fabs(y_goal - yC);
    }

    // 누적 오차가 가장 작은 다항식을 결정
    char closest;
    if (total_diff_A <= total_diff_B && total_diff_A <= total_diff_C)
    {
        closest = 'A';
    }
    else if (total_diff_B <= total_diff_A && total_diff_B <= total_diff_C)
    {
        closest = 'B';
    }
    else
    {
        closest = 'C';
    }

    fprintf(fout, "goal 포물선과 가장 가까운 다항식: %c\n", closest);
    fclose(fout);

    return 0;
}
