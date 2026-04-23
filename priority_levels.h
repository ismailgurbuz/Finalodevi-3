#ifndef PRIORITY_LEVELS_H
#define PRIORITY_LEVELS_H

// RFC 9213 standardına göre öncelik aralığı 0-7 (0 en yüksek)
typedef struct {
    int request_id;
    int urgency;      // RFC 9213: u=0 (High) to u=7 (Low)
    char method[8];   // GET, POST vb.
    char path[256];
} HttpRequest;

#endif