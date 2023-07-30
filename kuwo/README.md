
# 酷我音乐

> 改的很垃圾，patch isVip就可以的

kuwo 车机版，移除会员验证

1. VIP歌曲正常播放
2. VIP歌单可以播放
3. 可以修改音效
4. 可以修改皮肤
5. 移除了主界面的登录

- 一个修改的位置

```Java
    boolean a(Music music) {
        CarSoundEffectSettingPresenter carSoundEffectSettingPresenter = new CarSoundEffectSettingPresenter(MainActivity.getInstance());
        int a2 = ConfMgr.a("appconfig", "key_sound_effect_vinyl", 0);
        if (music.b() == 1) {
            carSoundEffectSettingPresenter.f();
        } else if (a2 == 1) {
            carSoundEffectSettingPresenter.h();
        }
        ArrayList arrayList = new ArrayList();
        arrayList.add(music);
        h();
        KwCarPlay.sendPlayerStatusBroadcast(App.getInstance(), PlayProxy.Status.INIT.ordinal(), music);
        MusicChargeManager.a().a(arrayList, 0, new MusicChargeListener() { // from class: cn.kuwo.mod.playcontrol.PlayControlImpl.7
            @Override // cn.kuwo.mod.vipnew.MusicChargeListener
            public void a(Music music2, MusicChargeStatus musicChargeStatus, String str) {
                App app;
                final PlayDelegate.ErrorCode errorCode = PlayDelegate.ErrorCode.SUCCESS;
                int i = 1;
                switch (musicChargeStatus) {
                    case Free:
                        PlayControlImpl.this.c(music2);
                        errorCode = PlayDelegate.ErrorCode.SUCCESS;
                        break;
                    case VIP:
                        errorCode = PlayDelegate.ErrorCode.NOT_VIP_USER;
                        app = App.getInstance();
                        KwCarPlay.sendPaySongAction(app, music2, i);
                        break;
                    case Song:
                        errorCode = PlayDelegate.ErrorCode.SONG;
                        app = App.getInstance();
                        i = 2;
                        KwCarPlay.sendPaySongAction(app, music2, i);
                        break;
                    case Album:
                        errorCode = PlayDelegate.ErrorCode.ALBUM;
                        app = App.getInstance();
                        i = 3;
                        KwCarPlay.sendPaySongAction(app, music2, i);
                        break;
                    case CarVip:
                        errorCode = PlayDelegate.ErrorCode.NOT_CAR_VIP_USER;
                        app = App.getInstance();
                        KwCarPlay.sendPaySongAction(app, music2, i);
                        break;
                    case Fail:
                        errorCode = PlayDelegate.ErrorCode.Check_Fail;
                        break;
                    case VinylNeedLogin:
                        errorCode = PlayDelegate.ErrorCode.VINYL_NEED_LOGIN;
                        break;
                }
                if (errorCode != PlayDelegate.ErrorCode.SUCCESS) {
                    MessageManager.a().b(new MessageManager.Runner() { // from class: cn.kuwo.mod.playcontrol.PlayControlImpl.7.1
                        @Override // cn.kuwo.core.messagemgr.MessageManager.Runner, cn.kuwo.core.messagemgr.MessageManager.Caller
                        public void call() {
                            PlayControlImpl.this.a(errorCode, (errorCode == PlayDelegate.ErrorCode.NOT_VIP_USER || errorCode == PlayDelegate.ErrorCode.NOT_CAR_VIP_USER) ? false : true);
                        }
                    });
                } else {
                    Log.e("kuwolog", "retryPlayVipTimes = 0  1");
                    PlayControlImpl.this.l = 0;
                }
                Log.d("PlayControlImpl", "music: " + music2.g + " status: " + musicChargeStatus + " message: " + str);
            }
        });
        return true;
    }

```

```smali=

    :pswitch_4 # Song
    sget-object v0, Lcn/kuwo/service/PlayDelegate$ErrorCode;->E:Lcn/kuwo/service/PlayDelegate$ErrorCode;

    invoke-static {}, Lcn/kuwo/kwmusiccar/App;->getInstance()Lcn/kuwo/kwmusiccar/App;

    move-result-object v1

    const/4 v2, 0x2 # Song

    goto :goto_1

    :pswitch_5 # VIP？
    # 修改
    goto :pswitch_6 
    sget-object v0, Lcn/kuwo/service/PlayDelegate$ErrorCode;->y:Lcn/kuwo/service/PlayDelegate$ErrorCode;

    :goto_0
    invoke-static {}, Lcn/kuwo/kwmusiccar/App;->getInstance()Lcn/kuwo/kwmusiccar/App;

    move-result-object v1

    :goto_1
    invoke-static {v1, p1, v2}, Lcn/kuwo/kwmusiccar/KwCarPlay;->sendPaySongAction(Landroid/content/Context;Lcn/kuwo/base/bean/Music;I)V

    goto :goto_2

    :pswitch_6 # Free ？
    iget-object v0, p0, Lcn/kuwo/mod/playcontrol/PlayControlImpl$7;->a:Lcn/kuwo/mod/playcontrol/PlayControlImpl;

    invoke-static {v0, p1}, Lcn/kuwo/mod/playcontrol/PlayControlImpl;->a(Lcn/kuwo/mod/playcontrol/PlayControlImpl;Lcn/kuwo/base/bean/Music;)V

    sget-object v0, Lcn/kuwo/service/PlayDelegate$ErrorCode;->a:Lcn/kuwo/service/PlayDelegate$ErrorCode;

    :goto_2
    sget-object v1, Lcn/kuwo/service/PlayDelegate$ErrorCode;->a:Lcn/kuwo/service/PlayDelegate$ErrorCode;

    # 修改
    # if-eq v0, v1, :cond_0
    goto :cond_0

    invoke-static {}, Lcn/kuwo/core/messagemgr/MessageManager;->a()Lcn/kuwo/core/messagemgr/MessageManager;

    move-result-object v1

    new-instance v2, Lcn/kuwo/mod/playcontrol/PlayControlImpl$7$1;

    invoke-direct {v2, p0, v0}, Lcn/kuwo/mod/playcontrol/PlayControlImpl$7$1;-><init>(Lcn/kuwo/mod/playcontrol/PlayControlImpl$7;Lcn/kuwo/service/PlayDelegate$ErrorCode;)V

    invoke-virtual {v1, v2}, Lcn/kuwo/core/messagemgr/MessageManager;->b(Lcn/kuwo/core/messagemgr/MessageManager$Runner;)V

```