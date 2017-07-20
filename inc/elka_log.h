#ifndef ELKA_LOG_H
#define ELKA_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__PX4_ROS)
#include <ros/console.h>
#define LOG_DEBUG(...) ROS_DEBUG(__VA_ARGS__)
#define LOG_INFO(...) ROS_INFO(__VA_ARGS__)
#define LOG_WARN(...) ROS_WARN(__VA_ARGS__)
#define LOG_ERR(...) ROS_ERROR(__VA_ARGS__)

#elif defined(__PX4_QURT) || defined(__PX4_POSIX)

#define LOG_DEBUG(...) PX4_DEBUG(...);
#define LOG_INFO(...) PX4_INFO(...);
#define LOG_WARN(...) PX4_WARN(...);
#define LOG_ERR(...) PX4_ERR(...);

#elif defined(__ELKA_FREERTOS)

//TODO log thru ftdi 
// Debug output on the ELKA board
#include <stdio.h>
#define LOG_DEBUG(...) 
#define LOG_INFO(...) 
#define LOG_WARN(...)
#define LOG_ERR(...) 

#elif defined(__ELKA_UBUNTU)
#include <stdio.h>

#define __elka_log_end_fmt "\n"
#define __elka_log_debug_str_fmt "DEBUG: "
#define __elka_log_info_str_fmt "INFO: "
#define __elka_log_warn_str_fmt "WARN: "
#define __elka_log_err_str_fmt "ERROR: "

#define LOG_DEBUG(fmt, ...) printf(__elka_log_debug_str_fmt\
                                 fmt\
                                 __elka_log_end_fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) printf(__elka_log_info_str_fmt\
                                 fmt\
                                 __elka_log_end_fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) printf(__elka_log_warn_str_fmt\
                                 fmt\
                                 __elka_log_end_fmt, ##__VA_ARGS__)
#define LOG_ERR(fmt, ...) printf(__elka_log_err_str_fmt\
                                 fmt\
                                 __elka_log_end_fmt, ##__VA_ARGS__)

#endif

#ifdef __cplusplus
}
#endif

#endif
