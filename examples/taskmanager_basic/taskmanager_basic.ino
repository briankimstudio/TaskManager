#include "TaskManager.h"

TaskManager taskMgr;
int tid;

void f1() {
  Serial.println("1 second");
}

void f2() {
  Serial.println("LED OFF");
  ledOff();
  taskMgr.modifyStatus(tid,TM_DISABLE);
}

void setup() {
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  Serial.println("Hello world");
  ledOn();
  tid = taskMgr.addTask(100,ledInvert); 
  // tid = taskMgr.addTask(3000,ledOff,TM_RUNONCE);
  // Serial.println(tid);
  taskMgr.addTask(5000,f2,TM_RUNONCE);
}

void loop() {
  taskMgr.run();
}