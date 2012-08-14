/*

  Switch 0.2
  By Waleed Ahmad <xnt14@xceleo.org>

*/
// Import libraries
#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>

// Outputs
const int o1 = 8;
const int o2 = 7;
const int o3 = 6;
const int o4 = 5;

// Output status holders

String o1_s = "0";
String o2_s = "0";
String o3_s = "0";
String o4_s = "0";

String i_buffer = ""; // Input buffer

EthernetServer server = EthernetServer(23); // Define server object running on port 23

void setup() {
  
  // Set output pins to OUTPUT mode.
  pinMode(o1, OUTPUT);
  pinMode(o2, OUTPUT);
  pinMode(o3, OUTPUT);
  pinMode(o4, OUTPUT);
  
  // Network setup
 
  /* Replace with your Ethernet shield's MAC Address.
     It should be on a sticker, under the board.      */
     
  byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  byte ip[] = { 10, 5, 1, 88 };
  
  Ethernet.begin(mac, ip); // Connect to network.

  server.begin(); // Start listening for connections.
  
}

void loop() {
 
 EthernetClient client = server.available(); // Define connected client object.
 
 // When client connects...
 if (client == true) { 
   
   char i_byte = (char)client.read(); // Get sent byte from socket.
   
   i_buffer += i_byte; // Add byte to buffer.
   
   // If line terminated...
   if (i_byte == '\n') { 
     
     // Parse buffer for command...
     switch (i_buffer) {
      
      // Output 1 -> ON
      case "output 1 1\n":
          digitalWrite(o1, HIGH);
          server.print("O1 -> ON\n");
          o1_s = "1";
          break;
      // Output 1 -> OFF
      case "output 1 0\n":
          digitalWrite(o1, LOW);
          server.print("O1 -> OFF\n");
          o1_s = "0";
          break;
          
          // Output 2 -> ON
      case "output 2 1\n":
          digitalWrite(o2, HIGH);
          server.print("O2 -> ON\n");
          o2_s = "1";
          break;
      // Output 2 -> OFF
      case "output 2 0\n":
          digitalWrite(o2, LOW);
          server.print("O2 -> OFF\n");
          o2_s = "0";
          break;
          
      // Output 3 -> ON
      case "output 3 1\n":
          digitalWrite(o3, HIGH);
          server.print("O3-> ON\n");
          o3_s = "1";
          break;
      // Output 3 -> OFF
      case "output 3 0\n":
          digitalWrite(o3, LOW);
          server.print("O3 -> OFF\n");
          o3_s = "0";
          break;
          
      // Output 4 -> ON
      case "output 4 1\n":
          digitalWrite(o4, HIGH);
          server.print("O4 -> ON\n");
          o4_s = "1";
          break;
      // Output 4 -> OFF
      case "output 4 0\n":
          digitalWrite(o4, LOW);
          server.print("O4 -> OFF\n");
          o4_s = "0";
          break;
      
      // Output * -> ON    
      case "output * 1\n":
          digitalWrite(o1, HIGH);
          digitalWrite(o2, HIGH);
          digitalWrite(o3, HIGH);
          digitalWrite(o4, HIGH);
          server.print("O{1,2,3,4} -> ON\n");
          o1_s = "1";
          o2_s = "1";
          o3_s = "1";
          o4_s = "1";
          break;
          
      // Output * -> OFF    
      case "output * 0\n":
          digitalWrite(o1, LOW);
          digitalWrite(o2, LOW);
          digitalWrite(o3, LOW);
          digitalWrite(o4, LOW);
          server.print("O{1,2,3,4} -> OFF\n");
          o1_s = "0";
          o2_s = "0";
          o3_s = "0";
          o4_s = "0";
          break;
          
      // Return status of all outputs
      case "output status\n":
          // Format as JSON string.
          server.print("{ \"o1\" : \"" + o1_s + "\", \"o2\" : \"" + o2_s + "\", \"o3\" : \"" + o3_s + "\", \"o4\" : \"" + o4_s + "\" }\n" );
          break;
     }
     
     i_buffer = ""; // Clear buffer.
     
   }
   
 }
  
}

