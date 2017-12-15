#include <avr/io.h>
#include "../headers/support/Infrared.hpp"
#include <avr/interrupt.h>
#include <stdlib.h>
#include "../headers/support/globals.hpp"

volatile uint8_t counter = 0; // kHz counter within the timer
volatile uint8_t kHz; // kHz variable used to setup the transmission with the correct kHz; Also used for setting time2Counter compare
volatile uint8_t startBit = 1; // 1 = ready to receive start bit; 0 = not ready to receive start bit
volatile uint8_t incomingData = 0;  // 1 = ready to receive data; 0 = not ready to receive data
volatile uint8_t dataPacket = 0x00; // Empty data packet
volatile uint8_t dataPacketInvert = 0xFF; // Empty inverted data packet
volatile uint8_t nrBits = 0; // 0-17 amount of bits in a data packet; 17 = complete data package received 
volatile uint8_t data; // Data variable used in the ISR to be send 
volatile uint8_t invertedData; // Inverted data
volatile uint8_t dataTBS = 0x00; // dataToBeSend is stored in data, during start bit; This way the data isnt corrupted during a transmission.
volatile uint8_t status = 0x00; // Status data
volatile uint8_t movement = 0x00; // Movement data
volatile uint8_t sendStartBit = 1;
volatile uint8_t nrSendBits = 0;
volatile uint8_t i = 0;
volatile uint8_t set_rand = 0;
volatile uint8_t arena;

/**
 * Infrared Constructor; calling function setupTransmission
 *
 * @param  void
 * @return void
 */
Infrared::Infrared()
{
  kHz = 38; 
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

  TCCR2A = (1 << WGM20) | (1 << COM2B1);// Set PWM Phase Correct mode, Clear OC2B on Compare Match
  TCCR2B = (1 << CS20) | (1 << WGM22); // clkT2S/8 prescaler
  TCNT2 = 0; // Initialize counter value to 0 to start counting from 0

  PORTD |= (1 << PORTD3); // Turn the trasnmitter on for an always on signal
}

/**
 * Initialize IR Receiver; Setting PC2 as input and use a pull-up resistor. Interrupts activated on OCR2A compare
 *
 * @param  void
 * @return void
 */
