#include <yarp/os/Network.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Bottle.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace yarp::os;
using namespace std::chrono_literals;

int main() {
    Network yarp;

    BufferedPort<Bottle> in;
    in.open("/receiver");

    // Aspetta che /sender sia disponibile
    bool ok = false;
    for (int i = 0; i < 10; ++i) {
        ok = Network::connect("/sender", "/receiver");
        if (ok) {
            std::cout << "Receiver connesso a /sender" << std::endl;
            break;
        } else {
            std::cout << "In attesa di connessione da /sender..." << std::endl;
            std::this_thread::sleep_for(1s);
        }
    }

    if (!ok) {
        std::cerr << "Impossibile connettere /sender a /receiver." << std::endl;
        return 1;
    }

    while (true) {
        Bottle* msg = in.read();
        if (msg != nullptr) {
            std::cout << "Receiver got: " << msg->toString() << std::endl;
        }
    }

    in.close();
    return 0;
}
