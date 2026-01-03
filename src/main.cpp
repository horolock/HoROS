#include "horos/node.hpp"
#include "horos/message.hpp"
#include "horos/executor.hpp"

#include <memory>

int main() {
    auto registry = std::make_shared<horos::TopicRegistry>();
    auto executor = std::make_shared<horos::Executor>();

    registry->set_executor(executor);

    auto talker_node = std::make_shared<horos::Node>("talker", registry);
    auto listener_node = std::make_shared<horos::Node>("listener", registry);

    listener_node->create_subscription("chatter", [](std::shared_ptr<horos::IntMessage> msg) {
        std::cout << " -> [Listener Node] Started Processing: " << msg->data << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << " -> [Listener Node] Finished Processing: " << msg->data << std::endl;
    });

    auto chatter_pub = talker_node->create_publisher("chatter");

    auto message = std::make_shared<horos::IntMessage>();
    message->data = 100;

    chatter_pub->publish(message);
    std::cout << "[Main] Publisher call is finished immediately!" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(3));

    return 0;
}