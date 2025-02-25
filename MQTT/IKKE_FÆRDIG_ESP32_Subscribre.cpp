
/* 
A C++ MQTT Subscriber that subscribes 
to the test/temperature topic 
*/

#include <mosquittopp.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

class MQTTSubscriber : public mosqpp::mosquittopp
{
public:
    MQTTSubscriber(const char *id, const char *host, int port) : mosquittopp(id)
    {
        connect(host, port, 60);
    }

    void on_connect(int rc)
    {
        if (rc == 0) {
            std::cout << "Connected to MQTT broker." << std::endl;
            subscribe(NULL, "test/temperature");
        } else {
            std::cout << "Failed to connect. RC: " << rc << std::endl;
        }
    }

    void on_message(const struct mosquitto_message *message)
    {
        if(message->payloadlen) {
            std::cout << "Received message on topic " << message->topic 
                      << ": " << static_cast(message->payload) << std::endl;
        } else {
            std::cout << "Received empty message on topic " << message->topic << std::endl;
        }
    }
};

int main()
{
    const char *host = "localhost";
    int port = 1883;

    mosqpp::lib_init();

    MQTTSubscriber subscriber("subscriber", host, port);

    while(true) {
        subscriber.loop();
        sleep(1);
    }

    mosqpp::lib_cleanup();

    return 0;
}

