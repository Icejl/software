
# source insight 4

version: xx

## 注册码

通过导入si4.lic文件进行注册，有以下校验：
1. 文件是xml格式
2. 对xml中ActId校验
3. 对xml中Serial校验
4. 对xml中Signature校验
5. 网络验证，要patch掉

## 结构

主体结构
```c
struct __declspec(align(4)) stu
{
  int op_type;          // =1 通过公钥校验sig，=3 通过xor校验，=2 延迟激活， 根据ActId得到的值
  char serial[38];
  char field_2A[218];
  char LicensedUser[127];
  int field_184;
  char fill[124];
  char Organization[256];
  char Email[768];
  int version;
  _BYTE gap608[4];
  int type;
  char Expiration[12];
  char Date[12];
  char HWID[18];
  char ActId[128];
  char field_6BA[128];
  char field_73A[34];
  char lic_file[34];
};

```

xml 结构体
```c
struct xml
{
  struct xml *parent;
  struct xml *child;
  struct xml *nodes;
  struct xml *prop;
  DWORD u2;
  char *key;
  char *value;
  struct xml *u1;
  struct xml *offset;
};
```


## 注册逻辑

### xml 解析

主要注册函数

```c
void __usercall __noreturn sub_5192C0(struct stu *this@<ecx>, int a2@<edi>, int a3)
{
  int v4; // eax
  int v5; // eax
  const char *v6; // edi
  int v8; // [esp+0h] [ebp-104h]
  int v9; // [esp+0h] [ebp-104h]
  int Buffer; // [esp+4h] [ebp-100h] BYREF
  int v11; // [esp+8h] [ebp-FCh]
  int v12; // [esp+Ch] [ebp-F8h]
  int v13; // [esp+10h] [ebp-F4h]
  int v14; // [esp+14h] [ebp-F0h]
  int v15; // [esp+18h] [ebp-ECh]
  int v16; // [esp+1Ch] [ebp-E8h]
  int v17; // [esp+20h] [ebp-E4h]

  sub_5161F0(this);
  write_log_413230("Loading license file", v8, Buffer, v11, v12, v13, v14, v15, v16, v17);
  call 517890;          //  主要的解析函数
  if ( v4 != 200 )
  {
    if ( a3 )
    {
      show_err_515EB0(this, v4);
      sub_4135B0();
    }
LABEL_4:
    sub_5161F0(this);
    return;
  }
  if ( this->op_type == 2 )
  {
    write_log_413230("Deferred Activation license file loaded.", v9, Buffer, v11, v12, v13, v14, v15, v16, v17);
    this->op_type = 0;
    return;
  }
  if ( this->op_type == 3 )                     // xor 校验signature
  {
    v5 = sub_517070(this->lic_file, this->field_73A);
    if ( v5 != 200 )
      goto LABEL_12;
    if ( !sub_5189E0(this) )
    {
      v5 = 491;
      goto LABEL_12;
    }
  }
  else                                          // op = 1 校验certification
  {
    v5 = sub_517E60(this->lic_file, this->field_73A);
    if ( v5 != 200 )
    {
LABEL_12:
      if ( a3 )
      {
        show_err_515EB0(this, v5);
        sub_4135B0();
      }
      goto LABEL_4;
    }
  }
  v6 = "Trial";
  if ( this->type != 1 )
    v6 = "Standard";
  sub_44F810((char *)&Buffer);
  write_log_413230("License OK: %s License activated %s UTC", (int)v6, (int)&Buffer, a2, v9, Buffer, v11, v12, v13, v14);
}
```

