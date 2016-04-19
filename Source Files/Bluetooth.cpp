//
//
//  Project : Holum
//  File Name : Bluetooth.cpp
//  Date : 20/03/2016
//
//

#include <Global.h>
#include <Bluetooth.h>

Bluetooth::Bluetooth() {
    available = false;
    direction = 0;
}

Bluetooth::Bluetooth(const Bluetooth &b) {}

bool Bluetooth::isAvailable() {
    return available;
}

void Bluetooth::isAvailable(bool available) {
    direction = 0;
    this->available = available;
}

int Bluetooth::getDirection() {
    return direction;
}

#ifdef _WIN32
    void Bluetooth::manageBluetooth() {
        time = seconds(0);
        exit = false;
        while (!exit) {
            if (clock.getElapsedTime() >= time) {
                time = seconds(3);
                available = false;
                direction = 0;
                if (!init());
                else if (!bindSocket());
                else if (!listenSocket());
                else if (!registerService());
                else if (!acceptSocket()) {
                    break;
                }
                else {
                    startCommunication();
                    break;
                }
                clock.restart();
            }
        }
    }

    bool Bluetooth::init() {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            #ifdef DEBUG
                cout << "Errore 021: Inizializzazione API Winsock fallita." << endl;
            #endif
            return false;
        }

        bSock = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
        if (bSock == INVALID_SOCKET) {
            #ifdef DEBUG
                cout << "Errore 022: Inizializzazione socket bluetooth fallita." << endl;
            #endif
            return false;
        }
        return true;
    }

    bool Bluetooth::bindSocket() {
        SOCKADDR_BTH bAddress;
        int bLenght;
        bAddress.addressFamily = AF_BTH;
        bAddress.btAddr = 0;
        bAddress.port = BT_PORT_ANY;
        bAddress.serviceClassId = GUID_NULL;
        bLenght = sizeof(bAddress);
        
        if (::bind(bSock, (sockaddr*)&bAddress, bLenght)) {
            #ifdef DEBUG
                cout << "Errore 023: Bind del socket bluetooth fallito." << endl;
            #endif
            return false;
        }
        getsockname(bSock, (sockaddr*)&bAddress, &bLenght);

        return true;
    }

    bool Bluetooth::listenSocket() {
        if (listen(bSock, 1) != 0) {
            #ifdef DEBUG
                cout << "Errore 024: Inizializzazione dello stato di ascolto del socket bluetooth fallita." << endl;
            #endif
            system("pause");
            return false;
        }
        return true;
    }

    bool Bluetooth::registerService() {
        WSAQUERYSET bService;
        GUID uuid;
        HRESULT h = CLSIDFromString(L"{00001105-0000-1000-8000-00805F9B34FB}", (LPCLSID)&uuid);

        memset(&bService, 0, sizeof(bService));
        bService.dwSize = sizeof(bService);
        bService.lpszServiceInstanceName = LPWSTR("HolumBS");
        bService.lpszComment = LPWSTR("Holum Bluetooth Service");
        bService.lpServiceClassId = &uuid;
        bService.dwNumberOfCsAddrs = 1;
        bService.dwNameSpace = NS_BTH;

        SOCKADDR_BTH address;
        sockaddr *tAddr = (sockaddr*)&address;

        int tLength = sizeof(SOCKADDR_BTH);

        getsockname(bSock, tAddr, &tLength);

        CSADDR_INFO csAddress;
        memset(&csAddress, 0, sizeof(csAddress));
        csAddress.LocalAddr.iSockaddrLength = sizeof(SOCKADDR_BTH);
        csAddress.LocalAddr.lpSockaddr = tAddr;
        csAddress.iSocketType = SOCK_STREAM;
        csAddress.iProtocol = BTHPROTO_RFCOMM;
        bService.lpcsaBuffer = &csAddress;

        if (WSASetService(&bService, RNRSERVICE_REGISTER, 0) != 0) {
            #ifdef DEBUG
                cout << "Errore 025: Registrazione del servizio Bluetooth SDP fallita." << endl;
            #endif
            system("pause");
            return false;
        }
        return true;
    }

    bool Bluetooth::acceptSocket() {
        SOCKADDR_BTH bAddressClient;
        int cLenght = sizeof(bAddressClient);

        bSockClient = accept(bSock, (sockaddr*)&bAddressClient, &cLenght);
        if (bSockClient == INVALID_SOCKET) {
            #ifdef DEBUG
                cout << "Errore 026: Socket del client bluetooth non valido." << endl;
            #endif
            return false;
        }
    }

    void Bluetooth::startCommunication() {
        int r = -1;
        char buffer[sizeof(int)] = { 0 };
        while (r != 0) {
            memset(buffer, 0, sizeof(buffer));
            r = recv(bSockClient, (char*)buffer, sizeof(buffer), 0);
            if (r == SOCKET_ERROR) {
                #ifdef DEBUG
                    cout << "Errore 027: Errore sconosciuto durante la comunicazione bluetooth." << endl;
                #endif
                break;
            }
            else {
                int n;
                memcpy(&n, buffer, sizeof(int));
                direction = n;
                available = true;
            }
        }
    }

    void Bluetooth::closeSocket() {
        exit = true;
        closesocket(bSock);
        closesocket(bSockClient);
    }

    bool Bluetooth::checkMessage() {
        fd_set set;
        struct timeval timeout;
        FD_ZERO(&set);
        FD_SET(bSockClient, &set);
        timeout.tv_sec = 0;
        timeout.tv_usec = 100;

        int r = select(bSockClient, &set, NULL, NULL, &timeout);
        if (r == 0 || r == -1) {
            return false;
        }
        else {
            return true;
        }
    }

    int Bluetooth::readMessage() {
        char buffer[sizeof(int)] = { 0 };
        memset(buffer, 0, sizeof(buffer));
        int r = recv(bSockClient, (char*)buffer, sizeof(buffer), 0);
        int n;
        memcpy(&n, buffer, sizeof(int));
        return n;
    }
#endif