#include "ChronalClassification.h"

#include <iostream>
#include <string>
#include <vector>
#include <functional>

// alright, on this one i'm using 'using', sorry google
using std::string;
using std::vector;
using std::function;

namespace ChronalClassification {
  namespace Opcodes {
    //addr (add register) stores into register C the result of adding register A and register B   .
    static const Opcode ADDR("addr",
                              [](vector<int> reg, vector<int> instruction){
                               int A, B, C; // sadly, no destructuring support for vector
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = reg[A] + reg[B];
                               return reg;
                              });

    // addi (add immediate) stores into register C the result of adding register A and value B.
    static const Opcode ADDI("addi",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C; // sadly, no destructuring support for vector
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = reg[A] + B;
                               return reg;
                             });
    // mulr (multiply register) stores into register C the result of multiplying register A and register B.
    static const Opcode MULR("mulr",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = reg[A] * reg[B];
                               return reg;
                             });
    // muli (multiply immediate) stores into register C the result of multiplying register A and value B.
    static const Opcode MULI("muli",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = reg[A] * B;
                               return reg;
                             });
    // banr (bitwise AND register) stores into register C the result of the bitwise AND of register A and register B.
    static const Opcode BANR("banr",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = reg[A] & reg[B];
                               return reg;
                             });
    // bani (bitwise AND immediate) stores into register C the result of the bitwise AND of register A and value B.
    static const Opcode BANI("bani",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = reg[A] & B;
                               return reg;
                             });
    // borr (bitwise OR register) stores into register C the result of the bitwise OR of register A and register B.
    static const Opcode BORR("borr",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = reg[A] | reg[B];
                               return reg;
                             });
    // bori (bitwise OR immediate) stores into register C the result of the bitwise OR of register A and value B.
    static const Opcode BORI("bori",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = reg[A] | B;
                               return reg;
                             });
    // setr (set register) copies the contents of register A into register C. (Input B is ignored.)
    static const Opcode SETR("setr",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = reg[A];
                               return reg;
                             });
    // seti (set immediate) stores value A into register C. (Input B is ignored.)
    static const Opcode SETI("seti",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = A;
                               return reg;
                             });
    // gtir (greater-than immediate/register) sets register C to 1 if value A is greater than register B. Otherwise, register C is set to 0.
    static const Opcode GTIR("gtir",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = (A > reg[B]) ? 1 : 0;
                               return reg;
                             });
    // gtri (greater-than register/immediate) sets register C to 1 if register A is greater than value B. Otherwise, register C is set to 0.
    static const Opcode GTRI("gtri",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = (reg[A] > B) ? 1 : 0;
                               return reg;
                             });
    // gtrr (greater-than register/register) sets register C to 1 if register A is greater than register B. Otherwise, register C is set to 0.
    static const Opcode GTRR("gtrr",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = (reg[A] > reg[B]) ? 1 : 0;
                               return reg;
                             });
    // eqir (equal immediate/register) sets register C to 1 if value A is equal to register B. Otherwise, register C is set to 0.
    static const Opcode EQIR("eqir",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = (A == reg[B]) ? 1 : 0;
;
                               return reg;
                             });
    // eqri (equal register/immediate) sets register C to 1 if register A is equal to value B. Otherwise, register C is set to 0.
    static const Opcode EQRI("eqri",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = (reg[A] == B) ? 1 : 0;
                               return reg;
                             });
    // eqrr (equal register/register) sets register C to 1 if register A is equal to register B. Otherwise, register C is set to 0.
    static const Opcode EQRR("eqrr",
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[1];
                               B = instruction[2];
                               C = instruction[3];

                               reg[C] = (reg[A] == reg[B]) ? 1 : 0;
                               return reg;
                             });

  static const vector<Opcode> OPCODES {
      ADDR,
      ADDI,
      MULR,
      MULI,
      BANR,
      BANI,
      BORR,
      BORI,
      SETR,
      SETI,
      GTIR,
      GTRI,
      GTRR,
      EQIR,
      EQRI,
      EQRR };
  }
}
