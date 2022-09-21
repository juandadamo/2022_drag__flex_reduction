#include <HX711.h>

const  int  DOUTD = A1 ; 
const  int  CLKD = A0 ;
const  int  DOUTP = A3 ; 
const  int  CLKP = A2 ;

HX711  balanced ;
HX711  balancep ;

void  setup ( )  { 
  Serial . begin ( 38400 ) ; 
  balanced . begin ( DOUTD ,  CLKD ) ; 
  Serial . println ( balanced . read ( ) ) ; 
  balanced . set_scale (1) ;  //The default scale is 1-156433.477
  //balanced . tare ( 1 ) ;   //The current weight is considered Tare.

  Serial . begin ( 38400 ) ; 
  balancep . begin ( DOUTP ,  CLKP ) ; 
  Serial . println ( balancep . read ( ) ) ; 
  balancep . set_scale (1) ;  //The default scale is 1-63122.455 
  //balancep . tare ( 1 ) ;   //The current weight is considered Tare.

  delay(1000);
  //Serial . println ( "Ready to weigh" ) ;
}
void  loop ( )  { 
  Serial . println ( String(balancep . get_units ( 1 ),0 ) +","+String(balanced . get_units ( 1 ),0)+"," + String(millis())) ;//Prints "Lift,Drag,time" 
}
