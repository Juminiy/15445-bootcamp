#ifndef UTIL_H
#define UTIL_H

#define __NO_COPY__(__class_name_) \
    __class_name_(const __class_name_ &) = delete; \
    __class_name_ &operator(const __class_name_ &) = delete

#define __time_now_ std::chrono::steady_clock::now
#define __dur_ms std::chrono::duration_cast<std::chrono::milliseconds>
#define __time_tillnow_dur_ms_(__tm_) __dur_ms(__time_now_()-__tm_).count()
#define __time_sleep_sec(__sec_) std::this_thread::sleep_for (std::chrono::seconds(__sec_))

#endif