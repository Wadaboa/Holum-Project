//
//
//  Project : Holum
//  File Name : Bluetooth.h
//  Date : 20/03/2016
//
//

class Bluetooth {
    private:
        bool exit;
        Clock clock2;
        Clock clock;
        Time time;
        #ifdef _WIN32
            SOCKET bSock;
            SOCKET bSockClient;
        #endif
        atomic_bool available;
        atomic_int direction;
        int count = 0;
    
    public:
        Bluetooth();
        Bluetooth(const Bluetooth &b);
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

        bool checkMessage();
        int readMessage();
};