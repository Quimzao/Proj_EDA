//
// Created by grupo8 on 18/04/2024.
//
#include <iostream>
#include <fstream>
#include "inicializacao.h"
#include "structs.h"

using namespace std;


//Pedro
void saveData(Plane* head, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error saving file" << endl;
        return;
    }
    Plane* current = head;
    while (current != nullptr) {
        outFile << "Flight Name: " << current->Flight_Name << endl;
        outFile << "Model: " << current->Model << endl;
        outFile << "Origin: " << current->Origin << endl;
        outFile << "Destination: " << current->Destination << endl;
        outFile << "Capacity: " << current->Capacity << endl;
        outFile << "Number of Passengers: " << current->Num_Passengers << endl;
        outFile << "Passengers: " << endl;
        PassengerNode* passengerCurrent = current->passengers;
        while (passengerCurrent != nullptr) {
            outFile << "First Name: " << passengerCurrent->passenger.First_Name << endl;
            outFile << "Second Name: " << passengerCurrent->passenger.Second_Name << endl;
            outFile << "Nationality: " << passengerCurrent->passenger.Nationality << endl;
            outFile << "Ticket Number: " << passengerCurrent->passenger.Ticket_No << endl;
            passengerCurrent = passengerCurrent->next;
        }
        outFile << "-----------------------" << endl;
        current = current->next;
    }
    outFile.close();
    cout << "Data saved to " << filename << endl;
}


//Pedro
void loadData(Plane*& head, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    head = nullptr;
    string line;
    while (getline(inFile, line)) {
        if (line.find("Flight Name: ") != string::npos) {
            Plane* newPlane = new Plane;
            newPlane->Flight_Name = line.substr(line.find(": ") + 2);
            getline(inFile, line);
            newPlane->Model = line.substr(line.find(": ") + 2);
            getline(inFile, line);
            newPlane->Origin = line.substr(line.find(": ") + 2);
            getline(inFile, line);
            newPlane->Destination = line.substr(line.find(": ") + 2);
            getline(inFile, line);
            newPlane->Capacity = stoi(line.substr(line.find(": ") + 2));
            getline(inFile, line);
            newPlane->Num_Passengers = stoi(line.substr(line.find(": ") + 2));
            newPlane->passengers = nullptr;
            newPlane->next = nullptr;
            getline(inFile, line); // "Passengers:"
            for (int i = 0; i < newPlane->Num_Passengers; ++i) {
                Passenger passenger;
                getline(inFile, line);
                passenger.First_Name = line.substr(line.find(": ") + 2);
                getline(inFile, line);
                passenger.Second_Name = line.substr(line.find(": ") + 2);
                getline(inFile, line);
                passenger.Nationality = line.substr(line.find(": ") + 2);
                getline(inFile, line);
                passenger.Ticket_No = stoi(line.substr(line.find(": ") + 2));
                addPassengerToPlane(*newPlane, passenger);
            }
            getline(inFile, line); // "-----------------------"
            addPlaneToList(head, newPlane);
        }
    }
    inFile.close();
    cout << "Data loaded from " << filename << endl;
}

// Function to create a passenger node
//Pedro
PassengerNode* createPassengerNode(const Passenger& passenger) {
    PassengerNode* newNode = new PassengerNode;
    newNode->passenger = passenger;
    newNode->next = nullptr;
    return newNode;
}

