import os
import subprocess

HWs = os.listdir(".")

wa = 0

for HW in HWs:
    if not HW.startswith("HW"):
        continue
    for i in range(1, 4):
        clist = [f"./{HW}/p{i}.out < {HW}/test/p{i}.in > result.txt"]
        try:
            proc = subprocess.Popen(clist, shell=True)
        except Exception as e:
            print(e)
            exit(1)
        retcode = proc.wait()
        if retcode != 0:
            print(f"{HW} {i} RE")
            exit(1)

        clist = ["diff", "-Z", "-u", "result.txt", f"{HW}/test/p{i}.ans"]
        try:
            proc = subprocess.Popen(clist, stdout=subprocess.PIPE)
        except Exception as e:
            print(e)
            exit(1)
        retcode = proc.wait()
        output = str(proc.stdout.read())

        if output == "b''":
            print(f"{HW} {i} AC")
        else:
            print(f"{HW} {i} WA")
            print(output)
            wa += 1

# remove result.txt
clist = ["rm", "result.txt"]
proc = subprocess.Popen(clist, stdout=subprocess.PIPE)
proc.wait()

exit(wa)
