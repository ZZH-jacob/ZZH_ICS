/*
 * @Author       : Chivier Humber
 * @Date         : 2021-09-14 21:44:05
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-10-31 15:59:54
 * @Description  : file content
 */
#pragma once

#include <iostream>
#include <fstream>
#include <cstdio>

#include <array>
#include <vector>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>

// Boost library
#include <boost/program_options.hpp>

// Application global variables
extern bool gIsSingleStepMode;//单步模式
extern bool gIsDetailedMode;//细节多步模式
extern std::string gInputFileName;//输入文件名
extern std::string gRegisterStatusFileName;//寄存器名
extern std::string gOutputFileName;//输出文件名
extern int gBeginningAddress;//起始地址