// Function to add a passenger to the plane's linked list
//Ralph
void addPassengerToPlane(Plane& plane, const Passenger& passenger) {
    PassengerNode* newNode = createPassengerNode(passenger);

    // If the plane has no passengers yet, add the new passenger as the first passenger
    if (plane.passengers == nullptr) {
        plane.passengers = newNode;
    } else {
        // Otherwise, traverse the linked list to find the last node and add the new passenger there
        PassengerNode* current = plane.passengers;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    // Increment the number of passengers on the plane
    plane.Num_Passengers++;
}

// Function to create passengers for a plane
//Ralph
void createPassengersForPlane(Plane& plane, int numPassengers, const string* pNome, int numPnome, const string* sNome, int numSnome, const string* nat, int numNat) {
    for (int i = 0; i < numPassengers; i++) {
        Passenger passenger;
        passenger.First_Name = pNome[rand() % numPnome];
        passenger.Second_Name = sNome[rand() % numSnome];
        passenger.Ticket_No = rand() % 9000 + 1000;
        passenger.Nationality = nat[rand() % numNat];
        addPassengerToPlane(plane, passenger);
    }
}

// Function to create a plane node
//Ralph
Plane* createPlane(const string* flightName, int numFlightName, const string* model, int numModel, const string* origin, int numOrigin, const string* destination, int numDestination, int capacity, const string* pNome, int numPnome, const string* sNome, int numSnome, const string* nat, int numNat) {
    Plane* newPlane = new Plane;
    newPlane->Flight_Name = flightName[rand() % numFlightName];
    newPlane->Model = model[rand() % numModel];
    newPlane->Origin = origin[rand() % numOrigin];
    newPlane->Destination = "aeroportoEDA";
    //newPlane->Destination = destination[rand() % numDestination];
    newPlane->Capacity = capacity;
    newPlane->passengers = nullptr;
    newPlane->Num_Passengers = 0;
    newPlane->next = nullptr;

    // Allocate passengers to the plane
    createPassengersForPlane(*newPlane, newPlane->Capacity, pNome, numPnome, sNome, numSnome, nat, numNat);

    return newPlane;
}

// Function to add a plane to the linked list of planes
//Quim
void addPlaneToList(Plane*& head, Plane* newPlane) {
    if (head == nullptr) {
        head = newPlane;
    } else {
        Plane* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newPlane;
    }
}

// Function to create planes
//Ralph
Plane* createPlanes(int numPlanes, const string* flightName, int numFlightName, const string* model, int numModel, const string* origin, int numOrigin, const string* destination, int numDestination, int capacity, const string* pNome, int numPnome, const string* sNome, int numSnome, const string* nat, int numNat) {
    Plane* head = nullptr;
    for (int i = 0; i < numPlanes; ++i) {
        Plane* newPlane = createPlane(flightName, numFlightName, model, numModel, origin, numOrigin, destination, numDestination, capacity, pNome, numPnome, sNome, numSnome, nat, numNat);
        addPlaneToList(head, newPlane);
    }
    return head;
}

// Function to read data from a file and return it as a dynamic array of strings
//Andre
string* readFromFile(const string& filename, int& QTDados) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    // Contar o número de nomes no ficheiro
    QTDados = 0;
    string line;
    while (getline(file, line)) {
        QTDados++;
    }

    // Voltar ao início do ficheiro e ler as marcas para o array dinâmico
    file.clear();
    file.seekg(0);

    string* dados = new string[QTDados];
    int i = 0;
    while (getline(file, line)) {
        dados[i++] = line;
    }

    file.close();
    return dados;
}

// Function to print the list of planes
//Ralph
void printPlanes(Plane* head) {
    Plane* current = head;
    while (current != nullptr) {
        cout <<"\n\n" << "| Flight Name: " << current->Flight_Name << "| \n";
        cout << "| Model: " << current->Model << "| \n";
        cout << "| Origin: " << current->Origin << "| \n";
        cout << "| Destination: " << current->Destination << "| \n";
        cout << "| Capacity: " << current->Capacity << "| \n" ;
        cout << "| Number of Passengers: " << current->Num_Passengers << "| \n" ;
        cout << "| Passengers:" ;

        PassengerNode* passengerCurrent = current->passengers;
        while (passengerCurrent != nullptr) {
            cout << passengerCurrent->passenger.First_Name << " " << passengerCurrent->passenger.Second_Name << " | ";
            passengerCurrent = passengerCurrent->next;
        }

        current = current->next;
    }
}


//Quim
Plane* movePlanesC_P(const string* flightName, int numFlightName,Plane*& head,const string* destination,int numDestination,int capacity, const string* pNome, int numPnome, const string* sNome, int numSnome, const string* nat, int numNat) {
    if (head == nullptr) {
        return nullptr;
    }

    Plane* planeToMove = head; // Get the first plane
    planeToMove->Flight_Name = flightName[rand() % numFlightName];
    planeToMove->Destination = destination[rand() % numDestination];

    planeToMove->passengers = nullptr;
    planeToMove->Num_Passengers = 0;

    createPassengersForPlane(*planeToMove, planeToMove->Capacity, pNome, numPnome, sNome, numSnome, nat, numNat);

    head = head->next; // Update head to the next plane
    planeToMove->next = nullptr; // Detach the plane from the list

    return planeToMove;
}
//Quim
Plane* movePlanesP_D(Plane*& head) {
    if (head == nullptr) {
        return nullptr;
    }

    Plane* planeToMove = head; // Get the first plane
    head = head->next; // Update head to the next plane
    planeToMove->next = nullptr; // Detach the plane from the list

    return planeToMove;
}

