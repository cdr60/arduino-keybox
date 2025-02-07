/***************************************************
  ETHERNET ARDUINO SHIELD WITH SDCARD
  ATTENTION :
  LES 2 NE PEUVENT PAS FONCTIONNER EN MEME TEMPS !
  CS DE SDCARD = 4
  CS D'ETHERNET = 10
  METTRE CES 2 PINS EN OUTPUT
  METTRE LE PIN DE LA FONCTION A UTILISER A LOW, L'AUTRE A HIGH A CHAQUE FOIS
  TESTS LED :
  ROUGE = 27,25,23 
  VERTE = 26,24,22
  35,34 = TEST LECTEUR SD
  33,32 = TEST FICHIER PARAML / CARTE SD
  31,30 = ETHERNET OK
  CHECK I2C STATUS 
  LED OK = 28,30,32,34,36,38,40,42
  LED KO = 29,31,33,35,37,39,41,43
  MCP : GPAXX = IN (0..7) , GPBXX = OUT (8..15)
****************************************************/


uint16_t  impulseduration=100;

 bool startloop =0;
 byte led_init_ko[] = {27,25,23};
 byte led_init_ok[] = {26,24,22};

byte led_mcp_ko[] = {28,30,32,34,36,38,40,42};
byte led_mcp_ok[] = {29,31,33,35,37,39,41,43};


 //Most Arduino shields
#define ETHERCSPIN 10
//MKR ETH shield   
//#define ETHERCSPIN 5
//Teensy 2.0
//#define ETHERCSPIN 0   
//Teensy++ 2.0
//#define ETHERCSPIN 20 
//ESP8266 with Adafruit Featherwing Ethernet
//#define ETHERCSPIN 15  
//ESP32 with Adafruit Featherwing Ethernet
//#define ETHERCSPIN 33 

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
// forcage possible par fichier ini
byte mac[] = {  0x00, 0x12, 0x34, 0x56, 0x78, 0x9A  };
//port TCPIP forçable par fichier ini
uint16_t port = 4925;

#include <Adafruit_MCP23X17.h>
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include <IniFile.h>
#include <Wire.h>

// change this to match your SD shield or module;
// Default SPI on Uno and Nano: pin 10
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// MKRZero SD: SDCARD_SS_PIN

#define SDCARDCSPIN 4

/************************/
EthernetServer server(23); //port 23 changé plus tard dans le code

/*************************************/
/* Fichier INI                       */
const char *paramfilename = "/PARAM.INI";

/**************************************/
/* LISTE MCP                        */
struct MCPINFO
{
  Adafruit_MCP23X17 mcp;
  uint8_t address;
};
/*8 MCP,  actifs ou pas*/
MCPINFO mcps[]
{
  {Adafruit_MCP23X17(), 0x00},
  {Adafruit_MCP23X17(), 0x00},
  {Adafruit_MCP23X17(), 0x00},
  {Adafruit_MCP23X17(), 0x00},
  {Adafruit_MCP23X17(), 0x00},
  {Adafruit_MCP23X17(), 0x00},
  {Adafruit_MCP23X17(), 0x00},
  {Adafruit_MCP23X17(), 0x00}
};
/**************************************/


/*Gestion erreur fichier SDCARD*/
void printErrorMessage(uint8_t e, bool eol = true)
{
  switch (e) {
  case IniFile::errorNoError:
    Serial.print("no error");
    break;
  case IniFile::errorFileNotFound:
    Serial.print("file not found");
    break;
  case IniFile::errorFileNotOpen:
    Serial.print("file not open");
    break;
  case IniFile::errorBufferTooSmall:
    Serial.print("buffer too small");
    break;
  case IniFile::errorSeekError:
    Serial.print("seek error");
    break;
  case IniFile::errorSectionNotFound:
    Serial.print("section not found");
    break;
  case IniFile::errorKeyNotFound:
    Serial.print("key not found");
    break;
  case IniFile::errorEndOfFile:
    Serial.print("end of file");
    break;
  case IniFile::errorUnknownError:
    Serial.print("unknown error");
    break;
  default:
    Serial.print("unknown error value");
    break;
  }
  if (eol)
    Serial.println();
}

