import os
import zipfile


class Pair:
    def __init__(self):
        self.name = ""
        self.content = ""


def zip(src, dst):
    zf = zipfile.ZipFile("%s.zip" % (dst), "w", zipfile.ZIP_DEFLATED)
    abs_src = os.path.abspath(src)
    for dirname, subdirs, files in os.walk(src):
        for filename in files:
            absname = os.path.abspath(os.path.join(dirname, filename))
            arcname = absname[len(abs_src) + 1:]
            print("zipping %s as %s" % (os.path.join(dirname, filename), arcname))
            zf.write(absname, arcname)
    zf.close()
def zipstr(dst):
    zf = zipfile.ZipFile("%s.zip" % (dst), "w", zipfile.ZIP_DEFLATED)
    zf.writestr('exemple.txt','texte')
    zf.close()
def read(dst):
    zf = zipfile.ZipFile("%s.zip" % (dst), "r", zipfile.ZIP_DEFLATED)
    out=[]
    for filename in zf.namelist():
        p = Pair()
        p.name=filename
        p.content=zf.open(filename).read().decode("utf-8")
        out.append(p)
    zf.close()
    return out