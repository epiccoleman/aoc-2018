#include "ChronalClassification.h" 

#include <iostream>

#include <algorithm>
using std::count_if;
using std::find_if;
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

map<int,unordered_set<int> > ChronalClassification::OpcodeClassifier::find_possible_opcode_ids() {
  // check each instruction for validity against each operation in opcodes.
  // store the index of the operation if the instruction validates.
  map<int, unordered_set<int> > possible_ops;
    for(const auto &instruction : instructions){
    for(int opcode_index = 0; opcode_index < opcodes.size(); opcode_index++){
      if(opcodes[opcode_index].validate(instruction)){
        possible_ops[instruction.opcode()].insert(opcode_index);
      }
    }
  }
  return possible_ops;
}

map<int,unordered_set<int> > ChronalClassification::OpcodeClassifier::remove_invalid_ops(map<int,unordered_set<int> > possible_ops_map) {
  // for each opcode index
  for(int i = 0; i < opcodes.size(); i++){
    unordered_set possible_ops = possible_ops_map[i];

    // get just the instructions with opcode i 
    vector<Instruction> instructions_with_code_n;
    std::copy_if(instructions.begin(), instructions.end(), back_inserter(instructions_with_code_n),
                 [i](Instruction instruction){
                   return instruction.opcode() == i;
                 });

    // if a given instruction fails the validation for a given possible operation, remove that operation from the possibilities for this opcode
    for(auto instruction : instructions_with_code_n){
      for(auto op : possible_ops){
        if(!opcodes[op].validate(instruction)){
          possible_ops_map[i].erase(op);
        }
      }
    }
  }
  return possible_ops_map;
}

map<int,int> ChronalClassification::OpcodeClassifier::deduce_ids(map<int,unordered_set<int> > possible_ops_map) {
  map<int, int> known_opcodes;
  // this looks for any code number which has only one possible match
  // this is also a totally unnecessary way to do this, but just look at that shambling horror of a lambda
  function<bool(map<int, unordered_set<int> >)>
    opcodes_with_more_than_one_possibility_exist = [](map<int, unordered_set<int> > p){
      return find_if(p.begin(),
                     p.end(),
                     [](std::pair<int, unordered_set<int> > possibilities){
                          return possibilities.second.size() >= 1;})
             != p.end();
  };

  while(opcodes_with_more_than_one_possibility_exist(possible_ops_map)){
    for (auto kv : possible_ops_map){
      if (kv.second.size() == 1){
        int opcode_index = *kv.second.begin(); //gross but fuck it
        known_opcodes[kv.first] = opcode_index;
      }
    }

    for (auto kv : known_opcodes){
      for (auto &thing : possible_ops_map){
        thing.second.erase(kv.second);
      }
    }
  }
  return known_opcodes;
}

void ChronalClassification::OpcodeClassifier::deduce_opcode_ids(){
  map<int, unordered_set<int> > opcode_possibilities;
  opcode_possibilities = find_possible_opcode_ids();
  opcode_possibilities = remove_invalid_ops(opcode_possibilities);
  opcode_map = deduce_ids(opcode_possibilities);
  std::cerr << "Known Codes:" <<std::endl;
  for (auto kv : opcode_map){
    std::cerr << kv.first << ": " << opcodes[kv.second].name << std::endl;
  }
}

// execute sample program
// vec int register
// for line in program 
// opcode_map[line[0]].operation(reg, line)
