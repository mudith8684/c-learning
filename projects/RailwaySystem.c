#include <stdio.h>

struct Train {
    char name[30];
    int totalSeats;
    float baseFare;
};

struct Passenger {
    char name[30];
    int age;
    int coach;
    int seat;
    float fare;
};

#define COACHES 6
#define SEATS 72

int seats[COACHES][SEATS] = {0};

void showSeats();
void bookTickets(int *totalBookings, float *totalRevenue, float baseFare);
void cancelTicket(int *totalBookings, float *totalRevenue, float baseFare);
void showRevenue(int totalBookings, float totalRevenue);

int main() {
    int choice;
    int totalBookings = 0;
    float totalRevenue = 0;
    float baseFare = 500;

    do {
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. Show Seats\n");
        printf("4. Revenue Report\n");
        printf("0. Exit\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                bookTickets(&totalBookings, &totalRevenue, baseFare);
                break;
            case 2:
                cancelTicket(&totalBookings, &totalRevenue, baseFare);
                break;
            case 3:
                showSeats();
                break;
            case 4:
                showRevenue(totalBookings, totalRevenue);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while(choice != 0);

    return 0;
}

void bookTickets(int *totalBookings, float *totalRevenue, float baseFare) {
    int coach, seat;
    printf("Enter coach (1-%d): ", COACHES);
    scanf("%d", &coach);
    printf("Enter seat (1-%d): ", SEATS);
    scanf("%d", &seat);
    coach--;
    seat--;
    if(coach < 0 || coach >= COACHES || seat < 0 || seat >= SEATS) {
        printf("Invalid seat location.\n");
        return;
    }
    if(seats[coach][seat] == 1) {
        printf("Seat already booked.\n");
    } else {
        seats[coach][seat] = 1;
        (*totalBookings)++;
        (*totalRevenue) += baseFare;
        printf("Ticket booked successfully!\n");
    }
}

void cancelTicket(int *totalBookings, float *totalRevenue, float baseFare) {
    int coach, seat;
    printf("Enter coach (1-%d): ", COACHES);
    scanf("%d", &coach);
    printf("Enter seat (1-%d): ", SEATS);
    scanf("%d", &seat);
    coach--;
    seat--;
    if(coach < 0 || coach >= COACHES || seat < 0 || seat >= SEATS) {
        printf("Invalid seat location.\n");
        return;
    }
    if(seats[coach][seat] == 0) {
        printf("Seat already empty.\n");
    } else {
        seats[coach][seat] = 0;
        (*totalBookings)--;
        (*totalRevenue) -= baseFare;
        printf("Ticket cancelled successfully.\n");
    }
}

void showSeats() {
    for(int i = 0; i < COACHES; i++) {
        printf("Coach %d: ", i+1);
        for(int j = 0; j < SEATS; j++) {
            printf("%d ", seats[i][j]);
        }
        printf("\n");
    }
}

void showRevenue(int totalBookings, float totalRevenue) {
    printf("Total Bookings: %d\n", totalBookings);
    printf("Total Revenue: %.2f\n", totalRevenue);
}
