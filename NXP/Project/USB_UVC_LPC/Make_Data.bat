::*********************************************************
::* Make data file                                        *
::* 2009-12-21,Mingfeng Xu                                *
::*********************************************************

:: Set base path
set basepath=%cd%\..\..\..

:: create data file
%basepath%\Tools\JPG2Data.exe %basepath%\Pics\test_1.jpg JPG1 > Inc\JGP1_Data.h
%basepath%\Tools\JPG2Data.exe %basepath%\Pics\test_2.jpg JPG2 > Inc\JGP2_Data.h
