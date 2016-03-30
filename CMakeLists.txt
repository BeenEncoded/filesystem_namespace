# This cmake script is COPYRIGHT Jonathan Craig Whitlock
#
# I release this under the MIT License:
#
# ------------------------------------------------------------------------------
# The MIT License (MIT)
#
# Copyright (c) 2014 Jonathan Whitlock
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ------------------------------------------------------------------------------
#
#
# General purpose CMakeLists.txt can generate a makefile
# easily by specifying the folder containing sources,
# and running CMake to generate the makefile.

set(CMAKE_VERSION_USED 3.3.0)

set(PROGRAM_NAME filesystem_abstraction)
set(SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/source)

#compiler flag settings
set(INCLUDE_ALL false) #if true, then it recursively includes all cpp and hpp files
set(ENABLE_MULTITHREADING true)
set(CPLUSPLUS_14 false)
set(C_11 false)
set(STRICT_COMPILE true)
set(STATIC_COMPILE true)
set(OPTIMIZE_BUILD_FLAGS true) #will only be used for release.  :)
set(64_BIT_BUILD true)

#wxWidgets settings:
set(USING_WXWIDGETS_LIB false)

#boost settings
set(USING_BOOST_LIBRARY true)
set(BOOST_LIB_COMPONENTS system filesystem regex) #change these library filenames if necessary
set(BOOST_LIB_COMPONENTS_LITERAL libboost_system.a libboost_filesystem.a libboost_regex.a)

#unittest++
set(USING_UNITTESTPP_LIBS true)

#Additional Libraries
set(USING_ADDITIONAL_LIBS false)
set(ADDITIONAL_LIB_COMPONENTS_LITERAL libUnitTest++.a) #add additional misc libs here

#ncurses settings
set(USING_NCURSES_LIBRARY false)
set(NCURSES_LIB_COMPONENTS ncurses) #change these library filenames if necessary
set(NCURSES_LIB_COMPONENTS_LITERAL libncurses.a)


#-------------------------------------------------------------------------------------------------
set(BUILD_SHARED_LIBS OFF)

# =================================================================================================
# =================================================================================================
# =================================================================================================
# =================================================================================================

macro(target_add_definitions targ defs)
    get_target_property(TARGET_PROPS ${targ} COMPILE_FLAGS)
    if(TARGET_PROPS)
        set_target_properties(${targ} PROPERTIES COMPILE_FLAGS "${TARGET_PROPS} ${defs}")
    else()
        set_target_properties(${targ} PROPERTIES COMPILE_FLAGS "${defs}")
    endif()
endmacro(target_add_definitions)

macro(target_add_preproc_defs targ defs)
    get_target_property(TARGET_PROPS ${targ} COMPILE_DEFINITIONS)
    if(TARGET_PROPS)
        set_target_properties(${targ} PROPERTIES COMPILE_DEFINITIONS "${TARGET_PROPS};${defs}")
    else()
        set_target_properties(${targ} PROPERTIES COMPILE_DEFINITIONS "${defs}")
    endif()
endmacro(target_add_preproc_defs)

#sets c++14
macro(use_cplusplus14 targ)
    target_add_definitions(${targ} "-std=c++14")
endmacro(use_cplusplus14)

#sets c99
macro(use_c99 targ)
    target_add_definitions(${targ} "-std=c99")
endmacro(use_c99)

#sets c11
macro(use_c11 targ)
    target_add_definitions(${targ} "-std=c11")
endmacro(use_c11)

#sets strict
macro(set_strict targ)
    target_add_definitions(${targ} "-Wall -pedantic -Wextra")
endmacro(set_strict)

#sets static
macro(set_static targ)
    target_add_definitions(${targ} "-static")
endmacro(set_static)

macro(link_mthread targ)
    if(CPLUSPLUS_11)
        if(ENABLE_MULTITHREADING)
            target_link_libraries(${targ} pthread)
        endif()
    endif()
endmacro(link_mthread)

#adds optimization flags
macro(add_build_optimizations targ)
    if("${targ}" STREQUAL "release")
        target_add_definitions(${targ} "-O -O3")
    endif()
endmacro(add_build_optimizations)

#adds boost library
macro(add_boost targ)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME ON)
    find_package(Boost REQUIRED COMPONENTS ${BOOST_LIB_COMPONENTS})
    if(Boost_FOUND)
        target_include_directories(${targ} PRIVATE ${Boost_INCLUDE_DIRS})
        link_directories(${Boost_LIBRARY_DIRS})
        target_link_libraries(${targ} ${BOOST_LIB_COMPONENTS_LITERAL})
    else()
        message("FATAL ERROR: boost library not found!")
    endif()
endmacro(add_boost)

