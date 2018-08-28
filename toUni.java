import java.io.*;

public class toUni{



  //스탠다드 모음
  final static String[] uASKII = {
   "0020", "0021", "0022", "0023",
   "0024", "0025", "0026", "0027",
   "0028", "0029", "002A", "002B",
   "002C", "002D", "002E", "002F",
   "0030", "0031", "0032", "0033",
   "0034", "0035", "0036", "0037",
   "0038", "0039", "003A", "003B",
   "003C", "003D", "003E", "003F",
   "0040", "0041", "0042", "0043",
   "0044", "0045", "0046", "0047",
   "0048", "0049", "004A", "004B",
   "004C", "004D", "004E", "004F",
   "0050", "0051", "0052", "0053", 
   "0054", "0055", "0056", "0057",
   "0058", "0059", "005A", "005B",
   "005C", "005D", "005E", "005F",
   "0060", "0061", "0062", "0063",
   "0064", "0065", "0066", "0067",
   "0068", "0069", "006A", "006B",
   "006C", "006D", "006E", "006F",
   "0070", "0071", "0072", "0073",
   "0074", "0075", "0076", "0077",
   "0078", "0079", "007A", "007B",
   "007C", "007D", "007E"
    };

  //한글 초중종성 
  final static String[] uHead = {
    "1100", "1101", "1102", "1103",
    "1104", "1105", "1106", "1107",
    "1108", "1109", "110A", "110B",
    "110C", "110D", "110E", "110F",
    "1110", "1111", "1112"};

  final static String[] uMid = {
    "1161", "1162", "1163", "1164",
    "1165", "1166", "1167", "1168", 
    "1169", "116A", "116B", "116C",
    "116D", "116E", "116F", "1170",
    "1171", "1172", "1173", "1174",
    "1175"};

  final static String[] uTail = {
    "11A8", "11A9", "11AA", "11AB",
    "11AC", "11AD", "11AE", "11AF",
    "11B0", "11B1", "11B2", "11B3",
    "11B4", "11B5", "11B6", "11B7",
    "11B8", "11B9", "11BA", "11BB",
    "11BC", "11BD", "11BE", "11BF",
    "11C0", "11C1", "11C2"};
  
  //약어
  final static int Wnum=3;
  final static String[] uWords = {
    //앞 공백, 뒤는 ‘,’과 ‘.’ 가능
    //그래서 그러나 그러면 그러므로 그런데 그리고 그리하여
    "4001", "4002", "4003", "4004", "4005","4006", "4007"
  };
  final static String[] sWords = {
    "그래서", "그러나", "그러면", "그러므로", "그런데", "그리고", "그리하여"};
  final static char[] cWords = {
    0x4001, 0x4002, 0x4003, 0x4004, 0x4005, 0x4006, 0x4007
  };

  public static void main(String[] args){

    try{


      BufferedReader in = new BufferedReader(
          new InputStreamReader(
            new FileInputStream(args[0]), "UTF-8"));
      BufferedWriter out = new BufferedWriter(
          new OutputStreamWriter(
            new FileOutputStream("out.txt"), "UTF-8"));

      String s;
      while ((s=in.readLine()) != null){
        out.write(toUni(s));
        out.newLine();
      }
      in.close();
      out.close();
    
    
    }catch(IOException e){
      System.err.println(e);
      System.exit(1);
    }


  }
  public static String toUni(String s){

    int cho, jung, jong;  //초,중,종성의 인덱스
    int askii;//아스키 스탠다드의 인덱스
    int yak;

    String result = "";
        
    //     < 1. 약어 처리 >
    //    
    s = yak(s);    
    System.out.println(s);
    //    < 2. 자, 모 분리 및 유니코드로 변환 >
    //
    for(int i=0; i< s.length(); i++){
      char ch = s.charAt(i);

      
      //한글인 경우
      if( (ch >=0xAC00) && (ch<= 0xD7A3) ){ //AC00(가)~D7A3(힣)인 경우
        jong = ch-0xAC00;
        cho = jong/(21*28);
        jong = jong%(21*28);
        jung = jong/28;
        jong = jong%28;

        result = result+ uHead[cho] + uMid[jung];
        if( jong != 0 ){
          result = result + uTail[jong];
        }else {
          //result = result + ch;
        }
      } // 스탠다드인 경우
      else if( (ch >=0x0020) && (ch<= 0x007E) ){
        askii = ch-0x0020;
        result = result + uASKII[askii];
      }// 약어인 경우
      else if( (ch>=0x4001) && (ch<= 0x4007) ){
        yak = ch-0x4001;
        result = result + uWords[yak];
      }

    }
    return result;
  }
  public static String yak(String s){
    int word=0;// 단어 인덱스
    String[] str1;
    String[] str2;
    // String.contains("aaa"); <- return boolean
    // String.replace("a", "b");
    
    //  그래서    4001

    //  그러나    4002
    
    //  그러면    4003

    //  그러므로  4004
    
    //  그런데    4005

    //  그리고    4006

    //  그리하여  4007
    for(int i=0; i<7; i++){
      if(s.contains( sWords[i] )){
        word = i;
        System.out.println(i);
        str1 = makeStr1(word);
        str2 = makeStr2(word);
        for(int j=0; j< Wnum;j++){
          s.replace( str1[j], str2[j]);
        }
      }
    }

    return s;
  }
  public static String[] makeStr1(int word){
    String[] str = new String[Wnum];
    str[0] = ' ' + sWords[word] + ' ';
    str[1] = ' ' + sWords[word] + ',';
    str[2] = ' ' + sWords[word] + '.';

    return str;
  }
  public static String[] makeStr2(int word){
    String[] str = new String[Wnum];
    str[0] = " " + cWords[word] + " ";
    str[1] = " " + cWords[word] + ",";
    str[2] = " " + cWords[word] + ".";

    return str;
  }
}

