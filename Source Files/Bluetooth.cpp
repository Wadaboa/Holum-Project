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
	time = seconds(3);
}

void Bluetooth::manageBluetooth() {
	
	while (true) {
		if (clock.getElapsedTime() > time) {
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
		cout << "Errore 0??: Inizializzazione Winsock API fallita." <<endl;
		return false;
	}

	bSock = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);

	if (bSock == INVALID_SOCKET) {
		cout << "Errore 0??: Inizializzazione socket bluetooth fallita." << endl;
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
		cout << "Errore 0??: Bind del socket fallito." << endl;
		return false;
	}

	getsockname(bSock, (sockaddr*)&bAddress, &bLenght);

	return true;
}

bool Bluetooth::listenSocket() {
	if (listen(bSock, 1) != 0) {
		cout << "Errore 0??: Inizializzazione dello stato di ascolto del socket fallita." << endl;
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
	bService.lpszServiceInstanceName = LPWSTR("Your mom");
	bService.lpszComment = LPWSTR("Coglione");
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
		cout << "Errore 0??: Registrazione del servizio Bluetooth SDP fallita." << endl;
		system("pause");
		return false;
	}
	return true;
}

bool Bluetooth::acceptSocket() {
	SOCKADDR_BTH bAddressClient;
	int cLenght = sizeof(bAddressClient);

	bSockClient = accept(bSock, (sockaddr*)&bAddressClient, &cLenght);
	if (bSockClient == INVALID_SOCKET)
	{
		cout << "Errore 0??: Socket del client non valido." << endl;
		return false;
	}
}

void Bluetooth::startCommunication() {
	int r = -1;

	while (r != 0) {
		char buffer[sizeof(int)] = { 0 };
		memset(buffer, 0, sizeof(buffer));
		r = recv(bSockClient, (char*)buffer, sizeof(buffer), 0);
		if (r == SOCKET_ERROR) {
			cout << "Errore 0??: Errore sconosciuto durante la comunicazione Bluetooth." << endl;
			break;
		}
		else {
			int n;
			memcpy(&n, buffer, sizeof(int));
			if (!available) {
				cout << n << endl;
				direction = n;
				available = true;
			}
		}
	}
}

bool Bluetooth::isAvailable() {
	return available;
}

void Bluetooth::isAvailable(bool available) {
	this->available = available;
	direction = 0;
}

void Bluetooth::closeSocket() {
	closesocket(bSock);
	closesocket(bSockClient);
}

int Bluetooth::getDirection() {
	return direction;
}
