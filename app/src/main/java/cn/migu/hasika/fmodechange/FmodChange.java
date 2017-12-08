package cn.migu.hasika.fmodechange;

/**
 * Created by hasika on 2017/12/7.
 */

public class FmodChange {
     public static int NORMAL = 0;
     public static int DASHU = 1;
     public static int LUOLI = 2;
     public static int GAOGUAI = 3;
     public static int KONGLING = 4;
     public static int JINGSONG = 5;
     public static int MORE_DASHU = 6;
     public static int MORE_LUOLI = 7;
     public static int MORE_GAOGUAI = 8;
     public static int MORE_KONGLING = 9;
     public static int RESET = 10;


     public native static void playNormal(int type, String path);
}
