/*
 * @Author       : Chivier Humber
 * @Date         : 2021-08-30 15:10:31
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-11-23 15:34:30
 * @Description  : file content
 */

#include "assembler.h"

void label_map_tp::AddLabel(const std::string &str, const value_tp &val) {
    labels_.insert(std::make_pair(str, val));
}//用于插入标签表

value_tp label_map_tp::GetValue(const std::string &str) const {
    // User (vAddress, -1) to represent the error case
    if (labels_.find(str) == labels_.end()) {
        // not found
        return value_tp(vAddress, -1);
    } else {
        return labels_.at(str);
    }
}//通过标签表找到其中的值

std::ostream &operator<<(std::ostream &os, const StringType &item) {
    switch (item) {
    case sComment:
        os << "Comment ";
        break;
    case sLabel:
        os << "Label";
        break;
    case sValue:
        os << "Value";
        break;
    case sOpcode:
        os << "Opcode";
        break;
    case sOprand:
        os << "Oprand";
        break;
    default:
        os << "Error";
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const ValueType &val) {
    switch (val) {
    case vAddress:
        os << "Address";
        break;
    case vValue:
        os << "Value";
        break;
    default:
        os << "Error";
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const value_tp &value) {
    if (value.type_ == vValue) {
        os << "[ " << value.type_ << " -- " << value.val_ << " ]";
    } else {
        os << "[ " << value.type_ << " -- " << std::hex << "0x" << value.val_ << " ]";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const label_map_tp &label_map) {
    for (auto item : label_map.labels_) {
        os << "Name: " << item.first << " " << item.second << std::endl;
    }
    return os;
}

int RecognizeNumberValue(std::string s) {
    int out=0;
    int num=0;
    int weight=0;
    std::string::iterator it;
    if(s[0]=='x'||s[0]=='X'){
        for(it=s.end()-1;it>s.begin();it--){
            num=CharToDec(*it);
            if(num==-1) break;
            else{
                out=out+num*pow(16,weight);
                weight++;
            }
        }
        if(s.find("-")!=s.npos) out=-out;
    }//16
    else {
        it=s.end()-1;
        while(CharToDec(*it)!=-1){
            num=CharToDec(*it);
            out=out+num*pow(10,weight);
            weight++;
            it--;
        }
        if(s.find("-")!=s.npos) out=-out;
    }//10
    return out;
    // Convert string s into a number
    // TO BE DONE
}

std::string NumberToAssemble(const int &number) {
     char a[17];
    int b=number;
    for(int i=15;i>=0;i--){
        if((b-floor((double)b/2)*2)==1) a[i]='1';
        else a[i]='0';
        b=floor((double)b/2);
    }
    a[16]='\0';
    return (std::string)a;
    // Convert the number into a 16 bit binary string
    // TO BE DONE
}

std::string NumberToAssemble(const std::string &number) {
    int num=RecognizeNumberValue(number);
        char a[17];
    int b=num;
    for(int i=15;i>=0;i--){
        if((b-floor((double)b/2)*2)==1) a[i]='1';
        else a[i]='0';
        b=floor((double)b/2);
    }
    a[16]='\0';
    return (std::string)a;
    // Convert the number into a 16 bit binary string
    // You might use `RecognizeNumberValue` in this function
    // TO BE DONE
}

std::string ConvertBin2Hex(std::string bin)  {
    int temp=0;
    int flag=0;
    std::string b;
    int size=bin.size();
    int n=size/4;
    if((size-4*n)>0){
        flag=1;
        b[n+1]='\0';
        for(int i=size-4*n-1;i>=0;i--){
            if(bin[i]=='1')  temp+=pow(2,size-4*n-1-i);
        }
        if(temp<=9) b[0]='0'+temp;
            else b[0]='a'+temp-10;
    }
    temp=0;
    b[n]='\0';
    while(n>0){
        for(int i=size-1;i>=size-4;i--){
            if(bin[i]=='1')  temp+=pow(2,size-i-1);
        }
        if(flag==1){
            if(temp<=9) b[n]='0'+temp;
            else b[n]='a'+temp-10;
        }
        else{
            if(temp<=9) b[n-1]='0'+temp;
            else b[n-1]='a'+temp-10;
        }
        n--;
        temp=0;
        size=size-4;
    }
    
    return b;
    // Convert the binary string into a hex string
    // TO BE DONE
}
//处理操作数
std::string assembler::TranslateOprand(int current_address, std::string str, int opcode_length) {//current_address未+1
    // Translate the oprand
    str = Trim(str);
    auto item = label_map.GetValue(str);
    if (!(item.getType() == vAddress && item.getVal() == -1)) {
        std::string out;
        std::string temp;
        out[opcode_length]='\0';
        int offset=item.getVal()-current_address-1;
            temp=NumberToAssemble(offset);
            out=temp.substr(15-opcode_length+1,opcode_length);
            return out;

        // str is a label
        // TO BE DONE
    }
    if (str[0] == 'R') {
        if(str[1]=='0') return "000";
        if(str[1]=='1') return "001";
        if(str[1]=='2') return "010";
        if(str[1]=='3') return "011";
        if(str[1]=='4') return "100";
        if(str[1]=='5') return "101";
        if(str[1]=='6') return "110";
        if(str[1]=='7') return "111";
        // str is a register
        // TO BE DONE
    } else {
        std::string out;
        std::string temp;
        int num=RecognizeNumberValue(str);
        out[opcode_length]='\0';
            temp=NumberToAssemble(num);
            out=temp.substr(15-opcode_length+1,opcode_length);
            return out;
        // str is an immediate number
        // TO BE DONE
    }
}

// TODO: add error line index
int assembler::assemble(std::string input_filename, std::string output_filename) {
    // assemble main function
    // parse program

    // store the original string
    std::vector<std::string> file_content;
    std::vector<std::string> origin_file;
    // store the tag for line
    std::vector<LineStatusType> file_tag;
    std::vector<std::string> file_comment;
    std::vector<int> file_address;
    int orig_address = -1;
    std::string line;

    std::ifstream input_file(input_filename);

    if (input_file.is_open()) {
        // Scan #0:
        // Read file
        // Store comments
        while (std::getline(input_file, line)) {
            // Remove the leading and trailing whitespace
            line = Trim(line);
            if (line.size() == 0) {
                // Empty line
                continue;
            }
            std::string origin_line = line;
            if(line[0]==';'&&line.size()==1){
                continue;
            }
            // Convert `line` into upper case
            // TO BE DONE
            
            // Store comments
            auto comment_position = line.find(";");
            if (comment_position == std::string::npos) {
                // No comments here
                file_content.push_back(line);
                origin_file.push_back(origin_line);
                file_tag.push_back(lPending);
                file_comment.push_back("");
                file_address.push_back(-1);
                continue;
            } else {
                std::string comment_str,content_str;
                comment_str=line.substr(comment_position+1);
                content_str=line.substr(0,comment_position);
                // Split content and comment
                // TO BE DONE
                
                // Delete the leading whitespace and the trailing whitespace
                comment_str = Trim(comment_str);
                content_str = Trim(content_str);
                // Store content and comment separately
                file_content.push_back(content_str);
                origin_file.push_back(origin_line);
                file_comment.push_back(comment_str);
                if (content_str.size() == 0) {
                    // The whole line is a comment
                    file_tag.push_back(lComment);
                } else {
                    file_tag.push_back(lPending);
                }
                file_address.push_back(-1);
            }
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
        // @ Input file read error
        return -1;
    }

    // Scan #1:
    // Scan for the .ORIG & .END pseudo code
    // Scan for jump label, value label, line comments
    int line_address = -1;
    for (int line_index = 0; line_index < file_content.size(); ++line_index) {
        if (file_tag[line_index] == lComment) {
            // This line is comment
            continue;
        }

        auto line = file_content[line_index];

        // * Pseudo Command
        if (line[0] == '.') {
            file_tag[line_index] = lPseudo;
            // This line is a pseudo instruction
            // Only .ORIG & .END are line-pseudo-command
            auto line_stringstream = std::istringstream(line);
            std::string pseudo_command;
            line_stringstream >> pseudo_command;

            if (pseudo_command == ".ORIG") {
                // .ORIG
                std::string orig_value;
                line_stringstream >> orig_value;
                orig_address = RecognizeNumberValue(orig_value);
                if (orig_address == std::numeric_limits<int>::max()) {
                    // @ Error address
                    return -2;
                }
                file_address[line_index] = -1;
                line_address = orig_address;
            } else if (pseudo_command == ".END") {
                // .END
                file_address[line_index] = -1;
                // If set line_address as -1, we can also check if there are programs after .END
                // line_address = -1;
            } else if (pseudo_command == ".STRINGZ") {
                file_address[line_index] = line_address;
                std::string word;
                line_stringstream >> word;
                if (word[0] != '\"' || word[word.size() - 1] != '\"') {
                    // @ Error String format error
                    return -6;
                }
                auto num_temp = word.size() - 1;
                line_address += num_temp;
            } else if (pseudo_command == ".FILL") {
                file_address[line_index] = line_address;
                line_address++;
                // TO BE DONE
            } else if (pseudo_command == ".BLKW") {
                file_address[line_index] = line_address;
                std::string word;
                line_stringstream >> word;
                int n;
                n=RecognizeNumberValue(word);
                line_address+=n;
                // TO BE DONE
            } else {
                // @ Error Unknown Pseudo command
                return -100;
            }

            continue;
        }

        if (line_address == -1) {
            // @ Error Program begins before .ORIG
            return -3;
        }

        file_address[line_index] = line_address;
        line_address++;

        // Split the first word in the line
        auto line_stringstream = std::stringstream(line);
        std::string word;
        line_stringstream >> word;
        if (IsLC3Command(word) != -1 || IsLC3TrapRoutine(word) != -1) {
            file_tag[line_index] = lOperation;
            continue;
            // * This is an operation line
            // TO BE DONE
        }

        // * Label
        // Store the name of the label
        auto label_name = word;
        // Split the second word in the line
        line_stringstream >> word;
        if (IsLC3Command(word) != -1 || IsLC3TrapRoutine(word) != -1 || word == "") {
            file_tag[line_index] = lOperation;
            label_map.AddLabel(label_name, value_tp(vAddress, line_address - 1));
            continue;
            // a label used for jump/branch
            // TO BE DONE
        } else {
            file_tag[line_index] = lPseudo;
            if (word == ".FILL") {
                line_stringstream >> word;
                auto num_temp = RecognizeNumberValue(word);
                if (num_temp == std::numeric_limits<int>::max()) {
                    // @ Error Invalid Number input @ FILL
                    return -4;
                }
                if (num_temp > 65535 || num_temp < -65536) {
                    // @ Error Too large or too small value  @ FILL
                    return -5;
                }
                label_map.AddLabel(label_name, value_tp(vAddress, line_address - 1));
            }
            if (word == ".BLKW") {
                line_stringstream >> word;//string
                auto num_temp = RecognizeNumberValue(word);
                label_map.AddLabel(label_name, value_tp(vAddress, line_address - 1));
                line_address=line_address+num_temp-1;
                // modify label map
                // modify line address
                // TO BE DONE
            }
            if (word == ".STRINGZ") {
                line_stringstream >> word;//string
                label_map.AddLabel(label_name, value_tp(vAddress, line_address - 1));
                line_address=line_address+word.size()-2;
                // modify label map
                // modify line address
                // TO BE DONE
            }
        }
    }

    if (gIsDebugMode) {
        // Some debug information
        std::cout << std::endl;
        std::cout << "Label Map: " << std::endl;
        std::cout << label_map << std::endl;

        for (auto index = 0; index < file_content.size(); ++index) {
            std::cout << std::hex << file_address[index] << " ";
            std::cout << file_content[index] << std::endl;
        }
    }

    // Scan #2:
    // Translate

    // Check output file
    if (output_filename == "") {
        output_filename = input_filename;
        if (output_filename.find(".") == std::string::npos) {
            output_filename = output_filename + ".asm";
        } else {
            output_filename = output_filename.substr(0, output_filename.rfind("."));
            output_filename = output_filename + ".asm";
        }
    }

    std::ofstream output_file;
    // Create the output file
    output_file.open(output_filename);
    if (!output_file) {
        // @ Error at output file
        return -20;
    }

    for (int line_index = 0; line_index < file_content.size(); ++line_index) {
        if (file_address[line_index] == -1 || file_tag[line_index] == lComment) {
            // * This line is not necessary to be translated
            continue;
        }

        auto line = file_content[line_index];
        auto line_stringstream = std::stringstream(line);

        if (gIsDebugMode)
            output_file << std::hex << file_address[line_index] << ": ";
        if (file_tag[line_index] == lPseudo) {
            // Translate pseudo command
            std::string word;
            line_stringstream >> word;
            if (word[0] != '.') {
                // Fetch the second word
                // Eliminate the label
                line_stringstream >> word;
            }

            if (word == ".FILL") {
                std::string number_str;
                line_stringstream >> number_str;
                auto output_line = NumberToAssemble(number_str);
                if (gIsHexMode)
                    output_line = ConvertBin2Hex(output_line);
                output_file << output_line << std::endl;
            } else if (word == ".BLKW") {
                int num=0;
                std::string number_str;
                line_stringstream >> number_str;
                num=RecognizeNumberValue(number_str);
                std::string output_line ="0000000000000000";
                if (gIsHexMode)
                    output_line = ConvertBin2Hex(output_line);
                for(int i=0;i<num;i++){
                    output_file << output_line << std::endl;
                }
                // Fill 0 here
                // TO BE DONE
            } else if (word == ".STRINGZ") {
                int n=0;
                std::string number_str;
                line_stringstream >> number_str;
                n=number_str.size();
                for(int i=1;i<=n-1;i++){
                    int c=number_str[i+1];
                    auto output_line = NumberToAssemble(c);
                    if (gIsHexMode)
                    output_line = ConvertBin2Hex(output_line);
                    output_file << output_line << std::endl;
                }
                // Fill string here
                // TO BE DONE
            }

            continue;
        }

        if (file_tag[line_index] == lOperation) {
            std::string word;
            line_stringstream >> word;
            if (IsLC3Command(word) == -1 && IsLC3TrapRoutine(word) == -1) {
                // Eliminate the label
                line_stringstream >> word;
            }

            std::string result_line = "";
            auto command_tag = IsLC3Command(word);
            auto parameter_str = line.substr(line.find(word) + word.size());
            parameter_str = Trim(parameter_str);
            for(int i=0;i<parameter_str.size();i++){
                if(parameter_str[i]==',') parameter_str[i]=' ';
            }
            // Convert comma into space for splitting
            // TO BE DONE

            auto current_address = file_address[line_index];

            std::vector<std::string> parameter_list;
            auto parameter_stream = std::stringstream(parameter_str);
            while (parameter_stream >> word) {
                parameter_list.push_back(word);
            }
            auto parameter_list_size = parameter_list.size();
            if (command_tag != -1) {
                // This is a LC3 command
                switch (command_tag) {
                case 0:
                    // "ADD"
                    result_line += "0001";
                    if (parameter_list_size != 3) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += TranslateOprand(current_address, parameter_list[0]);
                    result_line += TranslateOprand(current_address, parameter_list[1]);
                    if (parameter_list[2][0] == 'R') {
                        // The third parameter is a register
                        result_line += "000";
                        result_line += TranslateOprand(current_address, parameter_list[2]);
                    } else {
                        // The third parameter is an immediate number
                        result_line += "1";
                        // std::cout << "hi " << parameter_list[2] << std::endl;
                        result_line += TranslateOprand(current_address, parameter_list[2], 5);
                    }
                    break;
                case 1:
                result_line += "0101";
                    if (parameter_list_size != 3) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += TranslateOprand(current_address, parameter_list[0]);
                    result_line += TranslateOprand(current_address, parameter_list[1]);
                    if (parameter_list[2][0] == 'R') {
                        // The third parameter is a register
                        result_line += "000";
                        result_line += TranslateOprand(current_address, parameter_list[2]);
                    } else {
                        // The third parameter is an immediate number
                        result_line += "1";
                        // std::cout << "hi " << parameter_list[2] << std::endl;
                        result_line += TranslateOprand(current_address, parameter_list[2], 5);
                    }
                    // "AND"
                    // TO BE DONE
                     break;
                case 2:
                result_line += "0000";
                    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += "000";
                        result_line += TranslateOprand(current_address, parameter_list[0], 9);
                    // "BR"
                    // TO BE DONE
                     break;
                case 3:
                 result_line += "0000";
                    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += "100";
                        result_line += TranslateOprand(current_address, parameter_list[0], 9);
                    // "BRN"
                    // TO BE DONE
                     break;
                case 4:
                 result_line += "0000";
                    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += "010";
                        result_line += TranslateOprand(current_address, parameter_list[0], 9);
                    // "BRZ"
                    // TO BE DONE
                     break;
                case 5:
                 result_line += "0000";
                    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += "001";
                        result_line += TranslateOprand(current_address, parameter_list[0], 9);
                    // "BRP"
                    // TO BE DONE
                     break;
                case 6:
                 result_line += "0000";
                    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += "110";
                        result_line += TranslateOprand(current_address, parameter_list[0], 9);
                    // "BRNZ"
                    // TO BE DONE
                     break;
                case 7:
                 result_line += "0000";
                    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += "101";
                        result_line += TranslateOprand(current_address, parameter_list[0], 9);
                    // "BRNP"
                    // TO BE DONE
                     break;
                case 8:
                 result_line += "0000";
                    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += "011";
                        result_line += TranslateOprand(current_address, parameter_list[0], 9);
                    // "BRZP"
                    // TO BE DONE
                     break;
                case 9:
                    // "BRNZP"
                    result_line += "0000111";
                    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += TranslateOprand(current_address, parameter_list[0], 9);
                    break;
                case 10:
                result_line +="1100000";
                if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += TranslateOprand(current_address, parameter_list[0]);
                   result_line += "000000";
                    // "JMP"
                    // TO BE DONE
                     break;
                case 11:
                result_line += "01001";
                result_line += TranslateOprand(current_address, parameter_list[0],11);
                    // "JSR"
                    // TO BE DONE
                     break;
                case 12:
                result_line += "0100000";
                result_line += TranslateOprand(current_address, parameter_list[0]);
                result_line += "000000";
                    // "JSRR"
                    // TO BE DONE
                    break;
                case 13:
                result_line += "0010";
                result_line += TranslateOprand(current_address, parameter_list[0]);
                result_line += TranslateOprand(current_address, parameter_list[1],9);
                    // "LD"
                    // TO BE DONE
                     break;
                case 14:
                result_line += "1010";
                result_line += TranslateOprand(current_address, parameter_list[0]);
                result_line += TranslateOprand(current_address, parameter_list[1],9);
                    // "LDI"
                    // TO BE DONE
                     break;
                case 15:
                result_line += "0110";
                result_line += TranslateOprand(current_address, parameter_list[0]);
                result_line += TranslateOprand(current_address, parameter_list[1]);
                result_line += TranslateOprand(current_address, parameter_list[2],6);
                    // "LDR"
                    // TO BE DONE
                     break;
                case 16:
                result_line += "1110";
                result_line += TranslateOprand(current_address, parameter_list[0]);
                result_line += TranslateOprand(current_address, parameter_list[1],9);
                    // "LEA"
                    // TO BE DONE
                     break;
                case 17:
                result_line += "1001";
                    if (parameter_list_size != 2) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += TranslateOprand(current_address, parameter_list[0]);
                    result_line += TranslateOprand(current_address, parameter_list[1]);
                    result_line += "111111";
                    // "NOT"
                    // TO BE DONE
                     break;
                case 18:
                    // RET
                    result_line += "1100000111000000";
                    if (parameter_list_size != 0) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    break;
                case 19:
                    result_line += "1000000000000000";
                    if (parameter_list_size != 0) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    // RTI
                    // TO BE DONE
                     break;
                case 20:
                    // ST
                    result_line += "0011";
                    if (parameter_list_size != 2) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += TranslateOprand(current_address, parameter_list[0]);
                    result_line += TranslateOprand(current_address, parameter_list[1], 9);
                    break;
                case 21:
                 result_line += "1011";
                    if (parameter_list_size != 2) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += TranslateOprand(current_address, parameter_list[0]);
                    result_line += TranslateOprand(current_address, parameter_list[1], 9);
                    // STI
                    // TO BE DONE
                     break;
                case 22:
                    result_line += "0111";
                    if (parameter_list_size != 3) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += TranslateOprand(current_address, parameter_list[0]);
                    result_line += TranslateOprand(current_address, parameter_list[1]);
                    result_line += TranslateOprand(current_address, parameter_list[2], 6);
                    // STR
                    // TO BE DONE
                     break;
                case 23:
                    result_line += "11110000";
                    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    result_line += TranslateOprand(current_address, parameter_list[0],8);
                    // TRAP
                    // TO BE DONE
                     break;
                default:
                    // Unknown opcode
                    // @ Error
                    break;
                }
            } else {
                // This is a trap routine
                command_tag = IsLC3TrapRoutine(word);
                switch (command_tag) {
                    case 0:
                    // x20
                    result_line += "1111000000100000";
                    break;
                    case 1:
                    // x21
                    result_line += "1111000000100001";
                    break;
                    case 2:
                    // x22
                    result_line += "1111000000100010";
                    break;
                    case 3:
                    // x23
                    result_line += "1111000000100011";
                    break;
                    case 4:
                    // x24
                    result_line += "1111000000100100";
                    break;
                    case 5:
                    // x25
                    result_line += "1111000000100101";
                    break;
                    default:
                    // @ Error Unknown command
                    return -50;
                }
            }
            
            if (gIsHexMode)
                result_line = ConvertBin2Hex(result_line);
            output_file << result_line << std::endl;
        }
    }

    // Close the output file
    output_file.close();
    // OK flag
    return 0;
}
