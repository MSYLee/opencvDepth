String AckCheck;
String AckCheck_ORG = "OK";
String DoneCheck = "DO";
//String tmptest=0;
//시리얼 통신 테스트변수
char cominData;
char cominChar;
String comINinit = "";
String comString = "";
int modetmp = 1;


//시리얼 초기화 테스트 변수
char initinData;
char initinChar;
String BuildINinit = "";
String initString = "";






void readdata() {


  while (Serial.available() > 0) {
    if (Serial.find("DO")) {
      modetmp = 2;
      //Serial.println("START");
    }
  }

}



void reciveData() {

  while (Serial.available() > 0) {
    Serial.println("SEND_Request_enabled");
    Serial.print("modetmp :[");
    Serial.print(modetmp);
    Serial.print("]\n");
    Serial.flush();
    Serial.println("------Session Start-------");
  }


}