/**********************************************/
/*conversion string hex du fichier ini en entier*/
/**********************************************/
int StrToHex(char instr[])
{
  return (int) strtol(instr, 0, 16);
}

void SDCARD_Check()
{
  digitalWrite(ETHERCSPIN, HIGH); 
  digitalWrite(SDCARDCSPIN, LOW);
  Sd2Card card;
  SdVolume volume;
  SdFile root;

  Serial.print("\nInitializing SD card...");
  if (!card.init(SPI_HALF_SPEED, SDCARDCSPIN)) 
  {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    digitalWrite(led_init_ok[0], LOW); 
    digitalWrite(led_init_ko[0], HIGH); 
    while (1) {delay(10);}
  } 
  else 
  {
    Serial.println("Wiring is correct and a card is present.");
  }
   // print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (card.type()) 
  {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }
  if (!volume.init(card)) 
  {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    digitalWrite(led_init_ok[0], LOW); 
    digitalWrite(led_init_ko[0], HIGH); 
   while (1) {delay(10);}
  }
  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());
  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();
  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);
  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);
  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);
  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  root.close();
  digitalWrite(led_init_ok[0], HIGH); 
  digitalWrite(led_init_ko[0], LOW); 

}

void Read_IniParam()
{
  const size_t bufferLen = 80;
  char buffer[bufferLen];

  SPI.begin();
  if (!SD.begin(SDCARDCSPIN))
  {
      Serial.println("SD.begin() failed");
      digitalWrite(led_init_ok[1], LOW); 
      digitalWrite(led_init_ko[1], HIGH); 
      while (1);
  }

  IniFile ini(paramfilename);
  if (!ini.open()) 
  {
    Serial.print("Ini file ");
    Serial.print(paramfilename);
    Serial.println(" does not exist");
    // Cannot do anything else
    digitalWrite(led_init_ok[1], LOW); 
    digitalWrite(led_init_ko[1], HIGH); 
     while (1) {delay(10);}

  }
  Serial.println("Ini file exists");
  // Check the file is valid. This can be used to warn if any lines
  // are longer than the buffer.
  if (!ini.validate(buffer, bufferLen)) 
  {
    Serial.print("ini file ");
    Serial.print(ini.getFilename());
    Serial.print(" not valid: ");
    printErrorMessage(ini.getError());
    // Cannot do anything else
    digitalWrite(led_init_ok[1], LOW); 
    digitalWrite(led_init_ko[1], HIGH); 
    while (1) {delay(10);}

  }
  // Browse through all sections and print contents:
  IniFileState state;
  char sectName[bufferLen];
  Serial.println();

  while (ini.browseSections(sectName, bufferLen, state)) 
  {
    /*****************************************/
    if (strcmp(sectName,"network")==0)
    {
        Serial.println();
        Serial.println(sectName);
        if (ini.getValue(sectName, "mac", buffer, bufferLen)) 
        { 
          Serial.print(" mac ");
          Serial.print(buffer);
          Serial.print(" ");
          byte i=0;
          while (i<16)
          {
            String s="0x";
            //Serial.println(s);
            s+=buffer[i];
            //Serial.println(s);
            s+=buffer[i+1];
            //Serial.println(s);

            int s_len = s.length() + 1; 
            char c_array[s_len];
            s.toCharArray(c_array, s_len);
            byte n=i/3;
            mac[n]=StrToHex(c_array);
            //Serial.println(StrToHex(c_array),HEX);
            i=i+3;
          }
          Serial.print(" -- ");
        } else
          Serial.print(" mac nothing  -- ");


        if (ini.getValue(sectName, "port", buffer, bufferLen)) 
        { 
          Serial.print(" port ");
          uint16_t auxport=atol(buffer);
          if ((auxport>1000) and (auxport<65353)) port=auxport;
          else Serial.print(" port incorrect : min 1001, max 65355 ");
          Serial.print(port);
          Serial.print(" -- ");
        } else
        {
         Serial.print(" port nothing --  default value : ");  
         Serial.print(port);
        }

    }
    /*****************************************/
    if (strcmp(sectName,"timer")==0)
    {
        Serial.println();
        Serial.println(sectName);
        if (ini.getValue(sectName, "impulse", buffer, bufferLen)) 
        { 
          Serial.print(" impulse ");
          uint16_t auximpulse=atol(buffer);
          if ((auximpulse>=20) and (auximpulse<=65535)) impulseduration=auximpulse;
          else Serial.print(" impulse incorrect : min 20, max 65535 ");
          Serial.print(impulseduration);
          Serial.print(" -- ");
        } else
        {
         Serial.print(" impulse nothing --  default value : ");  
         Serial.print(impulseduration);
        }
    }
    /*****************************************/
    if (strcmp(sectName,"MCP2307-00")==0)
    {
      Serial.println();
      Serial.println(sectName);

      if (ini.getValue(sectName, "addr", buffer, bufferLen)) 
      { 
        Serial.print(" addr ");
        //Serial.print(buffer);
        //Serial.print(" in int ");
        mcps[0].address=StrToHex(buffer);
        Serial.print(mcps[0].address,HEX);
        Serial.print("  -- ");
      } else
        Serial.print(", addr nothing -- ");
     }
    /*****************************************/

    if (strcmp(sectName,"MCP2307-01")==0)
    {
      Serial.println();
      Serial.println(sectName);

      if (ini.getValue(sectName, "addr", buffer, bufferLen)) 
      { 
        Serial.print(" addr ");
        //Serial.print(buffer);
        //Serial.print(" in int ");
        mcps[1].address=StrToHex(buffer);
        Serial.print(mcps[1].address,HEX);
        Serial.print("  -- ");
      } else
        Serial.print(", addr nothing -- ");
     }     
    /*****************************************/

    if (strcmp(sectName,"MCP2307-02")==0)
    {
      Serial.println();
      Serial.println(sectName);

      if (ini.getValue(sectName, "addr", buffer, bufferLen)) 
      { 
        Serial.print(" addr ");
        //Serial.print(buffer);
        //Serial.print(" in int ");
        mcps[2].address=StrToHex(buffer);
        Serial.print(mcps[2].address,HEX);
        Serial.print("  -- ");
      } else
        Serial.print(", addr nothing -- ");
     }     
    /*****************************************/

    if (strcmp(sectName,"MCP2307-03")==0)
    {
      Serial.println();
      Serial.println(sectName);

      if (ini.getValue(sectName, "addr", buffer, bufferLen)) 
      { 
        Serial.print(" addr ");
        //Serial.print(buffer);
        //Serial.print(" in int ");
        mcps[3].address=StrToHex(buffer);
        Serial.print(mcps[3].address,HEX);
        Serial.print("  -- ");
      } else
        Serial.print(", addr nothing -- ");
     }     
    /*****************************************/


    if (strcmp(sectName,"MCP2307-04")==0)
    {
      Serial.println();
      Serial.println(sectName);

      if (ini.getValue(sectName, "addr", buffer, bufferLen)) 
      { 
        Serial.print(" addr ");
        //Serial.print(buffer);
        //Serial.print(" in int ");
        mcps[4].address=StrToHex(buffer);
        Serial.print(mcps[4].address,HEX);
        Serial.print("  -- ");
      } else
        Serial.print(", addr nothing -- ");
     }     
    /*****************************************/


    if (strcmp(sectName,"MCP2307-05")==0)
    {
      Serial.println();
      Serial.println(sectName);

      if (ini.getValue(sectName, "addr", buffer, bufferLen)) 
      { 
        Serial.print(" addr ");
        //Serial.print(buffer);
        //Serial.print(" in int ");
        mcps[5].address=StrToHex(buffer);
        Serial.print(mcps[5].address,HEX);
        Serial.print("  -- ");
      } else
        Serial.print(", addr nothing -- ");
     }     
    /*****************************************/

    if (strcmp(sectName,"MCP2307-06")==0)
    {
      Serial.println();
      Serial.println(sectName);

      if (ini.getValue(sectName, "addr", buffer, bufferLen)) 
      { 
        Serial.print(" addr ");
        //Serial.print(buffer);
        //Serial.print(" in int ");
        mcps[6].address=StrToHex(buffer);
        Serial.print(mcps[6].address,HEX);
        Serial.print("  -- ");
      } else
        Serial.print(", addr nothing -- ");
     }     
    /*****************************************/

    if (strcmp(sectName,"MCP2307-07")==0)
    {
      Serial.println();
      Serial.println(sectName);

      if (ini.getValue(sectName, "addr", buffer, bufferLen)) 
      { 
        Serial.print(" addr ");
        //Serial.print(buffer);
        //Serial.print(" in int ");
        mcps[7].address=StrToHex(buffer);
        Serial.print(mcps[7].address,HEX);
        Serial.print("  -- ");
      } else
        Serial.print(", addr nothing -- ");
     }     
    /*****************************************/
  }

  // finished!
  Serial.println();
  printErrorMessage(ini.getError());
  SD.end();
  digitalWrite(led_init_ok[1], HIGH); 
  digitalWrite(led_init_ko[1], LOW);
}
/*******************************************************************************/
void printmac(byte smac[])
{
// print
    for (int i=0; i<6; i++) 
  {
      if (smac[i]<10) 
      {
        Serial.print(0,HEX);
        Serial.print(smac[i],HEX);
      }
      else 
      {
        Serial.print(smac[i],HEX);
      }
      if (i<5) {Serial.print(":"); } else {Serial.println(); }
  }  
}
/*******************************************************************************/

