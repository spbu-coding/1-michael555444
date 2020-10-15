#include <stdio.h>
#include <math.h>
#include <string.h>

#define error(...) (fprintf(stderr, __VA_ARGS__))

double lft_brdr, rght_brdr;
char answer[4][25];

double meth_rect(int N) {
    double x_cord, h_cord, intgrl = 0;
    h_cord = (rght_brdr - lft_brdr) / N;
    x_cord = lft_brdr;
    for (int answr = 0; answr < N; answr++) {
        intgrl += sin(x_cord + h_cord / 2) * h_cord;
        x_cord += h_cord;
    }
    return intgrl;
}

double meth_simp(int parts_count) {
    double x_cord, h_cord, intgrl;
    h_cord = (rght_brdr - lft_brdr) / 2 / parts_count;
    intgrl = sin(lft_brdr) + sin(rght_brdr);
    x_cord = lft_brdr + h_cord;
    for (int answr = 1; answr < 2 * parts_count; answr++) {
        if (answr % 2 == 0) intgrl += 2 * sin(x_cord);
        else intgrl += 4 * sin(x_cord);
        x_cord += h_cord;
    }
    intgrl *= h_cord / 3;
    return intgrl;
}

void calcul_intgrl(int *a, int segments_length) {
    char middle_line[15];
    for (int i = 0; i < segments_length; i++) {
        double intgrl_rect, intgrl_simp;
        intgrl_rect = meth_rect(a[i]);
        intgrl_simp = meth_simp(a[i]);
        sprintf(middle_line, "%d", a[i]);
        strcat(answer[i], middle_line);
        strcat(answer[i], " ");
        sprintf(middle_line, "%2.5f", intgrl_rect);
        strcat(answer[i], middle_line);
        strcat(answer[i], " ");
        sprintf(middle_line, "%2.5f", intgrl_simp);
        strcat(answer[i], middle_line);
    }
}

int enter_numbers() {
    printf("Enter interval's left border: ");
    while (!(scanf("%lf", &lft_brdr))) {
        printf("Error! Enter again: ");
        while (getchar() != '\n');
    }
    if (lft_brdr < 0) {
        error("Error. Left border should be bigger than 0.");
        return -1;
    }
    printf("Enter interval's right border: ");
    while (!(scanf("%lf", &rght_brdr))) {
        printf("Error! Enter again: ");
        while (getchar() != '\n');
    }
    if (rght_brdr < lft_brdr) {
        error("Error. Right border should be bigger than left border.");
        return -1;
    }
    if (rght_brdr > M_PI) {
        error("Error. Right border should be less than PI.");
        return -1;
    }
    return 0;
}

int main() {
    int segments[] = {6, 10, 20, 100, 500, 1000};
    if (enter_numbers()) {
        return -1;
    }
    int const segments_length = sizeof(segments) / sizeof(int);
    calcul_intgrl(segments, segments_length);
    for (int i = 0; i < segments_length; i++) {
        printf("%s\n", answer[i]);
    }
    return 0;
}
