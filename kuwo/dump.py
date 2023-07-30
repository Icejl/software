import frida, sys

def on_message(message, data):
    print(message)
    
jscode = """
Java.perform(function x() {
    var it = setInterval(function(){
    try{
        let AnonymousClass1 = Java.use("cn.kuwo.kwmusiccar.MainActivity$1");
        AnonymousClass1["IPlayControlObserver_PlayFailed"].implementation = function (errorCode, z) {
            console.log(Java.use("android.util.Log").getStackTraceString(Java.use("java.lang.Throwable").$new()));
            
            console.log('IPlayControlObserver_PlayFailed is called' + ', ' + 'errorCode: ' + errorCode + ', ' + 'z: ' + z);
            let ret = this.IPlayControlObserver_PlayFailed(errorCode, z);
            console.log('IPlayControlObserver_PlayFailed ret value is ' + ret);
            return ret;
        };
        
        let AnonymousClass7 = Java.use("cn.kuwo.mod.playcontrol.PlayControlImpl$7");
        let status = Java.use("cn.kuwo.mod.vipnew.MusicChargeStatus");
        AnonymousClass7["a"].implementation = function (music2, musicChargeStatus, str) {
            console.log(Java.use("android.util.Log").getStackTraceString(Java.use("java.lang.Throwable").$new()));
            
            console.log('a is called' + ', ' + 'music2: ' + music2 + ', ' + 'musicChargeStatus: ' + musicChargeStatus + ', ' + 'str: ' + str);
            
            let ret = this.a(music2, musicChargeStatus, str);
            console.log('a ret value is ' + ret);
            return ret;
        };
        
        let AnonymousClass5 = Java.use("cn.kuwo.ui.fragment.OnlineRootFragment$5");
        AnonymousClass5["onPlayClick"].implementation = function (onlineRootAdapter, i, z3) {
        
            console.log(Java.use("android.util.Log").getStackTraceString(Java.use("java.lang.Throwable").$new()));
            
            console.log('onPlayClick is called' + ', ' + 'onlineRootAdapter: ' + onlineRootAdapter + ', ' + 'i: ' + i + ', ' + 'z3: ' + z3);
            let ret = this.onPlayClick(onlineRootAdapter, i, z3);
            console.log('onPlayClick ret value is ' + ret);
            return ret;
        };
        
        let QuickStateUtils = Java.use("cn.kuwo.ui.QuickStateUtils");
        QuickStateUtils["clickPlayIcon"].implementation = function (activity, baseQuickAdapter, i, sourceType) {
            console.log(Java.use("android.util.Log").getStackTraceString(Java.use("java.lang.Throwable").$new()));
            
            console.log('clickPlayIcon is called' + ', ' + 'activity: ' + activity + ', ' + 'baseQuickAdapter: ' + baseQuickAdapter + ', ' + 'i: ' + i + ', ' + 'sourceType: ' + sourceType);
            let ret = this.clickPlayIcon(activity, baseQuickAdapter, i, sourceType);
            console.log('clickPlayIcon ret value is ' + ret);
            return ret;
        };
            
    } catch(e) {
      console.log("failed!");
    }
  },200); // runs every 200milisecods
});
"""

device = frida.get_usb_device()
# ./frida-server -l 192.168.0.1:6666  # default 27042
#device = frida.get_device_manager().add_remote_device('127.0.0.1:27042')

#session = device.attach('cn.kuwo.kwmusiccar')
pid = device.spawn(['cn.kuwo.kwmusiccarcc'])
print(pid)
#pid = 5525
device.resume(pid)
session = device.attach(pid)

script = session.create_script(jscode)
script.on('message', on_message)
print('[*] Running')
script.load()
sys.stdin.read()