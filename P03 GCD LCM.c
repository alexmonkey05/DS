#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

// Pair 구조체: a와 b를 저장하여 유클리드 알고리즘의 상태를 나타냄
typedef struct {
    int a;
    int b;
} Pair;

// Stack 구조체: Pair를 저장하는 스택
typedef struct {
    Pair data[MAX_STACK_SIZE];
    int top;
} Stack;

// 스택 초기화
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비었는지 검사
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택이 가득 찼는지 검사
int isFull(Stack* s) {
    return s->top == MAX_STACK_SIZE - 1;
}

// 스택에 데이터 삽입
void push(Stack* s, Pair item) {
    if (isFull(s)) {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    s->data[++(s->top)] = item;
}

// 스택에서 데이터 삭제 및 반환
Pair pop(Stack* s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->data[(s->top)--];
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

    Stack stack;
    initStack(&stack);

    // 초기 상태를 스택에 푸시: (a, b)
    Pair p = { num1, num2 };
    push(&stack, p);

    int gcd = 0;
    // 유클리드 알고리즘을 스택을 이용해 반복 실행
    while (!isEmpty(&stack)) {
        Pair current = pop(&stack);
        if (current.b == 0) {
            gcd = current.a;
            break;
        }
        else {
            Pair next = { current.b, current.a % current.b };
            push(&stack, next);
        }
    }

    // 최소공배수 LCM = (a * b) / gcd
    int lcm = (original_a * original_b) / gcd;

    fprintf(outputFile, "최대공약수: %d\n", gcd);
    fprintf(outputFile, "최소공배수: %d\n", lcm);
    fclose(outputFile);

    return 0;
}