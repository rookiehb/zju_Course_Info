#ifndef __FUNCTION_H__
#define __FUNCTION_H__


#define MAX(a,b) a>b?a:b
#define MIN(a,b) a>b?b:a


/* 500ms定时器事件标志号 */
#define TIMER_BLINK500  1
/* 1000ms定时器事件标志号 */
#define TIMER_BLINK1000 2
/* 500ms定时器事件标志号 但应用不同 因此命名为TIMER_BLINK250*/
#define TIMER_BLINK250 3

#endif
