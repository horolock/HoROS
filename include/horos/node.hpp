#ifndef HOROS_NODE_HPP
#define HOROS_NODE_HPP

#include <string>
#include <memory>
#include <vector>

#include "horos/topic_registry.hpp"
#include "horos/publisher.hpp"

namespace horos {

class Node {
public:
    Node(const std::string& node_name, std::shared_ptr<TopicRegistry> registry)
        : node_name_(node_name), registry_(registry) {

        std::cout << "[Node : " << node_name_ << "] has been initialized." << std::endl;
    }

    std::shared_ptr<Publisher> create_publisher(const std::string& topic_name) {
        return std::make_shared<Publisher>(registry_, topic_name);
    }

    void create_subscription(const std::string& topic_name, TopicRegistry::Callback cb) {
        registry_->subscribe(topic_name, cb);
    }

    std::string get_name() const { return node_name_; }

private:
    std::string node_name_;
    std::shared_ptr<TopicRegistry> registry_;
};

} // namespace horos
#endif // HOROS_NODE_HPP
