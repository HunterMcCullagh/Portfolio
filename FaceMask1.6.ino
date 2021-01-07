#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_NeoPixel.h>
#include <FaceMask.h>



int i,j,k = 0;
FaceMask mask(i,j,k);
  
void setup()
{
  mask.maskSetup();
}


void loop()
{
  mask.talk();
}
