::*********************************************************
::* Make data file                                        *
::* 2009-12-21,Mingfeng Xu                                *
::*********************************************************

:: Set base path
set basepath=%cd%\..\..\..

:: create data file
%basepath%\Tools\JPG2Data.exe %basepath%\Pics\test_1.jpg JPG > Inc\JGP_Data.h
