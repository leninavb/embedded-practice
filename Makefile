CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -IUnity/src
UNITY = Unity/src/unity.c

build/test_smoke: test/test_smoke.c $(UNITY)
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@

build/test_bits: test/test_bits.c src/bits.c $(UNITY)
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@

test: build/test_smoke build/test_bits
	./build/test_smoke
	./build/test_bits

clean:
	rm -rf build

.PHONY: test clean