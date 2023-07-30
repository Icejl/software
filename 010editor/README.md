
# 010editor 注册机

版本：13.0.2

## 对象结构

```
+8 用户名
+16 密码
+24 LastDate
+60 网络验证
+68 有效时间 * 86400
```

## 移除网络验证

patch两处网络验证，或者直接替换010Editor.exe

```
48 89 5C 24 18 48 89 74 24 20 55 57 41 56 48 8D AC 24 90 F0 FF FF
48 31 C0 48 FF C0 C3 74 24 20 55 57 41 56 48 8D AC 24 90 F0 FF FF

48 89 5C 24 08 57 48 83 EC 20 83 79 3C 00 8B FA 48 8B D9 74 10
48 89 5C 24 08 57 48 83 EC 20 83 79 3C 00 8B FA 48 8B D9 EB 10
```

## 生成注册码

执行010gen.exe，生成注册码


## 代码

输入用户名密码进行验证

```c
void __fastcall sub_140210560(void (__fastcall ***a1)(QWidget **))
{
  ...
  if ( v12 )
  {
    v48 = QString::fromAscii_helper("Please completely enter your password.", 38i64);
    sub_14000AEBB(&v48);
    goto LABEL_27;
  }
  v13 = QLineEdit::text(a1[29], &v51);
  QString::operator=(&v50, v13);
  QString::~QString((QString *)&v51);
  if ( (unsigned int)sub_1400021C6(a1, &v50) )
  {
    v14 = QString::left(&v50, &v51, 19i64);
    QString::operator=(&v50, v14);
    QString::~QString((QString *)&v51);
  }
  v15 = QLineEdit::text(a1[27], &v51);
  sub_140009BE7(register_140D64950, v15);
  QString::~QString((QString *)&v51);
  sub_140003D73(register_140D64950, (__int64)&v50);
  v16 = sub_1400060D7(register_140D64950, 14u, 19242u);// 140D64950 = 时间戳 用户名 密码
  v17 = sub_140008693(register_140D64950, 14i64, 19242i64);// check
  v18 = register_140D64950;
  if ( v16 != 231 && *(_DWORD *)(register_140D64950 + 60) )
  {
    v19 = sub_140006956((int)a1, 0);            // 网络验证
    if ( v19 < 0 )
    {
      v20 = (const struct QString *)QString::number(v46, (unsigned int)v19, 10i64);
      v44 = QString::fromAscii_helper(
              "Could not contact the webserver. Please check your internet connection. If your internet connection is cur"
              "rently working, the server may be down. If this problem persists, please visit 'https://www.sweetscape.com/support/' (",
              224i64);
      ...
  }
  if ( v17 == 219 )
  {
    sub_14000376F(v18, (__int64)v46);           // 过期时间
    v43 = QString::fromAscii_helper("MMMM d, yyyy", 12i64);
    v26 = (const struct QString *)QDate::toString(v46, v47, &v43);
    v27 = (const struct QString *)QString::fromUtf8(
                                    &v44,
                                    "Password accepted. This license entitles you to:\n"
                                    "\n"
                                    "  - Free Upgrades\n"
                                    "  - Free Support\n"
                                    "  - Free Repository Updates\n"
                                    "\n"
                                    "until ",
                                    0xFFFFFFFFi64);
    v28 = v9 | 0x100;
    LODWORD(v48) = v28;
    QString::append((QString *)&v44, v26);
    QString::QString((QString *)&v51, v27);
    v28 |= 0x200u;
    LODWORD(v48) = v28;
    v29 = (const struct QString *)QString::fromUtf8(v45, &word_140631C1C, 0xFFFFFFFFi64);
    QString::append((QString *)&v51, v29);
    QString::~QString((QString *)v45);
    LODWORD(v48) = v28 & 0xFFFFFEFF;
    QString::~QString((QString *)&v44);
    QString::~QString((QString *)v47);
    QString::~QString((QString *)&v43);
    if ( (int)sub_14000AE25(register_140D64950) < 0 )// 判断时间有效性
      QString::operator+=(&v51, " (EXPIRED)");
   ...
}
```

