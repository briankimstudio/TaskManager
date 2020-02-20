/**
 * Periodic task manager for Arduino/ESP8266/ESP32
 *  * 
 * February 2020, Brian Kim
 */

#include "TaskManager.h"

TaskManager::TaskManager() {

};
int TaskManager::addTask(unsigned long interval,void(*callback)(), int runOnce) {
    unsigned long currentMillis = millis();
    taskItem newTask = {_id, TM_ENABLE, runOnce, currentMillis, interval, callback};
    Serial.printf("addTask id:%d %u\n",_id,interval);
    _table.push_back(newTask);
    return _id++;
};

void TaskManager::run() {
    unsigned long currentMillis = millis();
    std::vector<taskItem>::iterator p = _table.begin();
    while ( p != _table.end() ) {
        if ((currentMillis - (*p).lastMills > (*p).interval) && (*p).status == TM_ENABLE) {
            if ( (*p).mode == TM_RUNONCE ) {
                (*p).status = TM_DISABLE;
            }
            (*p).lastMills = currentMillis;
            (*p).callback();
        }
        *p++;
     }
};
void TaskManager::modifyInterval(int id, unsigned long interval) {
    std::vector<taskItem>::iterator p = _table.begin();
    while ( p != _table.end() ) {
        if ((*p).id == id) {
            Serial.printf("modifyInterval id:%d %u\n",id,interval);
            (*p).interval = interval;
            return;
        }
        *p++;
     }
};

void TaskManager::modifyStatus(int id, int status) {
    unsigned long currentMillis = millis();
    std::vector<taskItem>::iterator p = _table.begin();
    while ( p != _table.end() ) {
        if ((*p).id == id) {
            Serial.printf("modifyStatus id:%d %d\n",id,status);
            (*p).status = status;
            (*p).lastMills = currentMillis;
            return;
        }
        *p++;
     }
}
void TaskManager::disable(int id) {
    modifyStatus(id,TM_DISABLE);
};
void TaskManager::enable(int id) {
    modifyStatus(id,TM_ENABLE);
};

void setLed(int flag) {
  if ( flag ) {
    digitalWrite(LED,LED_ON);
  } else {
    digitalWrite(LED,LED_OFF);
  }
}
void ledOn() {
    setLed(1);
}
void ledOff() {
    setLed(0);
}
void ledInvert() {
    digitalWrite(LED,!(digitalRead(LED)));    
}
