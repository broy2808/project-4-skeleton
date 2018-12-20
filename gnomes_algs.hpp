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
// #include <experimental/optional>
#include <optional>



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

  // TODO: implement the exhaustive search algorithm, then delete this
  // comment.
  path best(setting);
  bool isValid=false;
  for(int i=0;i<=max_steps;i++){

    for(long int bits=0;bits<=(pow(2,i)-1);bits++){

     gnomes::step_direction dir;
     path candidate(setting);
     for(int k=0;k<=(i-1);k++){
        int bit= ((bits >> k) & 1);

        if (bit == 1){
          dir=STEP_DIRECTION_RIGHT;
          if(candidate.is_step_valid(dir)==true){
            candidate.add_step(dir);
          }
        }else{
          dir=STEP_DIRECTION_DOWN;
         if(candidate.is_step_valid(dir)==true){
          candidate.add_step(dir);
        }
        }


      }

       if ((isValid==false) or (candidate.total_gold()>best.total_gold())) {
         isValid=true;
         best=candidate;
        }
      }
    }
    std::cout<<" EXS Search BEST: "<<std::endl;
    best.print();
    std::cout<<std::endl;

  return best;

// return path(setting);


}

// Solve the greedy gnomes problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
path greedy_gnomes_dyn_prog(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  // TODO: implement the dynamic programming algorithm, then delete this
  // comment.
path best(setting);



std::vector<std::vector<std::optional<gnomes::path>>> A(setting.rows(), std::vector<std::optional<gnomes::path>>(setting.columns(),path(setting)));
std::optional<gnomes::path> point;
int gold_from_above,gold_from_left,above_step_size,left_step_size;

for(int i=0;i<=(setting.rows()-1);i++){
  for(int j=0;j<=(setting.columns()-1);j++){

        if (setting.get(i,j)==CELL_ROCK){
              A[i][j]==point;
              continue;
         }
      std::optional<gnomes::path> from_above,from_left;


       if((i>0) and (A[i-1][j].has_value())){
          gnomes::step_direction step_direction=STEP_DIRECTION_DOWN;

          if(A[i-1][j].value().is_step_valid(step_direction)==true){

             // a1.add_step(step_direction);
             A[i-1][j].value().add_step(step_direction);
             from_above=A[i-1][j].value();
             gold_from_above=from_above.value().total_gold();
             above_step_size=from_above.value().steps().size();
          }
       }
       if((j>0) and (A[i][j-1].has_value())){
          gnomes::step_direction step_direction=STEP_DIRECTION_RIGHT;

          if(A[i][j-1].value().is_step_valid(step_direction)==true){


             A[i][j-1].value().add_step(step_direction);
             from_left=A[i][j-1].value();
             gold_from_left=from_left.value().total_gold();
             left_step_size=from_left.value().steps().size();
          }
       }


        if((from_above.has_value())&&(from_left.has_value())){
             if(gold_from_left > gold_from_above){
               A[i][j]=from_left.value();
             }else{
               A[i][j]=from_above.value();
              }
         }
         if((from_above.has_value())&&(from_left==point)){
           A[i][j]=from_above.value();
         }
         if((from_left.has_value())&&(from_above==point)){
           A[i][j]=from_left.value();
        }
        if((from_left==point)&&(from_above==point)){


       }




     }
  }
 best = A[0][0].value();
 for(int i=0;i<=(setting.rows()-1);i++){
   for(int j=0;j<=(setting.columns()-1);j++){


     if((A[i][j].has_value()) && (A[i][j].value().total_gold() > best.total_gold())){

       best=A[i][j].value();
     }
   }
  }
std::cout<<" Best : "<<std::endl;
best.print();
return best;
// return path(setting);
}

}