解析函数，读取lic文件，解析xml格式，在0x00608320处可以找到lic格式
```c
int __thiscall __noreturn parse_lic_517890(struct stu *this)
{
  unsigned int i; // eax
  char *v3; // edi
  BOOL v4; // ebx
  int v6; // edi
  char v7; // al
  int v8; // eax
  char *String1; // [esp+Ch] [ebp-41Ch] BYREF
  int v10; // [esp+10h] [ebp-418h] BYREF
  int v11; // [esp+14h] [ebp-414h] BYREF
  int v12; // [esp+18h] [ebp-410h] BYREF
  int v13[256]; // [esp+1Ch] [ebp-40Ch] BYREF
  int v14; // [esp+424h] [ebp-4h]

  for ( i = 0; i < 0x80; ++i )
  {
    v13[i] = 0;
    v13[i + 128] = 0;
  }
  v14 = 0;
  this->type = 0;     
  call 516270;                      // 读取文件解析xml字段
  if ( sub_515730(v13, "Type", &String1) )
  {
    v3 = String1;
    if ( !_stricmp(String1, "Trial") )
    {
      this->type = 1;
    }
    else if ( !_stricmp(v3, "Beta") )
    {
      this->type = 3;
    }
    else if ( !_stricmp(v3, "Standard") )
    {
      this->type = 0;
    }
  }
  if ( !sub_515730(v13, "LicensedUser", &String1) )
    goto LABEL_41;
  strcpy(this->LicensedUser, String1);
  if ( sub_515730(v13, "Organization", &String1) )
    strcpy(this->Organization, String1);
  if ( sub_515730(v13, "Email", &String1) )
    strcpy(this->Email, String1);
  if ( !sub_515730(v13, "Serial", &String1) )
    goto LABEL_41;
  strcpy(this->serial, String1);
  if ( !sub_515730(v13, "ActId", &String1) )
    goto LABEL_41;
  strcpy(this->ActId, String1);
  v4 = match_actid_403510(this->ActId, byte_653F70, 4, 50, 7039) > 0;
  if ( !_stricmp(this->ActId, "Deferred") )
  {
    this->op_type = 2;                          // Deferred Activation
LABEL_19:
    v14 = -1;
    sub_515650((void **)v13);
    return 200;
  }
  if ( !check_serial_515C80(this->serial, &v12, &v11, &v10, !v4) || v11 != this->type )
  {
    v14 = -1;
    sub_515650((void **)v13);
    return 495;
  }
  v6 = v10;
  if ( v10 != unk_65BA13 )
    goto LABEL_35;
  if ( sub_45E6B0(&stru_66A920, this->serial) )
  {
    v14 = -1;
    sub_515650((void **)v13);
    return 460;
  }
  if ( v4 )
  {
    this->op_type = 3;
  }
  else
  {
    this->op_type = 1;
    if ( !sub_515730(v13, "HWID", &String1) )
    {
LABEL_41:
      v14 = -1;
      sub_515650((void **)v13);
      return 469;
    }
    strcpy(this->HWID, String1);
  }
  if ( !sub_515730(v13, "Version", &String1) )
    goto LABEL_41;
  v7 = *String1;
  if ( *String1 < '0' || v7 > '9' )
    goto LABEL_41;
  v8 = v7 - '0';
  this->version = v8;                           // = 4
  if ( v8 != unk_65BA13 || v8 != v6 )
  {
LABEL_35:
    v14 = -1;
    sub_515650((void **)v13);
    return 490;
  }
  *(_DWORD *)&this->Expiration[8] = 0;
  *(_DWORD *)&this->Expiration[4] = 0;
  *(_DWORD *)this->Expiration = 0;
  if ( !sub_515730(v13, "Expiration", &String1)
    || (sub_450B30((int *)this->Expiration, String1), sub_44F880((int *)this->Expiration)) )
  {
    *(_DWORD *)&this->Date[8] = 0;
    *(_DWORD *)&this->Date[4] = 0;
    *(_DWORD *)this->Date = 0;
    if ( !sub_515730(v13, "Date", &String1) )
      goto LABEL_19;
    sub_450B30((int *)this->Date, String1);
    if ( sub_44F880((int *)this->Date) )
      goto LABEL_19;
  }
  v14 = -1;
  sub_515650((void **)v13);
  return 483;
}
```

### 对 actid 校验

