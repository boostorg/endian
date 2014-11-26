# invoke: sed -r -i -f <path-to-this-file> <files-to-change...>

# name changes in arithmetic.hpp
s/(big|little|native)_(int|uint|float)(8|16|24|32|40|48|56|64)_t/\1_\2\3_ut/g
s/(big|little|native)_align_(int|uint|float)(8|16|24|32|40|48|56|64)_t/\1_\2\3_t/g

# name changes in conversion.hpp
s/(big|little)_endian\(/reverse_in_place_unless_native_\1(/g
s/(big|little)_endian_value\(/reverse_unless_native_\1(/g
