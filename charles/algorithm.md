

com.xk72.charles;


str : Name
str2: License
i2  : 4
```c
private long a(String str, String str2, int i2) {
    // license长度为18
    if (str2.length() != 18) {
        throw new LicenseException(n(0));
    }
    // license黑名单
    if (str2.equalsIgnoreCase("7055ce2f8cb4f9405f") || str2.equalsIgnoreCase("5bae9d8cdea32760ae") || str2.equalsIgnoreCase("f3264994d9ea6bc595") || str2.equalsIgnoreCase("b9930cef009d3a7865") || str2.equalsIgnoreCase("62bd6a5f95aa67998e") || str2.equalsIgnoreCase("a1c536c35904e64584") || str2.equalsIgnoreCase("d6e5590ecc05edd9b3") || str2.equalsIgnoreCase("8fbe36ce2726458b18") || str2.equalsIgnoreCase("042a8352caf1188945") || str2.equalsIgnoreCase("9d26d5088770221c3c") || str2.equalsIgnoreCase("e19b2a01905e4129bf") || str2.equalsIgnoreCase("68ebe4c9d792f31057") || str2.equalsIgnoreCase("4e4beb8a43e9feb9c7") || str2.equalsIgnoreCase("d04d85b44b306fc9ec") || str2.equalsIgnoreCase("2b5d21a38c9452e342") || str2.equalsIgnoreCase("88cb89c26a813bce44") || str2.equalsIgnoreCase("76c9ee78c8ab124054") || str2.equalsIgnoreCase("729db7c98163ac7d3d") || str2.equalsIgnoreCase("7c1d4761993c412472") || str2.equalsIgnoreCase("08bc0b7ec91cd0f4aa") || str2.equalsIgnoreCase("25bafae175decaedcc") || str2.equalsIgnoreCase("3181aae6822ef90ccd") || str2.equalsIgnoreCase("d7a8fe9dc9dc919f87") || str2.equalsIgnoreCase("728dae81d9d22aca03") || str2.equalsIgnoreCase("119a9b593348fa3e74") || str2.equalsIgnoreCase("04ab87c8d69667878e") || str2.equalsIgnoreCase("4b282d851ebd87a7bb") || str2.equalsIgnoreCase("ed526255313b756e42") || str2.equalsIgnoreCase("ed5ab211362ab25ca7") || str2.equalsIgnoreCase("18f4789a3df48f3b15") || str2.equalsIgnoreCase("67549e44b1c8d8d857") || str2.equalsIgnoreCase("4593c6c54227c4f17d") || str2.equalsIgnoreCase("1c59db29042e7df8ef") || str2.equalsIgnoreCase("a647e3dd42ce9b409b") || str2.equalsIgnoreCase("7e06d6a70b82858113") || str2.equalsIgnoreCase("ef4b5a48595197a373") || str2.equalsIgnoreCase("0ac55f6bebd0330640") || str2.equalsIgnoreCase("1beda9831c78994f43") || str2.equalsIgnoreCase("8a2b9debb15766bff9") || str2.equalsIgnoreCase("da0e7561b10d974216") || str2.equalsIgnoreCase("86257b04b8c303fd9a") || str2.equalsIgnoreCase("a4036b2761c9583fda") || str2.equalsIgnoreCase("18e69f6d5bc820d4d3") || str2.equalsIgnoreCase("a13746cb3d1c83bca6") || str2.equalsIgnoreCase("a4036b2761c9583fda")) {
        throw new LicenseException(n(1));
    }
    // 取license部分内容拼接数字
    // int(str2[2:10],16) << 32 | int(str2[10:18],16)
    long a2 = a(str2);
    // int(str2[0:2],16)
    int b2 = b(str2);
    // long al = -5408575981733630035L;
    // rc5 的 expandkey
    c(al);
    // rc5 加密
    long b3 = b(a2);
    // 将b3的8个字节进行亦或得到一个单字节数
    if (a(b3) != b2) {
        throw new LicenseException(n(1));
    }
    // xx xx xx xx 01 xx xx xx
    this.ae = (int) (((b3 << 32) >>> 32) >>> 24);
    if (this.ae == 1) {
        this.af = LicenseType.USER;
    } else if (this.ae != i2) {
        if (this.ae < i2) {
            throw new LicenseException(n(3));
        }
        throw new LicenseException(n(1));
    } else {
        switch ((int) ((((b3 << 32) >>> 32) >>> 16) & 255)) {
            case 1:
                this.af = LicenseType.USER;
                break;
            case 2:
                this.af = LicenseType.SITE;
                break;
            case 3:
                this.af = LicenseType.MULTI_SITE;
                break;
            default:
                throw new LicenseException(n(1));
        }
    }
    // long ak = 8800536498351690864L;
    // rc5 init
    c(ak);
    try {
        // 0xA58D19C600000000，a = 用户名处理函数
        int j = n(a(str.getBytes("UTF-8")));
        j ^= (int)(b3 >> 32L);
        return 0xA58D19C600000000L | ( j << 32L >>> 32L);
    } catch (UnsupportedEncodingException e2) {
        return -1L;
    }
}


private static final int n(byte[] bArr) {
    byte b2 = 0;
    for (byte b3 : bArr) {
        int i2 = b2 ^ b3;
        b2 = (i2 << 3) | (i2 >>> 29);
    }
    return b2;
}


// 用户名处理函数
private byte[] a(byte[] bArr) {
    int length = bArr.length;
    int i2 = length + 4;
    if (i2 % 8 != 0) {
        i2 += 8 - (i2 % 8);
    }
    byte[] bArr2 = new byte[i2];
    // 字符串转为数据，在前面添加4字节的size
    System.arraycopy(bArr, 0, bArr2, 4, length);
    bArr2[0] = (byte) (length >> 24);
    bArr2[1] = (byte) (length >> 16);
    bArr2[2] = (byte) (length >> 8);
    bArr2[3] = (byte) (length >> 0);
    return b(bArr2);
}

private byte[] b(byte[] bArr) {
    byte[] bArr2 = new byte[bArr.length];
    int length = bArr.length;
    int i2 = 0;
    long j2 = 0;
    for (int i3 = 0; i3 < length; i3++) {
        j2 = (j2 << 8) | (bArr[i3] & 255);
        i2++;
        if (i2 == 8) {
            // 每8个字节进行 rc5 加密， 然后写回
            long b2 = b(j2);
            bArr2[i3 - 7] = (byte) (b2 >>> 56);
            bArr2[i3 - 6] = (byte) (b2 >>> 48);
            bArr2[i3 - 5] = (byte) (b2 >>> 40);
            bArr2[i3 - 4] = (byte) (b2 >>> 32);
            bArr2[i3 - 3] = (byte) (b2 >>> 24);
            bArr2[i3 - 2] = (byte) (b2 >>> 16);
            bArr2[i3 - 1] = (byte) (b2 >>> 8);
            bArr2[i3 - 0] = (byte) (b2 >>> 0);
            i2 = 0;
            j2 = 0;
        }
    }
    return bArr2;
}


// 对返回值进行校验
private boolean n(long j2) {
    // 将b3的8个字节进行亦或得到一个单字节数
    int a2 = a(j2);
    // rc5 init
    c(j2);
    long j3 = j2;
    for (int i2 = 0; i2 < a2 + 35; i2++) {
        // rc5 加密
        j3 = b(j3);
    }
    // long an = 5911726755176091652L;
    return j3 == an;
}


```