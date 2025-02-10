#ifndef UTIL_H
#define UTIL_H

#define __NO_COPY__(__class_name_) \
    __class_name_(const __class_name_ &) = delete; \
    __class_name_ &operator(const __class_name_ &) = delete

#endif