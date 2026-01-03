#include "horos/topic_registry.hpp"
#include "horos/message.hpp"

int main(int argc, char* argv[]) {

    auto registry = std::make_shared<horos::TopicRegistry>();

    registry->subscribe("chatter", [](std::shared_ptr<horos::IntMessage> msg) {
        std::cout << "[Topic: chatter] Subscriber1 received: " << msg->data << std::endl;
    });

    registry->subscribe("chatter", [](std::shared_ptr<horos::IntMessage> msg) {
        std::cout << "[Topic: chatter] Subscriber2 received: " << msg->data << std::endl;
    });

    auto message = std::make_shared<horos::IntMessage>();

    message->data = 42;

    registry->publish("chatter", message);

    return 0;
}