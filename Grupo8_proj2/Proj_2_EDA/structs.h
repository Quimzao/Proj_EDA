//
// Created by grupo8 on 18/04/2024.
//

#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
//Pedro+-
using namespace std;

struct Passenger {
    string First_Name;
    string Second_Name;
    int Ticket_No;
    string Nationality;
    Passenger* next;
};

struct PassengerNode {
    Passenger passenger;
    PassengerNode* next;
};

struct Plane {
    string Flight_Name;
    string Model;
    string Origin;
    string Destination;
    int Capacity;
    int Num_Passengers;
    PassengerNode* passengers;
    Plane* next;
};

struct NationalityNode {
    string nationality;
    Passenger* passengers;
    NationalityNode* next;
};

#endif
