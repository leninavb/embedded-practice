#ifndef CAN_FRAME_H
#define CAN_FRAME_H

#include <stdint.h>

#define CAN_MAX_DLC    8u
#define CAN_MAX_ID     0x1FFFFFFFu   /* 29 bits (formato extendido) */
#define CAN_FRAME_SIZE 13u           /* 4 (id) + 1 (dlc) + 8 (datos) */

typedef struct {
    uint32_t id;
    uint8_t  dlc;
    uint8_t  data[CAN_MAX_DLC];
} can_frame_t;

/* Formato en bytes:
 *   [0..3]  id, big-endian (byte más significativo primero)
 *   [4]     dlc
 *   [5..12] datos; los bytes después de dlc van en 0
 * Devuelven 0 si todo bien y -1 si hay un argumento inválido. */
int can_serialize(const can_frame_t *frame, uint8_t *buf, uint8_t buf_len);
int can_deserialize(const uint8_t *buf, uint8_t buf_len, can_frame_t *frame);

#endif