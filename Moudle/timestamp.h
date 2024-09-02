#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <stdint.h>

typedef struct __timestamp TIMESTAMP, *PTIMESTAMP;

struct __timestamp
{
    volatile int32_t sec;
    volatile int32_t msec;
};

void Timestamp_Init(void);
TIMESTAMP Timestamp_GetUpTime(void);
TIMESTAMP Timestamp_GetRTCTime(void);

int32_t Timestamp_Sub(TIMESTAMP t1, TIMESTAMP t2);
int32_t Timestamp_Elapsed(TIMESTAMP t);
uint8_t Timestamp_IsEmpty(TIMESTAMP t);

void my_delay_us(uint32_t us);
void my_delay_ms(uint32_t ms);
void my_delay_s(uint32_t s);

extern TIMESTAMP UpTime_Timestamp;

#endif /* TIMESTAMP_H */
