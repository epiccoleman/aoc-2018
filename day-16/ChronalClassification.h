#ifndef DAY_16
#define DAY_16

#include <string>
#include <vector>
#include <functional>

// alright, on this one i'm using 'using', sorry google
using std::string;
using std::vector;
using std::function;

namespace ChronalClassification {
  struct Instruction {
    vector<int> before;
    vector<int> instruction;
    vector<int> after;
  };

  class Opcode {
  public:
    typedef function<vector<int>(vector<int>, vector<int>)> Operation;
    Opcode(string name, Operation op);
    bool validate(Instruction instruction);

  private:
    Operation operation;
    string name;
  };

  class OpcodeClassifier {
    vector<Instruction> instructions;
    vector<Opcode> opcodes;

    int count_possible_opcodes(Instruction instruction);
  };

  namespace Opcodes {
    //addr (add register) stores into register C the result of adding register A and register B   .
    static const Opcode ADDR("addr",
                              [](vector<int> input, vector<int> instruction){
                               int A, B, C; // sadly, no destructuring support for vector
                               A = input[1];
                               B = input[2];
                               C = instruction[3];

                               input[C] = A + B;
                               return input;
                              });

    // addi (add immediate) stores into register C the result of adding register A and value B.
    static const Opcode ADDI("addi",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // mulr (multiply register) stores into register C the result of multiplying register A and register B.
    static const Opcode MULR("mulr",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // muli (multiply immediate) stores into register C the result of multiplying register A and value B.
    static const Opcode MULI("muli",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // banr (bitwise AND register) stores into register C the result of the bitwise AND of register A and register B.
    static const Opcode BANR("banr",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // bani (bitwise AND immediate) stores into register C the result of the bitwise AND of register A and value B.
    static const Opcode BANI("bani",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // borr (bitwise OR register) stores into register C the result of the bitwise OR of register A and register B.
    static const Opcode BORR("borr",
                             [](vector<int> input, vector<int> instruction){
                               return vector<int>(0);
                             });
    // bori (bitwise OR immediate) stores into register C the result of the bitwise OR of register A and value B.
    static const Opcode BORI("bori",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // setr (set register) copies the contents of register A into register C. (Input B is ignored.)
    static const Opcode SETR("setr",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // seti (set immediate) stores value A into register C. (Input B is ignored.)
    static const Opcode SETI("seti",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // gtir (greater-than immediate/register) sets register C to 1 if value A is greater than register B. Otherwise, register C is set to 0.
    static const Opcode GTIR("gtir",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // gtri (greater-than register/immediate) sets register C to 1 if register A is greater than value B. Otherwise, register C is set to 0.
    static const Opcode GTRI("gtri",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // gtrr (greater-than register/register) sets register C to 1 if register A is greater than register B. Otherwise, register C is set to 0.
    static const Opcode GTRR("gtrr",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // eqir (equal immediate/register) sets register C to 1 if value A is equal to register B. Otherwise, register C is set to 0.
    static const Opcode EQIR("eqir",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // eqri (equal register/immediate) sets register C to 1 if register A is equal to value B. Otherwise, register C is set to 0.
    static const Opcode EQRI("eqri",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
    // eqrr (equal register/register) sets register C to 1 if register A is equal to register B. Otherwise, register C is set to 0.
    static const Opcode EQRR("eqrr",
                             [](vector<int>, vector<int>){
                               return vector<int>(0);
                             });
  }

}

#endif
