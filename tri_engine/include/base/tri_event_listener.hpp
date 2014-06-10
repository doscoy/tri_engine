
#ifndef TRI_EVENT_LISTENER_HPP_INCLUDED
#define TRI_EVENT_LISTENER_HPP_INCLUDED

#include "tri_event.hpp"
#include <memory>
#include "util/tri_nameable.hpp"


namespace t3 {
inline namespace base {

//  イベントリスナ
class EventListener
    : virtual public Nameable {
    
public:
    explicit EventListener() {}
    virtual ~EventListener();
    
public:
    //  イベントハンドラ
    virtual void handleEvent(const Event& event) = 0;
};

//  全てのイベントを受けるクラス
class EventSnooper
    : public EventListener {

public:
    EventSnooper();
    ~EventSnooper();

public:
    void handleEvent(const Event& event) override;
    
private:
    char msg_buffer_[4090];
};

}   // namespace base
}   // namespace t3

#endif  // TRI_EVENT_LISTENER_HPP_INCLUDED

