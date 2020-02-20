# TaskManager
Periodic task manager for Arduino/ESP8266/ESP32
Developing an application for Arduino/ESP8266/ESP32 often requires a need for executing certain functions at a specified interval. For example, if we want to turn LED on and off periodically, we may use delay() or millis() function to control it repeatedly. However, it is tedious to code control routines every time manually. That's exactly where TaskManager comes in to help you out and let you focus on the core logic.

TaskManager suppors two types of task; periodic task and run once task. 

*Periodic task* refers to a task that need to be called at a given interval repeatedly. It never ends and keep going while the system is running. TaskManager creates *Periodic task* by default.

*Run once task* refers to a task that will be called only once after a given interval. For example, if we want to turn LED off after 5 seconds, it would be implemented with *Run once task* type. To make a *run once task*, TM_RUNONCE option should be provided when task is created.

**1. Define a function.**

First, we need a function that is supposed to be running at a certain interval.
```
void f1() {
  Serial.println("5 second");
}
```

**2. Call `addTask()` with interval(milliseconds) and function name**

In this example, `f1` will be executed every 5 seconds
```
TaskManager taskMgr;
void setup() {
  taskMgr.addTask(5000,f1);
}
```

If we want to run the task only once, then we can specify the option `TM_RUNONCE` as a third parameter to `addTask()`. 
This is demonstrated in the example below.

**3. Call `run()` in main `loop`**

```
void loop() {
  taskMgr.run();
}
```

**Periodic task example code**

It demonstrates how to call function `f1` in every second.

```
#include "TaskManager.h"

TaskManager taskMgr;

void f1() {
  Serial.println("1 second");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello world");
  taskMgr.addTask(1000,f1); 
}

void loop() {
  taskMgr.run();
}
```

**Run once task example code**

It demonstrates how to run a task only once after a cetrain period. `f2` will be called after 5 seconds only once. 
It won't be called periodically.

```
#include "TaskManager.h"

TaskManager taskMgr;

void f2() {
  Serial.println("only once");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello world");
  taskMgr.addTask(5000,f2,TM_RUNONCE);
}

void loop() {
  taskMgr.run();
}
```
