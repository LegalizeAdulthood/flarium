cmake_minimum_required(VERSION 3.26)

set(FLARIUM_PROJECT_NAME "Flarium" CACHE STRING "Project name for IDEs")

project("${FLARIUM_PROJECT_NAME}")

set(CMAKE_MFC_FLAG $<$<CONFIG:Debug>:2,1>)
add_executable(Flarium WIN32
    StdAfx.h
    StdAfx.cpp

    Flarium24.h
    Flarium24.cpp

    Flarium24Doc.h
    Flarium24Doc.cpp

    Flarium24View.h
    Flarium24View.cpp

    MainFrm.h
    MainFrm.cpp

    Resource.h

    Affine.cpp
    BGColor.cpp
    Clouds.cpp
    Cmplx.cpp
    Delta_z.cpp
    Dib.cpp
    Equation.cpp
    FDimension.cpp
    Filter_Complete.cpp
    Filters.cpp
    Formulae.cpp
    Formulae2.cpp
    Formulae3.cpp
    Formulae4.cpp
    Formulae5.cpp
    Formulae6.cpp
    Formulae7.cpp
    Fparams.cpp
    gradient.cpp
    lattoof.cpp
    Nthorder.cpp
    OneNum.cpp
    Orient.cpp
    Pattern.cpp
    PrtScale.cpp
    Qparams.cpp
    Two_num.cpp
    Unique.cpp
    Xysize.cpp

    Flarium24.rc
    Flarium24.rc2
    Flarium24Doc.ico
    Toolbar.bmp
)
source_group(Resources REGULAR_EXPRESSION ".*\\.(bmp|ico|rc2)$")
target_compile_definitions(Flarium PUBLIC $<$<CONFIG:Debug>:_AFXDLL> _WIN32_WINNT=_WIN32_WINNT_WIN7)
target_compile_options(Flarium PUBLIC /W3)
target_precompile_headers(Flarium PUBLIC StdAfx.h)
target_link_libraries(Flarium PUBLIC Vfw32.lib)
