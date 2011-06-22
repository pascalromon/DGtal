SET(DGTAL_TESTS_SRC
   testImage
   testImageSpanIterators
   testCheckImageConcept
   )

SET(DGTAL_BENCH_SRC
  testImageContainerBenchmark
  testImageContainerByHashTree
  )

FOREACH(FILE ${DGTAL_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${LIBDGTAL_NAME} ${DGtalLibDependencies})
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)

#Benchmark target
FOREACH(FILE ${DGTAL_BENCH_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${LIBDGTAL_NAME})
  add_custom_target(${FILE}-benchmark COMMAND ${FILE} ">benchmark-${FILE}.txt" )
  ADD_DEPENDENCIES(benchmark ${FILE}-benchmark)
ENDFOREACH(FILE)



#-----------------------
#ITK based tests
#----------------------
IF(ITK_FOUND)
  SET(DGTAL_TESTS_ITK_SRC testITKImage)
ELSE(ITK_FOUND)
  SET(DGTAL_TESTS_ITK_SRC "")
ENDIF(ITK_FOUND)

FOREACH(FILE ${DGTAL_TESTS_ITK_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${LIBDGTAL_NAME} ${DGtalLibDependencies})
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)