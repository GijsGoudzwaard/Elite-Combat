#include <avr/io.h>
#include "../headers/Infrared.hpp"
#include <Arduino.h>

volatile int counter = 0; // kHz counter within the timer
volatile uint8_t kHz; // kHz variable used to setup the transmission with the correct kHz; Also used for setting time2Counter compare
volatile uint8_t startBit = 1; // 1 = ready to receive start bit; 0 = not ready to receive start bit
volatile uint8_t incomingData = 0;  // 1 = ready to receive data; 0 = not ready to receive data
volatile uint8_t dataPacket = 0x00; // Empty data packet
volatile uint8_t dataPacketInvert = 0xFF; // Empty inverted data packet
volatile uint8_t nrBits = 0; // 0-17 amount of bits in a data packet; 17 = complete data package received 
volatile uint8_t data; // Data variable used in the ISR to be send 
volatile uint8_t invertedData; // Inverted data
volatile uint8_t dataTBS = 63; // dataToBeSend is stored in data, during start bit; This way the data isnt corrupted during a transmission.
volatile uint8_t status = 0x00; // Status data
volatile uint8_t movement = 0x00; // Movement data

/**
 * Infrared Constructor; calling function setupTransmission
 *
 * @param  void
 * @return void
 */
Infrared::Infrared()
{
    kHz = 56;
    setupTransmission(kHz);    
}

/**
 * setupTransmission; containing all other functions for setting up the transmission.
 *
 * @param  uint8_t kHz
 * @return void
 */
void Infrared::setupTransmission(uint8_t kHz)
{
    cli(); // stop interrupts

    initIRTransmittor();
    initIRReceiver();
    initPWMSignal(kHz); 
    
    sei(); // Allow interrupts
}   

/**
 * Initialize IR Transmittor; Setting Phase Correct PWM mode, Clear OC2B on Compare match, no prescaler.
 *
 * @param  void
 * @return void
 */
void Infrared::initIRTransmittor()
{
    DDRD |= (1 << DDD3); // Set PD3 as output

    TCCR2A = (1 << WGM20) | (1 << COM2B1);// Set CTC Mode, Clear OC2B on Compare Match
    TCCR2B = (1 << CS20) | (1 << WGM22); // (1 << FOC2B); // clkT2S/8 prescaler 
    TCNT2  = 0; // Initialize counter value to 0 to start counting from 0

    PORTD |= (1 << PORTD3); // Turn the trasnmitter on for an always on signal
}

/**
 * Initialize IR Receiver; Setting PD2 as input and use a pull-up resistor. Interrupts activated on OCR2A compare
 *
 * @param  void
 * @return void
 */
void Infrared::initIRReceiver()
{
    DDRD &= ~(1 << DDD2); // Making sure PD2 is set as input
    PORTD |= (1 << DDD2); // Set a pull-up resistor on PD2 
    TIMSK2 = (1 << OCIE2A); // Activate interupts on OCR2A compare
}

/**
 * Initialize IR PWM signal; Set the OCR2A compare based on kHz 
 *
 * @param  uint8_t kHz
 * @return void
 */
void Infrared::initPWMSignal(uint8_t kHz)
{
    OCR2A = 0;
    if (kHz == 38)
    {
        OCR2A = 210; // Setting(210) PWM on 38kHz 
    } 
    if (kHz == 56) 
    {
        OCR2A = 138; // Setting(138) PWM on 58kHz // Setting(142) PWM on 56kHz 
    }
    
    OCR2B = OCR2A/3 ; //  33% duty cycle
}

/**
 * Returns last known movement data
 *
 * @param  void
 * @return uint8_t movement
 */
uint8_t Infrared::getMovement()
{
    return movement;
}

/**
 * Returns last known status data
 *
 * @param  void
 * @return uint8_t status
 */
uint8_t Infrared::getStatus()
{
    return status;
}

/**
 * Sets the data for the transmittor
 *
 * @param  uint8_t sendData
 * @return void
 */
void Infrared::sendData(uint8_t sendData)
{
     dataTBS = sendData;
}

