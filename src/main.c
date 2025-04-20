#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITER 100
#define TOLERANCE 1e-6

void print_help() {
    printf("Usage: projectile <v0> <theta_deg> <m> <g> <k>\n");
    printf("Arguments:\n");
    printf("  v0:       Initial velocity (m/s)\n");
    printf("  theta_deg: Launch angle (degrees, 0-90)\n");
    printf("  m:        Mass (kg)\n");
    printf("  g:        Gravity (m/s^2)\n");
    printf("  k:        Air drag coefficient (kg/s, 0 for no drag)\n");
    printf("Example:\n");
    printf("  projectile 20 45 1 9.8 0.1\n");
}

void calculate_landing_point(double v0, double theta_deg, double m, double g, double k, 
                            double *x_f, double *t_f) {
    double theta = theta_deg * M_PI / 180.0;
    double vx0 = v0 * cos(theta);
    double vy0 = v0 * sin(theta);

    if (k == 0.0) {
        *t_f = 2.0 * vy0 / g;
        *x_f = vx0 * (*t_f);
    } else {
        double t = 2.0 * vy0 / g;
        int iter = 0;
        double y, y_prime, delta_t;

        do {
            double exp_term = exp(-(k / m) * t);
            y = (m / k) * (vy0 + (m * g) / k) * (1.0 - exp_term) - (m * g / k) * t;
            y_prime = (vy0 + (m * g) / k) * exp_term - (m * g / k);

            if (fabs(y_prime) < TOLERANCE) {
                printf("Warning: Zero derivative encountered\n");
                break;
            }

            delta_t = y / y_prime;
            t -= delta_t;
            iter++;

            if (iter >= MAX_ITER) {
                printf("Warning: Max iterations (%d) reached\n", MAX_ITER);
                break;
            }
        } while (fabs(delta_t) > TOLERANCE);

        *t_f = t;
        *x_f = (m * vx0 / k) * (1.0 - exp(-(k / m) * (*t_f)));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        print_help();
        return 1;
    }

    double v0 = atof(argv[1]);
    double theta_deg = atof(argv[2]);
    double m = atof(argv[3]);
    double g = atof(argv[4]);
    double k = atof(argv[5]);

    if (v0 <= 0 || theta_deg < 0 || theta_deg > 90 || m <= 0 || g <= 0 || k < 0) {
        printf("Error: Invalid parameters\n");
        print_help();
        return 1;
    }

    double x_f, t_f;
    calculate_landing_point(v0, theta_deg, m, g, k, &x_f, &t_f);

    printf("Input Parameters:\n");
    printf("  v0     = %.2f m/s\n", v0);
    printf("  theta  = %.2f deg\n", theta_deg);
    printf("  m      = %.2f kg\n", m);
    printf("  g      = %.2f m/s^2\n", g);
    printf("  k      = %.2f kg/s\n", k);
    printf("Results:\n");
    printf("  Distance = %.2f m\n", x_f);
    printf("  Time     = %.2f s\n", t_f);

    return 0;
}
