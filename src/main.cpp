#include "mbed.h"

#define XBEE_UART P4_22,P4_23
DigitalOut nDTR(P4_19);
DigitalOut nRTS(P4_21);
DigitalOut nRESET(P4_17);
DigitalOut DIN(P4_22);
RawSerial pc(MBED_UARTUSB);
DigitalOut led_tx(LED1),led_rx(LED2);

int main() {
    pc.baud(115200);
    
    nDTR = 0; 
    nRTS = 1; 
    DIN = 0;
    nRESET = 1;
    wait_ms(1);
    nRESET = 0;
    wait_ms(1);
    nRESET = 1;
    wait_ms(10);

    RawSerial xbee(XBEE_UART);
    xbee.baud(115200);

    xbee.putc(0x0d);        

    while(1) {
        if (xbee.readable()) {
            pc.putc(xbee.getc());
            led_tx = !led_tx;
        }
        if (pc.readable()) {
            xbee.putc(pc.getc());
            led_rx = !led_rx;
        }
    }
}
