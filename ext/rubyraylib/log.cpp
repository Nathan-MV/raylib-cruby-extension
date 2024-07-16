// NOTE: Following functions implemented in module [utils]
//------------------------------------------------------------------
// RLAPI void TraceLog(int logLevel, const char *text, ...);         // Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
// RLAPI void SetTraceLogLevel(int logLevel);                        // Set the current threshold (minimum) log level
// RLAPI void *MemAlloc(unsigned int size);                          // Internal memory allocator
// RLAPI void *MemRealloc(void *ptr, unsigned int size);             // Internal memory reallocator
// RLAPI void MemFree(void *ptr);                                    // Internal memory free

// Set custom callbacks
// WARNING: Callbacks setup is intended for advanced users
// RLAPI void SetTraceLogCallback(TraceLogCallback callback);         // Set custom trace log
// RLAPI void SetLoadFileDataCallback(LoadFileDataCallback callback); // Set custom file binary data loader
// RLAPI void SetSaveFileDataCallback(SaveFileDataCallback callback); // Set custom file binary data saver
// RLAPI void SetLoadFileTextCallback(LoadFileTextCallback callback); // Set custom file text data loader
// RLAPI void SetSaveFileTextCallback(SaveFileTextCallback callback); // Set custom file text data saver

// Trace log level
// NOTE: Organized by priority level
// typedef enum {
//     LOG_ALL = 0,        // Display all logs
//     LOG_TRACE,          // Trace logging, intended for internal use only
//     LOG_DEBUG,          // Debug logging, used for internal debugging, it should be disabled on release builds
//     LOG_INFO,           // Info logging, used for program execution info
//     LOG_WARNING,        // Warning logging, used on recoverable failures
//     LOG_ERROR,          // Error logging, used on unrecoverable failures
//     LOG_FATAL,          // Fatal logging, used to abort program: exit(EXIT_FAILURE)
//     LOG_NONE            // Disable logging
// } TraceLogLevel;
