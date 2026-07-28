#include "hospital.h"


Patient patients[MAX_PATIENTS];
Doctor doctors[MAX_DOCTORS];
Appointment appointments[MAX_APPOINTMENTS];

PriorityPatient priorityQueue[MAX_QUEUE];

int patientCount = 0;
int doctorCount = 0;
int appointmentCount = 0;

int priorityCount = 0;
int arrivalCounter = 0;


void loadDemoDoctors()
{
    doctors[0].id = 501;
    strcpy(doctors[0].name, "Dr. Arjun Mehta");
    strcpy(doctors[0].specialization, "Cardiology");
    strcpy(doctors[0].startTime, "09:00");
    strcpy(doctors[0].endTime, "17:00");
    doctors[0].slotDuration = 30;


    doctors[1].id = 502;
    strcpy(doctors[1].name, "Dr. Priya Sharma");
    strcpy(doctors[1].specialization, "Cardiology");
    strcpy(doctors[1].startTime, "10:00");
    strcpy(doctors[1].endTime, "18:00");
    doctors[1].slotDuration = 30;


    doctors[2].id = 503;
    strcpy(doctors[2].name, "Dr. Neha Rao");
    strcpy(doctors[2].specialization, "Dermatology");
    strcpy(doctors[2].startTime, "09:00");
    strcpy(doctors[2].endTime, "16:00");
    doctors[2].slotDuration = 30;


    doctors[3].id = 504;
    strcpy(doctors[3].name, "Dr. Vikram Singh");
    strcpy(doctors[3].specialization, "Orthopaedics");
    strcpy(doctors[3].startTime, "08:00");
    strcpy(doctors[3].endTime, "16:00");
    doctors[3].slotDuration = 30;

    doctorCount = 4;
}


void dashboard()
{
    int booked = 0;
    int waiting = 0;
    int consulting = 0;
    int completed = 0;

    for (int i = 0; i < appointmentCount; i++)
    {
        switch (appointments[i].status)
        {
            case BOOKED:
                booked++;
                break;

            case WAITING:
                waiting++;
                break;

            case CONSULTING:
                consulting++;
                break;

            case COMPLETED:
                completed++;
                break;

            default:
                break;
        }
    }

    printf("\n==============================================\n");
    printf("         SMART HOSPITAL DASHBOARD\n");
    printf("==============================================\n");

    printf("Patients Registered : %d\n", patientCount);
    printf("Doctors Available   : %d\n", doctorCount);
    printf("Booked Appointments : %d\n", booked);
    printf("Waiting Patients    : %d\n", waiting);
    printf("In Consultation     : %d\n", consulting);
    printf("Completed           : %d\n", completed);
    printf("Priority Cases      : %d\n", priorityCount);

    printf("==============================================\n");
}


int main()
{
    int choice;

    loadDemoDoctors();

    while (1)
    {
        printf("\n\n");
        printf("====================================================\n");
        printf("   SMART HOSPITAL APPOINTMENT MANAGEMENT SYSTEM\n");
        printf("====================================================\n");

        printf("1. Register Patient\n");
        printf("2. View Patients\n");
        printf("3. Search Patient\n");

        printf("4. Add Doctor\n");
        printf("5. View Doctors\n");

        printf("6. Book Appointment\n");
        printf("7. View Appointments\n");

        printf("8. Smart Appointment Finder\n");

        printf("9. Patient Check-In\n");
        printf("10. View Live Waiting Queue\n");
        printf("11. Call Next Patient\n");
        printf("12. Complete Consultation\n");

        printf("13. Add Priority Patient\n");
        printf("14. View Priority Queue\n");
        printf("15. Process Priority Patient\n");

        printf("16. Cancel Appointment\n");

        printf("17. Dashboard\n");

        printf("0. Exit\n");

        printf("\nEnter choice: ");
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

            case 4:
                addDoctor();
                break;

            case 5:
                viewDoctors();
                break;

            case 6:
                bookAppointment();
                break;

            case 7:
                viewAppointments();
                break;

            case 8:
                smartAppointmentFinder();
                break;

            case 9:
                checkInPatient();
                break;

            case 10:
                viewWaitingQueue();
                break;

            case 11:
                callNextPatient();
                break;

            case 12:
                completeConsultation();
                break;

            case 13:
                addPriorityPatient();
                break;

            case 14:
                viewPriorityQueue();
                break;

            case 15:
                processPriorityPatient();
                break;

            case 16:
                cancelAppointment();
                break;

            case 17:
                dashboard();
                break;

            case 0:

                printf("\nThank you for using SmartCare.\n");
                return 0;

            default:
                printf("\nInvalid choice.\n");
        }
    }
}
