#ifndef MAIN_FM_FM_COMMAND_ADDRESS_DEF_H_
#define MAIN_FM_FM_COMMAND_ADDRESS_DEF_H_

// this is my remote control unit address.
// Write here your address.
// You can press any button on your remote control unit and check it in logs
// you also need to correct defines CONTROLLER_PDU_ARG_*
#define FM_COMMAND_ADDRESS__PDU1 		        0xA5B2
#define FM_COMMAND_ADDRESS__PDU2				0x0B80

#define FM_COMMAND_ADDRESS__MM_STEPPER_STATUS 	0x3726

#define FM_COMMAND_ADDRESS__OM_ALARM        	0x5A22
#define FM_COMMAND_ADDRESS__OM_AIR_STATUS       0x9725
#define FM_COMMAND_ADDRESS__OM_NOISE_DATA       0x7745
#define FM_COMMAND_ADDRESS__OM_CHARGE_STATUS    0x9399

#define FM_COMMAND_ADDRESS__HM_COMMAND			0xB724
#define FM_COMMAND_ADDRESS__HM_CHARGE_STATUS	0xC17A
#define FM_COMMAND_ADDRESS__HM_CHARGE_ERROR		0x2401
#define FM_COMMAND_ADDRESS__HM_BAT_STATUS		0x9924

#endif /* MAIN_FM_FM_COMMAND_ADDRESS_DEF_H_ */
