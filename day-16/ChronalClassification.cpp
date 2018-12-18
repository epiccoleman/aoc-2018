#include "ChronalClassification.h" 

#include <iostream>

#include <algorithm>
using std::count_if;
using std::copy_if;
using std::back_inserter;

ChronalClassification::Opcode::Opcode(string n, Operation op)
  : name(n),
    operation(op)
{}

bool ChronalClassification::Opcode::validate(Instruction instruction) const {
  return instruction.after == operation(instruction.before, instruction.instruction);
}

// bool ChronalClassification::Opcode::operator==(const Opcode& other) {
//   return name == other.name;
// }

void ChronalClassification::OpcodeClassifier::parse_input(vector<int> input) {
  for(int i = 0; i < input.size(); i += 12){
    instructions.push_back(
      Instruction{
        { input[i], input[i+1], input[i+2], input[i+3]},
        { input[i+4], input[i+5], input[i+6], input[i+7]},
        { input[i+8], input[i+9], input[i+10], input[i+11]}
      });
  }
}

int ChronalClassification::OpcodeClassifier::count_possible_opcodes(Instruction instruction) {
  return count_if(opcodes.begin(),
                  opcodes.end(),
                  [instruction](Opcode opcode){
                    return opcode.validate(instruction);
                  });
}

int ChronalClassification::OpcodeClassifier::count_samples_with_three_possible_opcodes() {
  return count_if(instructions.begin(),
                  instructions.end(),
                  [this](Instruction instruction){
                    return this->count_possible_opcodes(instruction) >= 3;
                  });
}

void ChronalClassification::OpcodeClassifier::deduce_opcode_ids(){
  // go through all instructions. find the set of possible opcodes. place possible opcodes for the instruction (id instructions.instruction[0]) into a map
  // iterate through the map. for each id, get the set of all instructions sharing that id. check each of the instructions against each of the possible instructions for that id in the map. eliminate any non-matches.
  // hopefully at the end of this process we have just one possible instruction at each id in the map. if not, we'll have to figure out a new bit.

  //for each instruction, determine which opcodes it could be.
  map<int, unordered_set<int> > numbered_opcodes;
  for(const auto &instruction : instructions){
    for(int i = 0; i < opcodes.size(); i++){
      if(opcodes[i].validate(instruction)){
        numbered_opcodes[instruction.instruction[0]].insert(i);
      }
    }
  }

  // for all instructions with a given n, check all the possible opcodes for n. erase any opcode in possible_ops that fails a validation. (this does only slightly more than fuck all)
  for(int i = 0; i < opcodes.size(); i++){
    // std::cerr << "Attempting to deduce: " << i << std::endl;
    unordered_set possible_ops = numbered_opcodes[i];
    vector<Instruction> instructions_with_code_n;
    // grab instructions matching n
    std::copy_if(instructions.begin(), instructions.end(), back_inserter(instructions_with_code_n),
                 [i](Instruction instruction){
                   return instruction.opcode() == i;
                 });
    // std::cerr << "Instructions: " << instructions_with_code_n.size() << std::endl;
    for(auto instruction : instructions_with_code_n){
      for(auto op : possible_ops){
        if(!opcodes[op].validate(instruction)){
          // std::cerr << "This instruction doesn't validate against " << opcodes[op].name << std::endl;
          // std::cerr << "erasing " << op << std::endl;
          // std::cerr << "size before " << numbered_opcodes[i].size() << std::endl;
          numbered_opcodes[i].erase(op);
          // std::cerr << "size after " << numbered_opcodes[i].size() << std::endl;
        }
      }
    }
  }

  map<int, int> known_opcodes;
  // this looks for any code number which has only one possible match
  for (int i = 0; i < 16; i++){
    for (auto kv : numbered_opcodes){
      if (kv.second.size() == 1){
        int opcode_index = *kv.second.begin(); //gross 
        known_opcodes[kv.first] = opcode_index;
      }
    }

    for (auto kv : known_opcodes){
      for (auto &thing : numbered_opcodes){
        thing.second.erase(kv.second);
      }
    }
  }

  // final output step

  std::cerr << "After proc" <<std::endl;
  for (auto kv : numbered_opcodes){
    std::cerr << "Operation: " << kv.first << std::endl;
    std::cerr << "could be: " << std::endl;
    for (auto n : kv.second) {
      std::cerr << opcodes[n].name << std::endl;
    }
  }

  std::cerr << "Known Codes:" <<std::endl;
  for (auto kv : known_opcodes){
    std::cerr << kv.first << ": " << opcodes[kv.second].name << std::endl;
  }
}

// execute sample program
// vec int register
// for line in program 
// opcode_map[line[0]].operation(reg, line)