void Ethernet_Setup()
{
  digitalWrite(ETHERCSPIN, LOW); 
  digitalWrite(SDCARDCSPIN, HIGH);

  digitalWrite(led_init_ok[2], LOW); 
  digitalWrite(led_init_ko[2], HIGH); 

  Ethernet.init(ETHERCSPIN);
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP with MAC Address :");
  printmac(mac);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP ");

    if (Ethernet.hardwareStatus() == EthernetNoHardware) 
    {

      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while(1);
    } 
    else if (Ethernet.linkStatus() == LinkOFF) 
    {
      Serial.println("Ethernet cable is not connected.");
      while(1);
    }

    digitalWrite(led_init_ok[2], LOW); 
    digitalWrite(led_init_ko[2], HIGH); 
    // no point in carrying on, so do nothing forevermore:
    while (true) 
    {
      delay(1);
    }

  }

  Serial.print("My MAC address : ");
  printmac(mac);   
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  Serial.print("My DNS IP address: ");
  Serial.println(Ethernet.dnsServerIP());
  Serial.print("My Gateway IP address: ");
  Serial.println(Ethernet.gatewayIP());
  
  digitalWrite(led_init_ok[2], HIGH); 
  digitalWrite(led_init_ko[2], LOW); 
}

/***********************************************/
void Check_MCP()
{
    Serial.println("Checking ans Setting UP MCP :");
    Wire.begin();
    for (byte i=0; i<8;i++)
    {
      digitalWrite(led_mcp_ko[i],HIGH);
      digitalWrite(led_mcp_ok[i],LOW);

      if (mcps[i].address==0) digitalWrite(led_mcp_ko[i],LOW);
      else
      {
          Wire.beginTransmission(mcps[i].address);
          if (Wire.endTransmission () == 0)
          {
            Serial.print ("MCP Found address: ");
            Serial.print (mcps[i].address, DEC);
            Serial.print (" (0x");
            Serial.print (mcps[i].address, HEX);
            Serial.println (")");
            digitalWrite(led_mcp_ko[i],LOW);
            digitalWrite(led_mcp_ok[i],HIGH);
          }
          else 
          {
            Serial.print ("NO MCP at address: ");
            Serial.print (mcps[i].address, DEC);
            Serial.print (" (0x");
            Serial.print (mcps[i].address, HEX);
            Serial.println (")");
            mcps[i].address=0x00;
          }
          delay(100);
      }
  }
  Wire.end();

  /***************************/
  /*Setting UP               */
  for (byte i=0; i<8;i++)
  {
    mcps[i].mcp.begin_I2C(mcps[i].address);
    /* GPAXX = INPUT */
    for (byte k=0; k<8;k++) { mcps[i].mcp.pinMode(k, INPUT_PULLUP ); }
    /* GPBXX = OUTPUT */
    for (byte k=8; k<16;k++) { mcps[i].mcp.pinMode(k, OUTPUT);  mcps[i].mcp.digitalWrite(k,LOW);}
  }


}

