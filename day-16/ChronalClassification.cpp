#include "ChronalClassification.h" 

#include <iostream>

#include <algorithm>
using std::count_if;
using std::find_if;
using std::copy_if;
using std::back_inserter;
#include <numeric>
using std::iota;

ChronalClassification::Opcode::Opcode(string n, Operation op)
  : name(n),
    operation(op)
{}

bool ChronalClassification::Opcode::validate(Instruction instruction) const {
  return instruction.after == operation(instruction.before, instruction.instruction);
}

ChronalClassification::OpcodeClassifier::OpcodeClassifier(vector<Opcode> ops, vector<int> input)
  : opcodes(ops)
{
  parse_input(input);
}

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

  unordered_set<int> all_ins;
  for(int i = 0; i < opcodes.size(); i++) all_ins.insert(i);

  map<int, unordered_set<int> > possible_ops;
  for(int i = 0; i < opcodes.size(); i++) possible_ops[i] = all_ins;

  for(const auto &instruction : instructions){
    unordered_set<int> valid_codes;

    for (int i = 0; i < opcodes.size(); i++){
      if(!opcodes[i].validate(instruction)){
        possible_ops[instruction.opcode()].erase(i);
      }
    }
  }
  return possible_ops;
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
  opcode_map = deduce_ids(find_possible_opcode_ids());
  std::cerr << "Known Codes:" <<std::endl;
  for (auto kv : opcode_map){
    std::cerr << kv.first << ": " << opcodes[kv.second].name << std::endl;
  }
}

vector<vector<int> > ChronalClassification::OpcodeClassifier::parse_program(std::vector<int> program) {
  vector<vector<int > > program_lines;
  for(int i = 0; i < program.size(); i += 4){
    program_lines.push_back( //don't be a hero
                           vector<int>
                             { program[i], program[i+1], program[i+2], program[i+3]}
                           );
  }
  return program_lines;
}

vector<int> ChronalClassification::OpcodeClassifier::execute_program(std::vector<int> program) {
  vector<vector<int> > parsed_program = parse_program(program); //lol

  vector<int> reg { 0, 0, 0, 0 };
  
  for(auto instruction : parsed_program){
    int operation = instruction[0];
    const Opcode &opcode = opcodes[opcode_map[operation]];
    reg = opcode.operation(reg, instruction);
  }

  return reg;
}
