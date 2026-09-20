target_sources(silverlight PRIVATE
        src/Shared/Cafe/swkbd.cpp
		src/Shared/CemuBind.cpp
        src/Shared/strop.cpp
        src/Shared/netop.cpp
        src/Shared/crypto.cpp
		#src/Shared/image.cpp
        src/Shared/Core/Logging.cpp
        src/Shared/Reflection/Assembly.cpp
        src/Shared/Reflection/AssemblyRegistry.cpp
        src/Shared/Reflection/NativeImpl/NativeAssembly.cpp
		src/Shared/SilverlightConfig.cpp

)
