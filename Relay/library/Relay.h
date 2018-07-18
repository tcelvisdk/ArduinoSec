int relayPort = 999;
void RelayInitialize(int port)
{
 relayPort = port;
  pinMode(relayPort, OUTPUT);       
}

void RelayOn()
{
  if (relayPort != 999)
     digitalWrite(relayPort, 0);           // Turns ON Relays 1
}

void RelayOff()
{
    if (relayPort != 999)
     digitalWrite(relayPort, 1);           // Turns ON Relays 1
}