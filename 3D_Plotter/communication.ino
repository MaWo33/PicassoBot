boolean newData = false;
const byte numChars = 255;
char receivedChars[numChars];

void printToAllSerials(const String& message) {
  Serial.println(message);
  Serial2.println(message);
  // Add more if your board supports them
}
void printToAllSerialsNoNewLine(const String& message) {
  Serial.print(message);
  Serial2.print(message);
  // Add more if your board supports them
}
void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  //delay(200);
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';  // terminate the string
      ndx = 0;
      newData = true;
    }
  }
  while (Serial2.available() > 0 && newData == false) {
    rc = Serial2.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';  // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}
long* getParams(int size) {
  long* params = new long[size];
  int index = 1;

  // Wait for data to be available in Serial
  while (Serial.available() == 0 & Serial2.available() == 0) {}

  // Delay for stability
  delay(100);

  // Receive data and store it in receivedChars
  recvWithEndMarker();

  // Tokenize the received data using commas
  char* token = strtok(receivedChars, ",");
  while (token != NULL && index < size) {
    // Store each parameter in the params array
    params[index] = atol(token);  // Convert char to int
    index++;
    printToAllSerialsNoNewLine(token);
    // Get the next token
    token = strtok(NULL, ",");
  }

  // Reset receivedChars
  receivedChars[0] = '\0';

  // Print the stored parameters
  /*for (int i = 0; i < index; i++)
  {
    printToAllSerialsNoNewLine(params[i]);
    printToAllSerialsNoNewLine(' ');
  }*/
  params[0] = index;
  for (int i = 0; i < index; i++) {
    printToAllSerialsNoNewLine("Param ");
    printToAllSerialsNoNewLine(String(i));
    printToAllSerialsNoNewLine(": ");
    printToAllSerials(String(params[i]));
  }
  newData = false;
  return params;
}
