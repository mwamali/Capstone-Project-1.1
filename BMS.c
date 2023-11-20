#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSENGERS 100
#define MAX_USERS 10

// Structure to represent a bus
struct Bus {
    int busNumber;
    int capacity;
    char model[50];
};

// Structure to represent a bus schedule
struct Schedule {
    int busNumber;
    char departureTime[10];
    char arrivalTime[10];
};

// Structure to represent a passenger
struct Passenger {
    int busNumber;
    char name[50];
    int age;
    int ticketNumber;
};

// Structure to represent user credentials
struct User {
    char username[50];
    char password[50];
    int role; // 1: admin, 2: operator, etc.
};

// Function to generate a ticket number
int generateTicketNumber() {
    static int ticketCounter = 1000; // Starting ticket number
    return ticketCounter++;
}

// Function to add a new bus
void addBus(struct Bus buses[], int *busCount) {
    struct Bus newBus;
    printf("Enter bus number: ");
    scanf("%d", &newBus.busNumber);
    printf("Enter capacity: ");
    scanf("%d", &newBus.capacity);
    printf("Enter model: ");
    scanf("%s", newBus.model);

    buses[*busCount] = newBus;
    (*busCount)++;
    printf("Bus added successfully!\n");
}

// Function to display all buses
void displayBuses(struct Bus buses[], int busCount) {
    printf("Buses in the system:\n");
    for (int i = 0; i < busCount; i++) {
        printf("Bus Number: %d | Capacity: %d | Model: %s\n",
               buses[i].busNumber, buses[i].capacity, buses[i].model);
    }
}

// Function to update bus details
void updateBus(struct Bus buses[], int busCount) {
    int searchBusNumber;
    printf("Enter the bus number to update: ");
    scanf("%d", &searchBusNumber);

    for (int i = 0; i < busCount; i++) {
        if (buses[i].busNumber == searchBusNumber) {
            printf("Enter new capacity: ");
            scanf("%d", &buses[i].capacity);
            printf("Enter new model: ");
            scanf("%s", buses[i].model);
            printf("Bus details updated!\n");
            return;
        }
    }
    printf("Bus not found!\n");
}

// Function to delete a bus
void deleteBus(struct Bus buses[], int *busCount) {
    int searchBusNumber;
    printf("Enter the bus number to delete: ");
    scanf("%d", &searchBusNumber);

    for (int i = 0; i < *busCount; i++) {
        if (buses[i].busNumber == searchBusNumber) {
            for (int j = i; j < *busCount - 1; j++) {
                buses[j] = buses[j + 1];
            }
            (*busCount)--;
            printf("Bus deleted!\n");
            return;
        }
    }
    printf("Bus not found!\n");
}

// Function to create a new schedule
void createSchedule(struct Schedule schedules[], int *scheduleCount) {
    struct Schedule newSchedule;
    printf("Enter bus number for the schedule: ");
    scanf("%d", &newSchedule.busNumber);
    printf("Enter departure time (HH:MM): ");
    scanf("%s", newSchedule.departureTime);
    printf("Enter arrival time (HH:MM): ");
    scanf("%s", newSchedule.arrivalTime);

    schedules[*scheduleCount] = newSchedule;
    (*scheduleCount)++;
    printf("Schedule created successfully!\n");
}

// Function to display all schedules
void displaySchedules(struct Schedule schedules[], int scheduleCount) {
    printf("Bus Schedules:\n");
    for (int i = 0; i < scheduleCount; i++) {
        printf("Bus Number: %d | Departure: %s | Arrival: %s\n",
               schedules[i].busNumber, schedules[i].departureTime, schedules[i].arrivalTime);
    }
}

