
from rc5 import _expand_key,_encrypt_block,_rotate_left,_decrypt_block
import random

def long_to_bytes(num):
    num &= 2**64 - 1 
    return num.to_bytes(8,byteorder='little',signed=False)
  
def bytes_to_long(b):
    return int.from_bytes(b,byteorder='little',signed=False)
    
def num_to_list(arr, off, num, count):
    for i in range(count):
        arr[off+i] = ( num >> ( 8 * (count-i-1) ) ) & 0xff
  
def list_to_int(arr,off,count):
    num = 0
    for i in range(count):
        num = (num << 8) | ( arr[off+i] & 0xff)
    return num
  
def name_to_bytes(name):
    length = len(name)
    arr = [0] * 4
    num_to_list(arr,0,length,4)
    t = arr + [ord(_) for _ in name]
    r = len(t) % 8
    if (r):
        t += (8 - r) * [0]
    return t

def long_xor(num):
    t = 0
    for i in range(8):
        t ^= num&0xff
        num >>= 8
    
    return t

def init_rc5( key_long ):
    key = long_to_bytes(key_long)
    S = _expand_key(key,32,12)
    return S
    

def deal_name(name):
    expand_key = init_rc5(0x7a21c951691cd470)
    arr = name_to_bytes(name)
    new_arr = [0] * len(arr)
    for i in range(0,len(arr),8):
        num = long_to_bytes( list_to_int(arr,i,8) )
        t = _encrypt_block(num,expand_key,64,12)
        num =  bytes_to_long( t )
        num_to_list(new_arr,i,num,8)
   
    b = 0
    for i in range(len(new_arr)):
        # 恶心，高位扩展
        a = new_arr[i] | 0xffffff00 if  new_arr[i] & 0x80  else new_arr[i]
        t = b ^ a
        b = _rotate_left(t,3,32)
    
    return b & 0xffffffff

def deal_license(lic):
    a = (int(lic[2:10],16) << 32) | int(lic[10:18],16)
    b = int(lic[0:2],16)
    expand_key = init_rc5(-5408575981733630035)
    c = _encrypt_block(long_to_bytes(a),expand_key,64,12)
    c = bytes_to_long(c)
    return c

def get_serail( num ):
    rn = random.randint(0,0xffff)
    serial = (num << 32) | 0x04020000 | rn #0x1CAD6BC
    expand_key = init_rc5(-5408575981733630035)
    c = _decrypt_block(long_to_bytes(serial),expand_key,64,12)
    
    a = long_xor(serial)
    
    t = c + a.to_bytes(1,byteorder='little',signed=False)
    return t[::-1].hex()
    

def check(num):
    n = long_xor(num)
    expand_key = init_rc5(num)
    t = long_to_bytes( num )
    for i in range( (n + 35) & 0xff):
        t = _encrypt_block(t,expand_key,64,12)
    
    t = bytes_to_long( t )
    if t == 0x520aac2983719004:
        return True
        
    return False

'''
生成的license
https://www.zzzmode.com/mytools/charles/

test
418d594b8d21d39020

test2
0c18080103e2a7a7eb

abna
09894df985f814fe78
'''


if __name__=='__main__':
    name = input()
    t = deal_name(name)
    lic = get_serail(t ^ 1418211210)
    print("name = ",name)
    print("license = ",lic)
    c = deal_license(lic)
    if check( (t ^ (c >> 32)) | 0xA58D19C600000000):
        print("check ok.")
    exit()
