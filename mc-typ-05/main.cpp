/* mc-typ-05: ver 1.0 */

#include "mbed.h"
#include <stdio.h>
#include <string>

string MC_ID="0";

Serial mPc(USBTX, USBRX);
Timer mTimer;

AnalogIn inSen1(dp13);
AnalogIn inSen2(dp11);
AnalogIn inSen3(dp10);
AnalogIn inSen4(dp9 );

int mTmMax=10;

string conv_zeroStr(string src ,int width){
    string ret="00000000";
    ret +=src;
    int iNum = ret.length();
    ret = ret.substr(iNum-width);
    return ret;    
}

void proc_start() {
    int iSen  =0;
    int iSen2 =0;
    int iSen3 =0;
    int iSen4 =0;
    float fSen  = inSen1;
    float fSen2 = inSen2;
    float fSen3 = inSen3;
    float fSen4 = inSen4;
    iSen  = int(fSen  * 1000);
    iSen2 = int(fSen2 * 1000);
    iSen3 = int(fSen3 * 1000);
    iSen4 = int(fSen4 * 1000);
    
    char buff[]="0000";
    string sPut="put_dat=";
    sPut += conv_zeroStr(MC_ID ,4);
    sprintf(buff, "%d", iSen);
    sPut +=conv_zeroStr(buff ,4);
    sprintf(buff, "%d", iSen2);
    sPut +=conv_zeroStr(buff ,4);
    sprintf(buff, "%d", iSen3);
    sPut +=conv_zeroStr(buff ,4);
    sprintf(buff, "%d", iSen4);
    sPut +=conv_zeroStr(buff ,4);
    
    mPc.printf("%s\n", sPut.c_str() );
}
    
int main() {
    mTimer.start();
    printf("start mc-typ-05.\n");
    while(1) {
        float sec= mTimer.read();
        if(sec >= mTmMax){
          proc_start();
          mTimer.reset();
        }
    }
}

