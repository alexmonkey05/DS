#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

// Pair ����ü: a�� b�� �����Ͽ� ��Ŭ���� �˰����� ���¸� ��Ÿ��
typedef struct {
    int a;
    int b;
} Pair;

// Stack ����ü: Pair�� �����ϴ� ����
typedef struct {
    Pair data[MAX_STACK_SIZE];
    int top;
} Stack;

// ���� �ʱ�ȭ
void initStack(Stack* s) {
    s->top = -1;
}

// ������ ������� �˻�
int isEmpty(Stack* s) {
    return s->top == -1;
}

// ������ ���� á���� �˻�
int isFull(Stack* s) {
    return s->top == MAX_STACK_SIZE - 1;
}

// ���ÿ� ������ ����
void push(Stack* s, Pair item) {
    if (isFull(s)) {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    s->data[++(s->top)] = item;
}

// ���ÿ��� ������ ���� �� ��ȯ
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
        fprintf(stderr, "������ �� �� �����ϴ�.\n");
        return 1;
    }

    int num1, num2;
    if (fscanf(inputFile, "%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "�߸��� �Է�\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }
    fclose(inputFile);

    // �ּҰ���� ����� ���� ���� �Է°� ����
    int original_a = num1;
    int original_b = num2;

    Stack stack;
    initStack(&stack);

    // �ʱ� ���¸� ���ÿ� Ǫ��: (a, b)
    Pair p = { num1, num2 };
    push(&stack, p);

    int gcd = 0;
    // ��Ŭ���� �˰����� ������ �̿��� �ݺ� ����
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

    // �ּҰ���� LCM = (a * b) / gcd
    int lcm = (original_a * original_b) / gcd;

    fprintf(outputFile, "�ִ�����: %d\n", gcd);
    fprintf(outputFile, "�ּҰ����: %d\n", lcm);
    fclose(outputFile);

    return 0;
}