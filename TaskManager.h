/**
 * Periodic task manager for Arduino/ESP8266/ESP32
 *  * 
 * February 2020, Brian Kim
 */

#ifndef Task_Manager_h
#define Task_Manager_h

#include <vector>
#include <Arduino.h>

#if defined(ESP8266)
#define LED     2
#define LED_ON  LOW
#define LED_OFF HIGH
#elif defined(ESP32)
#define LED     2
#define LED_ON  HIGH
#define LED_OFF LOW
#endif

void setLed(int flag);
void ledOn();
void ledOff();
void ledInvert();

#define TM_DISABLE 0
#define TM_ENABLE  1
#define TM_NORMAL  0
#define TM_RUNONCE 1

typedef struct {
    int id;
    int status; // 1 enable 0 disable
    int mode; // TM_NORMAL, TM_RUNONCE
    unsigned long lastMills;
    unsigned long interval;
    void(*callback)();
} taskItem;

class TaskManager {
    private:
    int _id;
    std::vector<taskItem> _table;
    public:
    TaskManager();
    int addTask(unsigned long interval,void(*callback)(),int runOnce = TM_NORMAL);
    void modifyInterval(int id, unsigned long interval);
    void disable(int id);
    void enable(int id);
    void modifyStatus(int id, int status);
    void run();
};

#endif