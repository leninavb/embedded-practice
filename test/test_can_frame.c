#include "unity.h"
#include "can_frame.h"
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void test_serialize_basico(void) {
    can_frame_t f = { .id = 0x12345678, .dlc = 3, .data = {0xAA, 0xBB, 0xCC} };
    uint8_t buf[CAN_FRAME_SIZE];
    uint8_t esperado[CAN_FRAME_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x03,
                                        0xAA, 0xBB, 0xCC, 0, 0, 0, 0, 0};
    memset(buf, 0xFF, sizeof(buf));
    TEST_ASSERT_EQUAL_INT(0, can_serialize(&f, buf, CAN_FRAME_SIZE));
    TEST_ASSERT_EQUAL_HEX8_ARRAY(esperado, buf, CAN_FRAME_SIZE);
}

void test_serialize_endianness(void) {
    can_frame_t f = { .id = 0x00000001, .dlc = 0 };
    uint8_t buf[CAN_FRAME_SIZE];
    TEST_ASSERT_EQUAL_INT(0, can_serialize(&f, buf, CAN_FRAME_SIZE));
    TEST_ASSERT_EQUAL_HEX8(0x00, buf[0]);
    TEST_ASSERT_EQUAL_HEX8(0x01, buf[3]);
}

void test_serialize_argumentos_invalidos(void) {
    can_frame_t f = { .id = 0x123, .dlc = 2 };
    uint8_t buf[CAN_FRAME_SIZE];
    TEST_ASSERT_EQUAL_INT(-1, can_serialize(NULL, buf, CAN_FRAME_SIZE));
    TEST_ASSERT_EQUAL_INT(-1, can_serialize(&f, NULL, CAN_FRAME_SIZE));
    TEST_ASSERT_EQUAL_INT(-1, can_serialize(&f, buf, CAN_FRAME_SIZE - 1));
    f.dlc = 9;
    TEST_ASSERT_EQUAL_INT(-1, can_serialize(&f, buf, CAN_FRAME_SIZE));
    f.dlc = 2;
    f.id = 0x20000000;
    TEST_ASSERT_EQUAL_INT(-1, can_serialize(&f, buf, CAN_FRAME_SIZE));
}

void test_deserialize_basico(void) {
    uint8_t buf[CAN_FRAME_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x03,
                                   0xAA, 0xBB, 0xCC, 0, 0, 0, 0, 0};
    can_frame_t f;
    TEST_ASSERT_EQUAL_INT(0, can_deserialize(buf, CAN_FRAME_SIZE, &f));
    TEST_ASSERT_EQUAL_HEX32(0x12345678, f.id);
    TEST_ASSERT_EQUAL_UINT8(3, f.dlc);
    TEST_ASSERT_EQUAL_HEX8(0xAA, f.data[0]);
    TEST_ASSERT_EQUAL_HEX8(0xCC, f.data[2]);
    TEST_ASSERT_EQUAL_HEX8(0x00, f.data[3]);
}

void test_deserialize_invalidos(void) {
    uint8_t buf[CAN_FRAME_SIZE] = {0};
    can_frame_t f;
    TEST_ASSERT_EQUAL_INT(-1, can_deserialize(NULL, CAN_FRAME_SIZE, &f));
    TEST_ASSERT_EQUAL_INT(-1, can_deserialize(buf, CAN_FRAME_SIZE, NULL));
    TEST_ASSERT_EQUAL_INT(-1, can_deserialize(buf, CAN_FRAME_SIZE - 1, &f));
    buf[4] = 9;   /* dlc inválido */
    TEST_ASSERT_EQUAL_INT(-1, can_deserialize(buf, CAN_FRAME_SIZE, &f));
    buf[4] = 2;
    buf[0] = 0xFF; /* id fuera de 29 bits */
    TEST_ASSERT_EQUAL_INT(-1, can_deserialize(buf, CAN_FRAME_SIZE, &f));
}

void test_ida_y_vuelta(void) {
    can_frame_t f = { .id = 0x1ABCDEF0, .dlc = 8,
                      .data = {1, 2, 3, 4, 5, 6, 7, 8} };
    can_frame_t g;
    uint8_t buf[CAN_FRAME_SIZE];
    TEST_ASSERT_EQUAL_INT(0, can_serialize(&f, buf, CAN_FRAME_SIZE));
    TEST_ASSERT_EQUAL_INT(0, can_deserialize(buf, CAN_FRAME_SIZE, &g));
    TEST_ASSERT_EQUAL_HEX32(f.id, g.id);
    TEST_ASSERT_EQUAL_UINT8(f.dlc, g.dlc);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(f.data, g.data, CAN_MAX_DLC);
}
void test_deserialize_no_modifica_frame_si_falla(void) {
    uint8_t buf[CAN_FRAME_SIZE] = {0x00, 0x00, 0x01, 0x00, 9};  /* dlc inválido */
    can_frame_t f = { .id = 0xABC, .dlc = 5 };
    TEST_ASSERT_EQUAL_INT(-1, can_deserialize(buf, CAN_FRAME_SIZE, &f));
    TEST_ASSERT_EQUAL_HEX32(0xABC, f.id);
    TEST_ASSERT_EQUAL_UINT8(5, f.dlc);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_serialize_basico);
    RUN_TEST(test_serialize_endianness);
    RUN_TEST(test_serialize_argumentos_invalidos);
    RUN_TEST(test_deserialize_basico);
    RUN_TEST(test_deserialize_invalidos);
    RUN_TEST(test_ida_y_vuelta);
    RUN_TEST(test_deserialize_no_modifica_frame_si_falla);
    return UNITY_END();
}