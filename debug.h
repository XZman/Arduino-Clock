// debug.h

#ifdef __DEBUG
#define debug_begin(s) Serial.begin(s)
#define debug_print(o) Serial.print(o)
#define debug_println(o) Serial.println(o)
#else
#define debug_begin(s) 
#define debug_print(o) 
#define debug_println(o) 
#endif
