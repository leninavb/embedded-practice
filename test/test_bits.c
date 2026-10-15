#include "unity.h"
#include "bits.h"

void setUp(void) {}
void tearDown(void) {}

void test_bit_set(void) {
    TEST_ASSERT_EQUAL_HEX32(0x00000001, bit_set(0x00000000, 0));
    TEST_ASSERT_EQUAL_HEX32(0x80000000, bit_set(0x00000000, 31));
    TEST_ASSERT_EQUAL_HEX32(0x00000001, bit_set(0x00000001, 0));
}

void test_bit_clear(void) {
    TEST_ASSERT_EQUAL_HEX32(0x000000FE, bit_clear(0x000000FF, 0));
    TEST_ASSERT_EQUAL_HEX32(0x7FFFFFFF, bit_clear(0xFFFFFFFF, 31));
}

void test_bit_toggle(void) {
    TEST_ASSERT_EQUAL_HEX32(0x00000008, bit_toggle(0x00000000, 3));
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bit_toggle(0x00000008, 3));
}

void test_bit_read(void) {
    TEST_ASSERT_EQUAL_UINT8(1, bit_read(0x00000010, 4));
    TEST_ASSERT_EQUAL_UINT8(0, bit_read(0x00000010, 3));
}

void test_posicion_fuera_de_rango(void) {
    TEST_ASSERT_EQUAL_HEX32(0x00000001, bit_set(0x00000001, 32));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, bit_clear(0xFFFFFFFF, 32));
    TEST_ASSERT_EQUAL_UINT8(0, bit_read(0xFFFFFFFF, 32));
}

void test_field_extract(void) {
    TEST_ASSERT_EQUAL_HEX32(0x3,        field_extract(0xABCD1234, 4, 4));
    TEST_ASSERT_EQUAL_HEX32(0xABCD,     field_extract(0xABCD1234, 16, 16));
    TEST_ASSERT_EQUAL_HEX32(0xABCD1234, field_extract(0xABCD1234, 0, 32));
}

void test_field_extract_invalido(void) {
    TEST_ASSERT_EQUAL_HEX32(0, field_extract(0xFFFFFFFF, 28, 8));
    TEST_ASSERT_EQUAL_HEX32(0, field_extract(0xFFFFFFFF, 0, 0));
}

void test_field_write(void) {
    TEST_ASSERT_EQUAL_HEX32(0x000000A0, field_write(0x00000000, 4, 4, 0xA));
    TEST_ASSERT_EQUAL_HEX32(0xFFFF00FF, field_write(0xFFFFFFFF, 8, 8, 0x00));
    TEST_ASSERT_EQUAL_HEX32(0x000000AF, field_write(0x0000000F, 4, 4, 0xA));
}

void test_field_write_valor_muy_grande(void) {
    TEST_ASSERT_EQUAL_HEX32(0x000000F0, field_write(0x00000000, 4, 4, 0x1F));
}

void test_field_write_invalido(void) {
    TEST_ASSERT_EQUAL_HEX32(0x00000000, field_write(0x00000000, 28, 8, 0xFF));
}

void test_bit_count(void) {
    TEST_ASSERT_EQUAL_UINT8(0,  bit_count(0x00000000));
    TEST_ASSERT_EQUAL_UINT8(1,  bit_count(0x00000001));
    TEST_ASSERT_EQUAL_UINT8(16, bit_count(0xA5A5A5A5));
    TEST_ASSERT_EQUAL_UINT8(32, bit_count(0xFFFFFFFF));
}
void test_field_write_ancho_cero(void) {
    TEST_ASSERT_EQUAL_HEX32(0x12345678, field_write(0x12345678, 4, 0, 0xF));
}

void test_field_write_ancho_completo(void) {
    TEST_ASSERT_EQUAL_HEX32(0xDEADBEEF, field_write(0x12345678, 0, 32, 0xDEADBEEF));
}

void test_field_extract_ancho_completo(void) {
    TEST_ASSERT_EQUAL_HEX32(0xABCD1234, field_extract(0xABCD1234, 0, 32));
}

void test_bit_count_kernighan(void) {
    TEST_ASSERT_EQUAL_UINT8(0,  bit_count_kernighan(0x00000000));
    TEST_ASSERT_EQUAL_UINT8(1,  bit_count_kernighan(0x00000001));
    TEST_ASSERT_EQUAL_UINT8(16, bit_count_kernighan(0xA5A5A5A5));
    TEST_ASSERT_EQUAL_UINT8(32, bit_count_kernighan(0xFFFFFFFF));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_bit_set);
    RUN_TEST(test_bit_clear);
    RUN_TEST(test_bit_toggle);
    RUN_TEST(test_bit_read);
    RUN_TEST(test_posicion_fuera_de_rango);
    RUN_TEST(test_field_extract);
    RUN_TEST(test_field_extract_invalido);
    RUN_TEST(test_field_write);
    RUN_TEST(test_field_write_valor_muy_grande);
    RUN_TEST(test_field_write_invalido);
    RUN_TEST(test_bit_count);
    RUN_TEST(test_field_write_ancho_cero);
    RUN_TEST(test_field_write_ancho_completo);
    RUN_TEST(test_field_extract_ancho_completo);
    RUN_TEST(test_bit_count_kernighan);
    return UNITY_END();
}