//------------------------------------------------------------------------------------------------------------------------------
// Samuel Williams
// SWWilliams@lbl.gov
// Lawrence Berkeley National Lab
//------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
//------------------------------------------------------------------------------------------------------------------------------
typedef struct {
  int num_ranks;	// total number of MPI ranks for MPI_COMM_WORLD
  int my_rank;		// my MPI rank for MPI_COMM_WORLD
  int       num_levels;	// depth of the v-cycle
  level_type ** levels;	// array of pointers to levels

  struct {
    uint64_t MGBuild; // total time spent building the coefficients...
    uint64_t MGSolve; // total time spent in MGSolve
  }cycles;
  int MGSolves_performed;
} mg_type;


//------------------------------------------------------------------------------------------------------------------------------
void  MGBuild(mg_type *all_grids, level_type *fine_grid, double a, double b, int minCoarseGridDim);
void  MGSolve(mg_type *all_grids, int u_id, int F_id, double a, double b, double desired_mg_norm);
void FMGSolve(mg_type *all_grids, int u_id, int F_id, double a, double b, double desired_mg_norm);
void MGPrintTiming(mg_type *all_grids);
void MGResetTimers(mg_type *all_grids);
//------------------------------------------------------------------------------------------------------------------------------
