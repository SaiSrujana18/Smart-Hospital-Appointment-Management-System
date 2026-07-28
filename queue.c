#include "hospital.h"


static unsigned long nextPrioritySequence = 1;


/* ==========================================
   PRIORITY NAME
   ========================================== */

const char *priorityName(int priority)
{
    switch (priority)
    {
        case 1:
            return "Emergency";

        case 2:
            return "Urgent";

        case 3:
            return "Senior";

        case 4:
            return "Normal";

        default:
            return "Unknown";
    }
}


/* ==========================================
   FIFO ENQUEUE

   Complexity: O(1)
   ========================================== */

void enqueueWaiting(int appointmentId)
{
    WaitingNode *newNode;


    newNode =
        (WaitingNode *)malloc(
            sizeof(WaitingNode)
        );


    if (newNode == NULL)
    {
        printf(
            "\nUnable to add patient to queue.\n"
        );

        return;
    }


    newNode->appointmentId =
        appointmentId;


    newNode->next =
        NULL;


    if (waitingRear == NULL)
    {
        waitingFront =
            newNode;

        waitingRear =
            newNode;
    }

    else
    {
        waitingRear->next =
            newNode;

        waitingRear =
            newNode;
    }
}


/* ==========================================
   FIFO DEQUEUE

   Complexity: O(1)
   ========================================== */

int dequeueWaiting(void)
{
    WaitingNode *temp;

    int appointmentId;


    if (waitingFront == NULL)
    {
        return -1;
    }


    temp =
        waitingFront;


    appointmentId =
        temp->appointmentId;


    waitingFront =
        waitingFront->next;


    if (waitingFront == NULL)
    {
        waitingRear =
            NULL;
    }


    free(temp);


    return appointmentId;
}


/* ==========================================
   VIEW WAITING QUEUE
   ========================================== */

void viewWaitingQueue(void)
{
    WaitingNode *current =
        waitingFront;

    int position = 1;


    printf("\n");
    printf("==============================================================\n");
    printf("                     LIVE WAITING QUEUE\n");
    printf("==============================================================\n");


    if (current == NULL)
    {
        printf(
            "Waiting queue is empty.\n"
        );

        return;
    }


    printf(
        "%-10s %-12s %-25s\n",
        "Position",
        "Appt ID",
        "Patient"
    );


    printf(
        "--------------------------------------------------------------\n"
    );


    while (current != NULL)
    {
        Appointment *appointment =
            findAppointmentById(
                current->appointmentId
            );


        if (appointment != NULL)
        {
            Patient *patient =
                findPatientById(
                    appointment->patientId
                );


            printf(
                "%-10d %-12d %-25s\n",
                position,
                appointment->id,
                patient != NULL
                    ? patient->name
                    : "Unknown"
            );
        }


        position++;


        current =
            current->next;
    }
}


/* ==========================================
   CALL NEXT PATIENT
   ========================================== */

void callNextPatient(void)
{
    int appointmentId;

    Appointment *appointment;

    Patient *patient;

    Doctor *doctor;


    appointmentId =
        dequeueWaiting();


    if (appointmentId == -1)
    {
        printf(
            "\nWaiting queue is empty.\n"
        );

        return;
    }


    appointment =
        findAppointmentById(
            appointmentId
        );


    if (appointment == NULL)
    {
        printf(
            "\nAppointment record not found.\n"
        );

        return;
    }


    strcpy(
        appointment->status,
        "IN_CONSULTATION"
    );


    patient =
        findPatientById(
            appointment->patientId
        );


    doctor =
        findDoctorById(
            appointment->doctorId
        );


    printf("\n");
    printf("========================================\n");
    printf("             NEXT PATIENT\n");
    printf("========================================\n");


    printf(
        "Patient : %s\n",
        patient != NULL
            ? patient->name
            : "Unknown"
    );


    printf(
        "Doctor  : %s\n",
        doctor != NULL
            ? doctor->name
            : "Unknown"
    );


    printf(
        "Status  : IN CONSULTATION\n"
    );
}


/* ==========================================
   ADD PRIORITY PATIENT

   Priority queue remains sorted.

   Lower priority number = more important.

   For equal priorities, sequence preserves
   FIFO ordering.
   ========================================== */

