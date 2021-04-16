#!/usr/bin/env bash

function test_convert() {
	echo "Converting \"$1\""
	./convert "$1"
	echo
}

make
test_convert "."
test_convert "f"
test_convert "0"
test_convert "nan"
test_convert "+inf"
test_convert "+inff"
test_convert "-inf"
test_convert "-inff"
test_convert "42.0f"
test_convert "*"
test_convert "0.0"
test_convert "a"
test_convert "42"
test_convert "9999f"
test_convert "-9999f"
test_convert "{"
test_convert "123"
test_convert "123.123f"
test_convert "123.123"
test_convert "999999999999999999999999999999999999999999999999999999999999999f"
test_convert "999999999999999999999999999999999999999999999999999999999999999"
test_convert "999999999999999999999999999999f"
test_convert "999999999999999999999999999999"
test_convert "NaN"
test_convert "0x23"
test_convert "InfiniTY"
test_convert "1234567890"
test_convert "1234567890.0f"
test_convert "1234567890.0"
test_convert ".."
test_convert ".0"
test_convert ".f"
test_convert ".000000000005f"
test_convert ".000000000005"
test_convert "hello"
test_convert "127.9"
test_convert "128"
test_convert "-1"
test_convert "+2147483647"
test_convert "+2147483648"
test_convert "+2147483648f"
test_convert "+2147483648.0"
test_convert "-2147483648"
test_convert "-2147483649"
test_convert "-2147483649f"
test_convert "-2147483649.0"
test_convert "--"
test_convert "++"
test_convert "+.f"
test_convert "-.f"
test_convert "-f"
test_convert "+f"
test_convert "+."
test_convert "-."
test_convert "+.0"
test_convert "-.0"
test_convert "+.0f"
test_convert "-.0f"
test_convert "-.1.0"
test_convert "-.1f0"