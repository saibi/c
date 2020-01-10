CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT("project name is cmake-test")

MESSAGE (${CMAKE_PROJECT_NAME})
SET (files main.c foo.c bar.c)
ADD_EXECUTABLE( app.out ${files} )