void addPriorityPatient(void)
{
    PriorityNode *newNode;

    PriorityNode *current;

    int patientId;

    int doctorId;


    if (patientHead == NULL)
    {
        printf(
            "\nRegister a patient first.\n"
        );

        return;
    }


    if (doctorHead == NULL)
    {
        printf(
            "\nAdd a doctor first.\n"
        );

        return;
    }


    printf("\nPatient ID: ");

    scanf(
        "%d",
        &patientId
    );


    if (
        findPatientById(patientId)
        == NULL
    )
    {
        printf(
            "\nPatient not found.\n"
        );

        return;
    }


    printf("Doctor ID: ");

    scanf(
        "%d",
        &doctorId
    );


    if (
        findDoctorById(doctorId)
        == NULL
    )
    {
        printf(
            "\nDoctor not found.\n"
        );

        return;
    }


    newNode =
        (PriorityNode *)malloc(
            sizeof(PriorityNode)
        );


    if (newNode == NULL)
    {
        printf(
            "\nMemory allocation failed.\n"
        );

        return;
    }


    newNode->patientId =
        patientId;


    newNode->doctorId =
        doctorId;


    printf(
        "Date (YYYY-MM-DD): "
    );

    scanf(
        "%10s",
        newNode->date
    );


    printf("\n");
    printf("1. Emergency\n");
    printf("2. Urgent\n");
    printf("3. Senior Citizen\n");
    printf("4. Normal\n");


    printf("Priority: ");

    scanf(
        "%d",
        &newNode->priority
    );


    if (
        newNode->priority < 1 ||
        newNode->priority > 4
    )
    {
        printf(
            "\nInvalid priority.\n"
        );

        free(newNode);

        return;
    }


    newNode->sequence =
        nextPrioritySequence++;


    newNode->next =
        NULL;


    /*
        Insert at head if highest priority.
    */

    if (
        priorityHead == NULL ||

        newNode->priority <
        priorityHead->priority
    )
    {
        newNode->next =
            priorityHead;

        priorityHead =
            newNode;
    }

    else
    {
        current =
            priorityHead;


        /*
            Move past nodes with higher priority
            and nodes with equal priority.

            This preserves FIFO for equal priority.
        */

        while (
            current->next != NULL &&

            current->next->priority <=
            newNode->priority
        )
        {
            current =
                current->next;
        }


        newNode->next =
            current->next;


        current->next =
            newNode;
    }


    printf(
        "\nPatient added to priority queue.\n"
    );
}


/* ==========================================
   VIEW PRIORITY QUEUE
   ========================================== */

void viewPriorityQueue(void)
{
    PriorityNode *current =
        priorityHead;

    int position = 1;


    printf("\n");
    printf("==========================================================================\n");
    printf("                            PRIORITY QUEUE\n");
    printf("==========================================================================\n");


    if (current == NULL)
    {
        printf(
            "Priority queue is empty.\n"
        );

        return;
    }


    printf(
        "%-10s %-25s %-20s %-15s\n",
        "Position",
        "Patient",
        "Priority",
        "Date"
    );


    printf(
        "--------------------------------------------------------------------------\n"
    );


    while (current != NULL)
    {
        Patient *patient =
            findPatientById(
                current->patientId
            );


        printf(
            "%-10d %-25s %-20s %-15s\n",
            position,
            patient != NULL
                ? patient->name
                : "Unknown",
            priorityName(
                current->priority
            ),
            current->date
        );


        position++;


        current =
            current->next;
    }
}


/* ==========================================
   PROCESS PRIORITY PATIENT
   ========================================== */

void processPriorityPatient(void)
{
    PriorityNode *node;

    Patient *patient;

    Doctor *doctor;


    if (priorityHead == NULL)
    {
        printf(
            "\nPriority queue is empty.\n"
        );

        return;
    }


    node =
        priorityHead;


    priorityHead =
        priorityHead->next;


    patient =
        findPatientById(
            node->patientId
        );


    doctor =
        findDoctorById(
            node->doctorId
        );


    printf("\n");
    printf("========================================\n");
    printf("       PROCESSING PRIORITY PATIENT\n");
    printf("========================================\n");


    printf(
        "Patient  : %s\n",
        patient != NULL
            ? patient->name
            : "Unknown"
    );


    printf(
        "Doctor   : %s\n",
        doctor != NULL
            ? doctor->name
            : "Unknown"
    );


    printf(
        "Priority : %s\n",
        priorityName(
            node->priority
        )
    );


    printf(
        "\nPatient sent for immediate consultation.\n"
    );


    free(node);
}