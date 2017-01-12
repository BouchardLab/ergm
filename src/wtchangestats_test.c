#include"wtchangestats_test.h"

WtD_CHANGESTAT_FN(d_test_abs_sum_minus_5){
  double sum = *(double *)mtp->storage;
  ZERO_ALL_CHANGESTATS();
  EXEC_THROUGH_TOGGLES({
    CHANGE_STAT[0] -= fabs(sum-5);
    sum += NEWWT-OLDWT;
    CHANGE_STAT[0] += fabs(sum-5);
    });
}

WtU_CHANGESTAT_FN(u_test_abs_sum_minus_5){
  INIT_STORAGE(double, sum, {
      *sum = 0;
      EXEC_THROUGH_NET_EDGES(tail, e1, head, y, {
	  *sum+=y;
	  head=head; e1=e1; // Prevent a compiler warning.
	});
    });

  EXEC_THROUGH_TOGGLES({
      *sum += NEWWT-OLDWT;
    });
}

WtS_CHANGESTAT_FN(s_test_abs_sum_minus_5){
  // Storage uninitialized: compute from scratch.
  if(!mtp->storage){
    double sum = 0;
    EXEC_THROUGH_NET_EDGES(tail, e1, head, y, {
	sum+=y;
	head=head; e1=e1; // Prevent a compiler warning.
      });
    CHANGE_STAT[0] = fabs((long int)sum-5);
  }else{ // Storage initialized: use it.
    CHANGE_STAT[0] = fabs(*(double *)mtp->storage-5);
  }
}

WtD_CHANGESTAT_FN(d_test_abs_sum_minus_5_no_s){d_test_abs_sum_minus_5(ntoggles, tails, heads, weights, mtp, nwp);}
WtU_CHANGESTAT_FN(u_test_abs_sum_minus_5_no_s){u_test_abs_sum_minus_5(ntoggles, tails, heads, weights, mtp, nwp);}