/******************************/
byte powbyte(byte x, byte y)
{
  byte val=x;
  for(byte z=0;z<=y;z++)
  {
    if(z==0)
      val=1;
    else
      val=val*x;
  }
  return val;
}
/******************************/

void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) 
  {

    ; // wait for serial port to connect. Needed for native USB port only

  }
  pinMode(ETHERCSPIN, OUTPUT);    
  pinMode(SDCARDCSPIN, OUTPUT); 
  /*TESTS LED*/
  byte delai=1000;
  for (byte i=0; i<3; i++) 
  {
    pinMode(led_init_ok[i], OUTPUT); 
    pinMode(led_init_ko[i], OUTPUT); 
    digitalWrite(led_init_ko[i],HIGH);
    digitalWrite(led_init_ok[i],HIGH);
  }
  delay(delai);

    for (byte i=0; i<3; i++) 
  {
    digitalWrite(led_init_ko[i],LOW);
    digitalWrite(led_init_ok[i],LOW);
  }
  delay(delai);

  for (byte i=0; i<8; i++)
  {
    pinMode(led_mcp_ko[i], OUTPUT); 
    pinMode(led_mcp_ok[i], OUTPUT); 
    digitalWrite(led_mcp_ko[i],HIGH);
    digitalWrite(led_mcp_ok[i],HIGH);
  }
  delay(delai);
  for (byte i=0; i<8; i++)
  {
    digitalWrite(led_mcp_ko[i],LOW);
    digitalWrite(led_mcp_ok[i],LOW);
  }

  SDCARD_Check();
  Read_IniParam();
  Ethernet_Setup();
  Check_MCP();

  Serial.print("Démarrage du service tcp sur le port ");
  Serial.println(port);
  server = EthernetServer(port);
  server.begin();

}