前面有4个固定字节，后面根据系统的磁盘id、用户sid、计算机名计算出一个字符串
```
BOOL __thiscall sub_5189E0(struct stu *this)
{
  int matched; // edi
  char Str2[256]; // [esp+8h] [ebp-100h] BYREF

  matched = match_actid_403510(this->ActId, byte_653F70, 4, 50, 7039);
  return matched && sub_517FA0(Str2, 0) && strcmp(&this->ActId[matched], Str2) == 0;
}
```

### Serial 校验

有两处调用，可以提供一些特殊值

```c
BOOL __cdecl check_serial_515C80(char *input, _DWORD *a2, _DWORD *a3, _DWORD *a4, int a5)
{
  char v5; // al
  char v6; // al
  char v7; // al
  char v8; // al
  int v10; // [esp+4h] [ebp-18h] BYREF
  char Destination[20]; // [esp+8h] [ebp-14h] BYREF

  _strupr(input);
  if ( strlen(input) != 19 )
    return 0;
  if ( input[4] != '-' )
    return 0;
  if ( input[9] != '-' )
    return 0;
  if ( input[14] != '-' )
    return 0;
  if ( *input != 'S' )
    return 0;
  if ( a5 )                                     // a5 = 0
  {
    v5 = input[6];
    if ( v5 != 'R' && v5 != 'G' && v5 != 'D' && v5 != 'F' )
      return 0;
  }
  v6 = input[1];
  if ( v6 < '0' || v6 > '9' )
    return 0;
  *a4 = v6 - '0';                               // = 4 
  v7 = input[2];
  switch ( v7 )
  {
    case 'T':
      *a3 = 1;
      break;
    case 'B':
      *a3 = 3;
      break;
    case 'S':
      *a3 = 0;
      break;
    case 'U':
      *a3 = 0;                                  // here
      break;
    default:
      return 0;
  }
  v8 = input[3];
  if ( v8 == 'G' )
  {
    *a2 = 1;
  }
  else
  {
    if ( v8 != 'R' )
      return 0;
    *a2 = 0;
  }
  if ( !a5 )
    return 1;
  strcpy(Destination, input);
  Destination[15] = 0;
  sub_5154E0(Destination, 15u, byte_607280, (char *)&v10);
  return *(_DWORD *)(input + 15) == v10;
}
```

### Signature 校验

op = 3，xor校验sig
```c
int __cdecl sub_517070(const CHAR *Code, void *a2)
{
  int result; // eax
  struct xml *v3; // eax
  struct xml *v4; // eax
  struct xml *v5; // esi
  struct xml *v6; // eax
  unsigned __int8 *value; // edi
  char *v8; // eax
  char *v9; // ebp
  size_t v10; // eax
  unsigned int v11; // eax
  char *v12; // ecx
  char *v13; // esi
  int v14; // esi
  int v15; // [esp+4h] [ebp-2124h] BYREF
  char v16[128]; // [esp+8h] [ebp-2120h] BYREF
  char v17[256]; // [esp+88h] [ebp-20A0h] BYREF
  char file_content[8096]; // [esp+188h] [ebp-1FA0h] BYREF

  result = read_file_515780(Code, file_content, 8096u);
  if ( result == 200 )
  {
    v3 = (struct xml *)sub_516940(file_content, a2);// 0045C320
    if ( v3 && (v4 = sub_4596C0(v3, "Signature"), (v5 = v4) != 0) && (v6 = sub_459EE0(v4, "Value")) != 0 )
    {
      value = (unsigned __int8 *)v6->value;
      file_content[(unsigned int)v5->offset] = 0;// 到Signature标签结束
      v8 = (char *)strdup_4453D0(file_content);
      v9 = v8;
      if ( v8 )
      {
        sub_4472C0(file_content, "\n\r\t ", v8);
        v10 = strlen(v9);
        sub_4031B0((unsigned __int8 *)v9, v10 + 1, 1968, 128, v16);
        b64decode_402EA0(value, v17, &v15);     // sig解base64
        if ( v15 == 128 )
        {
          v11 = 128;
          v12 = v16;
          v13 = v17;
          while ( *(_DWORD *)v13 == *(_DWORD *)v12 )// compare signature
          {
            v11 -= 4;
            v12 += 4;
            v13 += 4;
            if ( v11 < 4 )
            {
              if ( !v11 || *v12 == *v13 && (v11 <= 1 || v12[1] == v13[1] && (v11 <= 2 || v12[2] == v13[2])) )
              {
                v14 = 1;
                goto LABEL_20;
              }
              break;
            }
          }
        }
        v14 = 0;
LABEL_20:
        sub_425780(v9);
        return v14 != 0 ? 200 : 462;
      }
      else
      {
        return 492;
      }
    }
    else
    {
      return 460;
    }
  }
  return result;
}
```

