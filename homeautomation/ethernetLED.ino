#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
byte mac[] = {0x70, 0xA2, 0xDA, 0x0A, 0x48, 0xD3 };

// The IP address will be dependent on your local network:
IPAddress ip(192,168,10,99);
IPAddress gateway(192,168,10,1);
IPAddress subnet(255, 255, 255, 0);

// Initialize the Ethernet server library with the port you want to use.
EthernetServer server(5000);
String readString;

int led = 8;
int ledTwo = 9;
int motor = 7;

void setup()
{

pinMode(led, OUTPUT); 
pinMode(ledTwo, OUTPUT);
pinMode(motor, OUTPUT);


  Serial.begin(9600);

  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
  Serial.println("LED Controller Test 1.0");
}






void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)

  {
    Serial.println("new client");

    while (client.connected())
    {
      if (client.available())

      {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100)

        {

          //store characters to string
          readString += c;
          //Serial.print(c);


          Serial.write(c);
          // if you've gotten to the end of the line (received a newline
          // character) and the line is blank, the http request has ended,
          // so you can send a reply
          //if HTTP request has ended
          if (c == '\n') {
            Serial.println(readString); //print to serial monitor for debuging
//--------------------------------------------------------------------------------------------------------
// Needed to Display Site:
client.println("HTTP/1.1 200 OK"); //send new page
            client.println("Content-Type: text/html");
            client.println();
            client.println("<HTML>");
            client.println("<HEAD>");

// what is being Displayed :     
        
            client.println("<TITLE>Home Automation</TITLE>");
             client.println("<center>");
            client.println("</HEAD>");
            client.println("<BODY>");
            client.println("<H1>Granits Home Automation</H1>");
            client.println("<hr />");
            client.println("<center>");

            client.println("<a href=\"/?lighton\"\">Turn On Light</a>");
            client.println("<br />");
            client.println("<br />");
            client.println("<a href=\"/?lightoff\"\">Turn Off Light</a><br /><br />");     
            
            client.println("<a href=\"/?light2on\"\">Turn On Light 2</a>");
            client.println("<br />");
            client.println("<br />");
            client.println("<a href=\"/?light2off\"\">Turn Off Light 2 </a><br /><br />");
            
            client.println("<a href=\"/?light3on\"\">Turn On Motor</a>");
            client.println("<br />");
            client.println("<br />");
            client.println("<a href=\"/?light3off\"\">Turn Off Motor </a><br /><br />");

            client.println("<textarea> </textarea>");

                 

            client.println("</BODY>");
            client.println("</HTML>");

            delay(1);
            //stopping client
            client.stop();

            //-------------------------------------------------
            // LED 1
            if(readString.indexOf("?lighton") >0)//checks for on
            {
              digitalWrite(led, HIGH);    // set pin 8 high
              Serial.println("Led On");
            }
            //LED 2
            else if(readString.indexOf("?light2on") >0)//checks for on
            {
              digitalWrite(ledTwo, HIGH);    // set pin 8 high
              Serial.println("Led2 On");
            }
            else if(readString.indexOf("?light2off") >0)//checks for on
            {
              digitalWrite(ledTwo, LOW);    // set pin 8 high
              Serial.println("Led2 Off");
            }
             // MOTOR 
               else if(readString.indexOf("?light3on") >0)//checks for on
            {
              digitalWrite(motor, HIGH);    // set pin 8 high
              Serial.println("Motor  On");
            }
            else if(readString.indexOf("?light3off") >0)//checks for on
            {
              digitalWrite(motor, LOW);    // set pin 8 high
              Serial.println("Motor Off");
            } 

            
            //AVSLUT LED 1
           else{
              if(readString.indexOf("?lightoff") >0)//checks for off
              {
                digitalWrite(led, LOW);    // set pin 8 low
                Serial.println("Led Off");
              }
            }
            //clearing string for next read
            readString="";

            // give the web browser time to receive the data
            delay(1);
            // close the connection:
            client.stop();
            Serial.println("client disonnected");

          }
        }
      }
    }
  }
}
