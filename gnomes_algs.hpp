///////////////////////////////////////////////////////////////////////////////
// gnomes_algs.hpp
//
// Algorithms that solve the greedy gnomes problem.
//
// All of the TODO sections for this project reside in this file.
//
// This file builds on gnomes_types.hpp, so you should familiarize yourself
// with that file before working on this file.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>

#include "gnomes_types.hpp"

namespace gnomes {

// Solve the greedy gnomes problem for the given grid, using an exhaustive
// search algorithm.
//
// This algorithm is expected to run in exponential time, so the grid's
// width+height must be small enough to fit in a 64-bit int; this is enforced
// with an assertion.
//
// The grid must be non-empty.
path greedy_gnomes_exhaustive(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  // Compute maximum path length, and check that it is legal.
  const size_t max_steps = setting.rows() + setting.columns() - 2;
  assert(max_steps < 64);

  path best(setting);
 
  std::bitset<63> bits;
  
    for(int a = 1; a < max_steps; a++) {
          bits = 0;
          for(int c = 0; c <= pow(2,a)-1; c++) {
                path tem(setting);
                for(int b = 0; b < a; b++) {
                    if(bits[b] == 0) {
                        if(tem.is_step_valid(STEP_DIRECTION_RIGHT)) {
                            tem.add_step(STEP_DIRECTION_RIGHT);
                        }
                    }
                    else if(bits[b] == 1){
                        if(tem.is_step_valid(STEP_DIRECTION_DOWN)) {
                            tem.add_step(STEP_DIRECTION_DOWN);
                        }
                    }
                }
            
            if(tem.total_gold() > best.total_gold()) {
                  best = tem;
            }
            int bits_int = bits.to_ullong();
            bits = bits.to.ulong() + 1;
            
          }
    }
  
  return best;
}

// Solve the greedy gnomes problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
path greedy_gnomes_dyn_prog(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  path best(setting);
  std::vector<path> paths;
  std::vector<path> sol;
  std::vector<path> end;
  paths.push_back(best);
  
  for(int a = 0; a < setting.rows() + setting.columns() - 1; a++) {
      for(int i = 0; i < paths.size(); i ++) {
          int row = paths[i].final_row();
            if(row == setting.rows() - 1 && paths[i].is_step_valid(STEP_DIRECTION_RIGHT) == false) {
              end.push_back(path[i]);
            }
            else if( row == settings.rows() - 1) {
              end.push_back(paths[i]);
            }
            else {
               path current_right = paths[i];
               path current_down = paths[i];
                  if( current_right.is_step_valid(STEP_DIRECTION_RIGHT)) {
                      current_right.add_step(STEP_DIRECTION_RIGHT);
                      sol.push_back(current_right);
                  }
                  if( current_down.is_step_valid(STEP_DIRECTION_DOWN)) {
                      current_down.add_step(STEP_DIRECTION_DOWN);
                      sol.push_back(current_down);
                  }
            }
        std::cout << a << std::endl;
        paths = sol;
        sol.clear();
        
      }
      for( int i = 0; i < end.size(); i++) {
          if( end[i].total_gold() > best.total_gold()){
              best = end[i];
          }
      }
      return best;
}

}
