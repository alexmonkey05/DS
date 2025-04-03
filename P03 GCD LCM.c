#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

// Pair 구조체: a와 b를 저장하여 유클리드 알고리즘의 상태를 나타냄
typedef struct {
    int a;
    int b;
} Pair;

typedef Pair Element; // 스택 요소 타입을 Pair로 정의

// 스택의 데이터 및 관련 변수
Element data[MAX_STACK_SIZE]; // 스택 요소의 배열
int top; // 스택 상단 인덱스

void error(char str[]) {
    printf("%s\n", str);
    exit(1);
}

// 스택 초기화
void init_stack() {
    top = -1;
}

// 스택이 비었는지 검사
int is_empty() {
    return top == -1;
}

// 스택이 가득 찼는지 검사
int is_full() {
    return top == (MAX_STACK_SIZE - 1);
}

// 스택에 데이터 삽입
void push(Element e) {
    if (is_full())
        error("Overflow Error!");
    else
        data[++top] = e;
}

// 스택에서 데이터 삭제 및 반환
Element pop() {
    if (is_empty())
        error("Underflow Error!");
    return data[top--];
}

// 스택에서 최상단 요소 확인
Element peek() {
    if (is_empty())
        error("Underflow Error!");
    return data[top];
}

// 스택 크기 반환
int size() {
    return top + 1;
}

int main(void) {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (!inputFile || !outputFile) {
        fprintf(stderr, "파일을 열 수 없습니다.\n");
        return 1;
    }

    int num1, num2;
    if (fscanf(inputFile, "%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "잘못된 입력\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }
    fclose(inputFile);

    // 최소공배수 계산을 위해 원래 입력값 저장
    int original_a = num1;
    int original_b = num2;

    init_stack();

    // 초기 상태를 스택에 푸시: (a, b)
    Pair p = { num1, num2 };
    push(p);

    int gcd = 0;
    // 유클리드 알고리즘을 스택을 이용해 반복 실행
    while (!is_empty()) {
        Pair current = pop();
        if (current.b == 0) {
            gcd = current.a;
            break;
        }
        else {
            Pair next = { current.b, current.a % current.b };
            push(next);
        }
    }

    // 최소공배수 LCM = (a * b) / gcd
    int lcm = (original_a * original_b) / gcd;

    fprintf(outputFile, "최대공약수: %d\n", gcd);
    fprintf(outputFile, "최소공배수: %d\n", lcm);
    fclose(outputFile);

    return 0;
}
