
def bezout(a,b):
    r=a
    rp=b
    u=1
    v=0
    up=0
    vp=1
    while rp != 0:
        qr = divmod(r,rp)
        upp = u - qr[0] * up
        vpp = v - qr[0] * vp
        rs = r
        us = u
        vs = v
        r = rp
        u = up
        v = vp
        rp = qr[1]
        up = upp
        vp = vpp
    return (r,u,v)

for i in range(-64,64):
    for j in range(-64,64):
        print(i,',',j,':',str(bezout(i,j)))