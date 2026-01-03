#ifndef HOROS_TOPIC_REGISTRY_HPP
#define HOROS_TOPIC_REGISTRY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include "horos/message.hpp"

namespace horos {

class TopicRegistry {
public:
    using Callback = std::function<void(std::shared_ptr<IntMessage>)>;

    void subscribe(const std::string& topic_name, Callback cb) {
        registry_[topic_name].push_back(cb);
    }

    void publish(const std::string& topic_name, std::shared_ptr<IntMessage> msg) {
        std::cout << "[Topic : " << topic_name << "] Publisher sent: " << msg->data << std::endl;

        if (registry_.find(topic_name) != registry_.end()) {
            for (const auto& callback : registry_[topic_name]) {
                callback(msg);
            }
        }
    }

private:
    std::map<std::string, std::vector<Callback>> registry_;

};

} // namespace horos

#endif // HOROS_TOPIC_REGISTRY_HPP