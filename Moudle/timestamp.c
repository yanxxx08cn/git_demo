#include "timestamp.h"
#include "FreeRTOS.h"
#include "task.h"

/* 最大值 */
#define LIB_MAX(a, b) (((a) > (b)) ? (a) : (b))
/* 最小值 */
#define LIB_MIN(a, b) (((a) < (b)) ? (a) : (b))

#define TIMESTAMP_TIMER_IRQHANDLER

TIMESTAMP RTC_Timestamp;
TIMESTAMP UpTime_Timestamp;

void Timestamp_Init(void)
{
    TIMESTAMP tmp_time = {.msec = 0, .sec = 0};

    // 运行时间
    UpTime_Timestamp = tmp_time;

    // RTC时间
    RTC_Timestamp = tmp_time;
}

TIMESTAMP Timestamp_GetUpTime(void)
{
    return UpTime_Timestamp;
}

TIMESTAMP Timestamp_GetRTCTime(void)
{
    return RTC_Timestamp;
}

int32_t Timestamp_Sub(TIMESTAMP t1, TIMESTAMP t2)
{
    int32_t max_s = LIB_MAX((t1).sec, (t2).sec);
    int32_t min_s = LIB_MIN((t1).sec, (t2).sec);
    return (((max_s - min_s) > (0x7FFFFFFF / 1000 - 1))
                ? ((t1).sec > (t2).sec ? 0x7FFFFFFF : -0x7FFFFFFF)
                : (((t1).sec - (t2).sec) * 1000 + ((t1).msec - (t2).msec)));
}

int32_t Timestamp_Elapsed(TIMESTAMP t)
{
    TIMESTAMP now = Timestamp_GetUpTime();

    return Timestamp_Sub(now, t);
}

uint8_t Timestamp_IsEmpty(TIMESTAMP t)
{
    return (t.sec == 0) && (t.msec == 0);
}

void my_delay_us(uint32_t us)
{
}

void my_delay_ms(uint32_t ms)
{
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED &&
        !xPortIsInsideInterrupt())
    {
        vTaskDelay(ms);
    }
    else
    {
        my_delay_us(1000 * ms);
    }
}

void my_delay_s(uint32_t s)
{
    while (s--)
    {
        my_delay_ms(1000);
    }
}
