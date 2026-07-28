#include "hospital.h"


typedef struct
{
    int doctorId;

    int slotMinutes;

    char slot[6];

    int workload;

    int waiting;

    int score;

} Recommendation;


void smartAppointmentFinder()
{
    int patientId;

    char specialization[40];

    char date[11];


    printf(
        "\n=========== SMART APPOINTMENT FINDER ===========\n"
    );


    viewPatients();


    printf(
        "\nPatient ID: "
    );

    scanf(
        "%d",
        &patientId
    );


    if (
        getPatient(patientId) == NULL
    )
    {
        printf(
            "Invalid patient.\n"
        );

        return;
    }


    printf(
        "Required Specialization: "
    );

    scanf(
        " %[^\n]",
        specialization
    );


    printf(
        "Date (YYYY-MM-DD): "
    );

    scanf(
        "%10s",
        date
    );


    Recommendation results[MAX_DOCTORS];

    int resultCount = 0;


    /*
       Search doctors matching
       required specialization.
    */


    for (
        int i = 0;
        i < doctorCount;
        i++
    )
    {

        Doctor *doctor =
            &doctors[i];


        if (
            strcmp(
                doctor->specialization,
                specialization
            ) != 0
        )
        {
            continue;
        }


        int workload = 0;

        int waiting = 0;


        /*
           Calculate workload.
        */


        for (
            int j = 0;
            j < appointmentCount;
            j++
        )
        {

            Appointment *a =
                &appointments[j];


            if (
                a->doctorId ==
                    doctor->id &&

                strcmp(
                    a->date,
                    date
                ) == 0 &&

                a->status !=
                    CANCELLED
            )
            {

                workload++;


                if (
                    a->status ==
                    WAITING
                )
                {
                    waiting++;
                }
            }
        }


        int start =
            timeToMinutes(
                doctor->startTime
            );


        int end =
            timeToMinutes(
                doctor->endTime
            );


        /*
           Find earliest available slot.
        */


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
                    doctor->id,
                    date,
                    slot
                )
            )
            {

                Recommendation *r =
                    &results[
                        resultCount
                    ];


                r->doctorId =
                    doctor->id;


                r->slotMinutes =
                    t;


                strcpy(
                    r->slot,
                    slot
                );


                r->workload =
                    workload;


                r->waiting =
                    waiting;


                /*
                   Higher score is better.
                */


                r->score =
                    100
                    - workload * 3
                    - waiting * 10;


                resultCount++;


                break;
            }
        }
    }


    if (
        resultCount == 0
    )
    {
        printf(
            "\nNo suitable appointment found.\n"
        );

        return;
    }


    /*
       SORT RECOMMENDATIONS

       Priority:

       1. Earliest slot
       2. Highest score
    */


    for (
        int i = 0;
        i < resultCount - 1;
        i++
    )
    {

        for (
            int j = 0;
            j < resultCount - i - 1;
            j++
        )
        {

            int swap = 0;


            if (
                results[j].slotMinutes >
                results[j + 1].slotMinutes
            )
            {
                swap = 1;
            }


            else if (
                results[j].slotMinutes ==
                    results[j + 1].slotMinutes &&

                results[j].score <
                    results[j + 1].score
            )
            {
                swap = 1;
            }


            if (swap)
            {
                Recommendation temp =
                    results[j];


                results[j] =
                    results[j + 1];


                results[j + 1] =
                    temp;
            }
        }
    }


    printf(
        "\n============= RECOMMENDATIONS =============\n"
    );


    for (
        int i = 0;
        i < resultCount;
        i++
    )
    {

        Doctor *doctor =
            getDoctor(
                results[i].doctorId
            );


        printf(
            "\n%d. %s\n",
            i + 1,
            doctor->name
        );


        printf(
            "   Time     : %s\n",
            results[i].slot
        );


        printf(
            "   Workload : %d\n",
            results[i].workload
        );


        printf(
            "   Waiting  : %d\n",
            results[i].waiting
        );


        printf(
            "   Score    : %d\n",
            results[i].score
        );


        if (i == 0)
        {
            printf(
                "   *** BEST MATCH ***\n"
            );
        }
    }


    int choice;


    printf(
        "\nSelect recommendation (0 to cancel): "
    );


    scanf(
        "%d",
        &choice
    );


    if (
        choice <= 0 ||
        choice > resultCount
    )
    {
        return;
    }


    Recommendation selected =
        results[
            choice - 1
        ];


    Appointment *a =
        &appointments[
            appointmentCount
        ];


    a->id =
        10001 +
        appointmentCount;


    a->patientId =
        patientId;


    a->doctorId =
        selected.doctorId;


    strcpy(
        a->date,
        date
    );


    strcpy(
        a->scheduledTime,
        selected.slot
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


    printf(
        "\nSmart appointment booked successfully.\n"
    );


    printf(
        "Appointment ID: %d\n",
        a->id
    );
}
