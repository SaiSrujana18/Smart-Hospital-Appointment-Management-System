#include "hospital.h"


/* =========================
   GLOBAL DATA STRUCTURES
   ========================= */

Patient *patientHead = NULL;
Doctor *doctorHead = NULL;
Appointment *appointmentHead = NULL;

WaitingNode *waitingFront = NULL;
WaitingNode *waitingRear = NULL;

PriorityNode *priorityHead = NULL;


/* =========================
   PATIENT MENU
   ========================= */

void patientManagementMenu(void)
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("========================================\n");
        printf("          PATIENT MANAGEMENT\n");
        printf("========================================\n");

        printf("1. Register Patient\n");
        printf("2. View Patients\n");
        printf("3. Search Patient\n");
        printf("0. Back\n");

        printf("========================================\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                registerPatient();
                break;

            case 2:
                viewPatients();
                break;

            case 3:
                searchPatient();
                break;

            case 0:
                return;

            default:
                printf("\nInvalid choice.\n");
        }
    }
}


/* =========================
   DOCTOR MENU
   ========================= */

void doctorManagementMenu(void)
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("========================================\n");
        printf("          DOCTOR MANAGEMENT\n");
        printf("========================================\n");

        printf("1. Add Doctor\n");
        printf("2. View Doctors\n");
        printf("0. Back\n");

        printf("========================================\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addDoctor();
                break;

            case 2:
                viewDoctors();
                break;

            case 0:
                return;

            default:
                printf("\nInvalid choice.\n");
        }
    }
}


/* =========================
   WAITING QUEUE MENU
   ========================= */

void waitingQueueMenu(void)
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("========================================\n");
        printf("            WAITING QUEUE\n");
        printf("========================================\n");

        printf("1. View Waiting Queue\n");
        printf("2. Call Next Patient\n");
        printf("0. Back\n");

        printf("========================================\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                viewWaitingQueue();
                break;

            case 2:
                callNextPatient();

                /*
                   Status may change to
                   IN_CONSULTATION.
                */
                saveAppointments();

                break;

            case 0:
                return;

            default:
                printf("\nInvalid choice.\n");
        }
    }
}


/* =========================
   PRIORITY QUEUE MENU
   ========================= */

void priorityQueueMenu(void)
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("========================================\n");
        printf("            PRIORITY QUEUE\n");
        printf("========================================\n");

        printf("1. Add Priority Patient\n");
        printf("2. View Priority Queue\n");
        printf("3. Process Priority Patient\n");
        printf("0. Back\n");

        printf("========================================\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addPriorityPatient();
                break;

            case 2:
                viewPriorityQueue();
                break;

            case 3:
                processPriorityPatient();
                break;

            case 0:
                return;

            default:
                printf("\nInvalid choice.\n");
        }
    }
}


/* =========================
   APPOINTMENT ACTION MENU
   ========================= */

void appointmentActionMenu(void)
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("========================================\n");
        printf("       APPOINTMENT MANAGEMENT\n");
        printf("========================================\n");

        printf("1. Complete Consultation\n");
        printf("2. Cancel Appointment\n");
        printf("0. Back\n");

        printf("========================================\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                completeConsultation();
                break;

            case 2:
                cancelAppointment();
                break;

            case 0:
                return;

            default:
                printf("\nInvalid choice.\n");
        }
    }
}


/* =========================
   MAIN MENU
   ========================= */

void displayMainMenu(void)
{
    printf("\n");
    printf("==================================================\n");
    printf("     SMART HOSPITAL APPOINTMENT MANAGEMENT\n");
    printf("==================================================\n");

    printf("1. Patient Management\n");
    printf("2. Doctor Management\n");
    printf("3. Book Appointment\n");
    printf("4. View Appointments\n");
    printf("5. Smart Appointment Finder\n");
    printf("6. Patient Check-In\n");
    printf("7. Manage Waiting Queue\n");
    printf("8. Manage Priority Queue\n");
    printf("9. Complete / Cancel Appointment\n");
    printf("0. Exit\n");

    printf("==================================================\n");
}


/* =========================
   MAIN
   ========================= */

int main(void)
{
    int choice;

    /*
       Reconstruct the linked lists from
       persistent storage.
    */

    loadPatients();
    loadDoctors();
    loadAppointments();

    printf("\nHospital records loaded successfully.\n");

    while (1)
    {
        displayMainMenu();

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n');

            printf("\nInvalid input. Enter a number.\n");

            continue;
        }

        switch (choice)
        {
            case 1:
                patientManagementMenu();
                break;

            case 2:
                doctorManagementMenu();
                break;

            case 3:
                bookAppointment();
                break;

            case 4:
                viewAppointments();
                break;

            case 5:
                smartAppointmentFinder();
                break;

            case 6:
                patientCheckIn();
                break;

            case 7:
                waitingQueueMenu();
                break;

            case 8:
                priorityQueueMenu();
                break;

            case 9:
                appointmentActionMenu();
                break;

            case 0:

                /*
                   Final save before exit.
                */

                savePatients();
                saveDoctors();
                saveAppointments();

                printf("\nRecords saved successfully.\n");
                printf("Hospital Appointment System Closed.\n");

                return 0;

            default:
                printf("\nInvalid choice.\n");
        }
    }
}