//
// Created by grupo8 on 18/04/2024.
//

#ifndef INICIALIZACAO_H
#define INICIALIZACAO_H

#include <iostream>
#include <fstream>
#include "structs.h"








Plane* chegada(int numPlanes, const string* flightName, int numFlightName, const string* model, int numModel, const string* origin, int numOrigin, const string* destination, int numDestination, int capacity, const string* pNome, int numPnome, const string* sNome, int numSnome, const string* nat, int numNat);
Plane* descolados(int numPlanes, const string* flightName, int numFlightName, const string* model, int numModel, const string* origin, int numOrigin, const string* destination, int numDestination, int capacity, const string* pNome, int numPnome, const string* sNome, int numSnome, const string* nat, int numNat);
Plane* pista(Plane* inf);









//Pedro

void saveData(Plane* head, const string& filename);
void loadData(Plane*& head, const string& filename);
PassengerNode* createPassengerNode(const Passenger& passenger);
Plane* removeLastPlane(Plane*& head);
void removePlane(Plane*& head, const std::string& nome);
NationalityNode* insertNationalityNode(NationalityNode*& head, const string& nationality);
NationalityNode* findOrCreateNationalityNode(NationalityNode*& head, const string& nationality);

//e structs

//Ralph

void addPassengerToPlane(Plane& plane, const Passenger& passenger);
void createPassengersForPlane(Plane& plane, int numPassengers, const string* pNome, int numPnome, const string* sNome, int numSnome, const string* nat, int numNat);
Plane* createPlane(const string* flightName, int numFlightName, const string* model, int numModel, const string* origin, int numOrigin, const string* destination, int numDestination, int capacity, const string* pNome, int numPnome, const string* sNome, int numSnome, const string* nat, int numNat);
Plane* createPlanes(int numPlanes, const string* flightName, int numFlightName, const string* model, int numModel, const string* origin, int numOrigin, const string* destination, int numDestination, int capacity, const string* pNome, int numPnome, const string* sNome, int numSnome, const string* nat, int numNat);
void printPlanes(Plane* head);
Plane* reversePlaneList(Plane* head);

//Andre

string* readFromFile(const string& filename, int& QTDados);
void addPassengerInOrder(Passenger*& head, Passenger* newPassenger);
void addPassengerToNationalityList(NationalityNode* node, const Passenger& passenger);
void showPassengersOnRunway(Plane* runwayHead);
void showPassengersByNationality(Plane* runwayHead);
void searchPassengersByName(Plane* arrivalHead, Plane* departureHead, const std::string& firstName);
void editPassengerNationality(Plane* arrivalHead, int ticketNo, const std::string& newNationality);

//Quim

void addPlaneToList(Plane*& head, Plane* newPlane);
Plane* movePlanesC_P(const string* flightName, int numFlightName,Plane*& head,const string* destination,int numDestination,int capacity, const string* pNome, int numPnome, const string* sNome, int numSnome, const string* nat, int numNat);
Plane* movePlanesP_D(Plane*& head);
int countPlanes(Plane* head);
void emergencia(Plane*& head, const string& nome, Plane*& head2, const string& nome2, Plane*& head3);
void closeAirport(Plane*& chegadaList, int& closedCycles);
void reopenAirport(Plane*& chegadaList, Plane*& pistaList, Plane*& descoladaList, int& closedCycles, string* flightName, int numFlightName, string* model, int numModel, string* origin, int numOrigin, string* destination, int numDestination, string* pNome, int numPnome, string* sNome, int numSnome, string* nat, int numNat);

#endif