#adds wxWidgets library to target
macro(add_wxwidgets_lib targ)
    if(USING_WXWIDGETS_LIB)
        set(wxWidgets_USE_LIBS)
        find_package(wxWidgets)
        if(NOT wxWidgets_FOUND)
            message("wxWidgets libraries could not be located!!")
        else()
            #target_include_directories(${targ} PRIVATE "${wxWidgets_USE_FILE}")
            include("${wxWidgets_USE_FILE}")
            target_link_libraries(${targ} ${wxWidgets_LIBRARIES})
            
            #on linux using GTK:
            target_link_libraries(${targ} libwx_gtk2u_richtext-3.0.so)
        endif()
    endif()
endmacro(add_wxwidgets_lib)

#adds additional libraries
macro(add_additional_libs targ libs)
    foreach(tempf ${libs})
        message("Searching for library " ${tempf})
        find_library(LIBUNIT_TEST_PP_LOCATION add_unittestpp NAMES ${tempf})
        if(NOT LIBUNIT_TEST_PP_LOCATION)
            message("FATAL ERROR: Could not find " ${tempf} "!")
        else()
            message("Found library " ${tempf})
            target_link_libraries(${targ} ${LIBUNIT_TEST_PP_LOCATION})
        endif()
    endforeach()
endmacro(add_additional_libs)

#adds ncurses library
macro(add_ncurses targ)
    set(CURSES_NEED_NCURSES TRUE)
    find_package(Curses 5.9 REQUIRED COMPONENTS ${NCURSES_LIB_COMPONENTS})
    if(CURSES_FOUND)
        target_include_directories(${targ} PRIVATE ${CURSES_INCLUDE_DIR})
        target_link_libraries(${targ} ${NCURSES_LIB_COMPONENTS})
    else()
        message("FATAL ERROR: curses library not found!")
    endif()
endmacro(add_ncurses)

macro(find_dependent_includes targ)

    if(INCLUDE_ALL)
        file(GLOB_RECURSE project_HEADERS "${SOURCE_FOLDER}/*.hpp")

        set(project_INCLUDE_DIRS "")
        foreach(_headerFile ${project_HEADERS})
            get_filename_component(_dir ${_headerFile} PATH)
            list(APPEND project_INCLUDE_DIRS ${_dir})
        endforeach(_headerFile)
        list(REMOVE_DUPLICATES project_INCLUDE_DIRS)
        
        foreach(_include_directory_path ${project_INCLUDE_DIRS})
            target_include_directories(${targ} PRIVATE ${_include_directory_path})
        endforeach(_include_directory_path)
    else()
        target_include_directories(${targ} PRIVATE ${SOURCE_FOLDER})
    endif()

endmacro(find_dependent_includes)

#adds executable and source files
macro(add_files targ)
    file(GLOB_RECURSE CPP_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${SOURCE_FOLDER}/*.cpp" "${SOURCE_FOLDER}/*.hpp")
    add_executable(${targ} ${CPP_SOURCE})
    set_property(TARGET ${targ} PROPERTY FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/bin/${targ})
    find_dependent_includes(${targ})
    file(GLOB_RECURSE CPP "${SOURCE_FOLDER}/*.cpp" "${SOURCE_FOLDER}/*.hpp")
    link_directories(${CPP})
endmacro(add_files)

#adds flags
macro(add_comp_flags targ)
    if(STRICT_COMPILE)
        set_strict(${targ})
    endif()

    if("${targ}" STREQUAL "debug")
        target_add_definitions(${targ} "-g")
    elseif("${targ}" STREQUAL "testing")
        target_add_definitions(${targ} "-g")
    endif()

    if("${targ}" STREQUAL "release")
        add_build_optimizations(${targ})
    endif()

    if(STATIC_COMPILE)
        set_static(${targ})
    endif()

    if(CPLUSPLUS_14)
        use_cplusplus14(${targ})
    endif()

    if(64_BIT_BUILD)
        target_add_definitions(${targ} "-m64")
    else()
        target_add_definitions(${targ} "-m32")
    endif()
endmacro(add_comp_flags)

#creates an executable target with the current configuration.
#Each target has it's different compiler args, and library stuffs.
macro(create_target_build targ)
    add_files(${targ})
    add_comp_flags(${targ})
    
    if("${targ}" STREQUAL "testing")
        target_add_preproc_defs(${targ} "UNIT_TEST_PROG=true")
        if(USING_UNITTESTPP_LIBS)
            add_additional_libs(${targ} libUnitTest++.a)
        endif()
    endif()

    if(USING_ADDITIONAL_LIBS)
        add_additional_libs(${targ} ${ADDITIONAL_LIB_COMPONENTS_LITERAL})
    endif()

    link_mthread(${targ})

    if(USING_NCURSES_LIBRARY)
        add_ncurses(${targ})
    endif()
    
    if(USING_WXWIDGETS_LIB)
        add_wxwidgets_lib(${targ})
    endif()

    if(USING_BOOST_LIBRARY)
        add_boost(${targ})
    endif()
endmacro(create_target_build)

#this is where we start configuration:
cmake_minimum_required(VERSION ${CMAKE_VERSION_USED})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
project(${PROGRAM_NAME})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

create_target_build(release)
create_target_build(debug)
create_target_build(testing)
