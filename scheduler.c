#include "hospital.h"


/* ==========================================
   TIME -> MINUTES

   Example:

   16:30

   = 16 * 60 + 30
   = 990 minutes
   ========================================== */

int timeToMinutes(const char *time)
{
    int hour;

    int minute;


    if (
        sscanf(
            time,
            "%d:%d",
            &hour,
            &minute
        ) != 2
    )
    {
        return -1;
    }


    return (
        hour * 60 +
        minute
    );
}


/* ==========================================
   MINUTES -> TIME
   ========================================== */

void minutesToTime(
    int minutes,
    char *buffer
)
{
    int hour =
        minutes / 60;


    int minute =
        minutes % 60;


    sprintf(
        buffer,
        "%02d:%02d",
        hour,
        minute
    );
}


/* ==========================================
   SMART APPOINTMENT FINDER

   Searches doctors according to
   specialization.

   Then searches 30-minute slots and finds
   the earliest available appointment.

   DSA concepts:

   Linked-list traversal
   Searching
   Scheduling
   ========================================== */

void smartAppointmentFinder(void)
{
    int patientId;

    char specialization[SPEC_LEN];

    char date[DATE_LEN];

    Patient *patient;

    Doctor *doctor;

    Doctor *bestDoctor = NULL;

    int bestTime = -1;


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
            "\nNo doctors available.\n"
        );

        return;
    }


    printf("\n");
    printf("========================================\n");
    printf("       SMART APPOINTMENT FINDER\n");
    printf("========================================\n");


    printf("Patient ID: ");

    scanf(
        "%d",
        &patientId
    );


    patient =
        findPatientById(
            patientId
        );


    if (patient == NULL)
    {
        printf(
            "\nPatient not found.\n"
        );

        return;
    }


    printf("Required Specialization: ");

    scanf(
        " %59[^\n]",
        specialization
    );


    printf("Date (YYYY-MM-DD): ");

    scanf(
        "%10s",
        date
    );


    doctor =
        doctorHead;


    /*
        Traverse all doctors.
    */

    while (doctor != NULL)
    {
        if (
            strcmp(
                doctor->specialization,
                specialization
            ) == 0
        )
        {
            int start =
                timeToMinutes(
                    doctor->startTime
                );


            int end =
                timeToMinutes(
                    doctor->endTime
                );


            int slot;


            /*
                Search every 30-minute slot.
            */

            for (
                slot = start;
                slot < end;
                slot += 30
            )
            {
                char time[TIME_LEN];


                minutesToTime(
                    slot,
                    time
                );


                if (
                    isSlotAvailable(
                        doctor->id,
                        date,
                        time
                    )
                )
                {
                    /*
                        Choose earliest slot
                        across all matching doctors.
                    */

                    if (
                        bestTime == -1 ||
                        slot < bestTime
                    )
                    {
                        bestTime =
                            slot;


                        bestDoctor =
                            doctor;
                    }


                    /*
                        This is the earliest free
                        slot for this doctor.
                    */

                    break;
                }
            }
        }


        doctor =
            doctor->next;
    }


    if (bestDoctor == NULL)
    {
        printf(
            "\nNo available appointment found.\n"
        );

        return;
    }


    {
        char bestTimeString[TIME_LEN];


        minutesToTime(
            bestTime,
            bestTimeString
        );


        printf("\n");
        printf("========================================\n");
        printf("          BEST APPOINTMENT\n");
        printf("========================================\n");


        printf(
            "Patient : %s\n",
            patient->name
        );


        printf(
            "Doctor  : %s\n",
            bestDoctor->name
        );


        printf(
            "Specialization : %s\n",
            bestDoctor->specialization
        );


        printf(
            "Date    : %s\n",
            date
        );


        printf(
            "Time    : %s\n",
            bestTimeString
        );


        printf(
            "\nThis is the earliest available slot.\n"
        );
    }
}


/* ==========================================
   EARLY COMPLETION OPTIMISATION

   Example:

   Appointment slot: 16:00
   Expected block:    16:00 - 16:30

   Consultation ends: 16:20

   Next slot:         16:30
   Following slot:    17:00


   We check:

   1. Is there someone already waiting for
      this doctor?

      If yes, we do NOT let a new patient
      bypass them.

   2. Is the next scheduled slot empty?

      If yes, the newly available capacity
      can be utilised.

   This demonstrates dynamic scheduling.
   ========================================== */

void handleEarlyCompletion(
    int doctorId,
    const char *date,
    const char *completedTime
)
{
    int completion;

    int nextSlot;

    int followingSlot;

    char nextTime[TIME_LEN];

    char followingTime[TIME_LEN];

    WaitingNode *waiting;


    completion =
        timeToMinutes(
            completedTime
        );


    if (completion < 0)
    {
        return;
    }


    /*
        Round completion time upward to
        next 30-minute boundary.

        Example:

        16:20 -> 16:30
    */

    nextSlot =
        (
            (completion + 29)
            / 30
        ) * 30;


    followingSlot =
        nextSlot + 30;


    minutesToTime(
        nextSlot,
        nextTime
    );


    minutesToTime(
        followingSlot,
        followingTime
    );


    /*
        First check whether an eligible patient
        is already waiting for this doctor.

        Existing queue patients must not be
        bypassed.
    */

    waiting =
        waitingFront;


    while (waiting != NULL)
    {
        Appointment *appointment =
            findAppointmentById(
                waiting->appointmentId
            );


        if (
            appointment != NULL &&
            appointment->doctorId == doctorId &&
            strcmp(
                appointment->date,
                date
            ) == 0
        )
        {
            Patient *patient =
                findPatientById(
                    appointment->patientId
                );


            printf("\n");
            printf("SMART SCHEDULER:\n");


            printf(
                "Doctor became available at %s.\n",
                completedTime
            );


            printf(
                "Waiting patient %s already requires this doctor.\n",
                patient != NULL
                    ? patient->name
                    : "Unknown"
            );


            printf(
                "Existing waiting patient receives priority.\n"
            );


            return;
        }


        waiting =
            waiting->next;
    }


    /*
        Your requested rule:

        Only consider early slot utilisation
        when the following normal slot is empty.

        Example:

        available early at 16:20

        next boundary = 16:30
        following slot = 17:00

        If 17:00 is already booked, we don't
        advertise this as extra capacity for
        a new patient.
    */

    if (
        !isSlotAvailable(
            doctorId,
            date,
            followingTime
        )
    )
    {
        printf("\n");
        printf("SMART SCHEDULER:\n");


        printf(
            "Consultation completed at %s.\n",
            completedTime
        );


        printf(
            "Upcoming schedule is occupied.\n"
        );


        printf(
            "No extra walk-in slot opened.\n"
        );


        return;
    }


    /*
        Also ensure next slot itself isn't
        occupied.
    */

    if (
        !isSlotAvailable(
            doctorId,
            date,
            nextTime
        )
    )
    {
        printf("\n");
        printf("SMART SCHEDULER:\n");


        printf(
            "%s slot is already booked.\n",
            nextTime
        );


        return;
    }


    printf("\n");
    printf("========================================\n");
    printf("        SMART SLOT OPTIMISATION\n");
    printf("========================================\n");


    printf(
        "Consultation finished early at %s.\n",
        completedTime
    );


    printf(
        "No eligible patient is waiting.\n"
    );


    printf(
        "Upcoming %s slot is free.\n",
        followingTime
    );


    printf(
        "%s can now be offered to a walk-in/new patient.\n",
        nextTime
    );


    printf(
        "This avoids unnecessary waiting until %s.\n",
        followingTime
    );
}