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

    BufferedPort<Bottle> out;
    out.open("/sender");

    // Aspetta che /receiver sia disponibile
    bool ok = false;
    for (int i = 0; i < 10; ++i) {
        ok = Network::connect("/sender", "/receiver");
        if (ok) {
            std::cout << "Sender connesso a /receiver" << std::endl;
            break;
        } else {
            std::cout << "Tentativo di connessione fallito, riprovo..." << std::endl;
            std::this_thread::sleep_for(1s);
        }
    }

    if (!ok) {
        std::cerr << "Impossibile connettere /sender a /receiver dopo vari tentativi." << std::endl;
        return 1;
    }

    while (true) {
        Bottle& msg = out.prepare();
        msg.clear();
        msg.addString("Hello from sender");
        std::cout << "Sender: " << msg.toString() << std::endl;
        out.write();
        std::this_thread::sleep_for(1s);
    }

    out.close();
    return 0;
}
