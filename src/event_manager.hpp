#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <functional>
#include <vector>

template <class Event>
class EventManager
{
    public:
        static void addListener(std::function<void(const Event&)> to_call)
        {
            if (to_call)
                listeners.push_back(to_call);
        }

        static void fire(const Event &event)
        {
            for (auto &notify : listeners)
                notify(event);
        }

    private:
        static std::vector<std::function<void(const Event&)>> listeners;
};

template <class Event>
std::vector<std::function<void(const Event&)>> EventManager<Event>::listeners =
    std::vector<std::function<void(const Event&)>>();

#endif