/**********************************/
/* Cas renouvellement de bail     */
/**********************************/
void Ethernetmaintain()
{
switch (Ethernet.maintain()) 
  {
    case 1:
      //renewed fail
      Serial.println("Error: renewed fail");
      break;
    case 2:
      //renewed success
      Serial.println("Renewed success");
      //print your local IP address:
      Serial.print("My IP address: ");
      Serial.println(Ethernet.localIP());
      break;
    case 3:
      //rebind fail
      Serial.println("Error: rebind fail");
      break;
    case 4:
      //rebind success
      Serial.println("Rebind success");
      //print your local IP address:
      Serial.print("My IP address: ");
      Serial.println(Ethernet.localIP());
      break;

    default:
      //nothing happened
      break;
  }
}

/*********************************************/
/* Liberer une clé                           */ 
/*********************************************/
void FreeKey(byte cmd1, byte cmd2, byte num_key)
{
  byte num_key_in_mcp=num_key % 8;
  byte num_mcp=(num_key-num_key_in_mcp) / 8;
  if (mcps[num_mcp].address==0) 
  {
    Serial.print("Pas de MCP pour la clé ");
    Serial.println(num_key);
    return;
  }
  Serial.print("Ecriture MCP 0x");   Serial.print(mcps[num_mcp].address, HEX); Serial.println(" : ");
  Serial.print("Clé interne "); Serial.println(num_key_in_mcp);
  Serial.print("Pin interne "); Serial.println(8+num_key_in_mcp);

  /*activation sortie*/
  mcps[num_mcp].mcp.digitalWrite(8+num_key_in_mcp,HIGH);
  /*délais avant retour status*/
  delay(100);
  /*envoie statut*/
  SendStatusKey(cmd1,cmd2);
  /*si délaisimpusltion > 100, complément de délais avant fin impulsion*/
  if (impulseduration>100) delay(impulseduration-100);
  mcps[num_mcp].mcp.digitalWrite(8+num_key_in_mcp,LOW);
  return;
}

