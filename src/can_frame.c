#include "can_frame.h"
#include <stddef.h>

int can_serialize(const can_frame_t *frame, uint8_t *buf, uint8_t buf_len)
{

    if (frame == NULL || buf == NULL){
        return -1;
    }
    if (buf_len < CAN_FRAME_SIZE){
        return -1;
    }
    if (frame->dlc > CAN_MAX_DLC){
        return -1;
    }
    if (frame->id > CAN_MAX_ID){
        return -1;
    }

    buf[0] = (frame->id >> 24) & 0xFF;
    buf[1] = (frame->id >> 16) & 0xFF;
    buf[2] = (frame->id >> 8) & 0xFF;
    buf[3] = (frame->id >> 0) & 0xFF;
    buf[4] = frame->dlc;

    for (uint8_t i = 0; i < CAN_MAX_DLC; i++){
        if (i < frame -> dlc){
            buf[5+i] = frame->data[i];
        } else{
            buf[5+i]= 0;
        }
    }
    return 0;
}

int can_deserialize(const uint8_t *buf, uint8_t buf_len, can_frame_t *frame)
{
    if (frame == NULL || buf == NULL){
        return -1;
    }
    if (buf_len < CAN_FRAME_SIZE){
        return -1;
    }



    uint32_t b1 = (uint32_t)buf[0] << 24;
    uint32_t b2 = (uint32_t)buf[1] << 16;
    uint32_t b3 = (uint32_t)buf[2] << 8;
    uint32_t b4 = (uint32_t)buf[3] << 0;
    uint32_t pre_id = b1 | b2 | b3 | b4;
    if (pre_id > CAN_MAX_ID){
        return -1;
    }
    uint8_t b5 = (uint32_t)buf[4];
    if (b5 > CAN_MAX_DLC){
        return -1;
    }
    frame -> dlc = b5;
    frame -> id = pre_id;



    for ( uint8_t i = 0; i < CAN_MAX_DLC; i++){
        if (i < b5){
            frame -> data[i] = buf[5+i]; 
        } else{
            frame -> data[i] = 0;
        }
    }

    return 0;
}