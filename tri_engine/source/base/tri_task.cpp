
#include "tri_task.hpp"
#include "dbg/tri_assert.hpp"


namespace t3 {
inline namespace base {

void Task::onPauseTask(const Event& event) {

    const PauseEvent& pause_event = static_cast<const PauseEvent&>(event);

    T3_ASSERT_RANGE(pause_lv_, PAUSE_LV_1, PAUSE_LV_4);
    T3_ASSERT_RANGE(pause_event.getPauseLevel(), PAUSE_LV_1, PAUSE_LV_4);

    if (pause_lv_ <= pause_event.getPauseLevel()) {
        pauseTask();
    }

}


void Task::onResumeTask(const Event& event) {

    const ResumeEvent& resume_event = static_cast<const ResumeEvent&>(event);

    T3_ASSERT_RANGE(pause_lv_, PAUSE_LV_1, PAUSE_LV_4);
    T3_ASSERT_RANGE(resume_event.getPauseLevel(), PAUSE_LV_1, PAUSE_LV_4);

    if (pause_lv_ <= resume_event.getPauseLevel()) {
        resumeTask();
    }
    

}





}   // base
}   // t3

