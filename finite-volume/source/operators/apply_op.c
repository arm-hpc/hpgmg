//------------------------------------------------------------------------------------------------------------------------------
// Samuel Williams
// SWWilliams@lbl.gov
// Lawrence Berkeley National Lab
//------------------------------------------------------------------------------------------------------------------------------
void apply_op(level_type * level, int Ax_id, int x_id, double a, double b){  // y=Ax
  // exchange the boundary of x in preparation for Ax
  exchange_boundary(level,x_id,STENCIL_IS_STAR_SHAPED);
          apply_BCs(level,x_id);

  // now do Ax proper...
  uint64_t _timeStart = CycleTime();
  int box;

  #pragma omp parallel for private(box) OMP_THREAD_ACROSS_BOXES(level->concurrent_boxes)
  for(box=0;box<level->num_my_boxes;box++){
    int i,j,k,s;
    int jStride = level->my_boxes[box].jStride;
    int kStride = level->my_boxes[box].kStride;
    int  ghosts = level->my_boxes[box].ghosts;
    int     dim = level->my_boxes[box].dim;
    double h2inv = 1.0/(level->h*level->h);
    const double * __restrict__ x      = level->my_boxes[box].vectors[         x_id] + ghosts*(1+jStride+kStride); // i.e. [0] = first non ghost zone point
          double * __restrict__ Ax     = level->my_boxes[box].vectors[        Ax_id] + ghosts*(1+jStride+kStride); 
    const double * __restrict__ alpha  = level->my_boxes[box].vectors[VECTOR_ALPHA ] + ghosts*(1+jStride+kStride);
    const double * __restrict__ beta_i = level->my_boxes[box].vectors[VECTOR_BETA_I] + ghosts*(1+jStride+kStride);
    const double * __restrict__ beta_j = level->my_boxes[box].vectors[VECTOR_BETA_J] + ghosts*(1+jStride+kStride);
    const double * __restrict__ beta_k = level->my_boxes[box].vectors[VECTOR_BETA_K] + ghosts*(1+jStride+kStride);
    const double * __restrict__  valid = level->my_boxes[box].vectors[VECTOR_VALID ] + ghosts*(1+jStride+kStride);

    #pragma omp parallel for private(k,j,i) OMP_THREAD_WITHIN_A_BOX(level->threads_per_box)
    for(k=0;k<dim;k++){
    for(j=0;j<dim;j++){
    for(i=0;i<dim;i++){
      int ijk = i + j*jStride + k*kStride;
      Ax[ijk] = apply_op_ijk(x);
    }}}
  }
  level->cycles.apply_op += (uint64_t)(CycleTime()-_timeStart);
}
//------------------------------------------------------------------------------------------------------------------------------
