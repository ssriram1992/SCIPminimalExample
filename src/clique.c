#include <stdio.h>

#include "scip/pub_misc.h"
#include "scip/scip.h"
#include "scip/scipdefplugins.h"

int main(){
	// Set up SCIP environment
	SCIP* scip;
	SCIP_CALL (SCIPcreate(&scip));
  SCIP_CALL( SCIPincludeDefaultPlugins(scip) );
	//
	SCIPinfoMessage(scip, NULL, "Hello, World!\n");

	// IP to  be solved is the following
	// max x + y + z s.t.
	//  x + y     <= 1
	//  x +    z  <= 1
	//      y + z <= 1
	//  Optimal objective value is 1
	//  LP relaxation optimum is 1.5

	SCIP_VAR *x, *y, *z;
	// Create the model
	SCIP_CALL(SCIPcreateProbBasic(scip, "clique"));
	// Create the variables
  SCIP_CALL( SCIPcreateVarBasic(scip, &x, "x", 0, 1, -1.0, SCIP_VARTYPE_BINARY) );
  SCIP_CALL( SCIPcreateVarBasic(scip, &y, "y", 0, 1, -1.0, SCIP_VARTYPE_BINARY) );
  SCIP_CALL( SCIPcreateVarBasic(scip, &z, "z", 0, 1, -1.0, SCIP_VARTYPE_BINARY) );
	// Add the variables to the model
   SCIP_CALL( SCIPaddVar(scip, x) );
   SCIP_CALL( SCIPaddVar(scip, y) );
   SCIP_CALL( SCIPaddVar(scip, z) );

	 SCIP_Real coeffs[2]; coeffs[0] = 1; coeffs[1] = 1;

	 // x + y <= 1 constraint
	 {
		 SCIP_VAR* xy[2];
		SCIP_CONS* cons;
		 xy[0] = x;
		 xy[1] = y;
		 SCIP_CALL(SCIPcreateConsBasicLinear(scip, &cons, "xy", 2, xy, coeffs, 0,1));
      SCIP_CALL( SCIPaddCons(scip, cons) );
      SCIP_CALL( SCIPreleaseCons(scip, &cons) );
	 }
	 // x + z <= 1 constraint
	 {
		 SCIP_VAR* xy[2];
			 SCIP_CONS* cons;
		 xy[0] = x;
		 xy[1] = z;
		 SCIP_CALL(SCIPcreateConsBasicLinear(scip, &cons, "xz", 2, xy, coeffs, 0,1));
      SCIP_CALL( SCIPaddCons(scip, cons) );
      SCIP_CALL( SCIPreleaseCons(scip, &cons) );
	 }
	 // y + z <= 1 constraint
	 {
		 SCIP_VAR* xy[2];
			 SCIP_CONS* cons;
		 xy[0] = z;
		 xy[1] = y;
		 SCIP_CALL(SCIPcreateConsBasicLinear(scip, &cons, "yz", 2, xy, coeffs, 0,1));
      SCIP_CALL( SCIPaddCons(scip, cons) );
      SCIP_CALL( SCIPreleaseCons(scip, &cons) );
	 }
	 // Release the variables?
   SCIP_CALL( SCIPreleaseVar(scip, &x) );
   SCIP_CALL( SCIPreleaseVar(scip, &y) );
   SCIP_CALL( SCIPreleaseVar(scip, &z) );
	 
	 // printing the model
   SCIPinfoMessage(scip, NULL, "Original problem:\n");
   SCIP_CALL( SCIPprintOrigProblem(scip, NULL, "cip", FALSE) );

	 // SOlving the model
	 SCIP_CALL( SCIPsolve(scip));
   if( SCIPgetNSols(scip) > 0 )
   {
      SCIPinfoMessage(scip, NULL, "\nSolution:\n");
      SCIP_CALL( SCIPprintSol(scip, SCIPgetBestSol(scip), NULL, FALSE) );
   }

	 // free the memory
   SCIP_CALL( SCIPfree(&scip) );

	return 0;
}
