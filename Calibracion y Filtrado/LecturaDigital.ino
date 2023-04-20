#include <HX711.h>

#define DOUTD 3 
#define CLKD 2
#define DOUTP 5 
#define CLKP 4

HX711  balanced ;
HX711  balancep ;

void  setup ( )  { 
  Serial . begin ( 2000000 )  ;
  balanced . begin ( DOUTD ,  CLKD ) ; 
  Serial . println ( balanced . read ( ) ) ; 
  balanced . set_scale (1) ;  //The default scale is 1-156433.477
  //balanced . tare ( 1 ) ;   //The current weight is considered Tare.7

  Serial . begin ( 2000000 ) ; 
  balancep . begin ( DOUTP ,  CLKP ) ; 
  Serial . println ( balancep . read ( ) ) ; 
  balancep . set_scale (1) ;  //The default scale is 1-63122.455 
  //balancep . tare ( 1 ) ;   //The current weight is considered Tare.

  //Serial . println ( "Ready to weigh" ) ;
}
void  loop ( )  { 
  Serial . println ( String((balancep . get_units (1))) +","+String((balanced . get_units ( 1 )))+"," + String(millis())) ;//Prints "Lift,Drag,time" 
}