//Quim
int countPlanes(Plane* head) {
    int count = 0;
    Plane* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}
//Pedro
Plane* removeLastPlane(Plane*& head) {
    if (head == nullptr) {
        return nullptr; // List is empty, nothing to remove
    }

    if (head->next == nullptr) {
        // Only one plane in the list
        Plane* lastPlane = head;
        head = nullptr; // Update head to nullptr as list will be empty after removal
        return lastPlane;
    }

    // Iterate to find the second-to-last plane
    Plane* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    // Current is now the second-to-last plane
    Plane* lastPlane = current->next; // Last plane to remove
    current->next = nullptr; // Remove the last plane by setting second-to-last's next to nullptr

    return lastPlane;
}
//Pedro
void removePlane(Plane*& head, const std::string& nome) {
    Plane* current = head;
    Plane* previous = nullptr;

    while (current != nullptr) {
        if (current->Flight_Name == nome) {
            if (current == head) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}
//Quim
void emergencia(Plane*& head, const string& nome, Plane*& head2, const string& nome2, Plane*& head3) {
    // Search for the plane with nome in head
    Plane* prev = nullptr;
    Plane* current = head;

    while (current != nullptr) {
        if (current->Flight_Name == nome) {
            // Remove the plane from head
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            current->next = nullptr;

            // Add the plane to head2
            addPlaneToList(head2, current);

            // Now search for the plane with nome2 in head2
            Plane* prev2 = nullptr;
            Plane* current2 = head2;

            while (current2 != nullptr) {
                if (current2->Flight_Name == nome2) {
                    // Remove the plane from head2
                    if (prev2 == nullptr) {
                        head2 = current2->next;
                    } else {
                        prev2->next = current2->next;
                    }
                    current2->next = nullptr;

                    // Add the plane to head3
                    addPlaneToList(head3, current2);
                    break;
                }
                prev2 = current2;
                current2 = current2->next;
            }
            break;
        }
        prev = current;
        current = current->next;
    }
}
//Ralph
Plane* reversePlaneList(Plane* head) {
    Plane* prev = nullptr;
    Plane* current = head;
    Plane* next = nullptr;

    while (current != nullptr) {
        next = current->next;  // Armazenar próximo nó
        current->next = prev;  // Reverter o próximo do nó atual
        prev = current;        // Mover o prev um passo adiante
        current = next;        // Mover o current um passo adiante
    }
    head = prev;
    return head;
}



//Pedro
NationalityNode* insertNationalityNode(NationalityNode*& head, const string& nationality) {
    NationalityNode* newNode = new NationalityNode;
    newNode->nationality = nationality;
    newNode->passengers = nullptr;
    newNode->next = nullptr;

    if (head == nullptr || head->nationality > nationality) {
        newNode->next = head;
        head = newNode;
        return newNode;
    }

    NationalityNode* current = head;
    while (current->next != nullptr && current->next->nationality < nationality) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    return newNode;
}
//Pedro
NationalityNode* findOrCreateNationalityNode(NationalityNode*& head, const string& nationality) {
    NationalityNode* current = head;
    while (current != nullptr) {
        if (current->nationality == nationality) {
            return current;
        }
        current = current->next;
    }

    return insertNationalityNode(head, nationality);
}
//andre
void addPassengerInOrder(Passenger*& head, Passenger* newPassenger) {
    if (head == nullptr || (head->First_Name + head->Second_Name) > (newPassenger->First_Name + newPassenger->Second_Name)) {
        newPassenger->next = head;
        head = newPassenger;
    } else {
        Passenger* current = head;
        while (current->next != nullptr && (current->next->First_Name + current->next->Second_Name) < (newPassenger->First_Name + newPassenger->Second_Name)) {
            current = current->next;
        }
        newPassenger->next = current->next;
        current->next = newPassenger;
    }
}

void addPassengerToNationalityList(NationalityNode* node, const Passenger& passenger) {
    Passenger* newPassenger = new Passenger(passenger);
    newPassenger->next = nullptr;
    addPassengerInOrder(node->passengers, newPassenger);
}

void showPassengersByNationality(Plane* runwayHead) {
    NationalityNode* nationalityHead = nullptr;

    Plane* currentPlane = runwayHead;
    while (currentPlane != nullptr) {
        PassengerNode* currentPassenger = currentPlane->passengers;
        while (currentPassenger != nullptr) {
            NationalityNode* nationalityNode = findOrCreateNationalityNode(nationalityHead, currentPassenger->passenger.Nationality);
            addPassengerToNationalityList(nationalityNode, currentPassenger->passenger);
            currentPassenger = currentPassenger->next;
        }
        currentPlane = currentPlane->next;
    }

    for (NationalityNode* natNode = nationalityHead; natNode != nullptr; natNode = natNode->next) {
        cout << "Nationality: " << natNode->nationality << endl;
        Passenger* passenger = natNode->passengers;
        while (passenger != nullptr) {
            cout << "Passenger: " << passenger->First_Name << " " << passenger->Second_Name << " | ";
            cout << "Ticket No: TK" << passenger->Ticket_No << endl;
            passenger = passenger->next;
        }
    }

    // Clean up allocated memory
    while (nationalityHead != nullptr) {
        NationalityNode* temp = nationalityHead;
        nationalityHead = nationalityHead->next;
        delete temp;
    }
}

void showPassengersOnRunway(Plane* runwayHead) {
    Plane* currentPlane = runwayHead;
    while (currentPlane != nullptr) {
        cout << "Plane: " << currentPlane->Flight_Name << " - " << currentPlane->Model << endl;
        PassengerNode* currentPassenger = currentPlane->passengers;
        while (currentPassenger != nullptr) {
            cout << "Passenger: " << currentPassenger->passenger.First_Name << " " << currentPassenger->passenger.Second_Name << " | ";
            cout << "Ticket No: " << currentPassenger->passenger.Ticket_No << " | ";
            cout << "Nationality: " << currentPassenger->passenger.Nationality << endl;
            currentPassenger = currentPassenger->next;
        }
        currentPlane = currentPlane->next;
    }
}

void searchPassengersByName(Plane* arrivalHead, Plane* departureHead, const string& firstName) {
    Plane* currentPlane = arrivalHead;
    bool found = false;
    while (currentPlane != nullptr) {
        PassengerNode* currentPassenger = currentPlane->passengers;
        while (currentPassenger != nullptr) {
            if (currentPassenger->passenger.First_Name == firstName) {
                cout << "Passenger: " << currentPassenger->passenger.First_Name << " " << currentPassenger->passenger.Second_Name << " | ";
                cout << "Ticket No: " << currentPassenger->passenger.Ticket_No << " | ";
                cout << "Nationality: " << currentPassenger->passenger.Nationality << " | ";
                cout << "Plane: " << currentPlane->Flight_Name << " (Arrival)" << endl;
                found = true;
            }
            currentPassenger = currentPassenger->next;
        }
        currentPlane = currentPlane->next;
    }

    currentPlane = departureHead;
    while (currentPlane != nullptr) {
        PassengerNode* currentPassenger = currentPlane->passengers;
        while (currentPassenger != nullptr) {
            if (currentPassenger->passenger.First_Name == firstName) {
                cout << "Passenger: " << currentPassenger->passenger.First_Name << " " << currentPassenger->passenger.Second_Name << " | ";
                cout << "Ticket No: " << currentPassenger->passenger.Ticket_No << " | ";
                cout << "Nationality: " << currentPassenger->passenger.Nationality << " | ";
                cout << "Plane: " << currentPlane->Flight_Name << " (Departure)" << endl;
                found = true;
            }
            currentPassenger = currentPassenger->next;
        }
        currentPlane = currentPlane->next;
    }

    if (!found) {
        cout << "No passenger with the name " << firstName << " found." << endl;
    }
}

void editPassengerNationality(Plane* arrivalHead, int ticketNo, const string& newNationality) {
    Plane* currentPlane = arrivalHead;
    while (currentPlane != nullptr) {
        PassengerNode* currentPassenger = currentPlane->passengers;
        while (currentPassenger != nullptr) {
            if (currentPassenger->passenger.Ticket_No == ticketNo) {
                currentPassenger->passenger.Nationality = newNationality;
                cout << "Nationality updated for Ticket No: " << ticketNo << endl;
                return;
            }
            currentPassenger = currentPassenger->next;
        }
        currentPlane = currentPlane->next;
    }
    cout << "No passenger with Ticket No: " << ticketNo << " found." << endl;
}



