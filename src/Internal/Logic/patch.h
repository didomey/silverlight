#pragma once
#include<cstdint>
#include<Shared/Core/Logging.h>
#include<coreinit/dynload.h>
#include<vector>
#include<mutex>
#include <string>
inline uint8_t* text_section;
inline uint8_t* data_section;


static std::once_flag initialized_rpl_pointers;

inline void init_rpl_pointers(){
  auto rpl_count = OSDynLoad_GetNumberOfRPLs();

  std::vector<OSDynLoad_NotifyData> rpls(rpl_count);

  if(!OSDynLoad_GetRPLInfo(0, rpl_count, rpls.data())){
    CAFEERROR("failed to get rpls");
  }


  for(auto rpl: rpls){
    if(strstr(rpl.name, "Gambit") != NULL){
      text_section = (uint8_t*)rpl.textAddr;

      data_section = (uint8_t*)rpl.dataAddr;
    }
  }
}