/**
 * Returns last known movement data
 *
 * @param  void
 * @return void
 */
void timerDataSend()
{
    if (startBit)
    {
        TCCR2A |= (1 << COM2B1); // Set startbit turning the transmittor on, so the receiver reads a 0
        data = dataTBS; // Data is set ready during startbit operations
        invertedData = dataTBS; // InvertedData is set ready during startbit operations
    } 
    if (!startBit && nrBits <= 8) {
        uint8_t bit = 0x80 & data; // Storing msb and check if it is 0 or 1 
        if (!bit)
        {
            TCCR2A |= (1 << COM2B1); // Send a signal when there is a 1 bit, so the receiver reads a 0
        }
        else 
        {
            TCCR2A &= ~(1 << COM2B1); // Send no signal when there is a 0 bit, so the receiver reads a 1
        }
    }
/** 
 * Sending the inverted data; making the signal in balance with number of 0's and 1's
 * Making it possible to verify incoming data
 */
    if (!startBit && nrBits >= 9) {
        uint8_t bit = 0x80 & data;
        if (!bit)
        {
            TCCR2A &= ~(1 << COM2B1); // Send no signal when there is a 0 bit, so the receiver reads a 1
        }
        else 
        {
            TCCR2A |= (1 << COM2B1); // Send a signal when there is a bit, so the receiver reads a 0
        }
    }
    if (!startBit)
    {
        data = data<<1; // Shifting the msb out
    }
    if (nrBits == 8)
    {
        data = invertedData; // Rewrite data with the same incoming data, which is set during the startbit
    }
}

void timerDataReceive()
{
    if (~(PIND & (1<<PD2)) && startBit) // If there is a 0 (input) on the receiver and startbit is ready to be received
    {
        startBit = 0; // Already received a start bit, turning the expecting start bit off
        incomingData = 1; // Received a start bit, expecting incoming data
    }
    if (incomingData)
    {
        if (nrBits <= 8)
        {
            dataPacket = (dataPacket<<1); // Shifting a 0 in
            dataPacket |= ((PIND & (1<<PD2))>>2); // Writing a 0 or a 1 on the lsb
        }

        if (nrBits >= 9)
        {
            dataPacketInvert = (dataPacketInvert<<1); // Shifting a 0 in 
            // Serial.println(((PIND & (1<<PD2))>>2));
            dataPacketInvert |= ((PIND & (1<<PD2))>>2); // Writing a 0 or a 1 on the lsb
        }
        nrBits = nrBits +1;

        if (nrBits == 17) // 1 startbit + 8 data bits + 8 data bits inverted = complete datapackage received
        { 
            dataPacketInvert ^= 0xFF; // XOR dataPacketInvert for comparisson 
            Serial.print("1e pakket: ");
            Serial.print(dataPacket);
            Serial.print(" - 2e pakket: ");
            Serial.println(dataPacketInvert);
            dataPacketInvert ^= dataPacket; // Compare it with datapackage, if all bits are turned off this means the 2 bytes are equal

            if (dataPacketInvert == 0)
            {
                Serial.println(dataPacket);
                
                /*
                if ((dataPacket&0xC0) == 0x40){ // If the 1st and 2nd bits are 01 this is a data package containing status updates
                    status = dataPacket;
                }
                if ((dataPacket&0xC0) == 0xC0){ // If the 1st and 2nd bits are 11 this is a data package containing movement updates
                    movement = dataPacket;
                    
                } */
            }

            incomingData = 0; // Not ready to receive data
            startBit = 1; // Ready to receive start bit
            nrBits = 0; // Reset nr of bits inside the dataPacket
            dataPacket = 0;
            dataPacketInvert = 0;
        }
    }
}

/**
 * Interrupt on compare OCR2A register; sending and receiving data
 *
 * @param  void
 * @return void
 */
ISR(TIMER2_COMPA_vect)
{       
    if (counter == 12){      
    timerDataReceive(); // Calling the function to check for incoming data
    timerDataSend(); // Calling the function to send data
    counter = 0;
    }
    counter++;
}