验证算法
```c
__int64 __fastcall sub_14036E740(__int64 a1, unsigned int a2, unsigned int a3)
{
  ...
  if ( *(_DWORD *)(*(_QWORD *)(a1 + 8) + 4i64) && *(_DWORD *)(*(_QWORD *)(a1 + 16) + 4i64) )// 用户名 密码 长度
  {
    sub_140005560(a1, (__int64)pwd);            // 密码转16进制 1111-2222-3333-4444-5555
    v5 = &off_140B9A570;
    do
    {
      if ( (unsigned __int8)QString::operator==(a1 + 8, *v5) )// 用户名不能999
        return 231i64;
      ++v5;
    }
    ...
 
    v14 = (unsigned __int8)pwd[5];
    v15 = pwd[2];
    v16 = pwd[1];
    v17 = (unsigned __int8)pwd[0];
    v18 = pwd[3];
    // 不同类型注册
    switch ( pwd[3] )                           // case -100
    {
      case 0x9C:
        v19 = (unsigned __int8)(pwd[5] ^ pwd[2]) + ((unsigned __int8)(pwd[7] ^ pwd[1]) << 8);
        *(_DWORD *)(a1 + 44) = (unsigned __int8)sub_140004B01((unsigned __int8)(pwd[6] ^ pwd[0]));
        v20 = (unsigned __int16)sub_14000B046(v19);
        *(_DWORD *)(a1 + 48) = (unsigned __int16)v20;
        v21 = *(_DWORD *)(a1 + 44);
        if ( v21 && (unsigned int)(v20 - 1) <= 999 )
        {
          v22 = 0;
          if ( v21 < 2 )
            v22 = *(_DWORD *)(a1 + 44);
LABEL_26:
          QString::toUtf8(a1 + 8, v36);
          LOBYTE(v4) = v18 != -4;
          v24 = QByteArray::data((QByteArray *)v36);
          v25 = sub_140004A11((__int64)v24, v4, v22, *(unsigned int *)(a1 + 48));
          if ( pwd[4] == (_BYTE)v25 && (_BYTE)v14 == BYTE1(v25) && pwd[6] == BYTE2(v25) && pwd[7] == HIBYTE(v25) )
          {
            if ( v18 == (char)0x9C )
            {
              if ( v34 > *(_DWORD *)(a1 + 44) ) // v34 =0x14
              {
                v26 = 78;
LABEL_41:
                QByteArray::~QByteArray((QByteArray *)v36);
                return v26;
              }
LABEL_33:
              v26 = 45;                         // here.......
              goto LABEL_41;
            }
            if ( v18 == (char)0xFC )
            {
              v27 = sub_140009B97(
                      (unsigned __int8)pwd[0] + ((unsigned __int8)pwd[1] << 8) + ((unsigned __int8)pwd[2] << 16),
                      v25);
              if ( v27 )
              {
                *(_DWORD *)(a1 + 40) = v27;
                v26 = 147;
                goto LABEL_41;
              }
            }
            else if ( v29 )                     // case 0xac v29 不为0
            {
              if ( v35 > v29 )                  // v35 = 19242
              {
                v26 = 'N';
                goto LABEL_41;
              }
              goto LABEL_33;
            }
          }
          v26 = 231;
          goto LABEL_41;
        }
        break;
      case 0xFC:
        v22 = 255;
        *(_DWORD *)(a1 + 44) = 255;
        *(_DWORD *)(a1 + 48) = 1;
        *(_DWORD *)(a1 + 64) = 1;
        goto LABEL_26;
      case 0xAC:
        *(_DWORD *)(a1 + 44) = 2;
        v23 = sub_14000B046((unsigned __int16)((unsigned __int8)(v14 ^ v15) + ((unsigned __int8)(pwd[7] ^ v16) << 8)));
        *(_DWORD *)(a1 + 48) = v23;
        if ( (unsigned int)v23 - 1 <= 999 )
        {
          v29 = sub_140009B97(
                  ((unsigned __int8)pwd[6] ^ v17)
                + ((v14 ^ (unsigned __int8)pwd[9]) << 16)
                + (((unsigned __int8)pwd[8] ^ (unsigned int)(unsigned __int8)pwd[4]) << 8),
                  0x5B8C27i64);
          *(_DWORD *)(a1 + 68) = v29;           // 有效日期 * 86400
          v22 = v29;
          goto LABEL_26;
        }
        break;
    }
    return 231i64;
  }
  return 147i64;
}
```