/*********************************************/
/* interroger les MCP et envoyer le statut   */
/*********************************************/
void SendStatusKey(byte cmd1, byte cmd2)
{
    char byte_status[10]={cmd1,cmd2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    /*je boucle sur les 8 MCP*/
    for (byte m=0;m<8;m++)
    {
      byte k=0;
      /*je boucle sur les entrées du MCP*/
      if (mcps[m].address!=0) 
      { 
        Serial.print("Lecture MCP 0x");   Serial.print(mcps[m].address, HEX); Serial.print(" : ");
        byte v=0;
        for (byte n=0;n<8;n++) 
        {
          Serial.print(n);  Serial.print(":"); Serial.print(mcps[m].mcp.digitalRead(n));  Serial.print(" --  ");
          if ( mcps[m].mcp.digitalRead(n)==LOW) v=1; else v=0;
          k=k+v*powbyte(2,n); 
        }
        Serial.println();
      }
      byte_status[m+2]=k;
    }
    for (byte i=0;i<10;i++){ Serial.print("0x");   Serial.print(byte_status[ i ], HEX); Serial.print(" "); }

    for (byte i=0;i<10;i++) server.write(byte_status[i]);
}
/*********************************************/


/*********************************************/
/* Evoyer la valeur de l'impulseduration     */
/*********************************************/
void SendParam(byte cmd1, byte cmd2)
{
    char byte_status[10]={cmd1,cmd2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    byte_status[3]=impulseduration % 256;
    byte_status[4]=(impulseduration - (impulseduration % 256)) / 256;
    for (byte i=0;i<10;i++){ Serial.print("0x");   Serial.print(byte_status[ i ], HEX); Serial.print(" "); }
    for (byte i=0;i<10;i++) server.write(byte_status[i]);
}
/*********************************************/

void EtherServer()
{
  char byte_array[3];
  static int counter  = 0;
  static bool buffer_ready = false;
  EthernetClient client = server.available();
  if (client) 
  {
    while (client.connected()) 
    {
      if (client.available()) 
      {
        byte_array[ counter++ ] = client.read();
        //Buffer full
        if( counter == 3 )
        {
          counter = 0;
          buffer_ready = true;
        }
      }
      if (buffer_ready==true)
      {
          Serial.println();
          for (byte i=0;i<3;i++) { Serial.print("0x");   Serial.print(byte_array[ i ], HEX); Serial.print(" "); }
          Serial.println();
          if (byte_array[0]==0x10) 
          {
            if (byte_array[1]==0x01)
            {
                Serial.println("Demande libération de clé");
                //FreeKey envoie le statut des clés directement
                FreeKey(byte_array[0],byte_array[1],byte_array[2]);
                /*deconnecter le client*/
                delay(1);
                Serial.println("Sortie");
                client.stop();
            }
            else if ((byte_array[1]==0x02) and (byte_array[2]==0x00))
            {
                Serial.println("Demande de statut");
                SendStatusKey(byte_array[0],byte_array[1]);
                /*deconnecter le client*/
                delay(1);
                Serial.println("Sortie");
                client.stop();
            }
            else if ((byte_array[1]==0x03) and ((byte_array[2]==0x00) or (byte_array[2]==0xFF)))
            {
                Serial.println("Demande de paramètres");
                SendParam(byte_array[0],byte_array[1]);
                /*deconnecter le client*/
                delay(1);
                Serial.println("Sortie");
                client.stop();
            }
            else
            {
              Serial.println("Commande incomprise");
              for (byte i=0;i<3;i++) server.write(byte_array[i]);
              /*deconnecter le client*/
              delay(1);
              Serial.println("Sortie");
              client.stop();
            }
          }
          else
          {
            Serial.println("Commande incomprise");
            for (byte i=0;i<3;i++) server.write(byte_array[i]);
            /*deconnecter le client*/
            delay(1);
            Serial.println("Sortie");
            client.stop();
          }
          buffer_ready=false;
      }

    }
  }
}

/*********************************************/

void loop() 
{
  if (startloop==0)
  {
    Serial.println("Starting Main Loop");
    startloop=1;
  }

  EtherServer();
  Ethernetmaintain();
}