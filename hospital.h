#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 60
#define PHONE_LEN 20
#define SPEC_LEN 60
#define DATE_LEN 11
#define TIME_LEN 6

#define PATIENT_FILE "data/patients.dat"
#define DOCTOR_FILE "data/doctors.dat"
#define APPOINTMENT_FILE "data/appointments.dat"

/* =========================
   PATIENT LINKED LIST
   ========================= */

typedef struct Patient
{
    int id;
    char name[NAME_LEN];
    int age;
    char gender[15];
    char phone[PHONE_LEN];

    struct Patient *next;
} Patient;


/* =========================
   DOCTOR LINKED LIST
   ========================= */

typedef struct Doctor
{
    int id;
    char name[NAME_LEN];
    char specialization[SPEC_LEN];

    char startTime[TIME_LEN];
    char endTime[TIME_LEN];

    struct Doctor *next;
} Doctor;


/* =========================
   APPOINTMENT LINKED LIST
   ========================= */

typedef struct Appointment
{
    int id;
    int patientId;
    int doctorId;

    char date[DATE_LEN];
    char time[TIME_LEN];
    char status[25];

    struct Appointment *next;
} Appointment;


/* =========================
   FIFO WAITING QUEUE
   ========================= */

typedef struct WaitingNode
{
    int appointmentId;

    struct WaitingNode *next;
} WaitingNode;


/* =========================
   PRIORITY QUEUE
   ========================= */

typedef struct PriorityNode
{
    int patientId;
    int doctorId;

    char date[DATE_LEN];

    /*
       1 = Emergency
       2 = Urgent
       3 = Senior Citizen
       4 = Normal
    */
    int priority;

    unsigned long sequence;

    struct PriorityNode *next;
} PriorityNode;


/* =========================
   GLOBAL HEAD POINTERS
   ========================= */

extern Patient *patientHead;
extern Doctor *doctorHead;
extern Appointment *appointmentHead;

extern WaitingNode *waitingFront;
extern WaitingNode *waitingRear;

extern PriorityNode *priorityHead;


/* =========================
   PATIENT FUNCTIONS
   ========================= */

void registerPatient(void);
void viewPatients(void);
void searchPatient(void);

Patient *findPatientById(int id);

void loadPatients(void);
void savePatients(void);


/* =========================
   DOCTOR FUNCTIONS
   ========================= */

void addDoctor(void);
void viewDoctors(void);

Doctor *findDoctorById(int id);

void loadDoctors(void);
void saveDoctors(void);


/* =========================
   APPOINTMENT FUNCTIONS
   ========================= */

void bookAppointment(void);
void viewAppointments(void);

void patientCheckIn(void);

void completeConsultation(void);
void cancelAppointment(void);

Appointment *findAppointmentById(int id);

void loadAppointments(void);
void saveAppointments(void);


/* =========================
   WAITING QUEUE
   ========================= */

void enqueueWaiting(int appointmentId);
int dequeueWaiting(void);

void viewWaitingQueue(void);
void callNextPatient(void);


/* =========================
   PRIORITY QUEUE
   ========================= */

void addPriorityPatient(void);
void viewPriorityQueue(void);
void processPriorityPatient(void);


/* =========================
   SMART SCHEDULER
   ========================= */

void smartAppointmentFinder(void);

int isSlotAvailable(
    int doctorId,
    const char *date,
    const char *time
);

void handleEarlyCompletion(
    int doctorId,
    const char *date,
    const char *completedTime
);


/* =========================
   HELPERS
   ========================= */

int timeToMinutes(const char *time);
void minutesToTime(int minutes, char *buffer);

const char *priorityName(int priority);

#endif