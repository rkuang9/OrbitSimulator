cmake_minimum_required(VERSION 3.8)

project("OrbitSimulator")
set(CMAKE_CXX_STANDARD 14)
add_compile_definitions(_USE_MATH_DEFINES)

# Determine compiler
#if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	#set(BUILD "msvc-static")
	#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
#elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	#set(BUILD "static-debug")
#endif()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
SET(CMAKE_BUILD_TYPE Release)
set(SRC_FILES "include/simulator_includes.h"
        src/main.cpp
        src/init_universe.cpp
        src/barnes-hut/object.cpp include/barnes-hut/object.hpp
        src/barnes-hut/quadtree.cpp include/barnes-hut/quadtree.hpp
        include/list.hpp
        #src/ui/app.cpp include/ui/app.h
        #src/ui/ui.cpp include/ui/ui.h
        #src/ui/logger.cpp include/ui/logger.h
        src/barnes-hut/node.cpp include/barnes-hut/node.hpp
        src/barnes-hut/quadrant.cpp include/barnes-hut/quadrant.hpp
        src/barnes-hut/point.cpp include/barnes-hut/point.hpp
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin) # compiled executable goes into /bin
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib) # no use yet
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib) # no use yet

# Static linking for STL
set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -static") #-static-libgcc -static-libstdc++  -mwindows

# Location of wxWidgets library
#set(wxWidgets_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/wxWidgets-3.1.5-static-release/${BUILD})

# Request the required wxWidgets libs
#find_package(wxWidgets 3.1 COMPONENTS gl core base OPTIONAL_COMPONENTS net)

set(wxBUILD_USE_STATIC_RUNTIME ON)

# Include the wxWidgets use file to initialize various settings
#include(${wxWidgets_USE_FILE})

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR})

# clang-tidy options taken from CLion
#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,bugprone-argument-comment,bugprone-assert-side-effect,bugprone-bad-signal-to-kill-thread,bugprone-branch-clone,bugprone-copy-constructor-init,bugprone-dangling-handle,bugprone-dynamic-static-initializers,bugprone-fold-init-type,bugprone-forward-declaration-namespace,bugprone-forwarding-reference-overload,bugprone-inaccurate-erase,bugprone-incorrect-roundings,bugprone-integer-division,bugprone-lambda-function-name,bugprone-macro-parentheses,bugprone-macro-repeated-side-effects,bugprone-misplaced-operator-in-strlen-in-alloc,bugprone-misplaced-pointer-arithmetic-in-alloc,bugprone-misplaced-widening-cast,bugprone-move-forwarding-reference,bugprone-multiple-statement-macro,bugprone-no-escape,bugprone-not-null-terminated-result,bugprone-parent-virtual-call,bugprone-posix-return,bugprone-reserved-identifier,bugprone-sizeof-container,bugprone-sizeof-expression,bugprone-spuriously-wake-up-functions,bugprone-string-constructor,bugprone-string-integer-assignment,bugprone-string-literal-with-embedded-nul,bugprone-suspicious-enum-usage,bugprone-suspicious-include,bugprone-suspicious-memset-usage,bugprone-suspicious-missing-comma,bugprone-suspicious-semicolon,bugprone-suspicious-string-compare,bugprone-swapped-arguments,bugprone-terminating-continue,bugprone-throw-keyword-missing,bugprone-too-small-loop-variable,bugprone-undefined-memory-manipulation,bugprone-undelegated-constructor,bugprone-unhandled-self-assignment,bugprone-unused-raii,bugprone-unused-return-value,bugprone-use-after-move,bugprone-virtual-near-miss,cert-dcl21-cpp,cert-dcl58-cpp,cert-err34-c,cert-err52-cpp,cert-err58-cpp,cert-err60-cpp,cert-flp30-c,cert-msc50-cpp,cert-msc51-cpp,cert-str34-c,cppcoreguidelines-interfaces-global-init,cppcoreguidelines-narrowing-conversions,cppcoreguidelines-pro-type-member-init,cppcoreguidelines-pro-type-static-cast-downcast,cppcoreguidelines-slicing,google-default-arguments,google-explicit-constructor,google-runtime-operator,hicpp-exception-baseclass,hicpp-multiway-paths-covered,misc-misplaced-const,misc-new-delete-overloads,misc-no-recursion,misc-non-copyable-objects,misc-throw-by-value-catch-by-reference,misc-unconventional-assign-operator,misc-uniqueptr-reset-release,modernize-avoid-bind,modernize-concat-nested-namespaces,modernize-deprecated-headers,modernize-deprecated-ios-base-aliases,modernize-loop-convert,modernize-make-shared,modernize-make-unique,modernize-pass-by-value,modernize-raw-string-literal,modernize-redundant-void-arg,modernize-replace-auto-ptr,modernize-replace-disallow-copy-and-assign-macro,modernize-replace-random-shuffle,modernize-return-braced-init-list,modernize-shrink-to-fit,modernize-unary-static-assert,modernize-use-auto,modernize-use-bool-literals,modernize-use-emplace,modernize-use-equals-default,modernize-use-equals-delete,modernize-use-nodiscard,modernize-use-noexcept,modernize-use-nullptr,modernize-use-override,modernize-use-transparent-functors,modernize-use-uncaught-exceptions,mpi-buffer-deref,mpi-type-mismatch,openmp-use-default-none,performance-faster-string-find,performance-for-range-copy,performance-implicit-conversion-in-loop,performance-inefficient-algorithm,performance-inefficient-string-concatenation,performance-inefficient-vector-operation,performance-move-const-arg,performance-move-constructor-init,performance-no-automatic-move,performance-noexcept-move-constructor,performance-trivially-destructible,performance-type-promotion-in-math-fn,performance-unnecessary-copy-initialization,performance-unnecessary-value-param,portability-simd-intrinsics,readability-avoid-const-params-in-decls,readability-const-return-type,readability-container-size-empty,readability-convert-member-functions-to-static,readability-delete-null-pointer,readability-deleted-default,readability-inconsistent-declaration-parameter-name,readability-make-member-function-const,readability-misleading-indentation,readability-misplaced-array-index,readability-non-const-parameter,readability-redundant-control-flow,readability-redundant-declaration,readability-redundant-function-ptr-dereference,readability-redundant-smartptr-get,readability-redundant-string-cstr,readability-redundant-string-init,readability-simplify-subscript-expr,readability-static-accessed-through-instance,readability-static-definition-in-anonymous-namespace,readability-string-compare,readability-uniqueptr-delete-release,readability-use-anyofallof)

# Define the build target for the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link required libraries to the executable
#target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})


