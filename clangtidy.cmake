find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/sources/*.[ch]pp
        ${PROJECT_SOURCE_DIR}/sources/*.[ch]
        ${PROJECT_SOURCE_DIR}/include/*.[h]pp
        ${PROJECT_SOURCE_DIR}/include/*.[h]
    )

    add_custom_target(
        clangtidy
        COMMAND clang-tidy
        ${ALL_CXX_SOURCE_FILES}
        -checks=ccpcoreguidelines-*,fuchsia-*,google-*,cert-*,modernize-use-trailing-return-type,clang-analyzer-*,bugprone-*,concurrency-*,performance-*,portability-*,readability-*,llvm-*,-fuchsia-default-arguments-calls,-fuchsia-trailing-return,-fuchsia-overloaded-operator,-readability-const-return-type,-readability-convert-member-functions-to-static,-readability-avoid-const-params-in-decls,-cert-oop54-cpp
        #--p=c++20
        --
        -I/include
    )
endif()
