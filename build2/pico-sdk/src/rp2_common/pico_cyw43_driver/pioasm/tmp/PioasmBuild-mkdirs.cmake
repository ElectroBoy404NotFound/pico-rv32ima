# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/codespace/raspberry-pi-pico/pico/pico-sdk/tools/pioasm"
  "/workspaces/pico-rv32ima/build2/pioasm"
  "/workspaces/pico-rv32ima/build2/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm"
  "/workspaces/pico-rv32ima/build2/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/workspaces/pico-rv32ima/build2/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "/workspaces/pico-rv32ima/build2/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/workspaces/pico-rv32ima/build2/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/workspaces/pico-rv32ima/build2/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/workspaces/pico-rv32ima/build2/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
