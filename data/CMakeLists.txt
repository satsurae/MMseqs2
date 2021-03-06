find_program(XXD_EXECUTABLE xxd)
if(NOT XXD_EXECUTABLE)
    message(FATAL_ERROR "xxd not found in path. It is usually contained in your distributions vim-common package!")
endif()

find_program(SED_EXECUTABLE sed)
if(NOT SED_EXECUTABLE)
    message(FATAL_ERROR "sed not found in path!")
endif()

set(COMPILED_RESOURCES
        assembler.sh
        blastp.sh
        blastpgp.sh
        linclust.sh
        clustering.sh
        cascaded_clustering.sh
        update_clustering.sh
        searchtargetprofile.sh
        blosum30.out
        blosum35.out
        blosum40.out
        blosum45.out
        blosum50.out
        blosum55.out
        blosum60.out
        blosum62.out
        blosum65.out
        blosum70.out
        blosum75.out
        blosum80.out
        blosum85.out
        blosum90.out
        blosum95.out
        blosum100.out
        CovSeqidQscPercMinDiag.out
        CovSeqidQscPercMinDiagTargetCov.out
        )

set(GENERATED_OUTPUT_HEADERS "")
FOREACH(INPUT_FILE ${COMPILED_RESOURCES})
    get_filename_component(INPUT_FILE_NAME ${INPUT_FILE} NAME)
    set(OUTPUT_FILE ${PROJECT_SOURCE_DIR}/src/generatedfiles/${INPUT_FILE_NAME}.h)
    message("-- Compile ${INPUT_FILE_NAME} to ${OUTPUT_FILE}")
    add_custom_command(OUTPUT ${OUTPUT_FILE}
            COMMAND ${XXD_EXECUTABLE} -i ${INPUT_FILE_NAME} ${OUTPUT_FILE}
            COMMAND ${SED_EXECUTABLE} 's!unsigned char!static const unsigned char!' < ${OUTPUT_FILE} > ${OUTPUT_FILE}.tmp
            COMMAND mv -f ${OUTPUT_FILE}.tmp ${OUTPUT_FILE}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/data
            MAIN_DEPENDENCY ${INPUT_FILE_NAME})
    set_source_files_properties(${OUTPUT_FILE} PROPERTIES GENERATED TRUE)
    list(APPEND GENERATED_OUTPUT_HEADERS "${OUTPUT_FILE}")
ENDFOREACH()

add_custom_target(generated ALL DEPENDS ${GENERATED_OUTPUT_HEADERS})
