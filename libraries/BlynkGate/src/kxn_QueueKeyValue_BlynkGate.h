/**
 * @file kxn_QueueKeyValue.h
 * @author your name (you@domain.com)
 * @brief 
 * @version kxn_QueueKeyValue_h_1.0.2
 * @date 2024-03-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef kxn_QueueKeyValue_h
#define kxn_QueueKeyValue_h

#include "Arduino.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

#define STRUCT_QUEUE_BLYNK_GATE(QueueName) QueueName##Pair

#define DECLARE_QUEUE_BLYNK_GATE(QueueName, KeyType, ValueType, Size) \
typedef struct { \
    KeyType key; \
    ValueType value; \
} QueueName##Pair; \
extern QueueName##Pair QueueName##Array[];

#define DEFINE_QUEUE_BLYNK_GATE(QueueName, KeyType, ValueType, Size) \
QueueName##Pair QueueName##Array[Size]; \
int QueueName##Front = 0; \
int QueueName##Rear = -1; \
int QueueName##Count = 0;\
DEFINE_QUEUE_FUNCTIONS_BLYNK_GATE(QueueName, KeyType, ValueType, Size)

#define ENQUEUE_BLYNK_GATE(QueueName, key, value) enqueue_BlynkGate_##QueueName(key, value)
#define DEQUEUE_BLYNK_GATE(QueueName) dequeue_BlynkGate_##QueueName()
#define GETQUEUESIZE_BLYNK_GATE(QueueName) getQueueSize_BlynkGate_##QueueName()

#define DEFINE_QUEUE_FUNCTIONS_BLYNK_GATE(QueueName, KeyType, ValueType, Size) \
void enqueue_BlynkGate_##QueueName(KeyType key, ValueType value) { \
    if (QueueName##Count == Size) { \
        /*printf(#QueueName " array is full.\n"); */ \
    } else { \
        for (int i = 0; i < QueueName##Count; i++) { \
            if (QueueName##Array[(QueueName##Front + i) % Size].key == key) { \
                QueueName##Array[(QueueName##Front + i) % Size].value = value; \
                return; \
            } \
        } \
        QueueName##Rear = (QueueName##Rear + 1) % Size; \
        QueueName##Array[QueueName##Rear].key = key; \
        QueueName##Array[QueueName##Rear].value = value; \
        QueueName##Count++; \
    } \
} \
\
QueueName##Pair dequeue_BlynkGate_##QueueName() { \
    if (QueueName##Count == 0) { \
        /*printf(#QueueName " array is empty.\n");*/ \
        QueueName##Pair kv = {-1, -1}; \
        return kv; \
    } else { \
        QueueName##Pair kv = QueueName##Array[QueueName##Front]; \
        QueueName##Front = (QueueName##Front + 1) % Size; \
        QueueName##Count--; \
        return kv; \
    } \
} \
\
int getQueueSize_BlynkGate_##QueueName() { \
    return QueueName##Count; \
}



// DEFINE_QUEUE_BLYNK_GATE(Schedule, int, float, 3)

// // https://www.onlinegdb.com/online_c_compiler
// int QueueKeyValueTest() {
//     int key1 = 1, key2 = 2;
//     float value1 = 100.0, value2 = 200.0, value3 = 300.0;
//     ENQUEUE_BLYNK_GATE(Schedule, key1, value1);
//     ENQUEUE_BLYNK_GATE(Schedule, key2, value2);
//     ENQUEUE_BLYNK_GATE(Schedule, 1, 300.0);
//     ENQUEUE_BLYNK_GATE(Schedule, 4, 300.0);
//     ENQUEUE_BLYNK_GATE(Schedule, 5, 300.0);
//     ENQUEUE_BLYNK_GATE(Schedule, 6, 300.0);
//     ENQUEUE_BLYNK_GATE(Schedule, 7, 300.0);
//     ENQUEUE_BLYNK_GATE(Schedule, 8, 300.0);
//     ENQUEUE_BLYNK_GATE(Schedule, 9, 300.0);
//     ENQUEUE_BLYNK_GATE(Schedule, 10, 300.0);
//     ENQUEUE_BLYNK_GATE(Schedule, 11, 300.0);
    
//     printf("Queue size: %d\n", GETQUEUESIZE_BLYNK_GATE(Schedule));
//     SchedulePair kv = DEQUEUE_BLYNK_GATE(Schedule);
//     printf("Dequeued key: %d, value: %f\n", kv.key, kv.value);
//     printf("Queue size: %d\n", GETQUEUESIZE_BLYNK_GATE(Schedule));
    
//     ENQUEUE_BLYNK_GATE(Schedule, 12, 1200.0);
//     printf("Enqueued key: %d, value: %f\n", 12, 1200.00);
//     printf("Queue size: %d\n", GETQUEUESIZE_BLYNK_GATE(Schedule));
    
//     kv = DEQUEUE_BLYNK_GATE(Schedule);
//     printf("Dequeued key: %d, value: %f\n", kv.key, kv.value);
//     printf("Queue size: %d\n", GETQUEUESIZE_BLYNK_GATE(Schedule));
    
//     kv = DEQUEUE_BLYNK_GATE(Schedule);
//     printf("Dequeued key: %d, value: %f\n", kv.key, kv.value);
//     printf("Queue size: %d\n", GETQUEUESIZE_BLYNK_GATE(Schedule));
//     return 0;
// }

#endif