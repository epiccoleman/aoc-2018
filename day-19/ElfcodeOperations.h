#include "Elfcode.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

// alright, on this one i'm using 'using', sorry google
using std::string;
using std::vector;
using std::function;
using std::map;

namespace Elfcode {
  namespace Operations {
   //addr (add register) stores into register C the result of adding register A and register B   .
    static const Operation ADDR =
                              [](vector<int> reg, vector<int> instruction){
                               int A, B, C; // sadly, no destructuring support for vector
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = reg[A] + reg[B];
                               return reg;
                              };

    // addi (add immediate) stores into register C the result of adding register A and value B.
    static const Operation ADDI =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C; // sadly, no destructuring support for vector
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = reg[A] + B;
                               return reg;
                             };
    // mulr (multiply register stores into register C the result of multiplying register A and register B.
    static const Operation MULR =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = reg[A] * reg[B];
                               return reg;
                             };
    // muli (multiply immediate) stores into register C the result of multiplying register A and value B.
    static const Operation MULI =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = reg[A] * B;
                               return reg;
                             };
    // banr (bitwise AND register) stores into register C the result of the bitwise AND of register A and register B.
    static const Operation BANR =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = reg[A] & reg[B];
                               return reg;
                             };
    // bani (bitwise AND immediate) stores into register C the result of the bitwise AND of register A and value B.
    static const Operation BANI =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = reg[A] & B;
                               return reg;
                             };
    // borr (bitwise OR register) stores into register C the result of the bitwise OR of register A and register B.
    static const Operation BORR =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = reg[A] | reg[B];
                               return reg;
                             };
    // bori (bitwise OR immediate) stores into register C the result of the bitwise OR of register A and value B.
    static const Operation BORI =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = reg[A] | B;
                               return reg;
                             };
    // setr (set register) copies the contents of register A into register C. (Input B is ignored.)
    static const Operation SETR =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = reg[A];
                               return reg;
                             };
    // seti (set immediate) stores value A into register C. (Input B is ignored.)
    static const Operation SETI =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = A;
                               return reg;
                             };
    // gtir (greater-than immediate/register) sets register C to 1 if value A is greater than register B. Otherwise, register C is set to 0.
    static const Operation GTIR =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = (A > reg[B]) ? 1 : 0;
                               return reg;
                             };
    // gtri (greater-than register/immediate) sets register C to 1 if register A is greater than value B. Otherwise, register C is set to 0.
    static const Operation GTRI =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = (reg[A] > B) ? 1 : 0;
                               return reg;
                             };
    // gtrr (greater-than register/register) sets register C to 1 if register A is greater than register B. Otherwise, register C is set to 0.
    static const Operation GTRR =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = (reg[A] > reg[B]) ? 1 : 0;
                               return reg;
                             };
    // eqir (equal immediate/register) sets register C to 1 if value A is equal to register B. Otherwise, register C is set to 0.
    static const Operation EQIR =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = (A == reg[B]) ? 1 : 0;
;
                               return reg;
                             };
    // eqri (equal register/immediate) sets register C to 1 if register A is equal to value B. Otherwise, register C is set to 0.
    static const Operation EQRI =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = (reg[A] == B) ? 1 : 0;
                               return reg;
                             };
    // eqrr (equal register/register) sets register C to 1 if register A is equal to register B. Otherwise, register C is set to 0.
    static const Operation EQRR =
                             [](vector<int> reg, vector<int> instruction){
                               int A, B, C;
                               A = instruction[0];
                               B = instruction[1];
                               C = instruction[2];

                               reg[C] = (reg[A] == reg[B]) ? 1 : 0;
                               return reg;
                             };

    static const map<string, Operation> OPCODE_MAP {
      { "addr", ADDR },
      { "addi", ADDI },
      { "mulr", MULR },
      { "muli", MULI },
      { "banr", BANR },
      { "bani", BANI },
      { "borr", BORR },
      { "bori", BORI },
      { "setr", SETR },
      { "seti", SETI },
      { "gtir", GTIR },
      { "gtri", GTRI },
      { "gtrr", GTRR },
      { "eqir", EQIR },
      { "eqri", EQRI },
      { "eqrr", EQRR }};
  }
}
