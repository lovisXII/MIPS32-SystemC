// ### -------------------------------------------------------------- ###
// # files      : writeback.h                                           #
// # date       : Mar 01 2022                                           #
// # version    : v2.1                                                  #
// #                                                                    #
// # origin     : this description has been developed by CAO-VLSI team  #
// #              at MASI laboratory, University Pierre et Marie Curie  #
// #              4 Place Jussieu 75252 Paris Cedex 05 - France         #
// #                                                                    #
// # descr.     : data flow description of a five stage pipelined Mips  #
// #              R3000 processor                                       #
// #                                                                    #
// # Original                                                           #
// # authors    : D. Hommais, P. Bazargan Sabet                         #
// #                                                                    #
// # System-C                                                           #
// # rewriting  : F. Pecheux                                            #
// #                                                                    #
// # updating   : K. Lastra                                             #
// ### -------------------------------------------------------------- ###

#ifndef _WRITEBACK
#define _WRITEBACK

#include <systemc.h>
#include "constants.h"

SC_MODULE(writeback)
{
	sc_in<sc_uint<25>> 	I_TYPE_RM;		// instruction type
	sc_in<sc_uint<8>> 		OPCOD_RM;		// operation code
	sc_out<bool>			I_WRITE_SW;		// write into register
	sc_out<bool>			WLO_SW;			// low registers write enable
	sc_out<bool>			WHI_SW;			// high registers write enable

	SC_CTOR(writeback):
		I_WRITE_SW("I_WRITE_SW")
	{
		SC_METHOD(processI_WRITE_SW);
		sensitive 
			<< I_TYPE_RM;
		SC_METHOD(processWLO_SW);
		sensitive 
			<< OPCOD_RM;
		SC_METHOD(processWHI_SW);
		sensitive 
			<< OPCOD_RM;
	}

	void processI_WRITE_SW();

  // ### ----------------------------------------------------// ###
  // #   low and high registers' write enable:			#
  // #     - theses registers are modified when a Move into LO or	#
  // #       a Move into HI instruction is executed		#
  // ### ----------------------------------------------------// ###

	void processWLO_SW();

	void processWHI_SW();
};
#endif
