#pragma once

#include<coreinit/dynload.h>
#include "Shared/Core/Logging.h"

#define LOAD_FUNC(handle, func) \
	{ \
		OSDynLoad_Error err = OSDynLoad_FindExport(handle, OS_DYNLOAD_EXPORT_FUNC, #func, (void **) (&func)); \
		if (err != OSDynLoad_Error::OS_DYNLOAD_OK) { \
    		CAFEERROR("Couldn't find function with error code: " + std::to_string(err)); \
		} \
	}
