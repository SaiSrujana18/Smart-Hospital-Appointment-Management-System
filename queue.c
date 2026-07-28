#include "hospital.h"


void checkInPatient()
{
    int id;


    printf(
        "\nAppointment ID: "
    );

    scanf("%d", &id);


    Appointment *a =
        getAppointment(id);


    if (a == NULL)
    {
        printf(
            "Appointment not found.\n"
        );

        return;
    }


    if (a->status != BOOKED)
    {
        printf(
            "Appointment cannot be checked in.\n"
        );

        return;
    }


    a->status =
        WAITING;


    getCurrentTime(
        a->checkInTime
    );


    printf(
        "\nPatient checked in at %s.\n",
        a->checkInTime
    );


    printf(
        "Added to FIFO waiting queue.\n"
    );
}


void viewWaitingQueue()
{
    int doctorId;


    viewDoctors();


    printf(
        "\nDoctor ID: "
    );

    scanf("%d", &doctorId);


    printf(
        "\n========== LIVE WAITING QUEUE ==========\n"
    );


    int position = 1;


    /*
       Appointments enter WAITING state
       in check-in order.

       Therefore scanning the appointment
       array represents FIFO ordering for
       this case-study implementation.
    */


    for (int i = 0;
         i < appointmentCount;
         i++)
    {

        Appointment *a =
            &appointments[i];


        if (
            a->doctorId == doctorId &&
            a->status == WAITING
        )
        {

            Patient *p =
                getPatient(
                    a->patientId
                );


            printf(
                "%d. %s | Appointment %d | Scheduled %s | Check-in %s\n",
                position,
                p->name,
                a->id,
                a->scheduledTime,
                a->checkInTime
            );


            position++;
        }
    }


    if (position == 1)
    {
        printf(
            "Queue empty.\n"
        );
    }
}


void callNextPatient()
{
    int doctorId;


    viewDoctors();


    printf(
        "\nDoctor ID: "
    );

    scanf("%d", &doctorId);


    /*
       Check whether doctor is already
       consulting another patient.
    */

    for (int i = 0;
         i < appointmentCount;
         i++)
    {

        if (
            appointments[i].doctorId ==
                doctorId &&

            appointments[i].status ==
                CONSULTING
        )
        {

            printf(
                "\nDoctor is already consulting a patient.\n"
            );

            return;
        }
    }


    /*
       FIFO:
       first WAITING appointment found.
    */

    for (int i = 0;
         i < appointmentCount;
         i++)
    {

        Appointment *a =
            &appointments[i];


        if (
            a->doctorId == doctorId &&
            a->status == WAITING
        )
        {

            a->status =
                CONSULTING;


            getCurrentTime(
                a->actualStart
            );


            Patient *p =
                getPatient(
                    a->patientId
                );


            printf(
                "\nCalling next patient:\n"
            );


            printf(
                "%s\n",
                p->name
            );


            printf(
                "Consultation started at %s.\n",
                a->actualStart
            );


            return;
        }
    }


    printf(
        "\nNo patient waiting.\n"
    );
}


void completeConsultation()
{
    int appointmentId;


    printf(
        "\nAppointment ID: "
    );

    scanf(
        "%d",
        &appointmentId
    );


    Appointment *a =
        getAppointment(
            appointmentId
        );


    if (
        a == NULL ||
        a->status != CONSULTING
    )
    {

        printf(
            "Active consultation not found.\n"
        );

        return;
    }


    getCurrentTime(
        a->actualEnd
    );


    a->status =
        COMPLETED;


    printf(
        "\nConsultation completed at %s.\n",
        a->actualEnd
    );


    /*
       Check Dynamic Gap Recovery.
    */


    if (
        isRecoverableSlot(a)
    )
    {

        printf(
            "\n*** DYNAMIC SLOT RECOVERY ***\n"
        );


        printf(
            "%s appointment completed before its scheduled time.\n",
            a->scheduledTime
        );


        printf(
            "Next slot is empty.\n"
        );


        printf(
            "No patient is waiting.\n"
        );


        printf(
            "%s slot has been released for a new appointment.\n",
            a->scheduledTime
        );
    }
}


