#ifndef _PI_CONTROL
#define _PI_CONTROL

#include <systemc.h>

#include "pi_constants.h"

const sc_uint<2> c_idle=0x0;
const sc_uint<2> c_fadr=0x1;
const sc_uint<2> c_nadr=0x2;
const sc_uint<2> c_ldat=0x3;

const sc_uint<3> ack_rdy=0x3;
const sc_uint<3> ack_rdm=0x1;
const sc_uint<3> ack_spl=0x6;

SC_MODULE(pi_control)
{
  sc_in<bool> 		CK;			// external clock
  sc_in<bool> 		RESET_N;	// reset

  sc_in<sc_uint<32>> 	PI_A;		// address
  sc_in<sc_uint<4>> 		PI_OPC;		// operation code
  sc_in<bool> 		PI_READ;	// read operation
  sc_in<bool> 		PI_LOCK;	// lock

  sc_in<bool> 		PI_IREQ0;	// master's request
  sc_in<bool> 		PI_IREQ1;	// master's request
  sc_in<bool> 		PI_IREQ2;	// master's request
  sc_in<bool> 		PI_IREQ3;	// master's request
  sc_in<bool> 		PI_IREQ4;	// master's request
  sc_in<bool> 		PI_IREQ5;	// master's request
  sc_in<bool> 		PI_IREQ6;	// master's request
  sc_in<bool> 		PI_IREQ7;	// master's request

  sc_out<bool> 		PI_GNT0;		// master's grant
  sc_out<bool> 		PI_GNT1;		// master's grant
  sc_out<bool> 		PI_GNT2;		// master's grant
  sc_out<bool> 		PI_GNT3;		// master's grant
  sc_out<bool> 		PI_GNT4;		// master's grant
  sc_out<bool> 		PI_GNT5;		// master's grant
  sc_out<bool> 		PI_GNT6;		// master's grant
  sc_out<bool> 		PI_GNT7;		// master's grant

  sc_out<bool> 		PI_SEL0;		// slave selection
  sc_out<bool> 		PI_SEL1;		// slave selection
  sc_out<bool> 		PI_SEL2;		// slave selection
  sc_out<bool> 		PI_SEL3;		// slave selection
  sc_out<bool> 		PI_SEL4;		// slave selection
  sc_out<bool> 		PI_SEL5;		// slave selection
  sc_out<bool> 		PI_SEL6;		// slave selection
  sc_out<bool> 		PI_SEL7;		// slave selection

  sc_in<sc_uint<3>> 		PI_ACK;		// transfer acknow
  sc_out<bool> 		PI_TOUT;	// timeout

  sc_signal<sc_uint<8>> 	PI_IREQ;	// master's request
  sc_signal<sc_uint<8>> 	PI_GNT;		// master's grant
  sc_signal<sc_uint<8>> 	PI_SEL;		// slave selection

  sc_signal<bool> 	CK_SX;		// internal clk

  sc_signal<sc_uint<8>>	PRIOR_RX;	// priority reg.
  sc_signal<bool> 	WRTPRIO_SX;	// Priority reg. wen.

  sc_signal<bool>		CURPRIO_SX0;	// current priority msk
  sc_signal<bool>		CURPRIO_SX1;	// current priority msk
  sc_signal<bool>		CURPRIO_SX2;	// current priority msk
  sc_signal<bool>		CURPRIO_SX3;	// current priority msk
  sc_signal<bool>		CURPRIO_SX4;	// current priority msk
  sc_signal<bool>		CURPRIO_SX5;	// current priority msk
  sc_signal<bool>		CURPRIO_SX6;	// current priority msk
  sc_signal<bool>		CURPRIO_SX7;	// current priority msk
  sc_signal<sc_uint<8>>	CURPRIO_SX;	// current priority msk

  sc_signal<sc_uint<8>>	REQUEST_SX;	// requests
  sc_signal<sc_uint<8>>	GRANT_SX;	// internal grants
  sc_signal<sc_uint<8>>	DFLMSTR_SX;	// int. default master
  sc_signal<sc_uint<8>>	CMPDFLT_SX;	// def. master request
  sc_signal<bool> 	DFLTRQS_SX;	// def. master request

  sc_signal<sc_uint<8>>	SELECT_SX;	// int. device select

  sc_signal<sc_uint<2>>	C_STAT_RX;	// state register
  sc_signal<sc_uint<8>>	C_NXTS_SX;	// next state

  sc_signal<bool> 	TRANRQS_SX;	// effective transfer
  sc_signal<bool> 	DATARDY_SX;	// data ready
  sc_signal<bool> 	GLBRQST_SX;	// global request

  sc_signal<bool> 	RESET_RX;	// reset register

  SC_CTOR(pi_control)
  {
    SC_METHOD(processPI_IREQ);
    sensitive 
			<< PI_IREQ0 
			<< PI_IREQ1 
			<< PI_IREQ2 
			<< PI_IREQ3 
              
			<< PI_IREQ4 
			<< PI_IREQ5 
			<< PI_IREQ6 
			<< PI_IREQ7;
    SC_METHOD(processCK_SX);
    sensitive 
			<< CK;
    SC_METHOD(processREQUEST_SX);
    sensitive 
			<< PI_IREQ;
    SC_METHOD(processCURPRIO_SX7);
    sensitive 
			<< PRIOR_RX 
			<< REQUEST_SX 
			<< CURPRIO_SX6;
    SC_METHOD(processCURPRIO_SX6);
    sensitive 
			<< PRIOR_RX 
			<< REQUEST_SX 
			<< CURPRIO_SX5;
    SC_METHOD(processCURPRIO_SX5);
    sensitive 
			<< PRIOR_RX 
			<< REQUEST_SX 
			<< CURPRIO_SX4;
    SC_METHOD(processCURPRIO_SX4);
    sensitive 
			<< PRIOR_RX 
			<< REQUEST_SX 
			<< CURPRIO_SX3;
    SC_METHOD(processCURPRIO_SX3);
    sensitive 
			<< PRIOR_RX 
			<< REQUEST_SX 
			<< CURPRIO_SX2;
    SC_METHOD(processCURPRIO_SX2);
    sensitive 
			<< PRIOR_RX 
			<< REQUEST_SX 
			<< CURPRIO_SX1;
    SC_METHOD(processCURPRIO_SX1);
    sensitive 
			<< PRIOR_RX 
			<< REQUEST_SX 
			<< CURPRIO_SX0;
    SC_METHOD(processCURPRIO_SX0);
    sensitive 
			<< PRIOR_RX 
			<< REQUEST_SX 
			<< CURPRIO_SX7;
    SC_METHOD(processCURPRIO_SX);
    sensitive 
			<< CURPRIO_SX0 
			<< CURPRIO_SX1 
			<< CURPRIO_SX2 
			<< CURPRIO_SX3 
			<< CURPRIO_SX4 
			<< CURPRIO_SX5 
			<< CURPRIO_SX6 
			<< CURPRIO_SX7;
    SC_METHOD(processGRANT_SX);
    sensitive 
			<< REQUEST_SX 
			<< CURPRIO_SX;
    SC_METHOD(processDFLMSTR_SX);
    sensitive 
			<< PRIOR_RX;
    SC_METHOD(processGLBRQST_SX);
    sensitive 
			<< REQUEST_SX;
    SC_METHOD(processCMPDFLT_SX);
    sensitive 
			<< DFLMSTR_SX 
			<< REQUEST_SX;
    SC_METHOD(processDFLTRQS_SX);
    sensitive 
			<< CMPDFLT_SX;
    SC_METHOD(processSELECT_SX);
    sensitive 
			<< PI_A;
    SC_METHOD(processC_NXTS_SX);
    sensitive 
			<< RESET_RX 
			<< C_STAT_RX 
			<< GLBRQST_SX 
			<< DATARDY_SX 
			<< DFLTRQS_SX 
			<< PI_LOCK;
    SC_METHOD(processWRTPRIO_SX);
    sensitive 
			<< C_STAT_RX 
			<< GLBRQST_SX 
			<< DATARDY_SX;
    SC_METHOD(processPI_TOUT);
    SC_METHOD(processTRANRQS_SX);
    sensitive 
			<< PI_OPC;
    SC_METHOD(processDATARDY_SX);
    sensitive 
			<< PI_ACK;
    SC_METHOD(processPI_SEL);
    sensitive 
			<< C_STAT_RX 
			<< GLBRQST_SX 
			<< DFLTRQS_SX 
			<< SELECT_SX 
			<< TRANRQS_SX 
			<< DATARDY_SX;
    SC_METHOD(processPI_GNT);
    sensitive 
			<< C_STAT_RX 
			<< GLBRQST_SX 
			<< DFLMSTR_SX 
			<< DATARDY_SX 
              
			<< GLBRQST_SX 
			<< GRANT_SX 
			<< DFLTRQS_SX;
    SC_METHOD(processC_STAT_RX);
    sensitive 
			<< CK.pos();
    SC_METHOD(processPRIOR_RX);
    sensitive 
			<< CK.pos();
    SC_METHOD(processRESET_RX);
    sensitive 
			<< CK.pos();
    SC_METHOD(processGNTS);
    sensitive 
			<< PI_GNT;
    SC_METHOD(processSELS);
    sensitive 
			<< PI_SEL;
  }

  void processPI_IREQ();

// ### ------------------------------------------------------ ###
// #   the controller implements a rolling priority. The	#
// # controller set the lowest priority to the last request	#
// # that has been granted. Then the priority of the position i	#
// # is defined as being higher than the position i+1. Finally	#
// # the position 0 is considered to be the next position of	#
// # most significant position.					#
// #								#
// #   A register is used to save the position of the request	#
// # that has been granted the last time.			#
// ### ------------------------------------------------------ ###

// ### ------------------------------------------------------ ###
// #   internal clock						#
// ### ------------------------------------------------------ ###

  void processCK_SX();

// ### ------------------------------------------------------ ###
// #   requests							#
// ### ------------------------------------------------------ ###

  void processREQUEST_SX();

// ### ------------------------------------------------------ ###
// #   evaluate the priority masks for requests:		#
// #								#
// #   this is based on a propagation algorithm. The priority	#
// # register is filled with ones and only one zero at the	#
// # position of the last request granted by the controller.	#
// # Setting the priority mask of a position to one indicates	#
// # that either: there is a more prior request to this position#
// # or there is not a more prior request but a request is	#
// # present for the current position. The priority mask are	#
// # propagated from the highest to the lowest priority.	#
// #								#
// #    PP : Privious position's priority (= PM i-1)		#
// #    LG : Last granted request (= 0 if granted)		#
// #    RQ : Request						#
// #    PM : Priority mask					#
// #								#
// #         LG  PP  RQ |  PM					#
// #        ------------+-----					#
// #         0   x   x  |  0					#
// #         1   1   x  |  1					#
// #         1   0   1  |  1					#
// ### ------------------------------------------------------ ###

  void processCURPRIO_SX7();

  void processCURPRIO_SX6();

  void processCURPRIO_SX5();

  void processCURPRIO_SX4();

  void processCURPRIO_SX3();

  void processCURPRIO_SX2();

  void processCURPRIO_SX1();

  void processCURPRIO_SX0();

  void processCURPRIO_SX();
    
// ### ------------------------------------------------------ ###
// #   determine the internal grants before setting on the	#
// # Pi-bus:							#
// #								#
// #   a request is granted if there is not a higher priority	#
// # request.							#
// #								#
// #    PP : Privious position's priority			#
// #    LG : Last granted request (= 0 if granted)		#
// #    RQ : Request						#
// #    GT : Grant						#
// #								#
// #         LG  PP  RQ |  GT					#
// #        ------------+-----					#
// #         x   1   x  |  0					#
// #         x   0   0  |  0					#
// #         x   0   1  |  1					#
// ### ------------------------------------------------------ ###

  void processGRANT_SX();

// ### ------------------------------------------------------ ###
// #   define the default master:				#
// # the default master is the one who has the highest priority	#
// ### ------------------------------------------------------ ###

  void processDFLMSTR_SX();

// ### ------------------------------------------------------ ###
// #   check for requests					#
// #      - is there any request				#
// #      - is it from the default master			#
// ### ------------------------------------------------------ ###

  void processGLBRQST_SX();

  void processCMPDFLT_SX();

  void processDFLTRQS_SX();

// ### ------------------------------------------------------ ###
// #   address decoder						#
// ### ------------------------------------------------------ ###

  void processSELECT_SX();

// ### ----------------------------------------------------// ###
// #   bus controller's state machine comprises 4 states:	#
// #								#
// #     - the Idle (c_idle) state: the controller is waiting	#
// #       for a request					#
// #								#
// #     - the First Address (c_fadr) state: a request has been	#
// #       received and the corresponding grant has been sent.	#
// #       The controller is watching the bus and selecting the	#
// #       slaves						#
// #								#
// #     - during all the transfers on the bus except when the	#
// #       master is sending the first address, the controller	#
// #       is in the Next Addresses (c_nadr) state and watching	#
// #       the bus to select the slaves.			#
// #								#
// #     - when the last data is being transfering on the bus	#
// #       the controller is in the Last Data (c_ldat) state.	#
// ### ----------------------------------------------------// ###

// ### ----------------------------------------------------// ###
// #   next controller's state:					#
// #								#
// #     - the controller goes to the Idle (c_idle) state after	#
// #       a reset and remains in this state waiting for a	#
// #       request. Meanwhile, the default master is selected	#
// #       on the bus. When a request is received from a master	#
// #       other than the default master, the controller selects#
// #       the master through the priority mechanism. Then, the	#
// #       controller goes to the First Address (c_fadr) state	#
// #       if the selected master is not the default master or	#
// #       if there is more than one transfer to be performed.	#
// #       Otherwise the controller branches directly to the	#
// #       Last Data (c_ldat) state.				#
// #								#
// #     - in the First Address (c_fadr) state, the controller	#
// #       watches the bus and selects the slaves regarding the	#
// #       address. If only one data had to be transfered, the	#
// #       controllers goes to the Last Data (c_ldat) state.	#
// #       Otherwise, it goes to the Next Addresses (c_nadr)	#
// #       state.						#
// #								#
// #     - in the Next Addresses (c_nadr) state, the controller	#
// #       watches the bus and selects the slaves regarding the	#
// #       address. A slave is selected only if the previous	#
// #       transfer can be terminated. When the last bus	#
// #       transfer is detected, it goes to the Last Data	#
// #       (c_ldat) state.					#
// #								#
// #     - in the Last Data (c_ldat) state, the controller is	#
// #       waiting the last transfer on the bus. During the	#
// #       cycle the last data is being transfered on the bus	#
// #       the controller selects the default master is no	#
// #       request is pending and returns to the Idle (c_idle)	#
// #       state. In the other case, a master is selected	#
// #       regarding the priority mechanism and the controller	#
// #       goes directly to the First Address (c_fadr) state.	#
// ### ----------------------------------------------------// ###

  void processC_NXTS_SX();

// ### ------------------------------------------------------ ###
// #   update the priority register				#
// ### ------------------------------------------------------ ###

  void processWRTPRIO_SX();

// ### ------------------------------------------------------ ###
// #   assign outputs:						#
// # time out							#
// ### ------------------------------------------------------ ###

  void processPI_TOUT();

// ### ------------------------------------------------------ ###
// #   assign outputs:						#
// # select the correct slave regarding the address sent on the	#
// # bus.							#
// ### ------------------------------------------------------ ###

  void processTRANRQS_SX();

  void processDATARDY_SX();

  void processPI_SEL();

// ### ------------------------------------------------------ ###
// #   assign outputs:						#
// # send grants on the Pi-bus : when the controller is in the	#
// # Idle (c_idle) state or leaving the Last Data (c_ldat)	#
// # state, as long as no request has been received, select the	#
// # default master. If a request arrives and it is not from	#
// # the default master set the grants as calculated by the	#
// # priority mechanism. In all other cases no master is	#
// # selected.							#
// ### ------------------------------------------------------ ###

  void processPI_GNT();

// ### ------------------------------------------------------ ###
// #   update the controller's state register
// ### ------------------------------------------------------ ###

  void processC_STAT_RX();
    
// ### ------------------------------------------------------ ###
// #   update priority register					#
// ### ------------------------------------------------------ ###

  void processPRIOR_RX();

// ### ------------------------------------------------------ ###
// #   reset							#
// ### ------------------------------------------------------ ###

  void processRESET_RX();

  void processGNTS();

  void processSELS();
};
#endif
