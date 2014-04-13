
#ifndef TRI_EVENT_LISTENER_HPP_INCLUDED
#define TRI_EVENT_LISTENER_HPP_INCLUDED

#include "tri_event.hpp"
#include <memory>



namespace t3 {
inline namespace base {

//  イベントリスナ
class EventListener {
public:
    explicit EventListener() {}
    virtual ~EventListener() {}
    
public:
    
    //  リスナー名を取得
    virtual const char* getListenerName() const = 0;
    
    //  イベントを受けたか伝える
    //  伝播させたい（受けてない）時はfalseを返す
    virtual bool handleEvent(const EventInterface& event) = 0;

};

using EventListenerPtr = std::shared_ptr<EventListener>;

//  全てのイベントを受けるクラス
class EventSnooper
    : public EventListener {

public:
    EventSnooper();
    ~EventSnooper();

public:
    const char* getListenerName() const override {
        return "Snooper";
    }

    bool handleEvent(const EventInterface& event) override;
    
private:
    char msg_buffer_[4090];
};

}   // namespace base
}   // namespace t3

#endif  // TRI_EVENT_LISTENER_HPP_INCLUDED

