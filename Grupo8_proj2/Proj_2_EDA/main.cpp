/**
Grupo 8
André Afonso Teixeira Pereira 2052923
André Luís Pontes Gonçalves
Joaquim PAUlo Freitas Ferreira 2053023
Pedro Afonso Jesus Gouveia 2122123
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "inicializacao.h"
#include "structs.h"
#include <string>

using namespace std;
//quim
void closeAirport(Plane*& chegadaList, int& closedCycles) {
    cout << "Fechando aeroporto..." << endl;
    closedCycles = rand() % 5 + 1;  // Random number of cycles between 1 and 5
    cout << "Aeroporto fechado por " << closedCycles << " ciclos." << endl;
}
//quim
void reopenAirport(Plane*& chegadaList, Plane*& pistaList, Plane*& descoladaList, int& closedCycles, string* flightName, int numFlightName, string* model, int numModel, string* origin, int numOrigin, string* destination, int numDestination, string* pNome, int numPnome, string* sNome, int numSnome, string* nat, int numNat) {
    while (closedCycles > 0) {
        cout << "Aeroporto fechado. Restam " << closedCycles << " ciclos." << endl;

        // Add new planes to chegadaList even if it exceeds 10 planes
        addPlaneToList(chegadaList, createPlanes(1, flightName, numFlightName, model, numModel, origin, numOrigin, destination, numDestination, rand() % 5 + 16, pNome, numPnome, sNome, numSnome, nat, numNat));
        closedCycles--;
    }

    cout << "Reabrindo aeroporto e despachando backlog..." << endl;

    // Handle backlog
    while (countPlanes(chegadaList) > 10) {
        addPlaneToList(pistaList, movePlanesC_P(flightName, numFlightName, chegadaList, destination, numDestination, rand() % 5 + 16, pNome, numPnome, sNome, numSnome, nat, numNat));
        if (countPlanes(pistaList) > 7) {
            addPlaneToList(descoladaList, movePlanesP_D(pistaList));
        }
        if (countPlanes(descoladaList) > 5) {
            removeLastPlane(descoladaList);
        }
    }
}

int main() {
    const int numChegadas = 10;
    const int numPartidas = 5;
    const int numPista = 7;
    const int capacidadeMin = 10;
    const int capacidadeMax = 15;

    srand(time(nullptr));

    int numModel, numOrigin, numDestination, numCapacities, numFlightName, numPnome, numSnome, numNat;

    string* flightName = readFromFile("voo.txt", numFlightName);
    string* model = readFromFile("modelo.txt", numModel);
    string* origin = readFromFile("origem.txt", numOrigin);
    string* destination = readFromFile("destino.txt", numDestination);

    string* pNome = readFromFile("primeiro_nome.txt", numPnome);
    string* sNome = readFromFile("segundo_nome.txt", numSnome);
    string* nat = readFromFile("nacionalidade.txt", numNat);

    Plane* chegadaList = createPlanes(10, flightName, numFlightName, model, numModel, origin, numOrigin, destination, numDestination, rand() % 5 + 16, pNome, numPnome, sNome, numSnome, nat, numNat);
    Plane* pistaList = nullptr;
    Plane* descoladaList = nullptr;

    string av_at;
    string av_dc;

    int closedCycles = 0; // Variable to track the number of closed cycles

    char opcao;
    do {
        // Mostrar menu
        cout << "\n\n=========== Menu ===========" << endl;
        cout << "s - Simular ciclo" << endl;
        cout << "g - Gravar dados" << endl;
        cout << "l - Carregar dados" << endl;
        cout << "e - EMERGENCIA" << endl;
        cout << "o - Opcoes" << endl;
        cout << "i - Inverter pista" << endl;
        cout << "c - Fechar aeroporto" << endl;
        cout << "q - Sair" << endl;
        cout << "============================" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 's':
                if (closedCycles > 0) {
                    closedCycles--;
                    cout << "Aeroporto fechado. Ciclos restantes: " << closedCycles << endl;
                    addPlaneToList(chegadaList, createPlanes(1, flightName, numFlightName, model, numModel, origin, numOrigin, destination, numDestination, rand() % 5 + 16, pNome, numPnome, sNome, numSnome, nat, numNat));
                } else {
                    // Simular ciclo
                    addPlaneToList(pistaList, movePlanesC_P(flightName, numFlightName, chegadaList, destination, numDestination, rand() % 5 + 16, pNome, numPnome, sNome, numSnome, nat, numNat));
                    addPlaneToList(chegadaList, createPlanes(1, flightName, numFlightName, model, numModel, origin, numOrigin, destination, numDestination, rand() % 5 + 16, pNome, numPnome, sNome, numSnome, nat, numNat));

                    if (countPlanes(pistaList) > 7) {
                        addPlaneToList(descoladaList, movePlanesP_D(pistaList));
                    }

                    if (countPlanes(descoladaList) > 5) {
                        removeLastPlane(descoladaList);
                    }

                    cout << "\n\n=========== Chegada ===========";
                    printPlanes(chegadaList);
                    cout << "\n\n=========== Pista ===========";
                    printPlanes(pistaList);
                    cout << "\n\n=========== Partida ===========";
                    printPlanes(descoladaList);
                }
                break;

            case 'g':
                // Gravar dados
                saveData(chegadaList, "chegada.txt");
                saveData(pistaList, "pista.txt");
                saveData(descoladaList, "descolada.txt");
                break;

            case 'l':
                // Carregar dados
                loadData(chegadaList, "chegada.txt");
                loadData(pistaList, "pista.txt");
                loadData(descoladaList, "descolada.txt");
                break;

            case 'q':
                // Sair
                cout << "Saindo do programa..." << endl;
                break;

            case 'e':
                cout << "EMERGENCIA" << endl;
                cout << "Qual o nome do voo a aterrar? ";
                cin >> av_at;
                cout << "Qual o nome do voo a descolar? ";
                cin >> av_dc;

                emergencia(chegadaList, av_at, pistaList, av_dc, descoladaList);
                break;
            case 'o':
                // Menu de opções
                char subOption;
                do {
                    cout << "1. Mostrar os passageiros em pista" << endl;
                    cout << "2. Mostrar todos os passageiros em pista por nacionalidade, ordenados por ordem alfabetica" << endl;
                    cout << "3. Pesquisa sobre os passageiros nas chegadas e partidas (pelo primeiro nome)" << endl;
                    cout << "4. Editar a nacionalidade de passageiro num voo das chegadas" << endl;
                    cout << "b - Voltar" << endl;
                    cin >> subOption;

                    string firstName, newNationality;
                    int ticketNo;

                    switch (subOption) {
                        case '1':
                            showPassengersOnRunway(pistaList);
                            break;
                        case '2':
                            showPassengersByNationality(pistaList);
                            break;
                        case '3':
                            cout << "Digite o primeiro nome do passageiro: ";
                            cin >> firstName;
                            searchPassengersByName(chegadaList, descoladaList, firstName);
                            break;
                        case '4':
                            cout << "Digite o numero do bilhete do passageiro: ";
                            cin >> ticketNo;
                            cout << "Digite a nova nacionalidade do passageiro: ";
                            cin >> newNationality;
                            editPassengerNationality(chegadaList, ticketNo, newNationality);
                            break;
                    }
                } while (subOption != 'b');
                break;
            case 'i':
                // Inverter prioridade dos aviões em pista
                pistaList = reversePlaneList(pistaList);
                cout << "Prioridade dos avioes em pista invertida." << endl;
                break;

            case 'c':
                if (closedCycles == 0) {
                    closeAirport(chegadaList, closedCycles);
                } else {
                    cout << "Aeroporto ja esta fechado por " << closedCycles << " ciclos restantes." << endl;
                }
                break;

            default:
                cout << "Opcao invalida! Por favor, escolha uma opcao valida." << endl;
        }

        if (closedCycles == 0 && countPlanes(chegadaList) > 10) {
            reopenAirport(chegadaList, pistaList, descoladaList, closedCycles, flightName, numFlightName, model, numModel, origin, numOrigin, destination, numDestination, pNome, numPnome, sNome, numSnome, nat, numNat);
        }

    } while (opcao != 'q');

    return 0;
}