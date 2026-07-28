#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 20
#define MAX_APPOINTMENTS 500
#define MAX_QUEUE 100

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[15];
    char phone[15];
} Patient;

typedef struct {
    int id;
    char name[50];
    char specialization[40];
    char startTime[6];
    char endTime[6];
    int slotDuration;
} Doctor;

typedef enum {
    BOOKED,
    WAITING,
    CONSULTING,
    COMPLETED,
    CANCELLED
} AppointmentStatus;

typedef struct {
    int id;
    int patientId;
    int doctorId;

    char date[11];
    char scheduledTime[6];

    char checkInTime[6];
    char actualStart[6];
    char actualEnd[6];

    AppointmentStatus status;
} Appointment;

typedef struct {
    int appointmentId;
    int priority;
    int arrivalOrder;
} PriorityPatient;


/* GLOBAL DATA */

extern Patient patients[MAX_PATIENTS];
extern Doctor doctors[MAX_DOCTORS];
extern Appointment appointments[MAX_APPOINTMENTS];

extern PriorityPatient priorityQueue[MAX_QUEUE];

extern int patientCount;
extern int doctorCount;
extern int appointmentCount;
extern int priorityCount;
extern int arrivalCounter;


/* PATIENT */

void registerPatient();
void viewPatients();
void searchPatient();


/* DOCTOR */

void addDoctor();
void viewDoctors();


/* APPOINTMENT */

void bookAppointment();
void viewAppointments();
void cancelAppointment();

int isSlotAvailable(
    int doctorId,
    char date[],
    char time[]
);

int isRecoverableSlot(
    Appointment *appointment
);


/* FIFO QUEUE */

void checkInPatient();
void viewWaitingQueue();
void callNextPatient();
void completeConsultation();


/* PRIORITY QUEUE */

void addPriorityPatient();
void viewPriorityQueue();
void processPriorityPatient();


/* SMART SCHEDULER */

void smartAppointmentFinder();


/* DASHBOARD */

void dashboard();


/* UTILITY */

Patient *getPatient(int id);
Doctor *getDoctor(int id);
Appointment *getAppointment(int id);

int timeToMinutes(char time[]);
void getCurrentTime(char result[]);

#endif
