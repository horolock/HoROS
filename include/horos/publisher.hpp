#ifndef HOROS_PUBLISHER_HPP
#define HOROS_PUBLISHER_HPP

#include <string>
#include <memory>

#include "horos/topic_registry.hpp"
#include "horos/message.hpp"

namespace horos {

class Publisher {
public:
    Publisher(std::shared_ptr<TopicRegistry> registry, const std::string& topic_name) :
        registry_(registry), topic_name_(topic_name) {}

    void publish(std::shared_ptr<IntMessage> msg) {
        if (registry_) {
            registry_->publish(topic_name_, msg);
        }
    }

private:
    std::shared_ptr<TopicRegistry> registry_;
    std::string topic_name_;

};

} // namespace horos

#endif // HOROS_PUBLISHER_HPP