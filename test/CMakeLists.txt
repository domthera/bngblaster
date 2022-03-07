include_directories ("../src/")

set(LINK_LIBS cmocka pcap m)

add_executable (test-protocols protocols.c ../src/bbl_protocols.c)
target_include_directories(test-protocols PRIVATE ${LWIP_INCLUDE_DIRS})
target_link_libraries (test-protocols PRIVATE ${LWIP_SANITIZER_LIBS} lwipcore lwipcontribportunix ${LINK_LIBS})
target_compile_options(test-protocols PRIVATE -Werror -Wall -Wextra)
add_test (NAME "TestProtocols" COMMAND test-protocols)

add_executable (test-utils utils.c ../src/bbl_utils.c)
target_include_directories(test-utils PRIVATE ${LWIP_INCLUDE_DIRS})
target_link_libraries (test-utils PRIVATE ${LWIP_SANITIZER_LIBS} lwipcore lwipcontribportunix ${LINK_LIBS})
target_compile_options(test-utils PRIVATE -Werror -Wall -Wextra)
add_test (NAME "TestUtils" COMMAND test-utils)

add_executable (test-decode-pcap protocols_decode_pcap.c ../src/bbl_protocols.c)
target_include_directories(test-decode-pcap PRIVATE ${LWIP_INCLUDE_DIRS})
target_link_libraries (test-decode-pcap PRIVATE ${LWIP_SANITIZER_LIBS} lwipcore lwipcontribportunix ${LINK_LIBS})
target_compile_options(test-decode-pcap PRIVATE -Werror -Wall -Wextra)