op = 1，通过公钥验签
```c
int __cdecl sub_517E60(const CHAR *Code, void *a2)
{
  int result; // eax
  struct xml *v3; // eax
  struct xml *v4; // eax
  struct xml *v5; // esi
  struct xml *v6; // eax
  unsigned __int8 *value; // edi
  size_t v8; // eax
  char *v9; // esi
  int v10; // ecx
  char *i; // edx
  char v12; // al
  DWORD v13; // eax
  int v14; // edi
  DWORD dwSigLen; // [esp+4h] [ebp-23A4h] BYREF
  BYTE pbSignature[1024]; // [esp+8h] [ebp-23A0h] BYREF
  char Str[8096]; // [esp+408h] [ebp-1FA0h] BYREF

  result = read_file_515780(Code, Str, 8096u);
  if ( result == 200 )
  {
    v3 = (struct xml *)sub_516940(Str, a2);     // 0045C320 
    if ( v3 && (v4 = sub_4596C0(v3, "Signature"), (v5 = v4) != 0) && (v6 = sub_459EE0(v4, "Value")) != 0 )
    {
      value = (unsigned __int8 *)v6->value;
      Str[(unsigned int)v5->offset] = 0;
      v8 = strlen(Str);
      v9 = (char *)malloc(v8 + 1);
      if ( v9 )
      {
        v10 = 0;
        for ( i = Str; *i; ++i )
        {
          v12 = *i;
          if ( *i != '\n' && v12 != '\r' && v12 != '\t' && v12 != ' ' )
            v9[v10++] = v12;
        }
        v9[v10] = 0;
        b64decode_402EA0(value, pbSignature, &dwSigLen);
        v13 = strlen(v9);
        v14 = sub_515800((BYTE *)v9, v13, pbSignature, dwSigLen);// 公钥验签
        free(v9);
        return v14;
      }
      else
      {
        return 492;
      }
    }
    else
    {
      return 460;
    }
  }
  return result;
}
```

## 网络校验

发送lic到服务器校验，可以直接return 200

```c
void __thiscall sub_518290(struct stu *this, int a2)
{
  int v3; // [esp+0h] [ebp-3FA8h]
  int v4; // [esp+4h] [ebp-3FA4h]
  int v5[2024]; // [esp+8h] [ebp-3FA0h] BYREF
  char Str[8192]; // [esp+1FA8h] [ebp-2000h] BYREF

  memset(Str, 0, sizeof(Str));
  if ( sub_516370(this, (int)v5, 8096, a2) == 200 ) // 联网
  {
    if ( a2 )
    {
      if ( read_file_515780(this->lic_file, (char *)v5, 8096u) == 200 )
        sub_5180B0((const char **)this, (char *)v5);
    }
    else
    {
      write_log_413230("License Activated", v3, v4, v5[0], v5[1], v5[2], v5[3], v5[4], v5[5], v5[6]);
      if ( sub_4265B0(v5, (int)Str, 0x2000u) && (int)strlen(Str) >= 8 )
      {
        sub_5180B0((const char **)this, &Str[8]);
        sub_515A30(this->lic_file, &Str[8]);
      }
    }
  }
}
```