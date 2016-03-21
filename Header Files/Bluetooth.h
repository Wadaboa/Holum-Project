//
//
//  Project : Holum
//  File Name : Bluetooth.h
//  Date : 20/03/2016
//
//

class Bluetooth {
	private:
		Clock clock;
		Time time;
		SOCKET bSock;
		SOCKET bSockClient;
		bool available;
		int direction;
	public:
		Bluetooth();
		void manageBluetooth();
		bool init();
		bool bindSocket();
		bool listenSocket();
		bool registerService();
		bool acceptSocket();
		void startCommunication();
		bool isAvailable();
		void isAvailable(bool available);
		void closeSocket();
		int getDirection();
};