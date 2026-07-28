#include "hospital.h"


Appointment *getAppointment(int id)
{
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].id == id)
            return &appointments[i];
    }

    return NULL;
}


int timeToMinutes(char time[])
{
    int hour;
    int minute;

    sscanf(time, "%d:%d", &hour, &minute);

    return hour * 60 + minute;
}


void getCurrentTime(char result[])
{
    time_t current = time(NULL);

    struct tm *local = localtime(&current);

    sprintf(
        result,
        "%02d:%02d",
        local->tm_hour,
        local->tm_min
    );
}


/*
   DYNAMIC GAP RECOVERY

   Example:

   Appointment scheduled = 16:30
   Actual completion      = 16:20

   The 16:30 slot may be reused only when:

   1. Consultation completed before 16:30
   2. Next slot (17:00) is empty
   3. No patient is already WAITING for this doctor
*/

int isRecoverableSlot(Appointment *appointment)
{
    if (appointment->status != COMPLETED)
        return 0;

    if (strlen(appointment->actualEnd) == 0)
        return 0;


    int scheduled =
        timeToMinutes(appointment->scheduledTime);

    int completed =
        timeToMinutes(appointment->actualEnd);


    if (completed >= scheduled)
        return 0;


    Doctor *doctor =
        getDoctor(appointment->doctorId);

    if (doctor == NULL)
        return 0;


    int nextSlot =
        scheduled + doctor->slotDuration;


    /*
       CONDITION 1:
       Check whether the next slot already
       contains an active appointment.
    */

    for (int i = 0; i < appointmentCount; i++)
    {
        Appointment *a = &appointments[i];

        if (a->id == appointment->id)
            continue;

        if (a->doctorId != appointment->doctorId)
            continue;

        if (strcmp(a->date, appointment->date) != 0)
            continue;


        int appointmentTime =
            timeToMinutes(a->scheduledTime);


        if (appointmentTime == nextSlot &&
            a->status != CANCELLED)
        {
            return 0;
        }
    }


    /*
       CONDITION 2:
       Existing waiting patients get priority
       over creating a new appointment.
    */

    for (int i = 0; i < appointmentCount; i++)
    {
        Appointment *a = &appointments[i];

        if (a->doctorId ==
                appointment->doctorId &&

            strcmp(
                a->date,
                appointment->date
            ) == 0 &&

            a->status == WAITING)
        {
            return 0;
        }
    }


    return 1;
}


int isSlotAvailable(
    int doctorId,
    char date[],
    char time[]
)
{
    for (int i = 0; i < appointmentCount; i++)
    {
        Appointment *a =
            &appointments[i];


        if (a->doctorId == doctorId &&

            strcmp(a->date, date) == 0 &&

            strcmp(
                a->scheduledTime,
                time
            ) == 0)
        {

            if (a->status == CANCELLED)
                continue;


            /*
               Appointment completed early.

               Check if original slot can
               be recovered.
            */

            if (a->status == COMPLETED &&
                isRecoverableSlot(a))
            {
                continue;
            }


            return 0;
        }
    }


    return 1;
}


void bookAppointment()
{
    if (appointmentCount >= MAX_APPOINTMENTS)
    {
        printf("\nAppointment storage full.\n");
        return;
    }


    int patientId;
    int doctorId;

    char date[11];
    char time[6];


    printf("\n=============== BOOK APPOINTMENT ===============\n");


    viewPatients();

    printf("\nPatient ID: ");
    scanf("%d", &patientId);


    if (getPatient(patientId) == NULL)
    {
        printf("Invalid patient.\n");
        return;
    }


    viewDoctors();

    printf("\nDoctor ID: ");
    scanf("%d", &doctorId);


    Doctor *doctor =
        getDoctor(doctorId);


    if (doctor == NULL)
    {
        printf("Invalid doctor.\n");
        return;
    }


    printf("Date (YYYY-MM-DD): ");
    scanf("%10s", date);


    printf("\nAvailable Slots\n");
    printf("--------------------------------\n");


    int start =
        timeToMinutes(doctor->startTime);

    int end =
        timeToMinutes(doctor->endTime);


    for (
        int t = start;
        t + doctor->slotDuration <= end;
        t += doctor->slotDuration
    )
    {
        char slot[6];

        sprintf(
            slot,
            "%02d:%02d",
            t / 60,
            t % 60
        );


        if (
            isSlotAvailable(
                doctorId,
                date,
                slot
            )
        )
        {
            printf("%s\n", slot);
        }
    }


    printf("\nChoose Time: ");
    scanf("%5s", time);


    if (
        !isSlotAvailable(
            doctorId,
            date,
            time
        )
    )
    {
        printf("\nSlot unavailable.\n");
        return;
    }


    Appointment *a =
        &appointments[appointmentCount];


    a->id =
        10001 + appointmentCount;

    a->patientId =
        patientId;

    a->doctorId =
        doctorId;


    strcpy(
        a->date,
        date
    );

    strcpy(
        a->scheduledTime,
        time
    );


    strcpy(
        a->checkInTime,
        ""
    );

    strcpy(
        a->actualStart,
        ""
    );

    strcpy(
        a->actualEnd,
        ""
    );


    a->status =
        BOOKED;


    appointmentCount++;


    printf("\nAppointment booked successfully.\n");

    printf(
        "Appointment ID: %d\n",
        a->id
    );
}


void viewAppointments()
{
    printf("\n================ APPOINTMENTS ================\n");


    printf(
        "%-7s %-20s %-20s %-11s %-7s %-15s\n",
        "ID",
        "Patient",
        "Doctor",
        "Date",
        "Time",
        "Status"
    );


    printf(
        "--------------------------------------------------------------------------------\n"
    );


    for (int i = 0;
         i < appointmentCount;
         i++)
    {

        Appointment *a =
            &appointments[i];


        Patient *patient =
            getPatient(a->patientId);


        Doctor *doctor =
            getDoctor(a->doctorId);


        char status[20];


        switch (a->status)
        {
            case BOOKED:
                strcpy(status, "Booked");
                break;

            case WAITING:
                strcpy(status, "Waiting");
                break;

            case CONSULTING:
                strcpy(status, "Consulting");
                break;

            case COMPLETED:
                strcpy(status, "Completed");
                break;

            case CANCELLED:
                strcpy(status, "Cancelled");
                break;
        }


        printf(
            "%-7d %-20s %-20s %-11s %-7s %-15s\n",
            a->id,
            patient->name,
            doctor->name,
            a->date,
            a->scheduledTime,
            status
        );


        if (a->status == COMPLETED)
        {
            printf(
                "        Actual consultation: %s - %s\n",
                a->actualStart,
                a->actualEnd
            );


            if (isRecoverableSlot(a))
            {
                printf(
                    "        >> Original %s slot RECOVERED\n",
                    a->scheduledTime
                );
            }
        }
    }
}


void cancelAppointment()
{
    int id;


    printf(
        "\nAppointment ID to cancel: "
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


    a->status =
        CANCELLED;


    printf(
        "\nAppointment cancelled.\n"
    );

    printf(
        "%s slot is now available again.\n",
        a->scheduledTime
    );
}
