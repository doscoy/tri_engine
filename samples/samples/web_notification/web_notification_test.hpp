////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#ifndef WEB_NOTIFICATION_TEST_HPP_INCLUDED
#define WEB_NOTIFICATION_TEST_HPP_INCLUDED


#include "tri_engine.hpp"


class WebNotificationTest
    : public t3::SceneBase
{
public:
    WebNotificationTest();
    ~WebNotificationTest();
    
public:
    void initializeScene() override;
    void terminateScene() override;
    void updateScene(const t3::FrameInfo& frame_info) override;
    
private:
    class SceneContext;
    t3::UniquePtr<SceneContext> context_;

};

#endif // WEB_NOTIFICATION_TEST_HPP_INCLUDED
