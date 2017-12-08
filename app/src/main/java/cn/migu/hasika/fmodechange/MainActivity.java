package cn.migu.hasika.fmodechange;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        org.fmod.FMOD.init(MainActivity.this);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
        {
            String[] perms = { "android.permission.RECORD_AUDIO", "android.permission.WRITE_EXTERNAL_STORAGE" };
            if (checkSelfPermission(perms[0]) == PackageManager.PERMISSION_DENIED ||
                    checkSelfPermission(perms[1]) == PackageManager.PERMISSION_DENIED)
            {
                requestPermissions(perms, 200);
            }
        }
    }

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public void nativePlay(View btn) {
        btn.setEnabled(false);
        //file:///android_asset/raw/sample/logout.png
//        String path = Environment.getExternalStorageDirectory()+ File.separator+"1.mp3";
        String path = "file:///android_asset/1.mp3";

        switch (btn.getId()){
            case R.id.normal:
                FmodChange.playNormal(FmodChange.NORMAL, path);
                break;
            case R.id.dashu:
                FmodChange.playNormal(FmodChange.DASHU, path);
                break;
            case R.id.luoli:
                FmodChange.playNormal(FmodChange.LUOLI, path);
                break;
            case R.id.gaoguai:
                FmodChange.playNormal(FmodChange.GAOGUAI, path);
                break;
            case R.id.kongling:
                FmodChange.playNormal(FmodChange.KONGLING, path);
                break;
//            case R.id.jingsong:
//                FmodChange.playNormal(FmodChange.JINGSONG, path);
//                break;
            case R.id.more_dashu:
                FmodChange.playNormal(FmodChange.MORE_DASHU, path);
                break;
            case R.id.more_luoli:
                FmodChange.playNormal(FmodChange.MORE_LUOLI, path);
                break;
            case R.id.more_gaoguai:
                FmodChange.playNormal(FmodChange.MORE_GAOGUAI, path);
                break;
            case R.id.more_huisheng:
                FmodChange.playNormal(FmodChange.MORE_KONGLING, path);
                break;
            case R.id.more_huanyuan:
                FmodChange.playNormal(FmodChange.RESET, path);
                break;

                default:
                    break;
        }
        btn.setEnabled(true);

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        org.fmod.FMOD.close();
    }
}
