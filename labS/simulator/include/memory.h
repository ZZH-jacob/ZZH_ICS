/*
 * @Author       : Chivier Humber
 * @Date         : 2021-09-15 21:15:30
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-09-22 20:02:31
 * @Description  : file content
 */
#include "common.h"

namespace virtual_machine_nsp {//内存单元函数空间
const int kInstructionLength = 16;//内存大小为16bits

inline int16_t TranslateInstruction(std::string &line) {//翻译指令（16bits的有符号数），将16位的字符串翻译为int
    // TODO: translate hex mode
    int16_t result = 0;
    if (line.size() == kInstructionLength) {
        for (int index = 0; index < kInstructionLength; ++index) {
            result = (result << 1) | (line[index] & 1);
        }
    }
    return result;
}

const int kVirtualMachineMemorySize = 0xFFFF;//内存的地址大小

class memory_tp {//定义了一个类——内存
    private:
    int16_t memory[kVirtualMachineMemorySize];//内存的地址（不可查看）

    public:
    memory_tp() {
        memset(memory, 0, sizeof(int16_t) * kVirtualMachineMemorySize);//初始化内存全为0
    }
    // Managements
    void ReadMemoryFromFile(std::string filename, int beginning_address=0x3000);//读取文件内存函数
    int16_t GetContent(int address) const;//获取地址的内容
    int16_t& operator[](int address);//操作
};

}; // virtual machine nsp