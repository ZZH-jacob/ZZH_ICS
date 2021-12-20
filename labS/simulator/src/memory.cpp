/*
 * @Author       : Chivier Humber
 * @Date         : 2021-09-15 21:15:24
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-11-23 16:08:51
 * @Description  : file content
 */
#include "common.h"
#include "memory.h"

namespace virtual_machine_nsp {
    void memory_tp::ReadMemoryFromFile(std::string filename, int beginning_address) {
        beginning_address=0x3000;
        std::ifstream fp;
        fp.open(filename);
        int pose=beginning_address;
        char buf[20];
        while(fp>>buf){
            for(int i=0;i<16;i++){
                if(buf[i]=='1') memory[pose]=(memory[pose]<<1)+1;
                else memory[pose]<<=1;
            }
            pose++;
        }
        //zzh
        // Read from the file
        // TO BE DONE
    }

    int16_t memory_tp::GetContent(int address) const {
        return memory[address];
        // get the content
        // TO BE DONE
    }

    int16_t& memory_tp::operator[](int address) {
        return memory[address];
        // get the content
        // TO BE DONE
    }
}; // virtual machine namespace
