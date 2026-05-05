#include "../includes/Game.hpp"

#if (defined(ENABLE_FPGA_USB) || defined(__MICROBLAZE__) || defined(__PPC__)) && __has_include("xil_cache.h")
#define ENABLE_XILINX_CACHE 1
#include "xil_cache.h"
#endif

extern "C" int main(void){
#if defined(ENABLE_XILINX_CACHE)
   Xil_ICacheEnable();
   Xil_DCacheEnable();
#endif

   return Game::OnExecute();
}
