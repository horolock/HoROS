#include "horos/node.hpp"
#include "horos/message.hpp"

#include <memory>

int main() {
    auto global_registry = std::make_shared<horos::TopicRegistry>();

    auto talker_node = std::make_shared<horos::Node>("talker", global_registry);
    auto listener_node = std::make_shared<horos::Node>("listener", global_registry);

    listener_node->create_subscription("chatter", [](std::shared_ptr<horos::IntMessage> msg) {
        std::cout << " -> [Listener Node] I heard: " << msg->data << std::endl;
    });

    auto chatter_pub = talker_node->create_publisher("chatter");

    auto message = std::make_shared<horos::IntMessage>();
    message->data = 100;

    chatter_pub->publish(message);

    return 0;
}