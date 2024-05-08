cmake_minimum_required(VERSION 3.17)
project(XP-LuaDAP)

set(CMAKE_CXX_STANDARD 17)


set( XP_SDK "third_party_source/XPSDK301/SDK/" )
add_definitions( -DXPLM200=1 -DXPLM210=1 -DXPLM300=1 -DXPLM301=1 )

set( INC_XPLANE_SDK
        "${XP_SDK}/CHeaders/Widgets"
        "${XP_SDK}/CHeaders/Wrappers"
        "${XP_SDK}/CHeaders/XPLM"
        )


SET( LRDB_INCLUDES
        "third_party_source/LRDB-main/include"
        "third_party_source/LRDB-main/third_party/picojson"
        "third_party_source/LRDB-main/third_party/asio/asio/include"

        # --- Change the Lua sources here --- You also need to change the linker path.
        #"third_party_source/LRDB-main/third_party/lua-5.3.4/src"
        "/Users/br/Dev/LuaDAP/third_party_source/LuaJIT-2.1/src"
        )


INCLUDE_DIRECTORIES(
        ${INC_XPLANE_SDK}
        ${LRDB_INCLUDES}
)




IF( APPLE )
    # For XCode the exported_symbols_list should be ./mac_exported_symbols.txt
    # For building from the cmd-line using Unix Makefiles the file should be ../mac_exported_symbols.txt
    set( APPLE_EXPORTED_SYMBOLS "../mac_exported_symbols.txt" )
    IF( CMAKE_GENERATOR STREQUAL Xcode )
        set( APPLE_EXPORTED_SYMBOLS "./mac_exported_symbols.txt" )
    ENDIF( CMAKE_GENERATOR STREQUAL Xcode )

    #set(CMAKE_OSX_ARCHITECTURES "arm64")
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
    #set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")

    set(CMAKE_MACOSX_RPATH 0)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "12.00")

    set(CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk")


    #set(CMAKE_CXX_FLAGS "-std=c++17 -fPIC -O2 -Wall -Wextra -Wfatal-errors -Wno-overloaded-virtual -stdlib=libc++ -flto -Wno-unused-parameter -Wno-deprecated-declarations ")
    set(CMAKE_CXX_FLAGS "-std=c++17 -fPIC -O2 -Wall -Wextra -Wfatal-errors -Wno-overloaded-virtual -stdlib=libc++ -flto -Wno-deprecated-declarations ")


    # Linker options
    set(CMAKE_SHARED_LINKER_FLAGS "-ld_classic -undefined warning -flat_namespace -fvisibility=hidden -v -Wall -exported_symbols_list ${APPLE_EXPORTED_SYMBOLS}")

    LINK_DIRECTORIES(
            "libs/mac/LuaJIT-2.1.0-beta3/" # --- Change this if using a different Lua version.
    )

    SET( EXTRA_LIBS
            luajit.a
            )


    add_definitions( -DAPL=1 )


ENDIF( APPLE )




set( PLUGIN_SRCS
        src/library.cpp src/library.h
        )


# Don't do this.
# The "LRDB project" doesn't need to be compiled at all for this plugin to build and work.
#SUBDIRS(
        #"third_party_source/LRDB-main"
#)


add_library(${PROJECT_NAME} SHARED ${PLUGIN_SRCS})

# Tweak the output filename so we get XP-LuaDAP.xpl straight from the linker.
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX  "" )
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES SUFFIX ".xpl")


target_link_libraries( ${PROJECT_NAME} ${EXTRA_LIBS} )