/* =================================================
   PRIORITY QUEUE
   ================================================= */


void addPriorityPatient()
{
    int appointmentId;


    printf(
        "\nAppointment ID: "
    );

    scanf(
        "%d",
        &appointmentId
    );


    Appointment *a =
        getAppointment(
            appointmentId
        );


    if (a == NULL)
    {
        printf(
            "Appointment not found.\n"
        );

        return;
    }


    printf(
        "\nPriority Level\n"
    );

    printf(
        "1. Emergency\n"
    );

    printf(
        "2. Urgent\n"
    );

    printf(
        "3. Senior Citizen\n"
    );

    printf(
        "4. Normal\n"
    );


    int priority;


    printf(
        "Choose: "
    );

    scanf(
        "%d",
        &priority
    );


    priorityQueue[
        priorityCount
    ].appointmentId =
        appointmentId;


    priorityQueue[
        priorityCount
    ].priority =
        priority;


    priorityQueue[
        priorityCount
    ].arrivalOrder =
        arrivalCounter++;


    priorityCount++;


    /*
       Bubble Sort

       Lower number =
       higher priority.

       Same priority =
       FIFO arrival order.
    */


    for (
        int i = 0;
        i < priorityCount - 1;
        i++
    )
    {

        for (
            int j = 0;
            j < priorityCount - i - 1;
            j++
        )
        {

            int swap = 0;


            if (
                priorityQueue[j].priority >
                priorityQueue[j + 1].priority
            )
            {
                swap = 1;
            }


            else if (
                priorityQueue[j].priority ==
                priorityQueue[j + 1].priority &&

                priorityQueue[j].arrivalOrder >
                priorityQueue[j + 1].arrivalOrder
            )
            {
                swap = 1;
            }


            if (swap)
            {
                PriorityPatient temp =
                    priorityQueue[j];


                priorityQueue[j] =
                    priorityQueue[j + 1];


                priorityQueue[j + 1] =
                    temp;
            }
        }
    }


    printf(
        "\nPatient added to priority queue.\n"
    );
}


void viewPriorityQueue()
{
    printf(
        "\n========== PRIORITY QUEUE ==========\n"
    );


    if (
        priorityCount == 0
    )
    {
        printf(
            "Priority queue empty.\n"
        );

        return;
    }


    for (
        int i = 0;
        i < priorityCount;
        i++
    )
    {

        Appointment *a =
            getAppointment(
                priorityQueue[i].appointmentId
            );


        Patient *p =
            getPatient(
                a->patientId
            );


        char priorityName[20];


        switch (
            priorityQueue[i].priority
        )
        {

            case 1:

                strcpy(
                    priorityName,
                    "Emergency"
                );

                break;


            case 2:

                strcpy(
                    priorityName,
                    "Urgent"
                );

                break;


            case 3:

                strcpy(
                    priorityName,
                    "Senior"
                );

                break;


            default:

                strcpy(
                    priorityName,
                    "Normal"
                );
        }


        printf(
            "%d. %-25s %s\n",
            i + 1,
            p->name,
            priorityName
        );
    }
}


void processPriorityPatient()
{
    if (
        priorityCount == 0
    )
    {
        printf(
            "\nPriority queue empty.\n"
        );

        return;
    }


    PriorityPatient next =
        priorityQueue[0];


    Appointment *a =
        getAppointment(
            next.appointmentId
        );


    Patient *p =
        getPatient(
            a->patientId
        );


    printf(
        "\nHighest priority patient:\n"
    );


    printf(
        "%s\n",
        p->name
    );


    a->status =
        WAITING;


    getCurrentTime(
        a->checkInTime
    );


    /*
       Remove front element
       by shifting queue.
    */


    for (
        int i = 1;
        i < priorityCount;
        i++
    )
    {
        priorityQueue[i - 1] =
            priorityQueue[i];
    }


    priorityCount--;


    printf(
        "Patient moved to consultation waiting queue.\n"
    );
}
