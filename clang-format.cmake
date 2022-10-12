#My version of clang format cmake file

#Find and set ClangFormat
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/*.[ch]pp)
    set (EXCLUDE_DIR "/build/")
    foreach (TMP_PATH ${ALL_CXX_SOURCE_FILES})
        string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)       
        if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
            list (REMOVE_ITEM ALL_CXX_SOURCE_FILES ${TMP_PATH})
        endif()
    endforeach(TMP_PATH)
    string (REPLACE ";" " " ALL_CXX_SOURCE_FILES_SPACE_SEPARATED "${ALL_CXX_SOURCE_FILES}")
    #Diagnostic message checking that ALL_CXX_SOURCE_FILES not containing build directory
    message(STATUS "Diagnostic message: ${ALL_CXX_SOURCE_FILES_SPACE_SEPARATED}")
    #add_custom_target(format ALL)
    add_custom_target(   
        format     
        COMMAND clang-format
        -i
        -style=LLVM
        ${ALL_CXX_SOURCE_FILES_SPACE_SEPARATED}
    )
endif()