void Infrared::initIRReceiver()
{
  DDRC &= ~(1 << DDC2); // Making sure PC2 is set as input
  PORTC |= (1 << DDC2); // Set a pull-up resistor on PC2
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
  if (kHz == 38) {
    OCR2A = 210; // Setting(210) PWM on 38kHz
  }
  if (kHz == 57) {
    OCR2A = 140; // Setting(140) PWM on 57kHz
  }

  OCR2B = OCR2A / 3; // 33% duty cycle
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
 * Returns known kHz
 *
 * @param  void
 * @return uint8_t kHz
 */
uint8_t Infrared::getKhz()
{
  return kHz;
}

/**
 * Returns random arena
 *
 * @param  void
 * @return uint8_t arena
 */
uint8_t Infrared::getArena()
{
  return arena;
}

/**
 * Set random arena
 *
 * @param  void
 * @return uint8_t status
 */
void Infrared::setArena(uint8_t randArena)
{
  arena = randArena;
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
  if (sendStartBit) {
    TCCR2A |= (1 << COM2B1); // Set startbit turning the transmittor on, so the receiver reads a 0
    data = dataTBS; // Data is set ready during startbit operations
    //invertedData = ~dataTBS; // InvertedData is set ready during startbit operations
    // Out commented, to make 0 a 255.255 number even in inverted to turn the signals off when there is no dataTBS.
    if (dataTBS == 0) {
      invertedData = dataTBS;
    } else {
      invertedData = ~dataTBS; // InvertedData is set ready during startbit operations
    }


    sendStartBit = 0;
  }

  if ((!sendStartBit) && nrSendBits >= 1) {
    uint8_t bit = 0x80 & data; // Storing msb and check if it is 0 or 1
    if (bit) {
      TCCR2A |= (1 << COM2B1); // Send a signal when there is a 1 bit, so the receiver reads a 0
    } else {
      TCCR2A &= ~(1 << COM2B1); // Send no signal when there is a 0 bit, so the receiver reads a 1
    }
  }

  if (!sendStartBit && nrSendBits >= 1) {
    data = data << 1; // Shifting the msb out
  }

  nrSendBits++;

  if (nrSendBits == 9) {
    data = invertedData; // Rewrite data with the same incoming data, which is set during the startbit
  }

  if (nrSendBits == 18) // 1 start bit, 2*8 data bits, 1 stop bit
  {
    TCCR2A &= ~(1 << COM2B1); // Stop bit
    sendStartBit = 1;
    nrSendBits = 0;
  }
}

/**
 * receives data from opponent
 * 
 * @return void
 */
void timerDataReceive()
{
  if ((!(PINC & (1 << PC2))) &&
      startBit) // If there is a 0 (input) on the receiver and startbit is ready to be received
  {
    startBit = 0; // Received a start bit, turning 'expecting start bit' off
    incomingData = 1; // Received a start bit, turning 'expecting incoming data' on
    // Serial.print((PINC & (1<<PC2))>>2);
    // Serial.print(" ");
  }
  if (incomingData) {
    if (nrBits >= 1 && nrBits <= 8) {
      // Serial.print((PINC & (1<<PC2))>>2);
      dataPacket = (dataPacket << 1); // Shifting a 0 in
      dataPacket |= ((PINC & (1 << PC2)) >> 2); // Writing a 0 or a 1 on the lsb
    }

    // if (nrBits == 8)
    // {
    //     Serial.print(" ");
    // }
    if (nrBits >= 9) {
      // Serial.print((PINC & (1<<PC2))>>2);
      dataPacketInvert = (dataPacketInvert << 1); // Shifting a 0 in
      dataPacketInvert |= ((PINC & (1 << PC2)) >> 2); // Writing a 0 or a 1 on the lsb
    }
    nrBits = nrBits + 1;

    if (nrBits == 17) // 1 startbit + 8 data bits + 8 data bits inverted = complete datapackage received
    {
      // Serial.print(" Pakket 1: ");
      // Serial.print(dataPacket);
      // Serial.print(" Pakket 2: ");
      // Serial.println(dataPacketInvert);

      dataPacket ^= 0xFF; // XOR dataPacket for comparisson
      dataPacketInvert ^= dataPacket; // Compare it with both packages, if all bits are turned off this means the 2 bytes are equal

      if (dataPacketInvert == 0) {
        //    Serial.println(dataPacket);
        if ((dataPacket & 0x80) == 0x80) {
          arena = dataPacket & 0x3F;
        }

        if ((dataPacket & 0xC0) == 0x40) { // If the 1st and 2nd bits are 01 this is a data package containing status updates
          status = dataPacket;
        }
        if ((dataPacket & 0xC0) == 0xC0) { // If the 1st and 2nd bits are 11 this is a data package containing movement updates
          movement = dataPacket;

        }
      }

      incomingData = 0; // Not ready to receive data
      startBit = 1; // Ready to receive start bit
      nrBits = 0; // Reset nr of bits inside the dataPacket
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
  if (counter == kHz * 2) {
    timerDataReceive(); // Calling the function to check for incoming data
    // timerDataSend(); // Calling the function to send data
    if (i >= 17) // 17
    {
      timerDataSend(); // Calling the function to send data
    }
    counter = 0;
    i++;
    if (i == 35) // 34
    {
    Serial.println(freeRam());

      i = 0;
      // Serial.println((PIND & (1 << PD2))>>2);
      // Serial.println(dataTBS);
    }

    if (!set_rand && i == 34) // Wait for everything to settle then read the floating analog pin to setup a srand
    {
      Randomseed rseed;
      rseed.setup_seed();
      dataTBS = rand() % 64 + 1; // setup dataTBS for the selfcheck
      set_rand = 1; // srand has been set
    }
  }
  counter++;
}