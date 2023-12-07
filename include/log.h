#ifndef _LOG_H_
#define _LOG_H_
#include <cstdio>

typedef enum {
    LOG_LEVEL_VERBOSE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_NOTICE,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERR,
    LOG_LEVEL_CLOSE,
}log_level_t;

extern FILE *logfile;
extern log_level_t loglevel;
extern const char *log_level_name[LOG_LEVEL_CLOSE];

extern unsigned long get_log_time();
extern bool log_init(const char *logfile_name, log_level_t level);
extern void log_finish();

#define LOG_TRACE(level, format, ...) \
do  {\
    if(level >= loglevel)    \
        fprintf(logfile, "[Time:%lu][%s] " format, get_log_time(), log_level_name[level], ##__VA_ARGS__);   \
} while(0)

#define LOG_TRACE_NOTAG(level, format, ...) \
do  {\
    if(level >= loglevel)    \
        fprintf(logfile, format, ##__VA_ARGS__);   \
} while(0)

#define SLOG_TRACE(server, level, format, ...) \
do  {\
    if(level >= server.lvl)    \
        fprintf(server.fd, "[Time:%lu][%s] " format, get_log_time(), log_level_name[level], ##__VA_ARGS__);   \
} while(0)

#define SLOG_TRACE_NOTAG(server, level, format, ...) \
do  {\
    if(level >= server.lvl)    \
        fprintf(server.fd, format, ##__VA_ARGS__);   \
} while(0)


#ifdef DEBUG_PRINT
#define LOGV(format, ...) LOG_TRACE(LOG_LEVEL_VERBOSE, format, ##__VA_ARGS__)
#define LOGD(format, ...) LOG_TRACE(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define LOGV_NTAG(format, ...) LOG_TRACE_NOTAG(LOG_LEVEL_VERBOSE, format, ##__VA_ARGS__)
#define LOGD_NTAG(format, ...) LOG_TRACE_NOTAG(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define SLOGV(server, format, ...) SLOG_TRACE(server, LOG_LEVEL_VERBOSE, format, ##__VA_ARGS__)
#define SLOGD(server, format, ...) SLOG_TRACE(server, LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#else
#define LOGV(format, ...)
#define LOGD(format, ...)
#define LOGV_NTAG(format, ...)
#define LOGD_NTAG(format, ...)
#define SLOGV(server, format, ...)
#define SLOGD(server, format, ...)
#endif
#define LOGI(format, ...) LOG_TRACE(LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define LOGN(format, ...) LOG_TRACE(LOG_LEVEL_NOTICE, format, ##__VA_ARGS__)
#define LOGW(format, ...) LOG_TRACE(LOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define LOGE(format, ...) LOG_TRACE(LOG_LEVEL_ERR, format, ##__VA_ARGS__)
#define LOGI_NTAG(format, ...) LOG_TRACE_NOTAG(LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define LOGN_NTAG(format, ...) LOG_TRACE_NOTAG(LOG_LEVEL_NOTICE, format, ##__VA_ARGS__)
#define LOGW_NTAG(format, ...) LOG_TRACE_NOTAG(LOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define LOGE_NTAG(format, ...) LOG_TRACE_NOTAG(LOG_LEVEL_ERR, format, ##__VA_ARGS__)

#define SLOGI(server, format, ...) SLOG_TRACE(server, LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define SLOGN(server, format, ...) SLOG_TRACE(server, LOG_LEVEL_NOTICE, format, ##__VA_ARGS__)
#define SLOGW(server, format, ...) SLOG_TRACE(server, LOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define SLOGG(server, format, ...) SLOG_TRACE(server, LOG_LEVEL_ERR, format, ##__VA_ARGS__)

#define LOG_STDOUT(format, ...) \
do { \
    fprintf(stdout, "[Time:%lu]" format, get_log_time(), ##__VA_ARGS__);  \
} while(0)

#define LOG_STDOUT_NOTAG(format, ...) \
do { \
    fprintf(stdout, format, ##__VA_ARGS__);  \
} while(0)

#define LOG_STDERR(format, ...) \
do { \
    fprintf(stderr, "[Time:%lu]" format, get_log_time(), ##__VA_ARGS__);  \
} while(0)

#define LOG_STDERR_NOTAG(format, ...) \
do { \
    fprintf(stderr, format, ##__VA_ARGS__);  \
} while(0)


class LogServer {
public:
    ~LogServer();

    bool log_server_init(const char *log_name, log_level_t level);

    void verbose(const char *format, ...);
    void debug(const char *format, ...);
    void info(const char *format, ...);
    void notice(const char *format, ...);
    void warn(const char *format, ...);
    void err(const char *format, ...);

    FILE *fd = NULL;
    log_level_t lvl;
};

#endif