// Function to add a new passenger with a ticket
void addPassengerWithTicket(struct Passenger passengers[], int *passengerCount) {
    if (*passengerCount >= MAX_PASSENGERS) {
        printf("Maximum passengers reached. Cannot add more passengers.\n");
        return;
    }

    struct Passenger newPassenger;
    printf("Enter bus number: ");
    scanf("%d", &newPassenger.busNumber);
    printf("Enter passenger name: ");
    scanf("%s", newPassenger.name);
    printf("Enter passenger age: ");
    scanf("%d", &newPassenger.age);

    newPassenger.ticketNumber = generateTicketNumber();
    passengers[*passengerCount] = newPassenger;
    (*passengerCount)++;
    printf("Passenger added successfully! Ticket Number: %d\n", newPassenger.ticketNumber);
}

// Function to display passengers for a specific bus
void displayPassengers(struct Passenger passengers[], int passengerCount, int busNumber) {
    printf("Passengers for Bus Number %d:\n", busNumber);
    int found = 0;
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].busNumber == busNumber) {
            printf("Name: %s | Age: %d\n", passengers[i].name, passengers[i].age);
            found = 1;
        }
    }
    if (!found) {
        printf("No passengers found for this bus.\n");
    }
}

// Function to display ticket details for a specific passenger
void displayTicketDetails(struct Passenger passengers[], int passengerCount, int ticketNumber) {
    int found = 0;
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].ticketNumber == ticketNumber) {
            printf("Ticket Number: %d | Passenger Name: %s | Bus Number: %d\n",
                   passengers[i].ticketNumber, passengers[i].name, passengers[i].busNumber);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Ticket not found.\n");
    }
}

// Function to perform user authentication
int authenticateUser(struct User users[], int userCount, char username[], char password[]) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return users[i].role; // Return the user's role if authentication succeeds
        }
    }
    return -1; // Return -1 if authentication fails
}

int main() {
    struct Bus buses[50]; // Assuming a maximum of 50 buses
    struct Schedule schedules[50]; // Assuming a maximum of 50 schedules
    struct Passenger passengers[MAX_PASSENGERS]; // Assuming a maximum of 100 passengers
    struct User users[MAX_USERS]; // Assuming a maximum of 10 users
    int busCount = 0;
    int scheduleCount = 0;
    int passengerCount = 0;
    int userCount = 0;
    int choice;

    // Adding sample users (you can expand this)
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "adminpass");
    users[0].role = 1; // Admin role

    strcpy(users[1].username, "operator");
    strcpy(users[1].password, "operatorpass");
    users[1].role = 2; // Operator role

    userCount = 2; // Update the user count

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int role = authenticateUser(users, userCount, username, password);
    if (role != -1) {
        printf("Authentication successful! User role: %d\n", role);
        // Add logic here to grant access based on the user's role

        do {
            printf("\nBus Management System\n");
            printf("1. Add Bus\n");
            printf("2. Display Buses\n");
            printf("3. Update Bus Details\n");
            printf("4. Delete Bus\n");
            printf("5. Create Schedule\n");
            printf("6. Display Schedules\n");
            printf("7. Add Passenger with Ticket\n");
            printf("8. Display Passengers for Bus\n");
            printf("9. Display Ticket Details\n");
            printf("10. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addBus(buses, &busCount);
                    break;
                case 2:
                    displayBuses(buses, busCount);
                    break;
                case 3:
                    updateBus(buses, busCount);
                    break;
                case 4:
                    deleteBus(buses, &busCount);
                    break;
                case 5:
                    createSchedule(schedules, &scheduleCount);
                    break;
                case 6:
                    displaySchedules(schedules, scheduleCount);
                    break;
                case 7:
                    addPassengerWithTicket(passengers, &passengerCount);
                    break;
                case 8: {
                    int busNumber;
                    printf("Enter bus number: ");
                    scanf("%d", &busNumber);
                    displayPassengers(passengers, passengerCount, busNumber);
                    break;
                }
                case 9: {
                    int ticketNumber;
                    printf("Enter ticket number: ");
                    scanf("%d", &ticketNumber);
                    displayTicketDetails(passengers, passengerCount, ticketNumber);
                    break;
                }
                case 10:
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice! Try again.\n");
            }
        } while (choice != 10);
    } else {
        printf("Authentication failed. Invalid username or password.\n");
    }

    return 0;
}

