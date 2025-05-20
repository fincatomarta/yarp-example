#include <yarp/os/RFModule.h>
#include <yarp/os/ResourceFinder.h>
#include <yarp/os/Network.h>
#include <yarp/os/BufferedPort.h>
#include <iostream>

using namespace yarp::os;

class HelloModule : public RFModule {
    BufferedPort<Bottle> commandPort;
    std::string message = "Ciao dal robot!";
    double period = 1.0;

public:
    double getPeriod() override {
        return period;
    }

    bool updateModule() override {
        std::cout << message << std::endl;

        // Controlla se sono arrivati comandi sulla porta
        Bottle *cmd = commandPort.read(false);
        if (cmd) {
            std::cout << "Ricevuto comando: " << cmd->toString() << std::endl;
        }

        return true;
    }

    bool configure(ResourceFinder &rf) override {
        // Carica messaggio personalizzato se presente
        if (rf.check("message")) {
            message = rf.find("message").asString();
        }

        if (rf.check("period")) {
            period = rf.find("period").asFloat64();
        }

        // Apre la porta per ricevere comandi
        commandPort.open("/helloModule/cmd:i");

        std::cout << "Modulo configurato con messaggio: " << message << std::endl;
        return true;
    }

    bool interruptModule() override {
        commandPort.interrupt();
        return true;
    }

    bool close() override {
        commandPort.close();
        return true;
    }
};

int main(int argc, char *argv[]) {
    Network yarp;
    if (!yarp.checkNetwork()) {
        std::cerr << "Errore: YARP server non disponibile!" << std::endl;
        return 1;
    }

    ResourceFinder rf;
    rf.configure(argc, argv);

    HelloModule module;
    return module.runModule(rf);
}
