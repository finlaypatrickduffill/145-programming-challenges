
  int noteon_messages; /* total number of note on messages in the file */
  int noteoff_messages; /* total number of note off messages in the file */
  int keypressure_messages; /* total number of notekeypressure messages in the file... */
  int controllerchange_messages; /* etc. */
  int programchange_messages;
  int channelchange_messages;
  int channelpressure_messages;
  int pitchbend_messages;
  
  // status bytes in 0xFx are individiually labelled.
  int sysexclusive_messages;
  int songposition_messages;
  int songselect_messages;
  int busselect_messages;
  int tunerequest_messages;
  int eos_messages;
  int timingtick_messages;
  int startsong_messages;
  int continuesong_messages;
  int stopsong_messages;
  int activesensing_messages;
  int sysreset_messages;
  
  char *message_inst[5]; /* messages can be up to 5 bytes long */
  
  char exitkey;

typedef struct mid_data {
	
  int msgstreamlen;
  int msg_stream;
	
  int noteon_messages; /* total number of note on messages in the file */
  int noteoff_messages; /* total number of note off messages in the file */
  int keypressure_messages; /* total number of notekeypressure messages in the file... */
  int controllerchange_messages; /* etc. */
  int programchange_messages;
  int channelchange_messages;
  int channelpressure_messages;
  int pitchbend_messages;
  
  // status bytes in 0xFx are individiually labelled.
  int sysexclusive_messages;
  int songposition_messages;
  int songselect_messages;
  int busselect_messages;
  int tunerequest_messages;
  int eos_messages;
  int timingtick_messages;
  int startsong_messages;
  int continuesong_messages;
  int stopsong_messages;
  int activesensing_messages;
  int sysreset_messages;
  
  char *message_inst[5]; /* messages can be up to 5 bytes long */
  
  char exitkey;
} mdata;

int parse = 0;

void putmid(char *midi_trackdata) {
  


}