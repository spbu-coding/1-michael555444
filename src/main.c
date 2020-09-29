#include <stdio.h>
#include <math.h>
#include <string.h>

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

double meth_simp(int N) {
    double x_cord, h_cord, intgrl;
    h_cord = (rght_brdr - lft_brdr) / 2 / N;
    intgrl = sin(lft_brdr) + sin(rght_brdr);
    x_cord = lft_brdr + h_cord;
    for (int answr = 1; answr < 2 * N; answr++) {
        if (answr % 2 == 0) intgrl += 2 * sin(x_cord);
        else intgrl += 4 * sin(x_cord);
        x_cord += h_cord;
    }
    intgrl *= h_cord / 3;
    return intgrl;
}

void call(int a[6]) {
    char middle_line[15];
    for (int answr = 0; answr < 6; answr++) {
        double intgrl_rect, intgrl_simp;
        intgrl_rect = meth_rect(a[answr]);
        intgrl_simp = meth_simp(a[answr]);
        sprintf(middle_line, "%d", a[answr]);
        strcat(answer[answr], middle_line);
        strcat(answer[answr], " ");
        sprintf(middle_line, "%2.5f", intgrl_rect);
        strcat(answer[answr], middle_line);
        strcat(answer[answr], " ");
        sprintf(middle_line, "%2.5f", intgrl_simp);
        strcat(answer[answr], middle_line);
    }
}

int enter_numbers() {
    printf("Enter interval's left border: ");
    while (!(scanf("%lf", &lft_brdr))) {
        printf("Error! Enter again: ");
        while (getchar() != '\n');
    }
    if (lft_brdr < 0)
        return 1;
    printf("Enter interval's right border: ");
    while (!(scanf("%lf", &rght_brdr))) {
        printf("Error! Enter again: ");
        while (getchar() != '\n');
    }
    if (rght_brdr > M_PI)
        return 2;
}

int main() {
    int segments[] = {6, 10, 20, 100, 500, 1000};
    int errors = enter_numbers();
    if (errors == 1) {
        printf("Error left border. ErrorId: 1.");
        return 1;
    }
    if (errors == 2) {
        printf("Error right border. ErrorId: 2.");
        return 2;
    }
    call(segments);
    for (int answr = 0; answr < 6; answr++) {
        printf("%s\n", answer[answr]);
    }
    return 0;
}
